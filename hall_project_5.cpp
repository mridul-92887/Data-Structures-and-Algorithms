#include <bits/stdc++.h>
using namespace std;

// Define structures for all entities
struct Student {
    string studentID;
    string studentName;
    struct Student* next;
};

struct Seat {
    string seatNumber;
    bool isOccupied;
    struct Student* student;
    struct Seat* next;
};

struct Room {
    string roomNumber;
    struct Seat* seats;
    struct Room* next;
};

struct Floor {
    string floorNumber;
    struct Room* rooms;
    int roomCount; // Track the number of rooms in this floor
    struct Floor* next;
};

struct Building {
    string buildingName;
    struct Floor* floors;
    struct Building* next;
};

struct Hall {
    string hallName;
    struct Building* buildings;
    struct Hall* next;
};

// Global pointers for the head of the linked lists
struct Hall* hallList = nullptr;
struct Student* studentList = nullptr;

// Function to add a hall
void addHall(string hallName) {
    struct Hall* newHall = new Hall();
    newHall->hallName = hallName;
    newHall->buildings = nullptr;
    newHall->next = hallList;
    hallList = newHall;
    cout << "Hall '" << hallName << "' added successfully!" << endl;
}

// Function to add a building to a hall
void addBuildingToHall(string hallName, string buildingName, int totalFloors, int roomsPerFloor, int seatsPerRoom) {
    struct Hall* ptr = hallList;
    while (ptr != nullptr && ptr->hallName != hallName) {
        ptr = ptr->next;
    }
    if (ptr == nullptr) {
        cout << "Hall not found!" << endl;
        return;
    }

    // Create the building
    struct Building* newBuilding = new Building();
    newBuilding->buildingName = buildingName;
    newBuilding->floors = nullptr;
    newBuilding->next = ptr->buildings;
    ptr->buildings = newBuilding;

    // Create floors, rooms, and seats for this building
    struct Floor* lastFloor = nullptr;
    for (int i = 0; i < totalFloors; ++i) {
        struct Floor* newFloor = new Floor();
        newFloor->floorNumber = to_string(i + 1);
        newFloor->rooms = nullptr;
        newFloor->roomCount = 0;
        newFloor->next = nullptr;
        
        if (lastFloor != nullptr) {
            lastFloor->next = newFloor;
        }
        lastFloor = newFloor;

        // Add rooms and seats to this floor
        for (int j = 0; j < roomsPerFloor; ++j) {
            struct Room* newRoom = new Room();
            newRoom->roomNumber = "R" + to_string(j + 1);
            newRoom->seats = nullptr;
            newRoom->next = nullptr;

            struct Seat* lastSeat = nullptr;
            for (int k = 0; k < seatsPerRoom; ++k) {
                struct Seat* newSeat = new Seat();
                newSeat->seatNumber = "S" + to_string(k + 1);
                newSeat->isOccupied = false;
                newSeat->student = nullptr;
                newSeat->next = nullptr;
                
                if (lastSeat != nullptr) {
                    lastSeat->next = newSeat;
                }
                lastSeat = newSeat;
                
                newRoom->seats = lastSeat; // Set the first seat
            }

            newFloor->rooms = newRoom; // Set the first room
        }
    }

    cout << "Building '" << buildingName << "' added to hall '" << hallName << "' with " << totalFloors << " floors!" << endl;
}

// Function to display available seats in each room of each floor of a building
void displayAvailableSeatsInBuilding(string buildingName) {
    struct Hall* hallPtr = hallList;
    while (hallPtr != nullptr) {
        struct Building* buildingPtr = hallPtr->buildings;
        while (buildingPtr != nullptr && buildingPtr->buildingName != buildingName) {
            buildingPtr = buildingPtr->next;
        }
        if (buildingPtr != nullptr) {
            struct Floor* floorPtr = buildingPtr->floors;
            cout << "Available Seats in Building '" << buildingName << "':" << endl;
            cout << "____________________" << endl;
            while (floorPtr != nullptr) {
                cout << "Floor Number: " << floorPtr->floorNumber << endl;
                struct Room* roomPtr = floorPtr->rooms;
                while (roomPtr != nullptr) {
                    cout << "  Room Number: " << roomPtr->roomNumber << endl;
                    struct Seat* seatPtr = roomPtr->seats;
                    while (seatPtr != nullptr) {
                        if (!seatPtr->isOccupied) {
                            cout << "    Seat Number: " << seatPtr->seatNumber << " (Available)" << endl;
                        }
                        seatPtr = seatPtr->next;
                    }
                    roomPtr = roomPtr->next;
                }
                floorPtr = floorPtr->next;
            }
            return;
        }
        hallPtr = hallPtr->next;
    }
    cout << "Building not found!" << endl;
}

// Function to allocate a seat to a student
void allocateSeatToStudent(string studentID, string buildingName, string floorNumber, string roomNumber, string seatNumber) {
    struct Student* studentPtr = studentList;
    while (studentPtr != nullptr && studentPtr->studentID != studentID) {
        studentPtr = studentPtr->next;
    }
    if (studentPtr == nullptr) {
        cout << "Student not found!" << endl;
        return;
    }

    struct Hall* hallPtr = hallList;
    while (hallPtr != nullptr) {
        struct Building* buildingPtr = hallPtr->buildings;
        while (buildingPtr != nullptr && buildingPtr->buildingName != buildingName) {
            buildingPtr = buildingPtr->next;
        }
        if (buildingPtr != nullptr) {
            struct Floor* floorPtr = buildingPtr->floors;
            while (floorPtr != nullptr && floorPtr->floorNumber != floorNumber) {
                floorPtr = floorPtr->next;
            }
            if (floorPtr != nullptr) {
                struct Room* roomPtr = floorPtr->rooms;
                while (roomPtr != nullptr && roomPtr->roomNumber != roomNumber) {
                    roomPtr = roomPtr->next;
                }
                if (roomPtr != nullptr) {
                    struct Seat* seatPtr = roomPtr->seats;
                    while (seatPtr != nullptr && seatPtr->seatNumber != seatNumber) {
                        seatPtr = seatPtr->next;
                    }
                    if (seatPtr != nullptr) {
                        if (seatPtr->isOccupied) {
                            cout << "Seat is already occupied!" << endl;
                        } else {
                            seatPtr->isOccupied = true;
                            seatPtr->student = studentPtr;
                            cout << "Seat '" << seatNumber << "' allocated to student '" << studentPtr->studentName << "' in room '" << roomNumber << "'!" << endl;
                        }
                        return;
                    }
                }
            }
        }
        hallPtr = hallPtr->next;
    }
    cout << "Seat not found!" << endl;
}

// Main Function
int main() {
    while (true) {
        cout << "\n===== Hall Management System =====\n";
        cout << "1. Add Hall\n";
        cout << "2. Add Building to Hall\n";
        cout << "3. Add Room, Floors, and Seats in a Building\n";
        cout << "4. Display Available Seats in Building\n";
        cout << "5. Add Rooms to a Floor\n";
        cout << "6. Add Student\n";
        cout << "7. Allocate Seat to Student\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(); // Flush the input buffer

        switch (choice) {
            case 1: {
                string hallName;
                cout << "Enter Hall Name: ";
                getline(cin, hallName);
                addHall(hallName);
                break;
            }
            case 2: {
                string hallName, buildingName;
                int totalFloors, roomsPerFloor, seatsPerRoom;
                cout << "Enter Hall Name: ";
                getline(cin, hallName);
                cout << "Enter Building Name: ";
                getline(cin, buildingName);
                cout << "Enter Total Number of Floors: ";
                cin >> totalFloors;
                cout << "Enter Number of Rooms per Floor: ";
                cin >> roomsPerFloor;
                cout << "Enter Number of Seats per Room: ";
                cin >> seatsPerRoom;
                cin.ignore();
                addBuildingToHall(hallName, buildingName, totalFloors, roomsPerFloor, seatsPerRoom);
                break;
            }
            case 3: {
                string buildingName;
                cout << "Enter Building Name: ";
                getline(cin, buildingName);
                displayAvailableSeatsInBuilding(buildingName);
                break;
            }
            case 4: {
                string studentID, buildingName, floorNumber, roomNumber, seatNumber;
                cout << "Enter Student ID: ";
                getline(cin, studentID);
                cout << "Enter Building Name: ";
                getline(cin, buildingName);
                cout << "Enter Floor Number: ";
                getline(cin, floorNumber);
                cout << "Enter Room Number: ";
                getline(cin, roomNumber);
                cout << "Enter Seat Number: ";
                getline(cin, seatNumber);
                allocateSeatToStudent(studentID, buildingName, floorNumber, roomNumber, seatNumber);
                break;
            }
            case 8: {
                cout << "Exiting program..." << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        }
    }
}
