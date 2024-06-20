#ifndef RISCV_CONTROLLER_HPP
#define RISCV_CONTROLLER_HPP

#include "datapool.hpp"
#include "signal.hpp"

namespace cntrl
{

    using namespace one_cycle_params;
    using Instruction = Signal<controller::INPUT_SIZE>;
    using Controls = Signal<controller::OUTPUS_SIZE>;

    class IController
    {
    public:
        virtual ~IController() = default;

        // the whole decoding logic is here
        [[nodiscard]] virtual Controls decode(const Instruction&) const = 0;
    };

    class Controller final : public IController
    {
    public:
        enum InstructionType {
            R_FORMAT,
            LW,
            SW,
            BEQ
        };

        Controller() = default;
        ~Controller() override = default;

        [[nodiscard]] Controls decode(const Instruction&) const override;

    private:
        static InstructionType decodeInstructionType(const Instruction&);
        static Controls setControlLines(const Instruction&, InstructionType);
    };

}

#endif
