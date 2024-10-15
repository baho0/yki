#include "tilemanager.h"
#include "mapwidget.h"
#include <QGridLayout>
#include <QDebug>
TileManager::TileManager(int countOfTilesX,int countOfTilesY,QGridLayout *gridLayout,double latitude,double longitude,int zoom) {
    // Construct the URL for the OpenStreetMap tile (example for zoom level 12)
    this->gridLayout = gridLayout;
    this->zoom = zoom;
    this->countOfTilesX = countOfTilesX;
    this->countOfTİlesY = countOfTilesY;
    this->x = static_cast<int>(floor((longitude + 180) / 360 * (1 << zoom)));
    this->y = static_cast<int>(floor((1 - (log(tan(latitude * M_PI / 180) + 1 / cos(latitude * M_PI / 180)) / M_PI)) / 2 * (1 << zoom)));
    qDebug()<<"x is:" << this->x << " y is:" <<this->y;
}
void TileManager::designTheLayout(){
    for(int x=0;x<countOfTilesX;x++){
        for(int y=0;y<countOfTİlesY;y++){

            MapWidget *map=new MapWidget(nullptr,this->x+x,this->y+y);
            map->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            map->setFixedSize(250,250);
            //map->loadMap(this->x+x,this->y+y);
            map->show();
            this->gridLayout->addWidget(map,y,x);
        }
    }
}
