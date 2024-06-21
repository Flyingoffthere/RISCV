#ifndef RISCV_SIGNAL_HPP
#define RISCV_SIGNAL_HPP

#include <iostream>
#include <bitset>
#include <string>
#include <cmath>
#include "datapool.hpp"


class Signal
{
public:
    Signal() = default;
    explicit Signal(unsigned long long intRepresentation);
    explicit Signal(std::string stringRepresentation);
    explicit Signal(std::bitset<one_cycle_params::WORD_SIZE> data_) : data{data_}{};
    Signal(const Signal& sig) = default;
    ~Signal() = default;

    [[nodiscard]] std::size_t Size() const;

    [[nodiscard]] std::string String() const;
    [[nodiscard]] long long Decimal(bool isUnsigned) const;

    Signal operator& (Signal& other)
    {return Signal{this->data & other.data};}

    Signal operator| (Signal& other)
    {return Signal{this->data | other.data};}

    Signal operator^ (Signal& other)
    {return Signal{this->data ^ other.data};}

    std::bitset<one_cycle_params::WORD_SIZE>::reference operator[](std::size_t);

    Signal& operator&= (Signal mask)
    {data &= mask.data; return *this;}

    Signal& operator>>= (std::size_t shift)
    {data >>= shift; return *this;}

    friend bool operator==(const Signal& s1, const Signal& s2)
    {
        return s1.data == s2.data;
    }

private:
    std::bitset<one_cycle_params::WORD_SIZE> data{};
};

#endif
