//
// Created by Isaac on 2020/2/14.
//

#ifndef SATELLITE_MAINWINDOW_H
#define SATELLITE_MAINWINDOW_H

#include <QWidget>
#include "SceneWidget.h"
#include <Qt3DExtras>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QWidget {
Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void setSatellitePosion();
    void setGroundPosion();
    void moveSatellite();
    void stopSatellite();
    void updateTorusAngle();


private:
    SceneWidget *view;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    QLabel *satelliteAngleText;
    QLineEdit *satelliteLon;
    QLineEdit *satelliteLat;
    QPushButton *satelliteSubmit;
    QPushButton *satelliteReset;
    QLabel *groundAngleText;
    QLineEdit *groundLon;
    QLineEdit *groundLat;
    QPushButton *groundSubmit;
    QPushButton *groundReset;
    QLabel *satelliteMoveText;
    QLineEdit *satelliteMoveLon;
    QLineEdit *satelliteMoveLat;
    QPushButton *satelliteMoveSubmit;
    QPushButton *satelliteMoveStop;
    QLabel *torusText;
    QLineEdit *torusAngleX;
    QLineEdit *torusAngleY;
    QPushButton *torusChangeSubmit;
};

#endif //SATELLITE_MAINWINDOW_H
