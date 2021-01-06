#include "main.h"

int main() {
  // Initialize the UserMode with user (1)
  UserMode = USER;

  puts("--Welcome, please choose the user mode:--");

  char userModeInput;
  printf("User or Admin (u/a): ");
  scanf("%c", &userModeInput);

  // Check for admin
  if (tolower(userModeInput) == 'a') {
    authenticateAdmin();
  }

  // Start the loop
  while (true) {
    // If admin, proceed with the admin panel
    if (UserMode == ADMIN)
      showAdminPanel();
    else
      // Otherwise, proceed with the default user panel
      showUserPanel();
  }

  return 0;
}

void authenticateAdmin() {
  int i = 0;
  char pwd[PWD_LENGTH];

  // Loop 3 times
  while (i != 3) {
    printf("Tries: %d, Enter the password: ", i);
    scanf("%s", pwd);

    // Compare the two strings, and if they're the same,
    // allow the user to access with admin
    if (strcmp(pwd, DEFAULT_PASSWORD) == 0) {
      puts("Welcome Admin!");

      // Change the UserMode to admin.
      UserMode = ADMIN;

      // Break out of the function
      return;
    }

    // Increment i as the tries goes on
    i++;
  }

  // The user then failed to authenticate, exit the program.
  puts("Try limit is reached. Program will close.");
  exit(1);
}

int validateID(int id) {
  // If the ID is smaller than 0, return false
  if (id < 1)
    return false;

  // Search if the provided ID exists in our list
  // If so, return false, the new ID should be unique
  for (int i = 0; i < PATIENTS_NUM; i++) {
    if (Patients[i].id == id) {
      return false;
    }
  }

  // Return true, the ID is unique
  return true;
}

int findID(int id) {
  /*
    This function either returns the index of the patient
    in our array (zero -> PATIENTS_NUM-1) or -1 if not found/error
  */

  // If the ID is smaller than 0, return -1
  if (id < 1)
    return -1;

  // Search for the ID in our list, if found, return
  // the index of the patient in our array
  for (int i = 0; i < PATIENTS_NUM; i++) {
    if (Patients[i].id == id) {
      puts("Found");
      return i;
    }
  }

  // Otherwise, not found, return -1
  return -1;
}

int insertData(int id, char name[NAME_LENGTH], int age, int gender) {
  /*
    Loop through our patients array, and find an empty struct
    that contains id = 0 (our default) and enter the new data
  */
  for (int i = 0; i < PATIENTS_NUM; i++) {
    if (Patients[i].id == 0) {
      Patients[i].id = id;
      strcpy(Patients[i].name, name);
      Patients[i].age = age;
      Patients[i].gender = gender;

      // Return true indicating everything went well
      return true;
    }
  }

  // Return false indicating something went wrong
  return false;
}

void printAllPatients() {
  puts("\n--Patients Data--\n");
  for (int i = 0; i < PATIENTS_NUM; i++) {
    // Check if the item's id > 0 (which means not empty)
    if (Patients[i].id > 0) {
      printf("ID: %d, name: %s, age: %d, gender: %c\n", Patients[i].id,
             Patients[i].name, Patients[i].age,
             (Patients[i].gender == MALE) ? 'm' : 'f');
    }
  }
  puts("\n--Patients Data--\n");
}

void printSlots(int empty) {
  /*
    This function prints the empty / reserved slots
    based on the empty parameter value

    If empty == 0 -> prints reserved slots
    If empty == 1 -> prints empty slots
  */
  for (int i = 0; i < SLOTS_NUM; i++) {
    if (Slots[i].available == empty) {
      printf("Index: %d, time: %s, PatientID: %d\n", i + 1, Slots[i].time,
             Slots[i].patientID);
    }
  }

  puts("");
}

void reserveSlot(int patientID) {
  int slot;
  printf("Enter the index: ");
  scanf("%d", &slot);
  slot--;

  // Check user's input inside our Slots range
  if (slot >= 0 && slot < SLOTS_NUM) {
    // Reserve this slot
    Slots[slot].patientID = patientID;
    Slots[slot].available = false;
    puts("\n--Done: Slot reserved.--\n");
  } else {
    puts("\n--ERROR: Enter a correct index--\n");
  }
}

void cancelSlot(int patientID) {
  /*
    This function takes the patientID and search through our
    Slots array and cancel any reservations the patient has
  */

  int found = false;

  for (int i = 0; i < SLOTS_NUM; i++) {
    if (Slots[i].patientID == patientID) {
      // Clear the Slot's patientID value
      Slots[i].patientID = 0;

      // Set the Slot availability to true
      Slots[i].available = true;
      puts("\n--Done: Slot cleared.--\n");

      // Set our flag to true
      found = true;
    }
  }

  if (!found)
    puts("\n--ERROR: ID not found.--\n");
}

void findPatientByID(int id) {
  // Find a patient Struct by ID
  for (int i = 0; i < PATIENTS_NUM; i++) {
    if (Patients[i].id == id) {
      printf("ID: %d, Name: %s, Age: %d, Gender: %c\n", Patients[i].id,
             Patients[i].name, Patients[i].age,
             (Patients[i].gender == MALE) ? 'm' : 'f');
      puts("");
      return;
    }
  }
  puts("\n--ERROR: ID not found.--\n");
}

void showUserPanel() {
  puts("--Welcome, please choose one of the following:--");
  while (true) {
    puts("\n1- View Patient Record");
    puts("2- View today's reservations");
    puts("3- Switch to admin mode");
    puts("4- Exit\n");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
      case 1: {
        int id;
        printf("Enter the ID: ");
        scanf("%d", &id);
        findPatientByID(id);
        break;
      }
      case 2: {
        // Print reserved slots
        printSlots(false);
        break;
      }
      case 3: {
        authenticateAdmin();
        // If the user auths successfully, exit the function
        // and the loop inside the main will switch the panels
        return;
      }
      case 4: {
        exit(0);
      }
      default:
        continue;
    }
  }
}

void showAdminPanel() {
  puts("What do you want to do?");
  while (true) {
    puts("\n1- Add new patient");
    puts("2- Edit a patient");
    puts("3- Reserve a slot with the doctor");
    puts("4- Cancel a slot with the doctor");
    puts("5- Switch to normal User access");
    puts("6- Exit\n");

    int option;
    scanf("%d", &option);

    switch (option) {
      case 1: {
        int id;
        printf("Enter the ID: ");
        scanf("%d", &id);

        // If the ID isn't valid, repeat the loop
        if (!validateID(id)) {
          puts("\nERROR: ID already exists or < 0.\n");
          continue;
        }

        // ID is valid, init the needed variables
        char name[NAME_LENGTH], g;
        int age;
        printf("Enter the Name: ");
        scanf("%s", name);
        printf("Enter the Gender (m/f): ");
        scanf(" %c", &g);
        printf("Enter the Age: ");
        scanf("%d", &age);

        // Init new gender variable, and map user input to
        // MALE or FEMALE (0, 1)
        enum gender gender = (tolower(g) == 'm') ? MALE : FEMALE;

        // Insert the data and wait for the result (true, false)
        int result = insertData(id, name, age, gender);

        if (!result) {
          puts("Data not inserted.");
          continue;
        }

        // If data was inserted successfully, print all the patients data
        printAllPatients();
        break;
      }

      case 2: {
        int id;
        printf("Enter the ID: ");
        scanf("%d", &id);

        // Get the patient index in our array
        int patientRecord = findID(id);

        // If the value was -1, then the ID wasn't found
        if (patientRecord == -1) {
          puts("\nERROR: ID not found or < 0.\n");
          continue;
        }

        // Otherwise, init needed variables to edit the patient data
        char name[NAME_LENGTH], g;
        int age;

        // Declare new gender
        enum gender gender;

        // Copy the existing data into our variables
        strcpy(name, Patients[patientRecord].name);
        g = Patients[patientRecord].gender;
        age = Patients[patientRecord].age;

        printf("Enter the id (%d): ", id);
        scanf("%d", &id);
        printf("Enter the Name (%s): ", name);
        scanf("%s", name);
        printf("Enter the Gender (m/f) (%c): ", (g == MALE) ? 'm' : 'f');
        scanf(" %c", &g);
        printf("Enter the Age (%d): ", age);
        scanf("%d", &age);

        // Map the user's input from (m/f) to (MALE/FEMALE)
        gender = (tolower(g) == 'm') ? MALE : FEMALE;

        // Edit the patient's data
        Patients[patientRecord].id = id;
        strcpy(Patients[patientRecord].name, name);
        Patients[patientRecord].gender = gender;
        Patients[patientRecord].age = age;

        printAllPatients();
        break;
      }
      case 3: {
        puts("\n--Reserve a slot with the doctor--\n");
        // Print empty slots
        printSlots(true);

        int id;
        printf("Enter the ID: ");
        scanf("%d", &id);
        int patientRecord = findID(id);

        // If the value == -1, then the ID wasn't found
        if (patientRecord == -1) {
          puts("\nERROR: ID not found or < 0.\n");
          continue;
        }

        // Otherwise, reserve a slot with this ID
        reserveSlot(id);
        break;
      }
      case 4: {
        puts("\n--Cancel a slot with the doctor--\n");
        int id;
        printf("Enter the ID: ");
        scanf("%d", &id);
        int patientRecord = findID(id);

        if (patientRecord == -1) {
          puts("\nERROR: ID not found or < 0.\n");
          continue;
        }

        cancelSlot(id);
        break;
      }
      case 5: {
        // Switch modes and exit the function
        UserMode = USER;
        return;
      }
      case 6: {
        exit(0);
      }
      default:
        continue;
    }
  }
}
