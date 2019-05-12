/*
** EPITECH PROJECT, 2019
** CEventReceiver.hpp 
** File description:
** basile.lamarque@epitech.eu
*/

#ifndef OOP_INDIE_STUDIO_2018_CEVENTRECEIVER_HPP
#define OOP_INDIE_STUDIO_2018_CEVENTRECEIVER_HPP

#include <irrlicht.h>

class CEventReceiver : public irr::IEventReceiver{
    public :

        //Le constructeur.
        CEventReceiver(irr::scene::IAnimatedMeshSceneNode* Nmodele);
        //Capte automatiquement les events.
        virtual bool OnEvent(const irr::SEvent &event);
        //Met a jour la position du mesh.
        void majPosMesh();


    private :

        //Le modele qu'on va controler.
        irr::scene::IAnimatedMeshSceneNode* m_Nmodele;
        //Indique si on est deja en mouvement ou pas.
        bool m_isMoving;
};


#endif //OOP_INDIE_STUDIO_2018_CEVENTRECEIVER_HPP
