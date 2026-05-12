#pragma once
#include <QDialog>
#include "../src/GradeManager.hpp" // مسار الـ BST بتاعك

namespace Ui { class AddStudentDialog; }

class AddStudentDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddStudentDialog(GradeManager* manager, QWidget *parent = nullptr);
    ~AddStudentDialog();

private slots:
    void on_buttonBox_accepted(); // لما المستخدم يدوس Save

private:
    Ui::AddStudentDialog *ui;
    GradeManager* gradeManager;
};