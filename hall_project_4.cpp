#include <bits/stdc++.h>
using namespace std;

// Define structures for all entities
struct Seat {
    string seatNumber;
    bool isOccupied;
    string studentId; // Added to store student ID
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
void addBuildingToHall(string hallName, string buildingName, int totalFloors) {
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

    // Create floors for the building
    for (int i = 0; i < totalFloors; i++) {
        struct Floor* newFloor = new Floor();
        newFloor->floorNumber = to_string(i + 1);  // Floor numbering starts from 1
        newFloor->rooms = nullptr;
        newFloor->roomCount = 0;
        newFloor->next = newBuilding->floors;
        newBuilding->floors = newFloor;
    }

    cout << "Building '" << buildingName << "' with " << totalFloors << " floors added to hall '" << hallName << "'!" << endl;
}

// Function to add rooms to a floor along with seat numbers
void addRoomsToFloor(string buildingName, string floorNumber, vector<pair<string, int>> roomsAndSeats) {
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
                if (floorPtr->roomCount + roomsAndSeats.size() > 20) {
                    cout << "Error: This floor cannot accommodate more than 20 rooms. Try another floor!" << endl;
                    return;
                }

                // Adding rooms and seats to the floor
                for (auto &roomAndSeat : roomsAndSeats) {
                    struct Room* newRoom = new Room();
                    newRoom->roomNumber = roomAndSeat.first;
                    newRoom->seats = nullptr;

                    // Add seats to the room
                    for (int i = 1; i <= roomAndSeat.second; i++) {
                        struct Seat* newSeat = new Seat();
                        newSeat->seatNumber = roomAndSeat.first + "S" + to_string(i);
                        newSeat->isOccupied = false;
                        newSeat->studentId = ""; // Initialize student ID as empty
                        newSeat->next = newRoom->seats;
                        newRoom->seats = newSeat;
                    }

                    newRoom->next = floorPtr->rooms;
                    floorPtr->rooms = newRoom;
                    floorPtr->roomCount++;
                }

                cout << "Rooms with seats added to Floor '" << floorNumber << "' in Building '" << buildingName << "'!" << endl;
                return;
            }
        }
        hallPtr = hallPtr->next;
    }
    cout << "Building or floor not found!" << endl;
}

// Function to assign a student to a seat (mark as occupied)
void assignStudentToSeat(string buildingName, string roomNumber, string seatNumber, string studentId) {
    struct Hall* hallPtr = hallList;
    while (hallPtr != nullptr) {
        struct Building* buildingPtr = hallPtr->buildings;
        while (buildingPtr != nullptr && buildingPtr->buildingName != buildingName) {
            buildingPtr = buildingPtr->next;
        }
        if (buildingPtr != nullptr) {
            struct Floor* floorPtr = buildingPtr->floors;
            while (floorPtr != nullptr) {
                struct Room* roomPtr = floorPtr->rooms;
                while (roomPtr != nullptr && roomPtr->roomNumber != roomNumber) {
                    roomPtr = roomPtr->next;
                }
                if (roomPtr != nullptr) {
                    struct Seat* seatPtr = roomPtr->seats;
                    while (seatPtr != nullptr) {
                        if (seatPtr->seatNumber == seatNumber) {
                            if (seatPtr->isOccupied) {
                                cout << "Error: Seat is already occupied!" << endl;
                                return;
                            } else {
                                seatPtr->isOccupied = true;
                                seatPtr->studentId = studentId; // Assign student ID
                                cout << "Student with ID '" << studentId << "' assigned to Seat " << seatNumber << " in Room " << roomNumber << "!" << endl;
                                return;
                            }
                        }
                        seatPtr = seatPtr->next;
                    }
                }
                floorPtr = floorPtr->next;
            }
        }
        hallPtr = hallPtr->next;
    }
    cout << "Building or Room not found!" << endl;
}

// Function to display booked seats in a building
void displayBookedSeatsInBuilding(string buildingName) {
    struct Hall* hallPtr = hallList;
    while (hallPtr != nullptr) {
        struct Building* buildingPtr = hallPtr->buildings;
        while (buildingPtr != nullptr && buildingPtr->buildingName != buildingName) {
            buildingPtr = buildingPtr->next;
        }
        if (buildingPtr != nullptr) {
            struct Floor* floorPtr = buildingPtr->floors;
            cout << "Booked Seats in Building '" << buildingName << "':" << endl;
            while (floorPtr != nullptr) {
                cout << "Floor Number: " << floorPtr->floorNumber << endl;
                struct Room* roomPtr = floorPtr->rooms;
                while (roomPtr != nullptr) {
                    cout << "  Room Number: " << roomPtr->roomNumber << endl;
                    struct Seat* seatPtr = roomPtr->seats;
                    while (seatPtr != nullptr) {
                        if (seatPtr->isOccupied) {
                            cout << "    Seat Number: " << seatPtr->seatNumber << " (Booked by Student ID: " << seatPtr->studentId << ")" << endl;
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

// Function to search for a student by ID and display their details
void searchStudentById(string studentId) {
    struct Hall* hallPtr = hallList;
    while (hallPtr != nullptr) {
        struct Building* buildingPtr = hallPtr->buildings;
        while (buildingPtr != nullptr) {
            struct Floor* floorPtr = buildingPtr->floors;
            while (floorPtr != nullptr) {
                struct Room* roomPtr = floorPtr->rooms;
                while (roomPtr != nullptr) {
                    struct Seat* seatPtr = roomPtr->seats;
                    while (seatPtr != nullptr) {
                        if (seatPtr->isOccupied && seatPtr->studentId == studentId) {
                            cout << "Student found!" << endl;
                            cout << "  Student ID: " << studentId << endl;
                            cout << "  Building: " << buildingPtr->buildingName << endl;
                            cout << "  Floor: " << floorPtr->floorNumber << endl;
                            cout << "  Room: " << roomPtr->roomNumber << endl;
                            cout << "  Seat: " << seatPtr->seatNumber << endl;
                            return;
                        }
                        seatPtr = seatPtr->next;
                    }
                    roomPtr = roomPtr->next;
                }
                floorPtr = floorPtr->next;
            }
            buildingPtr = buildingPtr->next;
        }
        hallPtr = hallPtr->next;
    }
    cout << "Student with ID '" << studentId << "' not found!" << endl;
}

// Function to save data to a file
void saveDataToFile(const string& filename) {
    ofstream file(filename);

    if (!file) {
        cout << "Error: Could not open file!" << endl;
        return;
    }

    struct Hall* hallPtr = hallList;
    while (hallPtr != nullptr) {
        file << "Hall: " << hallPtr->hallName << endl;
        struct Building* buildingPtr = hallPtr->buildings;
        while (buildingPtr != nullptr) {
            file << "  Building: " << buildingPtr->buildingName << endl;
            struct Floor* floorPtr = buildingPtr->floors;
            while (floorPtr != nullptr) {
                file << "    Floor: " << floorPtr->floorNumber << endl;
                struct Room* roomPtr = floorPtr->rooms;
                while (roomPtr != nullptr) {
                    file << "      Room: " << roomPtr->roomNumber << endl;
                    struct Seat* seatPtr = roomPtr->seats;
                    while (seatPtr != nullptr) {
                        file << "        Seat: " << seatPtr->seatNumber
                             << " (Occupied: " << (seatPtr->isOccupied ? "Yes" : "No") << ")"
                             << " (Student ID: " << (seatPtr->isOccupied ? seatPtr->studentId : "None") << ")" << endl;
                        seatPtr = seatPtr->next;
                    }
                    roomPtr = roomPtr->next;
                }
                floorPtr = floorPtr->next;
            }
            buildingPtr = buildingPtr->next;
        }
        hallPtr = hallPtr->next;
    }

    cout << "Data saved to file successfully!" << endl;
}

// Function to display available seats in a building
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

// Function to delete all data
void deleteAllData() {
    struct Hall* hallPtr = hallList;
    while (hallPtr != nullptr) {
        struct Building* buildingPtr = hallPtr->buildings;
        while (buildingPtr != nullptr) {
            struct Floor* floorPtr = buildingPtr->floors;
            while (floorPtr != nullptr) {
                struct Room* roomPtr = floorPtr->rooms;
                while (roomPtr != nullptr) {
                    struct Seat* seatPtr = roomPtr->seats;
                    while (seatPtr != nullptr) {
                        struct Seat* tempSeat = seatPtr;
                        seatPtr = seatPtr->next;
                        delete tempSeat;
                    }
                    struct Room* tempRoom = roomPtr;
                    roomPtr = roomPtr->next;
                    delete tempRoom;
                }
                struct Floor* tempFloor = floorPtr;
                floorPtr = floorPtr->next;
                delete tempFloor;
            }
            struct Building* tempBuilding = buildingPtr;
            buildingPtr = buildingPtr->next;
            delete tempBuilding;
        }
        struct Hall* tempHall = hallPtr;
        hallPtr = hallPtr->next;
        delete tempHall;
    }
    hallList = nullptr; // Reset the global pointer
    cout << "All data deleted successfully!" << endl;
}

// Main Function with Switch
int main() {
    int choice = 0;
    while (choice != 10) {
        cout << "\n===== Hall Management System =====\n";
        cout << "1. Add Hall\n";
        cout << "2. Add Building to Hall\n";
        cout << "3. Add Rooms to Floor\n";
        cout << "4. Display Available Seats in a Building\n";
        cout << "5. Assign Student to Seat\n";
        cout << "6. Save Data to File\n";
        cout << "7. Display Booked Seats in a Building\n";
        cout << "8. Search Student by ID\n";
        cout << "9. Delete All Data\n";
        cout << "10. Exit\n";
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
                int totalFloors;
                cout << "Enter Hall Name: ";
                cin >> hallName;
                cout << "Enter Building Name: ";
                cin >> buildingName;
                cout << "Enter Total Floors: ";
                cin >> totalFloors;
                addBuildingToHall(hallName, buildingName, totalFloors);
                break;
            }
            case 3: {
                string buildingName, floorNumber;
                int numRooms;
                vector<pair<string, int>> roomsAndSeats;
                cout << "Enter Building Name: ";
                cin >> buildingName;
                cout << "Enter Floor Number: ";
                cin >> floorNumber;
                cout << "Enter Number of Rooms: ";
                cin >> numRooms;

                for (int i = 0; i < numRooms; i++) {
                    string roomNumber;
                    int seatCount;
                    cout << "Enter Room " << i + 1 << " Number: ";
                    cin >> roomNumber;
                    cout << "Enter Number of Seats in Room " << roomNumber << ": ";
                    cin >> seatCount;
                    roomsAndSeats.push_back(make_pair(roomNumber, seatCount));
                }

                addRoomsToFloor(buildingName, floorNumber, roomsAndSeats);
                break;
            }
            case 4: {
                string buildingName;
                cout << "Enter Building Name: ";
                cin >> buildingName;
                displayAvailableSeatsInBuilding(buildingName);
                break;
            }
            case 5: {
                string buildingName, roomNumber, seatNumber, studentId;
                cout << "Enter Building Name: ";
                cin >> buildingName;
                cout << "Enter Room Number: ";
                cin >> roomNumber;
                cout << "Enter Seat Number: ";
                cin >> seatNumber;
                cout << "Enter Student ID: ";
                cin >> studentId;
                assignStudentToSeat(buildingName, roomNumber, seatNumber, studentId);
                break;
            }
            case 6: {
                string filename;
                cout << "Enter filename to save data (e.g., data.txt): ";
                cin >> filename;
                saveDataToFile(filename);
                break;
            }
            case 7: {
                string buildingName;
                cout << "Enter Building Name: ";
                cin >> buildingName;
                displayBookedSeatsInBuilding(buildingName);
                break;
            }
            case 8: {
                string studentId;
                cout << "Enter Student ID: ";
                cin >> studentId;
                searchStudentById(studentId);
                break;
            }
            case 9: {
                deleteAllData();
                break;
            }
            case 10:
                cout << "Exiting the system..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}