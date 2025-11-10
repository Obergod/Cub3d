 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:08:16 by mafioron          #+#    #+#             */
/*   Updated: 2025/11/10 17:13:44 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../full_libft/include/libft.h"
# include "../full_libft/include/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define NO_TEXT 0
# define SO_TEXT 1
# define WE_TEXT 2
# define EA_TEXT 3
# define FLOOR 4
# define CEILING 5

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;

	char	**map;
	char	**textures;
	int		height;
	int		width;
	int		map_height;
	int		map_width;
	int		player_row;
	int		player_col;
	char	player_dir;
}	t_cub;


/*****		a trier		*******/
int		check_textures(char **cub, t_cub *vars);
void	flood_fill(char **map, int row, int col, bool *is_valid);
int		only_textures(char *texture);
int		check_wall(char **map, int row, int col);
int		check_map(char **cub_file, t_cub *cub);
int		test_image(t_cub *cub, char *texture);
int		check_colors(char *texture);
t_cub	*inits(void);
int		check_double(char **cub, int i);
int		check_errors(int fd, t_cub *cub);


/*****		Parsing_utils	*******/
int	is_texture(char *line);
void free_cub(t_cub *cub);


/*****		Player_utils	*******/
int	is_player(char c);
int	save_player(t_cub *cub, int row, int col, char dir);
int	check_tile(t_cub *cub, char **map, int row, int col);

/*****		inits		*******/
char	**init_textures(char **cub);
int	set_texture(char *cub, char **texture);







#endif
