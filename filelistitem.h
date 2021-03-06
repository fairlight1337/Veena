#ifndef FILELISTITEM_H
#define FILELISTITEM_H


#include <QtSvg>
#include <QSvgRenderer>
#include <QPainter>
#include <QImage>


class FileListItem
{
private:
    QString mFilePath;
    QImage mThumbnail;

    bool RenderFileToImage(QString filePath, QImage* target, bool keepAspectRatio = true);

public:
    FileListItem(QString filePath);

    QString GetFilename() const;
    QImage GetThumbnail() const;

    bool RenderToImage(QImage* target, bool keepAspectRatio = true);
};

#endif // FILELISTITEM_H
