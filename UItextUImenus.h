#ifndef __SCOREBOARDS_MENUS_LABELS_TEXTSCREEN_RELATED__
#define __SCOREBOARDS_MENUS_LABELS_TEXTSCREEN_RELATED__

enum scoreboard_constants {scoreboard_width_pixiedlimits = 50, val_column_pixiedlimits = 50,  SCOREBOARD_STACKSIZE = 100};
/** useful for object like stuff, handling values of unknown type, like scoreboard_items **/
typedef enum value_types { Zeroh, integer, dbl, flt, string, int16, uint16, int8, uint8, int64, uint64, wraprules, nil, spaces_only, pointer, special, no_edit, enum_values, colors_names } value_type_t;

#define NONE_OF_THESE_enum_value_types( x )\
(x != nil && x != no_edit && x != special && x != zero)

typedef struct code_word{
		char			word[30];
		short_tag_t quicky;
		int			code;
} code_words_t;

typedef struct menu_state{
	int	text_bkgrnd_color;
	bool	text_bkgrnd_on;
	int	block_bkgrnd_color;
	bool	block_bkgrnd_on;
	int	regular_text_color;
	bool	transparent_menu;
	int	text_transparent_color;
}menu_state_t;

/* trying on for size this style of compacting
** this struct  of unions and structs **/
typedef struct menu_items{
	char					itemName[60];
	short_tag_t			itemQuicky;
	int					itemNumber;
} menu_items_t;

typedef struct menu{
	type_tag_t		identity;
	menu_state_t	state;
	textscreen_t	*mscrn;
	char				**vertical_menu_strings;
	drawn_object_t	*menu_lo;
	drawn_object_t	*menu_hi;
	name_tag_t		name;
	menu_items_t	*menu_items;
}menu_t;

typedef struct scoreboard_items{
	char						itemName[60];
	short_tag_t				itemQuicky;
	int						itemNumber;
	enum value_types		value_type;
	union{
		int					*intptr;
		float					*floatptr;
		_Atomic float		*atomfloatptr;
		double				*doubleptr;
		char					*stringptr;
		enum wraprules		*wrapptr;
		void 					*allptr;
	};
}scoreboard_items_t;

typedef struct scoreboard{
	union{
		menu_t					menu;
	struct{
		type_tag_t				identity;
		menu_state_t			state;
		textscreen_t			*mscrn;
		char						**vertical_menu_strings;
		drawn_object_t			*score_beta;
		drawn_object_t			*score_alpha;
		name_tag_t				name;
		scoreboard_items_t	*board_items;
	};};
	int	value_column;
	int	value_width;
	int	decimal_pt_col;
	int	quicky_col;
	int	preferred_width;
	bool	hidden;
}scoreboard_t;

typedef struct scoreboard_items_store{
	int					itemNumber;
	enum value_types	value_type;
	union{
		int				*intptr;
		float				*floatptr;
		_Atomic float	*atomfloatptr;
		double			*doubleptr;
		char				*stringptr;
		enum wraprules *wrapptr;
		void				*allptr;
	};
	union{
		int				int_value;
		float				float_value;
		double			double_value;
		char				string_value[scoreboard_width_pixiedlimits];
		enum wraprules	wraprules_value;
	};
} scoreboard_items_store_t;

typedef struct scoreboard_store{
	scoreboard_t					*board;
	int								num_lines;
	scoreboard_items_store_t	*board_items;
	union{
		int				*intptr;
		float				*floatptr;
		_Atomic float	*atomfloatptr;
		double			*doubleptr;
		char				*stringptr;
		enum wraprules *wrapptr;
		void				*allptr;
	};
	struct scoreboard_store		*next_guy;
	struct scoreboard_store		*prior_guy;
} scoreboard_store_t;

typedef struct scoreboard_stack_history {
	scoreboard_store_t	scoreboard_anchor[SCOREBOARD_STACKSIZE];
	int 						stack_height;
	scoreboard_store_t	*stack_top;
	scoreboard_store_t	top_swap;
} scoreboard_stack_history_t;

scoreboard_t *pixi_limits_UI_scoreboard;

typedef struct word_code{
		name_tag_t	item;
		Q_t			tag;
}word_code_t;

typedef struct scoreboard_line{
		word_code_t		line_item;
		value_type_t	value_type;
		union{
			int				*intptr;
			float				*floatptr;
			_Atomic float	*atomfloatptr;
			double			*doubleptr;
			char				*stringptr;
			enum wraprules *wrapptr;
			void				*allptr;
		};
} scoreboard_line_t;

#define qt( x ) qwiktag( #x )

textscreen_t*
makeMenuVerticalList (	char name[],				char *choices[],	char *placement,
								double proportions,		int textcolor,		int text_bkgrnd_color,
								int txt_trnsprnt_color,	int txtscrn_bkgrnd_color
							);

xy_label_t*
xy_label_new ( xcb_point_t *xypoint, uint16_t sn_max_4_digits, float fontsize );

menu_t*
menu_new ( char *title, menu_items_t *items, menu_state_t menu_state );

bool
xy_label_print ( xy_label_t  *label, char *title, short int x, short int y );

scoreboard_t*
scoreboard_new ( char *title, scoreboard_items_t *items, menu_state_t menu_state, int value_with );

scoreboard_items_t*
scoreboard_item_search ( scoreboard_t *board, char *name_or_quicky );

bool
scoreboard_update ( scoreboard_t *scoreboard );

bool
scoreboard_line_print ( scoreboard_t *board, char *item_name );

scoreboard_store_t*
scoreboard_restore_from_stack ( scoreboard_stack_history_t *stack );

bool
fill_scoreboard_values ( scoreboard_store_t *store, scoreboard_t *board );

scoreboard_store_t*
store_scoreboard_values ( scoreboard_t *board );

bool
scoreboard_commit_to_stack (  scoreboard_store_t *stored_board,  scoreboard_stack_history_t *stack);

#endif
