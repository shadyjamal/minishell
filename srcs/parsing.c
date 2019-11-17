#include "minishell.h"

static size_t	ft_countwords(char const *s, char c)
{
	size_t words;

	words = 0;
	while (*s)
	{
		while (*s == c || *s == '\t')
			s++;
		if (*s)
		{
			words++;
			while (*s && *s != c && *s != '\t')
				s++;
		}
	}
	return (words);
}

static char		*ft_getword(char *word, char c)
{
	char *start;

	start = word;
	while (*word && *word != c && *word != '\t')
		word++;
	*word = '\0';
	return (ft_strdup(start));
}

static void		ft_freewords(char **words, size_t i)
{
	while (i--)
		ft_strdel(&(words[i]));
	free(*words);
}

static char		**ft_getwords(char *s, char c, size_t words_count)
{
	char	**words;
	char	*word;
	size_t	i;

	i = 0;
	if ((words = (char **)ft_memalloc(sizeof(char *) * (words_count + 1))))
	{
		while (i < words_count)
		{
			while (*s == c || *s == '\t')
				s++;
			if (*s)
			{
				if (!(word = ft_getword(s, c)))
				{
					ft_freewords(words, i);
					return (NULL);
				}
				words[i++] = word;
				s += (ft_strlen(word) + 1);
			}
		}
		words[i] = NULL;
	}
	return (words);
}

char			**ft_strparse(char const *s, char c)
{
	char	**words;
	char	*line;

	if (!s || !(line = ft_strdup((char *)s)))
		return (NULL);
	words = ft_getwords(line, c, ft_countwords(line, c));
	free(line);
	return (words);
}