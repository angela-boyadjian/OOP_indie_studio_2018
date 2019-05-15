/*
** EPITECH PROJECT, 2019
** DisplayLoader.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "DisplayLoader.hpp"

DisplayLoader::DisplayLoader(const std::shared_ptr<IDisplay> &d) :
    _d(d)
{}

bool DisplayLoader::addTileToMap(const SpriteInfo &info, float size, DisplayLoader::Map3D &map3d)
{
    if (info._messPath == "Cube")
        map3d.emplace_back(_d->_scenes->addCubeSceneNode(size, 0, -1));
    else {
        irr::core::vector3df scale(size / info._size.X,
                                   size / info._size.Y,
                                   size / info._size.Z);
        map3d.emplace_back(_d->_scenes->addAnimatedMeshSceneNode(
            _d->_scenes->getMesh(info._messPath.c_str())));
        map3d.back()->setScale(scale);
        map3d.back()->setRotation(irr::core::vector3df(-90.0f, 0, 0));
    }
    map3d.back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    map3d.back()->setMaterialTexture(0, _d->_driver->getTexture(
        info._texPath.c_str()));
    return true;
}

void DisplayLoader::preloadMapWall(DisplayLoader::Map3D &map3d, std::unique_ptr<IMap> &map)
{
    auto x = 0.0f;
    auto y = 10.0f;
    auto pos = map->getMapData()._rulesWall.find('/');

    for (__attribute__((unused)) auto tile : map->getMapData()._mapWall[0]) {
        addTileToMap(pos->second, 10.0f, map3d);
        map3d.back()->setPosition(irr::core::vector3df(x, 10.0f, 40.0f));
        x += 10.0f;
    }
    for (int i = 0; i != map->getMapData()._mapWall.size() + 2; i++) {
        addTileToMap(pos->second, 10.0f, map3d);
        map3d.back()->setPosition(irr::core::vector3df(x, y, 40.0f));
        addTileToMap(pos->second, 10.0f, map3d);
        map3d.back()->setPosition(irr::core::vector3df(0 - 10.0f, y, 40.0f));
        y -= 10.0f;
    }
    x = 0.0f;
    for (__attribute__((unused)) auto tile : map->getMapData()._mapWall[0]) {
        addTileToMap(pos->second, 10.0f, map3d);
        map3d.back()->setPosition(irr::core::vector3df(x, y + 10.0f, 40.0f));
        x += 10.0f;
    }
}

void DisplayLoader::loadMapWall(Map3D &map3d, std::unique_ptr<IMap> &map)
{
    auto x = 0.0f;
    auto y = 0.0f;

    preloadMapWall(map3d, map);
    for (auto &line : map->getMapData()._mapWall) {
        for (auto tile : line) {
            auto pos = map->getMapData()._rulesWall.find(tile);
            if (pos != map->getMapData()._rulesWall.end()) {
                addTileToMap(pos->second, 9.0f, map3d);
                map3d.back()->setPosition(irr::core::vector3df(x, y, 40.0f));
            }
            x += 10.0f;
        }
        x = 0;
        y -= 10.0f;
    }
}

void DisplayLoader::loadMapGround(Map3D &map3d, std::unique_ptr<IMap> &map)
{
    unsigned int value = 0;
    auto x = 0.0f;
    auto y = 0.0f;
    auto base = map->getMapData()._rulesGround.begin()->first;

    for (auto &line : map->getMapData()._mapWall) {
        for (__attribute__((unused)) auto tile : line) {
            auto pos = map->getMapData()._rulesGround.find(base - value);
            if (pos != map->getMapData()._rulesGround.end()) {
                addTileToMap(pos->second, 10.0f, map3d);
                map3d.back()->setPosition(irr::core::vector3df(x, y, 50.0f));
            }
            value += 1;
            if (value > map->getMapData()._rulesGround.size() - 1)
                value = 0;
            x += 10.0f;
        }
        x = 0;
        y -= 10.0f;
    }
}

std::vector<std::unique_ptr<DisplayLoader::Object>> DisplayLoader::loadMap(std::unique_ptr<IMap> &map)
{
    std::vector<std::unique_ptr<DisplayLoader::Object>> map3d;

    loadMapWall(map3d, map);
    loadMapGround(map3d, map);
    return map3d;
}