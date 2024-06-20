#include <stdexcept>
#include "../include/controller.hpp"

using namespace cntrl;

Controls Controller::decode(const Instruction& instr) const
{
    InstructionType instrType = decodeInstructionType(instr);
    Controls controls = setControlLines(instr, instrType);
    return controls;
}

Controller::InstructionType
Controller::decodeInstructionType(const Instruction& instr)
{
    if (instr == Instruction{0b0110011})
        return Controller::R_FORMAT;
    else if (instr == Instruction{0b0000011})
        return Controller::LW;
    else if (instr == Instruction{0b0100011})
        return Controller::SW;
    else if (instr == Instruction{0b1100111})
        return Controller::BEQ;
    else
        throw std::logic_error{"Incorrect instruction opcode field"};
}

Controls
Controller::setControlLines(const Instruction& instr, Controller::InstructionType instrType)
{
    using Funct3 = Signal<3>;
    using Funct7 = Signal<7>;

    switch (instrType) {

    }
}