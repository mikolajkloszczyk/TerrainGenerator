# TerrainGenerator
Aplikacja do automatycznego generowania terenu za pomocą szumu Perlina. Język C++, shadery w GLSL, GUI zostało zrobione w Qt, renderowanie terenu w OpenGL.

Zasada działania aplikacji:
Aplikacja generuje mapę wysokości oraz mapę wektorów normalnych zapisuje ją na GPU (oraz na dysku abyśmy mogli ją wykorzystać w innych programach), następnie tworzy płaską siatkę trójkątów. W vertex shaderze z mapy wysokości odczytuje się wysokość danego wierzchołka i tak tworzy mapę terenu. W fragment shaderze wykorzystałem mapę wektorów normalnych oraz cieniowanie Phonga dzięki czemu uzyskano ładny efekt graficzny oświetlenia.


Widok aplikacji:

![alt tag](https://imagizer.imageshack.us/v2/1763x955q90/661/lDftKs.png)
![alt tag](https://imagizer.imageshack.us/v2/1920x1040q50/661/qpSahV.png)

Wygenerowana mapa wysokości:

![alt tag](https://imagizer.imageshack.us/v2/512x512q90/673/FHlzwk.png)

Wygenerowana mapa wektorów normalnych:

![alt tag](https://imagizer.imageshack.us/v2/512x512q90/661/0GJfdm.png)
