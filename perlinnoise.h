#ifndef PERLINNOISE_H
#define PERLINNOISE_H
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

//! Klasa z Szumem Kena Perlina
class PerlinNoise
{
public:
    //! Konstruktor
    PerlinNoise(int seed);

    //! Domyślny konstruktor
    PerlinNoise();

    //! Funkcja zwracająca szum dla zadanego x,y,z
    double improvedNoise(double x, double y, double z);

    //! Metoda inicjalizująca obiekt
    void init(int seed);

private:

    //! tablica permutacji
    std::vector<int> p;
    double fade(double t);

    //! interpolacja liniowa
    double lerp(double t, double a, double b);

    //! obliczanie gradientów
    double grad(int hash, double x, double y, double z);
};

#endif // PERLINNOISE_H
