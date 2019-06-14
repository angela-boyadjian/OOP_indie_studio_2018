
add_library(Qt5::QTextToSpeechEngineFlite MODULE IMPORTED)

_populate_TextToSpeech_plugin_properties(QTextToSpeechEngineFlite RELEASE "texttospeech/libqttexttospeech_flite.so")

list(APPEND Qt5TextToSpeech_PLUGINS Qt5::QTextToSpeechEngineFlite)
