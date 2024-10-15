#include "mainwindow.h"
#include "tilemanager.h"
#include "mapwidget.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QGridLayout>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "freshMap_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    QWidget *mainWidget = new QWidget(nullptr);
    QWidget *mapWidget = new QWidget(nullptr);
    QGridLayout *mapGridLayout = new QGridLayout(nullptr);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mapGridLayout->setContentsMargins(0, 0, 0, 0);
    //w.resize(500,500);
    mapGridLayout->setSpacing(0);

    TileManager *tileManager = new TileManager(2,2,mapGridLayout,40.7128, -74.0060,15);
    tileManager->designTheLayout();
    mainWidget->setLayout(mainLayout);
    mapWidget->setLayout(mapGridLayout);
    mainLayout->addWidget(mapWidget);
    int rowCount = mapGridLayout->rowCount();
    int columnCount = mapGridLayout->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        mapGridLayout->setRowStretch(row+rowCount, 1); // Satırın esnekliği
    }

    for (int col = 0; col < columnCount; ++col) {
        mapGridLayout->setColumnStretch(col+columnCount, 1); // Sütunun esnekliği
    }
    w.setCentralWidget(mainWidget);
    w.show();
    return a.exec();
}
