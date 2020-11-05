#ifndef _RANGE_H_
#define _RANGE_H_

template <typename T = int>
class Range
{

public:
    Range(T lower = 0, T upper = 0) : lower(lower), upper(upper){};
    bool operator()(T value)
    {
        return (value >= this->lower && value <= this->upper) ? true : false;
    }

    bool operator>(T value)
    {
        return (value > this->upper) ? true : false;
    }

    bool operator<(T value)
    {
        return (value < this->lower) ? true : false;
    }

    T getLower() const { return this->lower; }
    T getUpper() const { return this->upper; }

    void setLower(T const value) { this->lower = value; }
    void setUpper(T const value) { this->upper = value; }

private:
    T lower;
    T upper;
};

#endif