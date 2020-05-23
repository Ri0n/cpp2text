#include <QRegExp>

#include "converter.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) { ui->setupUi(this); }

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pbConvert_clicked()
{
    Converter::Type srcType = Converter::Text;
    if (ui->rbSrcCpp->isChecked())
        srcType = Converter::Cpp;
    else if (ui->rbSrcJson->isChecked())
        srcType = Converter::Json;

    Converter::Type dstType = Converter::Text;
    if (ui->rbDstCpp->isChecked())
        dstType = Converter::Cpp;
    else if (ui->rbDstJson->isChecked())
        dstType = Converter::Json;

    Converter converter;
    converter.setSourceType(srcType);
    converter.setDestinationType(dstType);
    ui->teDestination->setPlainText(converter.convert(ui->teSource->toPlainText()));
}
