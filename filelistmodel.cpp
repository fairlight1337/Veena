#include "filelistmodel.h"


FileListModel::FileListModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

int FileListModel::rowCount(const QModelIndex& /*parent*/) const
{
   return mFiles.length();
}

int FileListModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 2;
}

QVariant FileListModel::data(const QModelIndex& index, int role) const
{
    const FileListItem& fli = mFiles.at(index.row());

    if (role == Qt::DisplayRole)
    {
        if(index.column() == 1)
        {
            return fli.GetFilename();
        }
    }
    else if(role == Qt::DecorationRole)
    {
        if(index.column() == 0)
        {
            QImage img = fli.GetThumbnail();

            return img;
        }
    }

    return QVariant();
}

void FileListModel::AddFile(QString filePath)
{
    QVector<QString> vector;
    vector.append(filePath);

    AddFiles(vector);
}

void FileListModel::AddFiles(QVector<QString> filePaths)
{
    beginInsertRows(QModelIndex(), mFiles.length(), mFiles.length() + filePaths.length() - 1);

    for(QString filePath : filePaths)
    {
        mFiles.append(FileListItem(filePath));
    }

    endInsertRows();
}

void FileListModel::Clear()
{
    if(mFiles.length() > 0)
    {
        beginRemoveRows(QModelIndex(), 0, mFiles.length() - 1);

        mFiles.clear();

        endRemoveRows();
    }
}

FileListItem FileListModel::GetItem(int index)
{
    return mFiles.at(index);
}
