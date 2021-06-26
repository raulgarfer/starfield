#include "game.h"
#include "manager/entity.h"
#include "system/render.h"
#include "system/fisica.h"
#include "system/ai.h"

#include "sprites/hero_left.h"
#include "sprites/joya.h"
#include "sprites/enemy.h"
#include "sprites/enemy_right.h"


//iniciar entidades
// innicia el entity manager. pone a 0 todo


void wait(u8 n){
	do{
		cpct_waitHalts(2);
		cpct_waitVSYNC();
	}while (n--);
}
//
//funcion para crear entidades
//usa plantillas de entidad
//
Entity_t* man_game_create_template_entity(const Entity_t* templ_e){
	Entity_t* e = man_entity_create(); //creacion de una entidad, devuelta como puntero, llamada e
	cpct_memcpy(e,templ_e, sizeof(Entity_t));		//copia a la direccion e, la entidad template , con el tamaño de la entidad
	return e;										//devuelva puntero a entidad recien creada
}



const  Entity_t enemy_template_e = {
	e_type_movable | e_type_render | e_type_ai,		//type, or aritmetico
	38,96,								//x,y
	SPR_ENEMY_RIGHT_W,
	SPR_ENEMY_RIGHT_H,								//ancho alto	
	1,0,								//velocidad x,y
	spr_enemy_right					//array de punteros de sprites
};
const  Entity_t joya_template_e = {
	e_type_render,		//type, or aritmetico
	70,190,								//x,y
	SPR_JOYA_W,
	SPR_JOYA_H,								//ancho alto	
	0,0,								//velocidad x,y
	spr_joya					//array de punteros de sprites
};

const Entity_t hero_template_e = {
	e_type_movable | e_type_input | e_type_render,		//status de entidad player
	8,12,						// x , y
	HERO_LEFT_W	,				//ancho sprite 
	HERO_LEFT_H	,				//alto 
	0,0,						//v elocidad x y
	hero_left 					//sprite por defecto
};

void man_game_init(){
	sys_render_init();
	man_entity_init();
// 
// cracion de entidades
//crea entidades mientras x no valga 0.
{
	u8 x=30;
	u8 y= 100;
		do{
				Entity_t* e = 	man_game_create_template_entity(&joya_template_e);
					x-=10;
					y-=20;
					e->x = x;
					e->y = y;
		}	while (x!=0);
}
man_game_create_template_entity(&enemy_template_e);
man_game_create_template_entity(&hero_template_e);
	
}
//
void man_game_play(){
	while (1){	
		sys_ai_update();

		sys_physics_update();
	//	sys_generator_update();
		sys_render_update();

		man_entity_update();
		wait(1);
		}	
}	
void man_game_update(){
	}