#pragma once
// device.h
#ifndef DEVICE_H
#define DEVICE_H

void load_devices(const char* filename);
void add_device(int id, const char* name, int status, float temp, int has_error);
void show_devices();
void toggle_device(int id);
void reset_device(int id);
void simulate_tick_all();
void create_device();
int find_device_by_id(int id);
void update_device();
void delete_device();

#endif
