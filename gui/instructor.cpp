#include "instructor.h"
#include "ui_instructor.h"
#include "addcoursedialog.h"
#include "../src/GradeManager.hpp"

#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>
#include <algorithm> // Needed for std::sort

// Update constructor to accept the backend pointer
Instructor::Instructor(GradeManager* backendPtr, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Instructor)
    , backend(backendPtr) // <-- Save the database reference
{
    ui->setupUi(this);

    // ==========================================
    // 1. Sidebar Navigation Logic
    // ==========================================
    connect(ui->btn_studentP, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->Studentpage);
        setWindowTitle("Students Dashboard");
    });
    connect(ui->btn_lecturerP, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->LecturerPage);
        setWindowTitle("Lecturers Dashboard");
    });
    connect(ui->btn_coursesP, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->CoursesPage);
        setWindowTitle("Courses Dashboard");
    });
    connect(ui->btn_reportsP, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->ReportsPage);
        setWindowTitle("Reports Dashboard");
    });

    // Report Sub-navigation
    connect(ui->btn_top, &QPushButton::clicked, this, [this]() {
        ui->reportstack->setCurrentWidget(ui->topstudentP);
        
        // <-- NEW: Trigger the sorting and UI population when tab opens
        populateTopStudentsReport(); 
    });
    connect(ui->btn_pass, &QPushButton::clicked, this, [this]() {
        ui->reportstack->setCurrentWidget(ui->passfaillp);
    });
    connect(ui->btn_grade, &QPushButton::clicked, this, [this]() {
        ui->reportstack->setCurrentWidget(ui->gradedis);
    });

    // ==========================================
    // 2. Tab UI Connections
    // ==========================================
    
    // Connect Buttons
    connect(ui->btn_addCourse, &QPushButton::clicked, this, &Instructor::on_btn_addCourse_clicked);
    connect(ui->btn_addLecturer, &QPushButton::clicked, this, &Instructor::on_btn_addLecturer_clicked);
    connect(ui->btn_addStudent, &QPushButton::clicked, this, &Instructor::on_btn_addStudent_clicked);

    // Run Visual Setups
    setupCoursesTable();
    setupLecturersTable();
    setupStudentsTable();
}

Instructor::~Instructor()
{
    delete ui;
}

// ==========================================
// 3. UI Setup Functions
// ==========================================

void Instructor::setupCoursesTable()
{
    // FORCE LIGHT MODE COLORS FOR COURSES TAB
    ui->lineEdit_Search->setStyleSheet(
        "QLineEdit {"
        "  color: #111827;" 
        "  background-color: #f9fafb;"
        "  border: 1px solid #e5e7eb;"
        "  border-radius: 5px;"
        "  padding: 8px;"
        "}"
    );

    ui->coursesTable->setStyleSheet(
        "QTableWidget { background-color: white; color: #374151; gridline-color: #f3f4f6; border: none; }"
        "QTableWidget::viewport { background-color: white; }"
        "QHeaderView::section { background-color: white; color: #111827; font-weight: bold; border: none; border-bottom: 2px solid #e5e7eb; }"
        "QTableWidget::item { background-color: white; color: #111827; }"
        "QTableWidget::item:selected { background-color: #eff6ff; color: #1d4ed8; }"
    );

    // Table settings
    ui->coursesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->coursesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Dummy data
    ui->coursesTable->setRowCount(1);
    ui->coursesTable->setItem(0, 0, new QTableWidgetItem("CSE333"));
    ui->coursesTable->setItem(0, 1, new QTableWidgetItem("Data Structures"));
    ui->coursesTable->setItem(0, 2, new QTableWidgetItem("3"));
    ui->coursesTable->setItem(0, 3, new QTableWidgetItem("Unassigned"));
    
    ui->label_TableTitle->setText("All Courses (Total: 1)");
    ui->label_Showing->setText("Showing 1 to 1 of 1 courses");
}

void Instructor::setupLecturersTable()
{
    // Stretch columns to fill space
    ui->lecturersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->lecturersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Add dummy data row
    ui->lecturersTable->setRowCount(1);
    ui->lecturersTable->setItem(0, 0, new QTableWidgetItem("101"));
    ui->lecturersTable->setItem(0, 1, new QTableWidgetItem("Dr. Ahmed Raza"));
    ui->lecturersTable->setItem(0, 2, new QTableWidgetItem("Computer Science"));
    
    // Update labels
    ui->label_LecTableTitle->setText("All Lecturers (Total: 1)");
    ui->label_ShowingLec->setText("Showing 1 to 1 of 1 lecturers");
}

void Instructor::setupStudentsTable()
{
    // 1. Force Light Mode Colors
    ui->lineEdit_SearchStu->setStyleSheet(
        "QLineEdit { color: #111827; background-color: #f9fafb; border: 1px solid #e5e7eb; border-radius: 5px; padding: 8px; }"
    );
    ui->studentsTable->setStyleSheet(
        "QTableWidget { background-color: white; color: #374151; gridline-color: #f3f4f6; border: none; }"
        "QTableWidget::viewport { background-color: white; }"
        "QHeaderView::section { background-color: white; color: #111827; font-weight: bold; border: none; border-bottom: 2px solid #e5e7eb; }"
        "QTableWidget::item { background-color: white; color: #111827; }"
        "QTableWidget::item:selected { background-color: #eff6ff; color: #1d4ed8; }"
    );

    // 2. Format columns
    ui->studentsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->studentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 3. DYNAMIC DATA INTEGRATION
    std::vector<Student*> allStudents = backend->getAllStudents();
    ui->studentsTable->setRowCount(allStudents.size());
    
    for (size_t i = 0; i < allStudents.size(); ++i) {
        Student* s = allStudents[i];
        QString gpaStr = QString::number(s->calculateCumulativeGPA(), 'f', 2);
        
        ui->studentsTable->setItem(i, 0, new QTableWidgetItem(QString::number(s->getID())));
        ui->studentsTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(s->getName())));
        ui->studentsTable->setItem(i, 2, new QTableWidgetItem("General")); // Placeholder for Dept
        ui->studentsTable->setItem(i, 3, new QTableWidgetItem(gpaStr));
        ui->studentsTable->setItem(i, 4, new QTableWidgetItem("Active"));
    }
}

// ==========================================
// 4. Report Integration
// ==========================================
void Instructor::populateTopStudentsReport()
{
    // 1. Get the flat list of pointers from the BST
    std::vector<Student*> students = backend->getAllStudents();

    // 2. Sort the vector by cGPA in Descending order (Highest first)
    std::sort(students.begin(), students.end(), [](Student* a, Student* b) {
        return a->calculateCumulativeGPA() > b->calculateCumulativeGPA();
    });

    // 3. Determine how many to show (e.g., Top 10)
    int displayCount = std::min((int)students.size(), 10);

    // 4. Set up the UI Table 
    // IMPORTANT: Make sure your QTableWidget in the .ui file for this page is named 'tableWidget'
    ui->tableWidget->setRowCount(displayCount);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 5. Populate the rows
    for (int i = 0; i < displayCount; ++i) {
        Student* s = students[i];
        QString gpaString = QString::number(s->calculateCumulativeGPA(), 'f', 2);

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1))); // Rank
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(s->getID())));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(s->getName())));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem("General"));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(gpaString));
    }
}

// ==========================================
// 5. Button Click Events
// ==========================================

void Instructor::on_btn_addCourse_clicked()
{
    AddCourseDialog dialog(this);
    dialog.exec(); 
}

void Instructor::on_btn_addLecturer_clicked()
{
    QMessageBox::information(this, "Coming Soon", "The Add Lecturer dialog will open here!");
}

void Instructor::on_btn_addStudent_clicked()
{
    QMessageBox::information(this, "Coming Soon", "The Add Student dialog will open here!");
}