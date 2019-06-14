/*
** EPITECH PROJECT, 2019
** MapSelectionScene.hpp 
** File description:
** basile.lamarque@epitech.eu
*/


#pragma once

#include "ISceneManager.hpp"

class MapSelectionScene : public ISceneManager {

    public:
        MapSelectionScene(Device &device, VideoDriver &driver);
        ~MapSelectionScene() = default;

        // NOTE CAMERA
        virtual void setCameraScene() override;

        // NOTE MAP
        virtual void setTerrain() override;
        virtual void setSkyDome() override;
        virtual void initTerrain() override;
        virtual void initAnimTerrain() override;
        virtual void setTerrainMaterial() override;

        // NOTE MESH SCENES
        virtual void addNewMesh(const char *meshPath) override;
        virtual void setMeshPosRot(irr::scene::IAnimatedMeshSceneNode *newScene) override;
        virtual void setMeshFrames(irr::scene::IAnimatedMeshSceneNode *newScene) override;
        virtual void setMeshAnimation(irr::scene::IAnimatedMeshSceneNode *newScene) override;
        virtual void addNewMeshScene(const char *scenePath, const irr::core::vector3df &scale) override;

        // NOTE GETTER
        virtual AnimatedMeshsScene getMeshScenes() override;
        virtual Scenes getSceneManager() override;

    private:
        Device const _device;
        VideoDriver const _driver;
        Camera              _camera;
        AnimatedMeshsScene _meshsScene;
};



