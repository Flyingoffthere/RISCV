#include "../include/main_memory.hpp"

using namespace mm;

long long handleAddress(AddrSignal addr)
{
    constexpr auto getNumUnitsInWord = []() -> std::size_t {
        switch (one_cycle_params::main_memory::ADDRESSING_UNIT) {
            case one_cycle_params::addressing_unit::HALFWORD:
                return 2;
            case one_cycle_params::addressing_unit::BYTE:
                return one_cycle_params::WORD_SIZE / 8;
        }
    };
    constexpr std::size_t nUnitsInWord = getNumUnitsInWord();

    long long index = addr.Decimal(true);
    if (index % nUnitsInWord != 0) throw std::logic_error{"Incorrect address: not aligned"};

    index /= nUnitsInWord;
    if (index >= one_cycle_params::main_memory::MEMORY_SIZE) throw std::logic_error{"Incorrect address: too big"};
    return index;
}

void MainMemory::loadData(DataSignal data, AddrSignal addr)
{
    if (state != WRITE_ENABLE) throw std::logic_error{"Incorrect state: not WRITE_ENABLE"};

    long long index = handleAddress(addr);
    memory[index] = data;
}

DataSignal MainMemory::getData(AddrSignal addr) const
{
    if (state != READ_ENABLE) throw std::logic_error{"Incorrect state: not READ_ENABLE"};

    long long index = handleAddress(addr);
    return memory[index];
}
