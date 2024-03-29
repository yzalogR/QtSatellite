//
// Created by Isaac on 2020/2/15.
//

#ifndef SATELLITE_SCENEWIDGET_H
#define SATELLITE_SCENEWIDGET_H

#include <Qt3DExtras>
#include "SatelliteModel.h"
#include "StarFinderModel.h"
#include "EarthModel.h"
#include "TorusModel.h"
#include "ConeModel.h"
#include "Light.h"


class SceneWidget : public Qt3DExtras::Qt3DWindow {
Q_OBJECT
public:
    explicit SceneWidget(QScreen *screen = nullptr);

    void setSatellitePosion(float longitude, float latitude);

    void setGroundPosion(float longitude, float latitude);

    void moveSatellite(float longitude, float latitude);

    void stopSatellite();

    void runSatelliteMoveTimer();
    void updateTorusAngle(float angleX,float angleY);

private:
    Qt3DCore::QEntity *createScene();

    SatelliteModel *satelliteModel = nullptr;
    StarFinderModel *starFinderModel = nullptr;
    EarthModel *earthModel = nullptr;
    TorusModel* torusModel = nullptr;
    ConeSignalModel* coneSignalModel = nullptr;
    Light *light = nullptr;

    Qt3DCore::QEntity *rootEntity = nullptr;

    QTimer *moveSatelliteTimer;
    QPointF moveSatelliteOffset;
};


#endif //SATELLITE_SCENEWIDGET_H
