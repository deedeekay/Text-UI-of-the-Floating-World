#ifndef __DOT_TOP_UIDrawnObjectsTextUI___TOP__
#define __DOT_TOP_UIDrawnObjectsTextUI___TOP__
#include "grali_animation_inlines.h"
//#include "UItextUImenus.h"
#include <pthread.h>
#include "grali_defines.h"
#include "grali_graph.h"

//#define __dbug_tiers__
#undef __dbug_tiers__


#ifdef __dbug_tiers__
static int enoff = 30;
#endif
pthread_mutex_t dot_list_mtx = PTHREAD_MUTEX_INITIALIZER;

void make_tiers ( int );

#define no_draw(x) x->drawme = false

#ifndef __drawn_object_clients__
#define __drawn_object_clients__
typedef enum drawn_object_clients { grob = 'g', sprite = 's', centered_sprite = 'c', buff = 'b',
												scoreboard = 'r', textscreen = 't', ppixies = 'x', structural = 'D',
												sequence = 'q', txt_menu = 'm', vector = 'v', label = 'l' ,
												xy_label = 'O'
} drawn_ob_client_t;
#endif

typedef struct dot_structural_element{
	drawn_object_t 	*prior_tier;
	drawn_object_t 	*next_tier;
	drawn_object_t 	*prior_place;
	drawn_object_t 	*next_place;
	type_tag_t 			DOType;
	name_tag_t 			DOname;
	drawn_ob_client_t	object_type;
	#ifdef __dbug_tiers__
	int					tier;
	int					place;
	#endif
}dot_structure_t;


typedef struct drawn_objects{
	drawn_object_t 	*prior_tier;
	drawn_object_t 	*next_tier;
	drawn_object_t 	*prior_place;
	drawn_object_t 	*next_place;
	type_tag_t 			DOType;
	name_tag_t 			DOname;
	drawn_ob_client_t	object_type;
	#ifdef __dbug_tiers__
	int				tier;
	int				place;
	#endif
	bool					drawme;
	union{
		xcb_point_t		xy_coord;
		struct{
			int16_t		x;
			int16_t		y;
		};};union{
		graliob_t 			*ob;
		gralibuf_t			*buf;
		particle_pixels_t *partipix;
		textscreen_t		*tscrn;
		vector_lines_t		*vec;
		xy_label_t			*label;
	};
	union{
		sequence_t		*seq;
		menu_t			*menu;
		scoreboard_t	*scrbrd;
	};
	int frame_update_count;
	int counter_4_frame_update;
	bool					*drawn_flag;
}drawn_object_t;

/*
SUPPOSED to scan through all the drawing tree and find the one
-and there is supposed to ONLY be one - pair of menus where
one of them is set to draw and other is not, and to set
*/
#define equal(nm1, nm2)\
	({char *nmptr = (char*)&nm1->DOname.name_tag, *nmptr2 = (char*)&nm2->DOname.name_tag;\
	(!strncmp(nmptr + 5, nmptr2 + 5, 9));})


drawn_object_t*
dot_list_seek ( name_tag_t name );

void
dot_menus_high_low_switch ( void );

drawn_object_t*
dot_list_remove ( name_tag_t name );

bool
dot_list_add ( drawn_object_t *dot, int tier);

bool
draw_DOTS_in_list ( const drawn_object_t *tierwalker );

drawn_object_t*
drawn_object_factory ( name_tag_t name, char graphic_type, bool drawme, void *graphic_obj);

void*
simple_draw_thread ( void *data );

void
fill_GLOBAL_dot_anchor ( gralibuf_t *buffer );

dot_structure_t*
structural_dots ( void );

void
make_tiers ( int num_tiers );

#endif
