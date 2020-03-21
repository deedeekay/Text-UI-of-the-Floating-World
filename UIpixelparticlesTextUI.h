#ifndef __UIPIXELPARTICLES_TYPES__
#define __UIPIXELPARTICLES_TYPES__
#include "UI_mainTextUI.h"
#include <float.h>
#include "UI_commonTextUI.h"
#include "UIgravitatorTextUI.c"
#include "UI_globalvarsTextUI.h"
#include "UI_mainTextUI.h"
#include <stdio.h>
#include "UI_commonTextUI.h"

typedef struct algorithmae{
	float			touch;//in charge/gravity formulae
	int			charge_formula_switch;
	int			collision_backup_switch;
	int			powerlaw_switch;
	float			powerlaw_pull;
	float			powerlaw_push;
	float			push_mult;
	float			pull_mult;
}pixie_algo_vars_t;

typedef struct pixies_data {
	name_tag_t					name;
	velocity_locale_t			delta_locale;
	phys_measures_t			*phys_measures;
	phys_properties_t			*phys_props;
	boundary_rules_t			*rules;
	phys_limits_rules_t		*phys_limits;
	xcb_point_t					*coordptr;
	int32_t						big_x;
	int32_t						big_y;
	union{// "little guy" is in honor and love for Karen Shirley
			// one heck of a good professor, and good person
	struct pixel_particle	*next_little_guy_pointer;
	int							next_little_guy_index;
	};
}pixies_data_t;

typedef struct pixies_loop{
	pixie_algo_vars_t	algorithm_switches;
	phys_measures_t	phys_measures;
	phys_properties_t	phys_props;
	boundary_rules_t	rules;
	pixies_data_t		*pixies_loop_anchor;
	particle_pixels_t	*graphic_pixels;
	int					number_of_particles;
	drawn_object_t		*particle_graphic;
	int					dot_level;
	uint64_t				loop_pause_interval;
	int					color;
	int(*color_choice_func)(int);
	name_tag_t			name;
	bool					*signals_flag;
	basic_signals_t	*signals;
	body_bucket_t 		**bucket_lists;
	int					number_of_bucket_lists;
}pixies_loop_t;

void*
pixies_loop_launcher ( void *data );

void
pixies_mass_move_collision ( pixies_data_t *moved, moved_collide_pkg_t *mover);

void
print_pixie_snapshot ( collider_snapshot_t values_snapshot, int snapdex );

collider_snapshot_t
pixie_parts_examine ( pixies_data_t pixel_loop);

void
pixies_simple_body_collision ( pixies_data_t *moved, moved_collide_pkg_t *mover);

uintptr_t
pixies_co_collision ( coroutine__s *hole, uintptr_t data );

uintptr_t
pixies_co_collider_gravity_atan2_sincosf ( wormhole_t *hole, void *data );

void
pixies_func_collider_gravity_atan2_sincosf ( pixies_data_t *particle, moved_collide_pkg_t *mover );

bool
pixies_gravity ( pixies_data_t *particle, moved_collide_pkg_t *mover, pixie_algo_vars_t algos);

void
pixies_bounds_enforce ( pixies_data_t *particle);

bool
pixie_bounds_phys_rules_filler ( phys_properties_t *property, phys_measures_t *measure, boundary_rules_t *rule, phys_limits_rules_t *limit, pixie_algo_vars_t *alg);

pixies_data_t*
pixies_list_maker ( pixies_loop_t pixies_loop);

void
pixie_particles_party_loop ( pixies_loop_t pixel_loop );

void*
pixies_loop_launcher ( void *data );

collider_snapshot_t
pixie_parts_examine ( pixies_data_t pixel_loop);

void
print_pixie_snapshot ( collider_snapshot_t values_snapshot, int snapdex );

#endif
