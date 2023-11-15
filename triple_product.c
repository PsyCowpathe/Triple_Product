#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int		ft_strlen(char	*str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		parse_suit(char *list, float **suit, int to_find)
{
	int		i;
	int		d;
	char	*tmp;
	int		count;

	i = 0;
	d = 0;
	count = 0;
	if ((tmp = malloc(sizeof(char) * ft_strlen(list))) == NULL)
		return (-1);
	if ((*suit = malloc(sizeof(float) * (ft_strlen(list) / 2) + 1)) == NULL)
		return (-1);
	while (list[i] != '\0')
	{
		d = 0;
		if (list[i] < '0' || list[i] > '9')
			return (-2);
		while (list[i] != '\0' && list[i] != ' ')
		{
			tmp[d] = list[i];
			tmp[d + 1] = '\0';
			d++;
			i++;
		}
		if (tmp[0] && atof(tmp) <= to_find)
			(*suit)[count++] = atof(tmp);
		while (list[i] && list[i] == ' ')
			i++;
	}
	return (count);
}

float	parse_to_find(char *nb)
{
	int		i;
	int		d;
	char	*tmp;

	i = 0;
	d = 0;
	if ((tmp = malloc(sizeof(char) * ft_strlen(nb))) == NULL)
		return (-1);
	while (nb[i] != '\0')
	{
		d = 0;
		if (nb[i] < '0' || nb[i] > '9')
			return (-1);
		while (nb[i] != '\0' && nb[i] != ' ')
		{
			tmp[d] = nb[i];
			d++;
			i++;
		}
		if (tmp[0])
			return (atof(tmp));
		i++;
	}
	return (-1);
}

void	search_product(float *suit, float to_find, int count)
{
	int		i = 0;
	int		d = 0;
	int		j = 0;

	while (i < count)
	{
		d = 0;
		if (fmod((to_find / suit[i]), 1) == 0)
		{
			while (d < count)
			{
				j = 0;
				if (fmod((to_find / suit[i]) / suit[d], 1) == 0)
				{
					while (j < count)
					{
						if (i != j && i != d && d != j && to_find / suit[i] / suit[d] == suit[j])
						{
							printf("%f * %f * %f\n", suit[i], suit[d], suit[j]);
						}
						j++;
					}
				}
				d++;
			}
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	float	*suit;
	float	to_find;
	int		count;

	if (argc != 3)
	{
		dprintf(2, "Bad args, usage : ./find_product <suit> <to_find>\n");
		return (1);
	}
	if ((to_find = parse_to_find(argv[2])) == -1)
	{
		dprintf(2, "Error : Invalid to_find\n");
		return (1);
	}
	if ((count = parse_suit(argv[1], &suit, to_find)) == -1)
	{
		dprintf(2, "Error : Malloc\n");
		return (1);
	}
	if (count == -2)
	{
		dprintf(2, "Error : Invalid number\n");
		return (1);
	}
	search_product(suit, to_find, count);
	return (0);
}