#ifndef RISCV_DATAPOOL_HPP
#define RISCV_DATAPOOL_HPP


#include <cstddef>

consteval size_t logTwo(std::size_t val)
{
    size_t runningVal = 2, power = 1;
    while (runningVal < val) {
        runningVal *= 2;
        power++;
    }
    if (runningVal > val)
        return 0;
    return power;
}

namespace one_cycle_params
{
    enum class addressing_unit {
        BYTE,
        HALFWORD
    };

    namespace instruction_memory
    {
        constexpr addressing_unit ADDRESSING_UNIT = addressing_unit::HALFWORD;
        constexpr std::size_t WORD_SIZE = 32;
        constexpr std::size_t MEMORY_SIZE = 512;
        constexpr std::size_t ADDR_SIZE = logTwo(MEMORY_SIZE);

        static_assert(WORD_SIZE % 8 == 0 && WORD_SIZE != 0); // bytes aligned
        static_assert(ADDR_SIZE != 0); // valid MEMORY_SIZE
    }

    namespace main_memory
    {
        constexpr addressing_unit ADDRESSING_UNIT = addressing_unit::BYTE;
        constexpr std::size_t WORD_SIZE = 32;
        constexpr std::size_t MEMORY_SIZE = 1024;
        constexpr std::size_t ADDR_SIZE = logTwo(MEMORY_SIZE);

        static_assert(ADDRESSING_UNIT == addressing_unit::BYTE);
        static_assert(WORD_SIZE % 8 == 0 && WORD_SIZE != 0);
        static_assert(ADDR_SIZE != 0);
    }

    namespace register_file
    {
        constexpr std::size_t WORD_SIZE = 32;
        constexpr std::size_t N_REGISTERS = 32;

        static_assert(WORD_SIZE % 8 == 0 && WORD_SIZE != 0);
        static_assert(N_REGISTERS > 0);
    }

}

#endif
