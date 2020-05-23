/*
Copyright 2020 Sergey Ilinykh

main.cpp - entry point

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

#include "converter.h"
#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("cpp2text");
    QCoreApplication::setApplicationVersion("1.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("String representation converter");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOptions({ { { "s", "source-type" },
                          QCoreApplication::translate("main", "Set source text type <source-type>."),
                          QCoreApplication::translate("main", "source-type") },
                        { { "d", "destination-type" },
                          QCoreApplication::translate("main", "Set destination text type <destination-type>."),
                          QCoreApplication::translate("main", "destination-type") },
                        { { "t", "text" },
                          QCoreApplication::translate("main", "Text to convert."),
                          QCoreApplication::translate("main", "text") } });

    parser.process(app);

    QString sourceTypeStr      = parser.value("source-type");
    QString destinationTypeStr = parser.value("destination-type");
    QString text               = parser.value("text");

    Converter::Type sourceType      = Converter::str2type(sourceTypeStr);
    Converter::Type destinationType = Converter::str2type(destinationTypeStr);
    if (sourceType != Converter::None && destinationType != Converter::None && !text.isEmpty()) {
        Converter c;
        c.setSourceType(sourceType);
        c.setDestinationType(destinationType);
        printf("%s\n", qPrintable(c.convert(text)));
        return 0;
    }

    MainWindow w;
    w.show();

    return app.exec();
}
