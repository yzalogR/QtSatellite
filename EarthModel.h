//
// Created by Isaac on 2020/1/22.
//

#ifndef SATELLITE_EARTHMODEL_H
#define SATELLITE_EARTHMODEL_H

#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DExtras>

class EarthModel : public Qt3DCore::QEntity {
public:
    explicit EarthModel(Qt3DCore::QEntity *parent);

private:
    Qt3DExtras::QSphereMesh *mesh;
    Qt3DCore::QTransform *transform;
    Qt3DExtras::QTextureMaterial *material;
    float radius;
};


#endif //SATELLITE_EARTHMODEL_H
