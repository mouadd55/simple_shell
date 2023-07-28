#include "simpleshell.h"

/**
 * nbr_len - Calculate the number of digits in an integer.
 * @nbr: The input number.
 * Return: The number of digits in the integer.
 */
int	nbr_len(long nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len++;
	while (nbr != 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

/**
 * _itoa - Convert an integer to a string.
 * @n: The integer to be converted.
 * Return: A newly allocated string representation
 * of the integer, or NULL on failure.
 */
char	*_itoa(long n)
{
	int			len;
	char		*str;
	long	nb;

	nb = n;
	len = nbr_len(nb);
	str = malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb *= (-1);
	}
	if (nb == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (nb != 0)
	{
		str[len--] = nb % 10 + 48;
		nb /= 10;
	}
	return (str);
}

/**
 * _atoi - Convert a string to a long integer.
 * @str: The input string to convert.
 * Return: The converted long integer.
 */
long	_atoi(const char *str)
{
	long	i;
	long	sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	return (res * sign);
}

/**
 * _strjoin - Concatenate two null-terminated strings.
 * @s1: The first string.
 * @s2: The second string.
 * Return: A newly allocated pointer to the concatenated
 *string, or NULL on failure.
 */
char	*_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		s1 = _strdup("");
	if (!s2)
		return (NULL);
	str = malloc((_strlen(s1) + _strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
