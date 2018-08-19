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

bool FileListItem::RenderFileToImage(QString filePath, QImage* target, bool keepAspectRatio)
{
    QSvgRenderer renderer(filePath);
    target->fill(0x00000000);

    QPainter painter(target);
    QRectF targetDrawingBounds;

    if(!keepAspectRatio)
    {
        targetDrawingBounds.setX(0);
        targetDrawingBounds.setY(0);
        targetDrawingBounds.setWidth(target->width());
        targetDrawingBounds.setHeight(target->height());
    }
    else
    {
        QSize svgSize = renderer.defaultSize();

        if(svgSize.width() > svgSize.height())
        {
            double ratio = (double)svgSize.height() / (double)svgSize.width();

            targetDrawingBounds.setWidth(target->width());
            targetDrawingBounds.setHeight(target->width() * ratio);

            targetDrawingBounds.setX(0);
            targetDrawingBounds.setY((target->height() - targetDrawingBounds.height()) / 2.0);

            targetDrawingBounds.setHeight(targetDrawingBounds.height() + targetDrawingBounds.y());
        }
        else
        {
            double ratio = (double)svgSize.width() / (double)svgSize.height();

            targetDrawingBounds.setWidth(target->width() * ratio);
            targetDrawingBounds.setHeight(target->height());

            targetDrawingBounds.setX((target->width() - targetDrawingBounds.width()) / 2.0);
            targetDrawingBounds.setY(0);

            targetDrawingBounds.setWidth(targetDrawingBounds.width() + targetDrawingBounds.x());
        }
    }

    renderer.render(&painter, targetDrawingBounds);

    return true;
}

bool FileListItem::RenderToImage(QImage* target, bool keepAspectRatio)
{
    return RenderFileToImage(mFilePath, target, keepAspectRatio);
}
