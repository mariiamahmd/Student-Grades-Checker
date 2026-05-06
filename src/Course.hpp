#pragma once

#include "Lecturer.hpp"
#include "Types.hpp"
#include <queue>
#include <string>
#include <vector>

class Course
{
private:
    int creditHours;
    std::string courseCode;
    std::string courseName;
    Lecturer *assignedLecturer;
    std::priority_queue<StudentScore> gradeHeap; // can be a vector instead of popping a queue

public:
    // Constructor prototype
    Course(int cHours,
           const std::string &code,
           const std::string &name,
           Lecturer *lecturer = nullptr);

    // Method prototypes
    void addStudentGrade(int id, const std::string &name, double grade);
    void displayTopStudents(int topN) const;
    void displayCourseInfo() const;
};