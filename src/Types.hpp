#pragma once

#include <string>

// Enum representing the academic term
enum class Term { Fall, Spring, Summer };

// Struct representing a student's score in a specific course
struct StudentScore
{
    int studentID;
    std::string studentName;
    double grade;

    // Operator overload for the Max-Heap in the Course class
    bool operator<(const StudentScore &other) const { return grade < other.grade; }
};
