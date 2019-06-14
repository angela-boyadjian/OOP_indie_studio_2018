
add_library(Qt5::QIBaseDriverPlugin MODULE IMPORTED)

_populate_Sql_plugin_properties(QIBaseDriverPlugin RELEASE "sqldrivers/libqsqlibase.so")

list(APPEND Qt5Sql_PLUGINS Qt5::QIBaseDriverPlugin)
