#pragma once

#include "Types.hpp"
#include <string>
#include <vector>

using namespace std;

// --- NEW: A struct to hold the data for an individual course ---
struct CourseRecord {
    string courseCode;
    Term semester;
    int credits;
    float grade; // We will use -1.0 to indicate a course is "In Progress" (no grade yet)
};

class Student
{
private:
    int studentID;
    int baseCreditHours; // Credits transferred from outside, if any
    string studentName;

    // --- NEW: Vector storing the student's actual course history ---
    vector<CourseRecord> registeredCourses;

public:
    // Constructors
    Student(int id, const string &name);
    Student(int id, const string &name, int cHours);

    // Getters
    int getID() const;
    const string &getName() const;
    int getTotalCreditHours() const; // Now calculates dynamically!

    // Read-only access to course history for the UI
    const vector<CourseRecord>& getRegisteredCourses() const;

    // --- NEW: Setters / Modifiers ---
    // 1. Registers a student for a course with no grade (-1.0)
    void registerCourse(const string& courseCode, Term term, int credits);

    // 2. Assigns a final grade to a course the student is taking
    bool setCourseGrade(const string& courseCode, float grade);

    // Core Business Logic
    float calculateCumulativeGPA() const;
};