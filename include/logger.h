#pragma once
#pragma warning(disable: 4996)
#include <iostream>
#include <ctime>
#include <fstream>
#include <chrono>

class LogTable
{
private:
    std::string operation;                                 // Название операции
    int operation_number;                                  // Количество операций

public:
    LogTable(std::string);                                 // Конструктор, принимающий название класса
    const LogTable& operator ++();                         // Префиксный инкремент, для увеличения количества совершенных операций
    void Logmsg(std::string);                              // Запись в файл информации о совершенных действиях

};