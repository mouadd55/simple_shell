#ifndef SIMPLESHELL_H
# define SIMPLESHELL_H


# include <sys/wait.h>
# include <limits.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <unistd.h>

/**
 * struct s_list - Represents a node in a linked list.
 * @content: A pointer to the content of the node (usually a string).
 * @type: A pointer to a string representing the type of the node.
 * @link: A pointer to the next node in the linked list.
 * @prev: A pointer to the previous node in the linked list.
 */
typedef struct s_list
{
	char			*content;
	char			*type;
	struct s_list	*link;
	struct s_list	*prev;
}					t_list;

/**
 * struct s_env - Represents a node in a linked list of env variables.
 * @key: A pointer to a string representing the key of an env variable.
 * @value: A pointer to a string representing the value of the env variable.
 * @link: A pointer to the next env variable in the linked list.
 * @prev: A pointer to the previous env variable in the linked list.
 */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*link;
	struct s_env	*prev;
}					t_env;

/**
 * struct s_cmd - Represents a node in a linked list of commands.
 * @flag: An integer representing a flag associated with the command.
 * @cmd: A pointer to a string array containing the command and its arguments.
 * @link: A pointer to the next command node in the linked list.
 * @prev: A pointer to the previous command node in the linked list.
 */
typedef struct s_cmd
{
	int				flag;
	char			**cmd;
	struct s_cmd	*link;
	struct s_cmd	*prev;
}					t_cmd;

/**
 * struct s_vars - Represents a set of variables used for shell execution.
 *
 * @i: Integer variables for temporary storage and control.
 * @j: Integer variables for temporary storage and control.
 * @end: Integer variables for temporary storage and control.
 * @flag: Integer variables for temporary storage and control.
 * @start: Integer variables for temporary storage and control.
 * @count: Integer variables for temporary storage and control.
 * @d_quotes: Integer variable representing the state of double quotes.
 * @child: A process ID representing the child process created by the shell.
 * @tmp: Pointers to temporary strings.
 * @tmp_str: Pointers to temporary strings.
 * @str: Pointers to temporary strings.
 * @val: Pointers to temporary strings.
 * @tmp_key: Pointers to temporary strings.
 * @command: Pointers to temporary strings.
 * @tmp_value: Pointers to temporary strings.
 * @arr: A pointer to a string array.
 * @env_arr: A pointer to a string array representing the env variables.
 * @lst: Pointers to t_list nodes for temporary storage and traversal.
 * @tmp1: Pointers to t_list nodes for temporary storage and traversal.
 * @temp1: A pointer to t_env node for temporary storage and traversal.
 * @final_list: A pointer to the head of the t_cmd linked list.
 */
typedef struct s_vars
{
	int				i;
	int				j;
	int				end;
	int				flag;
	int				start;
	int				count;
	int				d_quotes;
	pid_t			child;
	char			*tmp;
	char			*tmp_str;
	char			*str;
	char			*val;
	char			**arr;
	char			*tmp_key;
	char			*command;
	char			*tmp_value;
	char			**env_arr;
	t_list			*lst;
	t_list			*tmp1;
	t_env			*temp1;
	t_cmd			*final_list;
}					t_vars;

/********************************* Libft utils ******************************/

int					is_space(int c);
int					_isalpha(int ch);
char				is_special(char c);
int					is_alpha_num(char c);
char				is_quote(char input);
char				*_itoa(long n);
int					_isdigit(char *str);
long			_atoi(const char *str);
char				**_free_arr(char **str);
size_t				_strlen(const char *str);
char				*_strdup(const char *s1);
void				_putchar(char ch, int fd);
int					_strrchr(char *str, int c);
int					check_char(char *input, int c);
int					_strchr(char *str, int find);
char				*_strjoin(char *s1, char *s2);
char				*f_strchr(const char *s, int c);
char				*f_strrchr(const char *s, int c);
char				*_strtrim(char *s1, char *set);
char				*_strtrim(char *s1, char *set);
char				**_split(char const *s, char *c);
int					_strcmp(const char *s1, const char *s2);
char				*_substr(char const *s, unsigned int start, size_t len);
/********************************* List utils *******************************/

int					_lstsize(t_list *lst);
t_list				*_lstnew(char *content);
t_list				*_lstlast(t_list *head);
int					_lstsize_env(t_env *env);
t_cmd				*lstlast_final(t_cmd *head);
t_env				*_lstlast_env(t_env *head);
t_cmd				*lstnew_final(char **command);
void				*_destroy_list(t_list **head);
void				*_destroy_final(t_cmd **head);
void				*_destroy_list_env(t_env **head);
t_env				*_lstnew_env(char *key, char *value);
void				_lstadd_back(t_list **head, t_list *new);
void				_lstadd_back_env(t_env **head, t_env *new);

/***************************** Parsing functions ****************************/

void				lexer(t_list **list);
int					check_syntax(t_list *lst);
t_list				*_split_input(char *input);
void				syntax_error(char *s2, char e);
size_t				_count_char(char *input, char c);
void				split_string(t_vars *v, t_cmd *flst, t_env **env, int size);

/**************************** Builtins functions ****************************/

void				catching_signals(int sig);
int					search_for_pipe(t_vars *v);
void				switch_space(char *input, int x);
char				*_getenv(t_env *env, char *key);
t_env				*_split_environment(char **env);
void				ft_exit(char **cmd, t_cmd *final);
void				env_parsing(char **cmd, t_env *env);
void				spaces_in_quotes(t_cmd **final_list);
void				change_dir_2(t_env **envr, t_vars *v);
void				check_cmd(t_env **envr, t_cmd *f_list);
void				change_dir(t_env **envr, t_cmd *f_list);
int					_printf(const char *first, int fd, ...);
char				*spaces_in_quotes_utils(char *str, int idx);
void				lstadd_back_final(t_cmd **head, t_cmd *new);
void				_setenv(t_env **envr, char *key, char *value);
void				create_final_list(t_list *list, t_cmd **final_list);

/**************************** Execution Part *****************************/

int					lstsize_cmd(t_cmd *lst);
char				*get_path_value(t_env *env);
char				*get_paths(char *cmd, t_env *env);
char				*get_paths(char *cmd, t_env *env);
int					check_if_builtin(t_cmd *final_list);
void				_builtins(t_env *env, t_cmd *f_lst);
char				**create_2d_array_from_env_list(t_env *env);
void				execution(t_cmd *final_list, t_env **envr, t_list **lst);
void				simple_cmd(t_cmd *f_lst, t_env *env, char *cmd, char **arr);
#endif
