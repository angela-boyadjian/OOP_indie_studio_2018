#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "KF5::NewStuff" for configuration ""
set_property(TARGET KF5::NewStuff APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(KF5::NewStuff PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "KF5::KIOCore;KF5::KIOWidgets;KF5::Completion;KF5::I18n;KF5::ItemViews;KF5::IconThemes;KF5::TextWidgets"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libKF5NewStuff.so.5.58.0"
  IMPORTED_SONAME_NOCONFIG "libKF5NewStuff.so.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS KF5::NewStuff )
list(APPEND _IMPORT_CHECK_FILES_FOR_KF5::NewStuff "${_IMPORT_PREFIX}/lib/libKF5NewStuff.so.5.58.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
