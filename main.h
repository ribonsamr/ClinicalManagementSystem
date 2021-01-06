#ifndef MAIN_H
#define MAIN_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0
#define NAME_LENGTH 50
#define PWD_LENGTH 20
#define PATIENTS_NUM 10
#define SLOTS_NUM 5

// Main functions
void authenticateAdmin(void);
void showAdminPanel(void);
void showUserPanel(void);

// Operations Functions
int validateID(int);
int findID(int);
int insertData(int, char[NAME_LENGTH], int, int);
void printAllPatients(void);
void reserveSlot(int);
void cancelSlot(int);
void printSlots(int);
void findPatientByID(int);

// Declare our Admin password
const char* DEFAULT_PASSWORD = "1234";

// Declare UserMode and Gender enums
enum mode { ADMIN = 0, USER = 1 } UserMode;
enum gender { MALE = 0, FEMALE = 1 };

// Declare our Slots structure
struct slots {
  int patientID;
  int available;
  char time[NAME_LENGTH];
}
// And Declare Slots Array
Slots[SLOTS_NUM] = {
    {0, true, "2pm - 2:30pm"}, {0, true, "2.30pm - 3pm"},
    {0, true, "3.30pm - 4pm"}, {0, true, "4pm - 4:30pm"},
    {0, true, "4.30pm - 5pm"},
};

// Declare our Patients structure
struct patient {
  int id;
  char name[NAME_LENGTH];
  int age;
  enum gender gender;
}
// And Declare Patients Array
Patients[PATIENTS_NUM];

#endif