#ifndef RISCV_SIGNAL_HPP
#define RISCV_SIGNAL_HPP

#include <iostream>
#include <bitset>
#include <string>
#include <cmath>


template <std::size_t SignalWidth>
requires (SignalWidth > 0)
class Signal
{
public:
    Signal() = default;
    explicit Signal(unsigned long long intRepresentation);
    explicit Signal(std::string stringRepresentation);
    explicit Signal(std::bitset<SignalWidth> data_) : data{data_}{};
    ~Signal() = default;

    [[nodiscard]] std::size_t Size() const;

    [[nodiscard]] std::string String() const;
    [[nodiscard]] long long Decimal(bool isUnsigned) const;

    Signal<SignalWidth> operator& (Signal& other)
    {return Signal<SignalWidth>{this->data & other.data};}

    Signal<SignalWidth> operator| (Signal& other)
    {return Signal<SignalWidth>{this->data | other.data};}

    Signal<SignalWidth> operator^ (Signal& other)
    {return Signal<SignalWidth>{this->data ^ other.data};}

    auto operator[](std::size_t);

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



template <std::size_t signalWidth>
requires (signalWidth > 0)
Signal<signalWidth>::Signal(unsigned long long intRepresentation)
        :   data{intRepresentation}
{}

template <std::size_t signalWidth>
requires (signalWidth > 0)
Signal<signalWidth>::Signal(std::string stringRepresentation)
        :   data{stringRepresentation}
{}

template <std::size_t signalWidth>
requires (signalWidth > 0)
std::size_t Signal<signalWidth>::Size() const
{
    return data.size();
}

template <std::size_t signalWidth>
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

template <std::size_t signalWidth>
requires (signalWidth > 0)
std::string Signal<signalWidth>::String() const
{
    return data.to_string();
}


template <std::size_t signalWidth>
requires (signalWidth > 0)
auto Signal<signalWidth>::operator[](size_t index)
{
    return data[index];
}

// utils

template <std::size_t signalWidth, std::size_t start, std::size_t end>
Signal<end - start> sliceSignal(Signal<signalWidth> sig)
{
    std::bitset<end - start> result{};
    for (std::size_t i = start; i < end; i++)
        result[i - start] = sig[i];
    return Signal<end - start>{result};
}

template<std::size_t signalWidth1, std::size_t signalWidth2>
Signal<signalWidth1 + signalWidth2>
concatSignals(Signal<signalWidth1> sig1, Signal<signalWidth2> sig2)
{
    std::bitset<signalWidth1 + signalWidth2> result{};
    for (std::size_t i = 0; i < signalWidth1 + signalWidth2; i++) {
        if (i < signalWidth1)
            result[i] = sig1[i];
        else
            result[i] = sig2[i - signalWidth1];
    }
    return Signal<signalWidth1 + signalWidth2>{result};
}

#endif
