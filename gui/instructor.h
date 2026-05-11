#pragma once

#include <QWidget>
#include "..\src\GradeManager.hpp"
QT_BEGIN_NAMESPACE
namespace Ui { class Instructor; }
QT_END_NAMESPACE

class Instructor : public QWidget
{
    Q_OBJECT

public:
    explicit Instructor(QWidget *parent = nullptr);
    ~Instructor();

    void setGradeManager(GradeManager* manager);
private slots:
    void on_btn_addCourse_clicked();
    void on_btn_addLecturer_clicked();

private:
    Ui::Instructor *ui;

    GradeManager* gradeManager; // contains all students

    // loading report data in ui
    void loadTopStudentsReport();
    void loadPassFailReport();
    void loadGradeDistribution();

    void setupCoursesTable();
    void setupLecturersTable();
};