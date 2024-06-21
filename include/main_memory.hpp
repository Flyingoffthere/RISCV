#ifndef RISCV_MAIN_MEMORY_HPP
#define RISCV_MAIN_MEMORY_HPP

#include <array>
#include <vector>
#include "signal.hpp"
#include "datapool.hpp"

namespace mm
{

    using AddrSignal = Signal;
    using DataSignal = Signal;
    using MemoryType = std::array<DataSignal, one_cycle_params::main_memory::MEMORY_SIZE>;

    class IMainMemory
    {
    public:
        enum MemoryState {
            READ_ENABLE,
            WRITE_ENABLE
        };

        virtual ~IMainMemory() = default;

        virtual void loadData(DataSignal data, AddrSignal addr) = 0;
        [[nodiscard]] virtual DataSignal getData(AddrSignal addr) const = 0;

        virtual void clearMemory() = 0;

        [[nodiscard]] virtual MemoryState getMemoryState() const = 0;
        virtual void setMemoryState(MemoryState state) = 0;
    };

    class MainMemory final : public IMainMemory
    {
    public:
        MainMemory() = default;
        ~MainMemory() override = default;

        void loadData(DataSignal data, AddrSignal addr) override;
        [[nodiscard]] DataSignal getData(AddrSignal addr) const override;

        void clearMemory() override
        {memory.fill(DataSignal{0});}

        [[nodiscard]] MemoryState getMemoryState() const override
        {return state;}
        void setMemoryState(MemoryState state_) override
        {state = state_;}

    private:
        MemoryType memory{};
        MemoryState state{READ_ENABLE};
    };
}


#endif
