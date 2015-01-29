#include "camera.h"
#include <QDebug>

Camera::Camera(QVector3D cam_position)
{
    alpha = 135;
    beta = 40;
    position = cam_position;
    MouseSensitive = 0.2;
}
Camera::~Camera()
{

}
void Camera::mousePressEvent(QMouseEvent *event)
{
     lastMousePosition = event->pos();
     event->accept();
}
void Camera::mouseMoveEvent(QMouseEvent *event)
{
    int deltaX = event->x() - lastMousePosition.x();
    int deltaY = event->y() - lastMousePosition.y();
    if (event->buttons() & Qt::LeftButton)
    {
        alpha += deltaX*MouseSensitive;
        beta  +=  deltaY*MouseSensitive;
        lastMousePosition = event->pos();
     }
     event->accept();

}
float Camera::radians(float deg)
{
    return deg*0.0174532925;
}
void Camera::keyPressEvent(QKeyEvent* event)
{
    float moveSpeed = 5;
    if(event->key() == Qt::Key_W)
    {
        position.setX(position.x()-moveSpeed*sin(radians(-alpha)));
        position.setZ(position.z()-moveSpeed*cos(radians(-alpha)));
    }
    if(event->key() == Qt::Key_S)
    {
        position.setX(position.x()+moveSpeed*sin(radians(-alpha)));
        position.setZ(position.z()+moveSpeed*cos(radians(-alpha)));
    }
    if(event->key() == Qt::Key_Q)
    {
        position.setY(position.y()+moveSpeed);
    }
    if(event->key() == Qt::Key_E)
    {
        position.setY(position.y()-moveSpeed);
    }
    if(event->key() == Qt::Key_A)
    {
        position.setX(position.x()-moveSpeed*sin(radians(-alpha+90)));
        position.setZ(position.z()-moveSpeed*cos(radians(-alpha+90)));
    }
    if(event->key() == Qt::Key_D)
    {
        position.setX(position.x()-moveSpeed*sin(radians(-alpha-90)));
        position.setZ(position.z()-moveSpeed*cos(radians(-alpha-90)));
    }
}
QMatrix4x4 Camera::camLookAt()
{
    QMatrix4x4 vMatrix;
    vMatrix.setToIdentity();
    vMatrix.rotate(beta, 1, 0, 0 );
    vMatrix.rotate(alpha, 0, 1, 0 );
    vMatrix.translate(-position);
    return vMatrix;
}
