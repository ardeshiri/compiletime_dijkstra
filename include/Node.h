#ifndef NODE_H
#define NODE_H
#include <iostream>

struct info
{
    double w;
};

struct void_info
{
    double w;
};


template<typename T=void_info>
class Node
{
public:
    using info_type = T;

    constexpr Node(size_t n, const T& v = {}): number{n}, info{v}
    {}

    constexpr size_t get_number() const
    {
        return number;
    }

    constexpr T get_info() const
    {
        return info;
    }

private:
    size_t number;
    T info;
};


template<typename T>
std::ostream& operator<<(std::ostream& os, const Node<T>& n)
{
    os<<n.get_number();
    return os;
}

#endif // NODE_H
