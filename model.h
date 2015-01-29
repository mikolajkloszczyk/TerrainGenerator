#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QGLShaderProgram>
#include <QGLBuffer>

#include "errorlog.h"
//! Klasa z modelu 3d do wyświetlenia przez OpenGL
class Model
{
public:
    //! Domyślny konstruktor
    Model();

    //! Konstruktor wczytujący model z pliku *.obj oraz biblioteke materiałów do tego modelu z pliku *.mtl
    Model(QString file_name,QString file_name_mtl);

    //! Destruktor
    virtual ~Model();

    //! Metoda rysująca model przez shaderProgram - shader który wyrysuje model, pMatrix - macierz projekcji, vMatrix - macierz widoku, mMatrix - macierz modelu, LightPosition - pozycja światła
    virtual void draw(QGLShaderProgram * shaderProgram, QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QMatrix4x4 mMatrix, QVector3D LightPosition);

    //! Pozycja modelu
    QVector3D position;
protected:

    //! Metoda wczytująca model z pliku *.obj oraz biblioteke materiałów do tego modelu z pliku *.mtl
    void load(QString file_name,QString file_name_mtl);

    //! Liczba trójkątów
    unsigned int trianglesCount;

    //! Wskaźnik na bufor wierzchołków modelu
    QGLBuffer *buffer;

    //! Wskaźnik na bufor indeksów wierzchołków modelu
    QGLBuffer *bufferIndex;
};

#endif // MODEL_H
