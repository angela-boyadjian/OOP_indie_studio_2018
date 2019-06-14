#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "KF5::Codecs" for configuration ""
set_property(TARGET KF5::Codecs APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(KF5::Codecs PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libKF5Codecs.so.5.58.0"
  IMPORTED_SONAME_NOCONFIG "libKF5Codecs.so.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS KF5::Codecs )
list(APPEND _IMPORT_CHECK_FILES_FOR_KF5::Codecs "${_IMPORT_PREFIX}/lib/libKF5Codecs.so.5.58.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
