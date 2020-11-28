#include "mini.h"

int		main(void)
{
	char *line = (char *)malloc(sizeof(char) * 50);
	ft_memset(line, 0, 50);
	char *text = "e'ch'o 'jinw'a'sooyoon' 'rockpell'";
	// char *content = (char *)malloc(sizeof(char) * 30);
	int size = (int)ft_strlen(text);
	for(int p = 0; p < size; p++)
		line[p] = text[p];
	line[size] = 0;
	main_parse(line);
	return (0);
}