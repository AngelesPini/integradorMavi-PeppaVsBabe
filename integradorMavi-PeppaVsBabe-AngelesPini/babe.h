#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
class Babe {
public:
    Babe(Texture& textureBabe, float scale);

    void update();


    void verificarLimitesVentana(sf::RenderWindow& ventana);


    Sprite sprite;
    bool vivo;
    Clock tiempoVida;
};

