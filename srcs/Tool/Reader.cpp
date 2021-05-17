/*
** EPITECH PROJECT, 2019
** Reader.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include <fstream>
#include <numeric>
#include <algorithm>
//#include <boost/algorithm/string.hpp>
#include <sstream>

#include "Reader.hpp"

std::vector<std::string> Reader::vectorRead(const std::string &filename)
{
    std::vector<std::string> vector;
    std::ifstream file;
    std::string line;

    file.open(filename);
    if (file.fail()) {
        std::cerr << "Reader : " << filename <<
                  ": No such file or directory" << std::endl;
        std::stringstream errMsg;
        errMsg << "Could not load config file '" << filename << "'";
        std::cout << "fail here" << std::endl;
        throw std::runtime_error(
            (std::ostringstream()
                << "Could not load file '"
                << filename
                << "'"
            ).str()
        );
    }
    while (std::getline(file, line))
        vector.push_back(line);
    file.close();
    return vector;
}

std::string Reader::stringRead(const std::string &filename)
{
    auto v = vectorRead(filename);
    std::string s;

    s = std::accumulate(begin(v), end(v), s);
    return s;
}

std::vector<std::string> Reader::readDir(const std::string &dirname)
{
    DIR *dir = opendir(dirname.c_str());
    std::vector<std::string> read;
    struct dirent *ent;
    if (dir != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            if (ent->d_name[0] != '.')
                read.push_back(dirname + ent->d_name);
        }
        closedir(dir);
    } else {
        throw std::exception(); // tempo
    }
    // std::cout << std::endl;
    return read;
}

std::vector<std::string> &splitStrA(const std::string &InputString, char delimiterChar, std::vector<std::string> &ResultVec) {
    std::stringstream sStream(InputString);
    std::string item;
    while (std::getline(sStream, item, delimiterChar)) {
        ResultVec.push_back(item);
    }
    return ResultVec;
}

std::vector<SpriteInfo> Reader::readSpriteInfo(const std::string &filename)
{
    auto v = vectorRead(filename);
    std::vector<SpriteInfo> vec;

    for (auto &line : v) {
        std::vector<std::string> splitLine;
        splitStrA(line, ';', splitLine);
        vec.emplace_back(splitLine[0], splitLine[1], splitLine[2],
                         irr::core::vector3df(std::stof(splitLine[3]),
                                              std::stof(splitLine[4]),
                                              std::stof(splitLine[5])),
                                              static_cast<bool>(std::stof(splitLine[6])));
    }
    return vec;
}