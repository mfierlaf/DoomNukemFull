double		ft_atof(const char *str)
{
	int	i;
	char	is_floating_part;
	double	value;
	double	iter_floating_part;
	double	sign;

	is_floating_part = 0;
	i = -1;
	value = 0.0;
	iter_floating_part = 10.0;
	sign = 1.0;
	if (str[0] == '-')
	{
		sign = -1.0;
		i++;
	}
	if (!ft_isdigit(str[i + 1]))
		return (0.0);
	while (str[++i])
	{
		if (ft_isdigit(str[i]))
		{
			if (!is_floating_part)
			{
				if (value)
					value *= 10.0;
				value += (double)(str[i] - '0');
			}
			else
			{
				value += ((double)(str[i] - '0') / iter_floating_part);
				iter_floating_part *= 10.0;
			}
		}
		else if (str[i] == '.')
		{
			is_floating_part = 1;
		}
	}
	return (value * sign);
}
