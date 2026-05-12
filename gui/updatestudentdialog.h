#pragma once
#include <QDialog>
#include "../src/GradeManager.hpp"

namespace Ui { class UpdateStudentDialog; }

class UpdateStudentDialog : public QDialog {
    Q_OBJECT

public:
    explicit UpdateStudentDialog(GradeManager* manager, QWidget *parent = nullptr);
    ~UpdateStudentDialog();

private slots:
    void on_btnRegister_clicked();
    void on_btnGrade_clicked();

private:
    Ui::UpdateStudentDialog *ui;
    GradeManager* gradeManager;
};