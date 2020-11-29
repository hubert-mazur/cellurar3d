#ifndef _RANGE_H_
#define _RANGE_H_

// Template class for range
template <typename T = int>
class Range
{

public:
    // default Constructor
    Range(T lower = 0, T upper = 0) : lower(lower), upper(upper){};

    // check if value is inside range
    bool operator()(T value)
    {
        return (value >= this->lower && value <= this->upper) ? true : false;
    }

    // check if value is bigger than upper range's bound
    bool operator>(T value)
    {
        return (value > this->upper) ? true : false;
    }

    // check if value is smaller than lower range's bound
    bool operator<(T value)
    {
        return (value < this->lower) ? true : false;
    }

    // getters
    T getLower() const { return this->lower; }
    T getUpper() const { return this->upper; }

    // setters
    void setLower(T const value) { this->lower = value; }
    void setUpper(T const value) { this->upper = value; }

private:
    T lower;
    T upper;
};

#endif