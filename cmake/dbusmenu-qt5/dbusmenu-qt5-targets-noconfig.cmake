#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "dbusmenu-qt5" for configuration ""
set_property(TARGET dbusmenu-qt5 APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(dbusmenu-qt5 PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "Qt5::Gui;Qt5::Core;Qt5::DBus;Qt5::Widgets"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libdbusmenu-qt5.so.2.6.0"
  IMPORTED_SONAME_NOCONFIG "libdbusmenu-qt5.so.2"
  )

list(APPEND _IMPORT_CHECK_TARGETS dbusmenu-qt5 )
list(APPEND _IMPORT_CHECK_FILES_FOR_dbusmenu-qt5 "${_IMPORT_PREFIX}/lib/libdbusmenu-qt5.so.2.6.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
