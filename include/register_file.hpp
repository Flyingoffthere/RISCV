#ifndef RISCV_REGISTER_FILE_HPP
#define RISCV_REGISTER_FILE_HPP

#include <array>
#include "signal.hpp"
#include "datapool.hpp"


namespace rf
{

    using DataSignal = Signal;
    using MemoryType = std::array<DataSignal, one_cycle_params::register_file::N_REGISTERS>;

    class IRegisterFile
    {
    public:
        virtual ~IRegisterFile() = default;

        virtual DataSignal& operator[](std::size_t idx) = 0;
    };

    class RegisterFile final : public IRegisterFile
    {
    public:
        RegisterFile() = default;
        ~RegisterFile() override = default;

        DataSignal& operator[](std::size_t idx) override;

    private:
        MemoryType registers{};
    };
}

#endif
