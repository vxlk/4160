#ifndef POOL_H
#define POOL_H
#include <vector>
#include <string>

template <typename T>
class Pool
{
    std::vector<T> pool;
    int index;
    std::string objName;
public:

    explicit Pool(std::string name) : pool(), index(0), objName(name) {}

    T getFromPool() noexcept;

    void addBack(T) noexcept;

    inline int getIndex() const noexcept { return this->index; }
    inline int getSize() const noexcept { return (int)this->pool.size()-1; }

};
#endif