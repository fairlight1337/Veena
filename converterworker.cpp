#include "converterworker.h"


ConverterWorker::ConverterWorker(QObject* parent, FileListModel* model_passed, QString targetDirectory_passed, int targetWidth_passed, int targetHeight_passed)
    : QObject(parent)
    , model(model_passed)
    , targetWidth(targetWidth_passed)
    , targetHeight(targetHeight_passed)
    , targetDirectory(targetDirectory_passed)
{
}

void ConverterWorker::convert()
{
    int count = model->rowCount();

    for(int i = 0; i < count; ++i)
    {
        FileListItem item = model->GetItem(i);

        QImage img(targetWidth, targetHeight, QImage::Format_ARGB32);
        item.RenderToImage(&img);

        QString fileName = item.GetFilename();
        QFileInfo info(fileName);
        QString targetExtension = "png";

        QString path = QDir::cleanPath(targetDirectory + QDir::separator() + info.baseName() + "." + targetExtension);

        img.save(path);

        emit updateProgress(i + 1, count);
    }

    emit done();
}
