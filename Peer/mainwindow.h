#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "peer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void appendMessage(QString);

    void on_pb_send_clicked();

private:
    Ui::MainWindow *ui;
    Peer* peer ;
};

#endif // MAINWINDOW_H
