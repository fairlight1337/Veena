#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , converterThread(nullptr)
    , converterWorker(nullptr)
{
    ui->setupUi(this);

    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(ui->convertButton, SIGNAL(clicked()), this, SLOT(convert()));

    model = new FileListModel(nullptr);

    ui->filesTable->setModel(model);
}

MainWindow::~MainWindow()
{
    delete model;
    delete ui;
}

void MainWindow::clear()
{
    model->Clear();
}

void MainWindow::convert()
{
    if(model->rowCount() > 0)
    {
        QString dir = QFileDialog::getExistingDirectory(this, tr("Choose destination directory"),
                                                        QStandardPaths::displayName(QStandardPaths::HomeLocation),
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        if(!dir.isEmpty())
        {
            ui->convertButton->setEnabled(false);
            ui->clearButton->setEnabled(false);
            ui->filesTable->setEnabled(false);
            ui->targetWidth->setEnabled(false);
            ui->targetHeight->setEnabled(false);

            QApplication::processEvents();

            converterThread = new QThread(this);
            converterWorker = new ConverterWorker(nullptr, model, dir, ui->targetWidth->text().toInt(), ui->targetHeight->text().toInt());

            connect(converterWorker, SIGNAL(updateProgress(int, int)), this, SLOT(updateProgress(int, int)));
            connect(converterWorker, SIGNAL(done()), this, SLOT(convertFinished()));
            connect(converterThread, SIGNAL(destroyed(QObject*)), this, SLOT(deleteLater()));

            converterWorker->moveToThread(converterThread);
            converterWorker->convert();
        }
    }
}

void MainWindow::updateProgress(int numFinished, int numTotal)
{
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(numFinished);
    ui->progressBar->setMaximum(numTotal);

    QApplication::processEvents();
}

void MainWindow::convertFinished()
{
    disconnect(converterWorker, SIGNAL(updateProgress(int, int)), this, SLOT(updateProgress(int, int)));
    disconnect(converterWorker, SIGNAL(done()), this, SLOT(convertFinished()));

    converterWorker->deleteLater();
    converterWorker = nullptr;

    QApplication::processEvents();

    ui->targetHeight->setEnabled(true);
    ui->targetWidth->setEnabled(true);
    ui->filesTable->setEnabled(true);
    ui->clearButton->setEnabled(true);
    ui->convertButton->setEnabled(true);

    QApplication::processEvents();
}
