#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <QWidget>

namespace Ui {
class Instructor;
}

class Instructor : public QWidget
{
    Q_OBJECT

public:
    explicit Instructor(QWidget *parent = nullptr);
    ~Instructor();

private:
    Ui::Instructor *ui;
};

#endif // INSTRUCTOR_H
