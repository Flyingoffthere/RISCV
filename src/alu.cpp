#include "../include/alu.hpp"

using namespace alu;

Flags ALU::testZero(const alu::Output& output)
{
    return Flags{output == Output{0}};
}

Output
ALU::computePure(const alu::Input& inp1, const alu::Input& inp2, const alu::Opcode& opc) const
{
    Operation f = opStore.at(opc.String());
    Output output = f(inp1, inp2);
    return output;
}

AluOutput
ALU::compute(const alu::Input& inp1, const alu::Input& inp2, const alu::Opcode& opc) const
{
    Output output = computePure(inp1, inp2, opc);
    Flags zeroTest = testZero(output);
    return std::pair<Output, Flags>{output, zeroTest};
}

Output alu::Conj(Input i1, Input i2)
{return Output{i1 & i2};}

Output alu::Disj(Input i1, Input i2)
{return Output{i1 | i2};}

Output alu::Xor(Input i1, Input i2)
{return Output{i1 ^ i2};}
