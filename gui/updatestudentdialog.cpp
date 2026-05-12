#include "updatestudentdialog.h"
#include "ui_updatestudentdialog.h"
#include <QMessageBox>

UpdateStudentDialog::UpdateStudentDialog(GradeManager* manager, QWidget *parent) :
    QDialog(parent), ui(new Ui::UpdateStudentDialog), gradeManager(manager) {
    ui->setupUi(this);
}

UpdateStudentDialog::~UpdateStudentDialog() {
    delete ui;
}

// ----------------------------------------------------
// ACTION 1: Register for a new course
// ----------------------------------------------------
void UpdateStudentDialog::on_btnRegister_clicked() {
    bool okId;
    int id = ui->inputId->text().toInt(&okId);
    std::string courseCode = ui->inputRegCode->text().toStdString();
    int credits = ui->spinCredits->value();

    // Map the combo box selection to your Term enum
    // (Assuming 0 = Fall, 1 = Spring, 2 = Summer in your Types.hpp)
    Term selectedTerm = static_cast<Term>(ui->comboTerm->currentIndex());

    if (!okId || courseCode.empty()) {
        QMessageBox::warning(this, "Error", "Please enter a valid Student ID and Course Code.");
        return;
    }

    bool success = gradeManager->registerStudentForCourse(id, courseCode, selectedTerm, credits);

    if (success) {
        QMessageBox::information(this, "Success", "Student successfully registered for " + QString::fromStdString(courseCode) + ".");
        ui->inputRegCode->clear();
    } else {
        QMessageBox::warning(this, "Error", "Student ID not found in the system.");
    }
}

// ----------------------------------------------------
// ACTION 2: Assign a final grade
// ----------------------------------------------------
void UpdateStudentDialog::on_btnGrade_clicked() {
    bool okId;
    int id = ui->inputId->text().toInt(&okId);
    std::string courseCode = ui->inputGradeCode->text().toStdString();
    float grade = ui->spinGrade->value();

    if (!okId || courseCode.empty()) {
        QMessageBox::warning(this, "Error", "Please enter a valid Student ID and Course Code.");
        return;
    }

    bool success = gradeManager->gradeStudentCourse(id, courseCode, grade);

    if (success) {
        QMessageBox::information(this, "Success", "Grade successfully updated for " + QString::fromStdString(courseCode) + ".");
        ui->inputGradeCode->clear();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update. Verify the Student ID is correct and the student is actually registered for this course.");
    }
}