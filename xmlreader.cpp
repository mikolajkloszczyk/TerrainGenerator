#include "xmlreader.h"
XMLReader::XMLReader()
{
}
void XMLReader::loadSetingsFromXml(QString fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        while (!xmlReader.isEndDocument() && !xmlReader.hasError() )
        {
            xmlReader.readNext();
            if(xmlReader.name() == "Map")
            {
                continue;
            }
            if (xmlReader.isStartElement() && xmlReader.name() == "SizeSettings")
            {
                QXmlStreamAttributes attributes = xmlReader.attributes();
                if(attributes.hasAttribute("perlinSteps"))
                {
                       info.perlinOctaves = attributes.value("perlinSteps").toInt();
                }
                if(attributes.hasAttribute("pixelPerRect"))
                {
                       info.perlinOctavesStart = attributes.value("perlinOctavesStart").toInt();
                }
                info.size = readSize(attributes);
            }
            if (xmlReader.isStartElement() && xmlReader.name() == "WorldLight")
            {
                readLights(xmlReader);
            }
            if (xmlReader.isStartElement() && xmlReader.name() == "AddColor")
            {
                QXmlStreamAttributes attributes = xmlReader.attributes();
                addColor(attributes);
            }
        }
    }
}
void XMLReader::addColor(QXmlStreamAttributes attributes)
{
    mapColor color;
    color.heightEnd = 0;
    color.heightStart = 0;
    color.color = readColor(attributes);
    if(attributes.hasAttribute("heightEnd"))
    {
           color.heightEnd = attributes.value("heightEnd").toFloat();
    }
    if(attributes.hasAttribute("heightStart"))
    {
           color.heightStart = attributes.value("heightStart").toFloat();
    }
    info.mapColors.push_back(color);
}

void XMLReader::readLights(QXmlStreamReader &xmlReader)
{
    xmlReader.readNext();
    while (xmlReader.name() != "WorldLight")
    {
        if (xmlReader.isStartElement() && xmlReader.name() == "AbientColor")
        {
            QXmlStreamAttributes attributes = xmlReader.attributes();
            info.abientColor = readColor(attributes);
        }
        if (xmlReader.isStartElement() && xmlReader.name() == "SpecularColor")
        {
            QXmlStreamAttributes attributes = xmlReader.attributes();
            info.specularColor = readColor(attributes);
        }
        xmlReader.readNext();
    }
}

QVector3D XMLReader::readSize(QXmlStreamAttributes attributes)
{
    QVector3D sizeVector;
    if(attributes.hasAttribute("height"))
    {
           sizeVector.setY(attributes.value("height").toFloat());
    }
    if(attributes.hasAttribute("widthX"))
    {
           sizeVector.setX(attributes.value("widthX").toInt());
    }
    if(attributes.hasAttribute("widthZ"))
    {
           sizeVector.setZ(attributes.value("widthZ").toInt());
    }
    return sizeVector;
}
QVector3D XMLReader::readPosition(QXmlStreamAttributes attributes)
{
    QVector3D positionVector;
    if(attributes.hasAttribute("x"))
    {
          positionVector.setX(attributes.value("x").toFloat());
    }
    if(attributes.hasAttribute("y"))
    {
           positionVector.setY(attributes.value("y").toFloat());
    }
    if(attributes.hasAttribute("z"))
    {
          positionVector.setZ( attributes.value("z").toFloat());
    }
    return positionVector;
}
QColor XMLReader::readColor(QXmlStreamAttributes attributes)
{
    QColor color;
    if(attributes.hasAttribute("r"))
    {
          color.setRedF(attributes.value("r").toDouble());
    }
    if(attributes.hasAttribute("g"))
    {
          color.setGreenF(attributes.value("g").toDouble());
    }
    if(attributes.hasAttribute("b"))
    {
          color.setBlueF(attributes.value("b").toDouble());
    }
    if(attributes.hasAttribute("a"))
    {
          color.setAlphaF(attributes.value("a").toDouble());
    }
    return color;
}
