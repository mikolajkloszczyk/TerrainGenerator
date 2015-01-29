#include "mapdrawer.h"
#include <QtOpenGL>
#include <GL/gl.h>
MapDrawer::MapDrawer(MapInfo info)
{
    this->info = info;
    this->info.seed = -1;
    this->info.wireframedView = false;
    this->info.showNormalVectors = false;
    buffer = NULL;
    bufferIndex = NULL;
}
MapDrawer::~MapDrawer()
{
}

void MapDrawer::createTrianglesNet()
{
    GLfloat *vertices_tmp;
    GLuint *triangles_tmp;
    if(buffer != NULL)
    {
        buffer->destroy();
        delete buffer;
    }
    buffer = new QGLBuffer(QGLBuffer::VertexBuffer);
    buffer->create();
    buffer->bind();
    if(info.size.x() > 4096)
    {
        info.size.setX(4096);
    }
    if(info.size.z() > 4096)
    {
        info.size.setX(4096);
    }
    try
    {
    vertices_tmp = new GLfloat[(int)(info.size.x()*info.size.z())*3];
    }
    catch(std::exception &e)
    {
        qDebug() << e.what();
    }

    //vertices_tmp.reserve(info.size.x()*info.size.z());
    long long int counter = 0;
    for(int i = 0; i < info.size.x(); i++)
    {
        for(int j = 0; j < info.size.z(); j++)
        {
            vertices_tmp[counter++] = i;
            vertices_tmp[counter++] = 0;
            vertices_tmp[counter++]=  j;
        }
    }
    if(bufferIndex != NULL)
    {
        bufferIndex->destroy();
        delete bufferIndex;
    }
    bufferIndex = new QGLBuffer(QGLBuffer::IndexBuffer);
    bufferIndex->create();
    bufferIndex->bind();
    bufferIndex->setUsagePattern(QGLBuffer::StaticDraw);
    //triangles_tmp.reserve(info.size.x()*info.size.z()*6);
    triangles_tmp = new GLuint[(int)(info.size.x()*info.size.z()*6)];
    counter = 0;
    for(int i = 1; i < info.size.x()-1; i++)
    {
        for(int j = 1; j < info.size.z()-1; j++)
        {
            triangles_tmp[counter++] = (i+1)*info.size.z() + j+1;
            triangles_tmp[counter++] = (i+1)*info.size.z() + j;
            triangles_tmp[counter++] = i*info.size.z() + j;

            triangles_tmp[counter++] = (i+1)*info.size.z() + j+1;
            triangles_tmp[counter++] = i*info.size.z() + j;
            triangles_tmp[counter++] = (i)*info.size.z() + j+1;
        }
    }
    bufferIndex->allocate(info.size.x()*info.size.z()*6 * sizeof(GLuint));
    bufferIndex->write(0,&triangles_tmp[0],info.size.x()*info.size.z()*6 * sizeof(GLuint));
    bufferIndex->release();

    buffer->allocate(info.size.x()*info.size.z() * (3) * sizeof(GLfloat));
    buffer->write(0,&vertices_tmp[0],info.size.x()*info.size.z()* 3 * sizeof(GLfloat));

    buffer->release();
    if(!buffer->isCreated() || !bufferIndex->isCreated())
    {
        qCritical() << "Tworzenie bufora poszło nie tak... ";
    }
    qDebug() << "ilość wierzchołków " << QString::number(info.size.x()*info.size.z()*3);
    qDebug() << "ilość trójkątów " << QString::number(info.size.x()*info.size.z()*6);
    trianglesCount = info.size.x()*info.size.z()*6;
    delete []vertices_tmp;
    delete []triangles_tmp;
}
void MapDrawer::draw(QGLShaderProgram * shaderProgram, QGLShaderProgram * normalShaderProgram, QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QMatrix4x4 mMatrix, QVector3D LightPosition)
{
    if(info.showNormalVectors)
    {
        drawByShader(normalShaderProgram,pMatrix,vMatrix,mMatrix,LightPosition,GL_TRIANGLES_ADJACENCY );
    }
    if(!info.wireframedView)
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        drawByShader(shaderProgram,pMatrix,vMatrix,mMatrix,LightPosition, GL_TRIANGLES);
    }
    else
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        drawByShader(shaderProgram,pMatrix,vMatrix,mMatrix,LightPosition, GL_TRIANGLES);
    }
}
void MapDrawer::drawByShader(QGLShaderProgram * shaderProgram, QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QMatrix4x4 mMatrix, QVector3D LightPosition, int mode)
{
    shaderProgram->bind();
    mMatrix.translate(position);
    shaderProgram->setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);       //ustawiamy wartości zmiennych uniform do shadera
    shaderProgram->setUniformValue("mvMatrix", vMatrix * mMatrix);
    shaderProgram->setUniformValue("normalMatrix", mMatrix.normalMatrix());
    shaderProgram->setUniformValue("vLightPosition", LightPosition);
    shaderProgram->setUniformValue("numColors", info.mapColors.length());
    shaderProgram->setUniformValue("mapSize", info.size);

    for(int i = 0; i < info.mapColors.length(); i++)
    {
        QVector4D color;
        color.setX(info.mapColors[i].color.redF());
        color.setY(info.mapColors[i].color.greenF());
        color.setW(info.mapColors[i].color.alphaF());
        color.setZ(info.mapColors[i].color.blueF());
        shaderProgram->setUniformValue(QString("colors["+QString::number(i)+"].color").toStdString().c_str(), color);
        double startH = info.mapColors[i].heightStart*info.size.y();
        double endH = info.mapColors[i].heightEnd*info.size.y();
        shaderProgram->setUniformValue(QString("colors["+QString::number(i)+"].height").toStdString().c_str(), QVector3D(startH,endH,-1.0));
    }

    glBindTexture(GL_TEXTURE_2D, texture);
    shaderProgram->setUniformValue("texture", 0);

    this->buffer->bind();
    this->bufferIndex->bind();

    shaderProgram->setAttributeBuffer("vertex", GL_FLOAT, 0, 3, 0);
    shaderProgram->enableAttributeArray("vertex");
    buffer->release();
    glDrawElements(mode, trianglesCount, GL_UNSIGNED_INT, 0);         //rysujemy obiekt

    shaderProgram->release();

}
