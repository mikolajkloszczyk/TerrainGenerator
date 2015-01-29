#ifndef MAPGENERATEDIALOG_H
#define MAPGENERATEDIALOG_H

#include <QDialog>
#include "mapinfo.h"
namespace Ui {
class MapGenerateDialog;
}
//! Klasa do okna dialogowego z wyborem parametrów mapy
class MapGenerateDialog : public QDialog
{
    Q_OBJECT

public:
    //! Konstruktor
    explicit MapGenerateDialog(QWidget *parent = 0);

    //! Destru`ktor
    ~MapGenerateDialog();

    //! Metoda do ustawiania w oknie dialogowym informacji o mapie
    void setupStartValuesMap(MapInfo info);

    //! Metoda pobierająca z GUI informacje o mapie
    MapInfo returnValuesMap();
private slots:

    //! Slot zmieniający ziarno losowe
    void on_pushButton_clicked();
private:

    //! Obiekt okna dialogowego
    Ui::MapGenerateDialog *ui;
};

#endif // MAPGENERATEDIALOG_H
