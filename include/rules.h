#ifndef _RULES_H_
#define _RULES_H_

#include "range.h"

enum Neighbourhood
{
    Moore = 0,
    vonNeumann = 1
};

// class representing rules in simulation
class Rules
{
public:
    Rules(Range<int> born = Range<int>(13, 18), Range<int> survive = Range<int>(10, 20), int neighbourhood = 0) : born(born), survive(survive), neighbourhood(neighbourhood) {}

    // setters
    void setBornRule(Range<> range) { this->born = range; }
    void setSurviveRule(Range<> range) { this->survive = survive; }
    void setNeighbourhood(int neighbourhood) { this->neighbourhood = neighbourhood; }

    // getters
    int getNeighbourhoodRule() const { return this->neighbourhood; }
    Range<> &getBornRule() { return this->born; }
    Range<> &getSurviveRule() { return this->survive; }

private:
    Range<int> born;
    Range<int> survive;

    int neighbourhood;
};

#endif