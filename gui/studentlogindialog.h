#pragma once

#include <QDialog>
#include <QString>

namespace Ui { class StudentLoginDialog; }

class StudentLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentLoginDialog(QWidget *parent = nullptr);
    ~StudentLoginDialog();

    // Getter so the main window can retrieve the entered ID
    QString getEnteredID() const;

private slots:
    void on_btn_search_clicked();

private:
    Ui::StudentLoginDialog *ui;
};