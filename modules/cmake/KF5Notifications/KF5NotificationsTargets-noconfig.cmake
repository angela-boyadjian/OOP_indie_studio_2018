#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "KF5::Notifications" for configuration ""
set_property(TARGET KF5::Notifications APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(KF5::Notifications PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "KF5::CoreAddons;KF5::ConfigCore;KF5::WindowSystem;KF5::Codecs;Qt5::TextToSpeech;Qt5::X11Extras;dbusmenu-qt5"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libKF5Notifications.so.5.58.0"
  IMPORTED_SONAME_NOCONFIG "libKF5Notifications.so.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS KF5::Notifications )
list(APPEND _IMPORT_CHECK_FILES_FOR_KF5::Notifications "${_IMPORT_PREFIX}/lib/libKF5Notifications.so.5.58.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
