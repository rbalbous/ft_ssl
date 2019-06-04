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
};

struct		s_file_queue
{
	char			*str;
	t_file_queue	*next;
};


t_file_queue	*parser(int argc, char **argv, t_args *args);

#endif