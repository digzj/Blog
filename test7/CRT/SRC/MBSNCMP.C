/***
*mbsncmp.c - Compare n characters of two MBCS strings
*
*       Copyright (c) 1985-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Compare n characters of two MBCS strings
*
*******************************************************************************/

#ifdef _MBCS

#include <mtdll.h>
#include <cruntime.h>
#include <mbdata.h>
#include <mbctype.h>
#include <string.h>
#include <mbstring.h>

/***
*int mbsncmp(s1, s2, n) - Compare n characters of two MBCS strings
*
*Purpose:
*       Compares up to n charcters of two strings for lexical order.
*       Strings are compared on a character basis, not a byte basis.
*
*Entry:
*       unsigned char *s1, *s2 = strings to compare
*       size_t n = maximum number of characters to compare
*
*Exit:
*       returns <0 if s1 < s2
*       returns  0 if s1 == s2
*       returns >0 if s1 > s2
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _mbsncmp(
        const unsigned char *s1,
        const unsigned char *s2,
        size_t n
        )
{
        unsigned short c1, c2;

        if (n==0)
            return(0);

        if ( _ISNOTMBCP )
            return strncmp(s1, s2, n);

        _mlock(_MB_CP_LOCK);

        while (n--) {

            c1 = *s1++;
            if (_ISLEADBYTE(c1))
                c1 = ( (*s1 == '\0') ? 0 : ((c1<<8) | *s1++) );

            c2 = *s2++;
            if (_ISLEADBYTE(c2))
                c2 = ( (*s2 == '\0') ? 0 : ((c2<<8) | *s2++) );

            if (c1 != c2)
            {
                _munlock(_MB_CP_LOCK);
                return( (c1 > c2) ? 1 : -1);
            }

            if (c1 == 0)
            {
                _munlock(_MB_CP_LOCK);
                return(0);
            }
        }

        _munlock(_MB_CP_LOCK);
        return(0);
}

#endif  /* _MBCS */
