#include "Juego.h"

using namespace sf;


Juego::Juego() : enemigoDesaparecer(seconds(1)), babeDesaparecer(seconds(4.5)) {

    /*ventana*/
    App.create(sf::VideoMode(1200, 800, 32), "Peppa vs Babe");
    App.setMouseCursorVisible(false);

    /*texturas*/
    texture.loadFromFile("peppa.png");
    textureBabe.loadFromFile("babe.png");
    cursorTexture.loadFromFile("crosshair.png");
    textureProyectil.loadFromFile("proyectil.png");
    fondoTexture.loadFromFile("fondo.png");
    fondoSprite.setTexture(fondoTexture);

    cursorSprite.setTexture(cursorTexture);
    cursorSprite.setScale(0.3f, 0.3f);
    cursorSprite.setOrigin(cursorSprite.getGlobalBounds().width / 2, cursorSprite.getGlobalBounds().height / 2);

    /*valores*/
    enemigosDerrotados = 0;
    babesAsesinados = 0;
    vidas = 4;//inician en 4 porque al inciar el juego automaticamente me resta una vida por la Peppa que aparece en pantalla
    puntos = 1;//tuve que colocarlo en uno porque no contabilizaba bien los puntos y no pude hallar el error
    puntajeFinal = 0;

    /*fuentes y textos*/
    font.loadFromFile("Oswald-SemiBold.ttf");

    /*botón*/
    restartButton.setSize(sf::Vector2f(200, 50));
    restartButton.setPosition(500, 500);
    restartButton.setFillColor(Color::Green);

    /*fuentes y textos*/
    restartButtonText.setFont(font);
    restartButtonText.setCharacterSize(20);
    restartButtonText.setFillColor(Color::Black);
    restartButtonText.setString("Reiniciar");
    restartButtonText.setPosition(560, 510);

    texto.setFont(font);
    texto.setCharacterSize(24);
    texto.setFillColor(Color::Black);
    texto.setString("Vidas: 3");
    texto.setPosition(1000, 600);

    texto1.setFont(font);
    texto1.setCharacterSize(24);
    texto1.setFillColor(Color::Black);
    texto1.setString("Peppas eliminadas: ");

    texto2.setFont(font);
    texto2.setCharacterSize(100);
    texto2.setFillColor(Color::Black);
    texto2.setString("GAME OVER");
    texto2.setPosition(350, 200);

    texto3.setFont(font);
    texto3.setCharacterSize(24);
    texto3.setFillColor(Color::Black);
    texto3.setString("Puntaje final: ");
    texto3.setPosition(0, 20);
}

void Juego::ejecutar() {
    while (App.isOpen()) {
        procesarEventos();
        actualizar();
        dibujar();
    }
}

void Juego::procesarEventos() {
    Event event;
    while (App.pollEvent(event)) {
        if (event.type == Event::Closed) {
            App.close();
        }/*eventos del mouse*/
        else if (event.type ==Event::MouseMoved) {
            cursorSprite.setPosition(event.mouseMove.x, event.mouseMove.y);
        }
        else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            verificarColisiones(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
        }
    }
}
bool clicEnEnemigo = false;
void Juego::actualizar() {

    /*ciclo de peppas y babes*/
    for (Enemigo& enemigo : enemigos) {
        if (enemigo.vivo) {
            enemigo.update();
        }
    }

    for (Babe& babe : babes) {
        if (babe.vivo) {
            babe.update();
        }
    }
    /*actualizacion para que aparezcan y desaparezcan las pepas y babes mientras tenga vidas*/
    if (vidas > 0) {
        if (enemigoAparecer.getElapsedTime() >= enemigoDesaparecer) {

            enemigos.emplace_back(texture, 0.4f, textureProyectil, 0.2f);
            enemigoAparecer.restart();
            if (!clicEnEnemigo) {
                /*restar puntos de vida si no se hace click en un enemigo*/
                vidas --;
                texto.setString("Vidas: " + std::to_string(vidas));
            }
            clicEnEnemigo = false;
        }
        if (babeAparecer.getElapsedTime() >= babeDesaparecer) {
            babes.emplace_back(textureBabe, 0.4f);
            babeAparecer.restart();
        }

    }/*caso contrario, "game over"*/
    else {
        restartButton.setPosition(500, 500);
        texto2.setString("GAME OVER");
        texto3.setString("Puntaje final: " + std::to_string(puntajeFinal));
    }
}

void Juego::dibujar() {
    App.clear();
    App.draw(fondoSprite);
    /*mostrar personajes en pantalla*/
    for (Enemigo& enemigo : enemigos) {
        if (enemigo.vivo) {
            App.draw(enemigo.sprite);
            App.draw(enemigo.spriteProyectil);
        }
    }

    for (Babe& babe : babes) {
        if (babe.vivo) {
            App.draw(babe.sprite);
        }
    }
    /*cálculos para ganar o perder segun los enemigos derrotados o las vidas que tenga el jugador*/
    if (enemigosDerrotados == 50) {
        App.draw(texto2);
        App.draw(texto3);
        texto2.setString("WINNER");
        texto3.setString("Puntaje final: " + std::to_string(puntajeFinal));
        App.draw(restartButton);
        App.draw(restartButtonText);
    }else if (vidas <= 0) {
        App.draw(texto2);
        App.draw(texto3);
        App.draw(restartButton);
        App.draw(restartButtonText);
    }    


    App.draw(texto);
    App.draw(texto1);
    App.draw(cursorSprite);

    App.display();
}
/*reiniciar el juego cuando la partida termine*/
void Juego::reiniciarJuego() {
    enemigos.clear();
    babes.clear();
    enemigosDerrotados = 0;
    babesAsesinados = 0;
    vidas = 4;//inician en 4 porque al inciar el juego automaticamente me resta una vida por la Peppa que aparece en pantalla
    puntos = 1;
    puntajeFinal = 0;
    enemigoAparecer.restart();
    babeAparecer.restart();
    restartButton.setPosition(-1000, -1000);
    texto.setString("Vidas: 3");
    texto3.setString("Puntos: 0");
}
/*verificador de disparos*/
void Juego::verificarColisiones(sf::Vector2f cursorPosition) {

    if ((vidas == 0 || enemigosDerrotados == 50) && restartButton.getGlobalBounds().contains(cursorPosition)) {
        reiniciarJuego();//EN LA CONDICION WINNER TIENE UN BUG QUE NO ENTIENDO.
    }
    else {/*logica para la quita y suma de puntaje segun los enemigos impactados*/
        
        for (Enemigo& enemigo : enemigos) {
            for (Enemigo& enemigo : enemigos) {
                if (enemigo.vivo && enemigo.sprite.getGlobalBounds().contains(cursorSprite.getPosition())) {
                    enemigo.vivo = false; 
                    clicEnEnemigo = true;
                    if (enemigosDerrotados++ && puntos++) {
                        enemigosDerrotados + 1;
                        puntos + 1;

                    }
                }    

            }
            texto1.setString("Peppas eliminadas: " + std::to_string(enemigosDerrotados));
            texto3.setString("Puntos: " + std::to_string(puntos));

        }
        /*cálculo de babes impactados para la quita de puntaje final*/
        for (Babe& babe : babes) {
            if (babe.vivo && babe.sprite.getGlobalBounds().contains(cursorSprite.getPosition())) {
                babe.vivo = false;
                babesAsesinados++;
                puntos -= 10;
                puntajeFinal = puntos;
                if (babesAsesinados++) {
                    vidas--;
                }
                texto.setString("Vidas: " + std::to_string(vidas));
                texto3.setString("Puntos: " + std::to_string(puntos));

            }

        }
    }
}
