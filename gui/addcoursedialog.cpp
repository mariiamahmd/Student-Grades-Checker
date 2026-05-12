#include "addcoursedialog.h"
#include "ui_addcoursedialog.h" // Matches your UI file
#include <QMessageBox>

AddCourseDialog::AddCourseDialog(GradeManager* backendPtr, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddCourseDialog)
    , backend(backendPtr)
{
    ui->setupUi(this);
}

AddCourseDialog::~AddCourseDialog()
{
    delete ui;
}

// This function intercepts the "OK" button click from your QDialogButtonBox!
void AddCourseDialog::accept()
{
    // 1. Grab the text using the exact names from your XML file
    std::string code = ui->lineEdit_code->text().toStdString();
    std::string name = ui->lineEdit_name->text().toStdString();
    int credits = ui->spinBox_credits->value();

    // 2. Validate the input
    if (code.empty() || name.empty() || credits <= 0) {
        QMessageBox::warning(this, "Input Error", "Please fill out all fields correctly.");
        return; // Stops here, dialog stays open so they can fix it
    }

    // 3. Check if the course already exists in the Hash Map
    if (backend->searchCourse(code) != nullptr) {
        QMessageBox::warning(this, "Duplicate Error", "A course with this code already exists!");
        return; // Stops here
    }

    // 4. Create the new course and add it to the backend
    Course* newCourse = new Course(credits, code, name, nullptr);
    backend->addCourse(newCourse);

    QMessageBox::information(this, "Success", "Course added successfully!");

    // 5. Finally, call the base class accept() to actually close the pop-up window
    QDialog::accept();
}