#include "MyGLWidget.h"
#include <QGLFunctions>
#include <iostream>
#include <random>

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::DoubleBuffer/* Additional format options */), parent)
{
    timer = new QTimer();
    timer->start(5);
    connect(timer ,SIGNAL(timeout()),this,SLOT(timeout()));
    dttimer = QTime::currentTime();
}
MyGLWidget::~MyGLWidget()
{
    delete timer;

}
QSize MyGLWidget::sizeHint() const
{
    return QSize(640, 480);
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    camera.mousePressEvent(event);
}
void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    camera.mouseMoveEvent(event);
}
void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
    camera.keyPressEvent(event);
}

void MyGLWidget::timeout()
{
    updateGL();
    dt = dttimer.elapsed()/(double)1000;
    dttimer = QTime::currentTime();
}
void MyGLWidget::LoadShaderPorgram()
{
    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, "vertexShader.vsh");       //ładowanie i kompilowanie shaderów
    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, "fragmentShader.fsh");
    shaderProgram.link();


    normalVectorShaderProgram.addShaderFromSourceFile(QGLShader::Vertex, "normalsVertexShader.vsh");
    normalVectorShaderProgram.addShaderFromSourceFile(QGLShader::Fragment, "normalsFragmentShader.fsh");
    normalVectorShaderProgram.addShaderFromSourceFile(QGLShader::Geometry, "normalsGeometryShader.gsh");
    normalVectorShaderProgram.link();

    if(!shaderProgram.isLinked() || !normalVectorShaderProgram.isLinked())
    {
        std::string wyjatek = "Shader nie zliknowany poprawnie!";
        throw wyjatek;  //rzucamy wyjątek
    }

}


void MyGLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);        //włączamy testowanie głębokości
    glEnable(GL_CULL_FACE);         //włączamy obcinanie płaszczyzn tylnych
    glClearColor(0.3,0.7,0.8,1.0);       //ustawiamy czyszczenie bufora koloru na niebieski kolor
    try
    {
        LoadShaderPorgram();
    }
    catch(std::string str)
    {
        qCritical() << str.c_str();
    }
    XMLReader reader;
    reader.loadSetingsFromXml("map.xml");
    map = new Map(reader.info);
    mapDrawer = new MapDrawer(reader.info);
    mapDrawer->createTrianglesNet();
    mapDrawer->texture = bindTexture(*map->resultImg);
    qDebug() << sizeof(GLfloat) << sizeof(GLuint);
}
void MyGLWidget::resizeGL(int width, int height)
{
    if (height == 0)
    {
        height = 1;
    }
    this->height = height;
    this->width = width;
    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) width / (float) height, 0.1, 10000);     //ustawianie macierzy projekcji
    glViewport(0, 0, width, height);
}
double MyGLWidget::dt;
void MyGLWidget::paintGL()
{
    QElapsedTimer timer;
    timer.start();
    int error = glGetError();
    if(error != 0)
    {
        qDebug() << "error " << error;
    }
    static double yRot = 0;
    yRot += dt/2;
    QMatrix4x4 mMatrix;                                     //macierz model
    QMatrix4x4 vMatrix= camera.camLookAt();                 //macierz widoku
    QVector3D LightPosition(sin(yRot)*20000,10000.0,cos(yRot)*20000);                 //obliczamy położenie słońca


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     //czyścimy bufor koloru i głębi
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    
    mapDrawer->draw(&shaderProgram,&normalVectorShaderProgram,pMatrix,vMatrix,mMatrix,LightPosition);

    glDisable(GL_BLEND);
    emit onDrawEnd(timer.elapsed(), map->info.size.x()* map->info.size.z()*2, map->info.seed);
}
