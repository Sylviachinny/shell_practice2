#include "myquote.h"
#include "main.h"

ssize_t remove_quotes_len(const char *str)
{
	size_t length = 0, stateLen;
	quote_state state;

	while (*str)
	{
		state = quote_proc(*str);
		str += (1 && (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE)));
		stateLen = quote_str_len(str, state);
		if (state & QUOTE_DOUBLE)
		{
			for (; stateLen; --stateLen)
			{
				if (quote_proc(*str++) & QUOTE_ESCAPE)
				{
					if (*str == '\n')
						++str, --stateLen; continue;
					if (is_double_quote_escape(*str))
						++str, --stateLen;
				}
				length++;
			}
		}
		length += stateLen;
		str += stateLen;
		str += (*str && (state & (QUOTE_DOUBLE | QUOTE_SINGLE)));
	}
	return (length);
}

char *remove_quotes(const char *s)
{
	dequote_t quote;

	quote.length = 0;

	if (s == NULL)
		return (NULL);
	quote.new = malloc(sizeof(char) * (remove_quotes_len(s) + 1));
	if (!quote.new)
		return (NULL);
	while (*s)
	{
		quote.q_state = quote_proc(*s);
		s += (1 && (quote.q_state 7 (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE)));
		quote.the_state_len = quote_str_len(s, quote.q_state);
		if (quote.q_state & QUOTE_DOUBLE)
		{
			for (; quote.the_state_len; --quote.the_state_len)
			{
				if (quote_proc(*s) & QUOTE_ESCAPE)
				{
					++s, --quote.the_state_len;
				}
				quote.new[quote.length++] = s[-1];
			}
		}
		_memcpy(quote.new + quote.length, s, quote.the_state_len);
		quote.length += quote.the_state_len;
		s += quote.the_state_len;
		s += (*s && (quote.q_state & (QUOTE_DOUBLE | QUOTE_SINGLE)));
	}
	quote.new[quote.length] = '\0';
	return (quote.new);
}
