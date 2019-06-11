//
// Created by dclement on 5/20/19.
//

#pragma once

#include <memory>
#include <vector>

#include "irrlicht.h"

class ISceneManager {
    public:
        using Scenes = irr::scene::ISceneManager *;
        using SceneNode = irr::scene::ISceneNode *;
        using Camera = std::unique_ptr<irr::scene::ICameraSceneNode>;
        using Terrain = std::unique_ptr<irr::scene::ITerrainSceneNode>;
        using Selector = std::unique_ptr<irr::scene::ITriangleSelector>;
        using SceneManager = std::unique_ptr<irr::scene::ISceneManager>;
        using AnimTerrain = std::unique_ptr<irr::scene::ISceneNodeAnimator>;
        using AnimatedMeshs = std::vector<std::unique_ptr<irr::scene::IAnimatedMesh>>;
        using AnimatedMeshsScene = std::vector<std::shared_ptr<irr::scene::IAnimatedMeshSceneNode>>;
        using VideoDriver = irr::video::IVideoDriver *;
        using Device = std::shared_ptr<irr::IrrlichtDevice>;

        // NOTE CAMERA
        virtual void setCameraScene() = 0;

        // NOTE MAP
        virtual void setTerrain() = 0;
        virtual void setSkyDome() = 0;
        virtual void initTerrain() = 0;
        virtual void initAnimTerrain() = 0;
        virtual void setTerrainMaterial() = 0;

        // NOTE MESH SCENES
        virtual void addNewMesh(const char *meshPath) = 0;
        virtual void setMeshPosRot(irr::scene::IAnimatedMeshSceneNode *newScene) = 0;
        virtual void setMeshFrames(irr::scene::IAnimatedMeshSceneNode *newScene) = 0;
        virtual void setMeshAnimation(irr::scene::IAnimatedMeshSceneNode *newScene) = 0;
        virtual void addNewMeshScene(const char *scenePath, const irr::core::vector3df &scale) = 0;

        // NOTE GETTER
        virtual AnimatedMeshsScene getMeshScenes() = 0;
        virtual Scenes getSceneManager() = 0;

    protected:
        Scenes _smgr;
        Scenes _scene;
};
