#include "mapgeneratedialog.h"
#include "ui_mapgeneratedialog.h"
#include <QTime>
MapGenerateDialog::MapGenerateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapGenerateDialog)
{
    ui->setupUi(this);
}

MapGenerateDialog::~MapGenerateDialog()
{
    delete ui;
}
void MapGenerateDialog::setupStartValuesMap(MapInfo info)
{
    ui->widthX->setValue(info.size.x());
    ui->Hieght->setValue(info.size.y());
    ui->WidthZ->setValue(info.size.z());
    ui->PerlinSteps->setValue(info.perlinOctaves);
    ui->PixelPerRect->setValue(info.perlinOctavesStart);
    ui->frequency->setValue(info.amplitude);
}
MapInfo MapGenerateDialog::returnValuesMap()
{
    MapInfo info;
    info.size.setX(ui->widthX->value());
    info.size.setY(ui->Hieght->value());
    info.size.setZ(ui->WidthZ->value());
    info.perlinOctaves = ui->PerlinSteps->value();
    info.perlinOctavesStart = ui->PixelPerRect->value();
    info.seed = ui->seedText->value();
    info.amplitude = ui->frequency->value();
    return info;
}

void MapGenerateDialog::on_pushButton_clicked()
{
    QTime time = QTime::currentTime();
    uint seed = (abs((time.minute()+1)*(time.second()+1)*(time.hour()+1)*(time.msec()+1)*time.msecsSinceStartOfDay()))%(ui->seedText->maximum()-1000);
    ui->seedText->setValue(seed);
}


