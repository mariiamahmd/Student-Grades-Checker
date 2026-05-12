#pragma once
#include <QDialog>
#include "../src/GradeManager.hpp" // Ensure this path correctly points to your backend

namespace Ui { class SearchStudentDialog; }

class SearchStudentDialog : public QDialog {
    Q_OBJECT

public:
    explicit SearchStudentDialog(GradeManager* manager, QWidget *parent = nullptr);
    ~SearchStudentDialog();

private slots:
    void on_btnSearch_clicked();

private:
    Ui::SearchStudentDialog *ui;
    GradeManager* gradeManager; // Your BST connection
};