# This file was generated by ecm_install_qch_export(). DO NOT EDIT!

if (NOT TARGET KF5JobWidgets_QCH)

add_custom_target(KF5JobWidgets_QCH)
set_target_properties(KF5JobWidgets_QCH PROPERTIES
    DOXYGEN_TAGFILE "/usr/share/doc/qt/KF5JobWidgets.tags"
    QHP_NAMESPACE "org.kde.KJobWidgets"
    QHP_NAMESPACE_VERSIONED "org.kde.KJobWidgets.5_58_0"
    QHP_VIRTUALFOLDER "kjobwidgets"
    IMPORTED TRUE
)
set_property(TARGET KF5JobWidgets_QCH PROPERTY LINK_QCHS KF5CoreAddons_QCH;Qt5Widgets_QCH;Qt5Gui_QCH;Qt5Core_QCH)

endif()
