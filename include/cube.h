#ifndef _CUBE_H_
#define _CUBE_H_

#include <SFML/System.hpp>
#include "rules.h"

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

        Cell &operator=(const Cell &object)
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
    Cube(Rules rules = Rules()): rules(rules)
    {
        cube = new Cell **[size];
        for (int i = 0; i < size; i++)
        {
            cube[i] = new Cell *[size];
            for (int j = 0; j < size; j++)
                cube[i][j] = new Cell[size];
        }

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                for (int k = 0; k < size; k++)
                {
                    cube[i][j][k].setX(static_cast<float>(i) * 0.01);
                    cube[i][j][k].setY(static_cast<float>(j) * 0.01);
                    cube[i][j][k].setZ(static_cast<float>(k) * 0.01);
                }
    }

    Cube(const Cube &object): Cube()
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                for (int k = 0; k < size; k++)
                    this->cube[i][j][k] = object.cube[i][j][k];

        this->rules = object.rules;
    };

    ~Cube()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                delete[] cube[i][j];
            delete [] cube[i];
        }

        delete [] cube;
    }

    void evolve()
    {
        Cube evolutionaryCube = Cube(*this);

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (int k = 0; k < size; k++)
                {
                    int neighboursCount = 0;
                    for (int a = -1; a < 2; a++)
                        for (int b = -1; b < 2; b++)
                            for (int C = -1; C < 2; C++) // :D
                                if (checkCell(i + a, j + b, k + C))
                                    neighboursCount++;
                    
                    
                }
            }
        }
    }

private:
    Cell ***cube;
    int size = 50;
    Rules rules;

    inline bool checkCell(int i, int j, int k)
    {
        if ((i < 0 || i >= size) || (j < 0 || j >= size) || (k < 0 || k >= size))
            return false;

        if (cube[i][j][k].getState() != Dead)
            return true;

        return false;
    }
};

#endif