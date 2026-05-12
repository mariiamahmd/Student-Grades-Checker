#include "addstudentdialog.h"
#include "ui_addstudentdialog.h"
#include <QMessageBox>

AddStudentDialog::AddStudentDialog(GradeManager* manager, QWidget *parent) :
    QDialog(parent), ui(new Ui::AddStudentDialog), gradeManager(manager) {
    ui->setupUi(this);
}

AddStudentDialog::~AddStudentDialog() {
    delete ui;
}

void AddStudentDialog::on_buttonBox_accepted() {
    bool ok;
    int id = ui->inputId->text().toInt(&ok);
    std::string name = ui->inputName->text().toStdString();

    // Defense: التأكد من صحة البيانات
    if (!ok || name.empty()) {
        QMessageBox::warning(this, "Error", "Please enter a valid ID and Name.");
        return;
    }

    // Defense: التأكد إن الطالب مش موجود قبل كدا
    if (gradeManager->searchStudent(id) != nullptr) {
        QMessageBox::warning(this, "Error", "A student with this ID already exists!");
        return;
    }

    // إرسال البيانات للـ BST
    gradeManager->addStudent(id, name);
    QMessageBox::information(this, "Success", "Student Added Successfully!");
    accept(); // قفل النافذة
}