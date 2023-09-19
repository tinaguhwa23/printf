#include "main.h"

void flush_buffer(char buf[], int *index);

/**
 * _printf - Custom printf function.
 * @format: Format string.
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
	int j, buf_idx = 0, total_chars = 0;
	va_list args;
	char buf[1024];

	if (!format)
		return (-1);

	va_start(args, format);

	for (j = 0; format[j]; j++)
	{
		if (format[j] != '%')
		{
			buf[buf_idx++] = format[j];
			total_chars++;
		}
		else
		{
			switch (format[++j])
			{
				case 'c':
					buf[buf_idx++] = (char) va_arg(args, int);
					total_chars++;
					break;
				case 's':
				{
					char *str = va_arg(args, char *);

					while (*str)
					{
						buf[buf_idx++] = *str++;
						total_chars++;
					}
					break;
				}
				case '%':
					buf[buf_idx++] = '%';
					total_chars++;
					break;
				default:

					j--;
					break;
			}
		}

		if (buf_idx >= (int)sizeof(buf) - 1)
			flush_buffer(buf, &buf_idx);
	}

	flush_buffer(buf, &buf_idx);
	va_end(args);

	return (total_chars);
}

/**
 * flush_buffer - Buffer contents to standard output and reset buffer.
 * @buf: Buffer that contains characters.
 * @index: The current index in buffer.
 */
void flush_buffer(char buf[], int *index)
{
	if (*index > 0)
	{
		write(1, buf, *index);
		 *index = 0;
	}
}
