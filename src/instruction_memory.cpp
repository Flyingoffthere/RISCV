#include <stdexcept>
#include "../include/instruction_memory.hpp"

using namespace im;

InstrSignal InstructionMemory::getInstruction(const AddrSignal& addr) const
{
    constexpr auto getNumUnitsInWord = []() -> std::size_t {
        switch (one_cycle_params::instruction_memory::ADDRESSING_UNIT) {
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
    if (index >= loadedInstrs) throw std::logic_error{"Incorrect address: too big"};

    return memory[index];
}

void InstructionMemory::loadInstructions(std::vector<InstrSignal> instrs)
{
    if (loadedInstrs != 0) throw std::logic_error{"Attempt to overwrite instr memory.\n"
                                                  "Consider calling clearMemory."};
    if(instrs.size() >= one_cycle_params::instruction_memory::MEMORY_SIZE) throw std::logic_error{"Too many instrs"};

    for (int i = 0; i < instrs.size(); i++) {
        memory[i] = instrs[i];
        loadedInstrs++;
    }
}

void InstructionMemory::clearMemory()
{
    loadedInstrs = 0;
}