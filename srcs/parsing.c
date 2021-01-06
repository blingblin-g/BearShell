#include "mini.h"

int		is_semi_char(char c)
{
	if (c == ';')
		return (SEMI);
	if (c == 0)
		return (END);
	return (0);
}

int		is_pipe_char(char c)
{
	if (c == '|')
		return (PIPE);
	return (0);
}

int		is_redirection_char(char c)
{
	if (c == '>')
		return (OUTPUT);
	if (c == '<')
		return (INPUT);
	if (c == ' ')
		return (SPACE);
	return (0);
}

void	init_pars(t_parse *pars)
{
	pars->single_q = FALSE;
	pars->double_q = FALSE;
	pars->pro_lst = NULL;
	pars->line = NULL;
	pars->is_space = FALSE;
	pars->start = 0;
}

int		search_quotes(char c, char *line, int i) // return index of pair_quotes
{
	while (line[i])
	{
		if (line[i] == c)
			return (i);
		i++;
	}
	return (ERROR); // 다 돌았지만 못찾은거임. 즉 pair quote가 없는 것
}

t_list	*new_lst_trim(char *content)
{
	t_list	*tmp_lst;
	
	content = free_strtrim(&content, " ");
	tmp_lst = ft_lstnew(content);
	return (tmp_lst);
}

void	add_redirection_lst(t_parse *pars, t_list **lst, int type)
{
	char	*str;

	str = NULL;
	if (type == INPUT || type == OUTPUT || type == APPEND)
		pars->fd_count++;
	if (type == INPUT)
		str = ft_strdup("<");
	else if (type == OUTPUT)
		str = ft_strdup(">");
	else if (type == APPEND)
		str = ft_strdup(">>");
	if (str)
		ft_lstadd_back(lst, ft_lstnew(str));
}

int		input_pipe_lst(t_parse *pars, char *raw, t_list **raw_lst)
{
	t_list	*tmp_lst;
	size_t	i;
	int		type;

	i = 0;
	pars->start = i;
	type = 0;
	while (raw[i])
	{
		if (!pars->single_q && !pars->double_q)
		{
			if (i == 0 || (i != 0 && raw[i - 1] != '\\'))
			{
				if ((type = is_pipe_char(raw[i])))
				{
					if (i != pars->start)
					{
						tmp_lst = new_lst_trim(ft_substr(raw, pars->start, i - pars->start));
						if (type == OUTPUT && raw[i] && raw[i + 1] == '>')
							i++;
						ft_lstadd_back(raw_lst, tmp_lst);
					}
					pars->start = i + 1;
				}
				if (raw[i] == '\"')
					pars->double_q = TRUE;
				else if (raw[i] == '\'')
					pars->single_q = TRUE;
			}
		}
		else
		{
			if (i != 0 && pars->single_q && raw[i - 1] != '\\' && raw[i] == '\'')
				pars->single_q = FALSE;
			else if (i != 0 && pars->double_q && raw[i - 1] != '\\' && raw[i] == '\"')
				pars->double_q = FALSE;
		}
		i++;
	}
	tmp_lst = new_lst_trim(ft_substr(raw, pars->start, i - pars->start));
	ft_lstadd_back(raw_lst, tmp_lst);
	if (pars->single_q || pars->double_q)
		return (ERROR);
	return (SUCCESS);
}

int		input_redirection_lst(t_parse *pars, char *raw, t_list **raw_lst)
{
	t_list	*tmp_lst;
	size_t	i;
	int		type;

	i = 0;
	pars->start = i;
	type = 0;
	while (raw[i])
	{ 
		if (!pars->single_q && !pars->double_q)
		{
			if (i == 0 || (i != 0 && raw[i - 1] != '\\'))
			{
				if ((type = is_redirection_char(raw[i])))
				{
					if (i != pars->start)
					{
						tmp_lst = new_lst_trim(ft_substr(raw, pars->start, i - pars->start));
						ft_lstadd_back(raw_lst, tmp_lst);
					}
					if (type == OUTPUT && raw[i + 1] && raw[i + 1] == '>')
					{
						i++;
						type = APPEND;
					}
					add_redirection_lst(pars, raw_lst, type);
					pars->start = i + 1;
				}
				if (raw[i] == '\"')
					pars->double_q = TRUE;
				else if (raw[i] == '\'')
					pars->single_q = TRUE;
			}
		}
		else
		{
			if (i != 0 && pars->single_q && raw[i - 1] != '\\' && raw[i] == '\'')
				pars->single_q = FALSE;
			else if (i != 0 && pars->double_q && raw[i - 1] != '\\' && raw[i] == '\"')
				pars->double_q = FALSE;
		}
		i++;
	}
	tmp_lst = new_lst_trim(ft_substr(raw, pars->start, i - pars->start));
	ft_lstadd_back(raw_lst, tmp_lst);
	if (pars->single_q || pars->double_q)
		return (ERROR);
	return (SUCCESS);
}

int		main_parse(char *line, t_parse *pars)
{
	int		type;
	int		i;
	t_pro	*pro_lst;

	i = 0;
	pars->start = 0;
	type = 0;
	while (line[i])
	{
		if (!pars->single_q && !pars->double_q)
		{
			if (i == 0 || (i != 0 && line[i - 1] != '\\'))
			{
				if ((type = is_semi_char(line[i])))
				{
					pro_lst = new_prolst(ft_substr(line, pars->start, i - pars->start), type);
					add_back_prolst(&pars->pro_lst, pro_lst);
					pars->start = i + 1;
				}
				if (line[i] == '\"')
					pars->double_q = TRUE;
				else if (line[i] == '\'')
					pars->single_q = TRUE;
			}
		}
		else
		{
			if (i != 0 && pars->single_q && line[i - 1] != '\\' && line[i] == '\'')
				pars->single_q = FALSE;
			else if (i != 0 && pars->double_q && line[i - 1] != '\\' && line[i] == '\"')
				pars->double_q = FALSE;
		}
		i++;
	}
	pro_lst = new_prolst(ft_substr(line, pars->start, i - pars->start), type);
	add_back_prolst(&pars->pro_lst, pro_lst);
	pro_lst = pars->pro_lst;

	while (pro_lst)
	{
		pro_lst->raw = free_strtrim(&pro_lst->raw, " ");
		input_pipe_lst(pars, pro_lst->raw, &pro_lst->pipe_lst);
		pro_lst = pro_lst->next;
	}
	pro_lst = pars->pro_lst;

	return (0);
}

int		 init_exec(t_exec	*exec_info, int lst_count)
{
	int		fd_count;


	fd_count = exec_info->input_count + exec_info->output_count;
	printf("exec_info->input_count: [%d], exec_info->output_count: [%d]\n", exec_info->input_count, exec_info->output_count);
	if (exec_info->input_count > 0)
		if (!(exec_info->fd[0] = (int *)malloc(sizeof(int) * (exec_info->input_count))))
			return (ERROR);
	if (exec_info->output_count > 0)
		if (!(exec_info->fd[1] = (int *)malloc(sizeof(int) * (exec_info->output_count))))
			return (ERROR);
	if (exec_info->input_count <= 0)
		exec_info->fd[0] = NULL;
	if (exec_info->output_count <= 0)
		exec_info->fd[1] = NULL;
	if (!(exec_info->argv = (char **)calloc(sizeof(char *),
		(lst_count - fd_count + 1))))
		return (ERROR);
	// exec_info->argv[lst_count - fd_count * 2] = 0;
	exec_info->fd_input_idx = 0;
	exec_info->fd_output_idx = 0;
	exec_info->argv_idx = 0;
	return (SUCCESS);
}

void	get_fd_count(t_list	*redir_lst, t_exec *exec_info)
{
	exec_info->input_count = 0;
	exec_info->output_count = 0;
	while (redir_lst)
	{
		if (redir_lst->content)
		{
			if (((char *)redir_lst->content)[0] == '>')
				exec_info->output_count++;
			if (((char *)redir_lst->content)[0] == '<')
				exec_info->input_count++;
		}
		redir_lst = redir_lst->next;
	}
}

void	create_fds(t_exec *exec_info, char *redir_str, char *file_str)
{
	int	fd;

	fd = 0;
	if (!ft_strcmp(redir_str, ">"))
	{
		// printf("output fd: [%d], file_str: [%s]\n", fd, file_str);
		fd = open(file_str, O_RDWR | O_TRUNC | O_CREAT, 00777);
		exec_info->fd[1][exec_info->fd_output_idx++] = fd;
	}
	else if (!ft_strcmp(redir_str, ">>"))
	{
		// printf("append fd: [%d], file_str: [%s]\n", fd, file_str);
		fd = open(file_str, O_RDWR | O_APPEND | O_CREAT, 00777);
		exec_info->fd[1][exec_info->fd_output_idx++] = fd;
	}
	else if (!ft_strcmp(redir_str, "<"))
	{
		// printf("input fd: [%d], file_str: [%s]\n", fd, file_str);
		fd = open(file_str, O_RDONLY, 00777);
		exec_info->fd[0][exec_info->fd_input_idx++] = fd;
	}
}

t_exec	*create_exec(t_parse *pars, t_list *redir_lst)
{
	t_exec	*exec_info;
	char	*res;
	int		lst_count;

	if (!(exec_info = (t_exec *)malloc(sizeof(t_exec))))
		return (NULL);
	lst_count = ft_lstsize(redir_lst);
	get_fd_count(redir_lst, exec_info);
	init_exec(exec_info, lst_count);
	while (redir_lst)
	{
		res = process_quotes(pars, redir_lst->content);
		printf("after_parsing == [%s],[%p]\n", res, res);
		if (res && (res[0] == '>' || res[0] == '<'))
		{
			if (redir_lst->next)
				create_fds(exec_info, res, process_quotes(pars, redir_lst->next->content));
			redir_lst = redir_lst->next;
		}
		else if (ft_strcmp(res, ""))
		{
			exec_info->argv[exec_info->argv_idx] = res;
			exec_info->argv_idx++;
		}
		if (redir_lst)
			redir_lst = redir_lst->next;
	}
	return (exec_info);
}

void	free_exec_info(t_exec **exec_info)
{
	int		i;

	i = 0;
	free((*exec_info)->fd[0]);
	free((*exec_info)->fd[1]);
	free((*exec_info)->fd);
	while ((*exec_info)->argv[i])
	{
		free((*exec_info)->argv[i]);
		i++;
	}
	free((*exec_info)->argv);
}
