#ifndef CREATEMAPPROGRESDIALOG_H
#define CREATEMAPPROGRESDIALOG_H

#include <QDialog>

namespace Ui {
class CreateMapProgresDialog;
}
//! Klasa okna dialogowego z paskiem postępu
class CreateMapProgresDialog : public QDialog
{
    Q_OBJECT

public:
    //! Konstruktor
    explicit CreateMapProgresDialog(QWidget *parent = 0);

    //! Destruktor
    ~CreateMapProgresDialog();

    //! Metoda do ustawiania postępu na pasku postępu
    void setProgressOnBar(float progress);

    //! Metoda do ustawiania tekstu pod paskiem postępu
    void setText(QString text);

    //! Metoda do ustawiania tesktu oraz postępu
    void set(QString text, float progress);
private:

    //! Obiekt okna
    Ui::CreateMapProgresDialog *ui;
};

#endif // CREATEMAPPROGRESDIALOG_H
