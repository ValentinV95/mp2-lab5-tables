#pragma once
#pragma warning(disable: 4996)
#include <iostream>
#include <ctime>
#include <fstream>
#include <chrono>

class LogTable
{
private:
    std::string operation;
    int operation_number;
public:
    LogTable(std::string);

    const LogTable& operator ++();

    void Logmsg(std::string);
};