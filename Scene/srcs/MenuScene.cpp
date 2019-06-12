/*
** EPITECH PROJECT, 2019
** MenuScene.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "MenuScene.hpp"

MenuScene::MenuScene(std::shared_ptr<irr::scene::ISceneManager> father) :
    _master(father->addEmptySceneNode())
{}

void MenuScene::runScene()
{
    std::cout << "Run" << std::endl;
}

void MenuScene::loadScene()
{
    std::cout << "Load" << std::endl;
}

std::string MenuScene::getName()
{
    return _name;
}