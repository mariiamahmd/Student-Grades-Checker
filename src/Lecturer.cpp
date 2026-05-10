#include "Lecturer.hpp"
// Constructor prototype
Lecturer::Lecturer(int id, const std::string &lecturerName, const std::string &dept) : lecturerID(id), name(lecturerName), department(department){};

// Getter prototypes
int Lecturer::getID() const {
  return lecturerID;
};

const std::string &Lecturer::getName() const {
  return name;
};

const std::string &Lecturer::getDepartment() const {
  return department;
};