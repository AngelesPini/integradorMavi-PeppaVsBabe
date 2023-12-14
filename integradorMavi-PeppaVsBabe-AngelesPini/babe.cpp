#include "babe.h"
using namespace sf;

Babe::Babe(sf::Texture& textureBabe, float scale) {
    sprite.setTexture(textureBabe);
    sprite.setScale(0.8f, 0.8f);
    sprite.setPosition(rand() % 800, rand() % 600);
    tiempoVida = Clock();
    vivo = true;
}

void Babe::update() {
    if (vivo && tiempoVida.getElapsedTime().asSeconds() > 1.5) {
        vivo = false;
    }
}

void Babe::verificarLimitesVentana(sf::RenderWindow& ventana) {
    sf::Vector2f posicion = sprite.getPosition();


    if (posicion.x < 0) {
        posicion.x = 0;
    }
    else if (posicion.x > ventana.getSize().x) {
        posicion.x = ventana.getSize().x;
    }

    if (posicion.y < 0) {
        posicion.y = 0;
    }
    else if (posicion.y > ventana.getSize().y) {
        posicion.y = ventana.getSize().y;
    }

    sprite.setPosition(posicion);
}