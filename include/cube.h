#ifndef _CUBE_H_
#define _CUBE_H_

#include <SFML/System.hpp>

enum State
{
    Excellent = 4,
    Good = 3,
    Sick = 2,
    Agony = 1,
    Dead = 0
};

class Cube
{
    class Cell final
    {

    public:
        Cell(sf::Vector3f coordinates, unsigned state = Dead) : cellCoordinates(coordinates), state(state){};
        Cell(float x = 0.0, float y = 0.0, float z = 0.0, unsigned state = Dead)
        {
            this->cellCoordinates.x = x;
            this->cellCoordinates.y = y;
            this->cellCoordinates.z = z;
            this->state = state;
        }

        sf::Vector3f getCoordinates() const { return this->cellCoordinates; }
        unsigned getState() const { return this->state; }

        void setState(unsigned state) { this->state = state; }
        void setCoordinates(sf::Vector3f coordinates) { this->cellCoordinates = coordinates; }
        void setX(float x) { this->cellCoordinates.x = x; }
        void setY(float y) { this->cellCoordinates.y = y; }
        void setZ(float z) { this->cellCoordinates.z = z; }

        Cell& operator= (const Cell &object) 
        {
            this->cellCoordinates.x = object.cellCoordinates.x;
            this->cellCoordinates.y = object.cellCoordinates.y;
            this->cellCoordinates.z = object.cellCoordinates.z;
            this->state = object.state;

            return *this;
        }

    private:
        sf::Vector3f cellCoordinates;
        unsigned state;
    };

public:
    Cube()
    {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; j++)
                for (int k = 0; k < size; k++)
                    cube[i][j][k] = new Cell(static_cast<float>(i) * 0.01, static_cast<float>(j) * 0.01, static_cast<float>(k) * 0.01);
    }

    Cube(const Cube &object)
    {
        Cube copy = Cube();
        for (int i=0;i<size;i++)
            for (int j=0;j<size;j++)
                for (int k=0;k<size;k++)
                    copy.cube[i][j][k] = object.cube[i][j][k];
    }

    ~Cube()
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                for (int k = 0; k < size; k++)
                    delete cube[i][j][k];
    }



    void evolve()
    {
        Cube evolutionaryCube = Cube(*this);

        
    }

private:
    Cell *cube[100][100][100];
    int size = 100;
};

#endif