#ifndef __COMMON_USE_OBJECTS__
#define __COMMON_USE_OBJECTS__

#include "coroutine.h"

/* perhaps ought to add density, tho' it can be instantly calculated
** but this struct means to adapt several different objects of different types to use
** the same functions. Like object oriented spelled backwards? Inside out?
*/
typedef struct moved_collide_package{
	type_tag_t		identity;
	_Atomic float	*radius;
	_Atomic float	*radius_reciprocal;
	_Atomic float	*G;// as in gravity. pull could be  mass * G f'rxample
	_Atomic float	*mass;// mass * charge_constant == total force
	_Atomic float	*fxpos;
	_Atomic float	*fypos;
	_Atomic float	*deltax;
	_Atomic float	*deltay;
	_Atomic float	*deltax_result;
	_Atomic float	*deltay_result;
	_Atomic float	*elasticity;
	_Atomic float	*power_law;
	_Atomic float	*charge_constant;
	_Atomic float	*charge_adjustment;
}moved_collide_pkg_t;

typedef struct collide_snapshot{
	type_tag_t		identity;
	_Atomic float	radius;
	_Atomic float	radius_reciprocal;
	_Atomic float	G;// as in gravity. pull could be  mass * G f'rxample
	_Atomic float	mass;// mass * charge_constant == total force
	_Atomic float	fxpos;
	_Atomic float	fypos;
	_Atomic float	deltax;
	_Atomic float	deltay;
	_Atomic float	*deltax_result;
	_Atomic float	*deltay_result;
	_Atomic float	elasticity;
	float	power_law;
	float	*charge_constant;
	float	*charge_adjustment;
}collider_snapshot_t;

void
collider_examine ( moved_collide_pkg_t *collider ){
	moved_collide_pkg_t collider_snapshot;
	collider_snapshot_t	values_snapshot;
	collider_snapshot = *collider;
	values_snapshot.radius = *collider_snapshot.radius;
	values_snapshot.radius_reciprocal = *collider_snapshot.radius_reciprocal;
	values_snapshot.G = *collider_snapshot.G;
	values_snapshot.mass = *collider_snapshot.mass;
	values_snapshot.fxpos = *collider_snapshot.fxpos;
	values_snapshot.fypos = *collider_snapshot.fypos;
	values_snapshot.deltax = *collider_snapshot.deltax;
	values_snapshot.deltay = *collider_snapshot.deltay;
	values_snapshot.deltax_result = collider_snapshot.deltax_result;
	values_snapshot.deltay_result = collider_snapshot.deltay_result;
	values_snapshot.elasticity = *collider_snapshot.elasticity;
	values_snapshot.power_law = *collider_snapshot.power_law;
	values_snapshot.charge_constant = (float *) collider_snapshot.charge_constant;
	values_snapshot.charge_adjustment = (float*) collider_snapshot.charge_adjustment;
	printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\ncontents of values pointed to by collider");
	printf("\n~~~~~~~~~~~~~below~~~~~~~~~~~~~~~");
	printf("\nidentity.name: %s",			values_snapshot.identity.name);
//	printf("\nidentity.number: %llu",	values_snapshot.identity.number);
	printf("\nradius: %f.",					values_snapshot.radius );
	printf("\nradius_reciprocal: %f.",	values_snapshot.radius_reciprocal );
	printf("\nG: %f.",		values_snapshot.G );
	printf("\nmass: %f.",	values_snapshot.mass );
	printf("\nfxpos: %f.",	values_snapshot.fxpos );
	printf("\nfypos: %f.",	values_snapshot.fypos );
	printf("\ndeltax: %f.",	values_snapshot.deltax );
	printf("\ndeltay: %f.",	values_snapshot.deltay );
	printf("\ndeltax_result: %f.", ({double x = *values_snapshot.deltax_result;x;}) );
	printf("\ndeltay_result: %f.",	({double x = *values_snapshot.deltay_result;x;}));
	printf("\nelasticity: %f.",		values_snapshot.elasticity );
	printf("\npower_law: %f.",			values_snapshot.power_law );
	printf("\ncharge_constant: %f.", (float)*	values_snapshot.charge_constant );
	printf("\ncharge_adjustment: %f.", (float)	*values_snapshot.charge_adjustment );
	printf("\n~~~~~~~~~~~above~~~~~~~~~~~~~~~");
	printf("\ncontents of values pointed to by collider");
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
/*
	printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\naddresses held in pointer of collider");
	printf("\n~~~~~~~~~~~~~below~~~~~~~~~~~~~~~");
	printf("\nidentity.name: %s",			collider_snapshot.identity.name);
	printf("\nradius: %lu.",					(uint64_t)collider_snapshot.radius );
	printf("\nradius_reciprocal: %lu.",	(uint64_t)collider_snapshot.radius_reciprocal );
	printf("\nG: %lu.",		(uint64_t)collider_snapshot.G );
	printf("\nmass: %lu.",	(uint64_t)collider_snapshot.mass );
	printf("\nfxpos: %lu.",	(uint64_t)collider_snapshot.fxpos );
	printf("\nfypos: %lu.",	(uint64_t)collider_snapshot.fypos );
	printf("\ndeltax: %lu.",	(uint64_t)collider_snapshot.deltax );
	printf("\ndeltay: %lu.", (uint64_t)collider_snapshot.deltay );
	printf("\ndeltax_result: %lu.",	(uint64_t)collider_snapshot.deltax_result );
	printf("\ndeltay_result: %lu.",	(uint64_t)collider_snapshot.deltay_result );
	printf("\nelasticity: %lu.",		(uint64_t)collider_snapshot.elasticity );
	printf("\npower_law: %lu.",			(uint64_t)collider_snapshot.power_law );
	printf("\ncharge_constant: %lu.", 	(uint64_t)collider_snapshot.charge_constant );
	printf("\ncharge_adjustment: %lu.", 	(uint64_t)collider_snapshot.charge_adjustment );
	printf("\n~~~~~~~~~~~above~~~~~~~~~~~~~~~");
	printf("\naddresses held in pointer of collider");
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	*/
}
typedef struct x_y_label xy_label_t;
typedef struct menu menu_t;
typedef struct scoreboard scoreboard_t;
typedef struct drawn_objects drawn_object_t;
typedef struct vector_lines vector_lines_t;
typedef struct bounds_rules bounds_rules_t;
typedef struct drawn_objects drawn_object_t;
typedef struct physical_measures	phys_measures_t;
typedef struct physical_properties	phys_properties_t;
/*

extern const type_tag_t	collider_tg;
extern const type_tag_t	gravitator_tg;
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

/****************************
recasting of lovely coroutines, written and
copyrighted under the GNU Lesser General Public License 3.0
circa 2017, S.Conner
Wormholes are a topological feature of spacetime continuae
which connect disparate regions of spacetime otherwise of
arbitrarily great distance apart. This facilitates
near-instantaneous traversal of great distances, apparently
well above the speed of light to any other frame of reference
****************************
THESE wormholes permit the thread of execution to
travel without moving. Dive into one and emerge in a different
region, with its own frame of reference (stack frame, that is)
in a parallel universe(its own stack)

Once the  wormhole has been opened, it's stabilized and whereever
you encounter it, when if you hop in you emerge whereever the
last place anyone hopped into it: therefore careless hopping may
lead to unpredictable points of emergence!

It's good practice to only jump in and out of these suckers
directly, and not by reference. It ain't fair to carry one end
of the wormhole all over the universe! Tho' it can be fun.
****************************/

wormhole_t*
wormhole_open ( size_t stack_size, void*(*coroutine_function)(wormhole_t *return_rout, void *user_defined_data));

bool
wormhole_collapse ( wormhole_t *stack_and_pointers_to_free);

void*
wormhole_dive ( wormhole_t *tunnels_to_prior_yeild, void *user_defined_data);

#endif
