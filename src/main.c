//motor basico ecs
//basado en el video de fran gallego
//junio 2021
#include "cpctelera.h"
#include "manager/game.h"
//
//inicia el programa
//
void main(){
	/* inicis de programa, pone el mode y tinats*/
	cpct_disableFirmware();

	man_game_init();
	man_game_update();
	man_game_play();
}