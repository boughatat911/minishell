#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

static	size_t	word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s++ != c)
		len++;
	return (len);
}

static	size_t	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static	char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

static	void	free2d(char **array, int n)
{
	while (n--)
		free(array[n]);
	free(array);
}

char	**ft_split(char const *s, char c)
{
	size_t		count;
	size_t		i;
	char		**res;

	i = 0;
	if (!s)
		return (NULL);
	count = count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	while (i < count)
	{
		while (*s && *s == c)
			s++;
		res[i] = malloc(sizeof (char) * (word_len(s, c) + 1));
		if (!res[i])
			return (free2d(res, i), NULL);
		ft_strncpy(res[i], s, word_len(s, c));
		res[i++][word_len(s, c)] = '\0';
		s = s + word_len(s, c);
	}
	res[i] = NULL;
	return (res);
}


char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}
typedef struct s_token
{
    char *content;
    struct s_token *next;
} t_token;

t_token *ft_lstnew(char *content)
{
    t_token *node = malloc(sizeof(t_token));
    if (!node)
		return (NULL);
    node->content = content;
    node->next = NULL;
    return (node);
}

void ft_lstadd_back(t_token **lst, t_token *new)
{
    if (!*lst)
        *lst = new;
    else
    {
        t_token *tmp = *lst;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

char	*ft_substr(const char *s, int start, int len)
{
    char *substr = malloc(len + 1);
    if (!substr)
		return (NULL);
    ft_strncpy(substr, s + start, len);
    substr[len] = '\0';
    return (substr);
}
	// echo '"hello swor<''ld"' | grep hello > file.txt;

int main()
{
    t_token *token_list;
	int start = 0;
	token_list = NULL;
	char *substr;
	t_token *tmp;
	char **spl;
    char *input = readline("Minishell >> ");
    int i = 0;
	int pipe = 0;

    while (input[i] == ' ') // skip space
		i++;
	if (input[i] == '|') // check | is first this is syntax error
	{
		printf("syntax error pipe\n");
		exit (1);
	}
	//
	spl = ft_split(input, '|');
	while (spl[i])
	{
		ft_lstadd_back(token_list, spl[i]);
		i++;
	}
	i = 0;
    while (input[i])
    {
        if (input[i] == '"' || input == '\'')
        {
			char c = input[i];
            start = ++i;
            while (input[i] && input[i] != c)
                i++;
            if (input[i] == c)
            {
                substr = ft_substr(input, start, i - start);
                ft_lstadd_back(&token_list, ft_lstnew(substr));
				free(substr);
                i++;
            }
        }
        else if (input[i] == '\'')
        {
            start = ++i;
            while (input[i] && input[i] != '\'')
                i++;
            if (input[i] == '\'')
            {
                substr = ft_substr(input, start, i - start);
                ft_lstadd_back(&token_list, ft_lstnew(substr));
				free(substr);
				// printf(">>>%s\n", substr);
                i++;
            }
        }
        // else
        // {
        //     start = i;
        //     while (input[i] && input[i] != ' ' && input[i] != '"' && input[i] != '\'')
        //         i++;
        //     char *word = ft_substr(input, start, i - start);
        //     ft_lstadd_back(&token_list, ft_lstnew(word));
        // }
    }
    tmp = token_list;
    while (tmp)
    {
        printf("Token: [%s]\n", tmp->content);
        tmp = tmp->next;
    }
    return (0);
}


// t_token *new_token(char *content, t_token_type type)
// {
//     t_token *tok = malloc(sizeof(t_token));
//     tok->content = content;
//     tok->type = HERDOC;
//     tok->next = NULL;
//     return tok;
// }

// void add_token(t_token **lst, char *content, t_token_type type)
// {
//     t_token *tok = new_token(content, type);
//     if (!*lst)
//         *lst = tok;
//     else {
//         t_token *tmp = *lst;
//         while (tmp->next)
//             tmp = tmp->next;
//         tmp->next = tok;
//     }
// }
