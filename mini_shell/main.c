
// #include "minishell.h"
#include "../LIBFT/libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_token {
    char *content;
    struct s_token *next;
} t_token;
// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*node;

// 	node = malloc(sizeof(t_list));
// 	if (!node)
// 		return (NULL);
// 	node->content = content;
// 	node->next = NULL;
// 	return (node);
// }
// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*final;

// 	if (!new || !lst)
// 		return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	final = ft_lstlast(*lst);
// 	final->next = new;
// 	return ;
// }
char	*ft_ssubstr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = strlen(s);
	if (start > s_len)
		return (strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (i < len && s[start])
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}

	// echo '"hello swor<''ld"' | grep hello > file.txt;
// int main()
// {
// 	t_token *token_list;
// 	token_list = NULL;
// 	int i = 0;
// 	int j = 0;
// 	int pipe = 0;
// 	int start = 0;
// 	int end = 0;
// 	char *input;
// 	// Double
//     // int  in = 0;
// 	// int dbl = 0;
//     // int  out = 0;
//     // while (1)
// 	// {
// 		input = readline("Minishell >> ");
// 		// char *copy = ft_strdup(input);
// 		while (input[i] == ' ')
// 			i++;
// 		// if (input[i] == '|')
// 		// {
// 		// 	printf("error pipe\n");
// 		// 	exit(1);
// 		// }
// 		// char **pipe_split = ft_split(input, '|');
// 		while (input[i])
// 		{
			
// 			if (input[i] == '"')
// 			{
// 				start = i;
// 				while (input[i] =! '"')
// 					i++;
// 				if (input[i] == '"')
// 				{
// 					end = i ;
// 					token_list = ft_lstnew(ft_substr(input, start, end));
// 				}
// 			}
// 			else if (input[i] == '\'')
// 			{
// 				start = i;
// 				while (input[i] =! '\'')
// 					i++;
// 				if (input[i] == '\'')
// 				{
// 					end = i ;
// 					ft_lstadd_back(token_list, ft_lstnew(ft_substr(input, start, end - start)));
// 				}
// 			}
// 			i++;
// 		}
// 		t_token *tmp = token_list;

// 		while (tmp)
// 		{
// 			printf("%s\n", tmp->content);
// 			tmp = tmp->next;
// 		}
		
// 	}
// }


// --------------------------------------------------
			// if (input[i] == '|')
			// {
			// 	pipe++;
			// }
			// else if (input[i] == '>')
			// {

			// }
			// else if (input[i] == '"' || input[i] == '\'')
			// {

			// 	// read until closing quote
			// }
			// else
			// {

			// 	// build word token
			// }