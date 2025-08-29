#include "device.h"
#include "log.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>   // rand(), srand()
#include <ctime>

using namespace std;

struct Device {
    int id;
    string name;
    bool status;
    double temp;
    double pressure;
    double flow;
    bool has_error;
};

static vector<Device> devices;

//Load devices from file function
void load_devices(const char* filename) {
    ifstream fin(filename); // open file to read
    if (!fin.is_open()) {
        cerr << "Warning: Could not open " << filename
            << ". Starting with an empty list.\n";
        return;
    }

    devices.clear();
    Device d;
    while (fin >> d.id >> d.name >> d.status
        >> d.temp >> d.pressure >> d.flow >> d.has_error) {
        devices.push_back(d);
    }
    fin.close();
}

//Add device function
void add_device(int id, const string& name, int status,
    float temp, float pressure, float flow, int has_error) {
    Device d = { id, name, status, temp, pressure, flow, has_error };
    devices.push_back(d);
    write_log(("Device added: " + d.name).c_str());
}

//Show list devices function
void show_devices() {
    // Print table header with cyan borders
    cout << "\033[36m+----+----------------+--------+--------+----------+--------+--------+\033[0m\n";
    cout << "\033[36m| ID | Name           | Status | Temp   | Pressure | Flow   | Error  |\033[0m\n";
    cout << "\033[36m+----+----------------+--------+--------+----------+--------+--------+\033[0m\n";

    for (auto& d : devices) {
        // Choose color based on error
        string color = d.has_error ? "\033[31m" : "\033[32m"; // Red if error, green if OK

        cout << "| "
            << setw(2) << d.id << " | "
            << setw(14) << d.name << " | "
            << setw(6) << (d.status ? "ON" : "OFF") << " | "
            << setw(6) << fixed << setprecision(1) << d.temp << " | "
            << setw(8) << fixed << setprecision(1) << d.pressure << " | "
            << setw(6) << fixed << setprecision(1) << d.flow << " | "
            << color << setw(6) << (d.has_error ? "YES" : "NO") << "\033[0m"
            << " |\n";
    }

    // Footer line
    cout << "\033[36m+----+----------------+--------+--------+----------+--------+--------+\033[0m\n";
}

//Find device by id function
int find_device_by_id(int id) {
    for (int i = 0; i < (int)devices.size(); i++) {
        if (devices[i].id == id) return (int)i;
    }
    return -1;
}

//Toggle device function
void toggle_device(int id) {
    int idx = find_device_by_id(id);
    if (idx == -1) {
        cout << "Device not found.\n";
        return;
    }
    devices[idx].status = !devices[idx].status;
    write_log(("Toggled device " + devices[idx].name).c_str());
}

//Reset device status & error
void reset_device(int id) {
    int idx = find_device_by_id(id);
    if (idx == -1) {
        cout << "Device not found.\n";
        return;
    }
    devices[idx].has_error = 0;
    devices[idx].status = 0;
    write_log(("Reset device " + devices[idx].name).c_str());
}

//Simulate temparature function
void simulate_tick_all() {
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }

    for (auto& d : devices) {
        if (d.status) {
            // temp random
            d.temp += (rand() % 3 - 1);

            // pressure random
            d.pressure += (rand() % 5 - 2);

            // flow random
            d.flow += (rand() % 7 - 3);

            // Check error
            if (d.temp > 100 || d.pressure > 200 || d.flow < 10) {
                d.has_error = true;
                write_log(("Device error: " + d.name).c_str());
            }
        }
    }
}

//Create device function
void create_device() {
    int id;
    string name;
    bool status;
    double temp, pressure, flow;
    bool has_error;

    cout << "Enter new device ID: ";
    cin >> id;
    if (find_device_by_id(id) != -1) {
        cout << "A device with this ID already exists.\n";
        return;
    }

    cin.ignore(); // Clear leftover newline
    cout << "Enter device name: ";
    getline(cin, name);

    cout << "Enter status (0 = OFF, 1 = ON): ";
    cin >> status;

    cout << "Enter temperature: ";
    cin >> temp;

    cout << "Enter pressure: ";
    cin >> pressure;

    cout << "Enter flow: ";
    cin >> flow;

    cout << "Has error? (0 = No, 1 = Yes): ";
    cin >> has_error;

    add_device(id, name, status, temp, pressure, flow, has_error);

    cout << "Device created successfully!\n";
}

//Update device function
void update_device() {
    int id;
    cout << "Enter device ID to update: ";
    cin >> id;

    int idx = find_device_by_id(id);
    if (idx == -1) {
        cout << "Device not found.\n";
        return;
    }

    Device& d = devices[idx];
    cin.ignore(); // clear newline

    string input;
    cout << "Current name: " << d.name << "\nEnter new name (or '.' to skip): ";
    getline(cin, input);
    if (input != ".") d.name = input;

    cout << "Current status: " << (d.status ? "ON" : "OFF") << "\nEnter new status (0=OFF,1=ON, -1 to skip): ";
    int status;
    cin >> status;
    if (status == 0 || status == 1) d.status = status;

    cout << "Current temperature: " << d.temp << "\nEnter new temperature (-1 to skip): ";
    double temp;
    cin >> temp;
    if (temp >= 0) d.temp = temp;

    cout << "Current pressure: " << d.pressure << "\nEnter new pressure (-1 to skip): ";
    double pressure;
    cin >> pressure;
    if (pressure >= 0) d.pressure = pressure;

    cout << "Current flow: " << d.flow << "\nEnter new flow (-1 to skip): ";
    double flow;
    cin >> flow;
    if (flow >= 0) d.flow = flow;

    cout << "Current error status: " << (d.has_error ? "YES" : "NO") << "\nEnter new error status (0=No,1=Yes,-1 to skip): ";
    int err;
    cin >> err;
    if (err == 0 || err == 1) d.has_error = err;

    write_log(("Updated device " + d.name).c_str());
    cout << "Device updated successfully.\n";
}

//Delete device function
void delete_device() {
    int id;
    cout << "Enter device ID to delete: ";
    cin >> id;
    int idx = find_device_by_id(id);
    if (idx == -1) {
        cout << "Device not found.\n";
        return;
    }
    write_log(("Deleted device " + devices[idx].name).c_str());
    devices.erase(devices.begin() + idx);
    cout << "Delete Successfully ";
}
