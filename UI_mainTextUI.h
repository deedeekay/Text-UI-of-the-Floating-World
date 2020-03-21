#ifndef __MAIN_TEXTUI_HEADER__
#define __MAIN_TEXTUI_HEADER__


#define Usleep(x)										\
({	struct timespec timmey = {0, x * 1000};	\
	nanosleep(&timmey, NULL);						\
})

#define exwye ({\
						xcb_point_t xy = {\
							.x = rx(xres),\
							.y = rx(yres)\
						};\
						xy;\
					})

#define global_gsf GLOBAL_gsf
#define global_gsf_reciprocal  GLOBAL_gsf_reciprocal

#define qwiktag(x)\
		(short_tag_t){.name = x}

#ifndef	isanumber
#define	isanumber(x) (!isnan(x))
#endif

#ifndef TIMEVAR_num_seconds
#define TIMEVAR_num_seconds 1
#endif
#ifndef timevars
#define timevars\
			time_t TIMEVARS_starttime = time(NULL);\
			time_t TIMEVARS_endtime = 0;\
			int TIMEVARS_loopcount = 0;
#define timetop\
			TIMEVARS_endtime = time(NULL);\
			TIMEVARS_loopcount++;
#define timebottom\
			time_t TIMEVARS_ttime = difftime(TIMEVARS_endtime, TIMEVARS_starttime);\
			if(TIMEVARS_loopcount > 20000){\
				TIMEVARS_loopcount = 0;\
				TIMEVARS_starttime = time(NULL);\
			}\
			if(TIMEVARS_ttime == TIMEVAR_num_seconds){\
				printf("\nloops/sec: %d ", TIMEVARS_loopcount/TIMEVAR_num_seconds);\
				TIMEVARS_starttime = time(NULL);\
				TIMEVARS_loopcount = 0;\
			}
#endif
#define VALUEWIDTHCOLUMNS 0

#define byte_t uint8_t


typedef	void(*self_self_force)(void *myself, void *other);


/*	for determining the behavior upon reaching the edges of the screen
** inelastic_ means use the actor's bumper or edge elasticity to accel/decellerate
** decel_ means use decellerando, as if actor was above trigger level to decel
** wraparound is as in old videogames like Atari Combat for the VCS2600
** and bounce explains itself */
typedef enum wraprules { wraparound, decel_wraparound, inelastic_decel_wrap, inelastic_bounce, elastic_bounce, inelastic_decel_bounce } wraprules_t;

#ifndef __drawn_object_clients__
#define __drawn_object_clients__
typedef enum drawn_object_clients { grob = 'g', sprite = 's', centered_sprite = 'c', buff = 'b',
												scoreboard = 'r', textscreen = 't', ppixies = 'x', structural = 'D',
												sequence = 'q', txt_menu = 'm', vector = 'v', label = 'l' ,
												xy_label = 'O'
} drawn_ob_client_t;
#endif
typedef struct bounds{
	_Atomic float			xleft;
	_Atomic float			xright;
	_Atomic float			ytop;
	_Atomic float			ybottom;
	_Atomic float			bumper_elasticity;
	_Atomic float			bounds_decellerando;
	wraprules_t				wraprules;
	_Atomic float			margins;
	_Atomic float			margin_accel;
	_Atomic float			*gsf;
	_Atomic float			*gsf_reciprocal;
	struct bounds 			*next_bounds;
} boundary_rules_t;

typedef struct deltaXY{
	_Atomic float deltax;
	_Atomic float deltay;
}deltaXY_t;

typedef struct velocity_locale{
	_Atomic float	deltax;
	_Atomic float	deltay;
	_Atomic float	*deltax_result;
	_Atomic float	*deltay_result;
	_Atomic float	fxpos;
	_Atomic float	fypos;
	_Atomic float	*gsf;
	_Atomic float	*gsf_reciprocal;
} velocity_locale_t;

typedef struct physical_measures{
	_Atomic float						radius;
	_Atomic float						radius_reciprocal;
	_Atomic float						density;
	_Atomic float						mass;
}phys_measures_t;
/* note on qualities: perhaps the pull or charge may be arbitrary
** or perhaps or calculated acc'ding to universal constant
** sorta like the unversal gravitational constant
~~~~~~~~~~~~
** by charge_formula, which of several algorithms, either as
** by control structure witin functions or as separate functions
** just as there are several ways Newtons gravity is calculated
** in codee */
typedef struct physical_properties{
	_Atomic float			power_law;
	_Atomic float			elasticity;
	union{_Atomic float	charge;//probably == mass * charge_constant?
		_Atomic float		charge_constant;// charge strength per mass like G for Newton's
	};_Atomic float		charge_pole;// +/-, N/S, R/G/B[quarks and gluons]
	_Atomic float			G;
}phys_properties_t;

typedef struct limits_rules{
	_Atomic float		deltamax;
	_Atomic float		deltamin;
	_Atomic float		decellerando;
	_Atomic float		decell_to_min;
}phys_limits_rules_t;

typedef struct rules limits_rules_t;

typedef struct basic_body basic_body_t;

typedef struct basic_signals_st{
	bool	quit_signal;
	bool	vv;
	bool	pause_signal;
	bool	reverse_signal;
	int	pause_signal_interval_millisecs;
	bool	ui_terminal_on_signal;
	bool	grali_mono_text_input_error_signal;
	bool	mobile_labels;
} basic_signals_t;

struct {
	bool	gravA_ready;
	bool	UIthread_ready;
	bool	pixiesA_ready;
	bool	pixiesB_ready;
	bool	vectors_ready;
} readyFlags;
#include "UIgravitatorTextUI.h"


typedef struct body_bucket_generic {
	_Atomic int		*countdown_pointer;
	type_tag_t		identity;
	//if putting buckets into an array
	int				total_num_of_crews;
	int				rank;
	int				crew;
	int				crew_size;
	int				crewmember_sn;
	/* put buckets in an array as well as linking them
	** in a linked list - makes it easy to add arrays as
	** well as individual buckets, all linked
	** if .array_size == 1, we know it's an individual
	** link, if larger it's an array.
	** ???MAYBE? arrays, because of physical locality,
	** could be better for cacheing than individual links??
	*/
//	struct body_bucket	*next_b_bucket;
//	struct body_bucket	*prior_b_bucket;
	moved_collide_pkg_t	collider;
	drawn_object_t			*dot;
	basic_b_body_t			body;
	xy_label_t				label;
	useconds_t				usec_loop_pause;
	useconds_t				msec_loop_pause;
} body_bucket_generic_t;



typedef struct _simple_draw{
	graliob_t				*splash;
	int						refresh_tempo;
	bool						count_fps;
	bool						printtextscreen;
	drawn_object_t const *drawn_object_list_base;
	int						current_fps;
} simple_draw_t;

/***VVVVVVVVVVVVV*** Function like defines *******VVVVVVVVVVVVVVVVVVVVVVV***/
#define xypxz 	({\
					 xcb_point_t xy = {\
					 .x = rx(xres) * pixz,\
					 .y = rx(yres) * pixz\
					 };\
					 xy;\
				 })
;
#include "UI_DrawnObjectsTextUI.h"

/**^^^^^^^^^^^^^^^^^^********^^^^^^^^^^^^^^^^^^*******/
#define marky_mark_time\
			static struct timeval __MARK_TIME_timeval;\
			static uint64_t __MARK_TIME_timey;
#define mark_time\
			gettimeofday(&__MARK_TIME_timeval, NULL);

#define since_mark_time\
			__MARK_TIME_timey = seconds_since(__MARK_TIME_timeval);

#define print_mark_time \
			printf(": %ld", __MARK_TIME_timey);

uint64_t
seconds_since ( struct timeval then ){
	struct timeval nowtime;
	gettimeofday(&nowtime, NULL);
	uint64_t mytime = nowtime.tv_usec - then.tv_usec;
	mytime += 1000000 * (nowtime.tv_sec - then.tv_sec);
	return mytime;
}



//various initializers can check whether to load new config file
// permits more flexibility: different files, different
// values using same labels
char*
load_config ( int crew_number, name_tag_t category ){
	return NULL;
	if(crew_number < 0 || tag_equals_tag(category, name_tag("\0"))){
		return NULL;
	}else if(tag_equals_tag(category, name_tag("configload"))){
		return "TXTUI.cfg";
	}else{
		bug_report("STUB! PASS crew_number < 0 or category.name == name_tag(\"\0\")");
		return NULL;
	}
	return NULL;
}

void
text_UI_exit ( void *message );

void
repeat_lines ( char *line, int howmanytimes, uint64_t repeat_per_second );

void*
simples_and_menu_launcher_UI ( void* unused);

/***************** drawing, drawn_objects *********************/
void
draw_vector_lines ( const vector_lines_t *vec, gralibuf_t *to_draw_in );

void*
simple_draw_thread ( void *data );

bool
draw_DOTS_in_list ( const drawn_object_t *tierwalker );

bool
dot_list_add ( drawn_object_t *dot, int tier );

drawn_object_t*
dot_list_seek ( name_tag_t name );

drawn_object_t*
dot_list_remove ( name_tag_t name );

drawn_object_t*
drawn_object_factory ( type_tag_t DOType, char graphic_type, bool drawme, void *graphic_obj);

bool
dot_list_ordered_print ( const drawn_object_t *DrawnObjectTree_anchor );

void
fill_GLOBAL_dot_anchor ( gralibuf_t *buffer );
/***************** drawing, drawn_objects *********************/
/***************** menus and stuff  *********************/
void
top_menu_UI ( void);
void
UI_context_pixel_particles_first ( void );

void
dot_menus_high_low_switch ( void );
/***************** menus and stuff  *********************/

/*****************graphics  below ***********************************/
void*
load_various_graphics ( char *filename );

void
CreateAndSaveBackgrounds ( int gradient );

bool
saveBackrounds ( int fd, gralibuf_t *img, char *name );

bool
load_bkgrnd ( void );
//start rotation at offset degrees to avoid artifacting
sequence_t*
blue_yellow_saucer_seq ( float size, float steps_to_rotate, float offset );
 //start rotation at offset degrees to avoid artifacting
sequence_t*
greredbluora_spinner_sequence ( float size, float steps_to_rotate, float offset );
// produces graliob to use to make sequence
graliob_t*
blue_yellow_saucer_ob ( int radius );
//produces map used to make _ob
gralimap_t*
blue_yellow_saucermap ( int radius );

graliob_t*
blackmars_ob ( uint32_t color, int16_t x_center, int16_t y_center, uint16_t radius, uint16_t thick );

graliob_t*
bluemars_ob ( uint32_t color, int16_t x_center, int16_t y_center, uint16_t radius, uint16_t thick );

graliob_t*
greredbluora_spinner ( int radius );

gralimap_t*
green_red_blue_orange_spinner ( int radius );
/*****************graphics ***********************************/

#endif
