#ifndef RISCV_INSTRUCTION_MEMORY_HPP
#define RISCV_INSTRUCTION_MEMORY_HPP

#include <array>
#include <vector>
#include "signal.hpp"
#include "datapool.hpp"

namespace im
{

    using AddrSignal = Signal;
    using InstrSignal = Signal;
    using MemoryType = std::array<InstrSignal, one_cycle_params::instruction_memory::MEMORY_SIZE>;

    class IInstructionMemory
    {
    public:
        virtual ~IInstructionMemory() = default;

        // halfword addressing
        [[nodiscard]] virtual InstrSignal getInstruction(const AddrSignal& addr) const = 0;
        virtual void loadInstructions(std::vector<InstrSignal> instrs) = 0;
        virtual void clearMemory() = 0;

        [[nodiscard]] virtual std::size_t LoadedInstrs() const = 0;
    };

    class InstructionMemory final : public IInstructionMemory
    {
    public:
        InstructionMemory() = default;
        ~InstructionMemory() noexcept override = default;

        [[nodiscard]] InstrSignal getInstruction(const AddrSignal& addr) const override;
        void loadInstructions(std::vector<InstrSignal> instrs) override;
        void clearMemory() override;

        [[nodiscard]] std::size_t LoadedInstrs() const override
        {return loadedInstrs;}

    private:
        MemoryType memory{};
        std::size_t loadedInstrs{0};
    };
}




#endif
