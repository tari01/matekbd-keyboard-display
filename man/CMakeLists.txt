# matekbd-keyboard-display.1.gz

file (ARCHIVE_CREATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/matekbd-keyboard-display.1.gz" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/matekbd-keyboard-display.1" FORMAT raw COMPRESSION GZip)
install (FILES "${CMAKE_CURRENT_BINARY_DIR}/matekbd-keyboard-display.1.gz" DESTINATION "${CMAKE_INSTALL_FULL_MANDIR}/man1")
