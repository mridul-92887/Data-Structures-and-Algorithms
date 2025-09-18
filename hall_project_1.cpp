#include <bits/stdc++.h>
using namespace std;

// Define structures for all entities
struct Seat {
    string seatNumber;
    bool isOccupied;
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
struct Building* buildingList = nullptr;

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

// Main Function
int main() {
    while (true) {
        cout << "\n===== Hall Management System =====\n";
        cout << "1. Add Hall\n";
        cout << "2. Add Building to Hall\n";
        cout << "3. Add Rooms to Floor\n";
        cout << "4. Display Available Seats in Building\n";
        cout << "5. Exit\n";
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
                int totalFloors;
                cout << "Enter Hall Name: ";
                getline(cin, hallName);
                cout << "Enter Building Name: ";
                getline(cin, buildingName);
                cout << "Enter Total Number of Floors: ";
                cin >> totalFloors;
                addBuildingToHall(hallName, buildingName, totalFloors);
                break;
            }
            case 3: {
                string buildingName, floorNumber;
                int roomCount;
                cout << "Enter Building Name: ";
                getline(cin, buildingName);
                cout << "Enter Floor Number: ";
                getline(cin, floorNumber);
                cout << "Enter Number of Rooms to Add: ";
                cin >> roomCount;
                vector<pair<string, int>> roomsAndSeats(roomCount);
                cout << "Enter Room Numbers and Number of Seats for each room: " << endl;
                for (int i = 0; i < roomCount; i++) {
                    cout << "Room " << i + 1 << " Number: ";
                    cin >> roomsAndSeats[i].first;
                    cout << "Number of Seats for Room " << roomsAndSeats[i].first << ": ";
                    cin >> roomsAndSeats[i].second;
                }
                addRoomsToFloor(buildingName, floorNumber, roomsAndSeats);
                break;
            }
            case 4: {
                string buildingName;
                cout << "Enter Building Name: ";
                getline(cin, buildingName);
                displayAvailableSeatsInBuilding(buildingName);
                break;
            }
            case 5: {
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
