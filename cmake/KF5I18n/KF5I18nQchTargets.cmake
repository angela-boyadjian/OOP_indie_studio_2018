# This file was generated by ecm_install_qch_export(). DO NOT EDIT!

if (NOT TARGET KF5I18n_QCH)

add_custom_target(KF5I18n_QCH)
set_target_properties(KF5I18n_QCH PROPERTIES
    DOXYGEN_TAGFILE "/usr/share/doc/qt/KF5I18n.tags"
    QHP_NAMESPACE "org.kde.KI18n"
    QHP_NAMESPACE_VERSIONED "org.kde.KI18n.5_58_0"
    QHP_VIRTUALFOLDER "ki18n"
    IMPORTED TRUE
)
set_property(TARGET KF5I18n_QCH PROPERTY LINK_QCHS Qt5Core_QCH)

endif()
