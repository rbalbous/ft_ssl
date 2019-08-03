#ifndef FT_SSL

# define FT_SSL

# include "ft_printf.h"

/*
** DEFINE MESSAGE DIGEST COMMAND 
*/
# define MDC_NB 2
# define MDC_CMD {"md5", "sha256"}

typedef struct s_args		t_args;
typedef unsigned char		t_uint8;
typedef struct s_file_queue	t_file_queue;
typedef struct s_hash_md5	t_hash;

struct		s_args
{
	t_uint8 arg_q: 1;
	t_uint8 arg_p: 1;
	t_uint8 arg_s: 1;
	t_uint8 arg_r: 1;
	t_uint8 arg_nf: 1;
	t_int8 md;
};

struct		s_file_queue
{
	char			*str;
	t_file_queue	*next;
};

struct		s_hash_md5
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;
	unsigned int aa;
	unsigned int bb;
	unsigned int cc;
	unsigned int dd;
};


void			parser(int argc, char **argv, t_args *args);
void			disp_usage();
void			disp_usage_exit();
void			disp_usage_ssl_exit(char *str);
void			disp_usage_ssl(char *str);
void			algo_md5(t_args *args, char *str, char *file);

#endif