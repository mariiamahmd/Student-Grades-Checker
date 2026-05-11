#include "instructor.h"
#include "ui_instructor.h"
#include "addcoursedialog.h" 
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>

Instructor::Instructor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Instructor)
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

    // Run Visual Setups
    setupCoursesTable();
    setupLecturersTable();
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
    // ==========================================
    // FORCE LIGHT MODE COLORS FOR COURSES TAB
    // ==========================================
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
    // ==========================================

    // Your existing setup code continues here...
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

// ==========================================
// 4. Button Click Events
// ==========================================

void Instructor::on_btn_addCourse_clicked()
{
    AddCourseDialog dialog(this);
    dialog.exec(); 
}

void Instructor::on_btn_addLecturer_clicked()
{
    // Placeholder pop-up until you build AddLecturerDialog
    QMessageBox::information(this, "Coming Soon", "The Add Lecturer dialog will open here!");
}