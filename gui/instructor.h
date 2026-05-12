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
    void on_btn_assignLecturer_clicked();
    void on_btn_addStudent_clicked();

    // --- ADDED: Handlers for the new Student operations ---
    void on_btn_searchStudent_clicked();
    void on_btn_updateStudent_clicked();
    void on_btn_deleteStudent_clicked();

    void filterStudentsTable(const QString &searchText);

    void on_btn_addLecturer_clicked();
    void on_btn_deleteLecturer_clicked();
    void on_btn_updateLecturer_clicked();

    void on_lineEdit_SearchLec_textChanged(const QString &text);

    // NEW SLOTS FOR THE COURSES TAB
    void on_lineEdit_Search_textChanged(const QString &arg1); // Live Search
    void on_btn_deleteCourse_clicked(); // Make sure this matches your UI button name!
    void on_btn_updateCourse_clicked(); // Make sure this matches your UI button name!
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