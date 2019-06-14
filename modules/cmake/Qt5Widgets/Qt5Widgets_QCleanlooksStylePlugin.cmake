
add_library(Qt5::QCleanlooksStylePlugin MODULE IMPORTED)

_populate_Widgets_plugin_properties(QCleanlooksStylePlugin RELEASE "styles/libqcleanlooksstyle.so")

list(APPEND Qt5Widgets_PLUGINS Qt5::QCleanlooksStylePlugin)
