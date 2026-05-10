#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Instructor; }
QT_END_NAMESPACE

class Instructor : public QWidget
{
    Q_OBJECT

public:
    explicit Instructor(QWidget *parent = nullptr);
    ~Instructor();

private slots:
    // UI-only slot to open the pop-up dialog
    void on_btn_addCourse_clicked();

private:
    Ui::Instructor *ui;

    // Helper function to apply visual tweaks to the table
    void setupCoursesTable();
};