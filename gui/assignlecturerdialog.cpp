#include "assignlecturerdialog.h"
#include "ui_assignlecturerdialog.h"

AssignLecturerDialog::AssignLecturerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AssignLecturerDialog)
{
    ui->setupUi(this);
}

AssignLecturerDialog::~AssignLecturerDialog()
{
    delete ui;
}
