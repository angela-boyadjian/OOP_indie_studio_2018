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

void Map::preload()
{
    Reader reader;
    std::vector<std::string> vec;

    _data._mapData = reader.vectorRead(_filename);
    auto infos = reader.readSpriteInfo(_data._mapData.back());
    for (auto &info : infos)
        _data._rules.insert({info._referTo[0], info});
    _data._nbEnnemie = static_cast<unsigned int>(std::stoi(_data._mapData[0]));
    _data._time = static_cast<unsigned int>(std::stoi(_data._mapData[1]));
    _data._mapData.erase(_data._mapData.end() - 1, _data._mapData.end());
    _data._mapData.erase(_data._mapData.begin(), _data._mapData.begin() + 2);

    // GESTION D'ERREUR A AJOUTER;


}

void Map::addTileToMap(Display &d, char value, irr::core::vector3df origine)
{
    auto pos = _data._rules.find(value);

    if (pos != _data._rules.end()) {
        if (pos->second._messPath == "Cube")
            _3dMap.emplace_back(d._scenes->addCubeSceneNode(10.0f, 0, -1));
        else {
            irr::core::vector3df scale(10 / pos->second._size.X,
                                       10 / pos->second._size.Y,
                                       10 / pos->second._size.Z);
            _3dMap.emplace_back(d._scenes->addAnimatedMeshSceneNode(
                d._scenes->getMesh(
                    pos->second._messPath.c_str())));
            _3dMap.back()->setScale(scale);
            _3dMap.back()->setRotation(irr::core::vector3df(-90.0f, 0, 0));
        }
        _3dMap.back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _3dMap.back()->setMaterialTexture(0, d._driver->getTexture(
            _data._rules.find(value)->second._texPath.c_str()));
        _3dMap.back()->setPosition(origine);
    }
    _3dMap.emplace_back(d._scenes->addCubeSceneNode(10.0f, 0, -1));
    origine.Z += 10;
    _3dMap.back()->setPosition(origine);
    _3dMap.back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _3dMap.back()->setMaterialTexture(0, d._driver->getTexture("./../resources/maps/images.jpg"));
}

void Map::load(Display &d)
{
    auto x = 0.0f;
    auto y = 0.0f;

    preload();

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
    for (auto &line : _data._mapData) {
        for (auto tile : line) {
            addTileToMap(d, tile, irr::core::vector3df(x, y, 40.0f));
            x += 10.0f;
        }
        x = 0;
        y -= 10.0f;
    }
}

/*
 * for (auto &line : _data._mapData) {
        for (auto tile : line) {
            auto got = _data._rules.find(tile);
            if (got != _data._rules.end()) {
                std::cout << _data._rules.find(tile)->second._messPath
                          << std::endl;
                _3dMap.emplace_back(
                    d._scenes->addAnimatedMeshSceneNode(          // via le scene manager
                        d._scenes->getMesh(
                            _data._rules.find(
                                tile)->second._messPath.c_str())));
                _3dMap.back()->setMaterialFlag(
                    irr::video::EMF_LIGHTING, false);
                std::cout << _data._rules.find(tile)->second._texPath
                          << std::endl;
                _3dMap.back()->setMaterialTexture(
                    0,
                    d._driver->getTexture(
                        _data._rules.find(tile)->second._texPath.c_str()));
                _3dMap.back()->setPosition(irr::core::vector3df(x, y, 40.0f));
                _3dMap.back()->setRotation(irr::core::vector3df(-90.0f, 0, 0));
            }
            x += 5.0f;
 */