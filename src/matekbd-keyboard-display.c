/*
 * Copyright (C) 2006 Sergey V. Udaltsov <svu@gnome.org>
 * Copyright (C) 2023 Robert Tari <robert@tari.in>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <libxklavier/xklavier.h>
#include <libmatekbd/matekbd-keyboard-config.h>
#include <libmatekbd/matekbd-keyboard-drawing.h>

static GMainLoop *m_pLoop;

static void onDestroy ()
{
    g_main_loop_quit (m_pLoop);
}

int main (int argc, char **argv)
{
    gint nGroup = -1;
    GOptionEntry lEntries[] =
    {
        {"group", 'g', 0, G_OPTION_ARG_INT, &nGroup, "Group to display", "group number (1, 2, 3, 4)"},
        { NULL }
    };
    GError *pError = NULL;
    gdk_set_allowed_backends ("x11");
    gtk_init_with_args (&argc, &argv, NULL, lEntries, NULL, &pError);

    if (pError)
    {
        g_critical ("Error initializing GTK: %s", pError->message);
        exit (1);
    }

    GdkDisplay *pDisplay = gdk_display_get_default ();
    XklEngine *pEngine = xkl_engine_get_instance (GDK_DISPLAY_XDISPLAY (pDisplay));
    xkl_engine_start_listen (pEngine, XKLL_TRACK_KEYBOARD_STATE);
    XklConfigRegistry *pRegistry = xkl_config_registry_get_instance (pEngine);
    xkl_config_registry_load (pRegistry, TRUE);
    XklConfigRec *pConfigRec = xkl_config_rec_new ();
    xkl_config_rec_get_from_server (pConfigRec, pEngine);
    XklState *pState = xkl_engine_get_current_state (pEngine);
    guint nGroups = xkl_engine_get_num_groups (pEngine);

    if (nGroup != -1)
    {
        if (nGroup < 1 || nGroup > nGroups)
        {
            g_critical ("The group number is invalid: %d", nGroup);
            exit (2);
        }
        else
        {
            nGroup -= 1;
        }
    }
    else
    {
        nGroup = pState->group;
    }

    const gchar *sMerged = matekbd_keyboard_config_merge_items (pConfigRec->layouts[nGroup], pConfigRec->variants[nGroup]);
    gchar *sLayoutShort = NULL;
    gchar *sLayoutLong = NULL;
    gchar *sVariantShort = NULL;
    gchar *sVariantLong = NULL;
    matekbd_keyboard_config_get_descriptions (pRegistry, sMerged, &sLayoutShort, &sLayoutLong, &sVariantShort, &sVariantLong);
    const gchar *sLayout = matekbd_keyboard_config_format_full_layout (sLayoutLong, sVariantLong);
    GtkWidget *pDlg = matekbd_keyboard_drawing_new_dialog (nGroup, (gchar*) sLayout);
    g_signal_connect (pDlg, "destroy", onDestroy, NULL);
    gtk_widget_show_all (pDlg);
    m_pLoop = g_main_loop_new (NULL, TRUE);
    g_main_loop_run (m_pLoop);
    g_object_unref (pRegistry);
    g_object_unref (pEngine);

    return 0;
}
