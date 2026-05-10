#include "instructor.h"
#include "ui_instructor.h"
#include "addcoursedialog.h" // Make sure this file exists in your project!
#include <QTableWidgetItem>
#include <QHeaderView>

Instructor::Instructor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Instructor)
{
    ui->setupUi(this);

    // ==========================================
    // 1. Sidebar Navigation Logic (Your code)
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

    connect(ui->btn_top, &QPushButton::clicked, this, [this]() {
        ui->reportstack->setCurrentWidget(ui->topstudentP);
    });

    connect(ui->btn_pass, &QPushButton::clicked, this, [this]() {
        ui->reportstack->setCurrentWidget(ui->passfaillp);
    });

    connect(ui->btn_grade, &QPushButton::clicked, this, [this]() {
        ui->reportstack->setCurrentWidget(ui->gradedis);
    });

    // 1. Force the Search LineEdit to have dark text and a light background
    ui->lineEdit_Search->setStyleSheet(
        "QLineEdit {"
        "  color: #111827;"
        "  background-color: #f9fafb;"
        "  border: 1px solid #e5e7eb;"
        "  border-radius: 5px;"
        "  padding: 8px;"
        "}"
        );

    // 2. Force the Table to be white with dark text
    ui->coursesTable->setStyleSheet(
        "QTableWidget {"
        "  background-color: white;"
        "  color: #374151;"
        "  gridline-color: #f3f4f6;"
        "  border: none;"
        "}"
        "QTableWidget::viewport {"
        "  background-color: white;"
        "}"
        "QHeaderView::section {"
        "  background-color: white;"
        "  color: #111827;"
        "  font-weight: bold;"
        "  border: none;"
        "  border-bottom: 2px solid #e5e7eb;"
        "}"
        );

    // ==========================================
    // 2. Courses Tab UI Connections
    // ==========================================

    // Connect the Add Course button to open the pop-up window
    connect(ui->btn_addCourse, &QPushButton::clicked, this, &Instructor::on_btn_addCourse_clicked);

    // Run the visual setup for the table
    setupCoursesTable();
}

Instructor::~Instructor()
{
    delete ui;
}

// ==========================================
// 3. Courses Tab UI Functions
// ==========================================

void Instructor::setupCoursesTable()
{
    // Make the table columns stretch to fill the empty white space
    ui->coursesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Make the table read-only so users can't type directly into the cells
    ui->coursesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // --- Add a dummy row just so you can see the UI styling! ---
    ui->coursesTable->setRowCount(1);
    ui->coursesTable->setItem(0, 0, new QTableWidgetItem("CSE333"));
    ui->coursesTable->setItem(0, 1, new QTableWidgetItem("Data Structures"));
    ui->coursesTable->setItem(0, 2, new QTableWidgetItem("3"));
    ui->coursesTable->setItem(0, 3, new QTableWidgetItem("Unassigned"));

    // Update the visual labels to match our 1 row of dummy data
    ui->label_TableTitle->setText("All Courses (Total: 1)");
    ui->label_Showing->setText("Showing 1 to 1 of 1 courses");
}

void Instructor::on_btn_addCourse_clicked()
{
    // 1. Create the dialog window
    AddCourseDialog dialog(this);

    // 2. Show it to the user. Since we have no backend right now,
    // it will just open, look pretty, and close when they click OK/Cancel!
    dialog.exec();
}