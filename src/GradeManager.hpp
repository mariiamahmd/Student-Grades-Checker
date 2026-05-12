#pragma once
#include "Student.hpp"
#include "Course.hpp"
#include "Lecturer.hpp" 
#include "Types.hpp"
#include <string>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

// Node structure declaration for the Binary Search Tree
struct TreeNode
{
    Student student;
    TreeNode *left;
    TreeNode *right;

    // Constructor ensuring the student is copied safely
    TreeNode(const Student &s) : student(s), left(nullptr), right(nullptr) {}
};

class GradeManager
{
private:
    TreeNode *root; // Root of the Student BST

    // NEW: Course & Lecturer Hash Map Storage
    std::unordered_map<std::string, Course *> coursesDatabase; // Key: Course Code
    std::unordered_map<int, Lecturer *> lecturersDatabase;     // Key: Lecturer ID

    // Private helper functions for recursive BST operations
    TreeNode *insertHelper(TreeNode *node, const Student &newStudent);
    TreeNode *searchHelper(TreeNode *node, int id) const;

    // Deletion helpers
    TreeNode *deleteHelper(TreeNode *node, int id);
    TreeNode *findInOrderSuccessor(TreeNode *node) const;

    // Traversal and memory management
    void inorderTraversal(TreeNode *node) const;
    void destroyTree(TreeNode *node);

    // Habiba: Helper to collect students for the UI -->
    void collectStudentsInOrder(TreeNode *node, std::vector<Student *> &studentList) const;

public:
    // Constructor & Destructor
    GradeManager();
    ~GradeManager();

    // Core Student Operations (Using BST)
    void addStudent(int id, const string &name);
    Student *searchStudent(int id) const;
    bool deleteStudent(int id);

    // ==========================================
    // --- NEW: Course & Grade Modifiers ---
    // ==========================================

    // Registers a student for a course (default grade is -1.0)
    bool registerStudentForCourse(int studentId, const string& courseCode, Term term, int credits);

    // Updates the grade for a specific course the student is taking
    bool gradeStudentCourse(int studentId, const string& courseCode, float grade);

    // NEW: Course & Lecturer Operations
    void addCourse(Course *newCourse);
    Course *searchCourse(const std::string &courseCode) const;
    std::vector<Course *> getAllCourses() const;

    void addLecturer(Lecturer *newLecturer);
    Lecturer *searchLecturer(int id) const;
    std::vector<Lecturer *> getAllLecturers() const;
    bool deleteLecturer(int id);

    // UI Fetchers & Reports
    vector<Student *> getTopStudentsByCGPA(int topN = 10) const;
    void getPassFailReport(int &passCount, int &failCount, float passingGPA = 2.0) const;
    map<string, int> getGradeDistribution() const;
    std::vector<Student *> getAllStudentsAsList() const;
    bool deleteCourse(const std::string& courseCode);
};