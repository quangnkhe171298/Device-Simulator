#define _CRT_SECURE_NO_WARNINGS
#include "log.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void write_log(const char* message) {
    ofstream logfile("system.log", ios::app);
    if (!logfile.is_open()) {
        cerr << "Error: Could not open system.log\n";
        return;
    }

    time_t now = time(nullptr);
    tm* local_time = localtime(&now);

    logfile << "["
        << (1900 + local_time->tm_year) << "-"
        << (1 + local_time->tm_mon) << "-"
        << local_time->tm_mday << " "
        << local_time->tm_hour << ":"
        << local_time->tm_min << ":"
        << local_time->tm_sec << "] "
        << message << "\n";

    logfile.close();
}
