//
// Created by Isaac on 2020/2/4.
//

#ifndef SATELLITE_STARFINDERMODEL_H
#define SATELLITE_STARFINDERMODEL_H

#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DExtras>


class StarFinderModel : public Qt3DCore::QEntity {
public:
    explicit StarFinderModel(Qt3DCore::QEntity *parent);

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
    Qt3DRender::QSceneLoader *loader = nullptr;
    Qt3DCore::QTransform *transform = nullptr;
    float radius;
    float longitude, latitude, angle;
};


#endif //SATELLITE_STARFINDERMODEL_H
