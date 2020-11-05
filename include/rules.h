#ifndef _RULES_H_
#define _RULES_H_

#include "range.h"

enum Neighbourhood
{
    Moore = 0,
    vonNeumann = 1
};

class Rules
{

public:
    Rules(Range<int> born = Range<int>(13, 18), Range<int> survive = Range<int>(10, 20), Range<int> death = Range<int>(6, 22), int neighbourhood = 0) : born(born), survive(survive), death(death), neighbourhood(neighbourhood) {}

    void setBornRule(Range<> range) { this->born = range; }
    void setSurviveRule(Range<> range) { this->survive = survive; }
    void setDeathRule(Range<> range) { this->death = death; }

    Range<> getBornRule() const { return this->born; }
    Range<> getSurviveRule() const { return this->survive; }
    Range<> getDeathRule() const { return this->death; }
    
private:
    Range<int> born;
    Range<int> survive;
    Range<int> death;

    int neighbourhood;
};

#endif