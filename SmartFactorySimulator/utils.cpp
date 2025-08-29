#include "utils.h"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void enable_color() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

// Function to print menu and get user selection
int select_menu(const char* options[], int count) {
    int choice = -1;

    while (true) {
        // Print menu header in yellow
        cout << "\033[33m\n====== MENU ======\033[0m\n";

        // Print each option
        for (int i = 0; i < count; i++) {
            // Option number in cyan, text in default color
            cout << "\033[36m" << (i + 1) << ".\033[0m " << options[i] << "\n";
        }

        // Ask for input
        cout << "\033[32mChoose an option: \033[0m";
        cin >> choice;

        // Validate input
        if (cin.fail() || choice < 1 || choice > count) {
            cin.clear();              // Reset error state
            cin.ignore(10000, '\n');  // Discard invalid input
            cout << "\033[31mInvalid choice, please try again.\033[0m\n"; // Error in red
        }
        else {
            break;
        }
    }
    return choice;
}

// Function to show main menu depending on admin or normal user
int select_main_menu(int is_admin) {
    // Admin options
    const char* admin_options[] = {
        "Show Devices",
        "Add Device",
        "Update Device",
        "Delete Device",
        "Toggle Device",
        "Reset Device",
        "Run Sensor Test",
        "Real-time Monitor",
        "Exit"
    };

    // User options
    const char* user_options[] = {
        "Show Devices",
        "Toggle Device",
        "Run Sensor Test",
        "Real-time Monitor",
        "Exit"
    };

    // Call select_menu depending on role
    if (is_admin) {
        return select_menu(admin_options, 9);
    }
    else {
        return select_menu(user_options, 5);
    }
}
