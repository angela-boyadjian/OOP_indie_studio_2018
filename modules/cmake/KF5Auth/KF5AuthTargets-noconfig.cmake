#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "KF5::AuthCore" for configuration ""
set_property(TARGET KF5::AuthCore APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(KF5::AuthCore PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "Qt5::DBus"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libKF5AuthCore.so.5.58.0"
  IMPORTED_SONAME_NOCONFIG "libKF5AuthCore.so.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS KF5::AuthCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_KF5::AuthCore "${_IMPORT_PREFIX}/lib/libKF5AuthCore.so.5.58.0" )

# Import target "KF5::Auth" for configuration ""
set_property(TARGET KF5::Auth APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(KF5::Auth PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "Qt5::Widgets"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libKF5Auth.so.5.58.0"
  IMPORTED_SONAME_NOCONFIG "libKF5Auth.so.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS KF5::Auth )
list(APPEND _IMPORT_CHECK_FILES_FOR_KF5::Auth "${_IMPORT_PREFIX}/lib/libKF5Auth.so.5.58.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
