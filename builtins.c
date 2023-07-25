#include "simpleshell.h"

char	*ft_getenv(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->link;
	}
	return (NULL);
}

void	ft_setenv(t_env **envr, char *key, char *value)
{
	t_env	*env;

	env = *envr;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			free(env->value);
			env->value = ft_strdup(value);
			break ;
		}
		env = env->link;
	}
	free(value);
	return ;
}

void	pwd(t_cmd *f_list, t_env *env)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = strlower(f_list->cmd[0]);
	if (!ft_strcmp("pwd", pwd))
	{
		free(pwd);
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			pwd = ft_getenv(env, "PWD");
			i = 1;
		}
		ft_printf("%s\n", f_list->fd_out, pwd);
	}
	if (!i)
		free(pwd);
}

void	change_dir_2(t_env **envr, t_vars *v)
{
	if (v->tmp_str && !chdir(v->tmp_str))
	{
		v->command = getcwd(NULL, 0);
		if (!v->command)
		{
			ft_setenv(envr, "OLDPWD", ft_strdup(ft_getenv(*envr, "PWD")));
			v->tmp_value = ft_getenv(*envr, "PWD");
			ft_setenv(envr, "PWD", ft_strjoin(ft_strdup(v->tmp_value), "/.."));
			ft_putstr_fd("cd: error retrieving current", 2);
			ft_putstr_fd(" directory: getcwd: cannot access parent ", 2);
			ft_putstr_fd("directories: No such file or directory\n", 2);
		}
		else
		{
			ft_setenv(envr, "OLDPWD", ft_strdup(ft_getenv(*envr, "PWD")));
			ft_setenv(envr, "PWD", v->command);
		}
	}
	else
	{
		g_exit_status = 1;
		perror(v->tmp_str);
	}
}

int	check_cd_env(t_env **envr, t_cmd *f_list, t_vars *v)
{
	if (!f_list->cmd[1] || !ft_strcmp(f_list->cmd[1], "~"))
	{
		chdir(getenv("HOME"));
		return (1);
	}
	else if (!ft_strcmp(f_list->cmd[1], "-"))
	{
		if (ft_getenv(*envr, "OLDPWD"))
		{
			v->tmp_str = ft_strdup(ft_getenv(*envr, "OLDPWD"));
			ft_printf("%s\n", 1, v->tmp_str);
		}
		else
		{
			ft_putstr_fd("Shell: : cd: OLDPWD not set\n", 2);
			return (1);
		}
		return (0);
	}
	else
		v->tmp_str = ft_strdup(f_list->cmd[1]);
	return (0);
}

void	change_dir(t_env **envr, t_cmd *f_list)
{
	t_vars	v;

	v.tmp_str = NULL;
	if (!f_list->cmd[1] && !ft_getenv(*envr, "HOME"))
	{
		ft_putstr_fd("Shell: : cd: HOME not set\n", 2);
		return ;
	}
	else if (check_cd_env(envr, f_list, &v))
		return ;
	v.val = getcwd(NULL, 0);
	change_dir_2(envr, &v);
	free(v.tmp_str);
	free(v.val);
}

void	check_cmd(t_env **envr, t_cmd *f_list)
{
	if (f_list && !ft_strcmp(f_list->cmd[0], "cd"))
		change_dir(envr, f_list);
	if (f_list->cmd && f_list->cmd[0] && !ft_strcmp(f_list->cmd[0], "exit"))
		ft_exit(f_list->cmd, f_list);
	else if (lstsize_cmd(f_list) == 1 && f_list->cmd && f_list->cmd[0]
		&& !ft_strcmp(f_list->cmd[0], "env"))
		env_parsing(f_list->cmd, *envr, f_list->fd_out);
	pwd(f_list, *envr);
}
