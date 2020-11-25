#ifndef _CUBE_H_
#define _CUBE_H_

#include <SFML/System.hpp>
#include "rules.h"

class Cube
{
    class Cell final
    {

    public:
        Cell(sf::Vector3f coordinates, unsigned state = 50) : cellCoordinates(coordinates), state(state){};
        Cell(float x = 0.0, float y = 0.0, float z = 0.0, unsigned state = 0)
        {
            this->cellCoordinates.x = x;
            this->cellCoordinates.y = y;
            this->cellCoordinates.z = z;
            this->state = state;
        }

        sf::Vector3f getCoordinates() const { return this->cellCoordinates; }
        unsigned getState() const { return this->state; }
        int getNeighboursCount() const { return this->neighboursCount; }

        void setState(unsigned state) { this->state = state; }
        void setCoordinates(sf::Vector3f coordinates) { this->cellCoordinates = coordinates; }
        void setX(float x) { this->cellCoordinates.x = x; }
        void setY(float y) { this->cellCoordinates.y = y; }
        void setZ(float z) { this->cellCoordinates.z = z; }
        void setNeighboursCount(int count) { this->neighboursCount = count; }

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
        int neighboursCount = 0;
    };

public:
    Cube(Rules rules = Rules()) : rules(rules)
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

    Cube(const Cube &object) : Cube()
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
            delete[] cube[i];
        }

        delete[] cube;
    }

    Cube *evolve()
    {
        Cube *evolutionaryCube = new Cube(*this);
        // Cube *evolutionaryCub = new Cube(*this);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (int k = 0; k < size; k++)
                {
                    int neighboursCount = 0;
                    int state = this->cube[i][j][k].getState();
                    if (this->rules.getNeighbourhoodRule() == Moore)
                    {
                        for (int a = -1; a < 2; a++)
                            for (int b = -1; b < 2; b++)
                                for (int C = -1; C < 2; C++) // :D
                                    neighboursCount += checkCell(i + a, j + b, k + C);
                    }
                    else
                    {
                        for (int a = -1; a < 2; a++)
                            for (int b = -1; b < 2; b++)
                                neighboursCount += checkCell(i + a, j + b, k);
                    }

                    // subtract cell itself from neighbours count
                    neighboursCount -= 1;

                    this->cube[i][j][k].setNeighboursCount(neighboursCount);

                    if (state == 0 && this->rules.getBornRule()(neighboursCount))
                        evolutionaryCube->cube[i][j][k].setState(100);
                    else if (state != 0 && !this->rules.getSurviveRule()(neighboursCount))
                    {
                        evolutionaryCube->cube[i][j][k].setState(0);
                    }
                }
            }
        }

        return evolutionaryCube;
    }

    void initRandomData()
    {
        int begin = 0, end;
        begin = random() % 30;

        for (int rounds = 0; rounds < 30; rounds++)
        {
            end = random() % (30 - begin) + begin;
            std::cout << "From: " << begin << ", to: " << end << std::endl;
            for (int i = begin; i < end; i++)
            {
                begin = random() % 30;
                end = random() % (30 - begin) + begin;

                for (int j = begin; j < end; j++)
                {
                    begin = random() % 30;
                    end = random() % (30 - begin) + begin;
                    for (int k = begin; k < end; k++)
                    {
                        if (random() % 100 < 20)
                            this->cube[i][j][k].setState(100);
                    }
                }
            }
        }
    }

    Cell ***getCube() const { return this->cube; }
    Rules rules;

private:
    Cell ***cube;
    int size = 30;

    inline bool checkCell(int i, int j, int k)
    {
        if ((i < 0 || i >= size) || (j < 0 || j >= size) || (k < 0 || k >= size))
            return false;

        if (cube[i][j][k].getState() != 0)
            return true;

        return false;
    }
};

#endif