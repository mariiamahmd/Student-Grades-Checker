#include "GradeManager.hpp"
#include <iostream>

using namespace std;


GradeManager::GradeManager() : root(nullptr) {}

GradeManager::~GradeManager() {
    // clean up memory when the program closes
    destroyTree(root);
}

void GradeManager::destroyTree(TreeNode *node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void GradeManager::addStudent(int id, const string &name) {
    Student newStudent(id, name);
    root = insertHelper(root, newStudent);
}

Student* GradeManager::searchStudent(int id) const {
    TreeNode* result = searchHelper(root, id);

    if (result != nullptr) {
        // cast away const so the teammate's code can modify the student's grades
        return const_cast<Student*>(&(result->student));
    }
    return nullptr;
}

bool GradeManager::deleteStudent(int id) {
    // check if student exists first
    if (searchStudent(id) == nullptr) {
        return false;
    }

    root = deleteHelper(root, id);
    return true;
}

void GradeManager::addTermGPA(int studentId, Term term, float gpa) {
    Student* foundStudent = searchStudent(studentId);

    if (foundStudent != nullptr) {
        foundStudent->addTermGPA(term, gpa);
        cout << "GPA recorded for ID: " << studentId << "\n";
    } else {
        cout << "Error: Student ID " << studentId << " not found.\n";
    }
}

void GradeManager::displayAllStudents() const {
    if (root == nullptr) {
        cout << "No students in the system.\n";
        return;
    }

    cout << "--- Student Directory ---\n";
    inorderTraversal(root);
    cout << "-------------------------\n";
}

TreeNode* GradeManager::insertHelper(TreeNode *node, const Student &newStudent) {
    // found an empty leaf, create the node here
    if (node == nullptr) {
        return new TreeNode(newStudent);
    }

    // sort by ID
    if (newStudent.getID() < node->student.getID()) {
        node->left = insertHelper(node->left, newStudent);
    } else if (newStudent.getID() > node->student.getID()) {
        node->right = insertHelper(node->right, newStudent);
    }

    // duplicates are ignored automatically
    return node;
}

TreeNode* GradeManager::searchHelper(TreeNode *node, int id) const {
    // return if found or if we hit a dead end
    if (node == nullptr || node->student.getID() == id) {
        return node;
    }

    // navigate left or right based on ID
    if (id < node->student.getID()) {
        return searchHelper(node->left, id);
    }
    return searchHelper(node->right, id);
}

TreeNode* GradeManager::deleteHelper(TreeNode *node, int id) {
    if (node == nullptr) return node;

    // locate the node
    if (id < node->student.getID()) {
        node->left = deleteHelper(node->left, id);
    } else if (id > node->student.getID()) {
        node->right = deleteHelper(node->right, id);
    } else {
        // node found. handle cases where it has 0 or 1 child
        if (node->left == nullptr) {
            TreeNode *temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
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

TreeNode* GradeManager::findInOrderSuccessor(TreeNode *node) const {
    TreeNode *current = node;
    // go as far left as possible to find the smallest value
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

void GradeManager::inorderTraversal(TreeNode *node) const {
    if (node != nullptr) {
        inorderTraversal(node->left);
        node->student.displayStudentInfo();
        inorderTraversal(node->right);
    }
}