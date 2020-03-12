#include <Qt3DRender/QCamera>
#include <QVector2D>
#include <Qt3DInput/QAction>
#include <Qt3DInput/QActionInput>
#include <Qt3DInput/QAxis>
#include <Qt3DInput/QAnalogAxisInput>
#include <Qt3DInput/QMouseDevice>
#include <Qt3DInput/QKeyboardDevice>
#include <Qt3DInput/QMouseHandler>
#include <Qt3DInput/QKeyboardHandler>
#include <Qt3DCore/QTransform>
#include <QtMath>
#include "CustomCameraController.h"

CustomCameraController::CustomCameraController(Qt3DCore::QNode *parent) : Qt3DExtras::QAbstractCameraController(
        parent) {
    auto *mouseHandler = new Qt3DInput::QMouseHandler(this);
    mouseHandler->setSourceDevice(mouseDevice());

    QObject::connect(mouseHandler, &Qt3DInput::QMouseHandler::pressed, [this](Qt3DInput::QMouseEvent *pressedEvent) {
        pressedEvent->setAccepted(true);
        m_mouseLastPosition = QPoint(pressedEvent->x(), pressedEvent->y());
        m_mouseCurrentPosition = m_mouseLastPosition;
    });
    QObject::connect(mouseHandler, &Qt3DInput::QMouseHandler::positionChanged,
                     [this](Qt3DInput::QMouseEvent *positionChangedEvent) {
                         positionChangedEvent->setAccepted(true);
                         m_mouseCurrentPosition = QPoint(positionChangedEvent->x(), positionChangedEvent->y());
                     });
}

QVector3D CustomCameraController::projectToTrackball(const QPoint &screenCoords) const {
    auto sx = float(screenCoords.x()), sy = float(m_windowSize.height() - screenCoords.y());

    QVector2D p2d(sx / float(m_windowSize.width()) - 0.5f, sy / float(m_windowSize.height()) - 0.5f);

    float z;
    float r2 = m_trackballSize * m_trackballSize;
    if (p2d.lengthSquared() <= r2 * 0.5f)
        z = sqrt(r2 - p2d.lengthSquared());
    else
        z = r2 * 0.5f / p2d.length();

    QVector3D p3d(p2d, z);
    return p3d;
}

float clamp(float x) {
    return x > 1 ? 1 : (x < -1 ? -1 : x);
}

void CustomCameraController::createRotation(const QPoint &firstPoint, const QPoint &nextPoint, QVector3D &dir,
                                            float &angle) {
    auto lastPos3D = projectToTrackball(firstPoint).normalized();
    auto currentPos3D = projectToTrackball(nextPoint).normalized();

    dir = QVector3D::crossProduct(currentPos3D, lastPos3D);

    angle = acos(clamp(QVector3D::dotProduct(currentPos3D, lastPos3D)));
}

void CustomCameraController::moveCamera(const InputState &state, float dt) {
    auto theCamera = camera();

    if (theCamera == nullptr)
        return;

    auto ls = linearSpeed();
    if (state.leftMouseButtonActive) {
        QVector3D dir;
        float angle;
        createRotation(m_mouseLastPosition, m_mouseCurrentPosition, dir, angle);

        auto currentRotation = theCamera->transform()->rotation();

        auto rotatedAxis = currentRotation.rotatedVector(dir);
        angle *= m_rotationSpeed;
        theCamera->rotateAboutViewCenter(QQuaternion::fromAxisAndAngle(rotatedAxis, angle * M_1_PI * 180));
    } else if (state.middleMouseButtonActive) {
        auto offset = m_mouseCurrentPosition - m_mouseLastPosition;
        theCamera->translate(QVector3D(float(-offset.x()) / float(m_windowSize.width()) * ls,
                                       float(offset.y()) / float(m_windowSize.height()) * ls,
                                       0));
    } else if (dt != 0) {
        theCamera->translate(QVector3D(state.txAxisValue * ls,
                                       state.tyAxisValue * ls,
                                       state.tzAxisValue * ls) * dt,
                             Qt3DRender::QCamera::DontTranslateViewCenter);
    }
    if (state.rightMouseButtonActive) {
        theCamera->translate(QVector3D(state.rxAxisValue * linearSpeed(),
                                          state.ryAxisValue * linearSpeed(),
                                          state.tzAxisValue * linearSpeed()) * dt);
    }
    m_mouseLastPosition = m_mouseCurrentPosition;
}
