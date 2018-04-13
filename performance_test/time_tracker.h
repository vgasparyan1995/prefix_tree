#pragma once

#include <ctime>
#include <iostream>
#include <string>

struct time_tracker
{
public:
    explicit time_tracker(const std::string& name)
        : m_name(name)
    {
    }

    void start()
    {
        m_start = std::clock();
    }

    void end()
    {
        auto end = std::clock();
        m_duration += (end - m_start);
        m_start = end;
    }

    void print_compare(const time_tracker& against)
    {
        std::cout << "____" << m_duration << " cpu_time " << m_name << '\n';
        std::cout << "____" << against.m_duration << " cpu_time " << against.m_name << '\n';
        const auto diff = (double)m_duration / (double)against.m_duration;
        if (diff < 1.0) {
            std::cout << "\e[32m" << (1.0 - diff) * 100.0 << "% faster\e[0m\n";
        } else {
            std::cout << "\e[31m" << (diff - 1.0) * 100.0 << "% slower\e[0m\n";
        }
    }

    void reset()
    {
        m_duration = 0;
    }

private:
    using time_point = std::clock_t;
    using duration   = long int;

    std::string m_name;
    time_point  m_start;
    duration    m_duration;
};
