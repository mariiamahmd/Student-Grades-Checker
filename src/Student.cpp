#include "Student.hpp"
#include <iostream>
#include <string>

using namespace std;

Student::Student(int id, const string &name)
    : studentID(id), studentName(name), totalCreditHours(0)
{
}

Student::Student(int id, const std::string &name, int cHours)
    : studentID(id), studentName(name), totalCreditHours(cHours)
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

int Student::getTotalCreditHours() const
{
    return totalCreditHours;
}

const vector<pair<Term, float>> &Student::getTermGPAs() const
{
    return termGPAs;
}

void Student::addTermGPA(Term term, float gpa)
{
    termGPAs.push_back({term, gpa});
}

void Student::updateTotalCreditHours(int hours)
{
    totalCreditHours += hours;
}

float Student::calculateCumulativeGPA() const
{
    if (termGPAs.size() == 0)
        return 0.0;
    float sum = 0.0f;
    for (int i = 0; i < termGPAs.size(); i++)
    {
        sum += termGPAs[i].second;
    }
    return sum / termGPAs.size();
}

// void Student::displayStudentInfo() const
// {
//     cout << "ID: " << studentID << " | Name: " << studentName << "\n";
//     cout << "Total Credits: " << totalCreditHours << "\n";
//     cout << "Cumulative GPA: " << calculateCumulativeGPA() << "\n";
// }

// void Student::displayAcademicHistory() const
// {
//     cout << "Academic History for " << studentName << " (" << studentID << "):\n";

//     if (termGPAs.empty())
//     {
//         cout << "  No semester records found.\n";
//         return;
//     }
//     for (int i = 0; i < termGPAs.size(); i++)
//     {
//         cout << "  Term Code [" << static_cast<int>(termGPAs[i].first) << "] : GPA = " << termGPAs[i].second << "\n";
//     }
// }