#include <unistd.h>
#include <stdarg.h>

void	get_str(char *s, int *len)
{
	if (!s)
		s = "(null)";
	while (*s)
		*len += write(1, s++, 1);
}

void	get_digit(long nbr, int base, int *len)
{
	char	*hex = "0123456789abcdef";

	if (nbr < 0)
	{
		nbr = -nbr;
		*len += write(1, "-", 1);
	}
	if (nbr >= base)
		get_digit(nbr / base, base, len);
	*len += write(1, &hex[nbr % base], 1);
}

int ft_printf(const char *param, ... )
{
	int	len = 0;
	va_list	args;

	va_start(args, param);
	while (*param)
	{
		if (*param == '%' && (*(param + 1) == 's' || *(param + 1) == 'd' || *(param + 1) == 'x'))
		{
			param++;
			if (*param == 's')
				get_str(va_arg(args, char *), &len);
			else if (*param == 'd')
				get_digit((long)va_arg(args, int), 10, &len);
			else if (*param == 'x')
				get_digit((long)va_arg(args, unsigned int), 16, &len);
		}
		else
			len += write(1, param, 1);
		param++;
	}
	va_end(args);
	return (len);
}

int	main()
{
	ft_printf("%s %d %x\n", "Hello World", 42, 42);
	return (0);
}