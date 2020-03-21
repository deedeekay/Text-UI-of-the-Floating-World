#include "UIpixelparticlesTextUI.h"


void
print_pixie_snapshot( collider_snapshot_t values_snapshot, int snapdex );

collider_snapshot_t
pixie_parts_examine ( pixies_data_t pixel_loop);

void
pixies_simple_body_collision ( pixies_data_t *moved, moved_collide_pkg_t *mover);

float pmassadj;

void
pixies_mass_move_collision ( pixies_data_t *moved, moved_collide_pkg_t *mover){
	float  dvx2, a, vx, vy, yd, xd, fy, massratio;
	massratio = (50 * *mover->mass) / moved->phys_measures->mass;
	xd = (*mover->fxpos - moved->delta_locale.fxpos);// was INCORRECT! had been!!!!!*mover->fypos!!!!! - moved->fxpos
	yd = (*mover->fypos - moved->delta_locale.fypos);
	vx = (*mover->deltax = - moved->delta_locale.deltax);
	vy = (*mover->deltay - moved->delta_locale.deltay);
	if ((vx*xd + vy*yd) >= 0){
		return;//not approaching one another
	}
	fy = FLT_MIN * fabs(yd); //fy is 0 or greater-almost zero, can't get closer
	if (fabs(xd) < fy) { // if absolute x seperation is 0 or if not || xd is less than fy - closer to 0 than almost zero
		(xd < 0) ? (xd = -fy) : (xd = fy);// if this is the case make it equal to fy, but preserve the sign
	} // big question...why? I don't know much math
	//update velocities
	if ((yd) && (xd)){ //question  if the particles are almost but not quite touching??
		a = (fabs(yd) * yd) / (fabs(xd) * xd);
		// what's this mean? yd^2 / xd^2 but negative is either are negative but
		// positive if both are either negative or positive? why?
		dvx2 = -2 * (vx + a * vy) / ((1 + a * a ) * (1 + massratio));
		*mover->deltax = *mover->deltax + dvx2;
		*mover->deltay = *mover->deltay + a * dvx2;
		moved->delta_locale.deltax = moved->delta_locale.deltax - massratio * dvx2;
		moved->delta_locale.deltay = moved->delta_locale.deltay  -a * massratio * dvx2;
		if(moved->phys_props->elasticity == 0 || *mover->elasticity == 0){
			return;
		}
/*********** inela22000stic collisions - particles do not preserve the energy of impact;
** they slow with each collision *** OR speed up. negentropic? superentropic?
** adding more disorder than the original energy could supply
******/
		#define m1 moved->phys_measures->mass
		#define m2 (*mover->mass * 50)
		if  ((moved->phys_props->elasticity > 0) || (*mover->elasticity > 0)){
/** I have so deduced, that vx_cm and vy_cm are used for inelastic collisions
** or maybe I haven't I'm pretty sure tho'. I wonder if this is at all like the
** formulae for elastic and inelastic collisions*/
			float vx_cm = ((m1 * moved->delta_locale.deltax) + (m2 * *mover->deltax)) / (m1 + m2);
			float vy_cm = ((m1 * moved->delta_locale.deltay) + (m2 * *mover->deltay)) / (m1 + m2);
			if(rx(100)>=50){
				if(*mover->mass > 0.0115){
					moved->phys_measures->mass += FLT_EPSILON;
					*mover->mass -= FLT_EPSILON;
				}else if(moved->phys_measures->mass >= FLT_EPSILON){
					*mover->mass += FLT_EPSILON;
					moved->phys_measures->mass -= FLT_EPSILON;
					if(moved->phys_measures->mass <= 0) moved->phys_measures->mass = FLT_EPSILON;
				}
			}
			if(*mover->mass < 0.0000075 && moved->phys_measures->mass >= FLT_EPSILON){
				moved->phys_measures->mass -= FLT_EPSILON;
				*mover->mass += FLT_EPSILON;
				if(moved->phys_measures->mass <= 0) moved->phys_measures->mass = FLT_EPSILON;
			}
			moved->delta_locale.deltax = (moved->delta_locale.deltax - vx_cm) * moved->phys_props->elasticity + vx_cm;
			moved->delta_locale.deltay = (moved->delta_locale.deltay - vy_cm) * moved->phys_props->elasticity + vy_cm;
			*mover->deltax = (*mover->deltax - vx_cm) * *mover->elasticity + vx_cm;
			*mover->deltay = (*mover->deltay - vy_cm) * *mover->elasticity + vy_cm;
		}
	}
}

void
pixies_simple_body_collision ( pixies_data_t *moved, moved_collide_pkg_t *mover){
	float  dvx2, a, vx, vy, yd, xd, fy, massratio;
	if(moved->phys_measures->mass != 0){
		massratio = (50 * *mover->mass) / moved->phys_measures->mass;
	}else{
		massratio = (50 * *mover->mass) / FLT_MIN;
	}
	xd = (*mover->fxpos - moved->delta_locale.fxpos);
	yd = (*mover->fypos - moved->delta_locale.fypos);
	vx = (*mover->deltax - moved->delta_locale.deltax);
	vy = (*mover->deltay - moved->delta_locale.deltay);
	if ((vx * xd + vy * yd) >= 0){
		return;//not approaching one another
	}
	fy = FLT_MIN * fabs(yd); //fy is 0 or greater-almost zero, can't get closer
	if (fabs(xd) < fy) { // if absolute x seperation is 0 or if not || xd is less than fy - closer to 0 than almost zero
		(xd < 0) ? (xd = -fy) : (xd = fy);// if this is the case make it equal to fy, but preserve the sign
	} // big question...why? What does this do?
	//update velocities
	if ((yd) && (xd)){ //question  if the particles are almost but not quite touching??
		a = (fabs(yd) * yd) / (fabs(xd) * xd);
		// what's this mean? yd^2 / xd^2 but negative is either are negative but
		// positive if both are either negative or positive? why?
		dvx2 = -2 * (vx + a * vy) / ((1 + a * a ) * (1 + massratio));
		moved->delta_locale.deltax = moved->delta_locale.deltax + dvx2;
		moved->delta_locale.deltay = moved->delta_locale.deltay + a * dvx2;
		if(moved->phys_props->elasticity == 0){
			return;
		}
/*********** inela22000stic collisions - particles do not preserve the energy of impact;
** they slow with each collision *** OR speed up. negentropic? superentropic?
** adding more disorder than the original energy could supply
******/

/** I have so deduced, that vx_cm and vy_cm are used for inelastic collisions
** or maybe I haven't I'm pretty sure tho'. I wonder if this is at all like the
** formulae for elastic and inelastic collisions*/
		float vx_cm = ((m1 * moved->delta_locale.deltax) + (m2 * *mover->deltax)) / (m1 + m2);
		float vy_cm = ((m1 * moved->delta_locale.deltay) + (m2 * *mover->deltay)) / (m1 + m2);
		moved->delta_locale.deltax = (moved->delta_locale.deltax - vx_cm) * moved->phys_props->elasticity + vx_cm;
		moved->delta_locale.deltay = (moved->delta_locale.deltay - vy_cm) * moved->phys_props->elasticity + vy_cm;
		#undef m1
		#undef m2

	}
}

uintptr_t
pixies_co_collision (  coroutine__s *hole, uintptr_t data ){
	struct {
		pixies_data_t			*movd;
		moved_collide_pkg_t	*movr;
	} *colliders = (void*)data;
	float	dvx2, a, vx, vy, yd, xd, fy, massratio;
	#define moved colliders->movd
	#define mover colliders->movr
	do{
		xd = (moved->delta_locale.fxpos - *mover->fxpos);
		yd = (moved->delta_locale.fypos - *mover->fypos);
		vx = (moved->delta_locale.deltax - *mover->deltax);
		vy = (moved->delta_locale.deltay - *mover->deltay);
		if ((vx*xd + vy*yd) >= 0) goto superfart;//not approaching one another
		fy = FLT_MIN * fabsf(yd);
		if (fabsf(xd) < fy) {
			(xd < 0)? (xd = -fy) : (xd = fy);
		}
		//update velocities
		if ((yd) && (xd)){
			massratio = moved->phys_measures->mass / *mover->mass;
			a = (fabsf(yd) * yd) / (fabsf(xd) * xd);
			dvx2 = -2 * (vx + a * vy) / ((1 + a * a) * (1 + massratio));
			moved->delta_locale.deltax = moved->delta_locale.deltax + dvx2;
			moved->delta_locale.deltay = moved->delta_locale.deltay + a * dvx2;
	//*********** inelastic collisions below-without code below, you have elastic collisios
			if	((*mover->elasticity > 0)||(moved->phys_props->elasticity > 0)){
	//	vx_cm and vy_cm are used for inelastic collisions
				float vx_cm = ((*mover->mass * *mover->deltax) + (moved->phys_measures->mass * moved->delta_locale.deltax)) / (*mover->mass + moved->phys_measures->mass);
				float vy_cm = ((*mover->mass * *mover->deltay) + (moved->phys_measures->mass * moved->delta_locale.deltay)) / (*mover->mass + moved->phys_measures->mass);
				moved->delta_locale.deltax = (moved->delta_locale.deltax - vx_cm) * ((*mover->elasticity + moved->phys_props->elasticity) / 2) + vx_cm;
				moved->delta_locale.deltay = (moved->delta_locale.deltay - vy_cm) * ((*mover->elasticity + moved->phys_props->elasticity) / 2) + vy_cm;
			}
		}
superfart:;
	}while((colliders = (void *)coroutine_yield(hole, 1)));
	#undef moved
	#undef mover
	exit(0);
	return 0;
}

uintptr_t
pixies_co_collider_gravity_atan2_sincosf ( wormhole_t *hole, void *data ){
	struct {
		pixies_data_t			*movd;
		moved_collide_pkg_t	*movr;
	} *colliders = data;
	wormhole_t *bounce_co;
	coroutine_create(&bounce_co,  0, pixies_co_collision);
	do{
		#define moved colliders->movd
		#define mover colliders->movr
		float sideA, sideB, sideC, r, touch, totaldelta, angle;
		sideB = moved->delta_locale.fxpos - *mover->fxpos;
		sideC = moved->delta_locale.fypos - *mover->fypos;
		sideA = hypotf(sideB, sideC);
		touch = (*mover->radius + moved->phys_measures->radius) - sideA;
		if(touch >= 0.0){
//				pixies_simple_body_collision(moved, mover);
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
					moved->delta_locale.deltax -= sine * totaldelta;
					moved->delta_locale.deltay -= cosine * totaldelta;
					if(isnan(moved->delta_locale.deltax)){
						printf("\n *moved->deltax not isfinite");
					}
					if(isnan(moved->delta_locale.deltay)){
						printf("\n *moved->deltay not isfinite");
					}
				}else{
					printf("\nangle not isfinite");
				}
			}
		}
	}while((colliders = (void *)coroutine_yield(hole, 1)));
	#undef moved
	#undef mover
	return 0;
}
void
pixies_func_collider_gravity_atan2_sincosf ( pixies_data_t *particle, moved_collide_pkg_t *mover ){
	#define moved_v particle->delta_locale
	float sideA, sideB, sideC, r, touch, totaldelta, angle;
	sideB = moved_v.fxpos - *mover->fxpos;
	sideC = moved_v.fypos - *mover->fypos;
	sideA = hypotf(sideB, sideC);
	touch = (*mover->radius + particle->phys_measures->radius) - sideA;
	pixie_parts_examine(*particle);
	if(touch >= 0.0){
		pixies_simple_body_collision(particle, mover);
	}else{
		r = sideA * *mover->radius_reciprocal;
		if(r < 1.0) r = 1.0;
		totaldelta = *mover->G / (r * r);
		angle = atan2f(sideB, sideC);
		float sine, cosine;
		sincosf(angle, &sine, &cosine);
		moved_v.deltax -= sine * totaldelta;
		moved_v.deltay -= cosine * totaldelta;
	}
	#undef moved_v
}

bool
pixies_gravity ( pixies_data_t *particle, moved_collide_pkg_t *mover, pixie_algo_vars_t algos){
	#define moved_v particle->delta_locale
	float sideA, sideB, sideC, r, bsq, csq, asq, basq, casq, touch, angle;
	bool didcollide = false;
	sideB = (moved_v.fxpos) - (*mover->fxpos);
	sideC = (moved_v.fypos) - (*mover->fypos);
	sideA = hypot(sideB, sideC);
	if((sideA == 0.0)){
		/*almost 100% impossible, except for some bodies, it's
		** actually comparing itself to itself-thus zero seperation
		** we don't want self interaction in this pseudo Newtonian
		** digital universe...*/
		return true;
	}
	float radii = *mover->radius + particle->phys_measures->radius;
	touch = radii - sideA;
	if(touch > algos.touch){
		didcollide = true;
		switch(algos.collision_backup_switch){
			case 1:	angle = atan2(sideB, sideC);
						moved_v.fxpos += (sin(angle)*(touch));
						moved_v.fypos += (cos(angle)*(touch));
						sideB = (moved_v.fxpos) - (*mover->fxpos);
						sideC = (moved_v.fypos) - (*mover->fypos);
						sideA = hypot(sideB, sideC);
 						touch = radii - sideA;
						break;
			case 2:	asq = sideA * sideA;
						bsq = sideB * sideB;
						csq = sideC * sideC;
						moved_v.fxpos += (bsq / asq) * (touch) * esgn(sideB);
						moved_v.fypos += (csq / asq) * (touch) * esgn(sideC);
						sideB = (moved_v.fxpos) - (*mover->fxpos);
						sideC = (moved_v.fypos) - (*mover->fypos);
						sideA = hypot(sideB, sideC);
						touch = radii - sideA;
						break;
			default: asq = sideA * sideA;
						bsq = sideB * sideB;
						csq = sideC * sideC;
						basq = bsq / asq;
						casq = csq / asq;
						moved_v.fxpos += (basq * (touch) * (esgn(sideB)));
						moved_v.fypos += (casq * (touch) * (esgn(sideC)));
						sideB = (moved_v.fxpos) - (*mover->fxpos);
						sideC = (moved_v.fypos) - (*mover->fypos);
						sideA = hypot(sideB, sideC);
						touch = radii - sideA;
			break;
			bug_report("invalid ->phys_props->charge_formula");
						print_all_bugs();
						exit(0);
		}
		if(fabs(touch) >= 0.0){
			pixies_simple_body_collision (particle, mover);
		}
	}
	r = sideA * *mover->radius_reciprocal;
	float totaldelta;
	switch(algos.powerlaw_switch){
		case 2:	totaldelta = *mover->G / (r * r);
					break;
		case 3:	totaldelta = *mover->G / (r * r * r);
					break;
		case 4:	totaldelta = *mover->G / pow(r, algos.powerlaw_pull);
					break;
		case 5:	totaldelta = *mover->G / r;
					break;
		case 6:	totaldelta = *mover->G;
					break;
		default: totaldelta = *mover->G / (r * r);
					break;
					bug_report("must provide a powerlaw_switch");
					print_all_bugs();
					exit(0);
	}
	totaldelta *= 10;
	float dx, dy;
	/* delta delta x and delta delta y, and angle for atan2(),  */
	switch(algos.charge_formula_switch){
		case 1:	moved_v.deltax -= algos.pull_mult * totaldelta * (sideB / (fabs(sideB)+fabs(sideC)));
					moved_v.deltay -= algos.pull_mult * totaldelta * (sideC / (fabs(sideB)+fabs(sideC)));
					break;
		case 2:	angle = atan2(sideB, sideC);
					moved_v.deltax -= algos.pull_mult * (sin(angle)*(totaldelta));
					moved_v.deltay -= algos.pull_mult * (cos(angle)*(totaldelta));
					break;
		case 9:	angle = atan2f(sideB, sideC);
					float sine, cosine;
					sincosf(angle, &sine, &cosine);
					moved_v.deltax -= algos.pull_mult * (sine * totaldelta);
					moved_v.deltay -= algos.pull_mult * (cosine * totaldelta);
//					totaldelta = (*mover->G / pow(r, algos.powerlaw_push))  * -algos.push_mult;
					break;
		case 3:	if((sideA != 0.0)){
						asq = sideA * sideA;
						bsq = sideB * sideB;
						csq = sideC * sideC;
						basq = bsq / asq;
						casq = csq / asq;
						moved_v.deltax -= algos.pull_mult * basq * totaldelta * (sideB < 0.0 ? -1.0 : 1.0);
						moved_v.deltay -= algos.pull_mult * casq * totaldelta * (sideC < 0.0 ? -1.0 : 1.0);
					}
					break;
		case 4:	dx = totaldelta * (sideB/(fabs(sideB)+fabs(sideC)));
					dy = totaldelta * (sideC/(fabs(sideB)+fabs(sideC)));
					angle = atan2(sideB, sideC);
					dx = (dx + sin(angle) * totaldelta) * 0.5;
					dy = (dy + cos(angle) * totaldelta) * 0.5;
					moved_v.deltax -= algos.pull_mult * dx;
					moved_v.deltay -= algos.pull_mult * dy;
					break;
		case 5:	dx = totaldelta * (sideB / (fabs(sideB) + fabs(sideC)));
					dy = totaldelta * (sideC / (fabs(sideB) + fabs(sideC)));
					angle = atan2(sideB, sideC);
					dx = dx + sin(angle) * totaldelta +	(sideB / (sideB * sideC))
							* totaldelta;
					dy = dy +  cos(angle) * totaldelta + (sideC / (sideB * sideC))
							* totaldelta;
					moved_v.deltax -= algos.pull_mult * dx * 0.5;
					moved_v.deltay -= algos.pull_mult * dy * 0.5;
					break;
		case 6:	asq = hypot(sideB, sideC);
					asq *= asq;
					dx = totaldelta * (sideB/asq);
					dy = totaldelta * (sideC/asq);
					moved_v.deltax -= algos.pull_mult * dx;
					moved_v.deltay -= algos.pull_mult * dy;
					break;
		case 7:	moved_v.deltax -= algos.pull_mult * totaldelta * (pow(sideB,
						particle->phys_props->power_law) /
						pow(sideA, particle->phys_props->power_law)) * (sideB < 0.0 ? -1.0 : 1.0
					);
					moved_v.deltay -= totaldelta * (pow(sideC,
						particle->phys_props->power_law) /
						pow(sideA, particle->phys_props->power_law)) *
						(sideC < 0.0 ? -1.0 : 1.0
					);
					break;
		default: angle = atan2(sideB, sideC);
					moved_v.deltax -= algos.pull_mult * algos.pull_mult * (sin(angle)*(totaldelta));
					moved_v.deltay -= algos.pull_mult * algos.pull_mult * (cos(angle)*(totaldelta));
					break;
		bug_report("must provide a powerlaw_switch");
					print_all_bugs();
					exit(0);
	}
	return didcollide;
}

void
pixies_bounds_enforce ( pixies_data_t *particle){
#define deltbod particle->delta_locale
	float totaldelta = hypot(deltbod.deltax, deltbod.deltay);
	if(totaldelta > particle->phys_limits->deltamax){
		float angle = atan2(deltbod.deltax, deltbod.deltay);
		totaldelta = totaldelta * particle->phys_limits->decellerando;
		deltbod.deltax = sin(angle) * totaldelta;
		deltbod.deltay = cos(angle) * totaldelta;
	}else if(totaldelta > particle->phys_limits->deltamin){
		float angle = atan2(deltbod.deltax, deltbod.deltay);
		totaldelta = totaldelta * particle->phys_limits->decellerando;
		deltbod.deltax = sin(angle) * totaldelta;
		deltbod.deltay = cos(angle) * totaldelta;
	}
	deltbod.fxpos +=  deltbod.deltax;
	deltbod.fypos +=  deltbod.deltay;
	particle->big_x = particle->coordptr->x;
	particle->big_y = particle->coordptr->y;
	if (deltbod.fxpos  < particle->rules->xleft){
		deltbod.deltax  = 0;
		deltbod.deltay  = 0;
		*particle->coordptr = exwye;
		deltbod.fxpos = particle->big_x * *deltbod.gsf;
		deltbod.fypos = particle->big_y * *deltbod.gsf;
		return;
	}else if (deltbod.fxpos  > particle->rules->xright){
		deltbod.deltax  = 0;
		deltbod.deltay  = 0;
		*particle->coordptr = exwye;
		deltbod.fxpos  = particle->big_x * *deltbod.gsf;
		deltbod.fypos	= particle->big_y * *deltbod.gsf;
		return;
	}
	if (deltbod.fypos < particle->rules->ytop){
		deltbod.deltax	= 0;
		deltbod.deltay	= 0;
		deltbod.fxpos  = particle->big_x * *deltbod.gsf;
		deltbod.fypos	= particle->big_y * *deltbod.gsf;
		return;
	}else if (deltbod.fypos > particle->rules->ybottom){
		deltbod.deltax  = 0;
		deltbod.deltay  = 0;
		*particle->coordptr = exwye;
		deltbod.fxpos  = particle->big_x * *deltbod.gsf;
		deltbod.fypos	= particle->big_y * *deltbod.gsf;
		return;
	}
	particle->big_x = ((deltbod.fxpos * *deltbod.gsf_reciprocal));
	particle->big_y = ((deltbod.fypos * *deltbod.gsf_reciprocal));
	particle->big_x = pixz * particle->big_x;
	particle->big_y = pixz * particle->big_y;
	particle->coordptr->x = particle->big_x;
	particle->coordptr->y = particle->big_y;

#undef deltbod
}

bool
pixie_bounds_phys_rules_filler (phys_properties_t *property, phys_measures_t *measure, boundary_rules_t *rule, phys_limits_rules_t *limit, pixie_algo_vars_t *alg){
	if(!measure || !rule || !property){
		bug_report("NULL parameter(s) passed for *phys_measures, *rules");
		return false;
	}
	_Thread_local static phys_properties_t properties;
	_Thread_local static phys_measures_t measures;
	_Thread_local static phys_limits_rules_t limits;
	_Thread_local static boundary_rules_t rules;
	_Thread_local static pixie_algo_vars_t algos;
	_Thread_local static bool initialized;
	if(!initialized){
		algos.touch =							GETFLOAT(pixies_touch, 0.0);
		algos.charge_formula_switch =		GETFLOAT(pixies_chg_form_switch, 9);
		algos.collision_backup_switch =	GETFLOAT(pixies_coll_backup_switch, 2);
		algos.powerlaw_switch =				GETFLOAT(pixies_powlaw_switch, 2);
		algos.powerlaw_pull =				GETFLOAT(pixies_powlawpull, 2);
		algos.powerlaw_push =				GETFLOAT(pixies_powlaw_push, 3);
		algos.push_mult =						GETFLOAT(pixies_push_mult, -10);
		algos.pull_mult =						GETFLOAT(pixies_pull_mult, 10);
		measures.radius  =		GETFLOAT(pixies_radius, 12);
		measures.mass = 			GETFLOAT(pixies_mass, 6);
		//density isn't used by pixies-it's just here for form
		measures.density = 		measures.mass / measures.radius;
		properties.charge = 		GETFLOAT(pixies_charge_strength, 0);
		properties.elasticity =	GETFLOAT(pixies_elasticity, 0);
		properties.power_law =	GETFLOAT(pixies_pow_law, 2.0);
		limits.deltamax =			GETFLOAT(pixies_deltamax, 2);
		limits.deltamin =			GETFLOAT(pixies_deltamin, 0.999);
		limits.decellerando =	GETFLOAT(pixies_decellerando, 0.99);
		limits.decell_to_min =	GETFLOAT(pixies_decell_to_min, 0.99975);
		rules.gsf =					&GLOBAL_gsf;
		rules.gsf_reciprocal =	&GLOBAL_gsf_reciprocal;
		rules.xright =				(float)xres * global_gsf;
		rules.xleft = 				0.0;
		rules.ytop =				0.0;
		rules.margins =			GETFLOAT(pixies_margins, 1.0);// 1.0 x diameter of particle
		rules.margin_accel =		GETFLOAT(pixies_margin_accel, 0.9);
		rules.ybottom =			(float)yres * global_gsf;
		rules.wraprules =			GETINT(pixies_wraprules, 3);
		rules.bumper_elasticity = GETFLOAT(pixies_bumper_elasticity, 0);
	}
	*property = properties;
	*measure = measures;
	*rule = rules;
	*limit = limits;
	*alg = algos;
	return true;
}

pixies_data_t*
pixies_list_maker ( pixies_loop_t pixies_loop){
	#define pixels pixies_loop.graphic_pixels
	if(!pixie_bounds_phys_rules_filler(&GLOBAL_pixie_phys_properties, &GLOBAL_pixie_phys_measures, &GLOBAL_pixie_rules, &GLOBAL_pixie_phys_limits, &GLOBAL_pixie_algo_switches)){
		bug_report("pixie_bounds_phys_rules_filler() reports failure");
		return NULL;
	}
	static int initial_delta;
	if(!initial_delta)
		initial_delta = GETINT(pixel_parts_initial_delta, 10);
	pixies_data_t	*little_guys = calloc(pixies_loop.number_of_particles, sizeof(pixies_data_t));
	int index = 0;
	int pix_squarx = GETINT(pixies_squarxel_size, pixz);
	static int count;
	pixies_loop.algorithm_switches = GLOBAL_pixie_algo_switches;
	for(int i = 0; i < pixies_loop.number_of_particles; i++){
		pixels->squarxels[index] = exwye;
		little_guys[i].coordptr = pixels->squarxels + index;
		little_guys[i].delta_locale.fxpos =	little_guys[i].coordptr->x * global_gsf;
		little_guys[i].delta_locale.fypos =	little_guys[i].coordptr->y * global_gsf;
		little_guys[i].delta_locale.gsf = 	&GLOBAL_gsf;
		little_guys[i].delta_locale.gsf_reciprocal = &GLOBAL_gsf_reciprocal;
		little_guys[i].phys_props =			&GLOBAL_pixie_phys_properties;
		little_guys[i].phys_measures =		&GLOBAL_pixie_phys_measures;
		little_guys[i].phys_limits	=			&GLOBAL_pixie_phys_limits;
		little_guys[i].rules = 					&GLOBAL_pixie_rules;
		little_guys[i].rules = 					&GLOBAL_pixie_rules;
		little_guys[i].delta_locale.deltax = (rx(initial_delta)) - (initial_delta);
		little_guys[i].delta_locale.deltay = (rx(initial_delta)) - (initial_delta);
		little_guys[i].name.num = count++;
		little_guys[i].next_little_guy_index = i + 1;
		if(pix_squarx == 1){
			//index into the list o' xcb_point_t squarxels
			index++;//inc by 1, point to struct {short x, short y};
		}else{
			//index into the xcb_rectangle_t squarxels
			pixels->squarxels[index + 1].x = pix_squarx;
			pixels->squarxels[index + 1].y = pix_squarx;
			// index by 2 because we use a pointer to xcb_point_t
			// and xcb_rectangle_t is twice size of xcb_point_t
			// and the first two values are exactly like a point
			index += 2;//point to 'top' of struct {short x, short y, width, height
		}
	}
	/** a union allows ->next_little_guy_index and ->next_little_guy to be one element so that
	** a linked list can be tacked on to the end, and at the end of a for(;;)
	** the code can carry on either with a for(;;) or walking a linked list
	** and it makes skipping a little guy very easy within the array by changed ->next_little_guy_index
	** to point ahead of the one being left out. i = little_guys[i].next_little_guy_index **/
	//	mxLock(lazy_mtx);
	little_guys[pixies_loop.number_of_particles - 1].next_little_guy_index = 0;// little_guys;
	/*here we make a loop linking the array to itself for easy insertion of more arrays*/
	//	mxUnLock(lazy_mtx);
	return little_guys;
}

void
pixie_particles_party_loop ( pixies_loop_t pixel_loop ){
	pmassadj = GETFLOAT(pixie_mass_adjust, 5.0);
	bool coOrNo = GETBOOL(pixies_use_corountines, false);
	wormhole_t *collide_cohole;
	struct {
		pixies_data_t			*movd;
		moved_collide_pkg_t	*movr;
	} pixie_collider;
	if(coOrNo){
		coroutine_create(&collide_cohole,  0, (wormhole_func_t)pixies_co_collider_gravity_atan2_sincosf);
		printf("\njust letting you know coroutines in pixieloop is on");
	}
	//timevars
	for(;;){
		//timetop
		for(int i = 0; i < pixel_loop.number_of_particles; i++){
			if(GLOBAL_basic_signals.quit_signal){
				return;
			}
			for(int q = 0; q < GLOBAL_num_gravitator_A_crews; q++){
				body_bucket_t *listwalker = GLOBAL_gravitator_group_A_array[q];
				//do{
				for(int r = 0; r < listwalker[0].crew_size; r++){

					if(coOrNo){
						pixie_collider.movr = &listwalker[r].collider;
						pixie_collider.movd = pixel_loop.pixies_loop_anchor + i;
						coroutine_yield(collide_cohole, (uintptr_t)&pixie_collider);
					}else{
						pixies_func_collider_gravity_atan2_sincosf(pixel_loop.pixies_loop_anchor + i, &listwalker->collider);//, pixel_loop.algorithm_switches);
						//pixies_gravity(pixel_loop.pixies_loop_anchor + i, &listwalker->collider, pixel_loop.algorithm_switches);
					}
					//listwalker = listwalker->next_b_bucket;
				}//while(listwalker != GLOBAL_gravitator_group_A_array[q]);
			}
			pixies_bounds_enforce(pixel_loop.pixies_loop_anchor + i);
		}
		if(pixel_loop.loop_pause_interval){
			usleep(pixel_loop.loop_pause_interval);
		}
		//timebottom
	}
}

void*
pixies_loop_launcher ( void *data ){
//	usleep(100000);
	/* we don't mess with *data, so this is sorta
	** passed by value function. this is gonna be a thread
	** so void *data is required by pthread_create */
	pixies_loop_t particle_loop;
	if(data){
		particle_loop = *((pixies_loop_t*)data);
	}
	static int initcolor;
	particle_loop.color += initcolor++;
	if(initcolor == global_gradient ){
		initcolor = 0;
	}else{
		particle_loop.color += global_gradient;
	}
	if(!particle_loop.number_of_particles){
		bug_report("launcher must be provided with # of particles");
	}else if(GETBOOL(pixies_randomize, false)){
		particle_loop.number_of_particles += (rx(particle_loop.number_of_particles));
	}
	if(!particle_loop.name.number){
		particle_loop.name = name_tag("pixel_part");
		/* if multiple pixies, we can tell which because the last four bytes hold the count*/
		static uint32_t count;
		particle_loop.name.number |= count++;//might be useful later??
	}
	static int dot_level;
	if(!dot_level){
		dot_level = GETINT(pixies_tier, 4);
	}
	int pix_squarx = GETINT(pixies_squarxel_size, pixz);
	particle_loop.graphic_pixels = parti_pix_new(particle_loop.color, particle_loop.number_of_particles);
	particle_loop.graphic_pixels->pixz = 'r' * (pix_squarx > 1) + (pix_squarx == 1);
	particle_loop.particle_graphic = drawn_object_factory(particle_loop.name, 'x', true, particle_loop.graphic_pixels);
	particle_loop.dot_level = dot_level;
	if(particle_loop.loop_pause_interval)
		particle_loop.loop_pause_interval += (rx(particle_loop.loop_pause_interval) / 3);
	particle_loop.pixies_loop_anchor = pixies_list_maker(particle_loop);
	dot_list_add(particle_loop.particle_graphic, particle_loop.dot_level + grali_intrand(3));
	pixie_particles_party_loop(particle_loop);
	return NULL;
}


collider_snapshot_t
pixie_parts_examine ( pixies_data_t pixel_loop){
//	moved_collide_pkg_t collider_snapshot;
	collider_snapshot_t	values_snapshot;
//	collider_snapshot = *collider;
	values_snapshot.radius = pixel_loop.phys_measures->radius;
	values_snapshot.radius_reciprocal = pixel_loop.phys_measures->radius_reciprocal;
	values_snapshot.G =  pixel_loop.phys_props->G;
	values_snapshot.mass = pixel_loop.phys_measures->mass;
	values_snapshot.fxpos = pixel_loop.delta_locale.fxpos;
	values_snapshot.fypos = pixel_loop.delta_locale.fypos;
	values_snapshot.deltax = pixel_loop.delta_locale.deltax;
	values_snapshot.deltay = pixel_loop.delta_locale.deltay;
	values_snapshot.deltax_result = pixel_loop.delta_locale.deltax_result;
	values_snapshot.deltay_result = pixel_loop.delta_locale.deltay_result;
	values_snapshot.elasticity = pixel_loop.phys_props->elasticity;
	return values_snapshot;
}

void
print_pixie_snapshot( collider_snapshot_t values_snapshot, int snapdex ){
	printf("\nSNAPDEX[ %d]",snapdex);
	printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\ncontents of values pointed to by collider");
	printf("\n~~~~~~~~~~~~~below~~~~~~~~~~~~~~~");
	printf("\nidentity.name: %s",			values_snapshot.identity.name);
//	printf("\nidentity.number: %llu",	values_snapshot.identity.number);
	printf("\nradius: %f.",					values_snapshot.radius );
	printf("\nradius_reciprocal: %f.",	values_snapshot.radius_reciprocal );
	printf("\nG: %f.",		values_snapshot.G );
	printf("\nmass: %f.",	values_snapshot.mass );
	printf("\nfxpos: %f.",	(float)values_snapshot.fxpos );
	printf("\nfypos: %f.",	(float)values_snapshot.fypos );
	printf("\ndeltax: %f.",	values_snapshot.deltax);
	printf("\ndeltay: %f.",	values_snapshot.deltay );
	printf("\ndeltax_result: %f.",	(float)	(*values_snapshot.deltax_result) );
	printf("\ndeltay_result: %f.",	(float)	(*values_snapshot.deltay_result) );
	printf("\nelasticity: %f.",		values_snapshot.elasticity );
//	printf("\npower_law: %f.",			values_snapshot.power_law );
//	printf("\ncharge_constant: %f.", 	values_snapshot.charge_constant );
//	printf("\ncharge_adjustment: %f.", 	values_snapshot.charge_adjustment );
	printf("\n~~~~~~~~~~~above~~~~~~~~~~~~~~~");
	printf("\ncontents of values pointed to by collider");
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
}
