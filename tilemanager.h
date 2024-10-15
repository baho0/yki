#ifndef TILEMANAGER_H
#define TILEMANAGER_H
#include <QGridLayout>
class TileManager
{
public:
    TileManager(int countOfTilesX,int countOfTilesY,QGridLayout *gridLayout,double latitude,double longitude,int zoom);
    void designTheLayout();
    int x;
    int y;
    QGridLayout *gridLayout;
private:

    int countOfTilesX;
    int countOfTİlesY;
    int zoom;
};

#endif // TILEMANAGER_H
