#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> students; // {score, ID}

    for(int i = 0; i < n; i++) {
        int id, score;
        cin >> id >> score;
        students.push_back({score, id});
    }

    sort(students.begin(), students.end()); // score অনুযায়ী sort হবে (ascending)

    int sum = students[0].first + students[1].first + students[2].first;

    if(sum < 150) {
        cout << "Counseling Support Required\n";
    } else {
        cout << "Counseling Support Not Required\n";
        cout << students[0].first << " " << students[1].first << " " << students[2].first << "\n";
    }

    return 0;
}

//String 
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    // Vector to store {score, name} pair
    vector<pair<int, string>> students;

    for (int i = 0; i < n; i++) {
        string name;
        int score;
        cin >> name >> score;
        students.push_back({score, name});
    }

    // Sort the vector by score (ascending)
    sort(students.begin(), students.end());

    // Sum of the lowest three scores
    int sum = students[0].first + students[1].first + students[2].first;

    // Output
    if (sum < 150) {
        cout << "Counseling Support Required\n";
    } else {
        cout << "Counseling Support Not Required\n";
        cout << students[0].first << " " << students[1].first << " " << students[2].first << "\n";
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

struct Student {
    int id;
    int score;
};

int main() {
    int n;
    cin >> n;

    vector<Student> students(n);

    for (int i = 0; i < n; i++) {
        cin >> students[i].id >> students[i].score;
    }

    // Score অনুযায়ী ascending sort
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        return a.score < b.score;
    });

    int sum = students[0].score + students[1].score + students[2].score;

    if (sum < 150) {
        cout << "Counseling Support Required\n";
    } else {
        cout << "Counseling Support Not Required\n";
        cout << students[0].score << " " << students[1].score << " " << students[2].score << "\n";
    }

    return 0;
}


#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    // Vector to store {score, name} pair
    vector<pair<int, string>> students;

    for (int i = 0; i < n; i++) {
        string name;
        int score;
        cin >> name >> score;
        students.push_back({score, name});
    }

    // Sort by score (ascending)
    sort(students.begin(), students.end());

    // Sum of lowest 3 scores
    int sum = students[0].first + students[1].first + students[2].first;

    if (sum < 150) {
        cout << "Counseling Support Required\n";
    } else {
        cout << "Counseling Support Not Required\n";
        // Print 3 lowest score with names
        for (int i = 0; i < 3; i++) {
            cout << students[i].first << " " << students[i].second << "\n";
        }
    }

    return 0;
}

//struct use  

#include <bits/stdc++.h>
using namespace std;

struct Student {
    int id;
    string name;
    int score;
    string city;
};

int main() {
    int n;
    cin >> n;

    vector<Student> students(n);

    // Input student data
    for (int i = 0; i < n; i++) {
        cin >> students[i].id >> students[i].name >> students[i].score >> students[i].city;
    }

    // Sort by score ascending
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        return a.score < b.score;
    });

    // Sum of lowest 3 scores
    int sum = students[0].score + students[1].score + students[2].score;

    if (sum < 150) {
        cout << "Counseling Support Required\n";
    } else {
        cout << "Counseling Support Not Required\n";
        for (int i = 0; i < 3; i++) {
            cout << students[i].score << " " << students[i].name << " " << students[i].id << " " << students[i].city << "\n";
        }
    }

    return 0;
}
