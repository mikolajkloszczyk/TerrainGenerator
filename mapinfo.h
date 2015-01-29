#ifndef MAPXMLINFO_H
#define MAPXMLINFO_H
#include <QVector3D>
#include <QVector>
#include <QColor>
#include <QDebug>

//! Struktura koloru mapy
struct mapColor
{
    //! Kolor
   QColor color;

   //! Procentowe określenie początku oraz końca względem wysokości malowania mapy danym kolorem
   double heightStart,heightEnd;
};

//! Klasa z informacjami o mapie
class MapInfo
{
public:
    //! Domyślny konstruktor
    MapInfo();

    //! Rozmiar mapy
    QVector3D size;

    //! Pozycja mapy w przestrzeni świata
    QVector3D position;

    //! Wektor kolorów mapy
    QVector <mapColor> mapColors;

    //! Kolor rozbłysków(specular) materiału mapy
    QColor specularColor;

    //! Kolor otoczenia(ambient) materiału mapy
    QColor abientColor;

    //! Ilość oktaw szumu perlina
    int perlinOctaves;

    //! Od której oktawy szumu zaczynami tworzyć mapę
    int perlinOctavesStart;

    //! Zmienna określająca sposób wyświetlania mapy (trójkąty czy linie)
    bool wireframedView;

    //! Ziarno do generatora liczb pseudolosowych
    int seed;

    //! Zmienna określająca czy pokazywać wketory normalne
    bool showNormalVectors;

    //! Określa amplitude przy tworzeniu mapy. Ma wpływ na kształt wynikowej mapy.
    float amplitude;

};

#endif // MAPXMLINFO_H
