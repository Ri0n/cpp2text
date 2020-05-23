#ifndef CONVERTER_H
#define CONVERTER_H

#include <QString>

class Converter {
public:
    enum Type { Text, Cpp, Json };

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
