#ifndef MDIALOG_H
#define MDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <QDirModel>
#include <QFileSystemModel>

namespace Ui {
class mDialog;
}

class mDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mDialog(QWidget *parent = 0);
    ~mDialog();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_listView_activated(const QModelIndex &index);

    void on_listView_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

private:
    Ui::mDialog *ui;
    QFileSystemModel *dModel;
    QFileSystemModel *fModel;
};

#endif // MDIALOG_H
