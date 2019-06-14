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
#define posY -90
#define posZ 75

class GameBisScene : public IScene {
    public:
        using Map3D = std::vector<std::shared_ptr<IDisplay::Object>>;
        using Bots = std::vector<std::shared_ptr<Bot>>;
        using Players = std::vector<std::shared_ptr<Player>>;

        GameBisScene(std::shared_ptr<irr::IrrlichtDevice>, irr::scene::ISceneNode *, const std::string &, std::shared_ptr<Events>, std::shared_ptr<IDisplay>);
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

        //LOGIG
        void action();
        void botsAction();
        void playersAction();
        void changeFrameAndPos(const ACharacter *, const ACharacter::Action &, const ACharacter::Action &);
        std::vector<ACharacter::Action> movePlayers(const std::shared_ptr<Events> &, std::vector<std::string> &, IDisplay *);
        void changeAnimation(const std::size_t &, const ACharacter::Action &, const ACharacter::Action &);
        void changeModelPos(const std::size_t &, const IDisplay::pos3d &);
        irr::core::vector3df pos3dToVector(const IDisplay::pos3d &);
        ACharacter::Action  pressKeyAction(const AGame::Event &, const std::size_t &);

    private:
        std::shared_ptr<irr::scene::ISceneNode> _master;
        irr::scene::ISceneManager *_manager;
        std::string _name;
        bool _is_load;
        std::shared_ptr<IMap>           _map;
        std::unique_ptr<AGame>          _game;
        std::shared_ptr<irr::IrrlichtDevice> _device;
        std::shared_ptr<Events> _event;
        std::shared_ptr<IDisplay> _display;
        std::unique_ptr<IDisplayLoader> _dispLoader;
        std::map<std::size_t, ACharacter::Action>   _lastActions;
};



