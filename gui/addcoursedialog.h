#ifndef ADDCOURSEDIALOG_H
#define ADDCOURSEDIALOG_H

#include <QDialog>
#include "../src/GradeManager.hpp"

namespace Ui {
class AddCourseDialog;
}

class AddCourseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCourseDialog(GradeManager* backendPtr, QWidget *parent = nullptr);
    ~AddCourseDialog();

    // <-- NEW: We override the default "OK" button behavior
    void accept() override;

private:
    Ui::AddCourseDialog *ui;
    GradeManager* backend;
};

#endif // ADDCOURSEDIALOG_H