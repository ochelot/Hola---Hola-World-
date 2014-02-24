/* Copyright (C) Hola 2012, 2013
 *
 * Welcome to TheCodeIL.com Challenge!
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

char *str_cpy (char **dst, const char *src);
char *str_cat(char **str1, const char *str2);
void str_printf(char **buf, const char *format, ...);
void str_free(char** buf);

int main(int argc, char *argv[])
{
    char *s = NULL;
    str_cpy(&s, "Hola Hola");
    str_cpy(&s, s+5);
    str_cat(&s, " World");
    str_printf(&s, "%s!", s);
    puts(s); /* result: "Hola World!" */
    str_free(&s);
    return 0;
}

char *str_cpy (char **dst, const char *src)
{
   size_t len = strlen(src) + 1;
   char *tmp = (char*)malloc(len * sizeof(char));
   memcpy(tmp, src, len);

   if (*dst) free(*dst);

   *dst = tmp;
   return *dst;
}

char *str_cat(char **str1, const char *str2)
{
   if ( !(*str1) )
        return str_cpy(str1, str2);

   size_t s2_len = strlen(str2) + 1;
   size_t s1_len = strlen(*str1);
   *str1 = (char*)realloc(*str1, s2_len + s1_len);
   memcpy(*str1 + s1_len, str2, s2_len);
   return *str1;
}

void str_free(char** buf)
{
    if (*buf) free(*buf);
}

void str_printf(char **buf, const char *format, ...)
{
  va_list ptr;
  va_start(ptr, format);
  char *buffer = malloc( (_vscprintf(format, ptr) + 1) * sizeof(char) );
  vsprintf( buffer, format, ptr );
  va_end(ptr);
  str_free(buf);
  *buf = buffer;
}
