#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <memory>

#include <memory>
#include "../include/signal.hpp"
#include "../include/instruction_memory.hpp"
#include "../include/main_memory.hpp"
#include "../include/register_file.hpp"
#include "../include/alu.hpp"


TEST_CASE("signal construction", "[signal]")
{
    // check descriptors
    REQUIRE(Signal<5>{}.Size() == 5);
    REQUIRE(Signal<3>{"100"}.Size() == 3);
    REQUIRE(Signal<4>{0b1010}.Size() == 4);

    // check transforms
    REQUIRE(Signal<4>{"1011"}.String() == std::string{"1011"});
    REQUIRE(Signal<3>{0b110}.Decimal(true) == 6);
    REQUIRE(Signal<4>{0b1110}.Decimal(false) == -2);

    // check operators
    REQUIRE(Signal<4>{"1010"} == Signal<4>{0b1010});
    REQUIRE(Signal<3>{"110"}[0] == 0);
    REQUIRE(Signal<3>{0b110}[0] == 0);
    std::cout << Signal<3>{"110"} << std::endl;
    std::cout << Signal<3>{0b110} << std::endl;

    // check utils
    REQUIRE(sliceSignal<4, 1, 3>(Signal<4>{0b1101}) == Signal<2>{0b10});
    REQUIRE(concatSignals<2, 2>(Signal<2>{0b10}, Signal<2>{10})
            == Signal<4>{0b1010});

}

TEST_CASE("instruction memory", "[instruction_memory]")
{
    using namespace im;
    using namespace one_cycle_params::instruction_memory;

    std::unique_ptr<IInstructionMemory> instrMem {new InstructionMemory};

    SECTION("loading and removing instrs") {
        REQUIRE(instrMem->LoadedInstrs() == 0);
        instrMem->loadInstructions(std::vector<InstrSignal> {InstrSignal{0}});
        REQUIRE(instrMem->LoadedInstrs() == 1);
        instrMem->clearMemory();
        REQUIRE(instrMem->LoadedInstrs() == 0);
    }

    SECTION("work with empty memory") {
        CHECK_THROWS(instrMem->getInstruction(AddrSignal{0}));
        std::vector<InstrSignal> payload {InstrSignal{0}};
        instrMem->loadInstructions(payload);
        instrMem->clearMemory();
        CHECK_THROWS(instrMem->getInstruction(AddrSignal{0}));
    }

    SECTION("try to overwrite signal") {
        std::vector<InstrSignal> payload (MEMORY_SIZE + 1);
        CHECK_THROWS(instrMem->loadInstructions(payload));
    }

    SECTION("double load") {
        std::vector<InstrSignal> payload(1);
        instrMem->loadInstructions(payload);
        CHECK_THROWS(instrMem->loadInstructions(payload));
    }

    SECTION("try to get instrs") {
        std::vector<InstrSignal> payload(2);
        instrMem->loadInstructions(payload);
        InstrSignal fetched;

        fetched = instrMem->getInstruction(AddrSignal {0});
        REQUIRE(fetched == InstrSignal{0});
        CHECK_THROWS(instrMem->getInstruction(AddrSignal{1}));
    }
}

TEST_CASE("main memory", "[main_memory]")
{
    using namespace mm;

    std::unique_ptr<IMainMemory> mem {new MainMemory};

    SECTION("initial state") {
        REQUIRE(mem->getMemoryState() == IMainMemory::READ_ENABLE);
        REQUIRE(mem->getData(AddrSignal{0}) == DataSignal{0});
        CHECK_THROWS(mem->getData(AddrSignal{1}));
    }

    SECTION("check states functionality") {
        CHECK_THROWS(mem->loadData(DataSignal{0}, AddrSignal{0}));
        mem->setMemoryState(IMainMemory::WRITE_ENABLE);
        REQUIRE(mem->getMemoryState() == IMainMemory::WRITE_ENABLE);
        CHECK_THROWS(mem->getData(AddrSignal{0}));
        CHECK_NOTHROW(mem->loadData(DataSignal{0}, AddrSignal{0}));
    }

    SECTION("check storage") {
        mem->setMemoryState(IMainMemory::WRITE_ENABLE);
        mem->loadData(DataSignal{1}, AddrSignal{4});
        mem->setMemoryState(IMainMemory::READ_ENABLE);
        REQUIRE(mem->getData(AddrSignal{0}) == DataSignal{0});
        REQUIRE(mem->getData(AddrSignal{4}) == DataSignal{1});

        mem->clearMemory();
        REQUIRE(mem->getData(AddrSignal{4}) == DataSignal{0});
    }
}

TEST_CASE("register file", "[register_file]")
{
    using namespace rf;
    using namespace one_cycle_params::register_file;

    std::unique_ptr<IRegisterFile> rf {new RegisterFile};

    CHECK_THROWS((*rf)[N_REGISTERS]);
    REQUIRE((*rf)[0] == DataSignal{0});
    (*rf)[1] = DataSignal{1};
    REQUIRE((*rf)[1] == DataSignal{1});
}

TEST_CASE("ALU", "[ALU]")
{
    using namespace alu;

    OperationStore operationStore {
            {"00", Conj},
            {"01", Disj},
            {"11", Xor},
    };
    ALU alu{operationStore};
    auto operationTester =
        [alu](std::string i1_, std::string i2_, std::string opc_, std::string expected_) {
        Input i1{std::move(i1_)}, i2{std::move(i2_)};
        Opcode opc{std::move(opc_)};
        Output expected{std::move(expected_)}, output;

        output = alu.computePure(i1, i2, opc);
        REQUIRE(output == expected);
    };

    SECTION("conj") {
        operationTester("0", "1", "00", "0");
        operationTester("1", "1", "00", "1");
        operationTester("11", "01", "00", "01");
    }

    SECTION("disj") {
        operationTester("0", "1", "01", "1");
        operationTester("1", "1", "01", "1");
        operationTester("01", "01", "01", "01");
    }

    SECTION("xor") {
        operationTester("0", "1", "11", "1");
        operationTester("1", "1", "11", "0");
        operationTester("01", "01", "11", "00");
    }

}