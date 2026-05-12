#include "searchstudentdialog.h"
#include "ui_searchstudentdialog.h"
#include <QString>

SearchStudentDialog::SearchStudentDialog(GradeManager* manager, QWidget *parent) :
    QDialog(parent), ui(new Ui::SearchStudentDialog), gradeManager(manager) {
    ui->setupUi(this);
}

SearchStudentDialog::~SearchStudentDialog() {
    delete ui;
}

void SearchStudentDialog::on_btnSearch_clicked() {
    bool ok;
    int id = ui->inputId->text().toInt(&ok);

    // Defense: Validate input
    if (!ok) {
        ui->textResult->setText("❌ Error: Please enter a valid numeric ID.");
        return;
    }

    // Call your O(log n) BST search function!
    Student* found = gradeManager->searchStudent(id);

    if (found) {
        QString info = QString("✅ Student Found!\n\nName: %1\nID: %2\nTotal Credits: %3\nCumulative GPA: %4")
                           .arg(QString::fromStdString(found->getName()))
                           .arg(found->getID())
                           .arg(found->getTotalCreditHours())
                           .arg(found->calculateCumulativeGPA());

        ui->textResult->setText(info);
    } else {
        ui->textResult->setText("❌ Student not found in the database.");
    }
}