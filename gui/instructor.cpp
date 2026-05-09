#include "instructor.h"
#include "ui_instructor.h"

Instructor::Instructor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Instructor)
{
    ui->setupUi(this);

    connect(ui->btn_studentP, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->Studentpage);
        setWindowTitle("Students Dashboard");
    });
    connect(ui->btn_lecturerP, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->LecturerPage);
        setWindowTitle("Lecturers Dashboard");
    });
    connect(ui->btn_coursesP, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->CoursesPage);
        setWindowTitle("Courses Dashboard");
    });
    connect(ui->btn_reportsP, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->ReportsPage);
        setWindowTitle("Reports Dashboard");
    });

    connect(ui->btn_top, &QPushButton::clicked, this, [this]() {
        ui->reportstack->setCurrentWidget(ui->topstudentP);

    });

    connect(ui->btn_pass, &QPushButton::clicked, this, [this]() {
        ui->reportstack->setCurrentWidget(ui->passfaillp);

    });

    connect(ui->btn_grade, &QPushButton::clicked, this, [this]() {
        ui->reportstack->setCurrentWidget(ui->gradedis);

    });











}

Instructor::~Instructor()
{
    delete ui;
}
