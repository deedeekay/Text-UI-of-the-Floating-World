#ifndef UIVECTORLINESTEXTUI
#define UIVECTORLINESTEXTUI

#include "coroutine.h"


int VECTORS_color_gradient;

typedef struct vector_lines{
	type_tag_t		identity;
	float				maximum_line_length;
	uint32_t			number_of_points;
	line_t			**line_array;
	int8_t			squarxel_size;
	int				color_scale;
	xcb_point_t		*anchor;
	float_point_t	*float_anchor;
	xcb_point_t		*endpoint;
	float_point_t	*float_endpoint;
	int				power_law;
} vector_lines_t;

typedef struct vector_lines_loop{
	type_tag_t			identity;
	vector_lines_t		*vectors;
	useconds_t			loop_pause_duration;
	int					color;
	float					maxlen;
	name_tag_t			name;
	drawn_object_t		*graphic;
//	vector_rules_t	rules_limits;
	bool					*signals_flag;
	basic_signals_t	*signals;
	bool					drawn_signal;
} vect_lines_loop_t;

vector_lines_t*
vector_lines_filler(int columns, int rows, int power_law, float radius, int color){
	short howmany = columns * rows;
	vector_lines_t *dotty = malloc(sizeof(vector_lines_t));
	dotty->float_anchor = malloc(2 * howmany * sizeof(float));
	dotty->float_endpoint = malloc(2 * howmany * sizeof(float));
	dotty->number_of_points = howmany;
	if(pixz > 1){
		/* usinfg xcb_rectangle_t or xcb_point_t
		** pointers depending on squarxel_size
		** when drawing xcb_poly_point or
		** xcb_poly_rectangle() can be chosen between
		*/
		dotty->anchor = malloc(howmany * sizeof(xcb_rectangle_t));
		dotty->endpoint = malloc(howmany * sizeof(xcb_rectangle_t));
	}else{
		dotty->anchor = malloc(howmany * sizeof(xcb_point_t));
		dotty->endpoint = malloc(howmany * sizeof(xcb_point_t));
	}
	dotty->line_array = malloc(howmany * sizeof(line_t*));
	dotty->power_law = power_law;
	dotty->squarxel_size = pixz;
	dotty->color_scale = _greyscale;//GETINT(vectors_color, _greyscale);
	float cols = columns, rws = rows, xr = xres, yr = yres;
	float xinterval = xr / cols;
	float yinterval = yr / rws;
	for(float x = 0; x < columns; x++){
		for(float y = 0; y < rows; y++){
			int xint, yint;
			xint = x;
			yint = y;
			dotty->line_array[xint + yint * columns] = recycled_or_new_line(color, xint, yint, xint + 25, yint + 25,  NULL);
			float_point_t flot = {	.x = (0.5 + x) * xinterval * global_gsf,
									 		.y = (0.5 + y) * yinterval * global_gsf
										};
			xcb_point_t xpoint = {	.x = x * xinterval,
											.y = y * yinterval
							 		 	};
			dotty->anchor[xint + yint * columns] = xpoint;
			dotty->float_anchor[xint + yint * columns] = flot;
			xpoint.x += 25;
			xpoint.y += 25;
			flot.x = xpoint.x * global_gsf;
			flot.y = xpoint.y * global_gsf;
			dotty->endpoint[xint + yint * columns] = xpoint;
			dotty->float_endpoint[xint + yint * columns] = flot;
		}
	}
	return dotty;
}

/*  draws a line segment between x1,y1 and x2,y2 usinfg pixel_size sized   **
** blocks. Only uses the value of pixz, i.e. the pixel size of the main window**
** as matches xres and yres */
uintptr_t
vectors_drawline_co ( wormhole_t *hole, uintptr_t data){
	struct {
				int _colorscale;
				float maxx;
				short x1;
				short y1;
				short x2;
				short y2;
				line_t *old_line;
	} *line_data = (void*)data;
	line_t *line = line_data->old_line;
	static float minn;
	if(!minn){
		minn = GETFLOAT(vectors_min_len, 0.3333) * line_data->maxx;
	}
	do{
		if (line_data->x1 < line_data->x2){
			// if drawing from left to right, the line starts one pixel to far to the right
			// but not vice versa! -I eyeballed this, so it may be incorrect but I'm pretty sure
			line_data->x1--;
			line_data->x2--;
		}
		if(line_data->y1 < line_data->y2){
			// ditto for y as for x
			line_data->y1--;
			line_data->y2--;
		}
		int	dx = line_data->x2 - line_data->x1,
				dy = line_data->y2 - line_data->y1;
		float fx = dx, fy = dy;
		float maxymin = hypotf(fx, fy);
		if(maxymin < minn){
			line_data->old_line->number_squarxels = 0;
			line = line_data->old_line;
			goto superdick;
		}else if(maxymin > line_data->maxx){
			float angle = atan2f(fx, fy);
			fx = line_data->maxx * sinf(angle);
			fy = line_data->maxx * cosf(angle);
			dx = fx;
			dy = fy;
		}
		int	dxabs = abs(dx),
				dyabs = abs(dy),
				sdx = esgn(dx),
				sdy = esgn(dy),
				x = dyabs >> 1,
				y = dxabs >> 1,
				px = line_data->x1,
				py = line_data->y1,
				sizeofarray,
				memory_footprint_of_array;
		if(dxabs >= dyabs){
			sizeofarray = dxabs;
		}else{
			sizeofarray = dyabs;
		}
		if(pixz > 1){
			memory_footprint_of_array = sizeofarray * sizeof(xcb_rectangle_t);
		}else{
			memory_footprint_of_array = sizeofarray * sizeof(xcb_point_t);
		}
		if(line_data->old_line){
			line = line_data->old_line;
		}else{
			line = malloc(sizeof(line_t));
			*line = (line_t){};
		}
		if(memory_footprint_of_array > line->squarxel_array_size){
			line->squarxels = realloc(line->squarxels, memory_footprint_of_array);
			if(!line->squarxels){
				bug_report("failed reallocation");
				print_all_bugs();
				exit(0);
			}
			line->squarxel_array_size = memory_footprint_of_array;
		}
		int count = 0;
		//if this is a bhypotfnew line, realloc() acts as malloc() and automagically
		// we have a nicely created new line_t as simply as usinfg an old line_t
		//	line->number_squarxels = sizeofarray;
		xcb_rectangle_t	*rptr = line->rects;
		xcb_point_t			*pptr = line->points;// aka line->squarxels
		// Bresenham's algorithm
		if(dxabs >= dyabs){
			for(int i = 0;i < dxabs; i++){
				count++;
				y += dyabs;
				if (y >= dxabs){
					y -= dxabs;
					py += sdy;
				}
				px += sdx;
				if(pixz > 1){
					rptr->x = px * pixz;
					rptr->y = py * pixz;
					rptr->width  = pixz;
					rptr->height = pixz;
					rptr++;
				}else{
					pptr->x = px;
					pptr->y = py;
				pptr++;
				}
			}
		}else{
			for (int i = 0; i < dyabs;i++){
				count++;
				x += dxabs;
				if (x >= dyabs){
					x -= dyabs;
					px += sdx;
				}
				py += sdy;
				if(pixz > 1){
					rptr->x = px * pixz;
					rptr->y = py * pixz;
					rptr->width  = pixz;
					rptr->height = pixz;
					rptr++;
				}else{
					pptr->x = px;
					pptr->y = py;
					pptr++;
				}
			}
		}
		line->number_squarxels = count;
		if(count){
			float gg = VECTORS_color_gradient, cc = count;
			line->color = (line_data->_colorscale + VECTORS_color_gradient - 1) - ((gg * gg) * (cc / line_data->maxx)) / gg;
			if(line->color < line_data->_colorscale) line->color = line_data->_colorscale;
			if(line->color >= (line_data->_colorscale + VECTORS_color_gradient)) line->color = (line_data->_colorscale + VECTORS_color_gradient - 1);
		}
superdick:;
	}while((line_data = (void*)coroutine_yield(hole, (uintptr_t)line)));
	exit(0);
	return (uintptr_t)line;
}

uintptr_t
vectors_collide_pkg_co ( wormhole_t *hole, uintptr_t data ){
	struct{
		float_point_t point;
		moved_collide_pkg_t *interactor;
		float powerlaw;
		float maxlen;
		float pull_adjuster;
	} *vec_data = (void*)data;
	float sideA, sideB, sideC, r, totaldelta, angle;
	float_point_t xypull;
	do{
		sideB = vec_data->point.x - *vec_data->interactor->fxpos;
		sideC = vec_data->point.y - *vec_data->interactor->fypos;
		sideA = hypotf(sideB, sideC);
		r = sideA * *vec_data->interactor->radius_reciprocal;
		totaldelta = 1000 * *vec_data->interactor->mass / pow(r, vec_data->powerlaw);
		if(totaldelta > vec_data->maxlen)totaldelta = vec_data->maxlen;
		angle = atan2f(sideB, sideC);
		xypull.x = (sinf(angle)*(totaldelta)) * vec_data->pull_adjuster;
		xypull.y = (cosf(angle)*(totaldelta)) * vec_data->pull_adjuster;
	}while((vec_data = (void *)coroutine_yield(hole, (uintptr_t)&xypull)));
	bug_report("coroutine returning instead of yeilding");
	return 0;
}

void
vect_lines_loop_co ( vect_lines_loop_t *vectors_lines ){
	float_point_t *xy = NULL, xy1;
	body_bucket_t *listwalker = GLOBAL_gravitator_group_A_array[0];
	GLOBAL_dot_anchor->drawme = true;
	drawn_object_t *vecci = drawn_object_factory(name_tag("vectors grid #1"), 'v', true, vectors_lines->vectors);
	vecci->drawn_flag = &vectors_lines->drawn_signal;
	dot_list_add(vecci, 0);
	struct {
				int _colorscale;
				float maxx;
				short x;
				short y;
				short x1;
				short y1;
				line_t *old_line;
	} line_data = {};
	struct{
		float_point_t point;
		moved_collide_pkg_t *interactor;
		float powerlaw;
		float maxlen;
		float pull_adjuster;
	} vec_data = {};
	//timevars
	wormhole_t	*drawlines_co,
					*vectors_co;
	coroutine_create(&drawlines_co,  0, vectors_drawline_co);
	coroutine_create(&vectors_co,  0, vectors_collide_pkg_co);
	line_data.maxx = vectors_lines->maxlen;
	line_data._colorscale = vectors_lines->vectors->color_scale;
	for(;;){
		//timetop
		if(GLOBAL_basic_signals.vv){
				vecci->drawme = false;
				vectors_lines->drawn_signal = true;
		}else{
			vecci->drawme = true;
			vectors_lines->drawn_signal = false;
		}
		while(!vectors_lines->drawn_signal && vectors_lines->loop_pause_duration >= 0){
			usleep(vectors_lines->loop_pause_duration);
		}
		for(int i = 0; i < vectors_lines->vectors->number_of_points; i++){
			if(GLOBAL_basic_signals.quit_signal){
				return;
			}
			float count;
			count = 0;
			xy1.x = 0;
			xy1.y = 0;
			for(int q = 0; q < GLOBAL_num_gravitator_A_crews; q++){
				listwalker = GLOBAL_gravitator_group_A_array[q];
				for(int r = 0; r < listwalker[0].crew_size; r++){
					count++;
					vec_data.point = vectors_lines->vectors->float_anchor[i];
					vec_data.interactor = &listwalker[r].collider;
					vec_data.powerlaw = vectors_lines->vectors->power_law;
					vec_data.pull_adjuster = GETFLOAT(vectors_pull_multiplier, 10);
					vec_data.maxlen = vectors_lines->vectors->maximum_line_length;
					xy = (float_point_t*)coroutine_yield(vectors_co, (uintptr_t)&vec_data);
					xy1.x += xy->x;
					xy1.y += xy->y;
				}
				xy->x = xy1.x / count;
				xy->y = xy1.y / count;
				vectors_lines->vectors->float_endpoint[i].x = vectors_lines->vectors->float_anchor[i].x - xy->x;
				vectors_lines->vectors->float_endpoint[i].y = vectors_lines->vectors->float_anchor[i].y - xy->y;
				line_data.x = vectors_lines->vectors->float_anchor[i].x * global_gsf_reciprocal;
				line_data.y = vectors_lines->vectors->float_anchor[i].y * global_gsf_reciprocal;
				line_data.x1 = vectors_lines->vectors->float_endpoint[i].x * global_gsf_reciprocal;
				line_data.y1 = vectors_lines->vectors->float_endpoint[i].y * global_gsf_reciprocal;
				line_data.old_line = vectors_lines->vectors->line_array[i];
				vectors_lines->vectors->line_array[i] = (void *)coroutine_yield(drawlines_co, (uintptr_t)&line_data);
			}
		}
	//timebottom
	}
}

void*
vect_lines_loop_launcher ( void *data ){
	if(!data){
		bug_report("passed NULL for parameter *data");
		return NULL;
	}
	vect_lines_loop_t *loop = calloc(1, sizeof(vect_lines_loop_t));
	*loop = *((vect_lines_loop_t*)data);
	short columns = GETINT(vectors_columns, 10);
	loop->maxlen = GETFLOAT(vectors_maxlen, 7);
	short rows = GETINT(vectors_rows, 5);
	int power_law = GETINT(vectors_power_law, 2);
	float radius = GETFLOAT(vectors_radius, 2.0);
	VECTORS_color_gradient = GETINT(vectors_gradient, global_gradient);
	loop->vectors = vector_lines_filler(columns, rows, power_law, radius, _greenscale);
	loop->vectors->maximum_line_length = GETFLOAT(vectors_max_line_len, 40.0) * GLOBAL_gsf;
	char *nom = GETSTRING(vectors_first_vectors_name, "vectors-1");
	loop->loop_pause_duration = GETINT(vectors_loop_pause_usecs, 0);
	loop->name = name_tag(nom);
	vect_lines_loop_co(loop);
	return NULL;
}

/************************* functions below unused but saving them************
** it is important to not that the basq/asq, casq/asq  is not the equivalents
** of the  sin(angle), cos(angle)
**  the division method makes an other than circular "gravitaional field" */
void
draw_vector_lines ( const vector_lines_t *vec, gralibuf_t *to_draw_in ){
//	printf("\ndrawing lines");
	if(vec->squarxel_size > 1){
		for(int i = 0; i < vec->number_of_points; i++){
		//	printf("\n%d",vec->line_array[i]->color);
			xcb_poly_fill_rectangle(connection,
											to_draw_in->pixmap,
											globalcolorarray[vec->line_array[i]->color].gc,
											vec->line_array[i]->number_squarxels,
											vec->line_array[i]->rects
			);
		}
	}else{
		for(int i = 0; i < vec->number_of_points; i++){
			xcb_poly_point(connection,
								XCB_COORD_MODE_ORIGIN,
								to_draw_in->pixmap,
								globalcolorarray[vec->line_array[i]->color].gc,
								vec->line_array[i]->number_squarxels,
								vec->line_array[i]->points
			);
		}
	}
}


line_t*
vectors_drawline_algo_A ( int _colorscale, float maxx, short x1, short y1, short x2, short y2, line_t *old_line){
	static float minn;
	if(!minn){
		minn = GETFLOAT(vectors_min_len, 0.3333) * maxx;
	}
	int count = 0;
	if (x1 < x2){
		// if drawing from left to right, the line starts one pixel to far to the right
		// but not vice versa! -I eyeballed this, so it may be incorrect but I'm pretty sure
		x1--;
		x2--;
	}
	if(y1 < y2){
		// ditto for y as for x
		y1--;
		y2--;
	}
	int	dx = x2 - x1,
			dy = y2 - y1;
	float fx = dx, fy = dy;
	float maxymin = hypotf(fx, fy);
	if(maxymin < minn){
		old_line->number_squarxels = 0;
		return old_line;
	}else if(maxymin > maxx){
		float angle = atan2f(fx, fy);
		fx = maxx * sinf(angle);
		fy = maxx * cosf(angle);
//		old_line->number_squarxels = 0;
//		return old_line;
		dx = fx;
		dy = fy;
	}
	int	dxabs = abs(dx),
			dyabs = abs(dy),
			sdx = esgn(dx),
			sdy = esgn(dy),
			x = dyabs >> 1,
			y = dxabs >> 1,
			px = x1,
			py = y1,
			sizeofarray,
			memory_footprint_of_array;
	if(dxabs >= dyabs){
		sizeofarray = dxabs;
	}else{
		sizeofarray = dyabs;
	}
	if(pixz > 1){
		memory_footprint_of_array = sizeofarray * sizeof(xcb_rectangle_t);
	}else{
		memory_footprint_of_array = sizeofarray * sizeof(xcb_point_t);
	}
	line_t *line;
	if(old_line){
		line = old_line;
	}else{
		line = malloc(sizeof(line_t));
		*line = (line_t){};
	}
	if(memory_footprint_of_array > line->squarxel_array_size){
		line->squarxels = realloc(line->squarxels, memory_footprint_of_array);
		if(!line->squarxels){
			bug_report("failed reallocation");
			print_all_bugs();
			exit(0);
		}
		line->squarxel_array_size = memory_footprint_of_array;
	}
	//if this is a bhypotfnew line, realloc() acts as malloc() and automagically
	// we have a nicely created new line_t as simply as usinfg an old line_t
	//	line->number_squarxels = sizeofarray;
	xcb_rectangle_t	*rptr = line->rects;
	xcb_point_t			*pptr = line->points;// aka line->squarxels
	// Bresenham's algorithm
	if(dxabs >= dyabs){
		for(int i = 0;i < dxabs; i++){
			count++;
			y += dyabs;
			if (y >= dxabs){
				y -= dxabs;
				py += sdy;
			}
			px += sdx;
			if(pixz > 1){
				rptr->x = px * pixz;
				rptr->y = py * pixz;
				rptr->width  = pixz;
				rptr->height = pixz;
				rptr++;
			}else{
				pptr->x = px;
				pptr->y = py;
			pptr++;
			}
		}
	}else{
		for (int i = 0; i < dyabs;i++){
			count++;
			x += dxabs;
			if (x >= dyabs){
				x -= dyabs;
				px += sdx;
			}
			py += sdy;
			if(pixz > 1){
				rptr->x = px * pixz;
				rptr->y = py * pixz;
				rptr->width  = pixz;
				rptr->height = pixz;
				rptr++;
			}else{
				pptr->x = px;
				pptr->y = py;
				pptr++;
			}
		}
	}
	line->number_squarxels = count;
	if(count){
		float gg = VECTORS_color_gradient, cc = count;
		line->color = (_colorscale + VECTORS_color_gradient - 1) - ((gg * gg) * (cc / maxx)) / gg;
		if(line->color < _colorscale) line->color = _colorscale;
		if(line->color >= (_colorscale + VECTORS_color_gradient)) line->color = (_colorscale + VECTORS_color_gradient - 1);
	}
	return line;
}

float_point_t
vectors_sbod_interact_atan ( float_point_t point, moved_collide_pkg_t *interactor, float powerlaw, float maxlen, float pull_adjuster){
	float sideA, sideB, sideC, r, totaldelta, angle;
	sideB = point.x - *interactor->fxpos;
	sideC = point.y - *interactor->fypos;
	sideA = hypotf(sideB, sideC);
	r = sideA * *interactor->radius_reciprocal;
	totaldelta = 1000 * *interactor->mass / pow(r, powerlaw);
	if(totaldelta > maxlen)totaldelta = maxlen;
	angle = atan2f(sideB, sideC);
	float_point_t xypull;
	xypull.x = (sinf(angle)*(totaldelta)) * pull_adjuster;
	xypull.y = (cosf(angle)*(totaldelta)) * pull_adjuster;
	return xypull;
}

void
vsgect_lines_loop ( vect_lines_loop_t *vectors_lines ){
	float_point_t xy, xy1;
	int x, y, x1, y1;
	body_bucket_t *listwalker = GLOBAL_gravitator_group_A_array[0];
	GLOBAL_dot_anchor->drawme = true;
	drawn_object_t *vecci = drawn_object_factory(name_tag("vikki"), 'v', true, vectors_lines->vectors);
	vecci->drawn_flag = &vectors_lines->drawn_signal;
	dot_list_add(vecci, 0);
	//timevars
	for(;;){
		//timetop
		vectors_lines->drawn_signal = false;
		while(!vectors_lines->drawn_signal && vectors_lines->loop_pause_duration >= 0){
			usleep(vectors_lines->loop_pause_duration);
		}
		for(int q = 0; q < GLOBAL_num_gravitator_A_crews; q++){
			for(int i = 0; i < vectors_lines->vectors->number_of_points; i++){
				if(GLOBAL_basic_signals.quit_signal){
					return;
				}
				float count;
				count = 0;
				xy1.x = 0;
				xy1.y = 0;
				listwalker = GLOBAL_gravitator_group_A_array[q];
				for(int r = 0; r < listwalker[0].crew_size; r++){
		//		do{
					count++;
					xy = vectors_sbod_interact_atan( vectors_lines->vectors->float_anchor[i], &listwalker[r].collider, vectors_lines->vectors->power_law, vectors_lines->vectors->maximum_line_length, 10);
					xy1.x += xy.x;
					xy1.y += xy.y;
			//		listwalker = listwalker->next_b_bucket;
				}//while(listwalker != GLOBAL_gravitator_group_A_array[q]);
				xy.x = xy1.x / count;
				xy.y = xy1.y / count;
				vectors_lines->vectors->float_endpoint[i].x = vectors_lines->vectors->float_anchor[i].x - xy.x;
				vectors_lines->vectors->float_endpoint[i].y = vectors_lines->vectors->float_anchor[i].y - xy.y;
				x = vectors_lines->vectors->float_anchor[i].x * global_gsf_reciprocal;
				y = vectors_lines->vectors->float_anchor[i].y * global_gsf_reciprocal;
				x1 = vectors_lines->vectors->float_endpoint[i].x * global_gsf_reciprocal;
				y1 = vectors_lines->vectors->float_endpoint[i].y * global_gsf_reciprocal;
				vectors_lines->vectors->line_array[i] = vectors_drawline_algo_A( vectors_lines->vectors->color_scale, vectors_lines->maxlen,
														x, y, x1, y1,
														vectors_lines->vectors->line_array[i]
													 );
			}
		}//timebottom
	}
}

line_t*
vectors_drawline_algo_B ( int _colorscale, float maxx, short x1, short y1, short x2, short y2, line_t *old_line, gralibuf_t *to_draw_in){
	static float minn;

	if(!minn){
		minn = GETFLOAT(vectors_min_len, 0.3333) * maxx;
	}
	int count = 0;
	if (x1 < x2){
		// if drawing from left to right, the line starts one pixel to far to the right
		// but not vice versa! -I eyeballed this, so it may be incorrect but I'm pretty sure
		x1--;
		x2--;
	}
	if(y1 < y2){
		// ditto for y as for x
		y1--;
		y2--;
	}
	int	dx = x2 - x1,
			dy = y2 - y1;
	float fx = dx, fy = dy;
	float maxymin = hypotf(fx, fy);
	if(maxymin < minn){
		old_line->number_squarxels = 0;
		return old_line;
	}else if(maxymin > maxx){
		old_line->number_squarxels = 0;
		return old_line;
	}

	int	dxabs = abs(dx),
			dyabs = abs(dy),
			sdx = esgn(dx),
			sdy = esgn(dy),
			x = dyabs >> 1,
			y = dxabs >> 1,
			px = x1,
			py = y1,
			sizeofarray,
			memory_footprint_of_array;
	if(dxabs >= dyabs){
		sizeofarray = dxabs;
	}else{
		sizeofarray = dyabs;
	}
	if(pixz > 1){
		memory_footprint_of_array = sizeofarray * sizeof(xcb_rectangle_t);
	}else{
		memory_footprint_of_array = sizeofarray * sizeof(xcb_point_t);
	}
	line_t *line;
	if(old_line){
		line = old_line;
	}else{
		line = malloc(sizeof(line_t));
		*line = (line_t){};
	}
	if(memory_footprint_of_array > line->squarxel_array_size){
		line->squarxels = realloc(line->squarxels, memory_footprint_of_array);
		if(!line->squarxels){
			bug_report("failed reallocation");
			print_all_bugs();
			exit(0);
		}
		line->squarxel_array_size = memory_footprint_of_array;
	}
	//if this is a brand-new line, realloc() acts as malloc() and automagically
	// we have a nicely created new line_t as simply as usinfg an old line_t
//	line->number_squarxels = sizeofarray;
	xcb_rectangle_t	*rptr = line->rects;
	xcb_point_t			*pptr = line->points;// aka line->squarxels
	// Bresenham's algorithm
	if(dxabs >= dyabs){
		for(int i = 0;i < dxabs; i++){
			count++;
			y += dyabs;
			if (y >= dxabs){
				y -= dxabs;
				py += sdy;
			}
			px += sdx;
			if(pixz > 1){
				rptr->x = px * pixz;
				rptr->y = py * pixz;
				rptr->width  = pixz;
				rptr->height = pixz;
				rptr++;
			}else{
				pptr->x = px;
				pptr->y = py;
			pptr++;
			}
		}
	}else{
		for (int i = 0; i < dyabs;i++){
			count++;
			x += dxabs;
			if (x >= dyabs){
				x -= dyabs;
				px += sdx;
			}
			py += sdy;
			if(pixz > 1){
				rptr->x = px * pixz;
				rptr->y = py * pixz;
				rptr->width  = pixz;
				rptr->height = pixz;
				rptr++;
			}else{
				pptr->x = px;
				pptr->y = py;
				pptr++;
			}
		}
	}
	line->number_squarxels = count;
	if(count){
		float gg = VECTORS_color_gradient, cc = count;
		line->color = (_colorscale + VECTORS_color_gradient - 1) - ((gg * gg) * (cc / maxx)) / gg;
		if(line->color < _colorscale) line->color = _colorscale;
		if(line->color >= (_colorscale + VECTORS_color_gradient)) line->color = (_colorscale + VECTORS_color_gradient - 1);
		if(pixz > 1){
			xcb_poly_fill_rectangle(connection,
										to_draw_in->drawable,
										globalcolorarray[line->color].gc,
										count,
										line->rects
									);
		}else{
			xcb_poly_point(connection,
						XCB_COORD_MODE_ORIGIN,
						to_draw_in->drawable,
						globalcolorarray[line->color].gc,
						count,
						line->points
			);
		}
	}
	return line;
}

uintptr_t
vectors_collide_pkg_asq_co ( wormhole_t *hole, uintptr_t data ){
	struct{
		float_point_t point;
		moved_collide_pkg_t *interactor;
		float powerlaw;
		float maxlen;
		float pull_adjuster;
	} *vec_data = (void*)data;
	float sideA, sideB, sideC, r, totaldelta;
	float_point_t xypull;
	do{
		sideB = vec_data->point.x - *vec_data->interactor->fxpos;
		sideC = vec_data->point.y - *vec_data->interactor->fypos;
		float bsq = sideB * sideB;
		float csq = sideC * sideC;
		float asq = bsq + csq;
		sideA = sqrtf(asq);
		r = sideA * *vec_data->interactor->radius_reciprocal;
		totaldelta = 1000 * *vec_data->interactor->mass / pow(r, vec_data->powerlaw);
		if(totaldelta > vec_data->maxlen)totaldelta = vec_data->maxlen;
		xypull.x = bsq/asq * totaldelta * vec_data->pull_adjuster * (sideB < 0.0 ? -1.0 : 1.0);//(sinf(angle)*(totaldelta)) * vec_data->pull_adjuster;
		xypull.y = csq/asq * totaldelta * vec_data->pull_adjuster * (sideC < 0.0 ? -1.0 : 1.0);;//(cosf(angle)*(totaldelta)) * vec_data->pull_adjuster;
	}while((vec_data = (void *)coroutine_yield(hole, (uintptr_t)&xypull)));
	bug_report("coroutine returning instead of yeilding");
	return (uintptr_t)&xypull;
}


uintptr_t
vectors_drawline_asq_coroutine ( wormhole_t *hole, uintptr_t data){
	struct {
				int _colorscale;
				float maxx;
				short x1;
				short y1;
				short x2;
				short y2;
				line_t *old_line;
	} *line_data = (void*)data;
	line_t *line = line_data->old_line;
	static float minn;
	if(!minn){
		minn = GETFLOAT(vectors_min_len, 0.3333) * line_data->maxx;
	}
	do{
		if (line_data->x1 < line_data->x2){
			// if drawing from left to right, the line starts one pixel to far to the right
			// but not vice versa! -I eyeballed this, so it may be incorrect but I'm pretty sure
			line_data->x1--;
			line_data->x2--;
		}
		if(line_data->y1 < line_data->y2){
			// ditto for y as for x
			line_data->y1--;
			line_data->y2--;
		}
		int	dx = line_data->x2 - line_data->x1,
				dy = line_data->y2 - line_data->y1;
		float fx = dx, fy = dy;
		float bsq = fx * fx,
				csq = fy * fy,
				asq = bsq + csq;
		float maxymin = sqrtf(asq);//hypotf(fx, fy);
		if(maxymin < minn){
			line_data->old_line->number_squarxels = 0;
			line = line_data->old_line;
			goto superdick;
		}else if(maxymin > line_data->maxx){
			//float angle = atan2f(fx, fy);
	//		fx = line_data->maxx * bsq/asq * (dx < 0? -1.0 : 1.0);//sinf(angle);
	//		fy = line_data->maxx * csq/asq * (dy < 0? -1.0 : 1.0);//cosf(angle);
			dx = line_data->maxx * bsq/asq * (dx < 0? -1.0 : 1.0);//fx;
			dy = line_data->maxx * csq/asq * (dy < 0? -1.0 : 1.0);//fy;
		}
		int	dxabs = abs(dx),
				dyabs = abs(dy),
				sdx = esgn(dx),
				sdy = esgn(dy),
				x = dyabs >> 1,
				y = dxabs >> 1,
				px = line_data->x1,
				py = line_data->y1,
				sizeofarray,
				memory_footprint_of_array;
		if(dxabs >= dyabs){
			sizeofarray = dxabs;
		}else{
			sizeofarray = dyabs;
		}
		if(pixz > 1){
			memory_footprint_of_array = sizeofarray * sizeof(xcb_rectangle_t);
		}else{
			memory_footprint_of_array = sizeofarray * sizeof(xcb_point_t);
		}
		if(line_data->old_line){
			line = line_data->old_line;
		}else{
			line = malloc(sizeof(line_t));
			*line = (line_t){};
		}
		if(memory_footprint_of_array > line->squarxel_array_size){
			line->squarxels = realloc(line->squarxels, memory_footprint_of_array);
			if(!line->squarxels){
				bug_report("failed reallocation");
				print_all_bugs();
				exit(0);
			}
			line->squarxel_array_size = memory_footprint_of_array;
		}
		int count = 0;
		//if this is a bhypotfnew line, realloc() acts as malloc() and automagically
		// we have a nicely created new line_t as simply as usinfg an old line_t
		//	line->number_squarxels = sizeofarray;
		xcb_rectangle_t	*rptr = line->rects;
		xcb_point_t			*pptr = line->points;// aka line->squarxels
		// Bresenham's algorithm
		if(dxabs >= dyabs){
			for(int i = 0;i < dxabs; i++){
				count++;
				y += dyabs;
				if (y >= dxabs){
					y -= dxabs;
					py += sdy;
				}
				px += sdx;
				if(pixz > 1){
					rptr->x = px * pixz;
					rptr->y = py * pixz;
					rptr->width  = pixz;
					rptr->height = pixz;
					rptr++;
				}else{
					pptr->x = px;
					pptr->y = py;
				pptr++;
				}
			}
		}else{
			for (int i = 0; i < dyabs;i++){
				count++;
				x += dxabs;
				if (x >= dyabs){
					x -= dyabs;
					px += sdx;
				}
				py += sdy;
				if(pixz > 1){
					rptr->x = px * pixz;
					rptr->y = py * pixz;
					rptr->width  = pixz;
					rptr->height = pixz;
					rptr++;
				}else{
					pptr->x = px;
					pptr->y = py;
					pptr++;
				}
			}
		}
		line->number_squarxels = count;
		if(count){
			float gg = VECTORS_color_gradient, cc = count;
			line->color = (line_data->_colorscale + VECTORS_color_gradient - 1) - ((gg * gg) * (cc / line_data->maxx)) / gg;
			if(line->color < line_data->_colorscale) line->color = line_data->_colorscale;
			if(line->color >= (line_data->_colorscale + VECTORS_color_gradient)) line->color = (line_data->_colorscale + VECTORS_color_gradient - 1);
		}
superdick:;
	}while((line_data = (void*)coroutine_yield(hole, (uintptr_t)line)));
	exit(0);
	return (uintptr_t)line;
}

#endif
