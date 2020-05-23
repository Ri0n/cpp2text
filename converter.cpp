/*
Copyright 2020 Sergey Ilinykh

converter.cpp - Conversion class

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

#include <QJsonDocument>
#include <QStringList>
#include <QVariant>

Converter::Type Converter::str2type(const QString &type)
{
    if (type == "cpp")
        return Cpp;
    if (type == "json")
        return Json;
    if (type == "text")
        return Text;
    return None;
}

QString Converter::convert(const QString &source) const
{
    if (srcType_ == dstType_)
        return source;

    QString text;
    switch (srcType_) {
    case None:
        return QString();
    case Text:
        text = source;
        break;
    case Cpp:
        text = cppToText(source);
        break;
    case Json:
        text = jsonToText(source);
        break;
    }

    switch (dstType_) {
    case None:
        return QString();
    case Text:
        return text;
    case Cpp:
        return textToCpp(text);
    case Json:
        return textToJson(text);
        break;
    }

    return QString();
}

QString Converter::cppToText(const QString &source) const
{
    QString     copy  = source;
    QStringList lines = copy.replace("\r\n", "\n").split('\n');
    QString     text;
    QString     unescaped;
    foreach (const QString &l, lines) {
        QString s = l.trimmed();
        s         = s.mid(1, s.size() - 2);
        if (!s.size())
            continue;
        unescaped.clear();
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '\\') {
                if (i < s.size() - 1) {
                    /* cpp has more escape sequences. but I need just next ones atm */
                    if (s[i + 1] == 'n')
                        unescaped += '\n';
                    else if (s[i + 1] == 't')
                        unescaped += '\t';
                    else
                        unescaped += s[i + 1];
                    i++;
                } else {
                    break;
                }
            } else {
                unescaped += s[i];
            }
        }
        text += unescaped;
    }
    return text;
}

QString Converter::jsonToText(const QString &source) const
{
    auto doc = QJsonDocument::fromJson(QString("[%1]").arg(source).toUtf8());
    return doc.toVariant().toStringList().value(0);
}

QString Converter::textToCpp(const QString &source) const
{
    QStringList l = source.split('\n');
    QStringList escaped;
    QRegExp     re("(\"|\\\\)");
    foreach (const QString &s, l) {
        QString s2 = s;
        escaped += s2.replace(re, "\\\\1");
    }
    QString ret = '"' + escaped.join("\\n\"\n\"") + '"';
    if (ret.endsWith("\n\"\"")) {
        ret.resize(ret.size() - 3);
    }
    return ret;
}

QString Converter::textToJson(const QString &source) const
{
    QVariant v   = QStringList() << source;
    auto     doc = QJsonDocument::fromVariant(v);
    auto     arr = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
    return arr.mid(1, arr.size() - 2).trimmed();
}
