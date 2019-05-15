/*
** EPITECH PROJECT, 2019
** ATile.hpp 
** File description:
** basile.lamarque@epitech.eu
*/


#pragma once



class ATile {
        enum class STATE {

        };

        enum class TYPE {
                DWALL, // murs destructible
                WALL, // murs indestructible
                GROUND // sols
        };

    public:
        ATile() = default;
        ~ATile() = default;


        // NOTE GETTER SETTER

        unsigned int getIndex() const;
        void setIndex(unsigned int);
        TYPE getType() const;
        void setType(TYPE);
    private:
        unsigned int _index;
        TYPE _type;
        double _X;
        double _Y;
        double _Z;

};



