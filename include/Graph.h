#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <array>
template<typename T, std::size_t s, typename U, std::size_t t>
class Graph
{
public:
    using node_type = T;
    using edge_type = U;
    static const std::size_t node_count = s;
    constexpr Graph(const std::array<T, s>& node_in, const std::array<U, t>& edge_in): node_set{node_in}, edge_set{edge_in}
    {}

    constexpr const std::array<T, s> & get_node_set() const
    {
        return node_set;
    }

    constexpr const std::array<U, t> & get_edge_set() const
    {
        return edge_set;
    }

    std::ostream& print(std::ostream& os) const
    {
        os<<"V:"<<std::endl;
        for(auto v: node_set)
            os<<v<<" , ";
        os<<std::endl;
        os<<"G:"<<std::endl;
        for(auto g: edge_set)
            os<<g<<" , ";
        os<<std::endl;
        return os;
    }
private:
    std::array<T, s> node_set;
    std::array<U, t> edge_set;
};

template<typename T, size_t s, typename U, size_t t>
std::ostream& operator<<(std::ostream& os, const Graph<T,s,U,t>& g)
{
    return g.print(os);
}


#endif // GRAPH_H
