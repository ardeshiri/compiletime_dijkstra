#ifndef EDGE_H
#define EDGE_H
#include <iostream>

struct Edge
{
    size_t from;
    size_t to;
    double weight;
};

std::ostream& operator<<(std::ostream& os, const Edge& e)
{
    os<<"("<<e.from<<", "<<e.to<<", "<<e.weight<<")";
    return os;
}


#endif // EDGE_H
