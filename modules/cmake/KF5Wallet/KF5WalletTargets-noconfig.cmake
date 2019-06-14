#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "KF5::Wallet" for configuration ""
set_property(TARGET KF5::Wallet APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(KF5::Wallet PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "Qt5::DBus;Qt5::Widgets;KF5::WindowSystem;KF5::ConfigCore"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libKF5Wallet.so.5.58.0"
  IMPORTED_SONAME_NOCONFIG "libKF5Wallet.so.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS KF5::Wallet )
list(APPEND _IMPORT_CHECK_FILES_FOR_KF5::Wallet "${_IMPORT_PREFIX}/lib/libKF5Wallet.so.5.58.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
