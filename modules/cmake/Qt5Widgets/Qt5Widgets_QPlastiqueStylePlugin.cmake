
add_library(Qt5::QPlastiqueStylePlugin MODULE IMPORTED)

_populate_Widgets_plugin_properties(QPlastiqueStylePlugin RELEASE "styles/libqplastiquestyle.so")

list(APPEND Qt5Widgets_PLUGINS Qt5::QPlastiqueStylePlugin)
