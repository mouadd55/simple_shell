#ifndef SIMPLESHELL_H
# define SIMPLESHELL_H

# include <string.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

extern int			g_exit_status;

typedef struct s_list
{
	char			*content;
	int				pos;
	char			*type;
	struct s_list	*link;
	struct s_list	*prev;
}					t_list;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*link;
	struct s_env	*prev;
}					t_env;

typedef struct s_cmd
{
	int				flag;
	int				fd_in;
	int				fd_out;
	char			**cmd;
	struct s_cmd	*link;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_vars
{
	int				i;
	int				fd;
	int				j;
	int				end;
	int				flag;
	int				vars;
	int				start;
	int				count;
	int				d_quotes;
	pid_t			child;
	char			*tmp;
	char			*tmp_str;
	char			*str;
	char			*var;
	char			*val;
	char			**arr;
	char			*tmp_key;
	char			*command;
	char			*tmp_value;
	char			**env_arr;
	t_list			*lst;
	t_list			*tmp1;
	t_list			*tmp2;
	t_list			*tmp3;
	t_env			*temp1;
	t_env			*temp2;
	t_env			*temp3;
	t_cmd			*final_list;
}					t_vars;

/********************************* Libft utils ********************************/

int					is_space(int c);
int					ft_isalpha(int ch);
char				is_special(char c);
char				*ft_itoa(long long n);
char				is_quote(char input);
long long			ft_atoi(const char *str);
char				**ft_free_arr(char **str);
int					ft_isdigit(char *str);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
void				ft_putchar(char ch, int fd);
int					ft_strrchr(char *str, int c);
void				ft_putstr_fd(char *s, int fd);
int					check_char(char *input, int c);
int					ft_strchr(char *str, int find);
char				*ft_strjoin(char *s1, char *s2);
char				*f_strchr(const char *s, int c);
char				*f_strrchr(const char *s, int c);
char				*ft_strtrim(char *s1, char *set);
char				*ft_strtrim(char *s1, char *set);
char				**ft_split(char const *s, char *c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					is_alpha_num(char c);

/********************************* List utils *********************************/

int					ft_lstsize(t_list *lst);
t_list				*ft_lstnew(char *content);
t_list				*ft_lstlast(t_list *head);
int					ft_lstsize_env(t_env *env);
t_env				*ft_lstlast_env(t_env *head);
void				*ft_destroy_list(t_list **head);
void				*ft_destroy_list_env(t_env **head);
t_env				*ft_lstnew_env(char *key, char *value);
void				ft_lstadd_back(t_list **head, t_list *new);
void				ft_lstadd_back_env(t_env **head, t_env *new);

/***************************** Parsing functions ******************************/

void				lexer(t_list **list);
int					check_syntax(t_list *lst);
t_list				*ft_split_input(char *input);
void				syntax_error(char *s2, char e);
size_t				ft_count_char(char *input, char c);
void				split_string(t_vars *v, t_cmd *flst, t_env **env, int size);

/**************************** Builtins functions *****************************/

char				*ft_getenv(t_env *env, char *key);
char				*strlower(char *str);
void				catching_signals(int sig);
t_cmd				*lstlast_final(t_cmd *head);
t_env				*ft_copy_env_list(t_env *env);
void				*ft_destroy_final(t_cmd **head);
void				switch_space(char *input, int x);
t_env				*ft_split_environment(char **env);
void				ft_exit(char **cmd, t_cmd *final);
void				spaces_in_quotes(t_cmd **final_list);
void				change_dir_2(t_env **envr, t_vars *v);
void				change_dir(t_env **envr, t_cmd *f_list);
int					ft_printf(const char *first, int fd, ...);
char				*spaces_in_quotes_utils(char *str, int idx);
void				lstadd_back_final(t_cmd **head, t_cmd *new);
void				env_parsing(char **cmd, t_env *env, int fd_out);
void				create_final_list(t_list *list, t_cmd **final_list);
t_cmd				*lstnew_final(char **command, int fd_in, int fd_out);
void				check_cmd(t_env **envr, t_cmd *f_list);
void				first_conditions(t_list *tmp);
int					search_for_pipe(t_vars *v);
char				*strlower(char *str);
void				ft_setenv(t_env **envr, char *key, char *value);
void				pwd(t_cmd *f_list, t_env *env);
/**************************** Execution Part *****************************/

void				exit_by_signal(void);
int					lstsize_cmd(t_cmd *lst);
char				*get_path_value(t_env *env);
char				*get_paths(char *cmd, t_env *env);
char				*get_paths(char *cmd, t_env *env);
int					check_if_builtin(t_cmd *final_list);
char				**create_2d_array_from_env_list(t_env *env);
void				execution(t_cmd *final_list, t_env **envr, t_list **lst);
void				simple_cmd(t_cmd *f_lst, t_env *env, char *cmd, char **arr);
void				ft_builtins(t_env *env, t_cmd *f_lst);
#endif