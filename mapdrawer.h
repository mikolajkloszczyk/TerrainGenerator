#ifndef MAPDRAWER_H
#define MAPDRAWER_H
#include "model.h"
#include "map.h"
#include <QGLShaderProgram>
#include <QMatrix4x4>
#include <QVector3D>

//! Klasa do rysowania mapy
class MapDrawer : public Model
{
public:
    //! Konsturktor
    MapDrawer(MapInfo info);

    //! Destruktor
    virtual ~MapDrawer();

    //! Metoda do tworzenia siatki trójkątów
    void createTrianglesNet();

    //! Metoda do rysowania mapy
    virtual void draw(QGLShaderProgram * shaderProgram,QGLShaderProgram * normalShaderProgram,QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QMatrix4x4 mMatrix, QVector3D LightPosition);

    //! Tekstura mapy
    GLuint texture;

    //! Informacje o aktualnie rysowanej mapie
    MapInfo info;
private:

    //! Metoda do rysowania mapy
    virtual void drawByShader(QGLShaderProgram * shaderProgram, QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QMatrix4x4 mMatrix, QVector3D LightPosition, int mode);
};


#endif // MAPDRAWER_H
