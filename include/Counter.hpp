#ifndef COUNTER_HPP_INCLUDED
#define COUNTER_HPP_INCLUDED

#include <cstdint>

template<class T>
class Counter
{
    public:
        Counter();

    protected:
        ~Counter() = default;

    protected:
        static std::size_t sCount;
};

#include <Counter.inl>

#endif // COUNTER_HPP_INCLUDED
