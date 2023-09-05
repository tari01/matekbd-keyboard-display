# matekbd-keyboard-display

add_executable ("matekbd-keyboard-display" matekbd-keyboard-display.c)
target_compile_definitions ("matekbd-keyboard-display" PUBLIC G_LOG_DOMAIN="matekbd-keyboard-display")
target_link_libraries ("matekbd-keyboard-display" ${DEPS_LIBRARIES})
target_include_directories ("matekbd-keyboard-display" PUBLIC ${DEPS_INCLUDE_DIRS})
install (TARGETS "matekbd-keyboard-display" RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})
