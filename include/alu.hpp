#ifndef RISCV_ALU_HPP
#define RISCV_ALU_HPP

#include <utility>
#include <unordered_map>
#include "signal.hpp"
#include "datapool.hpp"

namespace alu
{
    using Input = Signal;
    using Opcode = Signal;
    using Output = Signal;
    using Flags = Signal;
    using AluOutput = std::pair<Output, Flags>;
    using Operation = Output(*)(Input, Input);

    using OperationStore = std::unordered_map<std::string, Operation>; // key is a string repr of Opcode

    class ALU
    {
    public:
        ALU() = delete;
        explicit ALU(const OperationStore& operationStore) : opStore{operationStore} {};
        ~ALU() = default;

        [[nodiscard]] AluOutput compute(const Input&, const Input&, const Opcode&) const;
        [[nodiscard]] Output computePure(const Input&, const Input&, const Opcode&) const;

    private:
        const OperationStore& opStore;
        static Flags testZero(const Output&) ;
    };

    Output Conj(Input i1, Input i2);
    Output Disj(Input i1, Input i2);
    Output Xor(Input i1, Input i2);
}

#endif