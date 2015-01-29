#include "map.h"
#include <QImage>
#include <QGlobal.h>
#include <QTime>
#include <QDebug>
#include <QColor>
#include <QXmlStreamReader>
#include <QtGlobal>
#include <QVector>
#include <QRgb>
#include <QApplication>
#include "createmapprogresdialog.h"
#include <new>          // std::bad_alloc
#include "perlinnoise.h"
#include <omp.h>
#include <QElapsedTimer>

Map::Map(MapInfo info)
{
    this->info.amplitude = 0.5f;
    this->info = info;
    this->info.showNormalVectors = false;
    this->info.seed = -1;
    this->info.wireframedView = false;

    heightImg = NULL;
    normalImg = NULL;
    resultImg = NULL;
    createFormPerlinNoise(info.size.x(),info.size.z(),info.perlinOctaves,NULL,true);

}
Map::~Map()
{
    if(heightImg != NULL)
        delete heightImg;
    if(normalImg != NULL)
        delete normalImg;
    if(resultImg != NULL)
        delete resultImg;
}

void Map::create(CreateMapProgresDialog *dialog)
{
   createFormPerlinNoise(info.size.x(),info.size.z(),info.perlinOctaves, dialog,true);
}

bool Map::createFormPerlinNoise(int mapSizeX, int mapSizeY, int mapNoiseSteps,CreateMapProgresDialog *dialog, bool saveMapToFile)
{
    QElapsedTimer timer;
    timer.start();
    QTime time = QTime::currentTime();
    if(heightImg != NULL)
        delete heightImg;

    //QImage **images;
    uchar * heightImgData = new uchar[mapSizeX*mapSizeY];
    //uchar **imagesChar = new uchar*[mapNoiseSteps];
    int width = mapSizeX;
    int height = mapSizeY;
    try
    {
        //heightImg = new QImage(mapSizeX,mapSizeY,QImage::Format_RGB888);
        heightImgData = new unsigned char[mapSizeX*mapSizeY];
        //images = new QImage*[mapNoiseSteps];

    }
    catch(std::exception &e)
    {
        qDebug() << "bad_alloc caught: " << e.what() << '\n';
        return false;
    }

    std::mt19937 rng;
    if(info.seed == -1)
    {
        int seed = (time.minute()+1)*(time.second()+1)*(time.hour()+1)*(time.msec()+1);
        rng.seed(seed);
        info.seed = seed;
    }
    else
    {
        rng.seed(info.seed);
    }
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,65536); // distribution in range [1, 6]


    while(pow(2, mapNoiseSteps+1) > mapSizeY)   //zmniejszamy liczbę mapNoiseSteps bo nasz końcowy obrazek byłby mniejszy od 1px
    {
        mapNoiseSteps--;
    }

    PerlinNoise* noise = new PerlinNoise[mapNoiseSteps];
    for(int i = 0; i < mapNoiseSteps; i++)
    {
        noise[i].init(dist6(rng));
        //imagesChar[i] = new unsigned char[mapSizeX*mapSizeY];
    }

    showOnDialog("Tworzenie obrazków.", 0.05f,dialog);

    #pragma omp parallel for
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            //obliczanie średniej ważonej dla poszczególnych map
            double px = 0.0;
            double mass = 0.0;
            for(int k = info.perlinOctavesStart; k < mapNoiseSteps; k++)
            {
                mass += pow(info.amplitude,mapNoiseSteps-k);
                px += (noise[k].improvedNoise(i/pow(2,k+1),j/pow(2,k+1),0)+1)*127.5*pow(info.amplitude,mapNoiseSteps-k);
            }
            heightImgData[(i*width+j)] = px/mass;
        }
    }
    delete []noise;

    showOnDialog("Tworzenie mapy normalnych.", 0.51f,dialog);
    createNormalImage(dialog, heightImgData, width, height);
    return true;

}
void Map::showOnDialog(QString text, float progress,CreateMapProgresDialog* dialog)
{
    static float static_progress = 0.00f;
    if(static_progress < progress)
    {
        static_progress = progress;
        if(dialog != NULL)
        {
            if(info.size.x() > 1500)
            {
                QApplication::processEvents();
            }
            dialog->setProgressOnBar(progress);
            dialog->setText(text);
        }
    }
}

void Map::createNormalImage(CreateMapProgresDialog *dialog, uchar * heightImgData, int width, int height)
{
    if(normalImg != NULL)
    {
        delete normalImg;
    }
    uchar *normalImgData = new uchar[4*width*height];
    #pragma omp parallel for
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            QVector<QVector3D> vertexs;
            vertexs.push_back(QVector3D(i,heightImgData[(i*width+j)]*info.size.y()/256.0f,j));
            if(i != 0 && j != 0)
            vertexs.push_back(QVector3D(i-1,heightImgData[((i-1)*width+j-1)]*info.size.y()/256.0f,j-1));
            if(j != 0)
            vertexs.push_back(QVector3D(i,heightImgData[((i)*width+j-1)]*info.size.y()/256.0f,j-1));
            if(i < width-1 && j != 0)
            vertexs.push_back(QVector3D(i+1,heightImgData[((i+1)*width+j-1)]*info.size.y()/256.0f,j-1));
            if(i < width-1)
            vertexs.push_back(QVector3D(i+1,heightImgData[((i+1)*width+j)]*info.size.y()/256.0f,j));
            if(j < height-1)
            vertexs.push_back(QVector3D(i,heightImgData[((i)*width+j+1)]*info.size.y()/256.0f,j+1));
            if(i != 0 && j < height-1)
            vertexs.push_back(QVector3D(i-1,heightImgData[((i-1)*width+j+1)]*info.size.y()/256.0f,j+1));
            if(i != 0)
            vertexs.push_back(QVector3D(i-1,heightImgData[((i-1)*width+j)]*info.size.y()/256.0f,j));
            QVector3D normal(0.0,0.0,0.0);
            QVector<QVector3D> normalsVec;
            for(int n = 2; n < vertexs.length(); n++)
            {
                normalsVec.push_back(QVector3D::normal(vertexs[0], vertexs[n-1],vertexs[n]));
            }
            for(int n = 0; n < normalsVec.length(); n++)
            {
                normal += normalsVec[n];
            }
            normal *= QVector3D(1/(float)normalsVec.length(),1/(float)normalsVec.length(),1/(float)normalsVec.length());
            normal.normalize();
            normalImgData[4*(i*width + j)] = (uchar)((1-(normal.x()*0.5+0.5f))*255);
            normalImgData[4*(i*width + j)+1] = (uchar)((1-(normal.y()*0.5+0.5f))*255);
            normalImgData[4*(i*width + j)+2] = (uchar)(((normal.z()*0.5+0.5f))*255);
            normalImgData[4*(i*width + j)+3] = (uchar)(((normal.z()*0.5+0.5f))*255);
        }
    }
    heightImg = new QImage(info.size.x(),info.size.z(),QImage::Format_RGB888);
    normalImg = new QImage(info.size.x(),info.size.z(),QImage::Format_RGB888);

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            QColor color;
            color.setRed(heightImgData[i*width+j]);
            color.setGreen(heightImgData[i*width+j]);
            color.setBlue(heightImgData[i*width+j]);
            heightImg->setPixel(i,j,color.rgb());

            color.setRed(normalImgData[4*(i*width+j)]);
            color.setGreen(normalImgData[4*(i*width+j)+1]);
            color.setBlue(normalImgData[4*(i*width+j)+2]);
            normalImg->setPixel(i,j,color.rgb());
        }
    }
    showOnDialog("Zapisywanie mapy wysokości.", 0.50f,dialog);
    heightImg->save("map.png");

    delete []heightImgData;
    delete []normalImgData;
    *normalImg = normalImg->scaled(heightImg->width()*0.5,heightImg->height()*0.5,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    *normalImg = normalImg->scaled(heightImg->width(),heightImg->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);


    if(resultImg != NULL)
        delete resultImg;
    resultImg =  new QImage(info.size.x()*2,info.size.z(),QImage::Format_RGB888);

    for(int i = 0; i < resultImg->width(); i++)
    {
        float progres = (i/(float)resultImg->width())*0.06f;
        showOnDialog("Scalanie tekstur.", 0.95f + progres,dialog);
        for(int j = 0; j < resultImg->height(); j++)
        {
            if(i < heightImg->width())
            {
                resultImg->setPixel(i,j,heightImg->pixel(i,j));
            }
            else
            {
                resultImg->setPixel(i,j,normalImg->pixel(i-normalImg->width(),j));

            }
        }
    }
    if(resultImg->width() > 4096)
    {
       resultImg->scaledToWidth(4096);
       resultImg->scaledToHeight(2048);
    }
    //normalImg->save("normal.png");
    //heightImg->save("map.png");
}
