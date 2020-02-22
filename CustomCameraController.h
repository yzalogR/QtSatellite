//
// Created by Isaac on 2020/1/23.
//

#ifndef SATELLITE_CUSTOMCAMERACONTROLLER_H
#define SATELLITE_CUSTOMCAMERACONTROLLER_H

#include <Qt3DExtras/QAbstractCameraController>
#include <QPoint>
#include <QSize>
#include <Qt3DCore/QTransform>


class CustomCameraController : public Qt3DExtras::QAbstractCameraController {
    Q_OBJECT
    Q_PROPERTY(QSize windowSize READ windowSize WRITE setWindowSize NOTIFY windowSizeChanged)
    Q_PROPERTY(float trackballSize READ trackballSize WRITE setTrackballSize NOTIFY trackballSizeChanged)
    Q_PROPERTY(float rotationSpeed READ rotationSpeed WRITE setRotationSpeed NOTIFY rotationSpeedChanged)
public:
    explicit CustomCameraController(Qt3DCore::QNode *parent = nullptr);

    QSize windowSize() const { return m_windowSize; }

    float trackballSize() const { return m_trackballSize; }

    float rotationSpeed() const { return m_rotationSpeed; }

public slots:
    void setWindowSize(QSize windowSize) {
        if (m_windowSize != windowSize) {
            m_windowSize = windowSize;
            emit windowSizeChanged(m_windowSize);
        }
    }

    void setTrackballSize(float trackballSize) {
        if (!qFuzzyCompare(m_trackballSize, trackballSize)) {
            m_trackballSize = trackballSize;
            emit trackballSizeChanged(m_trackballSize);
        }
    }

    void setRotationSpeed(float rotationSpeed) {
        if (!qFuzzyCompare(m_rotationSpeed, rotationSpeed)) {
            m_rotationSpeed = rotationSpeed;
            emit rotationSpeedChanged(m_rotationSpeed);
        }
    }

signals:
    void windowSizeChanged(QSize windowSize);
    void trackballSizeChanged(float trackballSize);
    void rotationSpeedChanged(float rotationSpeed);

private:
    void moveCamera(const InputState &state, float dt) override;

    QVector3D projectToTrackball(const QPoint &screenCoords) const;

    void createRotation(const QPoint &firstPoint, const QPoint &nextPoint, QVector3D &dir, float &angle);

    QPoint m_mouseLastPosition, m_mouseCurrentPosition;
    QSize m_windowSize;

    float m_trackballRadius = 1.0f;
    float m_panSpeed = 1.0f;
    float m_zoomSpeed = 1.0f;
    float m_rotationSpeed = 1.0f;
    float m_zoomCameraLimit = 1.0f;
    float m_trackballSize = 1.0f;
};


#endif //SATELLITE_CUSTOMCAMERACONTROLLER_H
