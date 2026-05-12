#pragma once
#include <QDialog>
#include "../src/GradeManager.hpp"

namespace Ui { class DeleteStudentDialog; }

class DeleteStudentDialog : public QDialog {
    Q_OBJECT

public:
    explicit DeleteStudentDialog(GradeManager* manager, QWidget *parent = nullptr);
    ~DeleteStudentDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DeleteStudentDialog *ui;
    GradeManager* gradeManager;
};