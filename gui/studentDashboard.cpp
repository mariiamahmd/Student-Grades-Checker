#include "studentdashboard.h"
#include "ui_studentdashboard.h"
#include "mainwindow.h"
#include <QTableWidgetItem>
#include <QString>

StudentDashboard::StudentDashboard(Student* student, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StudentDashboard)
    , currentStudent(student)
{
    ui->setupUi(this);

    // 2. Safety check: If for some reason the student is null, don't crash
    if (currentStudent) {
        this->setWindowTitle("Dashboard - " + QString::fromStdString(currentStudent->getName()));
        loadStudentData();
    }
}


StudentDashboard::~StudentDashboard()
{
    delete ui;
}

void StudentDashboard::loadStudentData()
{
    if(currentStudent == nullptr)
        return;

    // Basic info
    ui->labelName->setText(QString::fromStdString(currentStudent->getName()));
    ui->labelID->setText(QString::number(currentStudent->getID()));
    ui->labelCGPA->setText(QString::number(currentStudent->calculateCumulativeGPA(), 'f', 2));
    ui->labelHours->setText(QString::number(currentStudent->getTotalCreditHours()));

    // Academic history table - UPDATED FOR COURSERECORD SYSTEM
    const auto& history = currentStudent->getRegisteredCourses();

    ui->historyTable->setRowCount(history.size());
    ui->historyTable->setColumnCount(3); // Code, Semester, Grade
    ui->historyTable->setHorizontalHeaderLabels({"Course", "Semester", "Grade"});

    for(int i = 0; i < (int)history.size(); i++)
    {
        // 1. Semester Column
        QString termStr;
        switch(history[i].semester)
        {
        case Term::Fall:   termStr = "Fall"; break;
        case Term::Spring: termStr = "Spring"; break;
        case Term::Summer: termStr = "Summer"; break;
        default:           termStr = "Unknown";
        }

        // 2. Course Code Column
        ui->historyTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(history[i].courseCode)));

        // 3. Semester Column
        ui->historyTable->setItem(i, 1, new QTableWidgetItem(termStr));

        // 4. Grade Column (Handle "In Progress" courses which have a grade of -1.0)
        float gpa = history[i].grade;
        QString gradeStr = (gpa < 0) ? "In Progress" : QString::number(gpa, 'f', 2);
        ui->historyTable->setItem(i, 2, new QTableWidgetItem(gradeStr));
    }
}