#include <stdexcept>
#include "../include/controller.hpp"

using namespace cntrl;

Controls MainController::decode(Signal instr) const
{
    InstructionType instrType = decodeInstructionType(instr);
    Controls controls = setControlLines(instrType);
    return controls;
}

MainController::InstructionType
MainController::decodeInstructionType(Signal instr) const
{
    one_cycle_params::Bitmask opcodeBitmask {bitmasks.opcode};
    one_cycle_params::Mask opcodeMask {std::get<0>(opcodeBitmask)};
    std::size_t offset {std::get<1>(opcodeBitmask)};

    instr >>= offset;
    instr &= Signal{opcodeMask};

    if (instr == Signal{0b0110011})
        return MainController::R_FORMAT;
    else if (instr == Signal{0b0000011})
        return MainController::LW;
    else if (instr == Signal{0b0100011})
        return MainController::SW;
    else if (instr == Signal{0b1100111})
        return MainController::BEQ;
    else
        throw std::logic_error{"Incorrect instruction opcode field"};
}

Controls
MainController::setControlLines(MainController::InstructionType instrType)
{
    switch (instrType)
    {
        case MainController::R_FORMAT:
            return Signal{0b00100010};
        case MainController::LW:
            return Signal{0b11110000};
        case MainController::SW:
            return Signal{0b11001000};
        case MainController::BEQ:
            return Signal{0b01000101};
    }
}