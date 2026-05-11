#include "mainwindow.h"
#include "ui_mainwindow.h"
// Include the headers for your three pop-up windows
#include "addcoursedialog.h"
#include "assignlecturerdialog.h"
#include "inputgradedialog.h"
#include "instructor.h"
#include <QMessageBox>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_instructor, &QPushButton::clicked, this, [=](){

        Instructor *ins = new Instructor();
         ins->setGradeManager(gradeManager);
        ins->show();

    });
    this->setStyleSheet(R"(
    QWidget { background-color: white; }
    QFrame { background-color: white; border-radius: 12px; }
)");
    // ==========================================
    // 0. STARTUP STATE
    // ==========================================
    // Force the app to open on the Welcome Screen (Index 0 of mainStack)
    ui->mainStack->setCurrentIndex(0);


    // ==========================================
    // 1. ROLE SELECTION (The Welcome Screen)
    // ==========================================
    // Click "I am a Student" -> switch mainStack to page_2 (Index 1)
    connect(ui->btn_student, &QPushButton::clicked, this, [this]() {
        ui->mainStack->setCurrentIndex(1);
    });

    // Logout Button (Inside Lecturer View) -> switch back to Welcome Screen (Index 0)
    connect(ui->btn_instructor, &QPushButton::clicked, this, [this]() {
        ui->mainStack->setCurrentWidget(ui->page_5);
    });


    // ==========================================
    // 2. LECTURER SIDEBAR NAVIGATION
    // ==========================================
    // Links sidebar clicks to the lecturerPanes stacked widget
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
    // Kept empty to satisfy compiler if it's still in your header
}
void MainWindow::setGradeManager(GradeManager* manager)
{
    gradeManager = manager;
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


