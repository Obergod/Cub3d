/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:08:16 by mafioron          #+#    #+#             */
/*   Updated: 2025/06/30 17:08:18 by mafioron         ###   ########.fr       */
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
# define NO_TEXTURE 0
# define SO_TEXTURE 1
# define WE_TEXTURE 2
# define EA_TEXTURE 3
# define F_COLOR 4
# define C_COLOR 5

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;

	char	**map;
	char	**textures;
	int		height;
	int		width;
}	t_vars;



/*****		a trier		*******/
int		check_textures(char **cub, t_vars *vars);
void	flood_fill(char **map, int row, int col, bool *is_valid);
int		only_textures(char **cub, t_vars *vars);
int		check_wall(char **map, char c);
int		check_map(char **cub);
int		test_images(t_vars *vars);
t_vars	*inits(void);








#endif
