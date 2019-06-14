#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "PolkitQt5-1::Core" for configuration ""
set_property(TARGET PolkitQt5-1::Core APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(PolkitQt5-1::Core PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "Qt5::DBus"
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "Qt5::Core"
  IMPORTED_LOCATION_NOCONFIG "/usr/lib/libpolkit-qt5-core-1.so.1.112.0"
  IMPORTED_SONAME_NOCONFIG "libpolkit-qt5-core-1.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS PolkitQt5-1::Core )
list(APPEND _IMPORT_CHECK_FILES_FOR_PolkitQt5-1::Core "/usr/lib/libpolkit-qt5-core-1.so.1.112.0" )

# Import target "PolkitQt5-1::Gui" for configuration ""
set_property(TARGET PolkitQt5-1::Gui APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(PolkitQt5-1::Gui PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "Qt5::Core;Qt5::DBus"
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "PolkitQt5-1::Core;Qt5::Widgets"
  IMPORTED_LOCATION_NOCONFIG "/usr/lib/libpolkit-qt5-gui-1.so.1.112.0"
  IMPORTED_SONAME_NOCONFIG "libpolkit-qt5-gui-1.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS PolkitQt5-1::Gui )
list(APPEND _IMPORT_CHECK_FILES_FOR_PolkitQt5-1::Gui "/usr/lib/libpolkit-qt5-gui-1.so.1.112.0" )

# Import target "PolkitQt5-1::Agent" for configuration ""
set_property(TARGET PolkitQt5-1::Agent APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(PolkitQt5-1::Agent PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "Qt5::Core;PolkitQt5-1::Core"
  IMPORTED_LOCATION_NOCONFIG "/usr/lib/libpolkit-qt5-agent-1.so.1.112.0"
  IMPORTED_SONAME_NOCONFIG "libpolkit-qt5-agent-1.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS PolkitQt5-1::Agent )
list(APPEND _IMPORT_CHECK_FILES_FOR_PolkitQt5-1::Agent "/usr/lib/libpolkit-qt5-agent-1.so.1.112.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
