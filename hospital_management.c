#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Test {
    char name[50];
    float cost;
};

// Structure for a patient
struct Patient {
    int id;
    char name[50];
    char address[100];
    char contact_number[15];
    int age;
    char sex[10];
    char blood_group[10];
    char disease[100];
    int room_number;
    int is_admitted;
    int num_tests;
    struct Test tests[10];
    float bill;
    time_t admission_time;
    char dob[15];
    int is_discharged;
    char doctor_name[50];
    struct Patient* next;
};

// Structure for a doctor
struct Doctor {
    int id;
    char name[50];
    char specialty[50];
    char available_time[50];
    float consultation_fee;
    char phone_number[15];
    int cabin_number;
    struct Doctor* next;
};

// Structure for discharged patient
struct DischargedPatient {
    int id;
    char name[50];
    char address[100];
    char contact_number[15];
    int age;
    char sex[10];
    char blood_group[10];
    char disease[100];
    int room_number;
    float bill;
    time_t admission_time;
    time_t discharge_time;
    struct DischargedPatient* next;
};

// Structure for appointments
struct Appointment {
    int appointment_id;
    int patient_id;
    int doctor_id;
    char patient_name[50];
    char doctor_name[50];
    char appointment_time[50];
    char date[15];
    struct Appointment* next;
};

struct Patient* admitted_patient_list = NULL;
struct Patient* consultation_patient_list = NULL;
struct Doctor* doctor_list = NULL;
struct DischargedPatient* discharged_patient_list = NULL;
struct Appointment* appointment_list = NULL;

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Room rate based on room type
float get_room_rate(int room_type) {
    switch (room_type) {
        case 1: return 500;
        case 2: return 1000;
        case 3: return 2000;
        default: return 0;
    }
}

// Bill calculation
float calculate_bill(int room_type, int days_admitted, int num_tests, struct Test* tests, float consultation_fee) {
    float room_rate = get_room_rate(room_type);
    float test_charge = 0;
    for (int i = 0; i < num_tests; i++) {
        test_charge += tests[i].cost;
    }
    return (room_rate * days_admitted) + test_charge + consultation_fee;
}

// Suggest relevant doctors based on disease
struct Doctor* suggest_doctors_by_disease(const char* disease) {
    struct Doctor* filtered_list = NULL;
    struct Doctor* last = NULL;
    struct Doctor* doc = doctor_list;

    while (doc != NULL) {
        if ((strstr(disease, "heart") && strstr(doc->specialty, "Cardiologist")) ||
            (strstr(disease, "bone") && strstr(doc->specialty, "Orthopedics")) ||
            (strstr(disease, "skin") && strstr(doc->specialty, "Dermatology")) ||
            (strstr(disease, "pregnancy") && strstr(doc->specialty, "Gynecology")) ||
            (strstr(disease, "mental") && strstr(doc->specialty, "Psychiatry")) ||
            (strstr(disease, "stomach") && strstr(doc->specialty, "Gastroenterology"))) {
            struct Doctor* matched_doc = (struct Doctor*)malloc(sizeof(struct Doctor));
            if (matched_doc == NULL) {
                printf("Memory allocation failed.\n");
                return NULL;
            }
            *matched_doc = *doc;
            matched_doc->next = NULL;
            if (filtered_list == NULL) {
                filtered_list = matched_doc;
                last = matched_doc;
            } else {
                last->next = matched_doc;
                last = matched_doc;
            }
        }
        doc = doc->next;
    }
    return filtered_list;
}

// Book an appointment
void book_appointment() {
    struct Appointment* new_appointment = (struct Appointment*)malloc(sizeof(struct Appointment));
    if (new_appointment == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    int patient_id, doctor_id;
    struct Patient* patient = NULL;
    struct Doctor* doctor = NULL;

    printf("\n--- Book Appointment ---\n");
    printf("Enter Patient ID: ");
    if (scanf("%d", &patient_id) != 1) {
        printf("Invalid input for Patient ID.\n");
        free(new_appointment);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    // Check if patient exists
    patient = admitted_patient_list;
    while (patient != NULL) {
        if (patient->id == patient_id) break;
        patient = patient->next;
    }
    if (patient == NULL) {
        patient = consultation_patient_list;
        while (patient != NULL) {
            if (patient->id == patient_id) break;
            patient = patient->next;
        }
    }
    if (patient == NULL) {
        printf("Patient with ID %d not found.\n", patient_id);
        free(new_appointment);
        return;
    }

    printf("Enter Doctor ID: ");
    if (scanf("%d", &doctor_id) != 1) {
        printf("Invalid input for Doctor ID.\n");
        free(new_appointment);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    // Check if doctor exists
    doctor = doctor_list;
    while (doctor != NULL) {
        if (doctor->id == doctor_id) break;
        doctor = doctor->next;
    }
    if (doctor == NULL) {
        printf("Doctor with ID %d not found.\n", doctor_id);
        free(new_appointment);
        return;
    }

    // Check if doctor is suitable for patient's disease
    struct Doctor* suggested_doctors = suggest_doctors_by_disease(patient->disease);
    struct Doctor* temp_doc = suggested_doctors;
    int valid_doctor = 0;
    while (temp_doc != NULL) {
        if (temp_doc->id == doctor_id) {
            valid_doctor = 1;
            break;
        }
        temp_doc = temp_doc->next;
    }
    if (!valid_doctor) {
        printf("Doctor with ID %d is not suitable for the patient's disease.\n", doctor_id);
        while (suggested_doctors != NULL) {
            struct Doctor* temp = suggested_doctors;
            suggested_doctors = suggested_doctors->next;
            free(temp);
        }
        free(new_appointment);
        return;
    }
    while (suggested_doctors != NULL) {
        struct Doctor* temp = suggested_doctors;
        suggested_doctors = suggested_doctors->next;
        free(temp);
    }

    // Input appointment details
    printf("Enter Appointment Date (DD/MM/YYYY): ");
    if (fgets(new_appointment->date, sizeof(new_appointment->date), stdin) == NULL) {
        printf("Error reading date.\n");
        free(new_appointment);
        return;
    }
    new_appointment->date[strcspn(new_appointment->date, "\n")] = '\0';

    printf("Enter Appointment Time (e.g., 10AM-11AM): ");
    if (fgets(new_appointment->appointment_time, sizeof(new_appointment->appointment_time), stdin) == NULL) {
        printf("Error reading time.\n");
        free(new_appointment);
        return;
    }
    new_appointment->appointment_time[strcspn(new_appointment->appointment_time, "\n")] = '\0';

    // Check if doctor is available at the requested time
    if (strstr(doctor->available_time, new_appointment->appointment_time) == NULL) {
        printf("Doctor is not available at the requested time. Available time: %s\n", doctor->available_time);
        free(new_appointment);
        return;
    }

    // Check for time slot conflict
    struct Appointment* temp = appointment_list;
    while (temp != NULL) {
        if (temp->doctor_id == doctor_id &&
            strcmp(temp->date, new_appointment->date) == 0 &&
            strcmp(temp->appointment_time, new_appointment->appointment_time) == 0) {
            printf("Time slot already booked for this doctor.\n");
            free(new_appointment);
            return;
        }
        temp = temp->next;
    }

    // Assign appointment details
    static int appointment_counter = 1000;
    new_appointment->appointment_id = appointment_counter++;
    new_appointment->patient_id = patient_id;
    new_appointment->doctor_id = doctor_id;
    strncpy(new_appointment->patient_name, patient->name, sizeof(new_appointment->patient_name) - 1);
    strncpy(new_appointment->doctor_name, doctor->name, sizeof(new_appointment->doctor_name) - 1);
    new_appointment->next = appointment_list;
    appointment_list = new_appointment;

    // Update patient bill with consultation fee if not already assigned
    if (strcmp(patient->doctor_name, doctor->name) != 0) {
        strncpy(patient->doctor_name, doctor->name, sizeof(patient->doctor_name) - 1);
        patient->bill += doctor->consultation_fee;
    }

    printf("Appointment booked successfully! Appointment ID: %d\n", new_appointment->appointment_id);
    printf("Press Enter to continue...\n");
    getchar();
}

// View appointments
void view_appointments() {
    int choice;
    printf("\n--- View Appointments ---\n");
    printf("1. View by Patient ID\n");
    printf("2. View by Doctor ID\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid choice.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (appointment_list == NULL) {
        printf("No appointments booked.\n");
        return;
    }

    if (choice == 1) {
        int patient_id;
        printf("Enter Patient ID: ");
        if (scanf("%d", &patient_id) != 1) {
            printf("Invalid Patient ID.\n");
            clear_input_buffer();
            return;
        }
        clear_input_buffer();

        struct Appointment* temp = appointment_list;
        int found = 0;
        printf("\n--- Appointments for Patient ID %d ---\n", patient_id);
        while (temp != NULL) {
            if (temp->patient_id == patient_id) {
                printf("Appointment ID: %d\n", temp->appointment_id);
                printf("Patient: %s\n", temp->patient_name);
                printf("Doctor: %s\n", temp->doctor_name);
                printf("Date: %s\n", temp->date);
                printf("Time: %s\n\n", temp->appointment_time);
                found = 1;
            }
            temp = temp->next;
        }
        if (!found) {
            printf("No appointments found for Patient ID %d.\n", patient_id);
        }
    } else if (choice == 2) {
        int doctor_id;
        printf("Enter Doctor ID: ");
        if (scanf("%d", &doctor_id) != 1) {
            printf("Invalid Doctor ID.\n");
            clear_input_buffer();
            return;
        }
        clear_input_buffer();

        struct Appointment* temp = appointment_list;
        int found = 0;
        printf("\n--- Appointments for Doctor ID %d ---\n", doctor_id);
        while (temp != NULL) {
            if (temp->doctor_id == doctor_id) {
                printf("Appointment ID: %d\n", temp->appointment_id);
                printf("Patient: %s\n", temp->patient_name);
                printf("Doctor: %s\n", temp->doctor_name);
                printf("Date: %s\n", temp->date);
                printf("Time: %s\n\n", temp->appointment_time);
                found = 1;
            }
            temp = temp->next;
        }
        if (!found) {
            printf("No appointments found for Doctor ID %d.\n", doctor_id);
        }
    } else {
        printf("Invalid choice.\n");
    }
    printf("Press Enter to continue...\n");
    getchar();
}

// Add new patient
void add_new_patient() {
    struct Patient* new_patient = (struct Patient*)malloc(sizeof(struct Patient));
    if (new_patient == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter Patient ID: ");
    if (scanf("%d", &new_patient->id) != 1) {
        printf("Invalid Patient ID.\n");
        free(new_patient);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    printf("Enter Name: ");
    if (fgets(new_patient->name, sizeof(new_patient->name), stdin) == NULL) {
        printf("Error reading name.\n");
        free(new_patient);
        return;
    }
    new_patient->name[strcspn(new_patient->name, "\n")] = '\0';

    printf("Enter Address: ");
    if (fgets(new_patient->address, sizeof(new_patient->address), stdin) == NULL) {
        printf("Error reading address.\n");
        free(new_patient);
        return;
    }
    new_patient->address[strcspn(new_patient->address, "\n")] = '\0';

    printf("Enter Contact Number: ");
    if (fgets(new_patient->contact_number, sizeof(new_patient->contact_number), stdin) == NULL) {
        printf("Error reading contact number.\n");
        free(new_patient);
        return;
    }
    new_patient->contact_number[strcspn(new_patient->contact_number, "\n")] = '\0';

    printf("Enter Age: ");
    if (scanf("%d", &new_patient->age) != 1) {
        printf("Invalid age.\n");
        free(new_patient);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    printf("Enter Sex: ");
    if (fgets(new_patient->sex, sizeof(new_patient->sex), stdin) == NULL) {
        printf("Error reading sex.\n");
        free(new_patient);
        return;
    }
    new_patient->sex[strcspn(new_patient->sex, "\n")] = '\0';

    printf("Enter Blood Group: ");
    if (fgets(new_patient->blood_group, sizeof(new_patient->blood_group), stdin) == NULL) {
        printf("Error reading blood group.\n");
        free(new_patient);
        return;
    }
    new_patient->blood_group[strcspn(new_patient->blood_group, "\n")] = '\0';

    printf("Enter Date of Birth (DD/MM/YYYY): ");
    if (fgets(new_patient->dob, sizeof(new_patient->dob), stdin) == NULL) {
        printf("Error reading date of birth.\n");
        free(new_patient);
        return;
    }
    new_patient->dob[strcspn(new_patient->dob, "\n")] = '\0';

    printf("Enter Disease: ");
    if (fgets(new_patient->disease, sizeof(new_patient->disease), stdin) == NULL) {
        printf("Error reading disease.\n");
        free(new_patient);
        return;
    }
    new_patient->disease[strcspn(new_patient->disease, "\n")] = '\0';

    // Suggest doctors based on disease
    struct Doctor* suggested_doctors = suggest_doctors_by_disease(new_patient->disease);
    if (suggested_doctors == NULL) {
        printf("No specialist found for this disease. Cannot proceed with doctor assignment.\n");
        free(new_patient);
        return;
    }

    printf("Suggested doctors based on disease '%s':\n", new_patient->disease);
    struct Doctor* d = suggested_doctors;
    while (d != NULL) {
        printf("ID: %d | Name: %s | Specialty: %s | Fee: %.2f\n",
               d->id, d->name, d->specialty, d->consultation_fee);
        d = d->next;
    }

    // Ask for doctor ID from filtered list
    int doctor_id;
    printf("Enter the ID of the doctor to assign: ");
    if (scanf("%d", &doctor_id) != 1) {
        printf("Invalid doctor ID.\n");
        while (suggested_doctors != NULL) {
            struct Doctor* temp = suggested_doctors;
            suggested_doctors = suggested_doctors->next;
            free(temp);
        }
        free(new_patient);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    // Verify the chosen doctor is from filtered list
    struct Doctor* chosen_doc = suggested_doctors;
    while (chosen_doc != NULL) {
        if (chosen_doc->id == doctor_id) break;
        chosen_doc = chosen_doc->next;
    }
    if (chosen_doc == NULL) {
        printf("Invalid doctor selection.\n");
        while (suggested_doctors != NULL) {
            struct Doctor* temp = suggested_doctors;
            suggested_doctors = suggested_doctors->next;
            free(temp);
        }
        free(new_patient);
        return;
    }

    // Free suggested doctors list
    while (suggested_doctors != NULL) {
        struct Doctor* temp = suggested_doctors;
        suggested_doctors = suggested_doctors->next;
        free(temp);
    }

    // Assign selected doctor
    strncpy(new_patient->doctor_name, chosen_doc->name, sizeof(new_patient->doctor_name) - 1);
    new_patient->bill = chosen_doc->consultation_fee;

    printf("Is the patient admitted? (1-Yes, 0-No): ");
    if (scanf("%d", &new_patient->is_admitted) != 1) {
        printf("Invalid input.\n");
        free(new_patient);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (new_patient->is_admitted) {
        printf("Enter Room Number (100-199=General, 200-299=Semi-private, 300-399=Private): ");
        if (scanf("%d", &new_patient->room_number) != 1) {
            printf("Invalid room number.\n");
            free(new_patient);
            clear_input_buffer();
            return;
        }
        int room_type = new_patient->room_number / 100;
        float room_rate = get_room_rate(room_type);

        printf("Room Type: %s | Rate per Day: %.2f\n",
               (room_type == 1) ? "General" :
               (room_type == 2) ? "Semi-private" :
               (room_type == 3) ? "Private" : "Unknown",
               room_rate);

        printf("Enter Number of Days Admitted: ");
        int days_admitted;
        if (scanf("%d", &days_admitted) != 1) {
            printf("Invalid number of days.\n");
            free(new_patient);
            clear_input_buffer();
            return;
        }
        clear_input_buffer();

        // Ask if the user wants to add tests
        char add_tests_choice;
        printf("Do you want to add tests for the patient? (y/n): ");
        scanf(" %c", &add_tests_choice);
        clear_input_buffer();

        if (add_tests_choice == 'y' || add_tests_choice == 'Y') {
            printf("Enter Number of Tests: ");
            if (scanf("%d", &new_patient->num_tests) != 1) {
                printf("Invalid number of tests.\n");
                free(new_patient);
                clear_input_buffer();
                return;
            }
            clear_input_buffer();
            for (int i = 0; i < new_patient->num_tests; i++) {
                printf("Enter Test %d Name: ", i + 1);
                if (fgets(new_patient->tests[i].name, sizeof(new_patient->tests[i].name), stdin) == NULL) {
                    printf("Error reading test name.\n");
                    free(new_patient);
                    return;
                }
                new_patient->tests[i].name[strcspn(new_patient->tests[i].name, "\n")] = '\0';
                printf("Enter Test %d Cost: ", i + 1);
                if (scanf("%f", &new_patient->tests[i].cost) != 1) {
                    printf("Invalid test cost.\n");
                    free(new_patient);
                    clear_input_buffer();
                    return;
                }
                clear_input_buffer();
            }
        } else {
            new_patient->num_tests = 0;
        }

        new_patient->bill = calculate_bill(room_type, days_admitted, new_patient->num_tests, new_patient->tests, chosen_doc->consultation_fee);
        time(&new_patient->admission_time);
        new_patient->next = admitted_patient_list;
        admitted_patient_list = new_patient;
    } else {
        new_patient->room_number = 0;
        new_patient->bill = chosen_doc->consultation_fee;
        new_patient->next = consultation_patient_list;
        consultation_patient_list = new_patient;
    }

    new_patient->is_discharged = 0;

    printf("\nPatient added successfully!\n");
    printf("Do you want to book an appointment for this patient? (y/n): ");
    char book_choice;
    scanf(" %c", &book_choice);
    clear_input_buffer();
    if (book_choice == 'y' || book_choice == 'Y') {
        book_appointment();
    }

    printf("Press Enter to continue...\n");
    getchar();
}

// Discharge patient after full payment
void discharge_patient() {
    int patient_id;
    printf("Enter the Patient ID to discharge: ");
    if (scanf("%d", &patient_id) != 1) {
        printf("Invalid Patient ID.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    struct Patient* temp = admitted_patient_list;
    struct Patient* prev = NULL;
    while (temp != NULL) {
        if (temp->id == patient_id) {
            if (temp->is_discharged) {
                printf("Patient has already been discharged.\n");
                return;
            }
            printf("Total Bill: %.2f\n", temp->bill);
            float payment;
            printf("Enter payment amount: ");
            if (scanf("%f", &payment) != 1) {
                printf("Invalid payment amount.\n");
                clear_input_buffer();
                return;
            }
            clear_input_buffer();
            if (payment < temp->bill) {
                printf("Insufficient payment. Cannot discharge patient.\n");
                return;
            }
            printf("Payment successful. Change: %.2f\n", payment - temp->bill);
            temp->is_discharged = 1;

            struct DischargedPatient* new_discharged_patient = (struct DischargedPatient*)malloc(sizeof(struct DischargedPatient));
            if (new_discharged_patient == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }

            new_discharged_patient->id = temp->id;
            strncpy(new_discharged_patient->name, temp->name, sizeof(new_discharged_patient->name) - 1);
            strncpy(new_discharged_patient->address, temp->address, sizeof(new_discharged_patient->address) - 1);
            strncpy(new_discharged_patient->contact_number, temp->contact_number, sizeof(new_discharged_patient->contact_number) - 1);
            new_discharged_patient->age = temp->age;
            strncpy(new_discharged_patient->sex, temp->sex, sizeof(new_discharged_patient->sex) - 1);
            strncpy(new_discharged_patient->blood_group, temp->blood_group, sizeof(new_discharged_patient->blood_group) - 1);
            strncpy(new_discharged_patient->disease, temp->disease, sizeof(new_discharged_patient->disease) - 1);
            new_discharged_patient->room_number = temp->room_number;
            new_discharged_patient->bill = temp->bill;
            new_discharged_patient->admission_time = temp->admission_time;
            time(&new_discharged_patient->discharge_time);
            new_discharged_patient->next = discharged_patient_list;
            discharged_patient_list = new_discharged_patient;

            if (prev == NULL) {
                admitted_patient_list = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Patient discharged successfully.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Patient with ID %d not found.\n", patient_id);
}

// List discharged patients
void list_discharged_patients() {
    struct DischargedPatient* temp = discharged_patient_list;
    if (temp == NULL) {
        printf("No discharged patients.\n");
        return;
    }
    printf("\n--- List of Discharged Patients ---\n");
    while (temp != NULL) {
        const char* room_type;
        if (temp->room_number >= 100 && temp->room_number < 200) room_type = "General";
        else if (temp->room_number >= 200 && temp->room_number < 300) room_type = "Semi-private";
        else if (temp->room_number >= 300 && temp->room_number < 400) room_type = "Private";
        else room_type = "Unknown";
        printf("Patient ID: %d\n", temp->id);
        printf("Name: %s\n", temp->name);
        printf("Address: %s\n", temp->address);
        printf("Disease: %s\n", temp->disease);
        printf("Room Number: %d (%s Room)\n", temp->room_number, room_type);
        printf("Admission Time: %s", ctime(&temp->admission_time));
        printf("Discharge Time: %s", ctime(&temp->discharge_time));
        printf("Total Bill: %.2f\n\n", temp->bill);
        temp = temp->next;
    }
}

// Add multiple doctors
void add_doctors() {
    int num_doctors;
    printf("\nHow many doctors do you want to add? : ");
    if (scanf("%d", &num_doctors) != 1) {
        printf("Invalid number of doctors.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    
    for (int i = 0; i < num_doctors; i++) {
        struct Doctor* new_doctor = (struct Doctor*)malloc(sizeof(struct Doctor));
        if (new_doctor == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }

        printf("\n--- Adding Doctor %d ---\n", i + 1);
        printf("Enter Doctor ID: ");
        if (scanf("%d", &new_doctor->id) != 1) {
            printf("Invalid Doctor ID.\n");
            free(new_doctor);
            clear_input_buffer();
            return;
        }
        clear_input_buffer();

        // Check for duplicate doctor ID
        struct Doctor* temp = doctor_list;
        while (temp != NULL) {
            if (temp->id == new_doctor->id) {
                printf("Doctor ID %d already exists.\n", new_doctor->id);
                free(new_doctor);
                return;
            }
            temp = temp->next;
        }

        printf("Enter Doctor Name: ");
        if (fgets(new_doctor->name, sizeof(new_doctor->name), stdin) == NULL) {
            printf("Error reading doctor name.\n");
            free(new_doctor);
            return;
        }
        new_doctor->name[strcspn(new_doctor->name, "\n")] = '\0';

        printf("Enter Specialty: ");
        if (fgets(new_doctor->specialty, sizeof(new_doctor->specialty), stdin) == NULL) {
            printf("Error reading specialty.\n");
            free(new_doctor);
            return;
        }
        new_doctor->specialty[strcspn(new_doctor->specialty, "\n")] = '\0';

        printf("Enter Available Time: ");
        if (fgets(new_doctor->available_time, sizeof(new_doctor->available_time), stdin) == NULL) {
            printf("Error reading available time.\n");
            free(new_doctor);
            return;
        }
        new_doctor->available_time[strcspn(new_doctor->available_time, "\n")] = '\0';

        printf("Enter Consultation Fee: ");
        if (scanf("%f", &new_doctor->consultation_fee) != 1) {
            printf("Invalid consultation fee.\n");
            free(new_doctor);
            clear_input_buffer();
            return;
        }
        clear_input_buffer();

        printf("Enter Doctor's Phone Number: ");
        if (fgets(new_doctor->phone_number, sizeof(new_doctor->phone_number), stdin) == NULL) {
            printf("Error reading phone number.\n");
            free(new_doctor);
            return;
        }
        new_doctor->phone_number[strcspn(new_doctor->phone_number, "\n")] = '\0';

        printf("Enter Doctor's Cabin Number: ");
        if (scanf("%d", &new_doctor->cabin_number) != 1) {
            printf("Invalid cabin number.\n");
            free(new_doctor);
            clear_input_buffer();
            return;
        }
        clear_input_buffer();

        new_doctor->next = doctor_list;
        doctor_list = new_doctor;
        printf("\nDoctor added successfully!\n");
    }
    printf("\nAll doctors have been added successfully!\n");
    printf("Press Enter to continue...\n");
    getchar();
}

// List admitted patients
void list_admitted_patients() {
    struct Patient* temp = admitted_patient_list;
    if (temp == NULL) {
        printf("No admitted patients.\n");
        return;
    }
    printf("\n--- List of Admitted Patients ---\n");
    while (temp != NULL) {
        const char* room_type;
        if (temp->room_number >= 100 && temp->room_number < 200) room_type = "General";
        else if (temp->room_number >= 200 && temp->room_number < 300) room_type = "Semi-private";
        else if (temp->room_number >= 300 && temp->room_number < 400) room_type = "Private";
        else room_type = "Unknown";
        printf("Patient ID: %d\n", temp->id);
        printf("Name: %s\n", temp->name);
        printf("Address: %s\n", temp->address);
        printf("Disease: %s\n", temp->disease);
        printf("Room Number: %d (%s Room)\n", temp->room_number, room_type);
        printf("Doctor: %s\n", temp->doctor_name);
        printf("Admission Time: %s", ctime(&temp->admission_time));
        printf("Total Bill: %.2f\n\n", temp->bill);
        temp = temp->next;
    }
}

// List consultation-only patients
void list_consultation_patients() {
    struct Patient* temp = consultation_patient_list;
    if (temp == NULL) {
        printf("No consultation-only patients.\n");
        return;
    }
    printf("\n--- List of Consultation-Only Patients ---\n");
    while (temp != NULL) {
        printf("Patient ID: %d\n", temp->id);
        printf("Name: %s\n", temp->name);
        printf("Address: %s\n", temp->address);
        printf("Disease: %s\n", temp->disease);
        printf("Doctor: %s\n", temp->doctor_name);
        printf("Total Bill: %.2f\n\n", temp->bill);
        temp = temp->next;
    }
}

// List all doctors
void list_doctors() {
    struct Doctor* temp = doctor_list;
    if (temp == NULL) {
        printf("No doctors available.\n");
        return;
    }
    printf("\n--- List of Doctors ---\n");
    while (temp != NULL) {
        printf("Doctor ID: %d\n", temp->id);
        printf("Name: %s\n", temp->name);
        printf("Specialty: %s\n", temp->specialty);
        printf("Available Time: %s\n", temp->available_time);
        printf("Consultation Fee: %.2f\n", temp->consultation_fee);
        printf("Phone Number: %s\n", temp->phone_number);
        printf("Cabin Number: %d\n\n", temp->cabin_number);
        temp = temp->next;
    }
}

// Remove doctor by ID
void remove_doctor() {
    int doctor_id;
    printf("Enter the Doctor ID to remove: ");
    if (scanf("%d", &doctor_id) != 1) {
        printf("Invalid Doctor ID.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    struct Doctor* temp = doctor_list;
    struct Doctor* prev = NULL;
    while (temp != NULL) {
        if (temp->id == doctor_id) {
            // Check if doctor has any appointments
            struct Appointment* appt = appointment_list;
            while (appt != NULL) {
                if (appt->doctor_id == doctor_id) {
                    printf("Cannot remove doctor with ID %d as they have existing appointments.\n", doctor_id);
                    return;
                }
                appt = appt->next;
            }

            if (prev == NULL) {
                doctor_list = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Doctor with ID %d has been removed successfully.\n", doctor_id);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Doctor with ID %d not found.\n", doctor_id);
}

// Free all allocated memory before exiting
void free_memory() {
    // Free admitted patients
    struct Patient* pat_temp = admitted_patient_list;
    while (pat_temp != NULL) {
        struct Patient* next_pat = pat_temp->next;
        free(pat_temp);
        pat_temp = next_pat;
    }

    // Free consultation patients
    pat_temp = consultation_patient_list;
    while (pat_temp != NULL) {
        struct Patient* next_pat = pat_temp->next;
        free(pat_temp);
        pat_temp = next_pat;
    }

    // Free doctors
    struct Doctor* doc_temp = doctor_list;
    while (doc_temp != NULL) {
        struct Doctor* next_doc = doc_temp->next;
        free(doc_temp);
        doc_temp = next_doc;
    }

    // Free discharged patients
    struct DischargedPatient* dis_temp = discharged_patient_list;
    while (dis_temp != NULL) {
        struct DischargedPatient* next_dis = dis_temp->next;
        free(dis_temp);
        dis_temp = next_dis;
    }

    // Free appointments
    struct Appointment* appt_temp = appointment_list;
    while (appt_temp != NULL) {
        struct Appointment* next_appt = appt_temp->next;
        free(appt_temp);
        appt_temp = next_appt;
    }
}

// Main menu
void menu() {
    int choice;
    while (1) {
        printf("\n--- Hospital Management System ---\n\n");
        printf("1. Add New Patient\n");
        printf("2. List Admitted Patients\n");
        printf("3. List Consultation-Only Patients\n");
        printf("4. Add New Doctor\n");
        printf("5. List Doctors\n");
        printf("6. Discharge Patient\n");
        printf("7. List Discharged Patients\n");
        printf("8. Remove Doctor\n");
        printf("9. Book Appointment\n");
        printf("10. View Appointments\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: 
                add_new_patient(); 
                break;
            case 2: 
                list_admitted_patients(); 
                printf("Press Enter to continue...\n");
                getchar();
                break;
            case 3: 
                list_consultation_patients(); 
                printf("Press Enter to continue...\n");
                getchar();
                break;
            case 4: 
                add_doctors();
                break;
            case 5: 
                list_doctors(); 
                printf("Press Enter to continue...\n");
                getchar();
                break;
            case 6: 
                discharge_patient(); 
                printf("Press Enter to continue...\n");
                getchar();
                break;
            case 7: 
                list_discharged_patients(); 
                printf("Press Enter to continue...\n");
                getchar();
                break;
            case 8: 
                remove_doctor(); 
                printf("Press Enter to continue...\n");
                getchar();
                break;
            case 9: 
                book_appointment(); 
                break;
            case 10: 
                view_appointments(); 
                break;
            case 11: 
                free_memory();
                printf("Exiting program.\n");
                exit(0);
                break;
            default: 
                printf("Invalid choice! Try again.\n");
                printf("Press Enter to continue...\n");
                getchar();
        }
    }
}

int main() {
    // Doctor 1
    struct Doctor* doc1 = (struct Doctor*)malloc(sizeof(struct Doctor));
    if (doc1 == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    doc1->id = 102;
    strncpy(doc1->name, "Dr. Shireen Akhter", sizeof(doc1->name) - 1);
    strncpy(doc1->specialty, "Neurology", sizeof(doc1->specialty) - 1);
    strncpy(doc1->available_time, "1PM - 4PM", sizeof(doc1->available_time) - 1);
    doc1->consultation_fee = 1000.0;
    strncpy(doc1->phone_number, "01742638929", sizeof(doc1->phone_number) - 1);
    doc1->cabin_number = 202;

    // Doctor 2
    struct Doctor* doc2 = (struct Doctor*)malloc(sizeof(struct Doctor));
    if (doc2 == NULL) {
        printf("Memory allocation failed.\n");
        free(doc1);
        doctor_list = NULL;
        return 1;
    }
    doc2->id = 103;
    strncpy(doc2->name, "Dr. Faria Islam", sizeof(doc2->name) - 1);
    strncpy(doc2->specialty, "Orthopedics", sizeof(doc2->specialty) - 1);
    strncpy(doc2->available_time, "2PM - 5PM", sizeof(doc2->available_time) - 1);
    doc2->consultation_fee = 900.0;
    strncpy(doc2->phone_number, "013458929", sizeof(doc2->phone_number) - 1);
    doc2->cabin_number = 402;

    // Doctor 3
    struct Doctor* doc3 = (struct Doctor*)malloc(sizeof(struct Doctor));
    if (doc3 == NULL) {
        printf("Memory allocation failed.\n");
        free(doc1);
        free(doc2);
        doctor_list = NULL;
        return 1;
    }
    doc3->id = 104;
    strncpy(doc3->name, "Dr. Fuad Khan", sizeof(doc3->name) - 1);
    strncpy(doc3->specialty, "Dermatology", sizeof(doc3->specialty) - 1);
    strncpy(doc3->available_time, "11AM - 4PM", sizeof(doc3->available_time) - 1);
    doc3->consultation_fee = 600.0;
    strncpy(doc3->phone_number, "01842638929", sizeof(doc3->phone_number) - 1);
    doc3->cabin_number = 602;

    // Doctor 4
    struct Doctor* doc4 = (struct Doctor*)malloc(sizeof(struct Doctor));
    if (doc4 == NULL) {
        printf("Memory allocation failed.\n");
        free(doc1);
        free(doc2);
        free(doc3);
        doctor_list = NULL;
        return 1;
    }
    doc4->id = 105;
    strncpy(doc4->name, "Dr. Selina Parvin", sizeof(doc4->name) - 1);
    strncpy(doc4->specialty, "Gynecology", sizeof(doc4->specialty) - 1);
    strncpy(doc4->available_time, "10AM - 1PM", sizeof(doc4->available_time) - 1);
    doc4->consultation_fee = 1000.0;
    strncpy(doc4->phone_number, "0134638929", sizeof(doc4->phone_number) - 1);
    doc4->cabin_number = 302;

    // Doctor 5
    struct Doctor* doc5 = (struct Doctor*)malloc(sizeof(struct Doctor));
    if (doc5 == NULL) {
        printf("Memory allocation failed.\n");
        free(doc1);
        free(doc2);
        free(doc3);
        free(doc4);
        doctor_list = NULL;
        return 1;
    }
    doc5->id = 106;
    strncpy(doc5->name, "Dr. Razzak Kabir", sizeof(doc5->name) - 1);
    strncpy(doc5->specialty, "Psychiatry", sizeof(doc5->specialty) - 1);
    strncpy(doc5->available_time, "12PM - 4PM", sizeof(doc5->available_time) - 1);
    doc5->consultation_fee = 1500.0;
    strncpy(doc5->phone_number, "0174008929", sizeof(doc5->phone_number) - 1);
    doc5->cabin_number = 210;

    // Doctor 6
    struct Doctor* doc6 = (struct Doctor*)malloc(sizeof(struct Doctor));
    if (doc6 == NULL) {
        printf("Memory allocation failed.\n");
        free(doc1);
        free(doc2);
        free(doc3);
        free(doc4);
        free(doc5);
        doctor_list = NULL;
        return 1;
    }
    doc6->id = 107;
    strncpy(doc6->name, "Dr. Sarfraz Majumdar", sizeof(doc6->name) - 1);
    strncpy(doc6->specialty, "Gastroenterology", sizeof(doc6->specialty) - 1);
    strncpy(doc6->available_time, "3PM - 8PM", sizeof(doc6->available_time) - 1);
    doc6->consultation_fee = 1000.0;
    strncpy(doc6->phone_number, "0194263829", sizeof(doc6->phone_number) - 1);
    doc6->cabin_number = 412;

    // Doctor 7
    struct Doctor* doc7 = (struct Doctor*)malloc(sizeof(struct Doctor));
    if (doc7 == NULL) {
        printf("Memory allocation failed.\n");
        free(doc1);
        free(doc2);
        free(doc3);
        free(doc4);
        free(doc5);
        free(doc6);
        doctor_list = NULL;
        return 1;
    }
    doc7->id = 123;
    strncpy(doc7->name, "Dr. S Bevor Rhman", sizeof(doc7->name) - 1);
    strncpy(doc7->specialty, "Cardiologist", sizeof(doc7->specialty) - 1);
    strncpy(doc7->available_time, "9AM - 4PM", sizeof(doc7->available_time) - 1);
    doc7->consultation_fee = 1000.0;
    strncpy(doc7->phone_number, "0174263856", sizeof(doc7->phone_number) - 1);
    doc7->cabin_number = 705;

    // Doctor 8
    struct Doctor* doc8 = (struct Doctor*)malloc(sizeof(struct Doctor));
    if (doc8 == NULL) {
        printf("Memory allocation failed.\n");
        free(doc1);
        free(doc2);
        free(doc3);
        free(doc4);
        free(doc5);
        free(doc6);
        free(doc7);
        doctor_list = NULL;
        return 1;
    }
    doc8->id = 109;
    strncpy(doc8->name, "Dr. Nandinii Khan", sizeof(doc8->name) - 1);
    strncpy(doc8->specialty, "Cardiologist", sizeof(doc8->specialty) - 1);
    strncpy(doc8->available_time, "10AM - 5PM", sizeof(doc8->available_time) - 1);
    doc8->consultation_fee = 1200.0;
    strncpy(doc8->phone_number, "0134593728", sizeof(doc8->phone_number) - 1);
    doc8->cabin_number = 806;

    // Doctor 9
    struct Doctor* doc9 = (struct Doctor*)malloc(sizeof(struct Doctor));
    if (doc9 == NULL) {
        printf("Memory allocation failed.\n");
        free(doc1);
        free(doc2);
        free(doc3);
        free(doc4);
        free(doc5);
        free(doc6);
        free(doc7);
        free(doc8);
        doctor_list = NULL;
        return 1;
    }
    doc9->id = 110;
    strncpy(doc9->name, "Dr. Subhan Sarkar", sizeof(doc9->name) - 1);
    strncpy(doc9->specialty, "Dermatologist", sizeof(doc9->specialty) - 1);
    strncpy(doc9->available_time, "11AM - 6PM", sizeof(doc9->available_time) - 1);
    doc9->consultation_fee = 1500.0;
    strncpy(doc9->phone_number, "0194365891", sizeof(doc9->phone_number) - 1);
    doc9->cabin_number = 909;

    // Doctor 10
    struct Doctor* doc10 = (struct Doctor*)malloc(sizeof(struct Doctor));
    if (doc10 == NULL) {
        printf("Memory allocation failed.\n");
        free(doc1);
        free(doc2);
        free(doc3);
        free(doc4);
        free(doc5);
        free(doc6);
        free(doc7);
        free(doc8);
        free(doc9);
        doctor_list = NULL;
        return 1;
    }
    doc10->id = 111;
    strncpy(doc10->name, "Dr. Rina Jahan", sizeof(doc10->name) - 1);
    strncpy(doc10->specialty, "Gynecology", sizeof(doc10->specialty) - 1);
    strncpy(doc10->available_time, "9AM - 12PM", sizeof(doc10->available_time) - 1);
    doc10->consultation_fee = 1100.0;
    strncpy(doc10->phone_number, "0179267845", sizeof(doc10->phone_number) - 1);
    doc10->cabin_number = 120;

    // Link all doctors
    doc1->next = doc2;
    doc2->next = doc3;
    doc3->next = doc4;
    doc4->next = doc5;
    doc5->next = doc6;
    doc6->next = doc7;
    doc7->next = doc8;
    doc8->next = doc9;
    doc9->next = doc10;
    doc10->next = NULL;

    // Set the head of doctor list
    doctor_list = doc1;

    // Launch menu
    menu();

    // Free memory before exiting (unreachable due to menu loop)
    free_memory();
    return 0;
}