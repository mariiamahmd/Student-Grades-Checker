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
    void on_btn_addCourse_clicked();
    void on_btn_addLecturer_clicked();

private:
    Ui::Instructor *ui;
    
    void setupCoursesTable();
    void setupLecturersTable();
};