#include "mainwindow.h"
#include "ui_mainwindow.h"

// Include the headers for your pop-up windows
#include "addcoursedialog.h"
#include "assignlecturerdialog.h"
#include "inputgradedialog.h"
#include "instructor.h"
#include "studentlogindialog.h"
#include "../src/GradeManager.hpp"
#include "studentdashboard.h"
#include <QMessageBox>
#include <QPushButton>

// helper function to load data
// helper function to load data
void loadTestData(GradeManager* backend) {
    // ==========================================
    // 1. Inject Lecturers
    // ==========================================
    backend->addLecturer(new Lecturer(101, "Dr. Ahmed Raza", "Computer Science"));
    backend->addLecturer(new Lecturer(102, "Dr. Sarah Johnson", "Software Engineering"));
    backend->addLecturer(new Lecturer(103, "Dr. Tarek Amr", "Information Technology"));

    // ==========================================
    // 2. Inject Courses
    // ==========================================
    backend->addCourse(new Course(3, "CSE333", "Data Structures", backend->searchLecturer(101)));
    backend->addCourse(new Course(4, "CSE444", "Algorithms", backend->searchLecturer(102)));
    backend->addCourse(new Course(3, "SWE222", "Software Design", nullptr));

    // ==========================================
    // 3. Inject Students
    // ==========================================
    backend->addStudent(1045, "Ahmed Raza");
    backend->addStudent(1046, "Fatima Khan");
    backend->addStudent(1047, "Hassan Ali");
    backend->addStudent(1048, "Ayesha Noor");
    backend->addStudent(1049, "Usman Javed");

    // ==========================================
    // 4. Register Courses & Assign Grades (NEW SYSTEM)
    // ==========================================

    // Ahmed
    backend->registerStudentForCourse(1045, "CSE333", Term::Fall, 3);
    backend->gradeStudentCourse(1045, "CSE333", 3.8); // High grade
    backend->registerStudentForCourse(1045, "CSE444", Term::Spring, 4);
    backend->gradeStudentCourse(1045, "CSE444", 3.9);

    // Fatima
    backend->registerStudentForCourse(1046, "CSE333", Term::Fall, 3);
    backend->gradeStudentCourse(1046, "CSE333", 3.2);
    backend->registerStudentForCourse(1046, "SWE222", Term::Spring, 3);
    backend->gradeStudentCourse(1046, "SWE222", 3.5);

    // Hassan
    backend->registerStudentForCourse(1047, "CSE333", Term::Fall, 3);
    backend->gradeStudentCourse(1047, "CSE333", 2.5); // Lower grade

    // Ayesha (Top Student!)
    backend->registerStudentForCourse(1048, "CSE444", Term::Fall, 4);
    backend->gradeStudentCourse(1048, "CSE444", 4.0);
    backend->registerStudentForCourse(1048, "SWE222", Term::Spring, 3);
    backend->gradeStudentCourse(1048, "SWE222", 4.0);

    // Usman
    backend->registerStudentForCourse(1049, "SWE222", Term::Fall, 3);
    backend->gradeStudentCourse(1049, "SWE222", 3.1);
}

MainWindow::MainWindow(GradeManager* manager, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    backend(manager) // <-- This saves the pointer to the class variable 'backend'
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
    ui->mainStack->setCurrentIndex(0);

    // If main.cpp didn't give us a database, create one!
    if (backend == nullptr) {
        backend = new GradeManager();
    }

    // FIXED: Actually call the function to load the mock data!
    loadTestData(backend);


    // ==========================================
    // 1. ROLE SELECTION (The Welcome Screen)
    // ==========================================

    // INSTRUCTOR LOGIN
    connect(ui->btn_instructor, &QPushButton::clicked, this, [=](){

        // FIXED: Pass 'nullptr' so it opens as an independent window!
        Instructor *ins = new Instructor(backend, nullptr);
        ins->setAttribute(Qt::WA_DeleteOnClose); // Cleans up memory when closed
        ins->show();

        this->hide();
    });

    // STUDENT LOGIN
    connect(ui->btn_student, &QPushButton::clicked, this, [=]() {

        // Keep 'this' for the dialog so it stays centered on the welcome screen
        StudentLoginDialog* loginDialog = new StudentLoginDialog(backend, this);

        if (loginDialog->exec() == QDialog::Accepted) {
            Student* student = loginDialog->getLoggedStudent();

            // FIXED: Pass 'nullptr' to the dashboard so it opens independently!
            StudentDashboard* dashboard = new StudentDashboard(student, nullptr);
            dashboard->setAttribute(Qt::WA_DeleteOnClose);
            dashboard->show();

            this->hide();
        }
        delete loginDialog;
    });

    // ==========================================
    // 2. LECTURER SIDEBAR NAVIGATION (Legacy View)
    // ==========================================
    connect(ui->sidebarMenu, &QListWidget::currentRowChanged,
            ui->lecturerPanes, &QStackedWidget::setCurrentIndex);

    ui->sidebarMenu->setCurrentRow(0); // Default to first tab

    // ==========================================
    // 3. LECTURER DASHBOARD BUTTON CONNECTIONS
    // ==========================================

    // FIXED: Pass 'backend' into your handlers
    connect(ui->btnOpenAddCourse, &QPushButton::clicked, this, [=]() {
        handleAddCourse(backend);
    });

    connect(ui->btnOpenInputGrade, &QPushButton::clicked, this, [=]() {
        handleRecordGrade(backend);
    });

    connect(ui->btnOpenAssginLecturer, &QPushButton::clicked, this, [=]() {
        AssignLecturerDialog dialog(backend, this);
        if (dialog.exec() == QDialog::Accepted) {
            // Success handled internally
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

void MainWindow::onLecturerTabChanged(int index)
{
}

// Notice we updated this to receive the GradeManager pointer!
void MainWindow::handleAddCourse(GradeManager* backend) {
    // FIXED: Pass 'backend' as the first argument!
    AddCourseDialog dialog(backend, this);

    if (dialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Success", "Course Added to Hash Table!");
    }
}

void MainWindow::handleRecordGrade(GradeManager* backend) {
    // Note: If you haven't updated InputGradeDialog's constructor yet,
    // leave this as dialog(this) until we fix that file, otherwise it will throw the same error!

    InputGradeDialog dialog(this); // (We will change this to (backend, this) soon!)
    if (dialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Success", "Student Grade Recorded!");
    }
}