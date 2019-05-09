#pragma once

#include <exception>
#include <string>

class DisplayException : public std::exception {
public:
    explicit DisplayException(const std::string &error) : _message("[DISPLAY]: " + error) {}
    ~DisplayException() override = default;
    virtual const char *what() const throw() { return _message.c_str(); }

private:
    std::string _message;
};

class DeviceCreationError : public DisplayException {
public:
    DeviceCreationError() : DisplayException("Device creation failed") {}
    ~DeviceCreationError() final = default;
};

class MeshCreationError : public DisplayException {
public:
    MeshCreationError() : DisplayException("Mesh creation failed") {}
    ~MeshCreationError() final = default;
};

class MeshSceneCreationError : public DisplayException {
public:
    MeshSceneCreationError() : DisplayException("MeshScene creation failed") {}
    ~MeshSceneCreationError() = default;
};