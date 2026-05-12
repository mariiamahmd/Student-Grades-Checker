#include "GradeManager.hpp"
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

GradeManager::GradeManager() : root(nullptr) {}

GradeManager::~GradeManager()
{
    // clean up BST memory when the program closes
    destroyTree(root);

    for (auto& pair : coursesDatabase) {
        delete pair.second;
    }
    
    for (auto& pair : lecturersDatabase) {
        delete pair.second;
    }
}

void GradeManager::destroyTree(TreeNode *node)
{
    if (node != nullptr)
    {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

///////////adding student ////////////

void GradeManager::addStudent(int id, const string &name)
{
    Student newStudent(id, name);
    root = insertHelper(root, newStudent);
}


/////// search student ///////////

Student *GradeManager::searchStudent(int id) const
{
    TreeNode *result = searchHelper(root, id);

    if (result != nullptr)
    {
        // cast away const so the teammate's code can modify the student's grades
        return const_cast<Student *>(&(result->student));
    }
    return nullptr;
}

/////delete student//////

bool GradeManager::deleteStudent(int id)
{
    // check if student exists first
    if (searchStudent(id) == nullptr)
    {
        return false;
    }

    root = deleteHelper(root, id);
    return true;
}

// ==========================================
// --- NEW: Course Registration & Grading ---
// ==========================================

bool GradeManager::registerStudentForCourse(int studentId, const string& courseCode, Term term, int credits)
{
    Student *foundStudent = searchStudent(studentId);

    if (foundStudent != nullptr)
    {
        foundStudent->registerCourse(courseCode, term, credits);
        return true;
    }
    return false; // Student not found
}

bool GradeManager::gradeStudentCourse(int studentId, const string& courseCode, float grade)
{
    Student *foundStudent = searchStudent(studentId);

    if (foundStudent != nullptr)
    {
        return foundStudent->setCourseGrade(courseCode, grade);
    }
    return false; // Student not found
}


// void GradeManager::displayAllStudents() const
// {
//     if (root == nullptr)
//     {
//         cout << "No students in the system.\n";
//         return;
//     }

//     cout << "--- Student Directory ---\n";
//     inorderTraversal(root);
//     cout << "-------------------------\n";
// }

TreeNode *GradeManager::insertHelper(TreeNode *node, const Student &newStudent)
{
    // found an empty leaf, create the node here
    if (node == nullptr)
    {
        return new TreeNode(newStudent);
    }

    // sort by ID
    if (newStudent.getID() < node->student.getID())
    {
        node->left = insertHelper(node->left, newStudent);
    }
    else if (newStudent.getID() > node->student.getID())
    {
        node->right = insertHelper(node->right, newStudent);
    }

    // duplicates are ignored automatically
    return node;
}

TreeNode *GradeManager::searchHelper(TreeNode *node, int id) const
{
    // return if found or if we hit a dead end
    if (node == nullptr || node->student.getID() == id)
    {
        return node;
    }

    // navigate left or right based on ID
    if (id < node->student.getID())
    {
        return searchHelper(node->left, id);
    }
    return searchHelper(node->right, id);
}

TreeNode *GradeManager::deleteHelper(TreeNode *node, int id)
{
    if (node == nullptr)
        return node;

    // locate the node
    if (id < node->student.getID())
    {
        node->left = deleteHelper(node->left, id);
    }
    else if (id > node->student.getID())
    {
        node->right = deleteHelper(node->right, id);
    }
    else
    {
        // node found. handle cases where it has 0 or 1 child
        if (node->left == nullptr)
        {
            TreeNode *temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            TreeNode *temp = node->left;
            delete node;
            return temp;
        }

        // node has 2 children. replace it with the in-order successor
        TreeNode *temp = findInOrderSuccessor(node->right);
        node->student = temp->student;
        node->right = deleteHelper(node->right, temp->student.getID());
    }
    return node;
}

TreeNode *GradeManager::findInOrderSuccessor(TreeNode *node) const
{
    TreeNode *current = node;
    // go as far left as possible to find the smallest value
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

void GradeManager::inorderTraversal(TreeNode *node) const
{
    if (node != nullptr)
    {
        inorderTraversal(node->left);
        // node->student.displayStudentInfo();
        inorderTraversal(node->right);
    }
}


// Get top N students by CGPA
vector<Student*> GradeManager::getTopStudentsByCGPA(int topN) const {
    vector<Student*> allStudents = getAllStudentsAsList(); //Get them as lists first

    // Sort by CGPA
    sort(allStudents.begin(), allStudents.end(), //used stl sort
         [](const Student* a, const Student* b) {
             return a->calculateCumulativeGPA() > b->calculateCumulativeGPA();
         });

    // Return top N
    if (allStudents.size() > topN) {
        allStudents.resize(topN); //resize vector to contain on N students
    }

    return allStudents;
}

// Get pass/fail counts
void GradeManager::getPassFailReport(int &passCount, int &failCount, float passingGPA) const {
    passCount = 0;
    failCount = 0;

    vector<Student*> allStudents = getAllStudentsAsList();

    for (Student* student : allStudents) //Loop through each student
    {
        float cgpa = student->calculateCumulativeGPA(); //get each student gpa
        if (cgpa >= passingGPA) {
            passCount++;
        } else {
            failCount++;
        }
    }
}

// Get grade distribution (A, B, C, D, F) //to draw histogram
map<string, int> GradeManager::getGradeDistribution() const {
    map<string, int> distribution;  //mapping to store Grade and count
    distribution["A"] = 0;
    distribution["B"] = 0;
    distribution["C"] = 0;
    distribution["D"] = 0;
    distribution["F"] = 0;

    vector<Student*> allStudents = getAllStudentsAsList();

    for (Student* student : allStudents) //loop through each student and add its grade in its specific place
    {
        float cgpa = student->calculateCumulativeGPA();

        if (cgpa >= 3.7) {
            distribution["A"]++;
        } else if (cgpa >= 3.0) {
            distribution["B"]++;
        } else if (cgpa >= 2.0) {
            distribution["C"]++;
        } else if (cgpa >= 1.0) {
            distribution["D"]++;
        } else {
            distribution["F"]++;
        }
    }

    return distribution;
}

// COURSE OPERATIONS (O(1) Hash Map)
void GradeManager::addCourse(Course* newCourse) 
{
    if (newCourse != nullptr) {
        coursesDatabase[newCourse->getCourseCode()] = newCourse;
    }
}

Course* GradeManager::searchCourse(const std::string& courseCode) const 
{
    auto it = coursesDatabase.find(courseCode);
    if (it != coursesDatabase.end()) {
        return it->second; // Found it!
    }
    return nullptr; // Not found
}

std::vector<Course*> GradeManager::getAllCourses() const 
{
    std::vector<Course*> courseList;
    for (const auto& pair : coursesDatabase) {
        courseList.push_back(pair.second);
    }
    return courseList;
}

bool GradeManager::deleteCourse(const std::string& courseCode) 
{
    // Look for the course in the hash map
    auto it = coursesDatabase.find(courseCode);
    
    if (it != coursesDatabase.end()) {
        delete it->second;         // 1. Free the memory (avoid memory leaks!)
        coursesDatabase.erase(it); // 2. Remove it from the Hash Map
        return true;
    }
    return false; // Course not found
}

// LECTURER OPERATIONS (O(1) Hash Map)
void GradeManager::addLecturer(Lecturer* newLecturer) 
{
    if (newLecturer != nullptr) {
        lecturersDatabase[newLecturer->getID()] = newLecturer;
    }
}

bool GradeManager::deleteLecturer(int id) 
{
    auto it = lecturersDatabase.find(id);
    if (it != lecturersDatabase.end()) {
        
        // 1. Safety Check: If this lecturer is teaching a course, unassign them first!
        for (auto& pair : coursesDatabase) {
            if (pair.second->getAssignedLecturer() == it->second) {
                pair.second->setAssignedLecturer(nullptr);
            }
        }

        // 2. Free the memory and remove them from the system
        delete it->second;         
        lecturersDatabase.erase(it); 
        return true;
    }
    return false; // Not found
}

Lecturer* GradeManager::searchLecturer(int id) const 
{
    auto it = lecturersDatabase.find(id);
    if (it != lecturersDatabase.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<Lecturer*> GradeManager::getAllLecturers() const 
{
    std::vector<Lecturer*> lecturerList;
    for (const auto& pair : lecturersDatabase) {
        lecturerList.push_back(pair.second);
    }
    return lecturerList;
}

// ==============================================================
// NEW UI TRANSLATION METHODS
// ==============================================================
std::vector<Student *> GradeManager::getAllStudentsAsList() const
{
    std::vector<Student *> studentList;
    collectStudentsInOrder(root, studentList);
    return studentList;
}

void GradeManager::collectStudentsInOrder(TreeNode *node, std::vector<Student *> &studentList) const
{
    if (node != nullptr)
    {
        collectStudentsInOrder(node->left, studentList);

        // Grab the memory address of the student and add it to our UI list
        studentList.push_back(const_cast<Student *>(&(node->student)));

        collectStudentsInOrder(node->right, studentList);
    }
}