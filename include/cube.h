#ifndef _CUBE_H_
#define _CUBE_H_

#include <SFML/System.hpp>
#include "rules.h"

// class representing cube with cell inside
class Cube
{
    // class reppresenting single cell
    class Cell final
    {

    public:
        // Constructor with coordinates setting with Vector3f from SFML
        Cell(sf::Vector3f coordinates, bool state = false) : cellCoordinates(coordinates), state(state){};

        // Default constructor
        Cell(float x = 0.0, float y = 0.0, float z = 0.0, bool state = false)
        {
            this->cellCoordinates.x = x;
            this->cellCoordinates.y = y;
            this->cellCoordinates.z = z;
            this->state = state;
        }

        // getters
        sf::Vector3f getCoordinates() const { return this->cellCoordinates; }
        bool getState() const { return this->state; }
        int getNeighboursCount() const { return this->neighboursCount; }
        int getAge() const { return this->age; }

        // setters
        void setState(bool state) { this->state = state; }
        void setCoordinates(sf::Vector3f coordinates) { this->cellCoordinates = coordinates; }
        void setX(float x) { this->cellCoordinates.x = x; }
        void setY(float y) { this->cellCoordinates.y = y; }
        void setZ(float z) { this->cellCoordinates.z = z; }
        void setNeighboursCount(int count) { this->neighboursCount = count; }

        // Overloading of operator=
        Cell &operator=(const Cell &object)
        {
            this->cellCoordinates.x = object.cellCoordinates.x;
            this->cellCoordinates.y = object.cellCoordinates.y;
            this->cellCoordinates.z = object.cellCoordinates.z;
            this->state = object.state;
            this->age = object.age;
            return *this;
        }

        // functions responsible for cell growth, increments age
        void grow()
        {
            if (this->age < 10)
                this->age += 1;
        }

        // set cell age as newborn after dying, this not assuming that cell becomes alive
        void die() { this->age = 1; this->state = false; }

    private:
        sf::Vector3f cellCoordinates;
        bool state;
        int neighboursCount = 0;
        int age = 1;
    };

public:
    // Constructor for Cube
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

    // Copy constructor
    Cube(const Cube &object) : Cube()
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                for (int k = 0; k < size; k++)
                    this->cube[i][j][k] = object.cube[i][j][k];

        this->rules = object.rules;
    };

    // Destructor
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

    // Evolution function
    Cube *evolve()
    {
        // create a new Cube which is evolving
        Cube *evolutionaryCube = new Cube(*this);

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (int k = 0; k < size; k++)
                {
                    int neighboursCount = 0;
                    bool state = this->cube[i][j][k].getState();
                    // count neighbours
                    if (this->rules.getNeighbourhoodRule() == Moore)
                    {
                        for (int a = -1; a < 2; a++)
                            for (int b = -1; b < 2; b++)
                                for (int C = -1; C < 2; C++)
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

                    // decide what to do with cell
                    if (!state && this->rules.getBornRule()(neighboursCount))
                    {
                        evolutionaryCube->cube[i][j][k].setState(true);
                        evolutionaryCube->cube[i][j][k].grow();
                    }
                    else if (state && !this->rules.getSurviveRule()(neighboursCount))
                    {
                        evolutionaryCube->cube[i][j][k].setState(0);
                        evolutionaryCube->cube[i][j][k].die();
                    }
                    else if (state)
                    {
                        evolutionaryCube->cube[i][j][k].grow();
                    }
                }
            }
        }

        return evolutionaryCube;
    }

    // init random data, spawn cells at random positions with propability of 20%
    void initRandomData(bool createMode = true)
    {
        for (int rounds = 0; rounds < 50; rounds++)
        {
            int begin = 0, end;
            begin = random() % size;
            end = random() % (size - begin) + begin;

            for (int i = begin; i < end; i++)
            {
                begin = random() % size;
                end = random() % (size - begin) + begin;

                for (int j = begin; j < end; j++)
                {
                    begin = random() % size;
                    end = random() % (size - begin) + begin;
                    for (int k = begin; k < end; k++)
                    {
                        if (!createMode)
                        {
                            this->cube[i][j][k].setState(false);
                            this->cube[i][j][k].die();
                        }
                        if (random() % 100 < 20 && createMode)
                        {
                            this->cube[i][j][k].setState(true);
                            this->cube[i][j][k].grow();
                        }
                    }
                }
            }
        }
    }

    // kill all cells - start from beginning
    void dropBomb()
    {
        for (int i=0;i<this->size;i++) {
            for (int j=0;j<this->size;j++) {
                for (int k=0;k<this->size;k++) {
                    this->cube[i][j][k].die();
                }
            }
        }
    }

    int getSize() const { return this->size; }

    Cell ***getCube() const { return this->cube; }
    Rules rules;

private:
    Cell ***cube;
    int size = 30;

    // check if cell exists and return its state
    inline bool checkCell(int i, int j, int k)
    {
        if ((i < 0 || i >= size) || (j < 0 || j >= size) || (k < 0 || k >= size))
            return false;

        if (cube[i][j][k].getState())
            return true;

        return false;
    }
};

#endif