#ifndef ASSIGNLECTURERDIALOG_H
#define ASSIGNLECTURERDIALOG_H

#include <QDialog>

namespace Ui {
class AssignLecturerDialog;
}

class AssignLecturerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AssignLecturerDialog(QWidget *parent = nullptr);
    ~AssignLecturerDialog();

private:
    Ui::AssignLecturerDialog *ui;
};

#endif // ASSIGNLECTURERDIALOG_H
