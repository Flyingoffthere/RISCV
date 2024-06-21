#include "../include/register_file.hpp"

using namespace rf;

DataSignal& RegisterFile::operator[](std::size_t idx)
{
    if (idx >= one_cycle_params::register_file::N_REGISTERS) throw std::logic_error{"Too big index"};
    return registers[idx];
}