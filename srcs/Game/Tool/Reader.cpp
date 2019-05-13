/*
** EPITECH PROJECT, 2019
** Reader.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include <fstream>
#include <numeric>
#include <algorithm>
#include <boost/algorithm/string.hpp>
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
        throw std::exception();  // A changer
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

std::vector<SpriteInfo> Reader::readSpriteInfo(const std::string &filename)
{
    auto v = vectorRead(filename);
    std::vector<SpriteInfo> vec;

    for (auto &line : v) {
        std::stringstream test(line);
        std::vector<std::string> splitLine;
        std::string segment;
        boost::split(splitLine, line, boost::is_any_of(";"));
        std::cout << splitLine[3] << " " << splitLine[4] << " " << splitLine[5] << std::endl;
        vec.emplace_back(splitLine[0], splitLine[1], splitLine[2],
                         irr::core::vector3df(std::stof(splitLine[3]),
                                              std::stof(splitLine[4]),
                                              std::stof(splitLine[5])));
    }
    return vec;
}