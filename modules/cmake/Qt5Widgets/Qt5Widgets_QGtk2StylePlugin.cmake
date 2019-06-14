
add_library(Qt5::QGtk2StylePlugin MODULE IMPORTED)

_populate_Widgets_plugin_properties(QGtk2StylePlugin RELEASE "styles/libqgtk2style.so")

list(APPEND Qt5Widgets_PLUGINS Qt5::QGtk2StylePlugin)
