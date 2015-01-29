// window.cpp

#include <QtWidgets>
#include "window.h"
#include "ui_window.h"
#include <QApplication>
#include "myglwidget.h"
#include "mapgeneratedialog.h"
#include "createmapprogresdialog.h"
Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    connect(ui->myGLWidget, SIGNAL(onDrawEnd(float, int, int)), this, SLOT(onGLWidgetDrawed(float, int, int)));
}

Window::~Window()
{
    delete ui;
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
}

void Window::setSeedText(int seed)
{
   ui->seedText->setText("Ziarno mapy: " + QString::number(seed));
}
void Window::setTriangleNumberText(int numOfTriangles)
{
    ui->triangleNumText->setText("Liczba trójkątów: " + QString::number(numOfTriangles));
}

void Window::onGLWidgetDrawed(float drawTime, int infoTrinagles, int infoSeed)
{
   ui->drawTimeText->setText("Czas rysowania ostatniej klatki: " + QString::number(drawTime) + "ms");
   ui->seedText->setText("Ziarno mapy: " + QString::number(infoSeed));
   setTriangleNumberText(infoTrinagles);
}

void Window::on_pushButton_clicked()
{
    MapGenerateDialog* dialog = new MapGenerateDialog(this);
    dialog->setupStartValuesMap(ui->myGLWidget->map->info);
    if(dialog->exec())
    {
        MapInfo info = dialog->returnValuesMap();
        ui->myGLWidget->map->info.size = info.size;
        ui->myGLWidget->map->info.perlinOctavesStart = info.perlinOctavesStart;
        ui->myGLWidget->map->info.perlinOctaves = info.perlinOctaves;
        ui->myGLWidget->map->info.seed = info.seed;
        ui->myGLWidget->map->info.amplitude = info.amplitude;
        if(info.seed == -1)
        {
            QTime time = QTime::currentTime();
            uint seed = abs((time.minute()+1)*(time.second()+1)*(time.hour()+1)*(time.msec()+1)*time.msecsSinceStartOfDay());
            info.seed = seed;
        }
        ui->seedText->setText("Ziarno mapy: " + QString::number(info.seed));
        setTriangleNumberText(info.size.x()*info.size.z()*2);
        CreateMapProgresDialog* dialog2 = new CreateMapProgresDialog();
        dialog2->show();
        QApplication::processEvents();
        ui->myGLWidget->map->create(dialog2);
        ui->myGLWidget->mapDrawer->info = ui->myGLWidget->map->info;
        ui->myGLWidget->mapDrawer->createTrianglesNet();
        ui->myGLWidget->deleteTexture(ui->myGLWidget->mapDrawer->texture);
        ui->myGLWidget->mapDrawer->texture = ui->myGLWidget->bindTexture(*ui->myGLWidget->map->resultImg);
        dialog2->close();
        delete dialog2;
    }
    delete dialog;
}

void Window::on_checkBox_clicked(bool checked)
{
    ui->myGLWidget->map->info.showNormalVectors = checked;
    ui->myGLWidget->mapDrawer->info.showNormalVectors = checked;
}

void Window::on_WireframedView_clicked(bool checked)
{
    ui->myGLWidget->map->info.wireframedView = checked;
    ui->myGLWidget->mapDrawer->info.wireframedView = checked;
}
