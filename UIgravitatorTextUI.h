#ifndef __UI_GRAVITATOR_TEXT_UI_h
#define __UI_GRAVITATOR_TEXT_UI_h

#include "configreader.h"
#include "UI_commonTextUI.h"
#include "UI_DrawnObjectsTextUI.h"
extern _Atomic float	GLOBAL_gsf,
		  			GLOBAL_gsf_reciprocal;

typedef struct basic_signals_st extern_GLOBAL_basic_signals_t;

extern extern_GLOBAL_basic_signals_t GLOBAL_basic_signals;

struct drawn_objects;

typedef struct algorithma{
	_Atomic float	gravitator_adjustment;
	float				touch;
	int				charge_formula_switch;
	int				collision_overlap_switch;
	int				power_law_switch;
	int				power_law_alt_switch;
	int				chrg_frmla_alternate_switch;
	_Atomic float	result_x;
	_Atomic float	result_y;
}b_body_physics_switches_t;
/* NOTE ABOUT .power_law:
** power_law seems rightly to be a property, to go with
** .charge, especially, AND there will likely be multiple
** sets of algorithms, representing various properties
** similarly to, say, quarks, which have 1/3 and 2/3 electrical
** charges, colors, flavors etc.
**   Probably differeing power_laws will operate
** 	also when making quasi-biological traits, power_law
** 	pro'ly won't be part, but another name propery
**		or quality may be found in varying proportions
**		in different rule sets
**	SO: what to do with, where to put, power_law
**		really must not be permitted to freeze the rest of
**		of the data structures and functions
**LIKELY: the expediency of move_collide_t indirection
**		would cover for poor choices, but let's try to
**		keep it consistent and if possible, efficient
**		comprehensible, and lastly, elegant
**/
typedef struct basic_b_body basic_b_body_t;

typedef struct basic_b_body{
	int								array_size;//if part of an array
	name_tag_t						name;
	name_tag_t						category;
	velocity_locale_t				delta_locale;
	phys_measures_t				*measures;
	phys_measures_t				my_measures;
	phys_properties_t				*properties;
	phys_properties_t				my_properties;
	boundary_rules_t				*bounds;
	boundary_rules_t				my_bounds;
	phys_limits_rules_t			*rules;
	phys_limits_rules_t			my_rules;
	b_body_physics_switches_t	*physics_switches;
	b_body_physics_switches_t	my_physics_switches;
	union{
		xcb_point_t					*ptptr;
		xcb_rectangle_t			*rectptr;
	};
}b_body_t;

typedef struct body_bucket {
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
} body_bucket_t;

typedef struct b_body_loop_data{
	int				total_num_of_crews;
	int				crew_size;
	int				crew_number;
	int				rank;
	name_tag_t		name;
	name_tag_t  	category;
	body_bucket_t	***loop_anchors;
	_Atomic float	*gsf_pointer;
	_Atomic int		*countdown_pointer;
} b_body_loop_data_t;


uint64_t
seconds_since ( struct timeval then );


#endif
