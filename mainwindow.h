#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include <QMainWindow>

#include <filelistmodel.h>
#include <converterworker.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    FileListModel* model;
    QThread* converterThread;
    ConverterWorker* converterWorker;

private slots:
    void clear();
    void convert();

    void updateProgress(int numFinished, int numTotal);
    void convertFinished();
};

#endif // MAINWINDOW_H
