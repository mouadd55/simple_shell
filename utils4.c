#include "simpleshell.h"

/**
 * f_strrchr - Locate the last occurrence of a character in a string.
 * @str: The string to search within.
 * @c: The character to find.
 * Return: The index of the last occurrence of the character in the string,
 *         or 0 if the character is not found.
 */
char	*f_strrchr(const char *s, int c)
{
	int		len;
	char	*str;

	str = (char *)s;
	len = ft_strlen(str);
	while (len >= 0)
	{
		if (str[len] == (char)c)
			return (str + len);
		len--;
	}
	return (0);
}

/**
 * f_strchr - Locate the first occurrence of a character in a string.
 * @str: The string to search within.
 * @find: The character to find.
 * Return: The index of the first occurrence of the character in the string,
 *         or 0 if the character is not found.
 */
char	*f_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	if (c == '\0')
		return (str + i);
	return (0);
}

/**
 * ft_strtrim - Remove leading and trailing specified characters from a string.
 * @s1: The original string.
 * @set: The set of characters to be trimmed.
 * Return: A newly allocated string with leading and trailing specified
 *         characters removed, or NULL on failure.
 */
char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		j;
	int		end;
	char	*str;

	j = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (f_strchr(set, s1[i]) && s1[i])
		i++;
	while (f_strrchr(set, s1[end - 1]) && end > i)
		end--;
	str = malloc((end - i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < end)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

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
 * ft_itoa - Convert an integer to a string.
 * @n: The integer to be converted.
 * Return: A newly allocated string representation of the integer, or NULL on failure.
 */
char	*ft_itoa(long long n)
{
	int			len;
	char		*str;
	long long	nb;

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
