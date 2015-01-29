#ifndef MAP_H
#define MAP_H
#include "model.h"
#include "mapinfo.h"
#include "createmapprogresdialog.h"



//! Klasa do tworzenia mapy wysokości oraz mapy normalnych
class Map
{
public:

    //! Konstruktor tworzący mape o zadanych parametrach w parametrze info
    Map(MapInfo info);

    //! Destruktor
    ~Map();

    //! Tworzenie mapy o zadanych parametrach
    bool createFormPerlinNoise(int mapSizeX, int mapSizeY, int mapNoiseSteps, CreateMapProgresDialog *dialog, bool saveMapToFile = true);

    //! Zmienna przechowywująca parametry mapy
    MapInfo info;

    //! Metoda do tworzenia mapy o parametrach zawartych w zmiennej info
    void create(CreateMapProgresDialog *dialog);

    //! Bitmapa wysokości
    QImage *heightImg;

    //! Bitmapa wektorów normalnych
    QImage *normalImg;

    //! Bitmapa wynikowej tekstury która będzie przesłana do GPU
    QImage *resultImg;



    //! Metoda tworząca teksture wektorów normalnych
    void createNormalImage(CreateMapProgresDialog *dialog, uchar *heightData, int width, int height);

    //! Metoda ustawiające dany tekst i postęp na oknie dialogowym
    void showOnDialog(QString text, float progress, CreateMapProgresDialog *dialog);


};



#endif // MAP_H
