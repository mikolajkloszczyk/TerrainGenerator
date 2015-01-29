#ifndef MyGLWidget_H
#define MyGLWidget_H

#include <QtOpenGL>
#include <QGLShaderProgram>
#include <QTime>
#include <QGLFunctions>

#include "model.h"
#include "camera.h"
#include "errorlog.h"
#include "map.h"
#include "xmlreader.h"
#include "mapdrawer.h"

//! Klasa z widgetu OpenGL
class MyGLWidget : public QGLWidget, public QGLFunctions
{
    Q_OBJECT

public:
        //! Konstruktor
        MyGLWidget(QWidget *parent = 0);

        //! Destruktor
        ~MyGLWidget();

        //! Metoda wywoływana przy starcie aplikacji. Zmienia rozmiar okna na taki jaki zwraca ta metoda.
        QSize sizeHint() const;

protected:
        //! Metoda inicjalizująca OpenGL'a, shadery oraz mape.
        void initializeGL();

        //! Metoda która jest wywoływana podczas zmiany rozmiaru okna renderowania
        void resizeGL(int width, int height);

        //! Metoda która rysuje wszystkie obiekty
        void paintGL();

        //! Event naciśnięcia przycisku lub przyscisków myszy
        void mousePressEvent(QMouseEvent *event);

        //! Event przechwytujący przesunięcie myszki
        void mouseMoveEvent(QMouseEvent *event);

        //! Event naciśnięcia przycisku lub przyscisków klawiatury
        void keyPressEvent(QKeyEvent* event);

public:
        //! Obiekt mapy
        Map *map;

        //! Obiekt do rysowania mapy
        MapDrawer *mapDrawer;
private:
        //! Metoda wczytująca shadery
        void LoadShaderPorgram();

        //! Obiekt kamery
        Camera camera;

        //! Macierz projekcji
        QMatrix4x4 pMatrix;             //macierz projekcji

        //! Shader do rysowania mapy
        QGLShaderProgram shaderProgram;

        //! Shader do rysowania wektorów normalnych
        QGLShaderProgram normalVectorShaderProgram;

        //! Timer do odświerzania ekranu
        QTimer *timer;

        //! Zmienna potrzebna do obliczania czasu odświerzania ostatniej klatki
        QTime dttimer;

        //! Różnica w czasie między aktualną klatką a poprzednią
        static double dt;

        //! Wysokość okna renderowania
        float height;

        //! Szerokośc okna renderowania
        float width;

protected: Q_SLOT

    //! Slot wywoływany w momencie zakończenia odliczania przez timer i ponowne przerysowanie sceny
    void timeout();
signals:

    //! Sygnał emitowany podczas zakończenia rysowania sceny
     void onDrawEnd(float, int, int);

};

#endif  // MyGLWidget_H
