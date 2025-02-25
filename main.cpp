#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

#ifndef BUILD_COMMIT
#define BUILD_COMMIT "unknown"
#endif

#ifndef BUILD_BRANCH
#define BUILD_BRANCH "unknown"
#endif

#ifndef BUILD_TAG
#define BUILD_TAG "no-tag"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "=== Weather Checker Starting ===";
    qDebug() << "Build date:" << __DATE__ << __TIME__;
    qDebug() << "Git commit:" << BUILD_COMMIT;
    qDebug() << "Git branch:" << BUILD_BRANCH;

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "weather-checker_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
