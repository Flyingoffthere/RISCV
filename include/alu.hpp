#ifndef RISCV_ALU_HPP
#define RISCV_ALU_HPP

#include <utility>
#include <unordered_map>
#include "signal.hpp"
#include "datapool.hpp"

namespace alu
{
    using namespace one_cycle_params::alus;

    using Input = Signal<INPUT_SIZE>;
    using Opcode = Signal<OPCODE_SIZE>;
    using Output = Signal<OUTPUT_SIZE>;
    using Flags = Signal<NUM_FLAGS>;
    using Operation = Output(*)(Input, Input);

    class Hasher
    {
    public:
        std::size_t operator() (Opcode) const;
    };

    using OperationStore = std::unordered_map<Opcode, Operation, Hasher>;



    class ALU
    {
    public:
        ALU() = delete;
        explicit ALU(const OperationStore& operationStore) : opStore{operationStore} {};
        ~ALU() = default;

        std::pair<Output, Flags> compute(const Input&, const Input&, const Opcode&) const;

    private:
        const OperationStore& opStore;
        static Flags testZero(const Output&) ;
    };

}

#endif