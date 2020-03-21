#ifndef __DOT_TOP_UIDrawnObjectsTextUI___TOP__
#define __DOT_TOP_UIDrawnObjectsTextUI___TOP__
#include "UItextUImenus.h"
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


dot_structure_t*
structural_dots ( void );

#endif
