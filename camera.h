#ifndef CAMERA_H
#define CAMERA_H

#include <QtOpenGL>
#include <QVector3D>
#include <QMatrix4x4>
#include <QWidget>
#include <QEvent>

//! Klasa do obsługi kamery
class Camera
{
public:

    //! Konstruktor który ustawia kamerę w miejscu podanym w parametrze
    Camera(QVector3D cam_position = QVector3D(0.0f,255.0f,0.0f));

    //! Destruktor
    ~Camera();

    //! Metoda zwracająca macierz widoku kamery
    QMatrix4x4 camLookAt();

    //! Event naciskania przycisku myszy
    void mousePressEvent(QMouseEvent *event);

    //! Event poruszania myszką
    void mouseMoveEvent(QMouseEvent *event);

    //! Event naciskania klawisza myszki
    void keyPressEvent(QKeyEvent* event);
private:

    //! Aktualna pozycja kamery w przestrzeni świata
    QVector3D position;

    //! Zmienne określające ruch myszki po osi X
    double alpha;

    //! Zmienne określające ruch myszki po osi Y
    double beta;

    //! Czułość myszki
    double MouseSensitive;

    //! Zmienna przechowywująca ostatnią pozycje myszki
    QPoint lastMousePosition;

    //! Metoda do zamiany stopni na radiany
    float radians(float deg);



protected:


};


#endif // CAMERA_H
