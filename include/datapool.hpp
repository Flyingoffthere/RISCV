#ifndef RISCV_DATAPOOL_HPP
#define RISCV_DATAPOOL_HPP

#include <utility>
#include <cstddef>
#include <bitset>

consteval std::size_t logTwo(std::size_t val)
{
    std::size_t runningVal = 2, power = 1;
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
    constexpr std::size_t WORD_SIZE = 32;
    using Mask = std::bitset<WORD_SIZE>;
    using Bitmask = std::pair<Mask, std::size_t>; // mask-offset
    static_assert(WORD_SIZE % 8 == 0 && WORD_SIZE > 0);

    enum class addressing_unit {
        BYTE,
        HALFWORD
    };

    namespace instruction_memory
    {
        constexpr addressing_unit ADDRESSING_UNIT = addressing_unit::HALFWORD;
        constexpr std::size_t MEMORY_SIZE = 512;
    }

    namespace main_memory
    {
        constexpr addressing_unit ADDRESSING_UNIT = addressing_unit::BYTE;
        constexpr std::size_t MEMORY_SIZE = 1024;

        static_assert(ADDRESSING_UNIT == addressing_unit::BYTE);
    }

    namespace register_file
    {
        constexpr std::size_t N_REGISTERS = 32;

        static_assert(N_REGISTERS == 32);
    }

    namespace alus
    {
        struct Bitmasks {
            Bitmask controls {0b1111, 0};
        };
        constexpr Bitmasks bitmasks{};
    }

    namespace controllers
    {
        namespace main_controller
        {
            struct Bitmasks {
                Bitmask opcode {0b1111111, 0};
            };
            constexpr Bitmasks bitmasks{};
        }

        namespace alu_controller
        {
            struct Bitmasks {
                Bitmask aluOp {0b11, 0};
                Bitmask funct7 {0b1111111, 25};
                Bitmask funct3 {0b111, 12};
            };
            constexpr Bitmasks bitmasks{};
        }
    }

}

#endif
