#include "simpleshell.h"

void	print_env(int i, int count, t_env *env)
{
	if (i && i == count)
	{
		while (env)
		{
			if (env->value)
				ft_printf("%s=%s\n", 1, env->key, env->value);
			env = env->link;
		}
	}	
}

void	env_parsing(char **cmd, t_env *env)
{
	t_vars	v;

	v.i = -1;
	v.count = 0;
	while (cmd[++v.i])
	{
		if (ft_strcmp(cmd[v.i], "env") == 0)
			v.count++;
		else if (v.count && cmd[v.i][0] == '-' && ft_strlen(cmd[v.i]) > 1)
		{
			g_exit_status = 1;
			ft_printf("env: illegal option -- %c\n", 2, cmd[v.i][1]);
			return ;
		}
		else if (v.count && cmd[v.i][0] != '-')
		{
			g_exit_status = 127;
			ft_printf("env: %s: No such file or directory\n", 2, cmd[v.i]);
			return ;
		}
	}
	print_env(v.i, v.count, env);
}

t_env	*ft_split_environment(char **env)
{
	int		i;
	int		start;
	int		length;
	t_env	*envr;

	i = -1;
	envr = NULL;
	while (env[++i])
	{
		start = 0;
		length = ft_strlen(env[i]);
		while (env[i][start] != '=')
			start++;
		ft_lstadd_back_env(&envr, ft_lstnew_env(ft_substr(env[i], 0, start),
				ft_substr(env[i], start + 1, length)));
	}
	return (envr);
}
