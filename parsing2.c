#include "simpleshell.h"

void	syntax_error(char *s2, char e)
{
	ft_putstr_fd("Shell: : syntax error near unexpected token ", 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	if (e)
		ft_putchar(e, 2);
	ft_putchar('\n', 2);
	return ;
}

int	search_for_pipe(t_vars *v)
{
	while (v->tmp1)
	{
		if (!ft_strcmp(v->tmp1->type, "PIPE"))
			return (1);
		v->tmp1 = v->tmp1->link;
	}
	return (0);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (!str[++i])
			return (0);
	while (str[i])
		if (!(str[i] >= '0' && str[i++] <= '9'))
			return (0);
	return (1);
}

