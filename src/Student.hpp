#pragma once

#include "Types.hpp"
#include <string>
#include <utility> // Required for std::pair
#include <vector>
using namespace std;

class Student
{
private:
    int studentID;
    int totalCreditHours;
    string studentName;

    // Vector of pairs storing the Term enum and the corresponding float GPA
    vector<pair<Term, float>> termGPAs;

public:
    // Constructors
    Student(int id, const string &name);
    Student(int id, const string &name, int cHours);

    // Getters (Essential for your BST navigation and Qt GUI display)
    int getID() const;
    const string &getName() const;
    int getTotalCreditHours() const;
    const vector<pair<Term, float>> &getTermGPAs() const; // Read-only access for UI

    // Setters / Modifiers
    // The Curriculum Manager will call this to append a new semester's GPA
    void addTermGPA(Term term, float gpa);
    void updateTotalCreditHours(int hours);

    // Core Business Logic
    float calculateCumulativeGPA() const;

    // Display / Debugging Methods
    // void displayStudentInfo() const;
    // void displayAcademicHistory() const;
};