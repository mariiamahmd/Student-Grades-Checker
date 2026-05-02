#include "mainwindow.h"
#include "ui_mainwindow.h"

// Include the headers for your three pop-up windows
#include "addcoursedialog.h"
#include "assignlecturerdialog.h"
#include "inputgradedialog.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ==========================================
    // 0. STARTUP STATE
    // ==========================================
    // Force the app to open on the Welcome Screen (Index 0 of mainStack)
    ui->mainStack->setCurrentIndex(0);


    // ==========================================
    // 1. ROLE SELECTION (The Welcome Screen)
    // ==========================================
    // Click "I am a Student" -> switch mainStack to page_2 (Index 1)
    connect(ui->studentBtn, &QPushButton::clicked, this, [this]() {
        ui->mainStack->setCurrentIndex(1);
    });

    // Click "I am a Lecturer" -> switch mainStack to page_3 (Index 2)
    connect(ui->lecturerBtn, &QPushButton::clicked, this, [this]() {
        ui->mainStack->setCurrentIndex(2);
    });

    // Logout Button (Inside Lecturer View) -> switch back to Welcome Screen (Index 0)
    connect(ui->lecturerLogoutBtn, &QPushButton::clicked, this, [this]() {
        ui->mainStack->setCurrentIndex(0);
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

void MainWindow::onRoleSelected(int index) {
    // Kept empty to satisfy compiler if it's still in your header
}

void MainWindow::onLecturerTabChanged(int index) {
    // Kept empty to satisfy compiler if it's still in your header
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