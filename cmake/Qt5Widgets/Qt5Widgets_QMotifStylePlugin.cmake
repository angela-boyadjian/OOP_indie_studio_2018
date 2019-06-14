
add_library(Qt5::QMotifStylePlugin MODULE IMPORTED)

_populate_Widgets_plugin_properties(QMotifStylePlugin RELEASE "styles/libqmotifstyle.so")

list(APPEND Qt5Widgets_PLUGINS Qt5::QMotifStylePlugin)
