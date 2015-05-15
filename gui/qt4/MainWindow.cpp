#include "MainWindow.h"
#include <mgl2/qt.h>
#include <mgl2/surf.h>
#include <assert.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    core(new Nsga)
{
    ui->setupUi(this);
    qout.reset(new QDebugStream(std::cout, *(ui->logBox)));
    QMGL.reset(new QMathGL(ui->plotWidget));
    QMGL->setDraw(&drawer);
    QMGL->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    assert(core != NULL);
    settings.f[0] = std::string(ui->lineEdit->text().toStdString());
    settings.f[1] = std::string(ui->lineEdit_2->text().toStdString());

    settings.g[0] = std::string(ui->lineEdit_3->text().toStdString());
    settings.g[1] = std::string(ui->lineEdit_4->text().toStdString());
    settings.g[2] = std::string(ui->lineEdit_5->text().toStdString());
    settings.g[3] = std::string(ui->lineEdit_6->text().toStdString());
    settings.g[4] = std::string(ui->lineEdit_7->text().toStdString());

    setValidValue(ui->lineEdit_8, settings.individualsCount);
    setValidValue(ui->lineEdit_9, settings.generationsCount);
    setValidValue(ui->lineEdit_10, settings.variablesCount);

    settings.lowerBound = ui->lineEdit_11->text().toInt();
    settings.upperBound = ui->lineEdit_12->text().toInt();

   core->execute(settings);
   drawer.initData(core->result());
   QMGL->update();

}

void MainWindow::setValidValue(QLineEdit* line, unsigned& field)
{
    assert(line != NULL);
    const QString validStyle = "background-color: white;";
    const QString invalidStyle = "background-color: rgb(255, 96, 96);";

    if (line->text().toUInt() > 0)
    {
        line->setStyleSheet(validStyle);
        field = line->text().toUInt();
    }
    else
        line->setStyleSheet(invalidStyle);
}
