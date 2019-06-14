#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ical" for configuration "Release"
set_property(TARGET ical APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ical PROPERTIES
  IMPORTED_LOCATION_RELEASE "/usr/lib/libical.so.3.0.4"
  IMPORTED_SONAME_RELEASE "libical.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS ical )
list(APPEND _IMPORT_CHECK_FILES_FOR_ical "/usr/lib/libical.so.3.0.4" )

# Import target "ical_cxx" for configuration "Release"
set_property(TARGET ical_cxx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ical_cxx PROPERTIES
  IMPORTED_LOCATION_RELEASE "/usr/lib/libical_cxx.so.3.0.4"
  IMPORTED_SONAME_RELEASE "libical_cxx.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS ical_cxx )
list(APPEND _IMPORT_CHECK_FILES_FOR_ical_cxx "/usr/lib/libical_cxx.so.3.0.4" )

# Import target "icalss" for configuration "Release"
set_property(TARGET icalss APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(icalss PROPERTIES
  IMPORTED_LOCATION_RELEASE "/usr/lib/libicalss.so.3.0.4"
  IMPORTED_SONAME_RELEASE "libicalss.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS icalss )
list(APPEND _IMPORT_CHECK_FILES_FOR_icalss "/usr/lib/libicalss.so.3.0.4" )

# Import target "icalss_cxx" for configuration "Release"
set_property(TARGET icalss_cxx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(icalss_cxx PROPERTIES
  IMPORTED_LOCATION_RELEASE "/usr/lib/libicalss_cxx.so.3.0.4"
  IMPORTED_SONAME_RELEASE "libicalss_cxx.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS icalss_cxx )
list(APPEND _IMPORT_CHECK_FILES_FOR_icalss_cxx "/usr/lib/libicalss_cxx.so.3.0.4" )

# Import target "icalvcal" for configuration "Release"
set_property(TARGET icalvcal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(icalvcal PROPERTIES
  IMPORTED_LOCATION_RELEASE "/usr/lib/libicalvcal.so.3.0.4"
  IMPORTED_SONAME_RELEASE "libicalvcal.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS icalvcal )
list(APPEND _IMPORT_CHECK_FILES_FOR_icalvcal "/usr/lib/libicalvcal.so.3.0.4" )

# Import target "ical-glib" for configuration "Release"
set_property(TARGET ical-glib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ical-glib PROPERTIES
  IMPORTED_LOCATION_RELEASE "/usr/lib/libical-glib.so.3.0.4"
  IMPORTED_SONAME_RELEASE "libical-glib.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS ical-glib )
list(APPEND _IMPORT_CHECK_FILES_FOR_ical-glib "/usr/lib/libical-glib.so.3.0.4" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
