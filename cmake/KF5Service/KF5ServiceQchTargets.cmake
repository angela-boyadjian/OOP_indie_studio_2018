# This file was generated by ecm_install_qch_export(). DO NOT EDIT!

if (NOT TARGET KF5Service_QCH)

add_custom_target(KF5Service_QCH)
set_target_properties(KF5Service_QCH PROPERTIES
    DOXYGEN_TAGFILE "/usr/share/doc/qt/KF5Service.tags"
    QHP_NAMESPACE "org.kde.KService"
    QHP_NAMESPACE_VERSIONED "org.kde.KService.5_58_0"
    QHP_VIRTUALFOLDER "kservice"
    IMPORTED TRUE
)
set_property(TARGET KF5Service_QCH PROPERTY LINK_QCHS KF5Config_QCH;KF5CoreAddons_QCH)

endif()
