#include "mapwidget.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
MapWidget::MapWidget(QWidget *parent,int x,int y)
    : QLabel(parent), networkManager(new QNetworkAccessManager(this)) {
    connect(networkManager, &QNetworkAccessManager::finished,
            this, &MapWidget::onMapDownloaded);
    loadMap(x, y);
}



void MapWidget::loadMap(int x,int y) {
    // Construct the URL for the OpenStreetMap tile (example for zoom level 12)
    int zoom = 15;
    qInfo() << "x: " << x << " | y: " << y;
    QString urlString = QString("https://tile.openstreetmap.org/%1/%2/%3.png").arg(zoom).arg(x).arg(y);
    QNetworkRequest request(urlString);
    request.setRawHeader("User-Agent", "MyCustomMapApp/1.0");
    QNetworkReply *reply = networkManager->get(request);
    qDebug() << request.url();
}

void MapWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (!mapImage.isNull()) {
        painter.drawPixmap(0, 0, mapImage);
    }
}
void MapWidget::refreshMap(){
    qDebug()<<"ok";
    loadMap(x,y);
}
void MapWidget::onMapDownloaded(QNetworkReply *reply) {
    QByteArray imageData = reply->readAll();
    QImage mapImage;
    if (reply->error() == QNetworkReply::NoError) {
        if (mapImage.loadFromData(imageData)) {
            QSize newSize(250, 250);
            QImage resizedMapImage = mapImage.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            qDebug() << "Tile downloaded and resized successfully!";
            QLabel *mapLabel = new QLabel(this);
            mapLabel->setPixmap(QPixmap::fromImage(resizedMapImage));
            mapLabel->show();
            update();
        } else {
            qDebug() << "Failed to load map image from data.";
        }
    } else {
        qDebug() << "Error downloading map:" << reply->errorString();
    }
    reply->deleteLater();
}



