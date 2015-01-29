#include "perlinnoise.h"
#include <math.h>
#include <numeric>
PerlinNoise::PerlinNoise(int seed)
{
    init(seed);
}
PerlinNoise::PerlinNoise()
{
}
void PerlinNoise::init(int seed)
{
    p.resize(256);

    // zapełnianie tablicy wartościami od 0 do 255
    std::iota(p.begin(), p.end(), 0);

    // inicjalizacja generatora liczb pseudolosowych przy użyciu ziarna
    std::default_random_engine engine(seed);

    // wymieszanie tablicy
    std::shuffle(p.begin(), p.end(), engine);

    // duplikacja tablicy
    p.insert(p.end(), p.begin(), p.end());
}

double PerlinNoise::improvedNoise(double x, double y, double z)
{
        int X = (int)floor(x) & 255;                //wyszukiwanie wierzchołków sześcianu
        int Y = (int)floor(y) & 255;
        int Z = (int)floor(z) & 255;
        x -= floor(x);                              //znajdowanie relatywnych punktów x,y,z sześcianu
        y -= floor(y);
        z -= floor(z);
        double u = fade(x),                          //obliczenie przejść dla x,y,z
               v = fade(y),
               w = fade(z);
        int A = p[X  ]+Y, AA = p[A]+Z;
        int AB = p[A+1]+Z;
        int B = p[X+1]+Y, BA = p[B]+Z;
        int BB = p[B+1]+Z;

        return lerp(w, lerp(v, lerp(u, grad(p[AA  ], x  , y  , z   ),  //dodanie i interpolacja 8 wierzchołków sześcianu, zwrócenie wartości
               grad(p[BA  ], x-1, y  , z   )),
               lerp(u,grad(p[AB  ], x  , y-1, z   ),
               grad(p[BB  ], x-1, y-1, z   ))),
               lerp(v, lerp(u, grad(p[AA+1], x  , y  , z-1 ),
               grad(p[BA+1], x-1, y  , z-1 )),
               lerp(u, grad(p[AB+1], x  , y-1, z-1 ),
               grad(p[BB+1], x-1, y-1, z-1 ))));

}
double PerlinNoise::fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}
double PerlinNoise::lerp(double t, double a, double b)
{
    return (a + t * (b - a));
}
double PerlinNoise::grad(int hash, double x, double y, double z)
{
   int h = hash & 15;                      //zamienia najmłodsze 4 bity tablicy haszującej na 12 kierunków gradientu
   double u = h<8 ? x : y,
          v = h<4 ? y : h==12||h==14 ? x : z;
   return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}



