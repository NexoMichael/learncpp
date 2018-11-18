#include <iostream>
#include <chrono>

int main()
{
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock_t> m_beg;

    m_beg = clock_t::now();

    long c = 0;
    for (int i = 0; i < 100000; i++)
        c = c + i;

    double elapsed = std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();

    std::cout << "Elapsed: " << elapsed << "\n";

    return 0;
}