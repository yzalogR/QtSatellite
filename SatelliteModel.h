//
// Created by Isaac on 2020/1/22.
//

#ifndef SATELLITE_SATELLITEMODEL_H
#define SATELLITE_SATELLITEMODEL_H

#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DExtras>


class SatelliteModel : public Qt3DCore::QEntity {
    Q_OBJECT
public:
    explicit SatelliteModel(Qt3DCore::QEntity *parent);

private:
    Qt3DRender::QSceneLoader *loader = nullptr;
    Qt3DCore::QTransform *transform = nullptr;
    float radius;
};


#endif //SATELLITE_SATELLITEMODEL_H
