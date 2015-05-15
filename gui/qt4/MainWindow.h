#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <mgl2/qmathgl.h>

#include <QMainWindow>
#include <QDebugStream.h>
#include <ui_mainwindow.h>
#include <MathGlDrawer.h>
#include <Nsga.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<QMathGL> QMGL;
    MathGlDrawer drawer;
    CoreSettings settings;
    std::unique_ptr<Core<ResultType>> core;
    std::unique_ptr<QDebugStream> qout;

    void setValidValue(QLineEdit* line, unsigned &field);
};

#endif // MAINWINDOW_H
