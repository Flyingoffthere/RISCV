#include "../include/alu.hpp"

using namespace alu;

Flags ALU::testZero(const alu::Output& output)
{
    return Flags{output == Output{0}};
}

std::pair<Output, Flags>
ALU::compute(const alu::Input& inp1, const alu::Input& inp2, const alu::Opcode& opc) const
{
    Operation f = opStore.at(opc);
    Output output = f(inp1, inp2);
    Flags zeroTest = testZero(output);
    return std::pair<Output, Flags>{output, zeroTest};
}