#include <unistd.h>
#include <stdarg.h>

void	put_string(char *string, int *length)
{
	if (!string)
		string = "(null)";
	while (*string)
		*length += write(1, string++, 1);
}

void	put_digit(long number, int base, int *length)
{
	char	*hex = "0123456789abcdef";

	if (number < 0)
	{
		number *= -1;
		*length += write(1, "-", 1);
	}
	if (number >= base)
		put_digit((number / base), base, length);
	*length += write(1, &hex[number % base], 1);
}

int	ft_printf(const char *param, ... )
{
	int length = 0;
	va_list	args;

	va_start(args, param);
	while (*param)
	{
		if ((*param == '%') && ((*(param + 1) == 's') || (*(param + 1) == 'd') || (*(param + 1) == 'x')))
		{
			param++;
			if (*param == 's')
				put_string(va_arg(args, char *), &length);
			else if (*param == 'd')
				put_digit((long)va_arg(args, int), 10, &length);
			else if (*param == 'x')
				put_digit((long)va_arg(args, unsigned int), 16, &length);
		}
		else
			length += write(1, param, 1);
		param++;
	}
	va_end(args);
	return (length);
}
/*
int	main(void)
{
	ft_printf("%s %d %x\n", "Hello", 42, 42);
	return (0);
}
*/