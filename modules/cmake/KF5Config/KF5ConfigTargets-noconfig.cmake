#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "KF5::ConfigCore" for configuration ""
set_property(TARGET KF5::ConfigCore APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(KF5::ConfigCore PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "Qt5::DBus"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libKF5ConfigCore.so.5.58.0"
  IMPORTED_SONAME_NOCONFIG "libKF5ConfigCore.so.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS KF5::ConfigCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_KF5::ConfigCore "${_IMPORT_PREFIX}/lib/libKF5ConfigCore.so.5.58.0" )

# Import target "KF5::ConfigGui" for configuration ""
set_property(TARGET KF5::ConfigGui APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(KF5::ConfigGui PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libKF5ConfigGui.so.5.58.0"
  IMPORTED_SONAME_NOCONFIG "libKF5ConfigGui.so.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS KF5::ConfigGui )
list(APPEND _IMPORT_CHECK_FILES_FOR_KF5::ConfigGui "${_IMPORT_PREFIX}/lib/libKF5ConfigGui.so.5.58.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
