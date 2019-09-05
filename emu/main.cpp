#include "mz.hpp"

int main()
{

    MZ mz = MZ();
    mz.load_file("/Users/nexo/Documents/CodeArcheology/Legend_of_Kyrandia/SETUP.EXE");

    mz.debug_dump();

    mz.parse_opcodes();

    return 0;
}