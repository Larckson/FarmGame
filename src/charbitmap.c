/* Syntax highlighting makes X() show as a different color than 0 to make
letters viewed here in a code editor clearer */
#define X() 1

#define bit_to_byte(a,b,c,d,e,f,g,h) ((unsigned char) \
    (((a)<<7)|((b)<<6)|((c)<<5)|((d)<<4)|((e)<<3)|((f)<<2)|((g)<<1)|(h)))

static const unsigned char gfx_font[96][8] = {
    { /* 32 space */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 33 ! */
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 34 " */
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 35 # */
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 36 $ */
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 37 % */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 38 & */
        bit_to_byte(0,0,X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,0,X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),X(),0,X(),X(),0),
        bit_to_byte(X(),X(),0,X(),X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 39 ' */
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 40 ( */
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 41 ) */
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 42 * */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,0,X(),X(),X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),X()),
        bit_to_byte(0,0,X(),X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 43 + */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 44 , */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0)
    },
    { /* 45 - */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 46 . */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 47 / */
        bit_to_byte(0,0,0,0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(X(),0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 48 0 */
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,X(),X(),X(),0),
        bit_to_byte(X(),X(),0,X(),X(),X(),X(),0),
        bit_to_byte(X(),X(),X(),X(),0,X(),X(),0),
        bit_to_byte(X(),X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 49 X() */
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 50 2 */
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 51 3 */
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 52 4 */
        bit_to_byte(0,0,0,X(),X(),X(),0,0),
        bit_to_byte(0,0,X(),X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,X(),X(),X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 53 5 */
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 54 6 */
        bit_to_byte(0,0,X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),X(),0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 55 7 */
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 56 8 */
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 57 9 */
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 58 : */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 59 ; */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0)
    },
    { /* 60 < */
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 61 = */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 62 > */
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 63 ? */
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 64 @ */
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,X(),X(),X(),X(),0),
        bit_to_byte(X(),X(),0,X(),X(),X(),X(),0),
        bit_to_byte(X(),X(),0,X(),X(),X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 65 X() */
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 66 B */
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 67 C */
        bit_to_byte(0,0,X(),X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,0,X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 68 D */
        bit_to_byte(X(),X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 69 E */
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,0,X(),0),
        bit_to_byte(0,X(),X(),0,X(),0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),0,X(),0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,X(),0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 70 F */
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,0,X(),0),
        bit_to_byte(0,X(),X(),0,X(),0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),0,X(),0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 71 G */
        bit_to_byte(0,0,X(),X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,0,X(),X(),X(),X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 72 H */
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 73 I */
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 74 J */
        bit_to_byte(0,0,0,X(),X(),X(),X(),0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 75 K */
        bit_to_byte(X(),X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(X(),X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 76 L */
        bit_to_byte(X(),X(),X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 77 M */
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),X(),X(),0,X(),X(),X(),0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(X(),X(),0,X(),0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 78 N */
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),X(),X(),0,0,X(),X(),0),
        bit_to_byte(X(),X(),X(),X(),0,X(),X(),0),
        bit_to_byte(X(),X(),0,X(),X(),X(),X(),0),
        bit_to_byte(X(),X(),0,0,X(),X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 79 O */
        bit_to_byte(0,0,X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,0,X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 80 P */
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 81 Q */
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 82 R */
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(X(),X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 83 S */
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,X(),X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 84 T */
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(X(),0,X(),X(),0,X(),0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 85 U */
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 86 V */
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 87 W */
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,X(),0,X(),X(),0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(X(),X(),X(),0,X(),X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 88 X() */
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,0,X(),X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 89 Y */
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 90 Z */
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 91 [ */
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 92 \ */
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 93 ] */
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 94 ^ */
        bit_to_byte(0,0,0,X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 95 _ */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),X())
    },
    { /* 96 ` */
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 97 a */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 98 b */
        bit_to_byte(X(),X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 99 c */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 100 d */
        bit_to_byte(0,0,0,X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 101 e */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 102 f */
        bit_to_byte(0,0,X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 103 g */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),0,0,0)
    },
    { /* 104 h */
        bit_to_byte(X(),X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(X(),X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 105 i */
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 106 j */
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0)
    },
    { /* 107 k */
        bit_to_byte(X(),X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 108 l */
        bit_to_byte(0,X(),X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 109 m */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(X(),X(),0,X(),0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 110 n */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),X(),0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 111 o */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 112 p */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),0,X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),0,0,0,0)
    },
    { /* 113 q */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),0,X(),X(),0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(0,0,0,X(),X(),X(),X(),0)
    },
    { /* 114 r */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),0,X(),X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 115 s */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 116 t */
        bit_to_byte(0,0,0,X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,X(),0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 117 u */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 118 v */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 119 w */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(X(),X(),0,X(),0,X(),X(),0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 120 x */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(0,0,X(),X(),X(),0,0,0),
        bit_to_byte(0,X(),X(),0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,0,X(),X(),0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 121 y */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),0,0,X(),X(),0,0),
        bit_to_byte(0,X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,X(),X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),0,0,0)
    },
    { /* 122 z */
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(X(),0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,X(),X(),0,0,X(),0,0),
        bit_to_byte(X(),X(),X(),X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 123 { */
        bit_to_byte(0,0,0,X(),X(),X(),0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(X(),X(),X(),0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 124 | */
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,X(),X(),0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 125 } */
        bit_to_byte(X(),X(),X(),0,0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,0,X(),X(),X(),0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(0,0,X(),X(),0,0,0,0),
        bit_to_byte(X(),X(),X(),0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 126 ~ */
        bit_to_byte(0,X(),X(),X(),0,X(),X(),0),
        bit_to_byte(X(),X(),0,X(),X(),X(),0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0),
        bit_to_byte(0,0,0,0,0,0,0,0)
    },
    { /* 127 block */
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),X()),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),X()),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),X()),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),X()),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),X()),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),X()),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),X()),
        bit_to_byte(X(),X(),X(),X(),X(),X(),X(),X())
    }
};

#undef X()
