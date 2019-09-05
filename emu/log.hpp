#pragma once

#include <iostream>

enum class LogLevel
{
    Debug,
    Info,
    Warning,
    Error,
    Fatal,
};

std::ostream &log(const LogLevel level)
{
    switch (level)
    {
    case LogLevel::Debug:
        std::cout << "[D] ";
        break;
    case LogLevel::Info:
        std::cout << "[I] ";
        break;
    case LogLevel::Warning:
        std::cout << "[W] ";
        break;
    case LogLevel::Error:
        std::cout << "[E] ";
        break;
    case LogLevel::Fatal:
        std::cout << "[F] ";
        break;
    }

    return std::cout;
}