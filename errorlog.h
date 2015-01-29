#ifndef ERRORLOG_H
#define ERRORLOG_H

#include <QDebug>
#include <QTextStream>
#include <QFile>

//! Klasa zapisywania błędów do pliku
class ErrorLOG
{
private:

    //! Konstruktor
    ErrorLOG();

    //! Destruktor
    ~ErrorLOG();

    //! Plik do którego będziemy zapisywać błędy
    QFile err_file;

    //! Strumień tekstowy powiązany z plikiem err_file
    QTextStream err_stream;

public:

    //! Operator zapisu do pliku
    template < typename T >
    ErrorLOG & operator <<( const T & wypisz )
    {
        err_stream << wypisz;
        return * this;
    }

    //! Singleton klasy ErrorLOG
    static ErrorLOG & getSingleton()
    {
        static ErrorLOG singleton;
        return singleton;
    }
};



#endif // ERRORLOG_H
