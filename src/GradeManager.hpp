#pragma once

#include "Course.hpp"
#include "Lecturer.hpp"
#include "Student.hpp"
#include "Types.hpp"
#include <map>
#include <string>
#include <vector>

// Node structure declaration for the Binary Search Tree
struct TreeNode
{
    Student student;
    TreeNode *left;
    TreeNode *right;
    // Constructor prototype
    TreeNode(const Student &s);
};

class GradeManager
{
private:
    TreeNode *root; // Root of the Student BST (Ordered by Student ID)

    // Master lists for the other entities
    std::map<std::string, Course> coursesID;
    std::unordered_map<int, Lecturer> lecturers;

    // Private helper functions for recursive BST operations
    TreeNode *insertHelper(TreeNode *node, const Student &newStudent);
    TreeNode *searchHelper(TreeNode *node, int id) const;
    void inorderTraversal(TreeNode *node) const;
    void destroyTree(TreeNode *node);

public:
    // Constructor & Destructor prototypes
    GradeManager();
    ~GradeManager();

    // Core Student Operations (Using BST)
    void addStudent(int id, const std::string &name);
    bool searchStudent(int id) const;
    void displayAllStudents() const;
    void addTermGPA(int studentId, Term term, float gpa);

    // Core System Linkage Operations
    void addCourse(int creditHours, const std::string &code, const std::string &name);
    void addLecturer(int id, std::string name, const std::string &dept);
    void assignLecturerToCourse(int lecturerId, const std::string &courseCode);
    void recordGradeForCourse(const std::string &courseCode, int studentId, double grade);

    // Combines the ID/Grade from Course with the Name from the Student BST
    std::vector<StudentScore> getTopStudentsReport(const std::string &courseCode, int topN) const;
};