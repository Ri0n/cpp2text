/*
Copyright 2020 Sergey Ilinykh

mainwindow.cpp - Main dialog

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "mainwindow.h"
#include "converter.h"
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
