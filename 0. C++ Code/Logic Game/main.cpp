//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./Chess/CurrentGame.hpp"
#include "./Chess/GameInfo.h"


using namespace std;

int main(int argc, const char* argv[])
{
	//Instruccions necesaries per poder incloure la llibreria i que trobi el main
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO);

	//Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
	Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
	//Mostrem la finestra grafica
	pantalla.show();

	CurrentGame game;
    //game.init(GM_NORMAL, "data/Games/board.txt", "data/Games/movements.txt");
    bool final = false;
    int modeJoc;

    do
    {
        cout << "A quin mode vols jugar? " << endl;
        cout << "1: Normal, 2: Replay" << endl;
        cout << "Introdueix el mode de joc: ";
        cin >> modeJoc;
    } while (modeJoc < 1 || modeJoc > 2);

    if (modeJoc == 1)
    {
        game.init(GM_NORMAL, "data/Games/board.txt", "data/Games/movements.txt");
    }
    else if(modeJoc == 2)
    {
        game.init(GM_REPLAY, "data/Games/board.txt", "data/Games/movements.txt");
    }

    do
    {
        // Captura tots els events de ratolí i teclat de l'ultim cicle
        pantalla.processEvents();

        bool mouseStatus = Mouse_getBtnLeft();
        int mousePosX = Mouse_getX();
        int mousePosY = Mouse_getY();
        final = game.updateAndRender(mousePosX, mousePosY, mouseStatus, modeJoc);
        // Actualitza la pantalla
        pantalla.update();

    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && (!final));
    // Sortim del bucle si pressionem ESC
    if (final)
    {
        Sleep(4000);
    }

    game.end();
    
	//Instruccio necesaria per alliberar els recursos de la llibreria 
	SDL_Quit();
	return 0;
}

