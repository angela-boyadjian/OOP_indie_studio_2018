/*
** EPITECH PROJECT, 2019
** GameScene.hpp 
** File description:
** basile.lamarque@epitech.eu
*/

#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "IScene.hpp"
#include "BombermanPlayers/Player.hpp"
#include "BombermanPlayers/Bot.hpp"
#include "IMap.hpp"

#define posX -60
#define posY -100
#define posZ 75

class GameBisScene : public IScene {
    public:
        using Map3D = std::vector<std::shared_ptr<IDisplay::Object>>;

        GameBisScene(std::shared_ptr<irr::IrrlichtDevice>, irr::scene::ISceneNode *, const std::string &);
        ~GameBisScene() = default;

        // MANDATORY
        void deLoad() override;
        std::string runScene() override;
        void loadScene() override;
        std::string getName() override;

        // ONLY IN GAME
        void loadGame(const std::string &, std::unique_ptr<AGame> &);
        std::vector<std::unique_ptr<Player>> loadPlayer();
        std::vector<std::unique_ptr<Bot>> loadBot();

        // ASSET LOADER
        void loadGameAsset(std::shared_ptr<AGame> &);
        void loadPlayerAsset(const ACharacter::Color &, const std::vector<std::string> &);

        // NOTE MAP
        void loadMapAsset(const MapData &);
        void loadMapWall(const MapData &);
        void preloadMapWall(const MapData &);
        void loadMapEdgeTop(const MapData &);
        void loadMapEdgeSide(const MapData &);
        void loadMapEdgeLow(const MapData &);
        void addTileToMap(const irr::core::vector3df &, const SpriteInfo &, float);
        void loadMapGround(const MapData &);
        bool loadTileMap(const SpriteInfo &, float, GameBisScene::Map3D &);
        void loadCube(float , GameBisScene::Map3D &);
        void loadMess(const SpriteInfo &, float , GameBisScene::Map3D &);

    private:
        std::shared_ptr<irr::scene::ISceneNode> _master;
        irr::scene::ISceneManager *_manager;
        std::string _name;
        bool _is_load;
        std::shared_ptr<IMap>           _map;
        std::shared_ptr<AGame>          _game;
        std::vector<std::shared_ptr<irr::scene::IAnimatedMeshSceneNode>> _meshs;
        std::shared_ptr<irr::IrrlichtDevice> _device;
        Map3D _coliMap;
        Map3D _noncoliMap;
};



