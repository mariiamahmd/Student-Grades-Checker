#pragma once

#include "Lecturer.hpp"
#include "Types.hpp"
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>

class Course
{
private:
    int creditHours;
    std::string courseCode;
    std::string courseName;
    Lecturer *assignedLecturer;
    std::unordered_map<int, double> enrolledStudents; // Hash map for O(1) lookups and updates: Key = StudentID, Value = Grade
    // std::priority_queue<StudentScore> gradeHeap; // can be a vector instead of popping a queue

public:
    // Constructor prototype
    Course(int cHours, const std::string &code, const std::string &name);
    Course(int cHours, const std::string &code, const std::string &name, Lecturer *lecturer = nullptr);

    // Method prototypes
    void setStudentGrade(int studentId, double grade);
    std::vector<StudentScore> getTopStudents(int topN) const;
    void displayCourseInfo() const;
};