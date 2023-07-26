#include "simpleshell.h"

int	g_exit_status;

void	recreate_list(t_cmd *final_list, t_env **envr)
{
	t_vars	v;
	int		size;

	size = lstsize_cmd(final_list);
	while (final_list)
	{
		v.i = 0;
		v.str = NULL;
		while (final_list->cmd && final_list->cmd[v.i])
		{
			v.tmp = spaces_in_quotes_utils(final_list->cmd[v.i], 1);
			v.str = _strjoin(v.str, v.tmp);
			free(v.tmp);
			v.str = _strjoin(v.str, " ");
			v.i++;
		}
		if (v.str)
			split_string(&v, final_list, envr, size);
		final_list = final_list->link;
	}
	spaces_in_quotes(&final_list);
}

void	calling_function(t_env **envr, t_list **lst)
{
	t_cmd	*final_list;

	if (check_syntax(*lst))
	{
		g_exit_status = 258;
		return ;
	}
	lexer(lst);
	final_list = NULL;
	if (lst)
	{
		create_final_list(*lst, &final_list);
		if (g_exit_status != -1)
		{
			recreate_list(final_list, envr);
			execution(final_list, envr, lst);
		}
		else
			g_exit_status = 1;
	}
	_destroy_final(&final_list);
}

void	everything_starts_here(t_env *envr)
{
	char	*input;
	t_list	*lst;
	size_t buffer_size = 0;
	ssize_t num_chars_read = 0;

	signal(SIGINT, &catching_signals);
	while (1)
	{
	    input = NULL;
        printf("$ ");
		num_chars_read = getline(&input, &buffer_size, stdin);
		if (num_chars_read < 0)
			break;
		if (input[num_chars_read - 1] == '\n')
			input[num_chars_read - 1]  = '\0';
		if (!input)
			return ;
		if (_strlen(input))
		{
			lst = _split_input(input);
			if (lst)
				calling_function(&envr, &lst);
		}
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*envr;

	(void)av;
	if (ac != 1)
		return (0);
	envr = NULL;
	envr = _split_environment(env);
	signal(SIGQUIT, SIG_IGN);
	everything_starts_here(envr);
	printf("exit\n");
	return (0);
}
