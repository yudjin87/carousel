#include "TextLoggerTest.h"
#include <carousel/logging/TextLogger.h>
#include <QtTest/QtTest>
#include <iostream>

TextLoggerTest::TextLoggerTest()
{
}

void TextLoggerTest::writeToStream()
{
    QString log;
    QTextStream out(&log);

    TextLogger logger(out);

    QString message = "Hello, world!";
    logger.i(message);

    QVERIFY(log.contains(message));
    QVERIFY(log.contains("INF"));
}

void TextLoggerTest::writeToErrorStream()
{
    static QTextStream output(stdout);
    static QTextStream errors(stderr);

    TextLogger logger(output, errors);

    QString message = "Hello, world!";
    logger.i(message);
    logger.e("Errrrr");
}
