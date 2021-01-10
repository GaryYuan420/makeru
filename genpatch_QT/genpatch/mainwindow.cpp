#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QDebug>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowLog(const QString &log)
{
    ui->LogText->append(log);
}

void MainWindow::ClearLog()
{
    ui->LogText->clear();
}

void MainWindow::on_SrcPathButton_clicked()
{
    Inputpath = QFileDialog::getExistingDirectory();
    ui->SrcPathText->clear();
    ui->SrcPathText->insert(Inputpath);
}

void MainWindow::on_DstPathButton_clicked()
{
    Outputpath = QFileDialog::getExistingDirectory();
    ui->DstPathText->clear();
    ui->DstPathText->insert(Outputpath);
}

void MainWindow::on_SrcPathText_textChanged(const QString &arg1)
{
    Inputpath = arg1;
}


void MainWindow::on_DstPathText_textChanged(const QString &arg1)
{
    Outputpath = arg1;
}

void MainWindow::on_ProcButton_clicked()
{
    QString FileText;
    QString LineBuf;
    QString PathBuf;
    QString DirBuf;
    QString DstDirBuf;
    QString SrcPathBuf;
    QString DstPathBuf;
    QDir DstDir;
    QFileInfo Fileinfo;
    QFile File;
    int Counter = 0;
    FileText = ui->FileText->toPlainText();
    ClearLog();
    FileText = FileText.replace('\\', '/');
    Inputpath = Inputpath.replace('\\', '/');
    Outputpath = Outputpath.replace('\\', '/');

    while(!(LineBuf = FileText.section('\n', Counter, Counter)).isEmpty())
    {
        if(LineBuf.startsWith("added") || LineBuf.startsWith("modified"))
        {
            PathBuf =  LineBuf.section(' ', 1, -1).remove(QRegExp("^ +\\s*"));;
            SrcPathBuf = Inputpath + '/' + PathBuf;
            DstPathBuf = Outputpath + '/' + PathBuf;
            Fileinfo = SrcPathBuf;
            if(Fileinfo.isDir())
            {
                DstDir.mkpath(DstPathBuf);
                ShowLog(PathBuf + "...Dir Done!");
            }
            else if(Fileinfo.isFile())
            {
                DirBuf = PathBuf.section('/', 0, -2);
                DstDir.mkpath(Outputpath + '/' + DirBuf);
                if(File.copy(SrcPathBuf, DstPathBuf))
                {
                    ShowLog(PathBuf + "...File Done!");
                }
                else
                {
                    ShowLog(PathBuf + "...File Error!");
                    return;
                }
            }
            else
            {
                ShowLog(PathBuf + "...Not Exist!");
                return;
            }

        }
        Counter++;
    }

    return;
}



