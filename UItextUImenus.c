#ifndef __UI_text_menus_MENUS__
#define __UI_text_menus_MENUS__

/* switch between old values and current edit of values */
void
scoreboard_swap ( scoreboard_t *board, scoreboard_store_t *alternate);
/*retrieve_scoreboard_values() fills board with the values in store */

void
pixi_edit_limits_scoreboard ( scoreboard_t *board){
	txPrnt("\n\nTHIS IS A STUB FOR pixi_edit_limits_scoreboard\n\n");
}

void
help_menu ( void ){
	txPrnt("THIS IS A STUB FOR helpMenuFunction()\n");
	txPrnt("THIS IS A STUB FOR helpMenuFunction()\n");
}

void
pixi_data_restore ( void ){
	printf("\n this is a stub for the pixi_Data_restore");
	bug_report("called stub function-not true error(?)");
}

void
pixi_data_commit ( void ){
	printf("\n this is a stub for the pixi_data_commit");
	bug_report("called stub function-not true error(?)");
}

void
sbodDeleteFunc ( void *unused ){
	printf("\n this is a stub for the sbodDeleteFunc");
	bug_report("called stub function-not true error(?)");
}

void
pixi_edit_shared_body_data( void *unused ){
printf("\nthis is a stup for pixi_edit_shared_body_data-not true error");
bug_report("this is a stub for pixi_edit_shared_body_data-not true error");
}

void
sbod_Edit_individual ( void *unused ){
	printf("\nthis is a stup for sbod_Edit_individual-not true error");
	bug_report("this is a stub for sbod_Edit_individual-not true error");
}

void
sbodSharedEdit ( void *unused ){
	printf("\nthis is a stub for sbodSharedEdit()- not a true error");
	bug_report("this is a stub for sbodSharedEdit()- not a true error");
}

void
sbodGlobalsEdit ( void *unused ){
	printf("\nthis is a stub for sbodGlobalsEdit()- not a true error");
	bug_report("this is a stub for sbodGlobalsEdit()- not a true error");
}

void
sbodReview ( void *unused ){
	printf("\nthis is a stub for sbodReview()- not a true error");
	bug_report("this is a stub for sbodReview()- not a true error");
}

void
pixi_Data_shared ( void ){
	txPrnt("\n\n\tSTUB FOR EDITING PIXI PARTICLES SHARED BODY DATA\n\n");
	usleep(250000);
	;
}

void
enterValues ( void  ){
	txPrnt("\n\n\tSTUB enterValues() FOR ENTERING DATA FOR pixiEditRuleLimits()\n\n");
	usleep(250000);
}
menu_items_t UI_context_first_menu[] = {
	{.itemName = "Edit Pixel particles  ep",	.itemNumber = 0, .itemQuicky = qt(ep)},
	{.itemName = "Simple Bodies edit    sb", 	.itemNumber = 1, .itemQuicky = qt(sb)},
	{.itemName = "Keyboard Work         kw",	.itemNumber = 2, .itemQuicky = qt(kw)},
	{.itemName = "Make 8bit Characters  m8",	.itemNumber = 6, .itemQuicky = qt(kw)},
	{.itemName = "Global Values edit    gv", 	.itemNumber = 5, .itemQuicky = qt(gv)},
	{.itemName = "Print Drawn_object_t tree", .itemNumber = 3, .itemQuicky = qt(pd)},
	{.itemName = "Transparent Menu ..t",		.itemNumber = 4, .itemQuicky = qt(t)},
	{.itemNumber = -1}
};
#define GlPxRl GLOBAL_pixie_rules
#define GlbPxPrpty GLOBAL_pixie_phys_properties
#define GlbPxLimits 	GLOBAL_pixie_phys_limits
scoreboard_items_t pixi_limits_UI_scoreboard_items[] =
{
	{.itemNumber = 11, .itemName = {0},	.itemQuicky.number = 0, .value_type = spaces_only, .intptr = NULL},
	{.itemNumber = 110, .itemName = "deltamax          dm: ", 	.itemQuicky = qt(dm),		.value_type = flt,		.atomfloatptr = &GlbPxLimits.deltamax},
	{.itemNumber = 1, .itemName = "decellerando      dc: ",	.itemQuicky = qt(dc),		.value_type = flt,			.atomfloatptr = &GlbPxLimits.decellerando},
	{.itemNumber = 2, .itemName = "right margin      rm: ",	.itemQuicky = qt(rm),		.value_type = flt,			.atomfloatptr = &GlPxRl.xright},
	{.itemNumber = 3, .itemName = "left margin       lm: ",	.itemQuicky = qt(lm),		.value_type = flt,			.atomfloatptr = &GlPxRl.xleft},
	{.itemNumber = 4, .itemName = "top margin        tm: ", 	.itemQuicky = qt(tm),		.value_type = flt,			.atomfloatptr = &GlPxRl.ytop},
	{.itemNumber = 5, .itemName = "bottom margin     bm: ",	.itemQuicky = qt(bm),		.value_type = flt, 			.atomfloatptr = &GlPxRl.ybottom},
	{.itemNumber = 7, .itemName = "wrap rules:       wr: ",		.itemQuicky = qt(wr), 	.value_type = wraprules,	.wrapptr = &GlPxRl.wraprules},
	{.itemNumber = 9, .itemName = "elasticity        el: ",  	.itemQuicky = qt(el),	.value_type = flt,			.atomfloatptr = &GlbPxPrpty.elasticity},
	{.itemNumber = 10,.itemName = "margin decel      md: ", 	.itemQuicky = qt(md),		.value_type = flt,		.atomfloatptr = &GlPxRl.bumper_elasticity},
//	{.itemNumber = 8, .itemName = "loop pause, usecs lp: ", .itemQuicky =  qt(lp),	.value_type = integer,	.intptr = &GlPxRl.frequency},
	{.itemNumber = 14,.itemName = "cycle colors", 		.itemQuicky = qt(cc), 			.value_type = special,	.stringptr = "whooops! testing"},
	{.itemNumber = 13,.itemQuicky.number = 0, .value_type = spaces_only, .itemName = {0}, .intptr = NULL},
	{.itemNumber = -1,.itemQuicky.number = 0, .value_type = spaces_only, .itemName = {0}, .intptr = NULL}
};

menu_items_t pixi_edit_limits_UI_menu[] = {
	{.itemName = "Previous Menu         pm", 			.itemNumber = 2,	.itemQuicky = qt(pm)},
	{.itemName = "Edit Values           ev",			.itemNumber = 3,	.itemQuicky = qt(ev)},
	{.itemName = "Restore Values        rv",			.itemNumber = 4,	.itemQuicky = qt(rv)},
	{.itemName = "Commit Values         cv",			.itemNumber = 5,	.itemQuicky = qt(cv)},
	{.itemName = "Swap Old/New Values   sw",			.itemNumber = 8,	.itemQuicky = qt(sw)},
	{.itemName = "History               h",			.itemNumber = 10,	.itemQuicky = qt(h)},
 	{.itemName = "Transparent Menus     t (toggle)",.itemNumber = 6,	.itemQuicky = qt(t)},
	{.itemName = "Text Colors           tc",			.itemNumber = 9,	.itemQuicky = qt(tc)},
	{.itemName = "Hide Scoreboard       hs",			.itemNumber = 7, 	.itemQuicky = qt(hs)},
	{.itemNumber = -1}/* last item is < 0, tells us end of the list*/
};

menu_items_t pixi_top_UI_menu[] = {
  {.itemName = "Previous Menu           pm", .itemNumber = 10,	.itemQuicky = qt(pm)},
  {.itemName = "Transparent Menu        t",	.itemNumber = 2,	.itemQuicky = qt(t)},
  {.itemName = "Edit Rules & Limits     rl",	.itemNumber = 3,  .itemQuicky = qt(rl)},
  {.itemName = "Edit Shared Body Data   bd",	.itemNumber = 4,  .itemQuicky = qt(bd)},
  {.itemName = "Edit Individual Values  ei",	.itemNumber = 5,  .itemQuicky = qt(ei)},
  {.itemName = "Edit Global Pixi Data   eg", .itemNumber = 6,	.itemQuicky = qt(eg)},
  {.itemName = "end of the list", 				.itemNumber = -1, .itemQuicky.number = 0}
};


textscreen_t*
makeMenuVerticalList ( char name[], char *choices[], char *placement, double proportions, int textcolor, int text_bkgrnd_color, int txt_trnsprnt_color, int txtscrn_bkgrnd_color ){
	if(proportions > 1.0){
		bug_report("invalid value for parameter \"proportions\"");
		print_all_bugs();
		exit(0);
	}
	int 	columns = 0,
			lines= 0;
	// which do we have more of? lines or columns?
	for(; (choices[lines]); lines++){
		if (strlen(choices[lines]) >= columns)
			columns = strlen(choices[lines]);
	}
	if( !lines|| !columns){
		bug_report("no menu choices passed");
		print_all_bugs();
		exit(0);
	}
	// recalling that true_width and true_height are globals representing the
	// dimensions of global_display_window
	double 	bufwidth = true_width * proportions,
				bufheight = true_height * proportions,
				biggest = bufwidth,
				fontsize;
	if(bufheight > biggest) biggest = bufheight;
	if(lines > columns){
		fontsize = biggest / lines;
	} else{
		fontsize = biggest / columns;
	}
	textscreen_t *tscrn = mallocCustomTextScreen( name, &global_drawing_buffer, fontsize, columns, lines, textcolor, text_bkgrnd_color, txt_trnsprnt_color, txtscrn_bkgrnd_color);
	clearScreen(tscrn);
	double	screenwidth = tscrn->columnwidth * columns,
				screenheight = tscrn->lineheight * lines;
	if(placement){
		if( !strcmp(placement, "right center")){
			tscrn->xpos = true_width - screenwidth;
			tscrn->ypos = true_height / 2 - screenheight / 2;
		} else if(!strcmp(placement, "center top")){
			tscrn->xpos = true_width/2 - screenwidth / 2;
			tscrn->ypos = 0;
		} else if(!strcmp(placement, "center bottom")){
		 	tscrn->xpos = true_width/2 - screenwidth / 2;
			tscrn->ypos = true_height - screenheight;
		} else if (!strcmp(placement, "left top")){
			tscrn->xpos = 0;
			tscrn->ypos = 0;
		} else if (!strcmp(placement, "left bottom")){
			tscrn->xpos = 0;
			tscrn->ypos = true_height - bufwidth;
		} else if (!strcmp(placement, "left center")){
			tscrn->xpos = 0;
			tscrn->ypos = true_height / 2 - bufwidth / 2;
		} else if (!strcmp(placement, "right top")){
			tscrn->xpos = true_width - screenwidth;
			tscrn->ypos = 0;
		} else if(!strcmp(placement, "right bottom")){
			tscrn->xpos = true_width - screenwidth;
			tscrn->ypos = true_height - screenheight - 5;
		} else if(!strcmp(placement, "center center")){
			tscrn->xpos = true_width/2 - screenwidth / 2;
			tscrn->ypos = true_height / 2 - screenheight / 2;
		} else{
			bug_report("invalid value for parameter \"placement\"");
			print_all_bugs();
			exit(0);
		}
	}else{
		tscrn->xpos = 0;
		tscrn->ypos = 0;
	}
	for(lines = 0; (choices[lines]); lines++){
		printLn(choices[lines], tscrn);
	}
	return tscrn;
}

menu_t*
menu_new ( char *title, menu_items_t *items, menu_state_t menu_state ){
	int count = 0;
	menu_t *menu = calloc(1, sizeof(menu_t));
	menu->name = name_tag(title);
	menu->menu_items = items;
	for(count = 0; items[count].itemNumber != -1; count++);
	menu->vertical_menu_strings = calloc(count + 1, sizeof(char *));
	for(int i = 0; i < count/*items[i].itemNumber != -1*/; i++){
		menu->vertical_menu_strings[i] = items[i].itemName;
	}
	menu->mscrn = makeMenuVerticalList(title, menu->vertical_menu_strings, "right top", 0.4, menu_state.regular_text_color, menu_state.text_bkgrnd_color, menu_state.text_transparent_color,menu_state.block_bkgrnd_color);
	menu->mscrn->xpos = xres * 0.7 * pixz;
	menu->mscrn->ypos = yres * 0.05 * pixz;
	name_tag_t *name_tag_low = calloc(16, sizeof(char));
	name_tag_t *name_tag_hi = calloc(16, sizeof(char));
	snprintf(name_tag_low->name_tag, 15,"lo_%s", title);
	snprintf(name_tag_hi->name_tag, 15, "hi_%s", title);
	menu->menu_lo = drawn_object_factory(*name_tag_low, 'm', false, menu->mscrn);
	menu->menu_hi = drawn_object_factory(*name_tag_hi, 'm', true, menu->mscrn);
	dot_list_add(menu->menu_hi, 99);
	dot_list_add(menu->menu_lo, 0);
	return menu;
}

scoreboard_store_t*
store_scoreboard_values ( scoreboard_t *board ){
	static scoreboard_store_t blank = {};
	scoreboard_store_t *board_store = malloc(sizeof(scoreboard_store_t));
	*board_store = blank;
	// note that the spaces_only items bounding the tops and bottoms of scoareboards are
	// copied. Thats in case they become important to save in the unplanned future
	for(board_store->num_lines = 1; board->board_items[board_store->num_lines - 1].itemNumber != -1; board_store->num_lines++);// so count from 1, so a value of 10 == ten items.
	board_store->board_items = calloc(1, board_store->num_lines * sizeof(scoreboard_items_store_t));
	for(int i = 0; i < board_store->num_lines; i++){
		board_store->board_items[i].allptr = 		board->board_items[i].allptr;
		board_store->board_items[i].itemNumber =	board->board_items[i].itemNumber;
		board_store->board_items[i].value_type =	board->board_items[i].value_type;
		switch(board->board_items[i].value_type){
			case spaces_only:
				memset(board_store->board_items[i].string_value,' ', scoreboard_width_pixiedlimits);
				board_store->board_items[i].stringptr = board->board_items[i].stringptr;
				break;
			case string:
				//width is measured by # of character cells - monospaced
				//and the string is at most that many characters
				strncpy(board_store->board_items[i].string_value, board->board_items[i].stringptr, scoreboard_width_pixiedlimits);
				break;
			case integer:
				board_store->board_items[i].int_value = *board_store->board_items[i].intptr;
				break;
			case dbl:
				board_store->board_items[i].double_value = *board_store->board_items[i].doubleptr;
				break;
			case flt:
				board_store->board_items[i].float_value = *board_store->board_items[i].atomfloatptr;
				break;
			case wraprules:
				board_store->board_items[i].wraprules_value = *board_store->board_items[i].wrapptr;
				break;
			case special:
				break;
			default:
				bug_report("found invalid .value_type in scoreboard");
				free(board_store->board_items);
				free(board);
				return NULL;
		}
	}
	return board_store;
}

scoreboard_t*
scoreboard_new ( char *title, scoreboard_items_t *items, menu_state_t menu_state, int value_width ){
	int count = 0;
	scoreboard_t *board = calloc(1, sizeof(scoreboard_t));
	board->name = name_tag(title);
	board->value_width = value_width;
	board->board_items = items;
	for(count = 0; items[count].itemNumber != -1; count++);
	board->vertical_menu_strings = calloc(count + 1, sizeof(char *));
	for(int i = 0;items[i].itemNumber != -1; i++){
		if(items[i].value_type == spaces_only){
			memset(items[i].itemName, ' ', scoreboard_width_pixiedlimits);
		}
		board->vertical_menu_strings[i] = items[i].itemName;
	}
	board->mscrn = makeMenuVerticalList(title, board->vertical_menu_strings, "center center", 0.7, menu_state.regular_text_color, menu_state.block_bkgrnd_color, menu_state.text_bkgrnd_color, menu_state.text_transparent_color);
	board->value_column = board->mscrn->numcolumns - value_width;
	name_tag_t *name_tag_alpha = calloc(16, sizeof(char));
	name_tag_t *name_tag_beta = calloc(16, sizeof(char));
	snprintf(name_tag_alpha->name_tag, 15, "al_%s", title);
	snprintf(name_tag_beta->name_tag, 15, "be_%s", title);
	board->score_alpha = drawn_object_factory(*name_tag_alpha, 'r', true, board);
//	board->score_beta = drawn_object_factory(*name_tag_beta, 'd', true, board);
	board->hidden = false;
	dot_list_add(board->score_alpha, 99);
	return board;
}

bool
scoreboard_update ( scoreboard_t *scoreboard ){
	for(int i = 0; scoreboard->board_items[i].itemNumber != -1; i++){
		if(!scoreboard_line_print(scoreboard,  scoreboard->board_items[i].itemName)){
			bug_report("false returned by scoreboard_line_print()");
			return false;
		}
  }
  return true;
}
#define qwiknumber(x) ((short_tag_t*)(x))->number

scoreboard_items_t*
scoreboard_item_search ( scoreboard_t *board, char *name_or_quicky ){
	for(int i = 0; board->board_items[i].itemNumber != -1; i++){
		int len_itemname = strlen(board->board_items[i].itemName),
			len_name_or_quicky = strlen(name_or_quicky), the_shorter;
		if(len_name_or_quicky > len_itemname){
			the_shorter = len_itemname;
		}else{
			the_shorter = len_name_or_quicky;
		}
		if(len_name_or_quicky && len_itemname){
			if(!strncmp(name_or_quicky, board->board_items[i].itemName, the_shorter)||
			 (qwiknumber(name_or_quicky) == board->board_items[i].itemQuicky.number)){
				 return &board->board_items[i];
			}
		}
	}
	return NULL;
}


bool
scoreboard_line_print ( scoreboard_t *board, char *item_name_or_quicky ){
	char numstr[board->mscrn->numcolumns];
	memset(numstr, 0, board->mscrn->numcolumns);
	int len_name_or_quicky = strlen(item_name_or_quicky);
	int len_name;
	int i = 0;
	/* the ->value_column was to print from that column to the end, but for now
	** we're subtracting the strlen() of the value and subtract from what is
	** actually ->numcolumns since ->value_column == ->numcolumns here */
	char blanks[board->mscrn->numcolumns];
	memset(blanks, 0, board->mscrn->numcolumns);
	for(;board->board_items[i].itemNumber != -1; i++){
		len_name = strlen(board->board_items[i].itemName);
		/* just in case future use has us seeking using a portion of the .itemName
		** rather than all of it, as  scoreboard_update() calls it with the full name presently*/
		if(len_name > len_name_or_quicky) len_name = len_name_or_quicky;
		if(len_name){
			if(!strncmp(item_name_or_quicky, board->board_items[i].itemName, len_name)){
				break;
			}
		}
	}
	if(i == -1){
		bug_report("GOT TO -1");
		return false;
	}
	bool bugshit = true;
	switch (board->board_items[i].value_type){
		case spaces_only:
			return true;
			break;
		case nil:
			return true;
			break;
		case dbl:
			snprintf(numstr, 9, "%f", *board->board_items[i].doubleptr);
			break;
		case flt:
			snprintf(numstr, 9, "%f", *board->board_items[i].atomfloatptr);
			break;
		case integer:
			sprintf(numstr, "%d..........", *board->board_items[i].intptr);
			break;
		case special:
			/* might need to add something here.... */
			return true;
			break;
		case wraprules:
			if(*board->board_items[i].wrapptr == elastic_bounce){
				snprintf(numstr, board->value_column, "%s", "bounce");
			}else if(*board->board_items[i].wrapptr == inelastic_bounce){
				snprintf(numstr, board->value_column, "%s", "bounce + decellerate");
			}else if(*board->board_items[i].wrapptr == wraparound){
				snprintf(numstr,board->value_column, "%s", "wrap around");
			}else if(*board->board_items[i].wrapptr == decel_wraparound){
				snprintf(numstr, board->value_column, "%s", "wrap around + decellerate");
			}
			break;
		default:
		bug_report("scoreboard item has invalid value type");
			bugshit = false;
	}
	if(NONE_OF_THESE_enum_value_types(board->board_items[i].value_type)){
		if(strlen(numstr) > board->mscrn->numcolumns){
			bug_report("value to print is wider than # of columns");
			return false;
		}
		clearAt(board->mscrn->numcolumns - strlen(numstr) - 1, i, strlen(numstr), board->mscrn);
		bugshit = printAt(board->mscrn->numcolumns - strlen(numstr) - 1, i, numstr, board->mscrn);
		if(!bugshit){
			bug_report("putCursor fucked up");
			bugshit = false;
		}
	}
	return bugshit;
}

/* switch between old values and current edit of values */
void
scoreboard_swap ( scoreboard_t *board, scoreboard_store_t *alternate){
	static bool current_swapped_out = false;
	static scoreboard_store_t *intermediate;
	if(!current_swapped_out){
		current_swapped_out = true;
		intermediate = store_scoreboard_values(board);
		if(!intermediate){
			bug_report("store_scoreboard_values() returned NULL");
		}
		fill_scoreboard_values( alternate, board);
	}else{
		fill_scoreboard_values( intermediate, board);
		free(intermediate->board_items);
		free(intermediate);
		current_swapped_out = false;
	}
}




bool
scoreboard_commit_to_stack ( scoreboard_store_t *stored_board,  scoreboard_stack_history_t *stack){
	if(!stack || !stored_board){
		bug_report("NULL stack or NULL new_save or both");
		return false;
	}
	stack->stack_top->next_guy = stored_board;
	stored_board->prior_guy = stack->stack_top;
	stack->stack_top = stored_board;
	stack->stack_height += 1;
	return true;
}

scoreboard_store_t*
scoreboard_restore_from_stack ( scoreboard_stack_history_t *stack ){
	if(!stack){
		bug_report("NULL stack");
		return false;
	}
	if(stack->stack_height == 0){
		return NULL;
	}
	scoreboard_store_t *return_store = stack->stack_top;
	stack->stack_top = stack->stack_top->prior_guy;
	stack->stack_top->next_guy = NULL;
	stack->stack_height -= 1;
	return_store->prior_guy = NULL;
	return return_store;
}

/*retrieve_scoreboard_values() fills board width the values in store */
bool
fill_scoreboard_values ( scoreboard_store_t *store, scoreboard_t *board ){
	for(int q = 0; store->board_items[q].itemNumber != -1; q++){
		int i;
 		for(i = 0; (board->board_items[i].itemNumber != store->board_items[q].itemNumber)&&
				(board->board_items[i].itemNumber != -1); i++);
		if(board->board_items[i].itemNumber == -1){
			bug_report("could not find match for a board and board store matching items");
			return false;
		}else	if(board->board_items[i].value_type == store->board_items[q].value_type){
			switch(board->board_items[i].value_type){
				case spaces_only:
					// this spaces only issure needs fixing up. stringptr? no there is none
					board->board_items[i].stringptr = store->board_items[q].stringptr;
					break;
				case string:
					//width is measured by # of character cells - monospaced
					//and the string is at most that many characters
					if(board->board_items[i].stringptr){
						strncpy(board->board_items[i].stringptr, store->board_items[q].string_value, strlen(board->board_items[i].stringptr + 1));
					}else{
						board->board_items[i].stringptr = malloc(strlen(store->board_items[q].string_value));
						strncpy(board->board_items[i].stringptr, store->board_items[q].string_value, strlen(store->board_items[q].string_value + 1));
					}
					break;
				case integer:
					*board->board_items[i].intptr = store->board_items[q].int_value;
					break;
				case dbl:
					*board->board_items[i].doubleptr = store->board_items[q].double_value;
					break;
				case flt:
					*board->board_items[i].atomfloatptr = store->board_items[q].float_value;
					break;
				case wraprules:
					*board->board_items[i].wrapptr = store->board_items[q].wraprules_value;
					break;
				case special:
					break;
				case enum_values:
				case colors_names:
				case pointer:
				case no_edit:
					break;
				default:
					bug_report("found invalid .value_type in scoreboard");
					return false;
			}
		}else if(store->board_items[q].value_type == 0){
			printf("\n\nstore..value type: %d itemNumber: %d q: %d", store->board_items[q].value_type, store->board_items[q].itemNumber, q);
		}else {
			printf("\n\nstoredvalue type: %d .. scoreboard vauletype: %d .. itemnumber: %d",store->board_items[q].value_type,
		board->board_items[i].value_type, store->board_items[q].itemNumber);
		printf("\nitemname: %s",board->board_items[i].itemName);
			bug_report("stored scoreboard and scoreboard same itemnumber, different value types");
			return false;
		}
	}
	return true;
}

/* to pop a value off the stack, pass NULL, to push, pass a scoreboard_t */
scoreboard_t*
pixi_ed_limits_stack_pop_push ( scoreboard_t *board ){
	static scoreboard_stack_history_t pixedlimstack;
	static scoreboard_t blank = {};
	if(board){
		scoreboard_store_t *to_store = store_scoreboard_values(board);
		scoreboard_commit_to_stack(to_store, &pixedlimstack);
		return NULL;
	}
	scoreboard_store_t *to_retrieve = scoreboard_restore_from_stack(&pixedlimstack);
	scoreboard_t *return_board = malloc(sizeof(scoreboard_t));
	*return_board = blank;
	fill_scoreboard_values(to_retrieve, return_board);
	return return_board;
}

int
menu_choice ( menu_t *menu, char *instruct, char *prompt ){
	char *cmd;
	int len_itemName, len_cmd, the_shorter;
	if(GLOBAL_text_ui_state.menus_above_animation){
		menu->menu_hi->drawme = true;
		menu->menu_lo->drawme = false;
	}else{
		menu->menu_hi->drawme = false;
		menu->menu_lo->drawme = true;
	}
	if(!txCursor(0, 1)){
		bug_report("cannot txCursor()!");
//		text_UI_exit("failed in UI_context_first");
	}
	txClearScreen();
	txPrntLn(instruct);
	GLOBAL_basic_signals.grali_mono_text_input_error_signal = false;
	cmd = inputStringLn(prompt, txScreenExpose(), "nul", 0);
	if(cmd && cmd[0] == enter)return -2;//will use -2 to represent hitting return, no text
	if(!GLOBAL_basic_signals.grali_mono_text_input_error_signal){
		len_cmd = strlen(cmd);
	}else{
		bug_report("error from inputStringLn()");
		return -1;
	}
	int i = 0;
	for(;menu->vertical_menu_strings[i]; i++){
		len_itemName = strlen(menu->vertical_menu_strings[i]);
		if(len_cmd > len_itemName){
			the_shorter = len_itemName;
		}else{
			the_shorter = len_cmd;
		}
		if(len_cmd && len_itemName){
			if(!strncmp(cmd, menu->vertical_menu_strings[i], the_shorter)||
					shrt_eq_shrt(short_tag(cmd),
					menu->menu_items[i].itemQuicky)
			){
				txClear(len_cmd);
				txClearScreen();
				break;
			}
		}
	}
	txCursor(0, txScreenExpose()->numlines - 2);
	txClearScreen();
	txClearLn(txScreenExpose()->line);
	return menu->menu_items[i].itemNumber;
}

xy_label_t*
xy_label_new ( xcb_point_t *xypoint, uint16_t sn_max_4_digits, float fontsize ){
	char name[15] = {0};
	snprintf(name, 15, "sn: %d", sn_max_4_digits);
	return NULL;//makeXYLabel(name,3,20,fontsize, bright_green, &global_drawing_buffer);
}

bool
xy_label_print ( xy_label_t *label, char *title, short int x, short int y ){
	if(!label){
		bug_report("passed x_y_label_t *label == NULL");
		return false;
	}
	printF(label, "%s\nx: %d\ny: %d", title, x, y);
	return drawTextScreen((textscreen_t*)&label);
}

#endif
