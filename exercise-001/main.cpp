#include <fmt/chrono.h>
#include <fmt/format.h>

#include <iostream>
#include <random>

#include "CLI/CLI.hpp"
#include "config.h"

// .bss segment
int bss;

// .data segment
int data = 4711;

// .rodata segment
const int rodata = 42;

auto main(int argc, char **argv) -> int
{
    fmt::print("Value of variable bss {} address of variable bss {}\n",bss, fmt::ptr(&bss));

    fmt::print("Value of variable data {} address of variable data {}\n",data, fmt::ptr(&data));

    fmt::print("Value of variable rodata {} address of variable rodata {}\n",rodata, fmt::ptr(&rodata));


    return 0; /* exit gracefully*/
}