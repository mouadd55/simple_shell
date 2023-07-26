#include <unistd.h>
#include <stdarg.h>

/**
 * printc - Write a character to a file descriptor.
 * @c: The character to be written.
 * @fd: The file descriptor where the character will be written.
 * Return: 1 on successful write, or -1 on error.
 */
int	printc(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

/*
 * prints - Write a null-terminated string to a file descriptor.
 * @s: The string to be written.
 * @fd: The file descriptor where the string will be written.
 * Return: The number of characters written on successful write, or -1 on error.
 */
int	prints(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			printc(s[i++], fd);
	}
	return (i);
}

/**
 * ft_specifier - Handle formatting and printing of specific specifiers.
 * @args: The va_list containing the arguments.
 * @specifier: The format specifier character.
 * @fd: The file descriptor where the output will be written.
 * Return: The total number of characters printed for the specifier.
 */
int	ft_specifier(va_list args, char specifier, int fd)
{
	int	printed;

	printed = 0;
	if (specifier == 'c')
		printed += printc(va_arg(args, int), fd);
	else if (specifier == 's')
		printed += prints(va_arg(args, char *), fd);
	else if (specifier == '%')
		printed += printc('%', fd);
	return (printed);
}

/**
 * ft_printf - Custom implementation of printf that writes formatted output to a file descriptor.
 * @first: The format string containing the text and format specifiers.
 * @fd: The file descriptor where the output will be written.
 * @...: Variable arguments corresponding to the format specifiers in the format string.
 * Return: The total number of characters printed to the file descriptor, or -1 on error.
 */
int	ft_printf(const char *first, int fd, ...)
{
	int		i;
	int		out;
	va_list	args;

	i = 0;
	out = 0;
	va_start(args, fd);
	while (first[i])
	{
		if (first[i] == '%')
		{
			out += ft_specifier(args, first[i + 1], fd);
			i++;
		}
		else
			out += write(fd, &first[i], 1);
		i++;
	}
	va_end(args);
	return (out);
}
