#ifndef __UI_GRAVITATOR_TEXT_UI_c
#define __UI_GRAVITATOR_TEXT_UI_c

#undef __CHECK_INTERVALS_GRAVITATORS__

#include <lthread.h>
#include "coroutine.h"

#include "UIgravitatorTextUI.h"

extern body_bucket_t **GLOBAL_gravitator_group_A_array;
extern _Atomic int GLOBAL_num_gravitator_A_crews;

extern const type_tag_t	gravitator_tg;

_Atomic int gravitatorAcntdwn;

void
antibasic_inelastic_collision ( moved_collide_pkg_t *moved, moved_collide_pkg_t *mover){
	float	dvx2, a, vx, vy, yd, xd, fy, massratio;
	xd = (*moved->fxpos - *mover->fxpos);
	yd = (*moved->fypos - *mover->fypos);
	vx = (*moved->deltax - *mover->deltax);
	vy = (*moved->deltay - *mover->deltay);
	if ((vx * xd + vy * yd) >= 0) return;
	fy = FLT_MIN * fabsf(yd);
	if (fabsf(xd) < fy) {
		(xd < 0) ? (xd = -fy) : (xd = fy);
	}
	//update velocities
	if ((yd) && (xd)){
		float rnn = rx(100);
		if(rnn >=  63.0){
			rnn = (rnn/100.0);
			if(*mover->mass > *moved->mass && rx(100) > 35){
				if(!isnan(rnn * *moved->mass)){
					*mover->mass += rnn * *moved->mass;
					*moved->mass -= rnn * *moved->mass;
				}
			}else{
				if(!isnan(rnn * *mover->mass)){
					*moved->mass += rnn * *mover->mass;
					*mover->mass -= rnn * *mover->mass;
				}
			}
		}
		if(*moved->mass == *mover->mass){
			massratio = 1.0;
		}else{
			massratio = *moved->mass / *mover->mass;
		}		a = (fabsf(yd) * yd) / (fabsf(xd) * xd);
		dvx2 = -2 * (vx + a * vy) / ((1 + a * a) * (1 + massratio));
		*moved->deltax = *moved->deltax + dvx2;
		*moved->deltay = *moved->deltay + a * dvx2;
		*mover->deltax = *mover->deltax - massratio * dvx2;
		*mover->deltay = *mover->deltay - a * massratio * dvx2;
//*********** inelastic collisions below-without code below, you have elastic collisios
		if	((*mover->elasticity > 0)||(*moved->elasticity > 0)){
//	vx_cm and vy_cm are used for inelastic collisions
			float vx_cm = ((*mover->mass * *mover->deltax) + (*moved->mass * *moved->deltax)) / (*mover->mass + *moved->mass);
			float vy_cm = ((*mover->mass * *mover->deltay) + (*moved->mass * *moved->deltay)) / (*mover->mass + *moved->mass);
			*mover->deltax = (*mover->deltax - vx_cm) * *mover->elasticity + vx_cm;
			*mover->deltay = (*mover->deltay - vy_cm) * *mover->elasticity + vy_cm;
			*moved->deltax = (*moved->deltax - vx_cm) * *moved->elasticity + vx_cm;
			*moved->deltay = (*moved->deltay - vy_cm) * *moved->elasticity + vy_cm;
		}
	}
}

void
basic_elastic_collision ( moved_collide_pkg_t *moved, moved_collide_pkg_t *mover){
	float	dvx2, a, vx, vy, yd, xd, fy, massratio;
	xd = (*moved->fxpos - *mover->fxpos);
	yd = (*moved->fypos - *mover->fypos);
	vx = (*moved->deltax - *mover->deltax);
	vy = (*moved->deltay - *mover->deltay);
	if ((vx * xd + vy * yd) >= 0) return;//not approaching one another
	fy = FLT_MIN * fabsf(yd);
	if (fabsf(xd) < fy) {
		(xd < 0)? (xd = -fy) : (xd = fy);
	}
	//update velocities
	if ((yd) && (xd)){
		if(*moved->mass == *mover->mass){
			massratio = 1.0;
		}else{
			massratio = *moved->mass / *mover->mass;
		}
		a = (fabsf(yd) * yd) / (fabsf(xd) * xd);
		dvx2 = -2 * (vx + a * vy) / ((1 + a * a) * (1 + massratio));
		*moved->deltax_result += dvx2;
		*moved->deltay_result += a * dvx2;
		*mover->deltax_result -= massratio * dvx2;
		*mover->deltay_result -= a * massratio * dvx2;
	}
}

void
basic_inelastic_collision ( moved_collide_pkg_t *moved, moved_collide_pkg_t *mover){
	float	dvx2, a, vx, vy, yd, xd, fy, massratio;
	xd = (*moved->fxpos - *mover->fxpos);
	yd = (*moved->fypos - *mover->fypos);
	vx = (*moved->deltax - *mover->deltax);
	vy = (*moved->deltay - *mover->deltay);
	if ((vx*xd + vy*yd) >= 0) return;//not approaching one another
	fy = FLT_MIN * fabsf(yd);
	if (fabsf(xd) < fy) {
		(xd < 0)? (xd = -fy) : (xd = fy);
	}
	//update velocities
	if ((yd) && (xd)){
		if(*moved->mass == *mover->mass){
			massratio = 1.0;
		}else{
			massratio = *moved->mass / *mover->mass;
		}
		a = (fabsf(yd) * yd) / (fabsf(xd) * xd);
		dvx2 = -2 * (vx + a * vy) / ((1 + a * a) * (1 + massratio));
		*moved->deltax = *moved->deltax + dvx2;
		*moved->deltay = *moved->deltay + a * dvx2;
		*mover->deltax = *mover->deltax - massratio * dvx2;
		*mover->deltay = *mover->deltay - a * massratio * dvx2;
//*********** inelastic collisions below-without code below, you have elastic collisios
		if	((*mover->elasticity > 0)||(*moved->elasticity > 0)){
//	vx_cm and vy_cm are used for inelastic collisions
			float vx_cm = ((*mover->mass * *mover->deltax) + (*moved->mass * *moved->deltax)) / (*mover->mass + *moved->mass);
			float vy_cm = ((*mover->mass * *mover->deltay) + (*moved->mass * *moved->deltay)) / (*mover->mass + *moved->mass);
			*mover->deltax = (*mover->deltax - vx_cm) * *mover->elasticity + vx_cm;
			*mover->deltay = (*mover->deltay - vy_cm) * *mover->elasticity + vy_cm;
			*moved->deltax = (*moved->deltax - vx_cm) * *moved->elasticity + vx_cm;
			*moved->deltay = (*moved->deltay - vy_cm) * *moved->elasticity + vy_cm;
		}
	}
}

uintptr_t
co_collision (  coroutine__s *hole, uintptr_t data ){
	struct {
		moved_collide_pkg_t *movd;
		moved_collide_pkg_t *movr;
	} *colliders = (void*)data;
	float	dvx2, a, vx, vy, yd, xd, fy, massratio;
	#define moved colliders->movd
	#define mover colliders->movr
	do{
		xd = (*moved->fxpos - *mover->fxpos);
		yd = (*moved->fypos - *mover->fypos);
		vx = (*moved->deltax - *mover->deltax);
		vy = (*moved->deltay - *mover->deltay);
		if ((vx*xd + vy*yd) >= 0) goto supercunt;//not approaching one another
		fy = FLT_MIN * fabsf(yd);
		if (fabsf(xd) < fy) {
			(xd < 0)? (xd = -fy) : (xd = fy);
		}
		//update velocities
		if ((yd) && (xd)){
			massratio = *moved->mass / *mover->mass;
			a = (fabsf(yd) * yd) / (fabsf(xd) * xd);
			dvx2 = -2 * (vx + a * vy) / ((1 + a * a) * (1 + massratio));
			*moved->deltax = *moved->deltax + dvx2;
			*moved->deltay = *moved->deltay + a * dvx2;
			*mover->deltax = *mover->deltax - massratio * dvx2;
			*mover->deltay = *mover->deltay - a * massratio * dvx2;
	//*********** inelastic collisions below-without code below, you have elastic collisios
			if	((*mover->elasticity > 0)||(*moved->elasticity > 0)){
	//	vx_cm and vy_cm are used for inelastic collisions
				float vx_cm = ((*mover->mass * *mover->deltax) + (*moved->mass * *moved->deltax)) / (*mover->mass + *moved->mass);
				float vy_cm = ((*mover->mass * *mover->deltay) + (*moved->mass * *moved->deltay)) / (*mover->mass + *moved->mass);
				*mover->deltax = (*mover->deltax - vx_cm) * *mover->elasticity + vx_cm;
				*mover->deltay = (*mover->deltay - vy_cm) * *mover->elasticity + vy_cm;
				*moved->deltax = (*moved->deltax - vx_cm) * *moved->elasticity + vx_cm;
				*moved->deltay = (*moved->deltay - vy_cm) * *moved->elasticity + vy_cm;
			}
		}
supercunt:;
	}while((colliders = (void *)coroutine_yield(hole, 1)));
	#undef moved
	#undef mover
	exit(0);
	return 0;
}

bool
 two_charged_body_atan( moved_collide_pkg_t *moved, moved_collide_pkg_t *mover){
	float sideA, sideB, sideC, r, touch, totaldelta, angle;
	sideB = *moved->fxpos - *mover->fxpos;
	sideC = *moved->fypos - *mover->fypos;

	sideA = hypotf(sideB, sideC);
	touch = (*mover->radius + *moved->radius) - sideA;
	if(touch >= 0.0){
	basic_inelastic_collision (moved, mover);
		return true;
	}
	r = sideA * *mover->radius_reciprocal;
	/* pull is caculated as if G was the pull at the edge
	** of a circle, like it was the surface of a sphere
	** like Earth has 1 gravity pull at the surface. So
	** you can use Earth radii as the unit for r.
	** 2 radii above the surface give 1/4 gravity, etc.
	** it's not necessary to use radii. I just like to
	** you could use miles: 16,000 miles above the Earth
	** or inches, or Planck units. Seconds. You could
	** use seconds at a specific velocity. Light seconds
	** so, really, time or space are equal measures for
	** distance. I just realized that! Cool!*/
	if(r < 1.0) r = 1.0;
	totaldelta = *mover->G / (r * r);
	if((totaldelta)||!isnan(totaldelta)){
		angle = atan2f(sideB, sideC);
		if(angle||!isnan(angle)){
			*moved->deltax_result -= (sinf(angle) * (totaldelta));
			*moved->deltay_result -= (cosf(angle) * (totaldelta));
		}
	}
	return false;
}

bool
two_charged_body_basq_casq_interact ( moved_collide_pkg_t *moved, moved_collide_pkg_t *mover){
	float sideB = *moved->fxpos - *mover->fxpos;
	float sideC = *moved->fypos - *mover->fypos;
	float sideA = sqrt(sideB * sideB + sideC * sideC);
	float touch = (*mover->radius + *moved->radius) - sideA;
	if(touch >= 0.0){
	basic_inelastic_collision (moved, mover);
		return true;
	}
	float asq = sideA * sideA;
	float bsq = sideB * sideB;
	float csq = sideC * sideC;
	float basq = bsq / asq;
	float casq = csq / asq;
	float r = sideA * *moved->radius_reciprocal;
	/* pull is caculated as if G was the pull at the edge
	** of a circle, like it was the surface of a sphere
	** like Earth has 1 gravity pull at the surface. So
	** you can use Earth radii as the unit for r.
	** 2 radii above the surface give 1/4 gravity, etc.
	** it's not necessary to use radii. I just like to
	** you could use miles: 16,000 miles above the Earth
	** or inches, or Planck units. Seconds. You could
	** use seconds at a specific velocity. Light seconds
	** so, really, time or space are equal measures for
	** distance. I just realized that! Cool!*/
	if(r < 1) r = 1;
	if(isnan(r)){
			printf("\n *moved->deltax_result not isfinite");
	}
	float totaldelta = *mover->G / (r * r);
	*moved->deltax_result -= basq * (totaldelta) * (esgn(sideB));
	*moved->deltay_result -= casq * (totaldelta) * (esgn(sideC));
	if(isnan(*moved->deltax_result)){
		printf("\n *moved->deltax_result not normal");
	}

	if(isnan(*moved->deltay_result)){
		printf("\n *moved->deltay_result not isfinite");
	}
	return false;
}

uintptr_t
charged_colliders_atan2_sine_cosine ( wormhole_t *hole, void *data ){
	struct {
		moved_collide_pkg_t *movd;
		moved_collide_pkg_t *movr;
	} *colliders = data;
	wormhole_t *bounce_co;
	coroutine_create(&bounce_co,  0, co_collision);
	float margin = GETFLOAT(gravitators_collide_margin, 0);
	do{
		#define moved colliders->movd
		#define mover colliders->movr
		float sideA, sideB, sideC, r, touch, totaldelta, angle;
		if(moved != mover){
			sideB = *moved->fxpos - *mover->fxpos;
		  	sideC = *moved->fypos - *mover->fypos;
		  	sideA = hypotf(sideB, sideC);
		  	touch = (*mover->radius + *moved->radius) - sideA;
		  	if(touch >= margin){
//				basic_inelastic_collision(moved, mover);
				coroutine_yield(bounce_co, (uintptr_t)colliders);
		  	}else{
				/* pull is caculated as if G was the pull at the edge
				** of a circle, like it was the surface of a sphere
				** like Earth has 1 gravity pull at the surface. So
				** you can use Earth radii as the unit for r.
				** 2 radii above the surface give 1/4 gravity, etc.
				** it's not necessary to use radii. I just like to
				** you could use miles: 16,000 miles above the Earth
				** or inches, or Planck units. Seconds. You could
				** use seconds at a specific velocity. Light seconds
				** so, really, time or space are equal measures for
				** distance. I just realized that! Cool!*/
		  		r = sideA * *mover->radius_reciprocal;
				if(r < 1.0) r = 1.0;
			  	totaldelta = *mover->G / (r * r);
			  	if(isfinite(totaldelta)){
					if(isfinite(angle = atan2f(sideB, sideC)) ) {
			  			*moved->deltax_result -= (sinf(angle) * (totaldelta));
			  			*moved->deltay_result -= (cosf(angle) * (totaldelta));
						if(isnan(*moved->deltax_result)){
							printf("\n *moved->deltax_result not isfinite");
						}
						if(isnan(*moved->deltay_result)){
							printf("\n *moved->deltay_result not isfinite");
						}
					}else{
						printf("\nangle not isfinite");
					}
				}
			}
		}
	}while((colliders = (void *)coroutine_yield(hole, 1)));
	#undef moved
	#undef mover
	return 0;
}

uintptr_t
charged_colliders_atan2_sincosf ( wormhole_t *hole, void *data ){
	struct {
		moved_collide_pkg_t *movd;
		moved_collide_pkg_t *movr;
	} *colliders = data;
	wormhole_t *bounce_co;
	create_coroutine(&bounce_co,  0, co_collision);
	do{
		#define moved colliders->movd
		#define mover colliders->movr
		float sideA, sideB, sideC, r, touch, totaldelta, angle;
		if(moved != mover){
			sideB = *moved->fxpos - *mover->fxpos;
		  	sideC = *moved->fypos - *mover->fypos;
		  	sideA = hypotf(sideB, sideC);
		  	touch = (*mover->radius + *moved->radius) - sideA;
		  	if(touch >= 0.0){
//				basic_inelastic_collision(moved, mover);
				coroutine_yield(bounce_co, (uintptr_t)colliders);
		  	}else{
				/* pull is caculated as if G was the pull at the edge
				** of a circle, like it was the surface of a sphere
				** like Earth has 1 gravity pull at the surface. So
				** you can use Earth radii as the unit for r.
				** 2 radii above the surface give 1/4 gravity, etc.
				** it's not necessary to use radii. I just like to
				** you could use miles: 16,000 miles above the Earth
				** or inches, or Planck units. Seconds. You could
				** use seconds at a specific velocity. Light seconds
				** so, really, time or space are equal measures for
				** distance. I just realized that! Cool!*/
		  		r = sideA * *mover->radius_reciprocal;
				if(r < 1.0) r = 1.0;
			  	totaldelta = *mover->G / (r * r);
			  	if(isfinite(totaldelta)){
					if(isfinite(angle = atan2f(sideB, sideC))){
						float sine, cosine;
						sincosf(angle, &sine, &cosine);
			  			*moved->deltax_result -= sine * totaldelta;
			  			*moved->deltay_result -= cosine * totaldelta;
						if(isnan(*moved->deltax_result)){
							printf("\n *moved->deltax_result not isfinite");
						}
						if(isnan(*moved->deltay_result)){
							printf("\n *moved->deltay_result not isfinite");
						}
					}else{
						printf("\nangle not isfinite");
					}
				}
			}
		}
	}while((colliders = (void *)coroutine_yield(hole, 1)));
	#undef moved
	#undef mover
	return 0;
}

uintptr_t
charged_colliders_asq_div ( wormhole_t *hole, void *data ){
	struct {
		moved_collide_pkg_t *movd;
		moved_collide_pkg_t *movr;
	} *colliders = data;
	wormhole_t *bounce_co;
	coroutine_create(&bounce_co,  0, co_collision);
	do{
		#define moved colliders->movd
		#define mover colliders->movr
		float sideB = *moved->fxpos - *mover->fxpos;
		float sideC = *moved->fypos - *mover->fypos;
		float bsq = sideB * sideB;
		float csq = sideC * sideC;
		float asq = bsq + csq;
		float sideA = sqrt(asq);
		float touch = (*mover->radius + *moved->radius) - sideA;
		if(touch >= 0.0){
			coroutine_yield(bounce_co, (uintptr_t)colliders);
		}else{
			/* pull is caculated as if G was the pull at the edge
			** of a circle, like it was the surface of a sphere
			** like Earth has 1 gravity pull at the surface. So
			** you can use Earth radii as the unit for r.
			** 2 radii above the surface give 1/4 gravity, etc.
			** it's not necessary to use radii. I just like to
			** you could use miles: 16,000 miles above the Earth
			** or inches, or Planck units. Seconds. You could
			** use seconds at a specific velocity. Light seconds
			** so, really, time or space are equal measures for
			** distance. I just realized that! Cool!*/
			float r = sideA * *moved->radius_reciprocal;
			if(r < 1) r = 1;
			float totaldelta = *mover->G / (r * r);
			*moved->deltax_result -=  (bsq / asq) * (totaldelta) * (esgn(sideB));
			*moved->deltay_result -=  (csq / asq) * (totaldelta) * (esgn(sideC));
		}
	}while((colliders = (void *)coroutine_yield(hole, 1)));
	#undef moved
	#undef mover
	return 0;
}

void
FAST_two_charged_body_overlap_corrected_div_interact ( moved_collide_pkg_t *moved, moved_collide_pkg_t *mover){
	float sideA, sideB, sideC, r, bsq, csq, asq;
	_Thread_local static float totaldelta;
	sideB = (*moved->fxpos) - (*mover->fxpos);
	sideC = (*moved->fypos) - (*mover->fypos);
	bsq = sideB * sideB;
	csq = sideC * sideC;
	asq = bsq + csq;
	sideA = sqrtf(asq);
	if(!isnormal(sideA))
			return;
	float basq = bsq / asq;
	float casq = csq / asq;
	float touch = (*mover->radius + *moved->radius) - sideA;
	if(!isnormal(touch))
			return;
	bool collided = false;
	for(int i = 0; (touch >= 0.0 && i < 3); i++){
			collided = true;
			*moved->fxpos += (basq * (touch) * (esgn(sideB)));
			*moved->fypos += (casq * (touch) * (esgn(sideC)));
			sideB = (*moved->fxpos) - (*mover->fxpos);
			sideC = (*moved->fypos) - (*mover->fypos);
			bsq = sideB * sideB;
			csq = sideC * sideC;
			asq = bsq + csq;
			sideA = sqrtf(asq);
			touch = (*mover->radius + *moved->radius) - sideA;
			if(!isnormal(touch)){
				printf("\ntouch not normal");
				}
			if(!isnormal(bsq)){
				printf("\nbsq not normal");
			}
			if(!isnormal(csq)){
				printf("\ncsq not normal");
			}
			basq = bsq / asq;
			casq = csq / asq;
			if(!isnormal(basq)){
				printf("\nbasq not isnormal()");
				bug_report("basq not isnormal()");
			}
			if(!isnormal(casq)){
				printf("\ncasq not isnormal()");
				bug_report("casq not isnormal()");			}
	}
	if(collided){
		basic_inelastic_collision (moved, mover);
		return;
	}
	r = (sideA * *mover->radius_reciprocal);
	totaldelta = ((*mover->G) / (r * r));
	*moved->deltax_result -= totaldelta * basq * (esgn(sideB));
	*moved->deltay_result -= totaldelta * casq * (esgn(sideC));
	if(isnan(*moved->deltax_result)){
		printf("\n *moved->deltax_result not isfinite");
	}
	if(isnan(*moved->deltay_result)){
		printf("\n *moved->deltay_result not isfinite");
	}
}


void
SLOW_two_charged_body_overlap_corrected_atan_interact ( moved_collide_pkg_t *moved, moved_collide_pkg_t *mover){
	float sideA, sideB, sideC, r, touch, angle;
	bool collided = false;
	sideB = (*moved->fxpos) - (*mover->fxpos);
	sideC = (*moved->fypos) - (*mover->fypos);
	sideA = sqrtf(sideB * sideB + sideC * sideC);
	touch = (*mover->radius + *moved->radius) - sideA;
	angle = atan2f(sideB, sideC);
	float sinx = sinf(angle), cosy = cosf(angle);
	for(int i = 0; (touch >= 0.01 && i < 3); i++){
			collided = true;
			*moved->fxpos += sinx * (touch);
			*moved->fypos += cosy * (touch);
			sideB = (*moved->fxpos) - (*mover->fxpos);
			sideC = (*moved->fypos) - (*mover->fypos);
			sideA = sqrtf(sideB * sideB + sideC * sideC);
			touch = (*mover->radius + *moved->radius) - sideA;
	}
	if(collided){
		basic_inelastic_collision (moved, mover);
		return;
	}
	r = (sideA * *mover->radius_reciprocal);
	float totaldelta = ((*mover->G) / (r * r));
	*moved->deltax_result -= sinx * totaldelta;
	*moved->deltay_result -= cosy * totaldelta ;

}
void
charged_body_bounds_enforce ( b_body_t *b_body){
	#define rules b_body->rules
	#define bounds b_body->bounds
	#define delta_loc b_body->delta_locale
	float angle = atan2f(delta_loc.deltax, delta_loc.deltay),
			totaldelta = hypotf(delta_loc.deltax, delta_loc.deltay);
			if(totaldelta > rules->deltamax){
				totaldelta *= rules->decellerando;
				delta_loc.deltax *= rules->decellerando;//= sinf(angle) * totaldelta;
				delta_loc.deltay *= rules->decellerando;//= cosf(angle) * totaldelta;
			}else if(totaldelta > rules->deltamin){
				totaldelta *= rules->decell_to_min;
				delta_loc.deltax *= rules->decell_to_min;//= sinf(angle) * totaldelta;
				delta_loc.deltay *= rules->decell_to_min;//= cosf(angle) * totaldelta;
			}
	//delta_loc.fxpos += delta_loc.deltax;
	//delta_loc.fypos += delta_loc.deltay;
	switch (bounds->wraprules){
		case 0:
			if (delta_loc.fxpos < bounds->xleft){
				delta_loc.fxpos = bounds->xleft;
				delta_loc.deltax= -delta_loc.deltax;
			}else if (delta_loc.fxpos > bounds->xright){
				delta_loc.fxpos = bounds->xright;
				delta_loc.deltax= -delta_loc.deltax;
			}
			if (delta_loc.fypos < bounds->ytop){
				delta_loc.fypos = bounds->ytop;
				delta_loc.deltay= -delta_loc.deltay;
			}else if (delta_loc.fypos > bounds->ybottom) {
				delta_loc.fypos = bounds->ybottom;
				delta_loc.deltay= -delta_loc.deltay;
			}
			break;
		case 1:
			if (delta_loc.fxpos < bounds->xleft){
				totaldelta *= bounds->bumper_elasticity;
				delta_loc.deltax = sinf(angle) * totaldelta;
				delta_loc.deltay = cosf(angle) * totaldelta;
				delta_loc.fxpos = bounds->xleft;
				delta_loc.deltax = -delta_loc.deltax;
			}else if (delta_loc.fxpos > bounds->xright){
				totaldelta *= bounds->bumper_elasticity;
				delta_loc.deltax = sinf(angle) * totaldelta;
				delta_loc.deltay = cosf(angle) * totaldelta;
				delta_loc.fxpos = bounds->xright;
				delta_loc.deltax= -delta_loc.deltax;
			}
			if (delta_loc.fypos < bounds->ytop){
				totaldelta *= bounds->bumper_elasticity;
				delta_loc.deltax = sinf(angle) * totaldelta;
				delta_loc.deltay = cosf(angle) * totaldelta;
				delta_loc.fypos = bounds->ytop;
				delta_loc.deltay= -delta_loc.deltay;
			}else if (delta_loc.fypos > bounds->ybottom) {
				totaldelta *= bounds->bumper_elasticity;
				delta_loc.deltax = sinf(angle) * totaldelta;
				delta_loc.deltay = cosf(angle) * totaldelta;
				delta_loc.fypos = bounds->ybottom;
				delta_loc.deltay= -delta_loc.deltay;
			}
			break;
		case 2:
			if (delta_loc.fxpos <= bounds->xleft){
				delta_loc.fxpos = bounds->xright;
			}else if (delta_loc.fxpos >= bounds->xright){
				delta_loc.fxpos = bounds->xleft;
			}
			if (delta_loc.fypos <= bounds->ytop){
				delta_loc.fypos = bounds->ybottom;
			}else if (delta_loc.fypos >= bounds->ybottom){
				delta_loc.fypos = bounds->ytop;
			}
			break;
		case 3:
			if (delta_loc.fxpos <= bounds->xleft){
				totaldelta *= bounds->bounds_decellerando;
				delta_loc.deltax = sinf(angle) * totaldelta;
				delta_loc.deltay = cosf(angle) * totaldelta;
				delta_loc.fxpos = bounds->xright;
			}else if (delta_loc.fxpos >= bounds->xright){
				totaldelta *= bounds->bounds_decellerando;
				delta_loc.deltax = sinf(angle) * totaldelta;
				delta_loc.deltay = cosf(angle) * totaldelta;
				delta_loc.fxpos = bounds->xleft;
			}
			if (delta_loc.fypos <= bounds->ytop){
				totaldelta *= bounds->bounds_decellerando;
				delta_loc.deltax = sinf(angle) * totaldelta;
				delta_loc.deltay = cosf(angle) * totaldelta;
				delta_loc.fypos = bounds->ybottom;
			}else if (delta_loc.fypos >= bounds->ybottom){
				totaldelta *= bounds->bounds_decellerando;
				delta_loc.deltax = sinf(angle) * totaldelta;
				delta_loc.deltay = cosf(angle) * totaldelta;
				delta_loc.fypos = bounds->ytop;
			}
			break;
		default:
			break;
	}
	#undef body
	#undef delta_loc
	#undef bounds
	#undef rules
}

uintptr_t
co_charged_body_bounds_enforce ( wormhole_t *hole, void *data ){
	#define rules b_body->rules
	#define bounds b_body->bounds
	#define delta_loc b_body->delta_locale
	b_body_t *b_body = data;
	do{
		float angle = atan2f(delta_loc.deltax, delta_loc.deltay),
				totaldelta = hypotf(delta_loc.deltax, delta_loc.deltay);
		if(totaldelta > rules->deltamax){
			totaldelta *= rules->decellerando;
			delta_loc.deltax *= rules->decellerando;//= sinf(angle) * totaldelta;
			delta_loc.deltay *= rules->decellerando;//= cosf(angle) * totaldelta;
		}else if(totaldelta > rules->deltamin){
			totaldelta *= rules->decell_to_min;
			delta_loc.deltax *= rules->decell_to_min;//= sinf(angle) * totaldelta;
			delta_loc.deltay *= rules->decell_to_min;//= cosf(angle) * totaldelta;
		}
		//delta_loc.fxpos += delta_loc.deltax;
		//delta_loc.fypos += delta_loc.deltay;
		switch (bounds->wraprules){
			case 0:

				if (delta_loc.fxpos < bounds->xleft){
					delta_loc.fxpos = bounds->xleft;
					delta_loc.deltax= -delta_loc.deltax;
				}else if (delta_loc.fxpos > bounds->xright){
					delta_loc.fxpos = bounds->xright;
					delta_loc.deltax= -delta_loc.deltax;
				}
				if (delta_loc.fypos < bounds->ytop){
					delta_loc.fypos = bounds->ytop;
					delta_loc.deltay= -delta_loc.deltay;
				}else if (delta_loc.fypos > bounds->ybottom) {
					delta_loc.fypos = bounds->ybottom;
					delta_loc.deltay= -delta_loc.deltay;
				}
				break;
			case 1:
				if (delta_loc.fxpos < bounds->xleft){
					totaldelta *= bounds->bumper_elasticity;
					delta_loc.deltax = sinf(angle) * totaldelta;
					delta_loc.deltay = cosf(angle) * totaldelta;
					delta_loc.fxpos = bounds->xleft;
					delta_loc.deltax = -delta_loc.deltax;
				}else if (delta_loc.fxpos > bounds->xright){
					totaldelta *= bounds->bumper_elasticity;
					delta_loc.deltax = sinf(angle) * totaldelta;
					delta_loc.deltay = cosf(angle) * totaldelta;
					delta_loc.fxpos = bounds->xright;
					delta_loc.deltax= -delta_loc.deltax;
				}
				if (delta_loc.fypos < bounds->ytop){
					totaldelta *= bounds->bumper_elasticity;
					delta_loc.deltax = sinf(angle) * totaldelta;
					delta_loc.deltay = cosf(angle) * totaldelta;
					delta_loc.fypos = bounds->ytop;
					delta_loc.deltay= -delta_loc.deltay;
				}else if (delta_loc.fypos > bounds->ybottom) {
					totaldelta *= bounds->bumper_elasticity;
					delta_loc.deltax = sinf(angle) * totaldelta;
					delta_loc.deltay = cosf(angle) * totaldelta;
					delta_loc.fypos = bounds->ybottom;
					delta_loc.deltay= -delta_loc.deltay;
				}
				break;
			case 2:
				if (delta_loc.fxpos <= bounds->xleft){
					delta_loc.fxpos = bounds->xright;
				}else if (delta_loc.fxpos >= bounds->xright){
					delta_loc.fxpos = bounds->xleft;
				}
				if (delta_loc.fypos <= bounds->ytop){
					delta_loc.fypos = bounds->ybottom;
				}else if (delta_loc.fypos >= bounds->ybottom){
					delta_loc.fypos = bounds->ytop;
				}
				break;
			case 3:
				if (delta_loc.fxpos <= bounds->xleft){
					totaldelta *= bounds->bounds_decellerando;
					delta_loc.deltax = sinf(angle) * totaldelta;
					delta_loc.deltay = cosf(angle) * totaldelta;
					delta_loc.fxpos = bounds->xright;
				}else if (delta_loc.fxpos >= bounds->xright){
					totaldelta *= bounds->bounds_decellerando;
					delta_loc.deltax = sinf(angle) * totaldelta;
					delta_loc.deltay = cosf(angle) * totaldelta;
					delta_loc.fxpos = bounds->xleft;
				}
				if (delta_loc.fypos <= bounds->ytop){
					totaldelta *= bounds->bounds_decellerando;
					delta_loc.deltax = sinf(angle) * totaldelta;
					delta_loc.deltay = cosf(angle) * totaldelta;
					delta_loc.fypos = bounds->ybottom;
				}else if (delta_loc.fypos >= bounds->ybottom){
					totaldelta *= bounds->bounds_decellerando;
					delta_loc.deltax = sinf(angle) * totaldelta;
					delta_loc.deltay = cosf(angle) * totaldelta;
					delta_loc.fypos = bounds->ytop;
				}
				break;
			default:
				break;
		}
	}while((b_body = (void *)coroutine_yield(hole, 1)));
	return 0;
	#undef body
	#undef delta_loc
	#undef bounds
	#undef rules
}

phys_limits_rules_t
b_body_rules_filler ( int crew, name_tag_t category ){
	phys_limits_rules_t retval = {};
	retval.deltamax = GETFLOAT(gravitator_deltamax, 1);
	retval.deltamin = GETFLOAT(gravitator_deltamin, 0);
	retval.decellerando = GETFLOAT(gravitator_decellerando, 0.99);
	retval.decell_to_min = GETFLOAT(gravitator_decell_2_min, 0.999);
	return retval;
}

boundary_rules_t
b_body_bounds_filler ( int crew, name_tag_t category ){
 	boundary_rules_t retval = {};
	retval.bumper_elasticity		= GETFLOAT(gravitator_bumper_elasticity, 0.999999);
	retval.bounds_decellerando		= GETFLOAT(gravitator_bounds_decellerando, 1.0);
	retval.margins						= GETFLOAT(gravitator_margins, -10.0);
	retval.margin_accel				= GETFLOAT(gravitator_accellerando, 0.95);
	retval.wraprules					= GETINT(gravitator_wraprules, inelastic_bounce);
	retval.xleft						= GETFLOAT(gravitator_xleft, 0) - retval.margins;
	retval.xright						= GETFLOAT(gravitator_xright, 1920) + retval.margins;
	retval.ytop							= GETFLOAT(gravitator_ytop, 0)  - retval.margins;
	retval.ybottom						= GETFLOAT(gravitator_ybottom, 960) + retval.margins;
	switch(retval.wraprules){
	/* develop a way to fetch strings and interpret them into values
	** maybe of a set of enum values or maybe name_tag_t's */
		case wraparound:
		case decel_wraparound:
		case inelastic_decel_wrap:
		case inelastic_bounce:
		case elastic_bounce:
		case inelastic_decel_bounce:
			break;
		default:
			bug_report("wraprules value not one of the enum");
			retval.wraprules = inelastic_bounce;
	}
	return retval;
}

phys_measures_t
phys_measures_filler ( int crew, name_tag_t category ){
	phys_measures_t retval = {};
	static int random;
	if(!random){
		random = GETINT(gravitators_percent_rand, 20);
	}
	retval.radius					= GETFLOAT(gravitator_radius, 10.0);
	retval.radius_reciprocal	= 1.0 / retval.radius;
	retval.density					= GETFLOAT(gravitator_density, 1.0);
	switch(GETINT(gravitator_mass_switch, 99)){
		case 0: retval.mass = GETFLOAT(gravitator_mass, 1.0);
		break;
		case 2: retval.mass = retval.density * retval.radius;
		break;
		case 3: retval.mass = retval.density * retval.radius * retval.radius * M_PI;
		default: bug_report("no value provided for mass_switch: must be 1, 2, or 3");
	}
	//float percent = rx(random);
	//percent /= 100.0;
	//retval.mass *= percent;
	//if(retval.mass == 0)retval.mass = FLT_EPSILON;
	return retval;
}

phys_properties_t
phys_properties_filler ( int crew, name_tag_t category ){
	phys_properties_t retval = {};
	retval.power_law			= GETFLOAT(gravitators_power_law, 2.0);
	retval.elasticity			= GETFLOAT(gravitators_elasticity, 0.999999999);
	retval.charge				= GETFLOAT(gravitators_charge, 1);
	retval.charge_constant	= GETFLOAT(gravitators_charge_constant, 1);
	retval.charge_pole		= GETINT(gravitators_charge_pole,  0);
	retval.G						= GETFLOAT(gravitators_gravity, 1.0);
	return retval;
}

b_body_physics_switches_t
b_body_physics_switches_filler ( int crew, name_tag_t category ){
	b_body_physics_switches_t retval = {};
	retval.gravitator_adjustment			= GETFLOAT(gravitators_gravitator_adjustment, -0.01);
	retval.touch								= GETFLOAT(gravitators_touch, 0.0);
	retval.charge_formula_switch			= GETINT(gravitators_charge_formula_switch, 0);
	retval.collision_overlap_switch		= GETINT(gravitators_overlap_switch, 0);
	retval.power_law_switch					= GETINT(gravitators_powerlaw_switch, 0);
	retval.power_law_alt_switch			= GETINT(gravitators_power_law_alt_switch, 0);
	retval.chrg_frmla_alternate_switch	= GETINT(gravitators_charge_formula_alternate_switch, 0);
	return retval;
}

/* meant to initialize the same struct as used in different objects
** so there may be a wide range of values and/or algorithms to
** use to fill values, depending on the kinds of objects - speedy,
** slow, very random, very uniform etc.
** possibly using different config files-use load_config() to
** select acc'd to category and crew #
** possibly using category to seek a label as offset in searching
** for values
*/
velocity_locale_t
velocity_locale_initializer ( int category_switch ){
	bool close_config = setupConfigVars(load_config(0, name_tag("deltasinit")));
//	if(close_config)printf("true");
//	else printf("false");
	velocity_locale_t retval = {};
	retval.gsf = &GLOBAL_gsf;
	retval.gsf_reciprocal = &GLOBAL_gsf_reciprocal;
	int delta_rand;
	float flrx;
	switch(category_switch){
		case 0: 	delta_rand = GETINT(gravitators_randomize, xres);
					float shrink = GETFLOAT(gravitators_random_shrink, 0.001);
					flrx = rx(delta_rand);
					retval.deltax = (flrx - 0.5 * delta_rand) * shrink * (*retval.gsf);
					flrx = rx(delta_rand);
					retval.deltay = (flrx - 0.5 * delta_rand) * shrink * (*retval.gsf);
					retval.fxpos = rx(xres) * (*retval.gsf);
					retval.fypos = rx(yres) * (*retval.gsf);
		break;
		default: retval.deltax = 0.0;
					retval.deltay = 0.0;
					retval.fxpos = xres * (*retval.gsf);
					retval.fxpos = yres * (*retval.gsf);
	}
	if(close_config){
		closeConfigVars();
	}
	return retval;
}

void
b_body_loop ( body_bucket_t *bbucket_array ){
	wormhole_t *collide_cohole, *bounds_cohole;
	/** visually, this division based algorithm has possibly been fastest
	**  and certainly is faster than the separate sin and cos functions */
//	coroutine_create(&collide_cohole,  0, (wormhole_func_t)charged_colliders_asq_div);
//	coroutine_create(&collide_cohole,  0, charged_colliders_atan2_sine_cosine);
	/** the fastest by tiny margin, measure possibly accurate
	** enough to tell difference. Possibly it's sincosf avoids  memory access? */
	create_coroutine(&collide_cohole,  0, charged_colliders_atan2_sincosf);
	create_coroutine(&bounds_cohole, 0, co_charged_body_bounds_enforce);
	struct {
		moved_collide_pkg_t	*movd;
		moved_collide_pkg_t	*movr;
	} two_colliders;
	Usleep (100000);
	timevars
	gravitatorAcntdwn--;// so all crews start at the same approx time
	while(gravitatorAcntdwn){
		Usleep (15000);
	}
	readyFlags.gravA_ready = true;
	for(;;){
		#define b_array bbucket_array[i].body.delta_locale
		timetop
		for(int i = 0; i < bbucket_array[i].crew_size; i++){
			if(GLOBAL_basic_signals.quit_signal){
				return;
			}
//		forward framing is taken care of by draw thread. experimental
			bbucket_array[i].dot->ob = forward_frame_ob(bbucket_array[i].dot->seq);
			bbucket_array[i].dot->x = b_array.fxpos * *b_array.gsf_reciprocal;
			bbucket_array[i].dot->y = b_array.fypos * *b_array.gsf_reciprocal;
			for(int q = 0; q < GLOBAL_num_gravitator_A_crews; q++){
				body_bucket_t *listwalker = GLOBAL_gravitator_group_A_array[q];
				//do{
				for(int r = 0; r < bbucket_array[r].crew_size; r++){
					two_colliders.movd = &listwalker[r].collider;
					two_colliders.movr = &bbucket_array[i].collider;
					if(two_colliders.movd != two_colliders.movr){
				 		coroutine_yield(collide_cohole, (uintptr_t)&two_colliders);
						coroutine_yield(bounds_cohole, (uintptr_t)&bbucket_array[r].body);
						b_array.fxpos += b_array.deltax;
						b_array.fypos += b_array.deltay;
					}
					#undef b_array
				}
//			coroutine_yield(bounds_cohole, (uintptr_t)&bbucket_array[i].body);
			}
		}
		if(bbucket_array->usec_loop_pause){
			Usleep (bbucket_array->usec_loop_pause);
		}else if(bbucket_array->msec_loop_pause){
			lthread_sleep(bbucket_array->msec_loop_pause);
		}
		timebottom
	}
}

/* creates an array of body_bucket_t's with b_body in them, but leaves any values not
** provided, empty. where a pointer is NOT provided the data structure
** will be filled by hard coded labels sought with configreader or their default, also hard coded
** otherwise, structure left empty, but pointer filled with provided
** so, logically, the boolean vars indicating local-therefore individual measurees, etc
** are set to false
** */
body_bucket_t*
basic_b_bucket_llist_maker ( int num_crews,
	phys_measures_t				*prefab_measures,
	phys_properties_t				*prefab_properties,
	b_body_physics_switches_t	*prefab_physics_switches,
	boundary_rules_t				*prefab_bounds,
	phys_limits_rules_t			*prefab_rules,
	velocity_locale_t				*prefab_delta,
	bool								point_to_prefab_delta,
	int								crew_size,
	int								crew,
	name_tag_t						category,
	name_tag_t						name
 ){
	body_bucket_t *bucket_list = calloc(crew_size, sizeof(body_bucket_t));
	#define bbody (bucket_list + i)->body
	#define delta (bucket_list + i)->body.delta_locale
	#define measure (bucket_list + i)->body.measures
	#define props (bucket_list + i)->body.properties
	#define bounds (bucket_list + i)->body.bounds
	#define rules (bucket_list + i)->body.rules
	#define switches (bucket_list + i)->body.physics_switches
	#define pkg (bucket_list + i)->collider
	for(int i = 0; i < crew_size; i++){
		//(bucket_list + i)->next_b_bucket = bucket_list + i + 1;
		//(bucket_list + i)->prior_b_bucket = bucket_list + i -1;
		(bucket_list + i)->crew_size = crew_size;
		(bucket_list + i)->crew = crew;
		(bucket_list + i)->crew_size = crew_size;
		(bucket_list + i)->total_num_of_crews = num_crews;
		(bucket_list + i)->rank = i;
		(bucket_list + i)->crewmember_sn = crew_size * crew + i;
		bucket_list[i].usec_loop_pause = GETINT(gravitators_usec_pause, 0);//20000);
		bucket_list[i].msec_loop_pause = GETINT(gravitators_msec_pause, 0);
	//	bucket_list[i].total_num_of_crews = GETINT(gravitators_number_loops, 4);
		bbody.category = category;
		bbody.name = name;
		//because ->body is inside bucket_list[i] and bucket_list has its own ->array_size
		bbody.array_size = 0;
		if(prefab_measures){
			bbody.measures =			prefab_measures;
			bbody.my_measures =		*prefab_measures;
			pkg.radius =				&prefab_measures->radius;
			pkg.radius_reciprocal =	&prefab_measures->radius_reciprocal;
			pkg.mass =					&prefab_measures->mass;
		}else{
			bbody.measures =			&bbody.my_measures;
			bbody.my_measures =		phys_measures_filler(crew, category);
			pkg.radius =				&measure->radius;
			pkg.radius_reciprocal =	&measure->radius_reciprocal;
			pkg.mass =					&measure->mass;
		}
		if(prefab_properties){
			bbody.properties =		prefab_properties;
			bbody.my_properties =	*prefab_properties;
			pkg.elasticity =			&prefab_properties->elasticity;
			pkg.power_law =			&prefab_properties->power_law;
			pkg.charge_constant =	&prefab_properties->charge_constant;
			pkg.G =						&prefab_properties->G;
		}else{
			bbody.properties =		&bbody.my_properties;
			bbody.my_properties =	phys_properties_filler(crew, category);
			pkg.elasticity =			&props->elasticity;
			pkg.power_law =			&props->power_law;
			pkg.charge_constant =	&props->charge_constant;
			pkg.G =						&props->G;
			pkg.charge_adjustment =	&bbody.my_physics_switches.gravitator_adjustment;
		}
		if(prefab_rules){
			rules = prefab_rules;
			bbody.my_rules = *prefab_rules;
		}else{
			rules = &bbody.my_rules;
			bbody.my_rules = b_body_rules_filler(crew, category);
		}
		if(prefab_physics_switches){
			switches = prefab_physics_switches;
			bbody.my_physics_switches = *prefab_physics_switches;
		}else{
			switches = &bbody.my_physics_switches;
			bbody.my_physics_switches = b_body_physics_switches_filler(crew, category);
		}
		if(prefab_bounds){
			bounds = prefab_bounds;
			bbody.my_bounds = *prefab_bounds;
		}else{
			bounds = &bbody.my_bounds;
			bbody.my_bounds = b_body_bounds_filler(crew, category);
		}
		delta.gsf = &GLOBAL_gsf;
		delta.gsf_reciprocal = &GLOBAL_gsf_reciprocal;
		bounds->xleft = 0;
		bounds->xright = xres * (*delta.gsf);
		bounds->ytop = 0;
		bounds->ybottom = yres * (*delta.gsf);
		delta = velocity_locale_initializer(0);
		pkg.fxpos =				&delta.fxpos;
		pkg.fypos =				&delta.fypos;
		pkg.deltax =			&delta.deltax;
		pkg.deltay = 			&delta.deltay;
		pkg.deltax_result =	&delta.deltax;
		pkg.deltay_result =	&delta.deltay;
	//	pkg.radius_multiple = *pkg.radius * 4;
		float radius = *pkg.radius;
		//radius /= pixz;
		radius *= 2;
		radius *= GLOBAL_gsf_reciprocal;
		sequence_t *flyingsaucer;
		int steps = GETINT(gravitators_steps_per_360, 466);
		int mass_adjust_mult = GETFLOAT(gravitator_mass_differ_mult, 100.3638);
		if(rx(15) > 12){
			flyingsaucer =	blue_yellow_saucer_seq(radius, steps, 1.67);
			*pkg.mass *= mass_adjust_mult;
		}else{
			flyingsaucer =	greredbluora_spinner_sequence(radius, steps, 3.173);
		}
		bucket_list[i].dot = drawn_object_factory( name_tag("gravitator"), 'q', true, flyingsaucer);
		bucket_list[i].dot->frame_update_count = GETINT(gravitators_seq_frame_count, 4);
		bucket_list[i].dot->counter_4_frame_update = 0;
		dot_list_add(bucket_list[i].dot, (bucket_list + i)->crew + 6);
		bucket_list[i].body.ptptr = &bucket_list[i].dot->xy_coord;
		//collider_examine(&pkg);
		//measure->mass = 0.5;
		pkg.G = &props->G;
	#undef bbody
	#undef delta
	#undef measure
	#undef props
	#undef bounds
	#undef rules
	#undef switches
	}
	/* yes yes, of course + 0 is superfluous but it
	** makes it more immediately clear what's going on
	** for me and programmers at my level
	*/
	//(bucket_list + 0)->prior_b_bucket = bucket_list + (crew_size - 1);
	//(bucket_list + crew_size - 1)->next_b_bucket = (bucket_list + 0);
	return bucket_list;
}

//marky_mark_time;

void*
b_body_loop_launch ( void *data ){
	b_body_loop_data_t loop_data;
	loop_data = *((b_body_loop_data_t*)data);
	if(!tag_equals_tag(loop_data.category, gravitator_tg)){
		bug_report("loop_data.category != gravitator_tg");
		return NULL;
	}
	GLOBAL_gravitator_group_A_array[loop_data.crew_number] =
		basic_b_bucket_llist_maker (loop_data.crew_size,
											NULL,/* prefab measure */
											NULL, /* prefab properties*/
											NULL, /* prefab phsics switches*/
											NULL, /* prefab bounds*/
											NULL, /* prefab rules*/
											NULL, /* prefab delta*/
											false,/* point to refab delta*/
											loop_data.crew_size,/* crew size*/
											loop_data.crew_number,/* crew id  */
											gravitator_tg,
											loop_data.name
										);
	b_body_loop(GLOBAL_gravitator_group_A_array[loop_data.crew_number]);
	return NULL;
}

bool
gravitators_group_A( void) {
	GLOBAL_num_gravitator_A_crews = GETINT(gravitator_crews, 4);
	gravitatorAcntdwn = GLOBAL_num_gravitator_A_crews ;
	b_body_loop_data_t loop_data, loop_data_array[GLOBAL_num_gravitator_A_crews];
	loop_data.category = gravitator_tg;
	loop_data.crew_size = GETINT(gravitators_crew_size, 100);
	loop_data.loop_anchors = &GLOBAL_gravitator_group_A_array;
	loop_data.category = gravitator_tg;
	loop_data.total_num_of_crews = GETINT(gravitator_crews, 4);;
	loop_data.gsf_pointer = &GLOBAL_gsf;
	pthread_t *bbodythread = calloc(loop_data.total_num_of_crews, sizeof(pthread_t));
	GLOBAL_gravitator_group_A_array = calloc(loop_data.total_num_of_crews, sizeof(body_bucket_t*));
	#ifdef __CHECK_INTERVALS_GRAVITATORS__
	printf("\nGROUP A about to launch... Time since start: %ld\n", seconds_since(starttime));
	gettimeofday(&gravitatorslaunchtime, NULL);
	#endif
	for(int i = 0; i < loop_data.total_num_of_crews; i++){
		loop_data.crew_number = i;
		loop_data_array[i] = loop_data;
		#ifdef __CHECK_INTERVALS_GRAVITATORS__
		Usleep(10000);
		mark_time;
		#endif
		pthread_create(bbodythread + i, NULL, b_body_loop_launch, loop_data_array + i);
		#ifdef __CHECK_INTERVALS_GRAVITATORS__
		since_mark_time;
		printf("\n\tthread #: %d Launched\tTime to call pthread_create() and return: %ld", loop_data.crew_number, __MARK_TIME_timey);
		#endif
	}


	//pausing a moment for the threads to get their data before the automatic variables
	//are lost when this function returns
	//uint64_t gravA = seconds_since(starttime);
	#ifdef __CHECK_INTERVALS_GRAVITATORS__
	printf("\n\tgrav A threads launched time since starttime %ld", seconds_since(starttime));
	#endif
	//printf("\n\tgravitators_group_A() waiting on gravAcondwait# 1: %ld",seconds_since(starttime) - gravA);
	//pthread_cond_wait(&pixies_can_start_initing, &GLOBAL_THROWAWAY_mutex);
	//printf("\n\tgrav A woke from condwait time since starttime %ld", seconds_since(starttime));
	//pthread_cond_broadcast(&pixies_can_start_initing);
	return true;
}


#endif
