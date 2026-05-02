#include "addcoursedialog.h"
#include "ui_addcoursedialog.h"

AddCourseDialog::AddCourseDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddCourseDialog)
{
    ui->setupUi(this);
}

AddCourseDialog::~AddCourseDialog()
{
    delete ui;
}
