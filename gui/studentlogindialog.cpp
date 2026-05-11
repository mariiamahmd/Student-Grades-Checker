#include "studentlogindialog.h"
#include "ui_studentlogindialog.h"
#include <QMessageBox>

StudentLoginDialog::StudentLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentLoginDialog)
{
    ui->setupUi(this);
    
    // Connect the search button to our validation slot
    connect(ui->btn_search, &QPushButton::clicked, this, &StudentLoginDialog::on_btn_search_clicked);
}

StudentLoginDialog::~StudentLoginDialog()
{
    delete ui;
}

QString StudentLoginDialog::getEnteredID() const
{
    return ui->lineEdit_studentId->text();
}

void StudentLoginDialog::on_btn_search_clicked()
{
    QString enteredId = getEnteredID();

    // Basic Validation: Ensure they didn't leave it blank
    if (enteredId.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Student ID.");
        return;
    }

    // Later, you will check this ID against your GradeManager BST backend here!
    // For now, we just accept it and close the dialog.
    
    accept(); // This closes the dialog and returns QDialog::Accepted
}