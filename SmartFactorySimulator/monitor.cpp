#include "monitor.h"
#include "device.h"
#include "utils.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

#include <cstdlib>
#include <ctime>

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sensor_test() {
    cout << "Running sensor test";
    for (int i = 0; i < 5; i++) {
        cout << "." << flush; //flush: xa bo dem ngay lap tuc
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "\nSensor test completed successfully.\n";
}

void realtime_monitor() {
    cout << "Starting real-time monitoring. \n";
    while (true) {
        clear_screen();
        show_devices();
        simulate_tick_all();
        this_thread::sleep_for(chrono::seconds(1));
    }
}


