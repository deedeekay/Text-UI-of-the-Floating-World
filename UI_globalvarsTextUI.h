#ifndef __GLOBALS_TEXTUI__
#define __GLOBALS_TEXTUI__

#include <sys/time.h>
#include "grali_defines.h"
#include "grali_mono_text.h"
#include "UIpixelparticlesTextUI.h"
//typedef struct body_bucket body_bucket_t;

char	*cfgfilename;
bool	fullscreen,
		decor;
int 	squarxel_size;

//Initializing variables above
#define GLOBAL_gravitator_launch_countdown number_gravitators
#define GLOBAL_draw_ready_countdown draw_ready_countdown
#define GLOBAL_tempo_control global_tempo_control
//#define GLOBAL_pixies_init_start pixies_can_start_initing
#define GLOBAL_drawnob_add_mtx drawnob_add_mtx
#define GLOBAL_mobile_txtscrn mobile
#define GLOBAL_fps_report global_fps_report
#define GLOBAL_wraprules global_wraprules

drawn_object_t	*GLOBALtext_hi, *GLOBALtext_lo;
pthread_cond_t		GLOBCOND_quit_condition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t	GLOBMTX_quit_condtion_mutex = PTHREAD_MUTEX_INITIALIZER;
graliob_t 		*splash;
//sequence_t 		*globxhairs;
//sequence_t 		*crosshairs;
//textscreen_t	mobile;
/*^^^^not labelled "global" but nonetheless global variables ^^^*/
_Atomic int GLOBAL_num_gravitator_A_crews;//number_gravitator_A_crews;
body_bucket_t **GLOBAL_gravitator_group_A_array;
_Atomic float	GLOBAL_gsf,
		  			GLOBAL_gsf_reciprocal;
drawn_object_t 		*GLOBAL_dot_anchor;
basic_signals_t		GLOBAL_basic_signals = {.vv = true,
															.quit_signal = false,
															.pause_signal = true,
															.ui_terminal_on_signal = false,
															.reverse_signal = false,
															.pause_signal_interval_millisecs = 0,
															.grali_mono_text_input_error_signal = false,
															.mobile_labels = false
															};
phys_measures_t 		GLOBAL_pixie_phys_measures;
phys_properties_t		GLOBAL_pixie_phys_properties;
boundary_rules_t		GLOBAL_pixie_rules;
phys_limits_rules_t	GLOBAL_pixie_phys_limits;
pixie_algo_vars_t		GLOBAL_pixie_algo_switches;
struct {
	 bool menus_visible;
	 bool menus_transparent;
	 bool menus_above_animation;
//	 bool menus_text_unbacked;
	 bool global_text_visible;
	 bool global_text_above_animation;
//	 bool terminal_on;
 } GLOBAL_text_ui_state = {	.menus_visible = true,
										//	.menus_transparent = false,
										//	.menus_text_unbacked = false,
											.menus_above_animation = false
										//	.global_text_above_animation = true,
										//	.global_text_visible = true
									};
//extern const type_tag_t	gravitator_tg;
/*
extern const type_tag_t	collider_tg;
extern const type_tag_t	vector_lines_tg;
extern const type_tag_t	pixies_tg;
extern const type_tag_t	drawn_object_tg;
extern const type_tag_t	drawn_ob_tiers_tg;
extern const type_tag_t	textscreen_tg;
extern const type_tag_t	mobile_label_tg;
extern const type_tag_t	body_bucket_tg;
extern const type_tag_t	b_body_t_tg;
extern const type_tag_t	b_body_loop_data_tg;
extern const type_tag_t	velocity_locale_tg;
extern const type_tag_t	b_body_measures_tg;
extern const type_tag_t	b_body_properties_tg;
extern const type_tag_t	b_body_bounds_tg;
extern const type_tag_t	b_body_rules_tg;
extern const type_tag_t	b_body_physics_switches_tg;
extern const type_tag_t	vect_lines_loop__tg;
extern const type_tag_t	scoreboard_stack_history_tg;
extern const type_tag_t	scoreboard_tg;
extern const type_tag_t	scoreboard_store_tg;
extern const type_tag_t	scoreboard_items_store_tg;
extern const type_tag_t	scoreboard_items_tg;
extern const type_tag_t	menu_tg;
extern const type_tag_t	menu_state_tg;
extern const type_tag_t	menu_items_tg;
extern const type_tag_t	code_words_tg;
*/
#endif
