#ifndef CONVERTERWORKER_H
#define CONVERTERWORKER_H


#include <iostream>

#include <QObject>

#include <filelistmodel.h>


class ConverterWorker : public QObject
{
    Q_OBJECT

private:
    FileListModel* model;
    int targetWidth;
    int targetHeight;
    QString targetDirectory;

public:
    explicit ConverterWorker(QObject* parent, FileListModel* model_passed, QString targetDirectory_passed, int targetWidth_passed, int targetHeight_passed);

    void convert();

signals:
    void updateProgress(int numFinished, int numTotal);
    void done();

public slots:
};


#endif // CONVERTERWORKER_H
