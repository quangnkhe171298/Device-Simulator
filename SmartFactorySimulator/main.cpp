#include "device.h"
#include "monitor.h"
#include "utils.h"
#include <iostream>

using namespace std;

int main() {
    enable_color();
    cout << "=== IoT Device Management System ===\n";
    load_devices("devices.txt");

    int is_admin;
    cout << "Are you admin? (1 = Yes, 0 = No): ";
    cin >> is_admin;

    bool running = true;
    while (running) {
        int choice = select_main_menu(is_admin);

        if (is_admin) {
            switch (choice) {
            case 1: show_devices(); break;
            case 2: create_device(); break;
            case 3: update_device(); break;
            case 4: delete_device(); break;
            case 5: {
                int id; 
                cout << "Enter ID to toggle: "; 
                cin >> id;
                toggle_device(id);
            } 
                  break;
            case 6: {
                int id; 
                cout << "Enter ID to reset: "; 
                cin >> id;
                reset_device(id);
            } break;
            case 7: sensor_test(); break;
            case 8: realtime_monitor(); break;
            case 9: running = false; break;
            }
        }
        else {
            switch (choice) {
            case 1: show_devices(); break;
            case 2: {
                int id;
                cout << "Enter ID to toggle: ";
                cin >> id;
                toggle_device(id);
            }
                  break;
            case 3: sensor_test(); break;
            case 4: realtime_monitor(); break;
            case 5: running = false; break;
            }
        }
    }

    cout << "Goodbye!\n";
    return 0;
}
