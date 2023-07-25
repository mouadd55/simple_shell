#include "simpleshell.h"

int	is_alpha_num(char c)
{
	if (ft_isalpha(c) || check_char("0123456789", c))
		return (1);
	return (0);
}

int	is_space(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void	index_list(t_list **list)
{
	t_list	*tmp;
	int		count;

	tmp = *list;
	count = 0;
	while (tmp)
	{
		tmp->pos = count;
		count++;
		tmp = tmp->link;
	}
}

char	*strlower(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(str);
	while (tmp[i])
	{
		if (tmp[i] >= 'A' && tmp[i] <= 'Z')
			tmp[i] += 32;
		i++;
	}
	return (tmp);
}

void	split_string(t_vars *v, t_cmd *final_list, t_env **envr, int size)
{
	v->tmp1 = ft_split_input(v->str);
	lexer(&v->tmp1);
	if (size == 1)
		check_cmd(envr, final_list);
	ft_destroy_list(&v->tmp1);
	free(v->str);
	v->str = NULL;
}
