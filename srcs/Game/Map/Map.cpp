/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Map
*/
#include <irrlicht.h>
#include <zconf.h>

#include "Map.hpp"
#include "Display.hpp"
#include "Reader.hpp"

Map::Map(std::string const &filename) : _filename(filename)
{
}

Map::~Map()
{
}

void Map::displayMap(Display &d)
{

}

// NOTE Load les data qui serviront a load les objets 3D

void Map::preload()
{
    Reader reader;
    std::vector<std::string> vec;

    _data._mapWall = reader.vectorRead(_filename);
    auto infosWall = reader.readSpriteInfo(_data._mapWall.back());
    auto infosGround = reader.readSpriteInfo(_data._mapWall[_data._mapWall.size() - 2]);
    for (auto &info : infosWall) {
        std::cout << info._referTo[0] << std::endl;
        _data._rulesWall.insert({info._referTo[0], info});
    }
    for (auto &info : infosGround)
        _data._rulesGround.insert({info._referTo[0], info});
    _data._nbEnnemie = static_cast<unsigned int>(std::stoi(_data._mapWall[0]));
    _data._time = static_cast<unsigned int>(std::stoi(_data._mapWall[1]));
    _data._mapWall.erase(_data._mapWall.end() - 2, _data._mapWall.end());
    _data._mapWall.erase(_data._mapWall.begin(), _data._mapWall.begin() + 2);

    // GESTION D'ERREUR A AJOUTER;


}

// NOTE Ajoute une tuile a la map

void Map::addTileToMap(Display &d, char value, irr::core::vector3df origine, std::unordered_map<char, SpriteInfo> &rules, float size)
{
    auto pos = rules.find(value);

    if (pos != rules.end()) {
        if (pos->second._messPath == "Cube")
            _3dMap.emplace_back(d._scenes->addCubeSceneNode(size, 0, -1));
        else {
            irr::core::vector3df scale(size / pos->second._size.X,
                                       size / pos->second._size.Y,
                                       size / pos->second._size.Z);
            _3dMap.emplace_back(d._scenes->addAnimatedMeshSceneNode(
                d._scenes->getMesh(
                    pos->second._messPath.c_str())));
            _3dMap.back()->setScale(scale);
            _3dMap.back()->setRotation(irr::core::vector3df(-90.0f, 0, 0));
        }
        _3dMap.back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _3dMap.back()->setMaterialTexture(0, d._driver->getTexture(
           pos->second._texPath.c_str()));
        _3dMap.back()->setPosition(origine);
    }
}

// NOTE load les objets 3D de la map

void Map::loadWall(Display &d)
{
    auto x = 0.0f;
    auto y = 10.0f;

    for (__attribute__((unused)) auto tile : _data._mapWall[0]) {
        addTileToMap(d, '/', irr::core::vector3df(x, 10.0f, 40.0f),
                     _data._rulesWall, 10.0f);
        x += 10.0f;
    }
    for (std::size_t i = 0;  i != _data._mapWall.size() + 2; i++) {
        addTileToMap(d, '/', irr::core::vector3df(x, y, 40.0f),
                     _data._rulesWall, 10.0f);
        addTileToMap(d, '/', irr::core::vector3df(0 - 10.0f, y, 40.0f),
                     _data._rulesWall, 10.0f);
        y -= 10.0f;
        std::cout << i << std::endl;
    }
    x = 0.0f;
    for (__attribute__((unused)) auto tile : _data._mapWall[0]) {
        addTileToMap(d, '/', irr::core::vector3df(x, y + 10.0f, 40.0f),
                     _data._rulesWall, 10.0f);
        x += 10.0f;
    }
    x = 0;
    y = 0;
    for (auto &line : _data._mapWall) {
        for (auto tile : line) {
            addTileToMap(d, tile, irr::core::vector3df(x, y, 40.0f), _data._rulesWall, 9.0f);
            x += 10.0f;
        }
        x = 0;
        y -= 10.0f;
    }
}

void Map::loadGround(Display &d)
{
    unsigned int value = 0;
    auto x = 0.0f;
    auto y = 0.0f;
    auto base = _data._rulesGround.begin()->first;

    for (auto &line : _data._mapWall) {
        for (__attribute__((unused)) auto tile : line) {
            addTileToMap(d, static_cast<char>(base - value), irr::core::vector3df(x, y, 50.0f), _data._rulesGround, 10.0f);
            _3dMap.back()->setScale(irr::core::vector3df(10 / 9, 10 / 9, 10 / 9));
            value += 1;
            if (value > _data._rulesGround.size() - 1)
                value = 0;
            x += 10.0f;
        }
        x = 0;
        y -= 10.0f;
    }
}

void Map::load(Display &d)
{
    irr::SKeyMap keyMap[5];                             // re-assigne les commandes
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;           // avancer
    keyMap[0].KeyCode = irr::KEY_KEY_Z;                 // w
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD;          // reculer
    keyMap[1].KeyCode = irr::KEY_KEY_S;                 // s            //NOTE TEMPO
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;            // a gauche
    keyMap[2].KeyCode = irr::KEY_KEY_Q;                 // a
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;           // a droite
    keyMap[3].KeyCode = irr::KEY_KEY_D;                 // d
    keyMap[4].Action = irr::EKA_JUMP_UP;                // saut
    keyMap[4].KeyCode = irr::KEY_SPACE;                 // barre espace

    d._scenes->addCameraSceneNodeFPS(                // ajout de la camera FPS
        0, 100.0f, 0.1f, -1, keyMap, 5);
    preload();
    loadGround(d);
    loadWall(d);
}