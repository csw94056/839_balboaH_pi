/* misc.h
 * maths Macros
 * 6/21/99 */

#ifndef __GNUC__

/* Use the C* extensions: >? (MAX) and <? (MIN) operators */
#ifndef	MAX
#define	MAX(x, y) ((x) >? (y))
#endif

#ifndef	MIN
#define	MIN(x, y) ((x) <? (y))
#endif

#ifndef	ABS
#define	ABS(x)	((x) >? (-(x)))
#endif

#ifndef ROUND
#define ROUND(a) ( (int) {a > 0 ? a + 0.5 : a - 0.5; })
#endif


#else

#define ROUND(a)    ({ typeof (a) __a = (a); (int) ((__a > 0) ? (__a + 0.5) : (__a - 0.5)); })
#define MAX(a, b)   ({ typeof (a) _a = (a); typeof (b) _b = (b); _a > _b ? _a : _b; })
#define MIN(a, b)   ({ typeof (a) _a = (a); typeof (b) _b = (b); _a < _b ? _a : _b; })
#define ABS(a)      ({ typeof (a) _a = (a); _a < (typeof (a)) 0 ? -_a : _a; })

#endif
