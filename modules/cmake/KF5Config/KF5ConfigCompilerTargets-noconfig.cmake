#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "KF5::kconfig_compiler" for configuration ""
set_property(TARGET KF5::kconfig_compiler APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(KF5::kconfig_compiler PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/kf5/kconfig_compiler_kf5"
  )

list(APPEND _IMPORT_CHECK_TARGETS KF5::kconfig_compiler )
list(APPEND _IMPORT_CHECK_FILES_FOR_KF5::kconfig_compiler "${_IMPORT_PREFIX}/lib/kf5/kconfig_compiler_kf5" )

# Import target "KF5::kconf_update" for configuration ""
set_property(TARGET KF5::kconf_update APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(KF5::kconf_update PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/kf5/kconf_update"
  )

list(APPEND _IMPORT_CHECK_TARGETS KF5::kconf_update )
list(APPEND _IMPORT_CHECK_FILES_FOR_KF5::kconf_update "${_IMPORT_PREFIX}/lib/kf5/kconf_update" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
