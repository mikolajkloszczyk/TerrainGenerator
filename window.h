// window.h

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSlider>
#include "mapinfo.h"
namespace Ui {
class Window;
}
//! Klasa z głównego okna aplikacji
class Window : public QWidget
{
    Q_OBJECT

public:
    //! Konstruktor
    explicit Window(QWidget *parent = 0);

    //! Destruktor
    ~Window();

protected:
    //! Event naciśnięcia klawisza
    void keyPressEvent(QKeyEvent *event);
private slots:
    //! Slot który wywołuje się po przerysowaniu widgeta opengl, aktualizuje dane takie jak czas rysowania ostatniej klatki, informacje o ilości trójkątów, informacje o używanym aktualnie ziarnie mapy
    void onGLWidgetDrawed(float drawTime, int infoTrinagles, int infoSeed);

    //! Slot wywoływany podczas naciśnięcia klawisza "Generuj nową mape"
    void on_pushButton_clicked();

    //! Slot wywoływany gdy zaznaczymy lub odznaczymy checkBox pokaż wektory normalne
    void on_checkBox_clicked(bool checked);

    //! Slot wywoływany gdy zaznaczymy lub odznaczymy checkBox pokaż linie zamiast trójkątow
    void on_WireframedView_clicked(bool checked);

public slots:
    //! Slot ustawiający ziarno
    void setSeedText(int seed);

    //! Slot ustawiający liczbe trójkątów
    void setTriangleNumberText(int numOfTriangles);
private:

    //! Obiekt okna
    Ui::Window *ui;
};

#endif // WINDOW_H
