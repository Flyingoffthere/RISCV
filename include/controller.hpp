#ifndef RISCV_CONTROLLER_HPP
#define RISCV_CONTROLLER_HPP

#include "datapool.hpp"
#include "signal.hpp"

namespace cntrl
{

    using Controls = Signal;

    class IController
    {
    public:
        virtual ~IController() = default;

        // the whole decoding logic is here
        [[nodiscard]] virtual Controls decode(Signal) const = 0;
    };

    class MainController final : public IController
    {
    public:
        enum InstructionType {
            R_FORMAT,
            LW,
            SW,
            BEQ
        };

        MainController() = default;
        ~MainController() override = default;

        [[nodiscard]] Controls decode(Signal) const override;

    private:
        one_cycle_params::controllers::main_controller::Bitmasks bitmasks{
            one_cycle_params::controllers::main_controller::bitmasks
        };

        [[nodiscard]] InstructionType decodeInstructionType(Signal) const;
        static Controls setControlLines(InstructionType);
    };

}

#endif
