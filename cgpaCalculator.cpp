#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

/* ---------- Structure Definitions ---------- */

struct Course {
    string name;
    string grade;
    double gradePoint;
    int creditHours;
};

struct Semester {
    vector<Course> courses;
    int totalCredits = 0;
    double totalGradePoints = 0.0;
    double gpa = 0.0;
};

/* ---------- Grade Conversion Function ---------- */

double convertGradeToPoint(string grade) {
    for (char &c : grade)
        c = toupper(c);

    if (grade == "A") return 4.0;
    if (grade == "A-") return 3.7;
    if (grade == "B+") return 3.3;
    if (grade == "B") return 3.0;
    if (grade == "C") return 2.0;
    if (grade == "D") return 1.0;
    if (grade == "F") return 0.0;

    return -1.0;
}

/* ---------- Input Semester Data ---------- */

void inputSemesterData(Semester &sem, int semesterNumber) {

    int courseCount;

    cout << "\nEnter number of courses for Semester "
         << semesterNumber << ": ";
    cin >> courseCount;

    while (courseCount <= 0) {
        cout << "Invalid number. Enter again: ";
        cin >> courseCount;
    }

    sem.courses.resize(courseCount);

    for (int i = 0; i < courseCount; i++) {

        Course &c = sem.courses[i];

        cin.ignore();

        cout << "\nCourse " << i + 1 << " Name: ";
        getline(cin, c.name);

        do {
            cout << "Grade (A, A-, B+, B, C, D, F): ";
            cin >> c.grade;

            c.gradePoint = convertGradeToPoint(c.grade);

            if (c.gradePoint < 0)
                cout << "Invalid grade. Try again.\n";

        } while (c.gradePoint < 0);

        cout << "Credit Hours: ";
        cin >> c.creditHours;

        while (c.creditHours <= 0) {
            cout << "Invalid credit hours. Enter again: ";
            cin >> c.creditHours;
        }
    }
}

/* ---------- Calculate Semester Result ---------- */

void calculateSemesterResult(Semester &sem) {

    sem.totalCredits = 0;
    sem.totalGradePoints = 0.0;

    for (const Course &c : sem.courses) {
        sem.totalCredits += c.creditHours;
        sem.totalGradePoints += (c.gradePoint * c.creditHours);
    }

    sem.gpa = sem.totalGradePoints / sem.totalCredits;
}

/* ---------- Display Semester Result ---------- */

void displaySemesterResult(const Semester &sem, int semesterNumber) {

    cout << "\n=============================================================\n";
    cout << "                 Semester " << semesterNumber << " Result\n";
    cout << "=============================================================\n";

    cout << left
         << setw(25) << "Course"
         << setw(12) << "Grade"
         << setw(15) << "Credit Hours"
         << setw(15) << "Earned Points"
         << endl;

    cout << "-------------------------------------------------------------\n";

    for (const Course &c : sem.courses) {

        cout << left
             << setw(25) << c.name
             << setw(12) << c.grade
             << setw(15) << c.creditHours
             << setw(15) << fixed << setprecision(2)
             << (c.gradePoint * c.creditHours)
             << endl;
    }

    cout << "-------------------------------------------------------------\n";
    cout << "Total Credits : " << sem.totalCredits << endl;
    cout << "Semester GPA  : " << fixed << setprecision(2)
         << sem.gpa << endl;
}

/* ---------- Main Function ---------- */

int main() {

    int totalSemesters;

    cout << "Enter total number of semesters: ";
    cin >> totalSemesters;

    while (totalSemesters <= 0) {
        cout << "Invalid input. Enter again: ";
        cin >> totalSemesters;
    }

    vector<Semester> semesters(totalSemesters);

    double overallGradePoints = 0.0;
    int overallCredits = 0;

    for (int i = 0; i < totalSemesters; i++) {

        inputSemesterData(semesters[i], i + 1);
        calculateSemesterResult(semesters[i]);
        displaySemesterResult(semesters[i], i + 1);

        overallGradePoints += semesters[i].totalGradePoints;
        overallCredits += semesters[i].totalCredits;
    }

    double cgpa = overallGradePoints / overallCredits;

    cout << "\n=============================================================\n";
    cout << "Final CGPA : " << fixed << setprecision(2)
         << cgpa << endl;
    cout << "=============================================================\n";

    return 0;
}