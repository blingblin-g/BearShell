#include "mini.h"

int		main(void)
{
    // char	*inputs1[30] = {"echo123123", "test write"};
	// char	*inputs2[30] = {"echo11111111111", "-n", "test write"};

    // echo(inputs1);
	// printf("\n======================\n");
	// echo(inputs2);

	// char	buf[2097152];
	// char	*result;

	// result = getcwd(buf, 2097152);
	// printf("%s   : result=>[%s]\n", buf, result);

	// ft_lstiter(list, print_str);

	// get_info()->env_list = create_env_list();
	// char *str = ft_strdup("HOME=/Users/sooyoon");
	// char *str2 = ft_strdup("chlim=sooyoon");
	// // export(str);
	// export(str2);
	// env();
	// printf("\n======================\n");
	// unset(str);
	// ft_lstiter(get_info()->env_list, print_str);
	// free(str);
	// free(str2);
	// export(NULL);
	// t_parse tmp_parse;
	// int	i = 1;
	char *line = (char *)malloc(sizeof(char) * 50);
	ft_memset(line, 0, 50);
	char *text = "e'ch'o 'jinw'a'sooyoon' 'rockpell'";
	// char *content = (char *)malloc(sizeof(char) * 30);
	int size = (int)ft_strlen(text);

	for(int p = 0; p < size; p++)
		line[p] = text[p];
	line[size] = 0;
	// i=8;
	// tmp_parse.line = line;
	// 컨텐트에 라인을 넣은거에요?
	// 리스트 안에 있는 컨텐트의 주소
	// is_single_quote_zone(&tmp_parse, &i, &content);
	main_parse(line);
    return (0);
}
