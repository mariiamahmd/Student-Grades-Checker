#include "deletestudentdialog.h"
#include "ui_deletestudentdialog.h"
#include <QMessageBox>

DeleteStudentDialog::DeleteStudentDialog(GradeManager* manager, QWidget *parent) :
    QDialog(parent), ui(new Ui::DeleteStudentDialog), gradeManager(manager) {
    ui->setupUi(this);
}

DeleteStudentDialog::~DeleteStudentDialog() {
    delete ui;
}

void DeleteStudentDialog::on_buttonBox_accepted() {
    bool ok;
    int id = ui->inputId->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid ID.");
        return;
    }

    bool success = gradeManager->deleteStudent(id);

    if (success) {
        QMessageBox::information(this, "Deleted", "Student permanently removed from the system.");
        accept();
    } else {
        QMessageBox::warning(this, "Error", "Student not found!");
    }
}