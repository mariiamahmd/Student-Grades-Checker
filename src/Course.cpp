#include "Course.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

// Constructors Implementation
Course::Course(int cHours, const std::string &code, const std::string &name)
    : creditHours(cHours), courseCode(code), courseName(name), assignedLecturer(nullptr)
{
}

Course::Course(int cHours, const std::string &code, const std::string &name, Lecturer *lecturer)
    : creditHours(cHours), courseCode(code), courseName(name), assignedLecturer(lecturer)
{
}

// Setters & Getters
void Course::setStudentGrade(int studentId, double grade)
{
  enrolledStudents[studentId] = grade;
}

std::string Course::getCourseCode() const
{
  return courseCode;
}

std::string Course::getCourseName() const
{
  return courseName;
}

int Course::getCreditHours() const
{
  return creditHours;
}

Lecturer *Course::getAssignedLecturer() const
{
  return assignedLecturer;
}

int Course::getEnrolledCount() const
{
  return enrolledStudents.size();
}

std::vector<StudentScore> Course::getTopStudents(int topN) const
{
  std::vector<StudentScore> sortedScores;

  // 1. Extract from the unordered_map into our flat vector
  for (const auto &pair : enrolledStudents)
  {
    StudentScore score;
    score.studentID = pair.first;
    score.grade = pair.second;
    score.studentName = "Unknown"; // Placeholder: The Course object doesn't store strings of names

    sortedScores.push_back(score);
  }

  // 2. Sort the vector in descending order (highest grade first)
  std::sort(sortedScores.begin(), sortedScores.end(), [](const StudentScore &a, const StudentScore &b)
            { return a.grade > b.grade; });

  // 3. Trim the vector to only keep the Top N students
  // (We cast topN to size_t to safely compare it with vector.size())
  if (sortedScores.size() > static_cast<size_t>(topN))
  {
    sortedScores.resize(topN);
  }

  return sortedScores;
}