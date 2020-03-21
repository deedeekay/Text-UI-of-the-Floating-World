#ifndef __MAIN_BODY_TEXTUI__
#define __MAIN_BODY_TEXTUI__
#define _GNU_SOURCE
#include <math.h>
#include <x86_64-linux-gnu/sys/resource.h>
#include <sys/types.h>
#include <stdatomic.h>
#include <X11/Xlib-xcb.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sched.h>
#include <stdbool.h>
#include <time.h>
#include <float.h>
#include <stddef.h>
#include <sys/time.h>
#include "grali_mono_text.h"
#include "grali_animation_inlines.h"
#include "UI_globalvarsTextUI.h"
#include "UI_commonTextUI.h"
#include "grali_simple_txt.h"
#include "grali_animation_inlines.h"
#include "lthread.h"
#include "coroutine.h"
#include "Lay_Z_file.h"
#include "grali_defines.h"
#include "grali_graph.h"
#include "errorlib.h"
#include "grali_animation.h"
#include "configreader.h"
#include "grali_usa_qwerty_keybd.h"
#include "UI_mainTextUI.h"
#include "UI_globalvarsTextUI.h"
//_Atomic int GLOBAL_num_gravitator_A_crews;m
#include "UItextUImenus.h"
#include "UI_commonTextUI.h"
#include "UIgravitatorTextUI.h"
#include "grali_simple_txt.h"
#include "grali_usa_qwerty_keybd.h"
#include "UIspritesTextUI.c"
#include "UIgravitatorTextUI.c"
#include "UI_DrawnObjectsTextUI.h"
#include "UI_DrawnObjectsTextUI.c"
#include "UIpixelparticlesTextUI.c"
#include "UItextUImenus.c"
#include "UItextUI.c"
#include "UIvectorlinestextUI.c"

void
keypress ( xcb_key_press_event_t *ev){
	if(ctrl('q')||(ev->detail == 9)){
		text_UI_exit("ctrl-'q' or esc caught by keypress()");
	}
}// end keypress



#define KEVENTS_Q 20000

#define MAX 10
#define COLMOD 4
int	reps = 10000,
		max = MAX,
		aux = 0;


void
hidekeypress ( xcb_key_press_event_t *ev){
	/*static int index = -5;
	index++;
	if(kevents_Q_andfree ( ev, index )){
		printf("\n~index: %d~~~~keypress queued, something returned YES EV", index);
	}else{
		printf("\n~~~~~keypress queued, nothing returned to index: %d  YES EV", index);
	}

	if(kevents_Q_andfree ( NULL, index )){
		printf("\n~index: %d~~~~keypress queued, something returned. ev = NULL", index);
	}else{
		printf("\n~~~~~keypress queued, nothing returned to index: %d..ev = NULL", index);
	}

	if(kevents_Q_andfree ( ev, -1 )){
		printf("\n~index: -1~~~~keypress queued, something returned. ev = yes");
	}else{
		printf("\n~~~~~keypress queued, nothing returned to index.ev= yes");
	}*/
	if(ctrl('q')||(ev->detail == 9)){
		text_UI_exit("ctrl-'q' or esc caught by keypress()");
	}

	if(ctrl('m')){
		GLOBAL_text_ui_state.menus_visible = !GLOBAL_text_ui_state.menus_visible;
		GLOBAL_basic_signals.ui_terminal_on_signal = !GLOBAL_basic_signals.ui_terminal_on_signal;
	}else	if(ctrl('t')){
		GLOBAL_text_ui_state.global_text_visible = !GLOBAL_text_ui_state.global_text_visible;
	}
	if(alt('m') ){
		if(GLOBAL_text_ui_state.menus_visible){
			GLOBAL_text_ui_state.menus_above_animation = !GLOBAL_text_ui_state.menus_above_animation;
			dot_menus_high_low_switch();
		}
	}else	if(alt('t')){
		if(GLOBAL_text_ui_state.global_text_above_animation){
			GLOBALtext_hi->drawme = false;
			GLOBALtext_lo->drawme = true;
			GLOBAL_text_ui_state.global_text_above_animation = false;
		}else{
			GLOBALtext_hi->drawme = true;
			GLOBALtext_lo->drawme = false;
			GLOBAL_text_ui_state.global_text_above_animation = true;
		}
	}
}// end keypress

void
testrands(int reps, uint16_t max){
	static int testarray1[MAX];
	double  freps  = reps , fmax  = max;
	freps *= fmax;
//	int seed = seconds_since(starttime);
//	srand(seed);
	printf("\n");
	printf("\n");
	for(int i = 0; i < (MAX * reps); i++){
		uint16_t intvalue = rx(MAX );
	//	printf("\nintgrand #: %3d returned: %3d given a maximum value parameter of: %3d", i, intvalue, max );
		if(intvalue > MAX  || intvalue < 0){
			printf("\nintgrand returned: %d given a maximum value parameter of: %d", intvalue, MAX );
		} else{
			testarray1[intvalue] += 1;
		}
	//	if(grali_shortrand(40) > 39){
	//		seed = seconds_since(starttime);
	//		srand(seed);
	//	}
	}
	printf("\n");
	double  avgfavg = 0;
	double  iavg = 0;
	double  offavg = 0, groffavg = 0;
	int bigoff;
	for(int i = 0; i < MAX ; i++){
		double  flarray = testarray1[i];
		double  avg =
		 flarray / reps;
		 iavg += avg;
		printf("[%5d]: %5d .. avg: %5f\t", i, testarray1[i], avg);
		if(fabs(1.0 - avg) > groffavg){
			groffavg = fabs(1.0 - avg);
			bigoff = i;
		}
		offavg += fabs(1.0 - avg);
		if(!((i + COLMOD)%COLMOD)) printf("\n");
		avgfavg += flarray;
	}
	avgfavg /= freps;
	offavg /= MAX;
	iavg /= MAX;
	printf("\n\naverage average: %f .. iavg: %f .. avg. off-avg: %f", avgfavg, iavg, offavg);
	printf("\nrange: 0 - %5d \treps: %5d", MAX, reps);
	printf("\ngreatest amount off was [%5d]=%5d by this much: %f", bigoff, testarray1[bigoff], groffavg);
	printf("\n");
	printf("\n");
	exit(0);
}

void
text_UI_exit ( void *message ){
	#define message (char*)message
	if(!message){
		printf("\n\nText UI Project normal exit (we hope)");
	}else{
		printf("\n\n%s", message);
	}
	if(lazy_file_or_fd_is_open()){
		lazy_file_close();
	}
	print_all_bugs();
	GLOBAL_basic_signals.quit_signal = true;
	GLOBAL_basic_signals.grali_mono_text_input_error_signal = true;
	pthread_cond_broadcast(&GLOBCOND_quit_condition);
	usleep(100000);
	printf("\n\nFRIKKIN QKWITTEN TIME!!!");
	printf("\n\nFRIKKIN QKWITTEN TIME!!!");
	//printf("\n\nFRIKKIN QKWITTEN TIME!!!");
	//printf("\n\nFRIKKIN QKWITTEN TIME!!!");
	//printf("\n\nFRIKKIN QKWITTEN TIME!!!");
	//printf("\n\nFRIKKIN QKWITTEN TIME!!!");
	usleep(999999);
	//printf("\n\nIt's well past goddamn FRIKKIN QKWITTEN TIME!!!");
	//printf("\n\nIt's well past goddamn FRIKKIN QKWITTEN TIME!!!");
	//printf("\n\nIt's well past goddamn FRIKKIN QKWITTEN TIME!!!");
	//printf("\n\nIt's well past goddamn FRIKKIN QKWITTEN TIME!!!");
	//printf("\n\nIt's well past goddamn FRIKKIN QKWITTEN TIME!!!");
	printf("\n\nIt's well past goddamn FRIKKIN QKWITTEN TIME!!!");
	abort();
}


xcb_key_press_event_t*
kevents_Q_andfree ( xcb_key_press_event_t *ev, int index ){

	static xcb_key_press_event_t	**k,
											**kevents,
											*returnval;
	static int top = 0, bottom = 0;
	if(!ev && index == -1){
		bug_report("\nNULL ev and -1 index");
		returnval = NULL;
	}if(!k){
		k = calloc(KEVENTS_Q + 1, sizeof(void*));
		for(int i = 0; i < KEVENTS_Q + 1; i++){
			k[i] = (xcb_key_press_event_t*) -1;
		}
		kevents = k + 1;
	}
	//printf("\n\n~~~~~~~~~~~~~\ntop: %d\tbottom: %d\tindex: %d", top, bottom, index);
	if((ev && index < 0)||(index > top && bottom == 0)||(index < -1 || index >= KEVENTS_Q)){
		bug_report("index invalid");
		//printf("\nindex invalid--: %d", index);
		returnval  = NULL;
	}else{
		returnval = kevents[index];
	}
	if(1 || ev){
		kevents[top] = ev;
		//int oldtop = top;
		if(!ev)//printf("\nev = NULL so kevents[%d] = NULL", oldtop);
		//printf("\n	kevents[top] = ev;\t top: %d", top);
		top++;
		//printf("\ntop++ ");
		//printf("\ntop: %d\tbottom: %d", top, bottom);
		if(top == KEVENTS_Q){
			bottom = 1;
			top = 0;
			//printf("\nkey events Q top wraps around to bottom");
		}if(top == bottom){
			bottom++;
			//printf("\ntop: %d\tbottom: %d", top, bottom);
			if(bottom == KEVENTS_Q){
				bottom = 0;
			}
		}
		//printf("\n	kevents[oldtop] = ev;  oldtop: %d\ntop: %d\tbottom: %d\tindex: %d", oldtop, top, bottom, index);

	}
	//printf("\nreturn returnval;");
	return returnval;
}

void
keyrelease ( xcb_key_release_event_t *ev){
	;
}// end keyrelease



void*
multi_lthread_scheduler_coordinator ( void *unused ){
	//printf("\n calling gravitators A time since start: %ld", seconds_since(starttime));
	GLOBAL_num_gravitator_A_crews = GETINT(gravitator_crews, 3);
	gravitators_group_A();
	while(!readyFlags.gravA_ready){
		usleep(500);
	}
	if(GETBOOL(pixies_y_n, true) || (GETBOOL(pixies_y_n, true))){
		pixie_algo_vars_t alchoices;
		pixies_loop_t pixiloop = {
										.color = _yellowscale,
										.number_of_particles = GETINT(pixies_qty, 200),
										.dot_level = 3,
										.loop_pause_interval = 0,
										.signals = &GLOBAL_basic_signals,
										.name = name_tag("Pixi set A #"),
										.number_of_bucket_lists = GLOBAL_num_gravitator_A_crews,
										.bucket_lists = GLOBAL_gravitator_group_A_array
		};
		if(GETBOOL(pixies_y_n, true)){
			alchoices.touch = GETFLOAT(pixies_touch, 0.0005);
			alchoices.charge_formula_switch = GETINT(pixies_chg_form_switch, 89);
			alchoices.collision_backup_switch = GETINT(pixies_coll_backup_switch, 2);
			alchoices.powerlaw_switch = GETINT(pixies_powlaw_switch, 2);
			alchoices.powerlaw_pull = GETINT(pixies_powlawpull, 2);
			alchoices.powerlaw_push = GETINT(pixies_powlaw_push, 3);
			alchoices.push_mult = GETFLOAT(pixies_push_mult, 5.0);
			alchoices.pull_mult = GETFLOAT(pixies_pull_mult, 5.0);
			pixiloop.algorithm_switches = alchoices;
			pixiloop.loop_pause_interval = GETINT(pixies_usec_freq, 9090);
			int number_pixie_threads  = GETINT(pixies_num_loops, 10);
			pthread_t *pixies_set_A_threads = malloc(number_pixie_threads * sizeof(pthread_t));
			pixies_loop_t *pixiloopcopies = malloc(number_pixie_threads * sizeof(pixies_loop_t));
			pixiloop.color = _redscale;
			if(number_pixie_threads  > 0){
				for(int i = 0; i < number_pixie_threads ; i++){
					pixiloopcopies[i] = pixiloop;
					pixiloopcopies[i].name.eight_numbers[6] = '0' + i;
					pthread_create(pixies_set_A_threads + i, NULL, pixies_loop_launcher, pixiloopcopies + i);
					pixiloop.color++;
				}
			}
		}
		if(GETBOOL(pixiesB_y_n, true)){
			pixiloop.color = _greenscale;
			pixiloop.number_of_particles = GETINT(pixiesB_qty, 200),
			pixiloop.dot_level = 3;
			pixiloop.loop_pause_interval = GETINT(pixiesB_usec_freq, 9090);
			pixiloop.name = name_tag("Pixi set B #");
			alchoices.touch = GETFLOAT(pixiesB_touch, 0.0005);
			alchoices.charge_formula_switch = GETINT(pixiesB_chg_form_switch, 89);
			alchoices.collision_backup_switch = GETINT(pixiesB_coll_backup_switch, 2);
			alchoices.powerlaw_switch = GETINT(pixiesB_powlaw_switch, 2);
			alchoices.powerlaw_pull = GETINT(pixiesB_powlawpull, 2);
			alchoices.powerlaw_push = GETINT(pixiesB_powlaw_push, 2);
			alchoices.push_mult = GETFLOAT(pixiesB_push_mult, -5.0);
			alchoices.pull_mult = GETFLOAT(pixiesB_pull_mult, -5.0);
			pixiloop.algorithm_switches = alchoices;
			int number_pixie_threads  = GETINT(pixiesB_num_loops, 10);
			pthread_t *pixies_set_B_threads = malloc(number_pixie_threads * sizeof(pthread_t));
			pixies_loop_t *pixiloopcopies = malloc(number_pixie_threads * sizeof(pixies_loop_t));
			if(number_pixie_threads  > 0){
				for(int i = 0; i < number_pixie_threads ; i++){
					pixiloopcopies[i] = pixiloop;
					pixiloopcopies[i].name.eight_numbers[6] = '0' + i;
					pthread_create(pixies_set_B_threads + i, NULL, pixies_loop_launcher, pixiloopcopies + i);
					pixiloop.color++;
				}
			}
		}
	}
	if(GETBOOL(vectors_on, true)){
		vect_lines_loop_t vecdata = {
			.name = name_tag("Vector Field #1"),
			.signals = &GLOBAL_basic_signals,
			.signals_flag = NULL
		};
		static pthread_t vectorpthread;
		pthread_create(&vectorpthread, NULL, vect_lines_loop_launcher, &vecdata);
	}
	return NULL;
}// end mulit

void*
launchevents(void* evhandle){
	grali_events(*(grali_event_handlers_t*)evhandle, 30000, &GLOBAL_basic_signals.quit_signal);
	return NULL;
}

char*
testlookupcolors ( color_naming_t colors[] ){
	int i;
	for(i = 0; colors[i].enumname != -1; i++){
		printf("\nColor name: %s\tenumname value: %d\ti == %d\tindex#: %d", colors[i].name, colors[i].enumname, i, globalcolorarray[colors[i].enumname].index_number);
	}
	return colors[i].name;
}

int
main ( int argc, char **argv){
//	gettimeofday(&starttime, NULL);
	/*************************
	** set*() are for grali_mono* to communicate if
	** bad input and to know if quitting
	** so it will return right away with or without
	** having input anything
	*/
	setQuitSignal_4_mono_text(&GLOBAL_basic_signals.quit_signal);
	setErrorSignal_4_mono_text(&GLOBAL_basic_signals.grali_mono_text_input_error_signal);
	/**************************/
	uint8_t initbits = 0;
	if(argc == 2){
		initbits |= 8;
	}
	cfgfilename = "txtui.cfg";
	setupConfigVars(cfgfilename);
	grali_usa_qwerty_key_init();
	if(!initbits ){
		if(GETBOOL(fullscreen, false)){
			initbits |= 8;
		}
	}
	if(GETBOOL(decor, false)){
		initbits |= 16;
	}
	/* squarxel = square + pixel. *********
	** it is the basic unit. a real pixel**
	** is, in this application, the *******
	** smallest possible square - 1x1 *****
	** one pixel across and one pixel high*
	**************************************/
	squarxel_size = GETINT(squarxel, 2);
	xres = GETINT(xres, 800);
	yres = GETINT(yres, 400);
	xres = xres / squarxel_size + 1 * (xres % squarxel_size > 0);
	yres = yres / squarxel_size + 1 * (yres % squarxel_size > 0);
	GLOBAL_gsf = GETFLOAT(GLOBAL_gsf, 4.0);
	GLOBAL_gsf_reciprocal = 1.0 / GLOBAL_gsf;
	grali_init(initbits, xres, yres, squarxel_size);
	gralicolor_palette_init(GETINT(shade_gradient, 6));
	pthread_t events, drawthread, UIthread;
	pthread_create(&UIthread, NULL, simples_and_menu_launcher_UI, NULL);
	static grali_event_handlers_t evhandle = {
					.key_press_notify 	= keypress
//					, .key_release_notify 	= keyrelease
				};
	pthread_create(&events, NULL, launchevents, &evhandle);
	simple_draw_t *sdraw = calloc(1, sizeof(simple_draw_t));
	sdraw->refresh_tempo =  GETINT(screen_refresh_tempo_usecs, 16000);
	sdraw->count_fps = GETBOOL(count_display_fps, false);
	sdraw->printtextscreen = true;
	sdraw->drawn_object_list_base = GLOBAL_dot_anchor;
	if(GETBOOL(six_tone_bkgrnd, true)){
		byte_t fatpixelsize = grali_fat_pixels (true_width);
		grali_add_gradient(20, 99, 0, 0, 99, 20, 6, _cobaltscale);
		splash = massive_6_tone_background_ob(_cobaltscale, solid_black, true_width / fatpixelsize, true_height / fatpixelsize + 2);
		splash->first_color->name = name_tag("flash_bckgrnd");
		splash->first_color->id =	gralibuf_tag;
		graliob_scale_pixels(splash, pixz, fatpixelsize);
		graliob_draw(splash, &global_background_buffer);
	}else{
		gralibuf_clear(&global_background_buffer);
	}
	fill_GLOBAL_dot_anchor(&global_background_buffer);
	pthread_create(&drawthread, NULL, simple_draw_thread, sdraw);
	grali_background();
	xcb_flush(connection);
	grali_show();
	grali_start_display();
	txInit(GETINT(display_window_text_columns, xRes / 130), _yellowscale, bright_blue, _cobaltscale);
	txSetLeftMargin(5);
	txBackgroundColor(0);
	//gettimeofday(&uilaunchtime, NULL);
	//**** sleep a moment to let first threads get going ???????
	multi_lthread_scheduler_coordinator( NULL );
	//testrands(reps, max);
	pthread_cond_wait(&GLOBCOND_quit_condition, &GLOBMTX_quit_condtion_mutex);
	bug_report("THIS IS NOT A BUG REPORT..THIS IS THE END OF ALL THINGS");
	print_all_bugs();
	exit(0);
}// end main

void*
simples_and_menu_launcher_UI ( void *unused ){
	pthread_detach(pthread_self());
	drawn_object_t do1;
	lthread_t	*kybdtsk,
					*olympiad_crsr,
					*tmloop;
	lthread_cond_t *kybd_subtask_cond,
						*olymp_crsr_cond;
	lthread_cond_create(&kybd_subtask_cond);
	lthread_cond_create(&olymp_crsr_cond);
	do1.drawme = false;
	do1.object_type = 's';
	do1.next_tier = NULL;
	do1.next_place = NULL;
	do1.DOType = sequence_tag;
	do1.seq = spinner_sequence (13, 400, 17);
	dot_list_add(&do1, 99);
	void time_loop (void *unused)
	{
		int	kybd_cnt = 0,
				kyunit = GETINT(UI_kybd_cnt, 50),
				cursor_cnt = 0,
				crsrunit = GETINT(UI_cursor_cnt, 5);
		uint64_t UI_subtask_dispatch_loop_sleep = GETINT(UI_timer_loop_msecs, 10);
		for(;;){
			if(kybd_cnt < kyunit){
				kybd_cnt++;
			}else{
				lthread_cond_signal(kybd_subtask_cond);
				kybd_cnt = 0;
			}
			if(cursor_cnt < crsrunit){
				cursor_cnt++;
			}else{
				lthread_cond_signal(olymp_crsr_cond);
				cursor_cnt = 0;
			}
			if(GLOBAL_basic_signals.quit_signal){
				lthread_exit(tmloop);
				return;
			}
			lthread_sleep(UI_subtask_dispatch_loop_sleep);
		}
	}// end time_loop
	void olympiad_cursor ( void *unused)
	{
		uint64_t crsrwait = GETINT(ui_crsrwait, 30),
					longerwait = crsrwait * 5;
		do1.ob = forward_frame_ob(do1.seq);
		do1.drawme = true;
		while(1){
			int wt;
			wt = lthread_cond_wait(olymp_crsr_cond, longerwait);
			if(wt == -2){
				if(GLOBAL_basic_signals.quit_signal){
					lthread_exit(olympiad_crsr);
				}
			}
			while(do1.drawme){
				mouseXYplus(do1, -do1.ob->x_center, -do1.ob->y_center);
				do1.ob = forward_frame_ob(do1.seq);
				int wt;
				wt = lthread_cond_wait(olymp_crsr_cond, crsrwait);
				if(wt == -2){
					if(GLOBAL_basic_signals.quit_signal){
						lthread_exit(olympiad_crsr);
					}
				}
			}
		}
	}// end olympiad_cursor
	void keyboard_subtask(void *unused)
	{
		uint64_t kybdwait = GETINT(ui_kybdwait, 50);
		for(;;){
			if(-2 == lthread_cond_wait(kybd_subtask_cond, kybdwait)){
				if(GLOBAL_basic_signals.quit_signal){
					lthread_exit(kybdtsk);
				}
				//printf("\nTIMEOUT KEYBOARD !!!!!!!!!!!!!");
			}else{
				if(ctrl('q')||(globalkey.key_code == esc)){
					text_UI_exit("ctrl-'q' or esc caught by keyboard_subtask");
				}
				if(ctrl('\\')){
					text_UI_exit("simples_and_menu_launcher_UI kybd caught '\\' to quit");
					lthread_exit(kybdtsk);
				}else	if(ctrl('/')){
					if(do1.drawme){
						do1.drawme = false;
					}else{
						do1.drawme = true;
					}
				}
				if(ctrl('m')){
					GLOBAL_text_ui_state.menus_visible = !GLOBAL_text_ui_state.menus_visible;
				}else	if(ctrl('t')){
					GLOBAL_text_ui_state.global_text_visible = !GLOBAL_text_ui_state.global_text_visible;
				}
				if(alt('m') ){
					if(GLOBAL_text_ui_state.menus_visible){
						GLOBAL_text_ui_state.menus_above_animation = !GLOBAL_text_ui_state.menus_above_animation;
						dot_menus_high_low_switch();
					}
				}else	if(alt('t')){
					if(GLOBAL_text_ui_state.global_text_above_animation){
						GLOBALtext_hi->drawme = false;
						GLOBALtext_lo->drawme = true;
						GLOBAL_text_ui_state.global_text_above_animation = false;
					}else{
						GLOBALtext_hi->drawme = true;
						GLOBALtext_lo->drawme = false;
						GLOBAL_text_ui_state.global_text_above_animation = true;
					}
				}
			}
		}
	}// end keyboard_subtask
	lthread_t *text_UI_thread;
	void launch_text_UI ( void *unused ){
		/** the point of this thread/function is to
		** explore various ways lthreads could be used
		** in an interface or with other groups of
		** threads/functions, where it may make sense
		** for several threads to schedule cooperatively
		** and using lthread_compute_end() and _begin()
		** might be good if a thread seems like it should
		** split off on it's own posix thread
		** event based  **/
		lthread_compute_begin();
		UI_context_first();
		lthread_compute_end();
		lthread_exit(text_UI_thread);
	}
	lthread_create(&text_UI_thread, launch_text_UI, NULL);
	//printf("\nLTHREAD CREATED lthread text_UI_thread launching -launches itself into pthread");
	//printf("\nLTHREAD CREATing time_loop");
	lthread_create(&tmloop, time_loop, NULL);
	//printf("\nLTHREAD CREATED time_loop");
	lthread_create(&kybdtsk, keyboard_subtask, NULL);
	//printf("\nLTHREAD CREATED keyboard_subtask");
	lthread_create(&olympiad_crsr, olympiad_cursor, NULL);
	//printf("\nLTHREAD CREATED olympiad_crsr subtask");
	lthread_run();
	return NULL;
}

#endif
