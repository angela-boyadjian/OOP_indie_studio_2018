# This file was generated by ecm_install_qch_export(). DO NOT EDIT!

if (NOT TARGET KF5GlobalAccel_QCH)

add_custom_target(KF5GlobalAccel_QCH)
set_target_properties(KF5GlobalAccel_QCH PROPERTIES
    DOXYGEN_TAGFILE "/usr/share/doc/qt/KF5GlobalAccel.tags"
    QHP_NAMESPACE "org.kde.KGlobalAccel"
    QHP_NAMESPACE_VERSIONED "org.kde.KGlobalAccel.5_58_0"
    QHP_VIRTUALFOLDER "kglobalaccel"
    IMPORTED TRUE
)
set_property(TARGET KF5GlobalAccel_QCH PROPERTY LINK_QCHS Qt5Widgets_QCH;Qt5DBus_QCH)

endif()
