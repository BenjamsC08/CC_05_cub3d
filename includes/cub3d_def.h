/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_def.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:55:29 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/13 13:49:45 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEF_H
# define CUB3D_DEF_H

# define W_WIDTH			1920
# define W_HEIGHT			1080

# define MAX_TIME			45

# define MOUSE_HIDE			0

# define WALK_SPD			0.5f
# define RUN_SPD			1.0f
# define SENSI				0.5f
# define MOUSE_SENSI_SCALE	0.1f

# define FOV_DEG			70.0f

# define BLOCK				30
# define BLOCK2				10

# define PLAYER_RADIUS		0.10f
# define COLLISION_PAD		0.001f

# define DEGREE				0.0174532925f

# define DOOR_FRAMES		7
# define DOOR_FRAME_MS		120

# define INTERACT_DIST		1.2f
# define INTERACT_STEP		0.20f

# define CHROMA_RGB			0x00FF00FF

# define SPACE				32
# define A_KEY				97
# define D_KEY				100
# define E_KEY				101
# define M_KEY				109
# define S_KEY				115
# define W_KEY				119
# define BACKSPACE			65288
# define ESC				65307
# define L_ARROW			65361
# define U_ARROW			65362
# define R_ARROW			65363
# define D_ARROW			65364
# define PAD_4				65430
# define PAD_8				65431
# define PAD_6				65432
# define PAD_2				65433
# define SHIFT				65505
# define CAPS				65509
# define L_ALT				65513
# define R_ALT				65514
# define DEL				65535

# define MLX_BLACK			0
# define MLX_BLUE			255
# define MLX_GREEN			65280
# define MLX_BORDEAUX		5836288
# define MLX_GREY			9868950
# define MLX_GREY2			4210752
# define MLX_PURPLE			10160621
# define MLX_ORANGE			16075047
# define MLX_WHITE1			16119285
# define MLX_YELLOW			16187136
# define MLX_RED			16711680
# define MLX_WHITE			16777215

# define MLX_TIMER1			2479640
# define MLX_CTIMER1		14297575
# define MLX_TIMER2			14805006
# define MLX_CTIMER2		1972209
# define MLX_TIMER3			11210254
# define MLX_CTIMER3		5566961

# define NORTH				'N'
# define SOUTH				'S'
# define EAST				'E'
# define WEST				'W'

# define EXT				1
# define OPEN				2
# define BAD_COLOR			3
# define BAD_IMAGE			4
# define LINE				5
# define MAP				6

# define TIME_MAX			5999

# define TEX_PTH_DOOR		"./assets/closed_door.xpm"
# define TEX_PTH_DOOR1 		"./assets/closed_door1.xpm"
# define TEX_PTH_DOOR2 		"./assets/closed_door2.xpm"
# define TEX_PTH_DOOR3 		"./assets/closed_door3.xpm"
# define TEX_PTH_DOOR4 		"./assets/closed_door4.xpm"
# define TEX_PTH_DOOR5 		"./assets/closed_door5.xpm"
# define TEX_PTH_DOOR6 		"./assets/closed_door6.xpm"
# define TEX_PTH_DOOR7 		"./assets/closed_door7.xpm"
# define TEX_PTH_EXIT  		"./assets/wall_free.xpm"

typedef enum e_tex_id
{
	TEX_NORTH,
	TEX_SOUTH,
	TEX_WEST,
	TEX_EAST,
	TEX_DOOR_CLOSED,
	TEX_DOOR_CLOSED1,
	TEX_DOOR_CLOSED2,
	TEX_DOOR_CLOSED3,
	TEX_DOOR_CLOSED4,
	TEX_DOOR_CLOSED5,
	TEX_DOOR_CLOSED6,
	TEX_DOOR_CLOSED7,
	TEX_EXIT,
	TEX_COUNT
}	t_tex_id;

typedef pthread_mutex_t	t_mtx;

typedef struct s_vec
{
	float			x;
	float			y;
}					t_vec;

/**
 * @brief  Raycasting state structure.
 *
 * Holds all parameters required for Digital Differential Analysis (DDA)
 * during raycasting. Each field represents either the ray’s direction,
 * stepping logic, or intersection state.
 *
 * - dir       → Normalized direction vector of the ray in world units.
 * - delta     → Distance the ray must travel along x or y to
 *				 cross one grid line.
 * - side      → Current distance to the next grid boundary in each axis.
 * - mapx/y    → Current integer grid cell coordinates where the ray is located.
 * - stepx/y   → Step direction for grid traversal (-1 or +1 along each axis).
 * - side_hit  → Axis of last step (0 = x-side, 1 = y-side), used for shading.
 * - tile      → Characteristic of the map at the current grid cell (wall, empty,
 *				 closed door etc.).
 *
 * This structure is reinitialized per screen column during the raycasting loop
 * and updated by the DDA algorithm until a blocking tile is hit or bounds
 * are reached.
 */
typedef struct s_ray
{
	t_vec			dir;
	t_vec			delta;
	t_vec			side;
	int				mapx;
	int				mapy;
	int				stepx;
	int				stepy;
	int				side_hit;
	char			tile;
}					t_ray;

typedef struct s_cam
{
	t_vec			direction;
	t_vec			plane;
}					t_cam;

typedef struct s_tex
{
	void			*img;
	char			*addr;
	int				w;
	int				h;
	int				bpp;
	int				ll;
	int				endian;
}					t_tex;

typedef struct s_assets
{
	t_tex			tex[TEX_COUNT];
	char			*path[TEX_COUNT];
}					t_assets;

typedef struct s_slice
{
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_slice;

typedef struct s_texspan
{
	t_tex			*texture;
	int				screen_x;
	int				tex_x;
	float			step_y;
	float			tex_y_pos;
}					t_texspan;

typedef struct s_drawctx
{
	int				screen_x;
	float			perp_dist;
	t_ray			*ray;
	t_tex			*tex;
}					t_drawctx;

typedef struct s_rect
{
	int				x;
	int				y;
	int				w;
	int				h;
}					t_rect;

typedef struct s_text
{
	char			*str;
	t_uint			size;
	int				color;
	t_rect			frame;
}					t_text;

typedef struct s_timer
{
	t_uint		start_time;
	t_uint		max_time;
	t_uint		time;
	t_bool		run;
	pthread_t	thread;
	t_mtx		*mtx_time;
	t_mtx		*mtx_run;
	int			color;
}				t_timer;

typedef struct s_conf
{
	int			fd;
	int			is_preset;
	char		*preset;
}				t_conf;

typedef struct s_data_img
{
	int				bpp;
	int				ll;
	int				endian;
	void			*img;
	char			*addr;
}					t_data_img;

typedef struct s_data_desc
{
	char			*path_no;
	char			*path_so;
	char			*path_we;
	char			*path_ea;
	int				floor_color;
	int				ceiling_color;
	char			player;
	int				player_y;
	int				player_x;
	char			**map;
	char			**backup_map;
	int				line_length;
	int				nb_line;
	int				door_anim_on;
	int				door_anim_frame;
	int				door_x;
	int				door_y;
	char			*last_best_time;
	char			*prev_best_time;
	char			*score_history_path;
	t_bool			score_checked;
	t_bool			new_best_time;
	unsigned int	door_next_ms;
}					t_data_desc;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;
	float			backup_angle;
	t_bool			run;
	t_bool			key_up;
	t_bool			key_down;
	t_bool			key_left;
	t_bool			key_right;
	t_bool			rot_left;
	t_bool			rot_right;
}					t_player;

typedef struct s_minimap
{
	t_bool		disp_map;
	t_rect		map;
	t_rect		minimap;
	t_data_img	*mmap_img;
}				t_minimap;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_bool			start;
	t_gc			*gc;
	t_gc			**gc_head;
	t_data_desc		*data_desc;
	t_data_img		*data_img;
	t_player		*player;
	t_minimap		*minimap;
	t_timer			*timer;
	t_assets		assets;
	const char		*bonus_paths[TEX_COUNT - 3];
	int				***tab_num;
	t_bool			lock_mouse;
}					t_game;

#endif
