#include "filestableview.h"

FilesTableView::FilesTableView(QWidget* parent)
    : QTableView(parent)
{
    setAcceptDrops(true);
}

void FilesTableView::resizeEvent(QResizeEvent* event)
{
    this->setColumnWidth(0, 32);
    this->setColumnWidth(1, this->width() - 32);

    QTableView::resizeEvent(event);
}

void FilesTableView::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {
        FileListModel* flm = (FileListModel*)this->model();
        QList<QUrl> urlList = mimeData->urls();
        QVector<QString> filePaths;

        for (int i = 0; i < urlList.size(); ++i)
        {
            QString localFile = urlList.at(i).toLocalFile();
            filePaths.append(localFile);
        }

        flm->AddFiles(filePaths);
    }
}

void FilesTableView::dragEnterEvent(QDragEnterEvent* event)
{
    event->acceptProposedAction();
}

void FilesTableView::dragMoveEvent(QDragMoveEvent* event)
{
    event->acceptProposedAction();
}

void FilesTableView::dragLeaveEvent(QDragLeaveEvent* event)
{
    event->accept();
}
