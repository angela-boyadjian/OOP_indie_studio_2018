#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Phonon::phonon4qt5" for configuration ""
set_property(TARGET Phonon::phonon4qt5 APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(Phonon::phonon4qt5 PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "Qt5::Core;Qt5::Widgets;Qt5::DBus"
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG ""
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libphonon4qt5.so.4.10.2"
  IMPORTED_SONAME_NOCONFIG "libphonon4qt5.so.4"
  )

list(APPEND _IMPORT_CHECK_TARGETS Phonon::phonon4qt5 )
list(APPEND _IMPORT_CHECK_FILES_FOR_Phonon::phonon4qt5 "${_IMPORT_PREFIX}/lib/libphonon4qt5.so.4.10.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
