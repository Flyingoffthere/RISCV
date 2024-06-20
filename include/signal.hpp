#ifndef RISCV_SIGNAL_HPP
#define RISCV_SIGNAL_HPP

#include <iostream>
#include <bitset>
#include <string>
#include <cmath>


template <size_t SignalWidth>
requires (SignalWidth > 0)
class Signal
{
public:
    Signal() = default;
    explicit Signal(unsigned long long intRepresentation);
    explicit Signal(std::string stringRepresentation);
    ~Signal() = default;

    [[nodiscard]] size_t Size() const;

    [[nodiscard]] std::string String() const;
    [[nodiscard]] long long Decimal(bool isUnsigned) const;

    auto operator[](size_t);

    friend std::ostream& operator<<(std::ostream& ostream, const Signal<SignalWidth>& signal)
    {
        ostream << signal.data.to_string();
        return ostream;
    }

    friend bool operator==(const Signal<SignalWidth>& s1, const Signal<SignalWidth>& s2)
    {
        return s1.data == s2.data;
    }

private:
    std::bitset<SignalWidth> data{};
};



template <size_t signalWidth>
requires (signalWidth > 0)
Signal<signalWidth>::Signal(unsigned long long intRepresentation)
        :   data{intRepresentation}
{}

template <size_t signalWidth>
requires (signalWidth > 0)
Signal<signalWidth>::Signal(std::string stringRepresentation)
        :   data{stringRepresentation}
{}

template <size_t signalWidth>
requires (signalWidth > 0)
size_t Signal<signalWidth>::Size() const
{
    return data.size();
}

template <size_t signalWidth>
requires (signalWidth > 0)
long long Signal<signalWidth>::Decimal(bool isUnsigned) const
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

template <size_t signalWidth>
requires (signalWidth > 0)
std::string Signal<signalWidth>::String() const
{
    return data.to_string();
}


template <size_t signalWidth>
requires (signalWidth > 0)
auto Signal<signalWidth>::operator[](size_t index)
{
    return data[index];
}

#endif
