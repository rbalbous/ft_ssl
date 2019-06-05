#ifndef FT_SSL

# define FT_SSL

# include "ft_printf.h"

typedef struct s_args		t_args;
typedef unsigned char		t_uint8;
typedef struct s_file_queue	t_file_queue;

struct		s_args
{
	t_uint8 arg_q: 1;
	t_uint8 arg_p: 1;
	t_uint8 arg_s: 1;
	t_uint8 arg_r: 1;
	t_int8 md;
};

struct		s_file_queue
{
	char			*str;
	t_file_queue	*next;
};


void		parser(int argc, char **argv, t_args *args);

#endif