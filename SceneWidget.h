//
// Created by Isaac on 2020/2/15.
//

#ifndef SATELLITE_SCENEWIDGET_H
#define SATELLITE_SCENEWIDGET_H

#include <Qt3DExtras>
#include "SatelliteModel.h"
#include "StarFinderModel.h"
#include "EarthModel.h"
#include "Light.h"


class SceneWidget : public Qt3DExtras::Qt3DWindow {
Q_OBJECT
public:
    explicit SceneWidget(QScreen *screen = nullptr);
    void setSatellitePosion(float longitude , float latitude);
    void setGroundPosion(float longitude , float latitude);

private:
    Qt3DCore::QEntity *createScene();

    SatelliteModel *satelliteModel = nullptr;
    StarFinderModel *starFinderModel = nullptr;
    EarthModel *earthModel = nullptr;
    Light *light = nullptr;

    Qt3DCore::QEntity *rootEntity = nullptr;
};


#endif //SATELLITE_SCENEWIDGET_H
