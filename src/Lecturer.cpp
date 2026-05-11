#include "Lecturer.hpp"
// Constructor implementations
Lecturer::Lecturer(int id, const std::string &lecturerName, const std::string &dept) : lecturerID(id), name(lecturerName), department(dept) {};

// Getter implementations
int Lecturer::getID() const
{
  return lecturerID;
}

const std::string &Lecturer::getName() const
{
  return name;
}

const std::string &Lecturer::getDepartment() const
{
  return department;
}