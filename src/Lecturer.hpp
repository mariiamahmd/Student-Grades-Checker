#pragma once

#include <string>

class Lecturer
{
private:
    int lecturerID;
    std::string name;
    std::string department;

public:
    // Constructor prototype
    Lecturer(int id, const std::string &lecturerName, const std::string &dept);

    // Getter prototypes
    int getID() const;
    const std::string &getName() const;
    const std::string &getDepartment() const;

    // Display prototype
    // void displayInfo() const;
};