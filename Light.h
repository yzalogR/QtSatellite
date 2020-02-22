//
// Created by Isaac on 2020/2/21.
//

#ifndef SATELLITE_LIGHT_H
#define SATELLITE_LIGHT_H

#include <Qt3DCore>
#include <Qt3DRender>

class Light : public Qt3DCore::QEntity {
    Q_OBJECT
public:
    explicit Light(Qt3DRender::QCamera *camera, Qt3DCore::QEntity *parent = nullptr);

private:
    Qt3DRender::QPointLight *light = nullptr;
    Qt3DCore::QTransform *transform = nullptr;
};


#endif //SATELLITE_LIGHT_H
