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

    //Get satellite currently longitute and latitude
    QPointF getCurrentPosition();

    //Set satellite newest position
    void setCurrentPosition(float newLon, float newLat);

    //Refresh satellite in map location
    void updatePosition();

    //Refresh satellite angle
    void updateAngle();

    //Refresh angle and map location
    void update();

private:
    Qt3DRender::QSceneLoader *loader = nullptr;
    Qt3DCore::QTransform *transform = nullptr;
    float radius;
    float longitude, latitude, angle;

signals:
    void emitLonLat(float newLon,float newLat);
};


#endif //SATELLITE_SATELLITEMODEL_H
