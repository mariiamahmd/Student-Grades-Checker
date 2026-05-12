#ifndef ASSIGNLECTURERDIALOG_H
#define ASSIGNLECTURERDIALOG_H

#include <QDialog>
#include "../src/GradeManager.hpp" // <-- Include the backend

namespace Ui {
class AssignLecturerDialog;
}

class AssignLecturerDialog : public QDialog
{
    Q_OBJECT

public:
    // Update constructor to accept backend
    explicit AssignLecturerDialog(GradeManager* backendPtr, QWidget *parent = nullptr);
    ~AssignLecturerDialog();

    // Override the OK button behavior
    void accept() override;

private:
    Ui::AssignLecturerDialog *ui;
    GradeManager* backend; // Store the database pointer
};

#endif // ASSIGNLECTURERDIALOG_H