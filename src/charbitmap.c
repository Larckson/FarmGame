/* Syntax highlighting makes X() show as a different color than 0.
This makes the bitmaps for the different chars more distinct in code editors */
#define X() 1

#define BITTOBYTE(a,b,c,d,e,f,g,h) ((unsigned char) \
    (((a)<<7)|((b)<<6)|((c)<<5)|((d)<<4)|((e)<<3)|((f)<<2)|((g)<<1)|(h)))

static const unsigned char gfx_font[96][8]={
    /* Begin comma spacing override to allow for easily visible characters */
    { /* 32 space */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 33 ! */
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 34 " */
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 35 # */
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 36 $ */
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 37 % */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 38 & */
        BITTOBYTE(0  ,0  ,X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 39 ' */
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 40 ( */
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 41 ) */
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 42 * */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),X()),
        BITTOBYTE(0  ,0  ,X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 43 + */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 44 , */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  )
    },
    { /* 45 - */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 46 . */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 47 / */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 48 0 */
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,X(),X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),X(),0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 49 X() */
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 50 2 */
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 51 3 */
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 52 4 */
        BITTOBYTE(0  ,0  ,0  ,X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 53 5 */
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 54 6 */
        BITTOBYTE(0  ,0  ,X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 55 7 */
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 56 8 */
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 57 9 */
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 58 : */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 59 ; */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  )
    },
    { /* 60 < */
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 61 = */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 62 > */
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 63 ? */
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 64 @ */
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,X(),X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,X(),X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,X(),X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 65 X() */
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 66 B */
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 67 C */
        BITTOBYTE(0  ,0  ,X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 68 D */
        BITTOBYTE(X(),X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 69 E */
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,X(),0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 70 F */
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 71 G */
        BITTOBYTE(0  ,0  ,X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 72 H */
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 73 I */
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 74 J */
        BITTOBYTE(0  ,0  ,0  ,X(),X(),X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 75 K */
        BITTOBYTE(X(),X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 76 L */
        BITTOBYTE(X(),X(),X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 77 M */
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),0  ,X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,X(),0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 78 N */
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),X(),0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,X(),X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 79 O */
        BITTOBYTE(0  ,0  ,X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 80 P */
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 81 Q */
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 82 R */
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 83 S */
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 84 T */
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),0  ,X(),X(),0  ,X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 85 U */
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 86 V */
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 87 W */
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,X(),0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),0  ,X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 88 X() */
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 89 Y */
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 90 Z */
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 91 [ */
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 92 \ */
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 93 ] */
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 94 ^ */
        BITTOBYTE(0  ,0  ,0  ,X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 95 _ */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),X())
    },
    { /* 96 ` */
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 97 a */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 98 b */
        BITTOBYTE(X(),X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 99 c */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 100 d */
        BITTOBYTE(0  ,0  ,0  ,X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 101 e */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 102 f */
        BITTOBYTE(0  ,0  ,X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 103 g */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),0  ,0  ,0  )
    },
    { /* 104 h */
        BITTOBYTE(X(),X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 105 i */
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 106 j */
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  )
    },
    { /* 107 k */
        BITTOBYTE(X(),X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 108 l */
        BITTOBYTE(0  ,X(),X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 109 m */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,X(),0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 110 n */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 111 o */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 112 p */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),0  ,0  ,0  ,0  )
    },
    { /* 113 q */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),X(),X(),0  )
    },
    { /* 114 r */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 115 s */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 116 t */
        BITTOBYTE(0  ,0  ,0  ,X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 117 u */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 118 v */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 119 w */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,X(),0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 120 x */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,0  ,X(),X(),0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 121 y */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(0  ,X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,X(),X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),0  ,0  ,0  )
    },
    { /* 122 z */
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(X(),0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,X(),X(),0  ,0  ,X(),0  ,0  ),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 123 { */
        BITTOBYTE(0  ,0  ,0  ,X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 124 | */
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 125 } */
        BITTOBYTE(X(),X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,X(),X(),0  ,0  ,0  ,0  ),
        BITTOBYTE(X(),X(),X(),0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 126 ~ */
        BITTOBYTE(0  ,X(),X(),X(),0  ,X(),X(),0  ),
        BITTOBYTE(X(),X(),0  ,X(),X(),X(),0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ),
        BITTOBYTE(0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  )
    },
    { /* 127 block */
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),X()),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),X()),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),X()),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),X()),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),X()),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),X()),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),X()),
        BITTOBYTE(X(),X(),X(),X(),X(),X(),X(),X())
    }
    /* End comma spacing override */
};

#undef X
