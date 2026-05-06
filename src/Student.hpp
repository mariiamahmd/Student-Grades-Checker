#pragma once

#include "Types.hpp"
#include <string>
#include <utility> // Required for std::pair
#include <vector>

class Student
{
private:
    int studentID;
    int totalCreditHours;
    std::string name;
    // Vector of pairs storing the Term and the corresponding float GPA
    std::vector<std::pair<Term, float>> termGPAs;

public:
    // Constructor prototype
    Student(int id, const std::string &studentName);
    Student(int id, const std::string &studentName, int cHours);

    // Getter prototypes
    int getID() const;
    const std::string &getName() const;
    int getTotalCreditHours() const;

    // Term GPA method prototypes
    float calculateCumulativeGPA() const; // TODO: maybe reformat with a cGPA calculator tab

    // Display prototypes
    void displayStudentInfo() const;
    void displayAcademicHistory() const;
};