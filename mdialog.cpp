#include "mdialog.h"
#include "ui_mdialog.h"
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include "glwidget.h"
#include "viewer.h"

QString fInfo;

mDialog::mDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mDialog)
{
    QStringList filters;
    QString path;
    path = "/";
    filters << "*.stl";
    ui->setupUi(this);
    dModel = new QFileSystemModel(this);
    fModel = new QFileSystemModel(this);

    dModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dModel->setRootPath(path);
    ui->treeView->setModel(dModel);
    ui->treeView->resizeColumnToContents(0);

    fModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    fModel->setNameFilters(filters);
    fModel->setNameFilterDisables(false);
    fModel->setRootPath(path);
    ui->listView->setModel(fModel);
}

mDialog::~mDialog()
{
    delete ui;
}

void mDialog::on_treeView_clicked(const QModelIndex &index)
{
    QString nPath = dModel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(fModel->setRootPath(nPath));
    ui->treeView->expand(ui->treeView->currentIndex());
    ui->treeView->resizeColumnToContents(0);
}

void mDialog::on_listView_activated(const QModelIndex &index)
{
    fInfo = fModel->fileInfo(index).absoluteFilePath();
    GlWidget glwidget(this);
    Viewer v(this);
    glwidget.setPath(fInfo);
    v.exec();
}

void mDialog::on_listView_clicked(const QModelIndex &index)
{
    fInfo = fModel->fileInfo(index).absoluteFilePath();
}

void mDialog::on_pushButton_2_clicked()
{
    GlWidget glwidget(this);
    Viewer v(this);
    glwidget.setPath(fInfo);
    v.exec();

}
