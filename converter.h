/*
Copyright 2020 Sergey Ilinykh

converter.h - Conversion class

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

#ifndef CONVERTER_H
#define CONVERTER_H

#include <QString>

class Converter {
public:
    enum Type { None, Text, Cpp, Json };

    static Type str2type(const QString &type);

    void    setSourceType(Type source) { srcType_ = source; }
    void    setDestinationType(Type dst) { dstType_ = dst; }
    QString convert(const QString &source) const;

    QString cppToText(const QString &source) const;
    QString jsonToText(const QString &source) const;
    QString textToCpp(const QString &source) const;
    QString textToJson(const QString &source) const;

private:
    Type srcType_;
    Type dstType_;
};

#endif // CONVERTER_H
