/*
** EPITECH PROJECT, 2019
** CEventReceiver.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "CEventReceiver.hpp"

CEventReceiver::CEventReceiver(irr::scene::IAnimatedMeshSceneNode* Nmodele)
{
    //On pointe le mesh passe en parametre.
    m_Nmodele = Nmodele;
    //Par defaut on ne bouge pas
    m_isMoving = false;
}


bool CEventReceiver::OnEvent(const irr::SEvent &event)
{
    //On verifie que le pointeur est ok
    if(m_Nmodele != 0
       //Qu'il s'agit d'un event concernant un appui/relachement de touche
       && event.EventType == irr::EET_KEY_INPUT_EVENT
       //Qu'il s'agit de la touche z
       && event.KeyInput.Key == irr::KEY_KEY_Z)
    {
        //On assigne la bonne valeur directement
        m_isMoving = event.KeyInput.PressedDown;
        //L'event est traite, on retourne true
        return true;
    }
    //Si on arrive la, c'est qu'on a pas traite l'event
    return false;
}


void CEventReceiver::majPosMesh()
{
    //On verifie que le pointeur vers le mesh est
    //ok et que la touche est enfoncee
    if(m_Nmodele != 0 && m_isMoving == true)
    {
        //On commence par recuperer la position actuelle
        irr::core::vector3df v = m_Nmodele->getPosition();
        //On y ajoute la valeur de deplacement
        v.X += 1.0f;
        //On renvoie la nouvelle position
        m_Nmodele->setPosition(v);
    }
}