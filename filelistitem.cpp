#include "filelistitem.h"

FileListItem::FileListItem(QString filePath)
    : mFilePath(filePath)
    , mThumbnail(QImage(32, 32, QImage::Format_ARGB32))
{
    RenderFileToImage(filePath, &mThumbnail);
}

QString FileListItem::GetFilename() const
{
    QFileInfo info(mFilePath);

    return info.fileName();
}

QImage FileListItem::GetThumbnail() const
{
    return mThumbnail;
}

bool FileListItem::RenderFileToImage(QString filePath, QImage* target)
{
    QSvgRenderer renderer(filePath);
    target->fill(0x00000000);

    QPainter painter(target);
    renderer.render(&painter);

    return true;
}

bool FileListItem::RenderToImage(QImage* target)
{
    return RenderFileToImage(mFilePath, target);
}
