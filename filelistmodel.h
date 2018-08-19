#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H


#include <iostream>

#include <QAbstractTableModel>
#include <QList>

#include <filelistitem.h>


class FileListModel : public QAbstractTableModel
{
private:
    QList<FileListItem> mFiles;

public:
    FileListModel(QObject* parent);
    ~FileListModel() = default;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    void AddFile(QString filePath);
    void AddFiles(QVector<QString> filePaths);

    void Clear();

    FileListItem GetItem(int index);
};

#endif // FILELISTMODEL_H
