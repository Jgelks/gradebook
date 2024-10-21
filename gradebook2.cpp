#include <iostream>
#include <map>
#include <iomanip>

using namespace std;

class Gradebook {
private:
    map<string, string> students;
    map<string, int> assignments;
    map<string, map<string, int>> grades;

public:
    void addStudent(const string& firstName, const string& lastName, const string& studentId) {
        students[studentId] = firstName + " " + lastName;
    }

    void addAssignment(const string& name, int totalPoints) {
        assignments[name] = totalPoints;
    }

    void giveGrade(const string& studentId, const string& assignmentName, int grade) {
        if (students.find(studentId) != students.end() && assignments.find(assignmentName) != assignments.end()) {
            int totalPoints = assignments[assignmentName];
            if (grade >= 0 && grade <= totalPoints) {
                grades[studentId][assignmentName] = grade;
            } else {
                cout << "Grade must be between 0 and " << totalPoints << ".\n";
            }
        } else {
            cout << "Invalid student ID or assignment name.\n";
        }
    }

    void printReport() const {
        cout << "Student Report:\n";
        cout << string(30, '-') << '\n';
        cout << left << setw(15) << "Student ID" 
             << setw(25) << "Name";

        for (const auto& assignment : assignments) {
            cout << setw(15) << assignment.first;
        }
        cout << '\n';

        for (const auto& student : students) {
            const string& studentId = student.first;
            const string& name = student.second;
            cout << left << setw(15) << studentId 
                 << setw(25) << name;

            for (const auto& assignment : assignments) {
                string assignmentName = assignment.first;

                auto studentGradesIt = grades.find(studentId);
                if (studentGradesIt != grades.end()) {
                    auto gradeIt = studentGradesIt->second.find(assignmentName);
                    if (gradeIt != studentGradesIt->second.end()) {
                        cout << setw(15) << gradeIt->second;
                    } else {
                        cout << setw(15) << "-";
                    }
                } else {
                    cout << setw(15) << "-";
                }
            }
            cout << '\n';
        }
    }
};

int main() {
    Gradebook gradebook;

    gradebook.addStudent("John", "Smoth", "001");
    gradebook.addStudent("John", "Smoth", "002");
    gradebook.addStudent("Jane", "Spain", "003");

    gradebook.addAssignment("Math Homework", 100);
    gradebook.addAssignment("Science Project", 50);

    gradebook.giveGrade("001", "Math Homework", 100);
    gradebook.giveGrade("001", "Science Project", 45);
    gradebook.giveGrade("002", "Math Homework", 90);

    gradebook.printReport();

    return 0;
}