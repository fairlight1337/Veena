#ifndef FILESTABLEVIEW_H
#define FILESTABLEVIEW_H


#include <iostream>

#include <QTableView>

#include <filelistmodel.h>


class FilesTableView : public QTableView
{
public:
    FilesTableView(QWidget* parent = 0);

    void resizeEvent(QResizeEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;
};

#endif // FILESTABLEVIEW_H
