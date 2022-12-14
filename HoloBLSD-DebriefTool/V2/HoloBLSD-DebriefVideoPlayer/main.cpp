#include "mainwindow.h"
#include "qdatetime.h"
#include <QApplication>

#include <QDir>
#include <QtGlobal>
#include <stdio.h>
#include <stdlib.h>
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    QString debugMsg ="";
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
   /** switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug : %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info : %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning : %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical : %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal : %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    }*/

    debugMsg += function;
    debugMsg += "   -   ";
    debugMsg += localMsg.constData();
    QFile outFile(QDir::currentPath() + "\\LogHoloBLSD.txt");
        outFile.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(&outFile);
        ts << debugMsg <<  Qt::endl;
}



int main(int argc, char *argv[])
{
    qDebug()<< QDir::currentPath();
    qInstallMessageHandler(myMessageOutput);

    QApplication a(argc, argv);

    QFile style(":/Styles/Combinear.qss");
    style.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(style.readAll());
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return a.exec();
}
