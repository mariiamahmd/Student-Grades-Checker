#include "Student.hpp"
#include <iostream>

using namespace std;

Student::Student(int id, const string &name)
    : studentID(id), studentName(name), baseCreditHours(0)
{
}

Student::Student(int id, const string &name, int cHours)
    : studentID(id), studentName(name), baseCreditHours(cHours)
{
}

int Student::getID() const
{
    return studentID;
}

const string &Student::getName() const
{
    return studentName;
}

// Dynamically calculates total credits by adding base credits to completed courses
int Student::getTotalCreditHours() const
{
    int earnedCredits = baseCreditHours;
    for (const auto& course : registeredCourses) {
        // Only count credits if the course has a grade (>= 0.0)
        if (course.grade >= 0.0f) {
            earnedCredits += course.credits;
        }
    }
    return earnedCredits;
}

const vector<CourseRecord>& Student::getRegisteredCourses() const
{
    return registeredCourses;
}

// ==========================================
// NEW COURSE MANAGEMENT LOGIC
// ==========================================

void Student::registerCourse(const string& courseCode, Term term, int credits)
{
    // Defense: Prevent registering for the same course twice
    for (const auto& course : registeredCourses) {
        if (course.courseCode == courseCode) {
            return;
        }
    }

    // Add the course with a default "In Progress" grade of -1.0f
    registeredCourses.push_back({courseCode, term, credits, -1.0f});
}

bool Student::setCourseGrade(const string& courseCode, float grade)
{
    // Search for the course and update the grade
    for (auto& course : registeredCourses) {
        if (course.courseCode == courseCode) {
            course.grade = grade;
            return true; // Successfully updated
        }
    }
    return false; // Error: Student is not registered for this course
}

// ==========================================
// TRUE WEIGHTED GPA CALCULATION
// ==========================================

float Student::calculateCumulativeGPA() const
{
    float totalQualityPoints = 0.0f;
    int totalGradedCredits = 0;

    for (const auto& course : registeredCourses) {
        // Only calculate GPA for courses that have been completed
        if (course.grade >= 0.0f) {
            totalQualityPoints += (course.grade * course.credits);
            totalGradedCredits += course.credits;
        }
    }

    // Prevent division by zero if the student hasn't completed any courses yet
    if (totalGradedCredits == 0) {
        return 0.0f;
    }

    return totalQualityPoints / totalGradedCredits;
}