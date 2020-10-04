#ifndef CUB3D_H
# define CUB3D_H

typedef struct				s_map_info
{
	// Resolution
	char					*R_SPEC;
	int						R_width;
	int						R_height;


	// texture
	char					*NO_texture; // North texture
	char					*SO_texture; // South texture
	char					*WE_texture; // West wall texture
	char					*EA_texture; // East wall texture
	char					*sprite_texture; // sprite texture

	// FL RGB
	char					*FL_RGB; // Floor color
	int						FL_R;
	int						FL_G;
	int						FL_B;

	// CL RGB
	char					*CL_RGB; // Ceiling color
	int						CL_R;
	int						CL_G;
	int						CL_B;

}							t_map_info;

typedef struct				s_map
{
	char					**map;
	char					*map_1d;
	int						map_width;
	int						map_height;
	t_map_info				info;
}							t_map;

#endif