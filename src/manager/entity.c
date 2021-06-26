#include "entity.h"

Entity_t 	m_entities[Max_entities];			//se crea un array de x en_tidades, llamado entities, con los valores del struct Entity_t
u8			m_zero_type_at_theend; 		//pone un cero al final de las entidades, para poner entidad no valida
Entity_t* 	m_next_free_entity;		//crea un puntero a una entidad ,llamada next free entity,ahora es la 0,la primera
u8 			m_num_entities;			//numero de entidades reservadas 
//
//iniciar entidades
// innicia el entity manager. pone a 0 todo
void man_entity_init(){
	cpct_memset(m_entities,0,sizeof(m_entities));		//llena de 0 el array m_entities
	m_next_free_entity = m_entities;	//variable que apunta al vector primero del array de entidades
	m_num_entities=0;	//inimcia a 0 la variable reserved_entities
	m_zero_type_at_theend = e_type_invalid;
}
//
//creacion de entidades
//devuelve un puntero a entidad y incrementa en iuno la siguiente entidad kibre
//return entity_t* (punt4ero a la entidad recien creada)
/*	ld	bc, (_m_next_free_entity)
	ld	hl, #0x0005
	add	hl,bc
	ld	(_m_next_free_entity), hl*/
//precondicion debe haber espacio disponible en array de m_entities
Entity_t* man_entity_create(){
	Entity_t* e= m_next_free_entity;		//crea un puntero (e) que es la direccion next free entity
	m_next_free_entity = e+1;				// incrementa en 1 la variable next entity
	e->type = e_type_default;
	++m_num_entities;
	return e;								//devuelve el puntero a entidad
}		
//DESTROY
//destruye una entidad dada y libera su memoria asignada
//input;
// dead_e puntero a la entidad a ser destruida
//precondicion; dead_e debe apuntar a una entidad valida

void man_entity_destroy(Entity_t* dead_e){
	Entity_t* de= dead_e;
	Entity_t* last = m_next_free_entity;		//calcula la ultima posicion ocupada
		--last;
		if (de!=last){
			cpct_memcpy(dead_e,last,sizeof(Entity_t));	//crea una entidad nueva
			last->type =e_type_invalid;}
	m_next_free_entity = last;
		--m_num_entities;
	//dead_e -> type = e_type_invalid;
}
//
//input updfunc puntero a la funcion de actualizacion
//calls a given update function for all valid entioties. update entity and return void
//input: -pdsfunc:puntero a la funcion update
void man_entity_forall(void (*updfunc)(Entity_t*) ){
	Entity_t* e= m_entities;
	while (e->type != e_type_invalid){
		updfunc(e);
		++e;}
}
//
//input updfunc puntero a la funcion de actualizacion
//calls a given update function for all valid entioties. update entity and return void
//input: -pdsfunc:puntero a la funcion update
void man_entity_forall_matching(void (*updfunc)(Entity_t*),u8 signature ){
	Entity_t* e= m_entities;
	while (e->type != e_type_invalid){
		if ( (e->type & signature) == signature)	
			updfunc(e);
			++e;
			}
}
//marca para destruir
//input ; dead_e puntero a la entidad a destruir
//precondicion dead debe marcar a una entidad valida
void man_entity_set4destruction(Entity_t* dead_e){
	dead_e-> type |= e_type_dead;
}
//update
//actualiza el maneger de entidades destruyendo la entida marcada
void man_entity_update(){
	Entity_t* e = m_entities; //crea un puntero al ini{cio del array de entidaddes,llamado 'e'
		while (e->type != e_type_invalid){		//es invalida??
			if(e->type & e_type_dead) 	{	//0x80 o 0x00  // es dead?
					man_entity_destroy(e);}
					else {
				++e;}
		}
}
//FREE SPACE
//devuelve el numero de entidades libres
//u8 numero de entiudades libres
u8 man_entity_freeSpace(){
	return Max_entities - m_num_entities;
}
