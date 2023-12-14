#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;


class Enemigo {
public:
    Enemigo(Texture& texture, float scale, Texture& textureProyectil, float scaleProyectil);

    void update();
    void verificarLimitesVentana(RenderWindow& App);

    Sprite spriteProyectil;
    Sprite sprite;
    bool vivo;
    Clock tiempoVida;


};
