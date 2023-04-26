#include "logger.h"

LogTable::LogTable(std::string _operation)
{
    operation = _operation;
    operation_number = 0;
}

const LogTable& LogTable::operator ++()
{
    operation_number++;
    return *this;
}

void LogTable::Logmsg(std::string func_name)
{
    std::ofstream out("../../src/logs.txt", std::ofstream::app);
    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);

    if (!out.is_open()) throw std::runtime_error("File didn't open");

    out << std::ctime(&end_time) << func_name << " ";
    if (func_name == "UnorderedTable::push()") out << "(if only in search) ";
    out << "\"" << operation << "\" call number: " << operation_number << std::endl;

    out.close();

    operation_number = 0;
}