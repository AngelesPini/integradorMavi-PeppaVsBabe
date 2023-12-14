#include "enemigo.h"

using namespace sf;


Enemigo::Enemigo(Texture& texture, float scale, Texture& textureProyectil, float scaleProyectil) {
    spriteProyectil.setTexture(textureProyectil);
    sprite.setTexture(texture);
    spriteProyectil.setScale(0.2f, 0.2f);
    sprite.setScale(0.2f, 0.2f);
    sprite.setPosition(rand() % 800, rand() % 600);
    spriteProyectil.setPosition(rand() % 800, rand() % 600);
    tiempoVida = Clock();
    vivo = true;

}


void Enemigo::update() {
    if (vivo && tiempoVida.getElapsedTime().asSeconds() > 1.5) {
        vivo = false;

    }
}

void Enemigo::verificarLimitesVentana(RenderWindow& App) {
    Vector2f posicion = sprite.getPosition();

    if (posicion.x < 0) {
        posicion.x = 0;
    }
    else if (posicion.x > App.getSize().x) {
        posicion.x = App.getSize().x;
    }

    if (posicion.y < 0) {
        posicion.y = 0;
    }
    else if (posicion.y > App.getSize().y) {
        posicion.y = App.getSize().y;
    }

    sprite.setPosition(posicion);
    //spriteProyectil.setPosition(posicion);
}


