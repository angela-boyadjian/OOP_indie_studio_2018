//
// Created by dclement on 5/24/19.
//

#pragma once

#include "ISceneManager.hpp"

class MenuScene : public ISceneManager {
    public:
        MenuScene(Device &device, VideoDriver &driver);
        ~MenuScene() = default;

        // NOTE CAMERA
        void setCameraScene() override;

        // NOTE MAP
        void setTerrain() override;
        void setSkyDome() override;
        void initTerrain() override;
        void initAnimTerrain() override;
        void setTerrainMaterial() override;

        // NOTE MESH SCENES
        void addNewMesh(const char *meshPath) override;
        void setMeshPosRot(irr::scene::IAnimatedMeshSceneNode *newScene) override;
        void setMeshFrames(irr::scene::IAnimatedMeshSceneNode *newScene) override;
        void setMeshAnimation(irr::scene::IAnimatedMeshSceneNode *newScene) override;
        void addNewMeshScene(const char *scenePath, const irr::core::vector3df &scale) override;

        // NOTE GETTER
        AnimatedMeshsScene getMeshScenes() override;
        Scenes getSceneManager() override;

    private:
        Device const _device;
        VideoDriver const _driver;
        Camera              _camera;
        Selector            _selector;
        AnimTerrain         _animTerrain;
        Terrain             _terrain;
        AnimatedMeshs       _meshs;
        AnimatedMeshsScene  _meshsScene;
};
