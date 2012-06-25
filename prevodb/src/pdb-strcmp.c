#include "config.h"

#include <glib.h>

#include "pdb-strcmp.h"

static guint32
pdb_strcmp_get_value (const char *p)
{
  gunichar ch = g_unichar_tolower (g_utf8_get_char (p));

  switch (ch)
    {
    case 0x109:
      return 'c' * 2U + 1;
    case 0x11d:
      return 'g' * 2U + 1;
    case 0x125:
      return 'h' * 2U + 1;
    case 0x135:
      return 'j' * 2U + 1;
    case 0x15d:
      return 's' * 2U + 1;
    case 0x16d:
      return 'u' * 2U + 1;
    default:
      return ch * 2U;
    }
}

/* Compares two strings using Esperanto orthography */
int
pdb_strcmp (const char *a,
            const char *b)
{
  while (TRUE)
    {
      guint32 av = pdb_strcmp_get_value (a);
      guint32 bv = pdb_strcmp_get_value (b);

      if (av < bv)
        return -1;
      else if (av > bv)
        return 1;
      else if (av == '\0')
        return 0;
      else
        {
          a = g_utf8_next_char (a);
          b = g_utf8_next_char (b);
        }
    }
}