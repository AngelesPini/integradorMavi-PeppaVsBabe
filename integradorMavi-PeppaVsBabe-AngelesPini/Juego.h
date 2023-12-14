#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "enemigo.h"
#include "babe.h"


using namespace sf;

class Juego {
public:
    Juego();

    void ejecutar();

private:
    void procesarEventos();
    void actualizar();
    void dibujar();


    RenderWindow App;
    Texture texture;
    Texture textureBabe;
    Texture cursorTexture;
    Texture textureProyectil;
    Sprite cursorSprite;
    Texture fondoTexture;
    Sprite fondoSprite;
    std::vector<Enemigo> enemigos;
    std::vector<Babe> babes;
    int enemigosDerrotados;
    int babesAsesinados;
    int vidas;
    int puntos;
    int puntajeFinal;
    Clock enemigoAparecer;
    Time enemigoDesaparecer;
    Clock babeAparecer;
    Time babeDesaparecer;
    Font font;
    RectangleShape restartButton;
    Text restartButtonText;
    /*la logica de restart la busqué en google https://comohacerjuegos.blogspot.com/2013/02/el-primer-juego-en-sfml-20-ii-asteroid.html*/
    Text texto;
    Text texto1;
    Text texto2;
    Text texto3;

    void reiniciarJuego();
    void verificarColisiones(sf::Vector2f cursorPosition);

};


