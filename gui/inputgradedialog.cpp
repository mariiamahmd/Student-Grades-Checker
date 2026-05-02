#include "inputgradedialog.h"
#include "ui_inputgradedialog.h"

InputGradeDialog::InputGradeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InputGradeDialog)
{
    ui->setupUi(this);
}

InputGradeDialog::~InputGradeDialog()
{
    delete ui;
}
