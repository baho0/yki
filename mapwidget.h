#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QTimer>
#include <QLabel>
class MapWidget : public QLabel {
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = nullptr,int x =0,int y=0);
    void loadMap(int x,int y);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onMapDownloaded(QNetworkReply *reply);
    void refreshMap();
private:
    QTimer *refreshTimer;
    QPixmap mapImage;
    int x;
    int y;
    QNetworkAccessManager *networkManager;
};

#endif // MAPWIDGET_H
