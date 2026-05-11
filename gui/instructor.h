#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <QWidget>

#include "..\src\GradeManager.hpp"

#include <vector>

// Forward declaration of GradeManager so we don't have to include
// the heavy backend header in this small header file.
class GradeManager;

QT_BEGIN_NAMESPACE
namespace Ui { class Instructor; }
QT_END_NAMESPACE

class Instructor : public QWidget
{
    Q_OBJECT

public:
    // Updated constructor to accept the backend database pointer
    explicit Instructor(GradeManager* backendPtr, QWidget *parent = nullptr);
    ~Instructor();


private slots:
    // Button click handlers
    void on_btn_addCourse_clicked();
    void on_btn_addLecturer_clicked();
    void on_btn_addStudent_clicked();

private:
    Ui::Instructor *ui;

    // Pointer to the backend database instance
    GradeManager* backend;


    // loading report data in ui
    void loadTopStudentsReport();
    void loadPassFailReport();
    void loadGradeDistribution();



    // UI Setup and Logic Functions

    void setupCoursesTable();
    void setupLecturersTable();
    void setupStudentsTable();

    // Logic for generating the Top Students report
    void populateTopStudentsReport();
};

#endif // INSTRUCTOR_H