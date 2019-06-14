#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "KF5::XmlGui" for configuration ""
set_property(TARGET KF5::XmlGui APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(KF5::XmlGui PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "Qt5::Network;Qt5::PrintSupport;KF5::CoreAddons;KF5::WidgetsAddons;KF5::ItemViews;KF5::I18n;KF5::IconThemes;KF5::TextWidgets;KF5::WindowSystem;KF5::Attica;KF5::GlobalAccel"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libKF5XmlGui.so.5.58.0"
  IMPORTED_SONAME_NOCONFIG "libKF5XmlGui.so.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS KF5::XmlGui )
list(APPEND _IMPORT_CHECK_FILES_FOR_KF5::XmlGui "${_IMPORT_PREFIX}/lib/libKF5XmlGui.so.5.58.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
