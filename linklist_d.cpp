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


// Hall Management Functions
void addHall(string hallName) {
    struct Hall* newHall = new Hall();
    newHall->hallName = hallName;
    newHall->buildings = nullptr;
    newHall->next = hallList;
    hallList = newHall;
    cout << "Hall '" << hallName << "' added successfully!" << endl;
}

void displayHalls() {
    struct Hall* ptr = hallList;
    cout << "Halls:" << endl;
    cout << "____________________" << endl;
    while (ptr != nullptr) {
        cout << "Hall Name: " << ptr->hallName << endl;
        ptr = ptr->next;
    }
}

// Building Management Functions
void addBuildingToHall(string hallName, string buildingName) {
    struct Hall* ptr = hallList;
    while (ptr != nullptr && ptr->hallName != hallName) {
        ptr = ptr->next;
    }
    if (ptr == nullptr) {
        cout << "Hall not found!" << endl;
        return;
    }
    struct Building* newBuilding = new Building();
    newBuilding->buildingName = buildingName;
    newBuilding->floors = nullptr;
    newBuilding->next = ptr->buildings;
    ptr->buildings = newBuilding;
    cout << "Building '" << buildingName << "' added to hall '" << hallName << "' successfully!" << endl;
}

void displayBuildingsInHall(string hallName) {
    struct Hall* ptr = hallList;
    while (ptr != nullptr && ptr->hallName != hallName) {
        ptr = ptr->next;
    }
    if (ptr == nullptr) {
        cout << "Hall not found!" << endl;
        return;
    }
    struct Building* buildingPtr = ptr->buildings;
    cout << "Buildings in Hall '" << hallName << "':" << endl;
    cout << "____________________" << endl;
    while (buildingPtr != nullptr) {
        cout << "Building Name: " << buildingPtr->buildingName << endl;
        buildingPtr = buildingPtr->next;
    }
}

// Floor Management Functions
void addFloorToBuilding(string buildingName, string floorNumber) {
    struct Hall* hallPtr = hallList;
    while (hallPtr != nullptr) {
        struct Building* buildingPtr = hallPtr->buildings;
        while (buildingPtr != nullptr && buildingPtr->buildingName != buildingName) {
            buildingPtr = buildingPtr->next;
        }
        if (buildingPtr != nullptr) {
            struct Floor* newFloor = new Floor();
            newFloor->floorNumber = floorNumber;
            newFloor->rooms = nullptr;
            newFloor->next = buildingPtr->floors;
            buildingPtr->floors = newFloor;
            cout << "Floor '" << floorNumber << "' added to building '" << buildingName << "' successfully!" << endl;
            return;
        }
        hallPtr = hallPtr->next;
    }
    cout << "Building not found!" << endl;
}

void displayFloorsInBuilding(string buildingName) {
    struct Hall* hallPtr = hallList;
    while (hallPtr != nullptr) {
        struct Building* buildingPtr = hallPtr->buildings;
        while (buildingPtr != nullptr && buildingPtr->buildingName != buildingName) {
            buildingPtr = buildingPtr->next;
        }
        if (buildingPtr != nullptr) {
            struct Floor* floorPtr = buildingPtr->floors;
            cout << "Floors in Building '" << buildingName << "':" << endl;
            cout << "____________________" << endl;
            while (floorPtr != nullptr) {
                cout << "Floor Number: " << floorPtr->floorNumber << endl;
                floorPtr = floorPtr->next;
            }
            return;
        }
        hallPtr = hallPtr->next;
    }
    cout << "Building not found!" << endl;
}

// Room Management Functions
void addRoomToFloor(string floorNumber, string roomNumber) {
    struct Hall* hallPtr = hallList;
    while (hallPtr != nullptr) {
        struct Building* buildingPtr = hallPtr->buildings;
        while (buildingPtr != nullptr) {
            struct Floor* floorPtr = buildingPtr->floors;
            while (floorPtr != nullptr && floorPtr->floorNumber != floorNumber) {
                floorPtr = floorPtr->next;
            }
            if (floorPtr != nullptr) {
                struct Room* newRoom = new Room();
                newRoom->roomNumber = roomNumber;
                newRoom->seats = nullptr;
                newRoom->next = floorPtr->rooms;
                floorPtr->rooms = newRoom;
                cout << "Room '" << roomNumber << "' added to floor '" << floorNumber << "' successfully!" << endl;
                return;
            }
            buildingPtr = buildingPtr->next;
        }
        hallPtr = hallPtr->next;
    }
    cout << "Floor not found!" << endl;
}

void displayRoomsInFloor(string floorNumber) {
    struct Hall* hallPtr = hallList;
    while (hallPtr != nullptr) {
        struct Building* buildingPtr = hallPtr->buildings;
        while (buildingPtr != nullptr) {
            struct Floor* floorPtr = buildingPtr->floors;
            while (floorPtr != nullptr && floorPtr->floorNumber != floorNumber) {
                floorPtr = floorPtr->next;
            }
            if (floorPtr != nullptr) {
                struct Room* roomPtr = floorPtr->rooms;
                cout << "Rooms in Floor '" << floorNumber << "':" << endl;
                cout << "____________________" << endl;
                while (roomPtr != nullptr) {
                    cout << "Room Number: " << roomPtr->roomNumber << endl;
                    roomPtr = roomPtr->next;
                }
                return;
            }
            buildingPtr = buildingPtr->next;
        }
        hallPtr = hallPtr->next;
    }
    cout << "Floor not found!" << endl;
}

// Seat Management Functions
void addSeatToRoom(string roomNumber, string seatNumber) {
    struct Hall* hallPtr = hallList;
    while (hallPtr != nullptr) {
        struct Building* buildingPtr = hallPtr->buildings;
        while (buildingPtr != nullptr) {
            struct Floor* floorPtr = buildingPtr->floors;
            while (floorPtr != nullptr) {
                struct Room* roomPtr = floorPtr->rooms;
                while (roomPtr != nullptr && roomPtr->roomNumber != roomNumber) {
                    roomPtr = roomPtr->next;
                }
                if (roomPtr != nullptr) {
                    struct Seat* newSeat = new Seat();
                    newSeat->seatNumber = seatNumber;
                    newSeat->isOccupied = false;
                    newSeat->student = nullptr;
                    newSeat->next = roomPtr->seats;
                    roomPtr->seats = newSeat;
                    cout << "Seat '" << seatNumber << "' added to room '" << roomNumber << "' successfully!" << endl;
                    return;
                }
                floorPtr = floorPtr->next;
            }
            buildingPtr = buildingPtr->next;
        }
        hallPtr = hallPtr->next;
    }
    cout << "Room not found!" << endl;
}

void displaySeatsInRoom(string roomNumber) {
    struct Hall* hallPtr = hallList;
    while (hallPtr != nullptr) {
        struct Building* buildingPtr = hallPtr->buildings;
        while (buildingPtr != nullptr) {
            struct Floor* floorPtr = buildingPtr->floors;
            while (floorPtr != nullptr) {
                struct Room* roomPtr = floorPtr->rooms;
                while (roomPtr != nullptr && roomPtr->roomNumber != roomNumber) {
                    roomPtr = roomPtr->next;
                }
                if (roomPtr != nullptr) {
                    struct Seat* seatPtr = roomPtr->seats;
                    cout << "Seats in Room '" << roomNumber << "':" << endl;
                    cout << "____________________" << endl;
                    while (seatPtr != nullptr) {
                        cout << "Seat Number: " << seatPtr->seatNumber << ", Occupied: " << (seatPtr->isOccupied ? "Yes" : "No") << endl;
                        seatPtr = seatPtr->next;
                    }
                    return;
                }
                floorPtr = floorPtr->next;
            }
            buildingPtr = buildingPtr->next;
        }
        hallPtr = hallPtr->next;
    }
    cout << "Room not found!" << endl;
}

// Student Management Functions
void addStudent(string studentID, string studentName) {
    struct Student* newStudent = new Student();
    newStudent->studentID = studentID;
    newStudent->studentName = studentName;
    newStudent->next = studentList;
    studentList = newStudent;
    cout << "Student '" << studentName << "' added successfully!" << endl;
}

void displayStudents() {
    struct Student* ptr = studentList;
    cout << "Students:" << endl;
    cout << "____________________" << endl;
    while (ptr != nullptr) {
        cout << "Student ID: " << ptr->studentID << ", Name: " << ptr->studentName << endl;
        ptr = ptr->next;
    }
}

// Seat Allocation Function
void allocateSeatToStudent(string studentID, string hallName, string buildingName, string floorNumber, string roomNumber) {
    struct Student* studentPtr = studentList;
    while (studentPtr != nullptr && studentPtr->studentID != studentID) {
        studentPtr = studentPtr->next;
    }
    if (studentPtr == nullptr) {
        cout << "Student not found!" << endl;
        return;
    }

    struct Hall* hallPtr = hallList;
    while (hallPtr != nullptr && hallPtr->hallName != hallName) {
        hallPtr = hallPtr->next;
    }
    if (hallPtr == nullptr) {
        cout << "Hall not found!" << endl;
        return;
    }

    struct Building* buildingPtr = hallPtr->buildings;
    while (buildingPtr != nullptr && buildingPtr->buildingName != buildingName) {
        buildingPtr = buildingPtr->next;
    }
    if (buildingPtr == nullptr) {
        cout << "Building not found!" << endl;
        return;
    }

    struct Floor* floorPtr = buildingPtr->floors;
    while (floorPtr != nullptr && floorPtr->floorNumber != floorNumber) {
        floorPtr = floorPtr->next;
    }
    if (floorPtr == nullptr) {
        cout << "Floor not found!" << endl;
        return;
    }

    struct Room* roomPtr = floorPtr->rooms;
    while (roomPtr != nullptr && roomPtr->roomNumber != roomNumber) {
        roomPtr = roomPtr->next;
    }
    if (roomPtr == nullptr) {
        cout << "Room not found!" << endl;
        return;
    }

    struct Seat* seatPtr = roomPtr->seats;
    while (seatPtr != nullptr && seatPtr->isOccupied) {
        seatPtr = seatPtr->next;
    }
    if (seatPtr == nullptr) {
        cout << "No available seats in room '" << roomNumber << "'!" << endl;
        return;
    }

    seatPtr->isOccupied = true;
    seatPtr->student = studentPtr;
    cout << "Seat allocated to student '" << studentPtr->studentName << "' in room '" << roomNumber << "'!" << endl;
}

// Main Function
int main() {
    while (true) {
        cout << "1. Add Hall" << endl;
        cout << "2. Add Building to Hall" << endl;
        cout << "3. Add Floor to Building" << endl;
        cout << "4. Add Room to Floor" << endl;
        cout << "5. Add Seat to Room" << endl;
        cout << "6. Add Student" << endl;
        cout << "7. Display Halls" << endl;
        cout << "8. Display Buildings in Hall" << endl;
        cout << "9. Display Floors in Building" << endl;
        cout << "10. Display Rooms in Floor" << endl;
        cout << "11. Display Seats in Room" << endl;
        cout << "12. Display Students" << endl;
        cout << "13. Allocate Seat to Student" << endl;
        cout << "14. Exit" << endl;
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string hallName;
                cout << "Enter Hall Name: ";
                cin >> hallName;
                addHall(hallName);
                break;
            }
            case 2: {
                string hallName, buildingName;
                cout << "Enter Hall Name: ";
                cin >> hallName;
                cout << "Enter Building Name: ";
                cin >> buildingName;
                addBuildingToHall(hallName, buildingName);
                break;
            }
            case 3: {
                string buildingName, floorNumber;
                cout << "Enter Building Name: ";
                cin >> buildingName;
                cout << "Enter Floor Number: ";
                cin >> floorNumber;
                addFloorToBuilding(buildingName, floorNumber);
                break;
            }
            case 4: {
                string floorNumber, roomNumber;
                cout << "Enter Floor Number: ";
                cin >> floorNumber;
                cout << "Enter Room Number: ";
                cin >> roomNumber;
                addRoomToFloor(floorNumber, roomNumber);
                break;
            }
            case 5: {
                string roomNumber, seatNumber;
                cout << "Enter Room Number: ";
                cin >> roomNumber;
                cout << "Enter Seat Number: ";
                cin >> seatNumber;
                addSeatToRoom(roomNumber, seatNumber);
                break;
            }
            case 6: {
                string studentID, studentName;
                cout << "Enter Student ID: ";
                cin >> studentID;
                cout << "Enter Student Name: ";
                cin >> studentName;
                addStudent(studentID, studentName);
                break;
            }
            case 7: {
                displayHalls();
                break;
            }
            case 8: {
                string hallName;
                cout << "Enter Hall Name: ";
                cin >> hallName;
                displayBuildingsInHall(hallName);
                break;
            }
            case 9: {
                string buildingName;
                cout << "Enter Building Name: ";
                cin >> buildingName;
                displayFloorsInBuilding(buildingName);
                break;
            }
            case 10: {
                string floorNumber;
                cout << "Enter Floor Number: ";
                cin >> floorNumber;
                displayRoomsInFloor(floorNumber);
                break;
            }
            case 11: {
                string roomNumber;
                cout << "Enter Room Number: ";
                cin >> roomNumber;
                displaySeatsInRoom(roomNumber);
                break;
            }
            case 12: {
                displayStudents();
                break;
            }
            case 13: {
                string studentID, hallName, buildingName, floorNumber, roomNumber;
                cout << "Enter Student ID: ";
                cin >> studentID;
                cout << "Enter Hall Name: ";
                cin >> hallName;
                cout << "Enter Building Name (optional, press Enter to skip): ";
                cin.ignore();
                getline(cin, buildingName);
                cout << "Enter Floor Number (optional, press Enter to skip): ";
                getline(cin, floorNumber);
                cout << "Enter Room Number (optional, press Enter to skip): ";
                getline(cin, roomNumber);
                allocateSeatToStudent(studentID, hallName, buildingName, floorNumber, roomNumber);
                break;
            }
            case 14: {
                cout << "Exiting..." << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        }
    }
    return 0;
}