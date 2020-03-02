#ifndef SATELLITE_CONESIGNALMODEL_H
#define SATELLITE_CONESIGNALMODEL_H

#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DExtras>
#include "SatelliteModel.h"

class ConeSignalModel : public Qt3DCore::QEntity {
public:
    explicit ConeSignalModel(Qt3DCore::QEntity *parent,SatelliteModel* satellite);
    void recvSatelliteLonLat(float newLon,float newLat);
    void updatePosition();
    void updateAngle();
    void update();
    void updateColor(bool found);

private:
    Qt3DRender::QMaterial *material;
    Qt3DCore::QEntity *signalEntity;
    Qt3DExtras::QConeMesh *signalMesh;
    Qt3DCore::QTransform *transform = nullptr;
    SatelliteModel* mSatellite = nullptr;
    float radius;
    float longitude, latitude;
};


#endif
