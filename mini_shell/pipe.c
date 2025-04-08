#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int	check_quotes(char c, int *single, int *double_q)
{
	if (c == '\'' && !*double_q)
		*single = !*single;
	if (c == '"' && !*single)
		*double_q = !*double_q;
	return (*single || *double_q);
}

static size_t	word_len_pipe(char *s, char c)
{
	size_t	len;
	int		single_q;
	int		double_q;

	len = 0;
	single_q = 0;
	double_q = 0;
	while (*s && (*s != c || single_q || double_q))
	{
		check_quotes(*s, &single_q, &double_q);
		len++;
		s++;
	}
	return (len);
}

static size_t	count_words_pipe(char const *s, char c)
{
	int	count;
	int	in_word;
	int	single_q;
	int	double_q;

	count = 0;
	in_word = 0;
	single_q = 0;
	double_q = 0;
	if (!s)
		return (0);
	while (*s)
	{
		check_quotes(*s, &single_q, &double_q);
		if (*s == c && !single_q && !double_q)
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

static char	*ft_strncpy(char *dst, const char *src, size_t len)
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

static void	free2darray(char **array, int n)
{
	while (n--)
		free(array[n]);
	free(array);
}

char	**ft_split_pipe(char *s, char c)
{
	size_t	count;
	size_t	i;
	char	**res;

	i = 0;
	if (!s)
		return (NULL);
	count = count_words_pipe(s, c);
	res = (char **)malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	while (i < count)
	{
		while (*s && *s == c)
			s++;
		res[i] = malloc(sizeof(char) * (word_len_pipe(s, c) + 1));
		if (!res[i])
			return (free2darray(res, i), NULL);
		ft_strncpy(res[i], s, word_len_pipe(s, c));
		res[i++][word_len_pipe(s, c)] = '\0';
		s = s + word_len_pipe(s, c);
	}
	res[i] = NULL;
	return (res);
}
void	free2d(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}
// int main()
// {
// 	char *input = readline("minishell> ");
// 	// char *input = "echo "hello |" | grep hello > file.txt | ls";
// 	char **cmds = ft_split_pipe(input, '|');
// 	int i = 0;

// 	while (cmds[i])
// 	{
// 		printf("Command %d: [%s]\n", i, cmds[i]);
// 		i++;
// 	}
// 	free2d(cmds);
// 	free(input);
// 	return (0);
// }