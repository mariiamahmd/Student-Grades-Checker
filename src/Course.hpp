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

public:
    // Constructor prototype
    Course(int cHours, const std::string &code, const std::string &name);
    Course(int cHours, const std::string &code, const std::string &name, Lecturer *lecturer = nullptr);

    // Setters & Getters
    std::string getCourseCode() const;
    std::string getCourseName() const;
    int getCreditHours() const;
    Lecturer *getAssignedLecturer() const;
    void setCourseName(const std::string &name) { courseName = name; }
    void setCreditHours(int hours) { creditHours = hours; }
    void setAssignedLecturer(Lecturer *lecturer) { assignedLecturer = lecturer; }
    void setStudentGrade(int studentId, double grade);

    int getEnrolledCount() const;
    std::vector<StudentScore> getTopStudents(int topN) const;
};