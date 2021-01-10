#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ShowLog(const QString &log);
    void ClearLog(void);
private slots:
    void on_SrcPathButton_clicked();

    void on_DstPathButton_clicked();

    void on_ProcButton_clicked();

    void on_SrcPathText_textChanged(const QString &arg1);

    void on_DstPathText_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QString Inputpath;
    QString Outputpath;

};
#endif // MAINWINDOW_H
