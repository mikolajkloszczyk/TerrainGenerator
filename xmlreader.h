#ifndef XMLREADER_H
#define XMLREADER_H

#include "mapinfo.h"
#include <QString>
#include <QXmlStreamReader>
#include <QFile>
#include <QColor>

//! aKlasa do czytania konfiguracyjnego pliku XML
class XMLReader
{
public:
    //! Domyślny konstruktor
    XMLReader();
    //! Funkcja do wczytywania parametrów mapy z pliku Xml o podanej w parametrze ścieżce
    void loadSetingsFromXml(QString fileName);

    //! Zmienna do której zapisywane są informacje odczytane z pliku Xml
    MapInfo info;
private:
    //! Metoda do wczytywania z pliku Xml rozmiaru mapy
    QVector3D readSize(QXmlStreamAttributes attributes);

    //! Metoda do wczytywania z pliku Xml pozycji mapy
    QVector3D readPosition(QXmlStreamAttributes attributes);

    //! Metoda do wczytywania z pliku Xml koloru
    QColor readColor(QXmlStreamAttributes attributes);

    //! Metoda do dodawania oświetlenia świata
    void readLights(QXmlStreamReader &xmlReader);

    //! Metoda do dodawanie kolorów mapy
    void addColor(QXmlStreamAttributes attributes);
};

#endif // XMLREADER_H
