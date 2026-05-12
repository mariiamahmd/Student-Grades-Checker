#include <QApplication>
#include "gui/mainwindow.h"

#include "gui/instructor.h"
#include "src/GradeManager.hpp"
#include "src/Student.hpp"
#include "src/Lecturer.hpp"
#include "src/Course.hpp"

#include "src/Types.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GradeManager manager;

    // ==========================================
    // Add Students
    // ==========================================

    manager.addStudent(1001, "Ahmed");
    manager.addStudent(1002, "Mariam");
    manager.addStudent(1003, "Omar");
    manager.addStudent(1004, "Sara");
    manager.addStudent(1005, "Youssef");

    // ==========================================
    // Register Courses & Assign Grades
    // ==========================================

    // Ahmed (Expected CGPA ~ 3.85)
    manager.registerStudentForCourse(1001, "CSE101", Term::Fall, 3);
    manager.gradeStudentCourse(1001, "CSE101", 3.8);
    manager.registerStudentForCourse(1001, "MAT101", Term::Spring, 3);
    manager.gradeStudentCourse(1001, "MAT101", 3.9);

    // Mariam (Expected CGPA ~ 3.1)
    manager.registerStudentForCourse(1002, "CSE101", Term::Fall, 3);
    manager.gradeStudentCourse(1002, "CSE101", 3.0);
    manager.registerStudentForCourse(1002, "MAT101", Term::Spring, 3);
    manager.gradeStudentCourse(1002, "MAT101", 3.2);

    // Omar (Expected CGPA ~ 1.65)
    manager.registerStudentForCourse(1003, "CSE101", Term::Fall, 3);
    manager.gradeStudentCourse(1003, "CSE101", 1.5);
    manager.registerStudentForCourse(1003, "MAT101", Term::Spring, 3);
    manager.gradeStudentCourse(1003, "MAT101", 1.8);

    // Sara (Expected CGPA ~ 2.6)
    manager.registerStudentForCourse(1004, "CSE101", Term::Fall, 3);
    manager.gradeStudentCourse(1004, "CSE101", 2.5);
    manager.registerStudentForCourse(1004, "MAT101", Term::Spring, 3);
    manager.gradeStudentCourse(1004, "MAT101", 2.7);

    // Youssef (Expected CGPA ~ 3.95)
    manager.registerStudentForCourse(1005, "CSE101", Term::Fall, 3);
    manager.gradeStudentCourse(1005, "CSE101", 4.0);
    manager.registerStudentForCourse(1005, "MAT101", Term::Spring, 3);
    manager.gradeStudentCourse(1005, "MAT101", 3.9);


    MainWindow w(&manager);
    w.show();


    return a.exec();
}