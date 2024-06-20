#ifndef RISCV_COMMUNICATION_HPP
#define RISCV_COMMUNICATION_HPP

#include <vector>
#include "signal.hpp"


class ComputerComponent;

class ICommunication {
    enum class EventType;

public:
    virtual ~ICommunication() = default;
    virtual void passData(std::vector<Signal> data,
                          EventType event) = 0;
};

class ComputerComponent {
protected:
    ICommunication* computer_;

public:
    explicit ComputerComponent(ICommunication* computer = nullptr)
    :   computer_{computer}
    {}
    void setComputer(ICommunication* computer)
    {
        computer_ = computer;
    }
};

#endif
