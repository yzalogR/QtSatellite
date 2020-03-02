//
// Created by Isaac on 2020/2/4.
//

#ifndef SATELLITE_TORUSMODEL_H
#define SATELLITE_TORUSMODEL_H

#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DExtras>


class TorusModel : public Qt3DCore::QEntity {
public:
    explicit TorusModel(Qt3DCore::QEntity *parent);

    //Get starfinder longitude and latitude;
    QPointF getCurrentPosition();
    //Set starfinder newest position
    void setCurrentPosition(float newLon, float newLat);
    //Refresh starfinder in map location
    void updatePosition();
    //Refresh starfinder angle
    void updateAngle();
    //Refresh angle and map location
    void update();

private:
    // Material
    Qt3DRender::QMaterial *material;
    Qt3DCore::QEntity *torusEntity;
    Qt3DExtras::QTorusMesh *torusMesh;
    Qt3DCore::QTransform *transform = nullptr;
    float radius;
    float angle;
};


#endif //SATELLITE_TORUSMODEL_H
