#include <bits/stdc++.h>
using namespace std;

struct Student {
    string name;
    string id;
    string department;
    string bloodGroup;
    string phone;
    string email;
    string room;
    Student* next;
};

struct Action {
    string description;
    Action* next;
};

struct Room {
    string roomNo;
    int capacity;
    int occupied;
    Room* next;
};

Student* studentList = nullptr;
Action* actionStack = nullptr;
Room* roomList = nullptr;


const string ADMIN_EMAIL = "mridul_92887@gmail.com";
const string ADMIN_PASSWORD = "mridul+++";
const string CEO_EMAIL = "ceo@hostel.com";
const string CEO_PASSWORD = "ceo123";

struct WaitingStudent {
    string name;
    string id;
    string requestedRoom;
    WaitingStudent* next;
};

WaitingStudent* waitingQueueFront = nullptr;
WaitingStudent* waitingQueueRear = nullptr;


void pushAction(string action) {
    Action* newAction = new Action;
    newAction->description = action;
    newAction->next = actionStack;
    actionStack = newAction;
}

void enqueueWaitingStudent(string name, string id, string room) {
    WaitingStudent* newStudent = new WaitingStudent;
    newStudent->name = name;
    newStudent->id = id;
    newStudent->requestedRoom = room;
    newStudent->next = nullptr;

    if (waitingQueueRear == nullptr) {
        waitingQueueFront = waitingQueueRear = newStudent;
    } else {
        waitingQueueRear->next = newStudent;
        waitingQueueRear = newStudent;
    }
    pushAction("Added to waiting list: " + name + " (Room: " + room + ")");
}

void dequeueWaitingStudent() {
    if (waitingQueueFront == nullptr) return;

    WaitingStudent* temp = waitingQueueFront;
    waitingQueueFront = waitingQueueFront->next;

    if (waitingQueueFront == nullptr) {
        waitingQueueRear = nullptr;
    }
    delete temp;
}

void printAvailableRooms() {
    cout << "\n===== AVAILABLE ROOMS =====";
    cout << "\n" << left 
         << setw(10) << "ROOM" 
         << setw(15) << "OCCUPANCY" 
         << "AVAILABLE BEDS";
    cout << "\n" << setfill('-') << setw(40) << "-" << setfill(' ');
    
    Room* temp = roomList;
    while(temp != nullptr) {
        if(temp->occupied < temp->capacity) {
            string occupancy = to_string(temp->occupied) + "/" + to_string(temp->capacity);
            cout << "\n" << left 
                 << setw(10) << temp->roomNo 
                 << setw(15) << occupancy 
                 << (temp->capacity - temp->occupied);
        }
        temp = temp->next;
    }
    cout << "\n";
}


void printAllRooms() {
    cout << "\n===== ALL ROOMS =====";
    cout << "\n" << left 
         << setw(10) << "ROOM" 
         << setw(15) << "OCCUPANCY" 
         << "STATUS";
    cout << "\n" << setfill('-') << setw(40) << "-" << setfill(' ');
    
    Room* temp = roomList;
    while(temp != nullptr) {
        string occupancy = to_string(temp->occupied) + "/" + to_string(temp->capacity);
        string status = (temp->occupied < temp->capacity) ? "Available" : "FULL";
        cout << "\n" << left 
             << setw(10) << temp->roomNo 
             << setw(15) << occupancy 
             << status;
        temp = temp->next;
    }
    cout << "\n";
}

bool isRoomAvailable(string roomNo) {
    Room* temp = roomList;
    while(temp != nullptr) {
        if(temp->roomNo == roomNo && temp->occupied < temp->capacity) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}


bool roomExists(string roomNo) {
    Room* temp = roomList;
    while(temp != nullptr) {
        if(temp->roomNo == roomNo) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void ceoAddStudent() {
    Student* newStudent = new Student;
    
    cout << "\n===== ADD STUDENT (CEO OVERRIDE) =====";
    cout << "\nName: "; getline(cin, newStudent->name);
    cout << "ID: "; getline(cin, newStudent->id);
    cout << "Department: "; getline(cin, newStudent->department);
    cout << "Blood Group: "; getline(cin, newStudent->bloodGroup);
    cout << "Phone: "; getline(cin, newStudent->phone);
    cout << "Email: "; getline(cin, newStudent->email);
    

    printAvailableRooms();
    
    cout << "Room: "; getline(cin, newStudent->room);
    Room* room = roomList;
    while(room != nullptr && room->roomNo != newStudent->room) {
        room = room->next;
    }
    
    if(room != nullptr) {
        room->occupied++;
        cout << "\nAssigned to Room " << newStudent->room << "\n";
    } else {
        newStudent->room = "CEO-OVERRIDE";
        cout << "\nRoom not found - assigned special CEO-OVERRIDE status\n";
    }
    
    newStudent->next = studentList;
    studentList = newStudent;
    
    pushAction("CEO added student: " + newStudent->name);
    
    cout << "\nUpdated room availability:\n";
    printAvailableRooms();
    cout << "\nStudent added with CEO privileges!\n";
}

void ceoRemoveStudent() {
    cout << "\n===== REMOVE STUDENT (CEO OVERRIDE) =====";
    string id;
    cout << "\nEnter student ID to remove: ";
    getline(cin, id);
    
    Student* curr = studentList;
    Student* prev = nullptr;
    
    while(curr != nullptr && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }
    
    if(curr == nullptr) {
        cout << "Student not found!\n";
        return;
    }
    
    if(curr->room != "Not Allocated") {
        Room* room = roomList;
        while(room != nullptr && room->roomNo != curr->room) {
            room = room->next;
        }
        if(room != nullptr) room->occupied--;
    }
    
    if(prev == nullptr) {
        studentList = curr->next;
    } else {
        prev->next = curr->next;
    }
    
    pushAction("CEO removed student: " + curr->name);
    delete curr;
    cout << "Student forcibly removed!\n";
}
void forceRoomChanges() {
    cout << "\n===== FORCE ROOM REALLOCATION =====";
    string oldRoom, newRoom;
    printAvailableRooms();
    
    cout << "\nEnter CURRENT room number: ";
    getline(cin, oldRoom);
    cout << "Enter NEW room number: ";
    getline(cin, newRoom);
    
    Room* oldR = roomList;
    Room* newR = roomList;
    while(oldR != nullptr && oldR->roomNo != oldRoom) oldR = oldR->next;
    while(newR != nullptr && newR->roomNo != newRoom) newR = newR->next;
    
    if(oldR == nullptr || newR == nullptr) {
        cout << "Invalid room selection!\n";
        return;
    }
    
    int moved = 0;
    Student* s = studentList;
    while(s != nullptr) {
        if(s->room == oldRoom) {
            s->room = newRoom;
            moved++;
        }
        s = s->next;
    }
    
    oldR->occupied -= moved;
    newR->occupied += moved;
    
    pushAction("CEO forced room change: " + oldRoom + " to " + newRoom);
    cout << moved << " students moved from " << oldRoom << " to " << newRoom << "\n";
}

void viewAllLogs() {
    cout << "\n===== SYSTEM ACTION LOG =====";
    Action* temp = actionStack;
    while(temp != nullptr) {
        cout << "\n" << temp->description;
        temp = temp->next;
    }
    cout << "\n===========================\n";
}

void ceoMenu() {
    int choice;
    do {
        cout << "\n===== CEO CONTROL PANEL =====";
        cout << "\n1. Add Student (Override)";
        cout << "\n2. Remove Student (Override)";
        cout << "\n3. Force Room Changes";
        cout << "\n4. View All System Logs";
        cout << "\n5. Exit CEO Mode";
        cout << "\nEnter choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: ceoAddStudent(); break;
            case 2: ceoRemoveStudent(); break;
            case 3: forceRoomChanges(); break;
            case 4: viewAllLogs(); break;
            case 5: break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 6);
}

int authenticateUser() {
    string email, password;
    int attempts = 0;
    
    while(attempts < 3) {
        cout << "\n===== HOSTEL MANAGEMENT LOGIN =====";
        cout << "\nEmail: ";
        getline(cin, email);
        
        cout << "Password: ";
        password = "";
        char ch;
        while((ch = getchar()) != '\n') {
            password += ch;
        }
        
        if(email == ADMIN_EMAIL && password == ADMIN_PASSWORD) {
            cout << "\n\nAdmin login successful!\n";
            return 1;
        }
        else if(email == CEO_EMAIL && password == CEO_PASSWORD) {
            cout << "\n\nCEO login successful!\n";
            return 2;
        }
        else {
            attempts++;
            cout << "\n\nWrong email or password! Try again.\n";
            if(attempts < 3) {
                cout << "Press Enter to continue...";
                cin.ignore();
            }
        }
    }
    cout << "\nToo many failed attempts. Program exiting...\n";
    return 0;
}

void initializeRooms() {
    string rooms[] = {"101", "102", "103", "104", "105"};
    for(string roomNo : rooms) {
        Room* newRoom = new Room;
        newRoom->roomNo = roomNo;
        newRoom->capacity = 4;
        newRoom->occupied = 0;
        newRoom->next = roomList;
        roomList = newRoom;
    }
}

void printStudentDetails(Student* student) {
    cout << "\n===== STUDENT DETAILS =====";
    cout << "\nName: " << student->name;
    cout << "\nID: " << student->id;
    cout << "\nDepartment: " << student->department;
    cout << "\nBlood Group: " << student->bloodGroup;
    cout << "\nPhone: " << student->phone;
    cout << "\nEmail: " << student->email;
    cout << "\nRoom: " << student->room;
    cout << "\n==========================\n";
}

void showRecentActions() {
    if(actionStack == nullptr) {
        cout << "No recent actions!\n";
        return;
    }

    cout << "\n===== RECENT ACTIONS =====\n";
    Action* temp = actionStack;
    int count = 0;
    while(temp != nullptr && count < 5) {
        cout << "- " << temp->description << "\n";
        temp = temp->next;
        count++;
    }
}

void showWaitingList() {
    cout << "\n===== WAITING QUEUE (FIFO) =====";
    WaitingStudent* temp = waitingQueueFront;
    while (temp != nullptr) {
        cout << "\n" << temp->name << " (ID: " << temp->id 
             << ") - Waiting for: " << temp->requestedRoom;
        temp = temp->next;
    }
    cout << "\n==============================\n";
}

Room* findAvailableRoom() {
    Room* temp = roomList;
    while(temp != nullptr) {
        if(temp->occupied < temp->capacity) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void addStudent() {
    Student* newStudent = new Student;
    
    cout << "\nEnter student details:\n";
    cout << "Name: "; getline(cin, newStudent->name);
    cout << "ID: "; getline(cin, newStudent->id);
    cout << "Department: "; getline(cin, newStudent->department);
    cout << "Blood Group: "; getline(cin, newStudent->bloodGroup);
    cout << "Phone: "; getline(cin, newStudent->phone);
    cout << "Email: "; getline(cin, newStudent->email);
    
    printAvailableRooms();
    cout << "Enter room number (or leave blank for auto-allocation): ";
    string roomChoice;
    getline(cin, roomChoice);
    
    if(!roomChoice.empty()) {
        if(isRoomAvailable(roomChoice)) {
            newStudent->room = roomChoice;
            Room* temp = roomList;
            while(temp != nullptr) {
                if(temp->roomNo == roomChoice) {
                    temp->occupied++;
                    break;
                }
                temp = temp->next;
            }
            cout << "Assigned to Room " << roomChoice << "\n";
        } else {
            cout << "Room not available or invalid. Auto-assigning...\n";
            Room* availableRoom = findAvailableRoom();
            if(availableRoom != nullptr) {
                newStudent->room = availableRoom->roomNo;
                availableRoom->occupied++;
                cout << "Auto-assigned to Room " << availableRoom->roomNo << "\n";
            } else {
                newStudent->room = "Not Allocated";
                cout << "No rooms available currently\n";
            }
        }
    } else {
        Room* availableRoom = findAvailableRoom();
        if(availableRoom != nullptr) {
            newStudent->room = availableRoom->roomNo;
            availableRoom->occupied++;
            cout << "Auto-assigned to Room " << availableRoom->roomNo << "\n";
        } else {
            newStudent->room = "Not Allocated";
            cout << "No rooms available currently\n";
        }
    }
    
    newStudent->next = nullptr;

    if(studentList == nullptr) {
        studentList = newStudent;
    } else {
        Student* temp = studentList;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }

    pushAction("Added student: " + newStudent->name);
    cout << "Student added successfully!\n";
}

void displayStudents() {
    if(studentList == nullptr) {
        cout << "No students in the system!\n";
        return;
    }

    cout << "\n" <<right<< setw(35) << "_______ALL STUDENTS_______" << "\n\n";
    cout << left 
         << setw(10) << "ID" 
         << setw(25) << "NAME" 
         << setw(15) << "PHONE"
         << "ROOM\n";
    cout << setfill('-') << setw(55) << "-" << setfill(' ') << "\n";
    
    Student* temp = studentList;
    while(temp != nullptr) {
        cout << left
             << setw(10) << temp->id
             << setw(25) << temp->name 
             << setw(15) << temp->phone
             << temp->room << "\n";
        temp = temp->next;
    }
}

void searchById() {
    if(studentList == nullptr) {
        cout << "No students in the system!\n";
        return;
    }

    string id;
    cout << "Enter student ID to search: ";
    getline(cin, id);

    Student* temp = studentList;
    bool found = false;
    
    while(temp != nullptr) {
        if(temp->id == id) {
            printStudentDetails(temp);
            found = true;
            break;
        }
        temp = temp->next;
    }

    if(!found) {
        cout << "Student not found!\n";
    }
}

void searchByDepartment() {
    if(studentList == nullptr) {
        cout << "No students in the system!\n";
        return;
    }

    string dept;
    cout << "Enter department to search: ";
    getline(cin, dept);

    Student* temp = studentList;
    bool found = false;
    
    cout << "\nStudents in " << dept << " department : \n";
    cout << "\n==============================";

    while(temp != nullptr) {
        if(temp->department == dept) {
            cout << "\nName: " << temp->name;
            cout << "\nID: " << temp->id;
            cout << "\nDepartment: " << temp->department;
            cout << "\nBlood Group: " << temp->bloodGroup;
            cout << "\nPhone: " << temp->phone;
            cout << "\nEmail: " << temp->email;
            cout << "\nRoom: " << temp->room;
            cout << "\n==============================";
            found = true;
        }
        temp = temp->next;
    }

    if(!found) {
        cout << "\nNo students found in this department!";
        cout << "\n==============================";
    }
    cout << "\n";
}

void searchByBloodGroup() {
    if(studentList == nullptr) {
        cout << "No students in the system!\n";
        return;
    }

    string bg;
    cout << "Enter blood group to search: ";
    getline(cin, bg);

    Student* temp = studentList;
    bool found = false;
    
    cout << "\nStudents with blood group " << bg << ": \n";
    cout << "\n==============================";

    while(temp != nullptr) {
        if(temp->bloodGroup == bg) {
            cout << "\nName: " << temp->name;
            cout << "\nID: " << temp->id;
            cout << "\nDepartment: " << temp->department;
            cout << "\nBlood Group: " << temp->bloodGroup;
            cout << "\nPhone: " << temp->phone;
            cout << "\nEmail: " << temp->email;
            cout << "\nRoom: " << temp->room;
            cout << "\n==============================";
            found = true;
        }
        temp = temp->next;
    }

    if(!found) {
        cout << "\nNo students found with this blood group!";
        cout << "\n==============================";
    }
    cout << "\n";
}

void searchByRoom() {
    if (studentList == nullptr) {
        cout << "No students in the system!\n";
        return;
    }

    string room;
    cout << "Enter room number to search: ";
    getline(cin, room);

    Student* temp = studentList;
    bool found = false;
    
    cout << "\nStudents in room " << room << ": \n";
    cout << "\n==============================";

    while (temp != nullptr) {
        if (temp->room == room) {
            cout << "\nName: " << temp->name;
            cout << "\nID: " << temp->id;
            cout << "\nDepartment: " << temp->department;
            cout << "\nBlood Group: " << temp->bloodGroup;
            cout << "\nPhone: " << temp->phone;
            cout << "\nEmail: " << temp->email;
            cout << "\n==============================";
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "\nNo students found in this room!";
        cout << "\n==============================";
    }
    cout << "\n";
}

void searchStudent() {
    int choice;
    do {
        cout << "\n===== SEARCH OPTIONS =====";
        cout << "\n1. Search by ID";
        cout << "\n2. Search by Department";
        cout << "\n3. Search by Blood Group";
        cout << "\n4. Search by Room";
        cout << "\n5. Back to Main Menu";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: searchById(); break;
            case 2: searchByDepartment(); break;
            case 3: searchByBloodGroup(); break;
            case 4: searchByRoom(); break;
            case 5: return;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 5);
}

void removeStudent() {
    if(studentList == nullptr) {
        cout << "No students in the system!\n";
        return;
    }

    string id;
    cout << "Enter student ID to remove: ";
    getline(cin, id);

    Student* current = studentList;
    Student* prev = nullptr;

    while(current != nullptr && current->id != id) {
        prev = current;
        current = current->next;
    }

    if(current == nullptr) {
        cout << "Student not found!\n";
        return;
    }

    if(current->room != "Not Allocated") {
        Room* room = roomList;
        while(room != nullptr) {
            if(room->roomNo == current->room) {
                room->occupied--;
                break;
            }
            room = room->next;
        }
    }

    if(prev == nullptr) {
        studentList = current->next;
    } else {
        prev->next = current->next;
    }

    pushAction("Removed student: " + current->name);
    cout << "Student removed successfully!\n";
    delete current;
}

void modifyStudent() {
    if(studentList == nullptr) {
        cout << "No students in the system!\n";
        return;
    }

    string id;
    cout << "Enter student ID to modify: ";
    getline(cin, id);

    Student* temp = studentList;
    while(temp != nullptr && temp->id != id) {
        temp = temp->next;
    }

    if(temp == nullptr) {
        cout << "Student not found!\n";
        return;
    }

    cout << "\nCurrent Details:";
    printStudentDetails(temp);

    cout << "\nEnter new details (leave blank to keep current):\n";
    cout << "New name: ";
    string newName;
    getline(cin, newName);
    if(!newName.empty()) temp->name = newName;

    cout << "New department: ";
    string newDept;
    getline(cin, newDept);
    if(!newDept.empty()) temp->department = newDept;

    cout << "New blood group: ";
    string newBg;
    getline(cin, newBg);
    if(!newBg.empty()) temp->bloodGroup = newBg;

    cout << "New phone: ";
    string newPhone;
    getline(cin, newPhone);
    if(!newPhone.empty()) temp->phone = newPhone;

    cout << "New email: ";
    string newEmail;
    getline(cin, newEmail);
    if(!newEmail.empty()) temp->email = newEmail;

    pushAction("Modified student: " + temp->name);
    cout << "Student details updated!\n";
}
void allocateRoom() {
    if (studentList == nullptr) {
        cout << "No students in the system!\n";
        return;
    }

    string id;
    cout << "Enter student ID to allocate room: ";
    getline(cin, id);

    Student* student = studentList;
    while (student != nullptr && student->id != id) {
        student = student->next;
    }

    if (student == nullptr) {
        cout << "Student not found!\n";
        return;
    }

    if (student->room != "Not Allocated") {
        cout << "Student already has a room allocated!\n";
        return;
    }

    printAvailableRooms();
    cout << "Enter room number to allocate: ";
    string roomNo;
    getline(cin, roomNo);

    if (isRoomAvailable(roomNo)) {
        student->room = roomNo;
        Room* room = roomList;
        while (room != nullptr && room->roomNo != roomNo) {
            room = room->next;
        }
        if (room != nullptr) room->occupied++;
        cout << "Allocated Room " << roomNo << " to " << student->name << "\n";
        pushAction("Allocated room " + roomNo + " to " + student->name);
    } else {
        cout << "Room full! Added to waiting list.\n";
        enqueueWaitingStudent(student->name, student->id, roomNo);
    }
}

void vacateRoom() {
    if (studentList == nullptr) {
        cout << "No students in the system!\n";
        return;
    }

    string id;
    cout << "Enter student ID to vacate room: ";
    getline(cin, id);

    Student* student = studentList;
    while (student != nullptr && student->id != id) {
        student = student->next;
    }

    if (student == nullptr) {
        cout << "Student not found!\n";
        return;
    }

    if (student->room == "Not Allocated") {
        cout << "Student has no room allocated!\n";
        return;
    }

    string vacatedRoom = student->room;
    Room* room = roomList;
    while (room != nullptr && room->roomNo != vacatedRoom) {
        room = room->next;
    }
    
    if (room != nullptr) {
        room->occupied--;
        
        WaitingStudent* prev = nullptr;
        WaitingStudent* current = waitingQueueFront;
        
        while (current != nullptr) {
            if (current->requestedRoom == vacatedRoom) {
                // Find the student in main list
                Student* waitingStudent = studentList;
                while (waitingStudent != nullptr && waitingStudent->id != current->id) {
                    waitingStudent = waitingStudent->next;
                }
                
                if (waitingStudent != nullptr) {
                    waitingStudent->room = vacatedRoom;
                    room->occupied++;
                    cout << "Automatically allocated Room " << vacatedRoom 
                         << " to " << waitingStudent->name << " from waiting list\n";
                    pushAction("Auto-allocated room " + vacatedRoom + " to " + waitingStudent->name);
                    
                    // Remove from queue
                    if (prev == nullptr) {
                        waitingQueueFront = current->next;
                    } else {
                        prev->next = current->next;
                    }
                    if (current == waitingQueueRear) {
                        waitingQueueRear = prev;
                    }
                    delete current;
                    break;
                }
            }
            prev = current;
            current = current->next;
        }
    }

    student->room = "Not Allocated";
    cout << "Vacated Room " << vacatedRoom << " from " << student->name << "\n";
    pushAction("Vacated room " + vacatedRoom + " from " + student->name);
}

void roomOccupancy() {
    if(roomList == nullptr) {
        cout << "No rooms initialized!\n";
        return;
    }
    cout << "\n===== ROOM OCCUPANCY =====";
    cout << "\nRoom\tOccupied\tAvailable\n";
    cout << "---------------------------\n";
    Room* temp = roomList;
    while(temp != nullptr) {
        cout << temp->roomNo << "\t" << temp->occupied << "/4\t\t" 
             << (temp->capacity - temp->occupied) << "\n";
        temp = temp->next;
    }
}

void generateReport() {
    ofstream reportFile("hall_report.txt");
    
    if(studentList == nullptr) {
        reportFile << "No student data available!\n";
    } else {
        reportFile << "===== HALL MANAGEMENT REPORT =====\n";
        reportFile << "ID\tName\t\tRoom\tDepartment\n";
        reportFile << "----------------------------------------\n";
        
        Student* temp = studentList;
        while(temp != nullptr) {
            reportFile << temp->id << "\t" << temp->name << "\t" 
                      << temp->room << "\t" << temp->department << "\n";
            temp = temp->next;
        }
    }
    reportFile.close();
    pushAction("Generated report");
    cout << "Report generated as hall_report.txt\n";
}

void saveToFile() {
    ofstream studentFile("students.txt");
    ofstream roomFile("rooms.txt");
    
    Student* sTemp = studentList;
    while(sTemp != nullptr) {
        studentFile << sTemp->name << "," << sTemp->id << "," 
                   << sTemp->department << "," << sTemp->bloodGroup << ","
                   << sTemp->phone << "," << sTemp->email << "," 
                   << sTemp->room << "\n";
        sTemp = sTemp->next;
    }
    
    Room* rTemp = roomList;
    while(rTemp != nullptr) {
        roomFile << rTemp->roomNo << "," << rTemp->capacity << "," 
                << rTemp->occupied << "\n";
        rTemp = rTemp->next;
    }
    
    studentFile.close();
    roomFile.close();
}

void loadFromFile() {
    ifstream studentFile("students.txt");
    if(studentFile) {
        string line;
        while(getline(studentFile, line)) {
            size_t pos[6];
            pos[0] = line.find(",");
            for(int i=1; i<6; i++) {
                pos[i] = line.find(",", pos[i-1]+1);
            }
            
            Student* newStudent = new Student;
            newStudent->name = line.substr(0, pos[0]);
            newStudent->id = line.substr(pos[0]+1, pos[1]-pos[0]-1);
            newStudent->department = line.substr(pos[1]+1, pos[2]-pos[1]-1);
            newStudent->bloodGroup = line.substr(pos[2]+1, pos[3]-pos[2]-1);
            newStudent->phone = line.substr(pos[3]+1, pos[4]-pos[3]-1);
            newStudent->email = line.substr(pos[4]+1, pos[5]-pos[4]-1);
            newStudent->room = line.substr(pos[5]+1);
            newStudent->next = nullptr;
            
            if(studentList == nullptr) {
                studentList = newStudent;
            } else {
                Student* temp = studentList;
                while(temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newStudent;
            }
        }
        studentFile.close();
    }
    
    ifstream roomFile("rooms.txt");
    if(roomFile) {
        string line;
        while(getline(roomFile, line)) {
            size_t pos1 = line.find(",");
            size_t pos2 = line.find(",", pos1+1);
            
            Room* newRoom = new Room;
            newRoom->roomNo = line.substr(0, pos1);
            newRoom->capacity = stoi(line.substr(pos1+1, pos2-pos1-1));
            newRoom->occupied = stoi(line.substr(pos2+1));
            newRoom->next = nullptr;
            
            if(roomList == nullptr) {
                roomList = newRoom;
            } else {
                Room* temp = roomList;
                while(temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newRoom;
            }
        }
        roomFile.close();
    }
}


void mainMenu() {
    int choice;
    do {
        cout << "\n===== HALL MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Remove Student";
        cout << "\n5. Modify Student";
        cout << "\n6. Allocate Room";
        cout << "\n7. Vacate Room";
        cout << "\n8. Room Occupancy";
        cout << "\n9. Recent Actions";
        cout << "\n10. Generate Report";
        cout << "\n11. View Waiting List";
        cout << "\n12. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: removeStudent(); break;
            case 5: modifyStudent(); break;
            case 6: allocateRoom(); break;
            case 7: vacateRoom(); break;
            case 8: roomOccupancy(); break;
            case 9: showRecentActions(); break;
            case 10: generateReport(); break;
            case 11: showWaitingList(); break;
            case 12: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 12);
}
int main() {
    initializeRooms();
    loadFromFile();
    
    int userType = authenticateUser();
    
    if(userType == 1) {
        mainMenu(); 
    } 
    else if(userType == 2) {
        ceoMenu(); 
    }
    
    saveToFile();
    return 0;
}