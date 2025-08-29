#include "monitor.h"
#include "device.h"
#include "utils.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sensor_test() {
    cout << "Running sensor test...\n";
    srand(time(0));

    bool all_pass = true;
    for (int i = 0; i < 5; i++) {
        int temp = 20 + rand() % 15;
        cout << "Temp Reading " << (i + 1) << ": " << temp << "C";

        if (temp > 32) {
            cout << "  -> FAIL\n";
            all_pass = false;
        }
        else {
            cout << "  -> OK\n";
        }

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    if (all_pass) cout << "\nAll sensors OK. Test PASSED.\n";
    else cout << "\nSome sensors failed! Test FAILED.\n";
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


