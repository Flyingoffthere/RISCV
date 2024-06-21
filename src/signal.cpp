#include "../include/signal.hpp"

Signal::Signal(unsigned long long intRepresentation)
        :   data{intRepresentation}
{}

Signal::Signal(std::string stringRepresentation)
        :   data{stringRepresentation}
{}

std::size_t Signal::Size() const
{
    return data.size();
}

long long Signal::Decimal(bool isUnsigned) const
{
    if (isUnsigned)
        return data.to_ullong();
    else {
        long long base = 2, result = 0;
        size_t lastIndex = data.size() - 1;
        for (size_t i = 0; i < lastIndex; i++)
            result += data[i] * std::pow(base, i);
        result -= data[lastIndex] * std::pow(base, lastIndex);
        return result;
    }
}

std::string Signal::String() const
{
    return data.to_string();
}


std::bitset<one_cycle_params::WORD_SIZE>::reference Signal::operator[](std::size_t index)
{
    return data[index];
}