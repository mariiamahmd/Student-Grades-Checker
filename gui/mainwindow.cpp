#include "mainwindow.h"
#include "ui_mainwindow.h"

// Include the headers for your pop-up windows
#include "addcoursedialog.h"
#include "assignlecturerdialog.h"
#include "inputgradedialog.h"
#include "instructor.h"
#include "studentlogindialog.h"
#include "../src/GradeManager.hpp"

#include <QMessageBox>
#include <QPushButton>

// helper function to load data
void loadTestData(GradeManager* backend) {
    // Inject Students
    backend->addStudent(1045, "Ahmed Raza");
    backend->addStudent(1046, "Fatima Khan");
    backend->addStudent(1047, "Hassan Ali");
    backend->addStudent(1048, "Ayesha Noor");
    backend->addStudent(1049, "Usman Javed");

    // ==========================================
    // Inject Courses & Grades to create different cGPAs
    // ==========================================

    // Ahmed (High GPA ~ 3.85)
    backend->registerStudentForCourse(1045, "CSE101", Term::Fall, 3);
    backend->gradeStudentCourse(1045, "CSE101", 3.8);
    backend->registerStudentForCourse(1045, "MAT101", Term::Spring, 3);
    backend->gradeStudentCourse(1045, "MAT101", 3.9);

    // Fatima (Medium GPA ~ 3.35)
    backend->registerStudentForCourse(1046, "CSE101", Term::Fall, 3);
    backend->gradeStudentCourse(1046, "CSE101", 3.2);
    backend->registerStudentForCourse(1046, "MAT101", Term::Spring, 3);
    backend->gradeStudentCourse(1046, "MAT101", 3.5);

    // Hassan (Lower GPA ~ 2.7)
    backend->registerStudentForCourse(1047, "CSE101", Term::Fall, 3);
    backend->gradeStudentCourse(1047, "CSE101", 2.5);
    backend->registerStudentForCourse(1047, "MAT101", Term::Spring, 3);
    backend->gradeStudentCourse(1047, "MAT101", 2.9);

    // Ayesha (Top Student! ~ 3.95)
    backend->registerStudentForCourse(1048, "CSE101", Term::Fall, 3);
    backend->gradeStudentCourse(1048, "CSE101", 4.0);
    backend->registerStudentForCourse(1048, "MAT101", Term::Spring, 3);
    backend->gradeStudentCourse(1048, "MAT101", 3.9);

    // Usman (Medium GPA ~ 3.05)
    backend->registerStudentForCourse(1049, "CSE101", Term::Fall, 3);
    backend->gradeStudentCourse(1049, "CSE101", 3.1);
    backend->registerStudentForCourse(1049, "MAT101", Term::Spring, 3);
    backend->gradeStudentCourse(1049, "MAT101", 3.0);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Light mode override for the main window
    this->setStyleSheet(R"(
        QWidget { background-color: white; }
        QFrame { background-color: white; border-radius: 12px; }
    )");

    // ==========================================
    // 0. STARTUP STATE & DATABASE INIT
    // ==========================================
    // Force the app to open on the Welcome Screen
    ui->mainStack->setCurrentIndex(0);

    // Initialize the main backend database
    GradeManager* masterBackend = new GradeManager();

    // Load the mock data into the tree immediately
    loadTestData(masterBackend);

    // ==========================================
    // 1. ROLE SELECTION (The Welcome Screen)
    // ==========================================

    // INSTRUCTOR LOGIN
    connect(ui->btn_instructor, &QPushButton::clicked, this, [=](){
        // Open the Instructor Dashboard AND pass the backend to it!
        Instructor *ins = new Instructor(masterBackend);
        ins->show();

        // Optional: you can hide the main window here if you want using this->hide();
    });

    // STUDENT LOGIN
    connect(ui->btn_student, &QPushButton::clicked, this, [this, masterBackend]() {
        StudentLoginDialog loginDialog(this);

        if (loginDialog.exec() == QDialog::Accepted) {
            QString studentIdStr = loginDialog.getEnteredID();
            int id = studentIdStr.toInt();

            // Check if student actually exists in the database before logging in
            if (masterBackend->searchStudent(id) != nullptr) {
                QMessageBox::information(this, "Login Successful", "Welcome to your dashboard, Student ID: " + studentIdStr);
                ui->mainStack->setCurrentIndex(1);
            } else {
                QMessageBox::warning(this, "Login Failed", "Student ID not found in the system.");
            }
        }
    });

    // ==========================================
    // 2. LECTURER SIDEBAR NAVIGATION (Legacy/Alternative View)
    // ==========================================
    connect(ui->sidebarMenu, &QListWidget::currentRowChanged,
            ui->lecturerPanes, &QStackedWidget::setCurrentIndex);

    ui->sidebarMenu->setCurrentRow(0); // Default to first tab

    // ==========================================
    // 3. LECTURER DASHBOARD BUTTON CONNECTIONS
    // ==========================================
    connect(ui->btnOpenAddCourse, &QPushButton::clicked, this, &MainWindow::handleAddCourse);
    connect(ui->btnOpenInputGrade, &QPushButton::clicked, this, &MainWindow::handleRecordGrade);

    // Assign Lecturer Pop-up
    connect(ui->btnOpenAssginLecturer, &QPushButton::clicked, this, [this]() {
        AssignLecturerDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            QMessageBox::information(this, "Success", "Lecturer Assigned Successfully!");
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ==========================================
// 4. THE SLOT IMPLEMENTATIONS
// ==========================================

void MainWindow::onLecturerTabChanged(int index) {
}

void MainWindow::handleAddCourse() {
    AddCourseDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Success", "Course Added to Hash Table!");
    }
}

void MainWindow::handleRecordGrade() {
    InputGradeDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Success", "Student Grade Recorded!");
    }
}