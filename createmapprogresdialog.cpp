#include "createmapprogresdialog.h"
#include "ui_createmapprogresdialog.h"
#include <QDebug>
CreateMapProgresDialog::CreateMapProgresDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateMapProgresDialog)
{
    ui->setupUi(this);
}

CreateMapProgresDialog::~CreateMapProgresDialog()
{
    delete ui;
}
void CreateMapProgresDialog::setProgressOnBar(float progress)
{
    this->ui->progressBar->setValue(progress * 100);
}
void CreateMapProgresDialog::setText(QString text)
{
    this->ui->label->setText(text);
   // qDebug() << text;
}
void CreateMapProgresDialog::set(QString text, float progress)
{
    setProgressOnBar(progress);
    setText(text);
}
