#ifndef SIMPLESHELL_H
# define SIMPLESHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

typedef struct s_err
{
	char *error;
	int nbr;
} t_err;

typedef struct s_info
{
	int ac;
	int interactive;
	int nbr_error;
	int count_cmd;
	int exit_status;
	int current_path;
	pid_t pid;
	char **av;
	char *cmd;
	char *path_value;
	char *buf;
	char **args;
	char *env;
}   t_info;

extern char **environ;

int	_isalpha(int ch);
size_t	_strlen(const char *str);
char	*_strdup(const char *s1);
int	check_char(char *input, int c);
void	_putchar(char ch, int fd);
int	_strcmp(const char *s1, const char *s2);
char	*_substr(char const *s, unsigned int start, size_t len);
void *_re_alloc(void *addr, size_t before, size_t after);
int	_isdigit(char c);
int	nbr_len(long nbr);
char	*_itoa(long n);
void what_error(t_info *vars);
int check_if_arg_has_an_alpha(char *s);
void more_errors(t_info *vars, char *more);
int is_builtin_ar_not(t_info *vars, char **args);
int check_if_arg_has_an_alpha(char *s);
char *find_exact_error(t_info vars);
void execution2(char *cmd, char **args, t_info *vars, char *buf);
int has_x_permission(char *file_name);
int exit_args(t_info *vars, char *nbr);
char	*_strjoin(char *s1, char *s2);
long	_atoi(const char *str);
void tokenization(t_info *vars, char **args);
char *_strcpy(char *dest, char *src);
char *exit_status_and_pid(t_info *vars, char *var);
char *build_error_message(char *part1, char *part2, char *part3, const char *between);
char *take_input();
int check_if_file_exist(char *file);
char *find_right_path(const char *name);
char	**_free_arr(char **str);
int	_count_words(char const *s, char *c);
char	**_split(char const *s, char *c);
int execute_command(char *cmd, char **args, char *buf, t_info *info);
char *where_is_the_cmd(char *filename);
int	printc(char c, int fd);
int	prints(char *s, int fd);
int	_printf(const char *first, int fd, ...);
int	_specifier(va_list args, char specifier, int fd);

#endif
