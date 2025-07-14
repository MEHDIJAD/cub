/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:23:10 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/14 16:21:01 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h> 
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <stdbool.h>

//# include "../MLX/minilibx.h" // TODO: later or not because will switch to mac
# include "../minilibx_opengl/mlx.h"

// # include "../minilibx-linux/mlx.h"

#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280
#define TILE_SIZE 32
#define MINIMAP_TILE_SIZE 18
#define PI 3.14159265358979323846
#define FOV_ANGLE (60 * (PI / 180.0))

#define NAME "cub3D"
#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 5
#define WALL '1'
#define FLOOR '0'


// # define S_KEY	1
// # define A_KEY	0
// # define W_KEY	13
// # define D_KEY	2
// # define ESC_KEY	53

// # define DOWN_KEY	125
// # define UP_KEY		126
// # define RIGHT_KEY	124
// # define KEY_LEFT	123


# define KEY_W        13
# define KEY_A         0
# define KEY_S         1
# define KEY_D         2
# define KEY_ESC      53

# define KEY_UP      126
# define KEY_LEFT    123
# define KEY_RIGHT   124
# define KEY_DOWN    125


//------------------//


// this will hold RGB in the map sep by comma
typedef struct s_rgb
{
	int red;
	int green;
	int blue;
	int is_set; //  check if the F or C been found the susccessfully parsed 
} t_rgb;

// thie hils textures and color assets

typedef struct s_assets
{
	char *north_tex_path;
	char *east_tex_path;
	char *south_tex_path;
	char *west_tex_path;
	t_rgb floor_rgb;
	t_rgb ceilllig_rgb;
	void *wall_textures[4]; 

	int checker_flag; 
	
}t_assets;

typedef struct  s_map
{
	char **grid; // this i will be transfering into int each one atoi '1' ==> 1 {later} 
	int height; // nmr of rows in the map 
	int width; // max width in the map to allocate based on it + 1 of null ; others with "\0" 
	double map_player_x;
	double map_player_y;
	char spawn_side_face; //{N S W E}
	
}	t_map;


typedef struct  s_id_checker
{
	int no;
	int ea;
	int so;
	int f;
	int we;
	int c;
}t_id_checker;

typedef struct s_imag
{
	void	*img_ptr;
	char	*addr;
	int		bpp; // Bits per pixel x - COL
	int		line_len; // Bytes per line y - ROWS
	int		endian;
}	t_img;

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	bool	was_hit_vertical;

	bool	is_ray_facing_down;
	bool	is_ray_facing_up;
	bool	is_ray_facing_left;
	bool	is_ray_facing_right;

	float horz_wallhitx;
	float horz_wallhity;
	float vert_wallhitx;
	float vert_wallhity;

	bool found_horz_wall;
	bool found_vert_wall;
	
}	t_ray;

typedef struct s_player
{
	float	x;
	float	y;
	float	rotation_angle;
	int		turn_direction; // -1 for left, +1 for right
	int    strafe_direction;
	int		walk_direction; // -1 for back, +1 for forward 
	float	move_speed;
	float	rotation_speed;
}	t_player;


typedef struct s_game
{
	void *mlx;
	void *win;
	t_map map;
	int	screen_width; // will be macro later
	int	screen_height; // same
	t_assets asset_data;
	t_img	img;
	t_ray 	ray;
	t_player player; // TODO: for mehdi to add this one; 
	t_id_checker checklist; 
	
	
}t_game;

//-------- Helpers Func ----------//



	
void free_grid(char **grid);
//int  exit_game(t_cub_data *data);
void exit_with_error(char *message, t_game *game);

//LIB

// Memory and Character Functions
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_itoa(int n);
void ft_putstr(char *str);
// String Manipulation Functions
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);

// File Descriptor Functions
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

// Linked List Struct and Functions
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));


// GNL 
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);



//-------- Parsing Func ----------//



//void free_grid(char **grid);
//int  exit_game(t_game *game);


//-------- Rendring Func ----------//
bool	intialize_mlx(t_game *game);
void	render(t_game *game);
bool	intialize_ray(t_game *game);
float	normalize_angle(float angle);
bool	hit_wall(t_game *game, float x, float y);
int		ft_exit(t_game *game);


//-------- testing makefile relink and functionality ----------//
	void ft_prt_pars();
	// void ft_prt_rend();
	void ft_prt_tool();

	
#endif
