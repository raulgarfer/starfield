#pragma once
#include "cpctelera.h"

//pone el numero maximo de entidades
#define Max_entities 10
//
//creacion de struct de entidad. son variables de distinto tipo, que se llama Entity_t
//
#define e_type_dead 	0x80		//ob10000000
#define e_type_invalid 	0x00			
#define e_type_render 	0x01		//0b00000001
#define e_type_movable 	0x02		//0b00000010 entidad con bit activo de movil, cambia x y/o y en algun momento
#define e_type_input 	0x04		//0b00000100 entidad con bit activo como input, se puede manejar con teclado
#define e_type_ai	 	0x08		//0b00001000 entidad con bit actrivo como IA			

#define e_type_default  0x7F

typedef struct te{
	u8 	type;			//tipo de entidad
	i8 	x,y;			//x e y de entidad	
	u8 	w,h;			//ancho, alto de entidad
	i8 	vx,vy;			//velocidad x e y de entidad
	u8* sprite;			//puntero a sprite
}Entity_t;
/*
	funciones publicas
*/
void 		man_entity_init();
Entity_t* 	man_entity_create();
void 		man_entity_destroy(Entity_t* dead_e);
void 		man_entity_forall(void (*updfunc)(Entity_t*) );
void 		man_entity_set4destruction(Entity_t* dead_e);
void		man_entity_update();
u8 			man_entity_freeSpace();
void 		man_entity_forall_matching(void (*updfunc)(Entity_t*),u8 signature );
