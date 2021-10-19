#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <fstream>
#include <random>
#include <typeinfo>
#include <map>
#include <type_traits>
#include <ranges>
#include <variant>
#include <concepts>
#include <memory_resource>
#include <array>
#include <unordered_map>
#include <limits>
#include "Node.h"
#include "Edge.h"
#include "Graph.h"

using namespace std;

template<typename T, size_t s, typename U, size_t t>
constexpr array<tuple<bool, size_t, size_t>, s> dijk(Graph<T,s,U,t> g, size_t sn)
{
    array<tuple<bool, size_t, size_t>, s> dist_table{}; /// infinite(false), dist, from
    array<bool, s> met_set{}; /// empty(false), node
    for_each(dist_table.begin(), dist_table.end(), [](auto& row){ get<0>(row) = false; get<1>(row) = 0; get<2>(row) = 0;});
    for_each(met_set.begin(), met_set.end(), [](auto& item){item = false;});
    met_set[sn] = true; /// adding sn(source node) to met set
    get<0>(dist_table[sn]) = true; /// adding sn to dist table
    get<1>(dist_table[sn]) = 0;
    get<2>(dist_table[sn]) = sn;
    size_t current_node {sn};

    for(;;)
    {
        for(const auto& x: g.get_edge_set()) /// update dist_table
        {
            if(x.from == current_node)
            {
                if(get<0>(dist_table[x.to])==false)
                {
                    get<0>(dist_table[x.to]) = true;
                    get<1>(dist_table[x.to]) = x.weight + get<1>(dist_table[x.from]);
                    get<2>(dist_table[x.to]) = x.from;
                }
                else if( get<1>(dist_table[x.to]) > x.weight + get<1>(dist_table[x.from]))
                {
                    get<1>(dist_table[x.to]) = x.weight + get<1>(dist_table[x.from]);
                    get<2>(dist_table[x.to]) = x.from;
                }
            }
        }
        if(all_of( met_set.begin(), met_set.end(), [](const auto& p){ return p==true; })) break; /// see if we are done

        size_t min_val{numeric_limits<size_t>::max()};
        size_t indx {0};
        for(const auto& n: met_set) /// find minimum in the dist table which is not in the in met set and add it to the met set
        {
            if(n==false && get<0>(dist_table[indx])==true && min_val > get<1>(dist_table[indx]))
                {
                    min_val = get<1>(dist_table[indx]);
                    current_node = indx;
                }
            indx++;
        }
        met_set[current_node]=true; /// adding the node to the met set
    }
    return dist_table;
}


constexpr size_t sould_be_compiletime()
{
    #include "graph.txt"
    Graph gp{n, e};
    dijk(gp,0);
    return 1;
}

int main()
{
    static_assert(sould_be_compiletime()==1, "won't happen");
    #include "graph.txt"
    Graph gp{n, e};
    auto res = dijk(gp,0);
}
