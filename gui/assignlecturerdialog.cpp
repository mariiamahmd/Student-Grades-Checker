#include "assignlecturerdialog.h"
#include "ui_assignlecturerdialog.h"
#include <QMessageBox>

AssignLecturerDialog::AssignLecturerDialog(GradeManager* backendPtr, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AssignLecturerDialog)
    , backend(backendPtr)
{
    ui->setupUi(this);
}

AssignLecturerDialog::~AssignLecturerDialog()
{
    delete ui;
}

// ==========================================
// HANDLE THE "OK" BUTTON CLICK
// ==========================================
void AssignLecturerDialog::accept()
{
    // 1. Grab the text from your specific UI fields
    QString courseCodeStr = ui->courseCodeEdit->text().trimmed();
    QString lecturerIdStr = ui->lecturerIdEdit->text().trimmed();

    // 2. Make sure they didn't leave the boxes blank
    if (courseCodeStr.isEmpty() || lecturerIdStr.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in both the Course Code and Lecturer ID.");
        return;
    }

    // 3. Convert the typed ID into a number safely
    bool isNumber;
    int lecturerId = lecturerIdStr.toInt(&isNumber);
    if (!isNumber) {
        QMessageBox::warning(this, "Format Error", "Lecturer ID must be a valid number!");
        return;
    }

    // 4. Find the actual objects in the database
    Course* courseToUpdate = backend->searchCourse(courseCodeStr.toStdString());
    Lecturer* lecturerToAssign = backend->searchLecturer(lecturerId);

    // 5. Verify the Course exists
    if (courseToUpdate == nullptr) {
        QMessageBox::critical(this, "Not Found", "Could not find Course: " + courseCodeStr);
        return;
    }

    // 6. Verify the Lecturer exists
    if (lecturerToAssign == nullptr) {
        QMessageBox::critical(this, "Not Found", "Could not find Lecturer ID: " + lecturerIdStr);
        return;
    }

    // 7. If both exist, make the assignment!
    courseToUpdate->setAssignedLecturer(lecturerToAssign);
    QMessageBox::information(this, "Success", "Lecturer assigned successfully to " + courseCodeStr + "!");

    // Close the dialog
    QDialog::accept();
}