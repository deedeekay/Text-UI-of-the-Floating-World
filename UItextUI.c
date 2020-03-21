#ifndef __TEXT_UI_UI__
#define __TEXT_UI_UI__


void
pixi_edit_limits_UI ( void );

void
intemcallbackstub(void*data){
	return;
}

void
UI_context_globals ( void ){
	;//stubb. function clipped, put in UImenus_clippingsTextUI.c
}

void
keyboard_work ( void ){
	;//stubb. function clipped, put in UImenus_clippingsTextUI.c
} // keyboard_work()

#define menu_hilow_fix(x)\
	if(GLOBAL_text_ui_state.menus_above_animation){\
		x->menu_hi->drawme = true;\
		x->menu_lo->drawme = false;\
	}else{\
		x->menu_hi->drawme = false;\
		x->menu_lo->drawme = true;\
	}

#define call_from_within_menu( ... )\
	menu->menu_hi->drawme = false;\
	menu->menu_lo->drawme = false;\
	__VA_ARGS__;\
	if(GLOBAL_text_ui_state.menus_visible){\
		if(GLOBAL_text_ui_state.menus_above_animation){\
			menu->menu_hi->drawme = true;\
			menu->menu_lo->drawme = false;\
		}else{\
			menu->menu_hi->drawme = false;\
			menu->menu_lo->drawme = true;\
		}\
	}

#define call_from_within_menu_with_scoreboard( ... )\
	board->score_alpha->drawme = false;\
	menu->menu_hi->drawme = false;\
	menu->menu_lo->drawme = false;\
	__VA_ARGS__;\
	if(GLOBAL_text_ui_state.menus_visible){\
		if(GLOBAL_text_ui_state.menus_above_animation){\
			menu->menu_hi->drawme = true;\
			menu->menu_lo->drawme = false;\
			board->score_alpha->drawme = false;\
		}else{\
			menu->menu_hi->drawme = false;\
			menu->menu_lo->drawme = true;\
			board->score_alpha->drawme = true;\
		}\
	}

void
repeat_lines ( char *line, int howmanytimes, uint64_t repeat_per_second){
	uint64_t pause = (999999 / repeat_per_second);
	for(int i = 0; i < howmanytimes; i++){
		txPrnt(line);
		usleep(pause);
	}
	txClearScreen();
}

void
UI_context_simple_bodies_first ( void ){
	;// stubb
} // UI_context_simple_bodies_first()

void
UI_context_pixel_particles_first ( void ) {
	static menu_t *menu = NULL;
	static menu_state_t menu_state =
					{
						.text_bkgrnd_on = true,
						.text_bkgrnd_color = orange,
						.block_bkgrnd_on = false,
						.block_bkgrnd_color = solid_black,
						.regular_text_color = solid_black,
						.transparent_menu = false,
						.text_transparent_color = bright_green
					};
	if(!menu){
		menu = menu_new("pixi_top_menu", pixi_top_UI_menu, menu_state);
	}
	menu_hilow_fix(menu);
	txClearScreen();
	#define tscrn txScreenExpose()
	for(;;){
		switch(menu_choice(menu,"Pixel-Particles top Menu Context; proceed from here!\n", "Command: ")){
			case -2: //means [enter] was typed, with no preceding text
						break;
			case -1: //bug_report("error from menu_choice()");
						//text_UI_exit("menu_choice() signalled error");
						break;
			case 10: /* remember that .itemNumber is NOT the same as the line number
						** and it may be any arbitrary integer************************/
						menu->menu_lo->drawme = false;
						menu->menu_hi->drawme = false;
						return;
			case 2:	if(!GLOBAL_text_ui_state.menus_transparent){
							if(!textScreenTransparentToggle(menu->mscrn))textScreenTransparentToggle(menu->mscrn);
							GLOBAL_text_ui_state.menus_transparent = true;
						}else{
							if(textScreenTransparentToggle(menu->mscrn))textScreenTransparentToggle(menu->mscrn);
							GLOBAL_text_ui_state.menus_transparent = false;
						}
						break;
			case 3:call_from_within_menu(
						pixi_edit_limits_UI();
					);
					break;
			case 4:call_from_within_menu(
						pixi_edit_shared_body_data(NULL)
					);
					break;
			case 5:call_from_within_menu(
						intemcallbackstub(NULL);
					);
					break;
			case 6:call_from_within_menu(
						intemcallbackstub(NULL);
					);
					break;
			default:
					break;
		}
	}
} // UI_context_pixel_particles_first()

void
UI_context_first ( void ){
	static menu_t *menu = NULL;
	static menu_state_t menu_state;
	if(!menu){
		menu_state = (menu_state_t){
							.text_bkgrnd_on = true,
							.text_bkgrnd_color = orange,
							.block_bkgrnd_on = false,
							.block_bkgrnd_color = _cobaltscale,
							.regular_text_color = solid_black,
							.transparent_menu = false,
							.text_transparent_color = bright_green
						};
		menu = menu_new("1st_menu", UI_context_first_menu, menu_state);
	}
	menu_hilow_fix(menu);
	txClearScreen();
	#define tscrn txScreenExpose()
	for(;;){
		switch(menu_choice(menu,"Top Menu Context, proceed from here!\n", "Command: ")){//UI_context_first_menu[i].itemNumber){
			case -2: //means [enter] was typed, with no preceding text
						break;
			case -1: //bug_report("error from menu_choice()");
						//text_UI_exit("menu_choice() signalled error");
						break;
			case 0:	call_from_within_menu(
							UI_context_pixel_particles_first()
						);
						break;
			case 1:	call_from_within_menu(
							UI_context_simple_bodies_first()
						);
						break;
			case 2:	call_from_within_menu(
							keyboard_work()
						);
						break;
			case 4:	if(!GLOBAL_text_ui_state.menus_transparent){
							if(!textScreenTransparentToggle(menu->mscrn))textScreenTransparentToggle(menu->mscrn);
							GLOBAL_text_ui_state.menus_transparent = true;
						}else{
							if(textScreenTransparentToggle(menu->mscrn))textScreenTransparentToggle(menu->mscrn);
							GLOBAL_text_ui_state.menus_transparent = false;
						}
						break;
			case 5:	call_from_within_menu(
							UI_context_globals();
						);
						break;
			default:
						break;
		}
	}
	#undef tscrn
} // end UI_context_first()

void
pixi_edit_limits_UI ( void ){
	#define board pixi_limits_UI_scoreboard
	static bool scoreboard_visible = true;
	static menu_t *menu = NULL;
	static menu_state_t menu_state =	{
						.regular_text_color = solid_black,
						.text_bkgrnd_on = true,
						.text_bkgrnd_color = orange,
						.block_bkgrnd_on = true,
						.block_bkgrnd_color = solid_black,
						.transparent_menu = false,
						.text_transparent_color = bright_green
					};
	static menu_state_t scoreboard_state = {
						.regular_text_color = banana,
						.text_bkgrnd_on = true,
						.text_bkgrnd_color = orange,
						.block_bkgrnd_on = false,
						.block_bkgrnd_color = solid_black,
						.transparent_menu = true,
						.text_transparent_color = bright_green
					};
	if(!board){
		pixi_limits_UI_scoreboard = scoreboard_new("px_lmts", pixi_limits_UI_scoreboard_items, scoreboard_state, VALUEWIDTHCOLUMNS);
	}
	scoreboard_store_t *save_board;
	save_board = store_scoreboard_values(pixi_limits_UI_scoreboard);
	if(!menu){
		menu = menu_new("pixi_ed_limts", pixi_edit_limits_UI_menu, menu_state);
	}
	txClearScreen();
	#define tscrn txScreenExpose()
	char *cmd;
	int len_itemName, len_cmd, the_shorter;
	if(scoreboard_visible){
		if(!scoreboard_update(pixi_limits_UI_scoreboard)){
			bug_report("scoreboard_update() returned false");
		}
		board->score_alpha->drawme = true;
	}
	for(;;){
		menu_hilow_fix(menu);
		if(!txCursor(0, 1)){
			bug_report("cannot txCursor()!");
			GLOBAL_basic_signals.quit_signal = true;
			usleep(100000);
			text_UI_exit("failed in pixi_edit_limits_UI");
		}
		txClearLn(tscrn->line);
		txPrnt("Pixies, Edit Limits\n");
		cmd = inputStringLn("EDIT particles Choice: ", tscrn, "nul", 0);
		if(GLOBAL_basic_signals.grali_mono_text_input_error_signal){
			bug_report("error from grali_mono_text function");
			text_UI_exit(" grali_mono*() signalled error");
		}
		len_cmd = strlen(cmd);
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
		txCursor(0, tscrn->numlines - 2);
		txClearScreen();
		txClearLn(tscrn->line);
		if(!scoreboard_update(board)){
			bug_report("scoreboard_update() returned false");
		}
		switch(pixi_edit_limits_UI_menu[i].itemNumber){

			case 2:	menu->menu_lo->drawme = false;
						menu->menu_hi->drawme = false;
						board->score_alpha->drawme = false;
						return;
			case 3:	call_from_within_menu_with_scoreboard(
							pixi_edit_limits_scoreboard(board);
						);
						break;
			case 4:	call_from_within_menu_with_scoreboard(
							pixi_data_restore();
						);
						break;
			case 5:	call_from_within_menu_with_scoreboard(
							pixi_data_commit();
						);
						break;
			case 6:	if(!GLOBAL_text_ui_state.menus_transparent){
							if(!textScreenTransparentToggle(menu->mscrn))textScreenTransparentToggle(menu->mscrn);
							if(!textScreenTransparentToggle(board->mscrn))textScreenTransparentToggle(board->mscrn);
							GLOBAL_text_ui_state.menus_transparent = true;
						}else{
							if(textScreenTransparentToggle(menu->mscrn))textScreenTransparentToggle(menu->mscrn);
							if(textScreenTransparentToggle(board->mscrn))textScreenTransparentToggle(board->mscrn);
							GLOBAL_text_ui_state.menus_transparent = false;
						}
						break;
			case 7:	if(GLOBAL_text_ui_state.menus_visible == true){
							if(scoreboard_visible == true){
								board->score_alpha->drawme = false;
								scoreboard_visible = false;
							}else{
								board->score_alpha->drawme = true;
								scoreboard_visible = true;
							}
						}
						break;
			case 8:
					scoreboard_swap(board, save_board);
					break;
			case 9:
					while(1){
						ifkey('\r',
							break;
						);
						if(globalmouse.wheelup){
							board->mscrn->text_color++;
							if(board->mscrn->text_color > last_initialized_palette_color){
								board->mscrn->text_color = last_initialized_palette_color;
							}
						}
						if(globalmouse.wheeldown){
							board->mscrn->text_color--;
							if(board->mscrn->text_color < 1){
								board->mscrn->text_color = 1;
							}
						}
					//	scoreboard_update(pixi_limits_UI_scoreboard);
					}
			default:
				i = 0;
				for(;board->vertical_menu_strings[i]; i++){
					len_itemName = strlen(board->vertical_menu_strings[i]);
					if(len_cmd > len_itemName){
						the_shorter = len_itemName;
					}else{
						the_shorter = len_cmd;
					}
					if(len_cmd && len_itemName){
						if(!strncmp(cmd, board->vertical_menu_strings[i], the_shorter)||
								shrt_eq_shrt(short_tag(cmd),
								board->board_items[i].itemQuicky))
						{
							break;
						}
					}
				}
				txClearScreen();
				#define tscrn txScreenExpose()
				switch(board->board_items[i].itemNumber){
					scoreboard_items_t *item;
					case -2: //means [enter] was typed, with no preceding text
								break;
					case -1: //bug_report("error from menu_choice()");
								//text_UI_exit("menu_choice() signalled error");
								break;
					case 110:
						item = scoreboard_item_search(board, "deltamax");
						*item->floatptr = inputDouble("DELTAMAX...NEW VALUE: ", tscrn, *item->floatptr);
						break;
					case 1:
						item = scoreboard_item_search(board, "decelle");
						*item->floatptr = inputDouble("DECELLERANDO...NEW VALUE: ", tscrn, *item->floatptr);
						break;
					case 2:
						item = scoreboard_item_search(board, "right marg");
						*item->floatptr = inputDouble("RIGHT MARGIN...NEW VALUE: ", tscrn, *item->floatptr);
						break;
					case 3:
						item = scoreboard_item_search(board, "left marg");
						*item->floatptr = inputDouble("LEFT MARGIN...NEW VALUE: ", tscrn, *item->floatptr);
						break;
					case 4:
						item = scoreboard_item_search(board, "top margin");
						*item->floatptr = inputDouble("TOP MARGIN...NEW VALUE: ", tscrn, *item->floatptr);
					break;
					case 5:
						item = scoreboard_item_search(board, "bottom margin");
						*item->floatptr = inputDouble("BOTTOM MARGIN...NEW VALUE: ", tscrn, *item->floatptr);
					break;
					case 7:
						item = scoreboard_item_search(board, "wraparound");
						char *rapper = inputString("WRAP AROUND RULE...NEW VALUE: ", tscrn, 0, 30);
						free(rapper);
					break;
					case 8:
						item = scoreboard_item_search(board, "loop pause");
						*item->intptr = inputInt("LOOP PAUSE-uSECS...NEW VALUE: ", tscrn, *item->intptr);
					break;
					case 9:
						item = scoreboard_item_search(board, "elasticity");
						*item->floatptr = inputDouble("ELASTICITY...NEW VALUE: ", tscrn, *item->floatptr);
					break;
					case 10:
						item = scoreboard_item_search(board, "margin decel");
						*item->floatptr = inputDouble("MARGIN/BUMPER ELASTICITY...NEW VALUE: ", tscrn, *item->floatptr);
					break;
					case 14:
						for(;;){
							txClearScreen();
							GLOBALtext_hi->drawme = true;
							GLOBALtext_lo->drawme = false;
							GLOBAL_text_ui_state.global_text_above_animation = true;
							GLOBAL_text_ui_state.global_text_visible = true;
							txCursor(5,10);
							txPrnt("CYCLE COLORS\ntype '<' or ',' to scroll, '>' or '.' to scroll the other way\ntype 'x' or 'X' to exit\n");
							txPrnt("OR type '#' to enter a number\n");
							txPrntf("\ncurrent color: %d", tscrn->text_color);
							ifkey('x',
								break;
							);
							ifkey('X',
								break;
							);
							ifkey('#',
								tscrn->text_color = inputInt("\nTERMINAL TEXT COLOR...NEW VALUE: ", tscrn, tscrn->text_color);
							);
							ifkey('<',
								if(tscrn->text_color > last_initialized_palette_color){
									tscrn->text_color = 1;
								}
								tscrn->text_color++;
							);
							ifkey(',',
								if(tscrn->text_color > last_initialized_palette_color){
									tscrn->text_color = 1;
								}
								tscrn->text_color++;
							);
							ifkey('>',
								if(tscrn->text_color < 1){
									tscrn->text_color = last_initialized_palette_color;
								}
								tscrn->text_color--;
							);
							ifkey('.',
								if(tscrn->text_color < 1){
									tscrn->text_color = last_initialized_palette_color;
								}
								tscrn->text_color--;
							);
							usleep(100000);
						}
						break;
					default:
					break;
				}
				break;
			}
			txClearScreen();
			if(!scoreboard_update(pixi_limits_UI_scoreboard)){
				bug_report("scoreboard_update() returned false");
			}
	#undef board
	#undef tscrn
	} // end pixi_edit_limits_UI()
}

#endif
