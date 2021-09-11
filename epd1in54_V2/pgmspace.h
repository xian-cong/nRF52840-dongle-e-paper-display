#ifndef __PGMSPACE_H_
#define __PGMSPACE_H_ 1

#define __need_size_t
#include <inttypes.h>
#include <stddef.h>
#include <avr/io.h> //continue soon

#ifndef __ATTR_CONST__
#define __ATTR_CONST__ __attribute__((__const__))
#endif

#ifndef __ATTR_PROGMEM__
#define __ATTR_PROGMEM__ __attribute__((__progmem__))
#endif

#ifndef __ATTR_PURE__
#define __ATTR_PURE__ __attribute__((__pure__))
#endif

/**
   \ingroup avr_pgmspace
   \def PROGMEM
   Attribute to use in order to declare an object being located in
   flash ROM.
 */
#define PROGMEM __ATTR_PROGMEM__

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__DOXYGEN__)
/*
 * Doxygen doesn't grok the appended attribute syntax of
 * GCC, and confuses the typedefs with function decls, so
 * supply a doxygen-friendly view.
 */
/**
   \ingroup avr_pgmspace
   \typedef prog_void
   Type of a "void" object located in flash ROM.  Does not make much
   sense by itself, but can be used to declare a "void *" object in
   flash ROM.
*/
typedef void PROGMEM prog_void;
/**
   \ingroup avr_pgmspace
   \typedef prog_char
   Type of a "char" object located in flash ROM.
*/
typedef char PROGMEM prog_char;

/**
   \ingroup avr_pgmspace
   \typedef prog_uchar
   Type of an "unsigned char" object located in flash ROM.
*/
typedef unsigned char PROGMEM prog_uchar;


/**
   \ingroup avr_pgmspace
   \typedef prog_int8_t
   Type of an "int8_t" object located in flash ROM.
*/
typedef int8_t PROGMEM prog_int8_t;

/**
   \ingroup avr_pgmspace
   \typedef prog_uint8_t
   Type of an "uint8_t" object located in flash ROM.
*/
typedef uint8_t PROGMEM prog_uint8_t;

/**
   \ingroup avr_pgmspace
   \typedef prog_int16_t
   Type of an "int16_t" object located in flash ROM.
*/
typedef int16_t PROGMEM prog_int16_t;

/**
   \ingroup avr_pgmspace
   \typedef prog_uint16_t
   Type of an "uint16_t" object located in flash ROM.
*/
typedef uint16_t PROGMEM prog_uint16_t;

/**
   \ingroup avr_pgmspace
   \typedef prog_int32_t
   Type of an "int32_t" object located in flash ROM.
*/
typedef int32_t PROGMEM prog_int32_t;

/**
   \ingroup avr_pgmspace
   \typedef prog_uint32_t
   Type of an "uint32_t" object located in flash ROM.
*/
typedef uint32_t PROGMEM prog_uint32_t;

/**
   \ingroup avr_pgmspace
   \typedef prog_int64_t
   Type of an "int64_t" object located in flash ROM.
   \note This type is not available when the compiler
   option -mint8 is in effect.
*/
typedef int64_t PROGMEM prog_int64_t;

/**
   \ingroup avr_pgmspace
   \typedef prog_uint64_t
   Type of an "uint64_t" object located in flash ROM.
   \note This type is not available when the compiler
   option -mint8 is in effect.
*/
typedef uint64_t PROGMEM prog_uint64_t;
#else  /* !DOXYGEN */
typedef void prog_void PROGMEM;
typedef char prog_char PROGMEM;
typedef unsigned char prog_uchar PROGMEM;

typedef int8_t    prog_int8_t   PROGMEM;
typedef uint8_t   prog_uint8_t  PROGMEM;
typedef int16_t   prog_int16_t  PROGMEM;
typedef uint16_t  prog_uint16_t PROGMEM;
typedef int32_t   prog_int32_t  PROGMEM;
typedef uint32_t  prog_uint32_t PROGMEM;
#if !__USING_MINT8
typedef int64_t   prog_int64_t  PROGMEM;
typedef uint64_t  prog_uint64_t PROGMEM;
#endif
#endif /* defined(__DOXYGEN__) */

/* Although in C, we can get away with just using __c, it does not work in
   C++. We need to use &__c[0] to avoid the compiler puking. Dave Hylands
   explaned it thusly,
     Let's suppose that we use PSTR("Test"). In this case, the type returned
     by __c is a prog_char[5] and not a prog_char *. While these are
     compatible, they aren't the same thing (especially in C++). The type
     returned by &__c[0] is a prog_char *, which explains why it works
     fine. */

#if defined(__DOXYGEN__)
/*
 * The #define below is just a dummy that serves documentation
 * purposes only.
 */
/** \ingroup avr_pgmspace
    \def PSTR(s)
    Used to declare a static pointer to a string in program space. */
# define PSTR(s) ((const PROGMEM char *)(s))
#else  /* !DOXYGEN */
/* The real thing. */
# define PSTR(s) (__extension__({static char __c[] PROGMEM = (s); &__c[0];}))
#endif /* DOXYGEN */

#define __LPM_classic__(addr)   \
(__extension__({                \
    uint16_t __addr16 = (uint16_t)(addr); \
    uint8_t __result;           \
    __asm__                     \
    (                           \
        "lpm" "\n\t"            \
        "mov %0, r0" "\n\t"     \
        : "=r" (__result)       \
        : "z" (__addr16)        \
        : "r0"                  \
    );                          \
    __result;                   \
}))

#define __LPM_enhanced__(addr)  \
(__extension__({                \
    uint16_t __addr16 = (uint16_t)(addr); \
    uint8_t __result;           \
    __asm__                     \
    (                           \
        "lpm %0, Z" "\n\t"      \
        : "=r" (__result)       \
        : "z" (__addr16)        \
    );                          \
    __result;                   \
}))

#define __LPM_word_classic__(addr)          \
(__extension__({                            \
    uint16_t __addr16 = (uint16_t)(addr);   \
    uint16_t __result;                      \
    __asm__                                 \
    (                                       \
        "lpm"           "\n\t"              \
        "mov %A0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %B0, r0"   "\n\t"              \
        : "=r" (__result), "=z" (__addr16)  \
        : "1" (__addr16)                    \
        : "r0"                              \
    );                                      \
    __result;                               \
}))

#define __LPM_word_enhanced__(addr)         \
(__extension__({                            \
    uint16_t __addr16 = (uint16_t)(addr);   \
    uint16_t __result;                      \
    __asm__                                 \
    (                                       \
        "lpm %A0, Z+"   "\n\t"              \
        "lpm %B0, Z"    "\n\t"              \
        : "=r" (__result), "=z" (__addr16)  \
        : "1" (__addr16)                    \
    );                                      \
    __result;                               \
}))

#define __LPM_dword_classic__(addr)         \
(__extension__({                            \
    uint16_t __addr16 = (uint16_t)(addr);   \
    uint32_t __result;                      \
    __asm__                                 \
    (                                       \
        "lpm"           "\n\t"              \
        "mov %A0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %B0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %C0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %D0, r0"   "\n\t"              \
        : "=r" (__result), "=z" (__addr16)  \
        : "1" (__addr16)                    \
        : "r0"                              \
    );                                      \
    __result;                               \
}))

#define __LPM_dword_enhanced__(addr)        \
(__extension__({                            \
    uint16_t __addr16 = (uint16_t)(addr);   \
    uint32_t __result;                      \
    __asm__                                 \
    (                                       \
        "lpm %A0, Z+"   "\n\t"              \
        "lpm %B0, Z+"   "\n\t"              \
        "lpm %C0, Z+"   "\n\t"              \
        "lpm %D0, Z"    "\n\t"              \
        : "=r" (__result), "=z" (__addr16)  \
        : "1" (__addr16)                    \
    );                                      \
    __result;                               \
}))

#if defined (__AVR_HAVE_LPMX__)
#define __LPM(addr)         __LPM_enhanced__(addr)
#define __LPM_word(addr)    __LPM_word_enhanced__(addr)
#define __LPM_dword(addr)   __LPM_dword_enhanced__(addr)
#else
#define __LPM(addr)         __LPM_classic__(addr)
#define __LPM_word(addr)    __LPM_word_classic__(addr)
#define __LPM_dword(addr)   __LPM_dword_classic__(addr)
#endif

/** \ingroup avr_pgmspace
    \def pgm_read_byte_near(address_short)
    Read a byte from the program space with a 16-bit (near) address. 
    \note The address is a byte address.
    The address is in the program space. */

#define pgm_read_byte_near(address_short) __LPM((uint16_t)(address_short))

/** \ingroup avr_pgmspace
    \def pgm_read_word_near(address_short)
    Read a word from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */

#define pgm_read_word_near(address_short) __LPM_word((uint16_t)(address_short))

/** \ingroup avr_pgmspace
    \def pgm_read_dword_near(address_short)
    Read a double word from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */

#define pgm_read_dword_near(address_short) \
    __LPM_dword((uint16_t)(address_short))

#if defined(RAMPZ) || defined(__DOXYGEN__)

/* Only for devices with more than 64K of program memory.
   RAMPZ must be defined (see iom103.h, iom128.h).
*/

/* The classic functions are needed for ATmega103. */

#define __ELPM_classic__(addr)      \
(__extension__({                    \
    uint32_t __addr32 = (uint32_t)(addr); \
    uint8_t __result;               \
    __asm__                         \
    (                               \
        "out %2, %C1" "\n\t"        \
        "mov r31, %B1" "\n\t"       \
        "mov r30, %A1" "\n\t"       \
        "elpm" "\n\t"               \
        "mov %0, r0" "\n\t"         \
        : "=r" (__result)           \
        : "r" (__addr32),           \
          "I" (_SFR_IO_ADDR(RAMPZ)) \
        : "r0", "r30", "r31"        \
    );                              \
    __result;                       \
}))

#define __ELPM_enhanced__(addr)     \
(__extension__({                    \
    uint32_t __addr32 = (uint32_t)(addr); \
    uint8_t __result;               \
    __asm__                         \
    (                               \
        "out %2, %C1" "\n\t"        \
        "movw r30, %1" "\n\t"       \
        "elpm %0, Z+" "\n\t"        \
        : "=r" (__result)           \
        : "r" (__addr32),           \
          "I" (_SFR_IO_ADDR(RAMPZ)) \
        : "r30", "r31"              \
    );                              \
    __result;                       \
}))

#define __ELPM_word_classic__(addr)     \
(__extension__({                        \
    uint32_t __addr32 = (uint32_t)(addr); \
    uint16_t __result;                  \
    __asm__                             \
    (                                   \
        "out %2, %C1"   "\n\t"          \
        "mov r31, %B1"  "\n\t"          \
        "mov r30, %A1"  "\n\t"          \
        "elpm"          "\n\t"          \
        "mov %A0, r0"   "\n\t"          \
        "in r0, %2"     "\n\t"          \
        "adiw r30, 1"   "\n\t"          \
        "adc r0, __zero_reg__" "\n\t"   \
        "out %2, r0"    "\n\t"          \
        "elpm"          "\n\t"          \
        "mov %B0, r0"   "\n\t"          \
        : "=r" (__result)               \
        : "r" (__addr32),               \
          "I" (_SFR_IO_ADDR(RAMPZ))     \
        : "r0", "r30", "r31"            \
    );                                  \
    __result;                           \
}))

#define __ELPM_word_enhanced__(addr)    \
(__extension__({                        \
    uint32_t __addr32 = (uint32_t)(addr); \
    uint16_t __result;                  \
    __asm__                             \
    (                                   \
        "out %2, %C1"   "\n\t"          \
        "movw r30, %1"  "\n\t"          \
        "elpm %A0, Z+"  "\n\t"          \
        "elpm %B0, Z"   "\n\t"          \
        : "=r" (__result)               \
        : "r" (__addr32),               \
          "I" (_SFR_IO_ADDR(RAMPZ))     \
        : "r30", "r31"                  \
    );                                  \
    __result;                           \
}))

#define __ELPM_dword_classic__(addr)      \
(__extension__({                          \
    uint32_t __addr32 = (uint32_t)(addr); \
    uint32_t __result;                    \
    __asm__                               \
    (                                     \
        "out %2, %C1"          "\n\t"     \
        "mov r31, %B1"         "\n\t"     \
        "mov r30, %A1"         "\n\t"     \
        "elpm"                 "\n\t"     \
        "mov %A0, r0"          "\n\t"     \
        "in r0, %2"            "\n\t"     \
        "adiw r30, 1"          "\n\t"     \
        "adc r0, __zero_reg__" "\n\t"     \
        "out %2, r0"           "\n\t"     \
        "elpm"                 "\n\t"     \
        "mov %B0, r0"          "\n\t"     \
        "in r0, %2"            "\n\t"     \
        "adiw r30, 1"          "\n\t"     \
        "adc r0, __zero_reg__" "\n\t"     \
        "out %2, r0"           "\n\t"     \
        "elpm"                 "\n\t"     \
        "mov %C0, r0"          "\n\t"     \
        "in r0, %2"            "\n\t"     \
        "adiw r30, 1"          "\n\t"     \
        "adc r0, __zero_reg__" "\n\t"     \
        "out %2, r0"           "\n\t"     \
        "elpm"                 "\n\t"     \
        "mov %D0, r0"          "\n\t"     \
        : "=r" (__result)                 \
        : "r" (__addr32),                 \
          "I" (_SFR_IO_ADDR(RAMPZ))       \
        : "r0", "r30", "r31"              \
    );                                    \
    __result;                             \
}))

#define __ELPM_dword_enhanced__(addr)     \
(__extension__({                          \
    uint32_t __addr32 = (uint32_t)(addr); \
    uint32_t __result;                    \
    __asm__                               \
    (                                     \
        "out %2, %C1"   "\n\t"            \
        "movw r30, %1"  "\n\t"            \
        "elpm %A0, Z+"  "\n\t"            \
        "elpm %B0, Z+"  "\n\t"            \
        "elpm %C0, Z+"  "\n\t"            \
        "elpm %D0, Z"   "\n\t"            \
        : "=r" (__result)                 \
        : "r" (__addr32),                 \
          "I" (_SFR_IO_ADDR(RAMPZ))       \
        : "r30", "r31"                    \
    );                                    \
    __result;                             \
}))

#if defined (__AVR_HAVE_LPMX__)
#define __ELPM(addr)        __ELPM_enhanced__(addr)
#define __ELPM_word(addr)   __ELPM_word_enhanced__(addr)
#define __ELPM_dword(addr)  __ELPM_dword_enhanced__(addr)
#else
#define __ELPM(addr)        __ELPM_classic__(addr)
#define __ELPM_word(addr)   __ELPM_word_classic__(addr)
#define __ELPM_dword(addr)  __ELPM_dword_classic__(addr)
#endif

/** \ingroup avr_pgmspace
    \def pgm_read_byte_far(address_long)
    Read a byte from the program space with a 32-bit (far) address. 
    \note The address is a byte address. 
    The address is in the program space. */

#define pgm_read_byte_far(address_long)  __ELPM((uint32_t)(address_long))

/** \ingroup avr_pgmspace
    \def pgm_read_word_far(address_long)
    Read a word from the program space with a 32-bit (far) address. 
    \note The address is a byte address.
    The address is in the program space. */

#define pgm_read_word_far(address_long)  __ELPM_word((uint32_t)(address_long))

/** \ingroup avr_pgmspace
    \def pgm_read_dword_far(address_long)
    Read a double word from the program space with a 32-bit (far) address. 
    \note The address is a byte address.
    The address is in the program space. */

#define pgm_read_dword_far(address_long) __ELPM_dword((uint32_t)(address_long))

#endif /* RAMPZ or __DOXYGEN__ */

/** \ingroup avr_pgmspace
    \def pgm_read_byte(address_short)
    Read a byte from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */

#define pgm_read_byte(address_short)    pgm_read_byte_near(address_short)

/** \ingroup avr_pgmspace
    \def pgm_read_word(address_short)
    Read a word from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */

#define pgm_read_word(address_short)    pgm_read_word_near(address_short)

/** \ingroup avr_pgmspace
    \def pgm_read_dword(address_short)
    Read a double word from the program space with a 16-bit (near) address. 
    \note The address is a byte address. 
    The address is in the program space. */

#define pgm_read_dword(address_short)   pgm_read_dword_near(address_short)

/** \ingroup avr_pgmspace
    \def PGM_P
    Used to declare a variable that is a pointer to a string in program
    space. */

#ifndef PGM_P
#define PGM_P const prog_char *
#endif

/** \ingroup avr_pgmspace
    \def PGM_VOID_P
    Used to declare a generic pointer to an object in program space. */

#ifndef PGM_VOID_P
#define PGM_VOID_P const prog_void *
#endif

extern PGM_VOID_P memchr_P(PGM_VOID_P s, int val, size_t len) __ATTR_CONST__;
extern int memcmp_P(const void *, PGM_VOID_P, size_t) __ATTR_PURE__;
extern void *memcpy_P(void *, PGM_VOID_P, size_t);
extern void *memmem_P(const void *, size_t, PGM_VOID_P, size_t) __ATTR_PURE__;
extern PGM_VOID_P memrchr_P(PGM_VOID_P s, int val, size_t len) __ATTR_CONST__;
extern char *strcat_P(char *, PGM_P);
extern PGM_P strchr_P(PGM_P s, int val) __ATTR_CONST__;
extern PGM_P strchrnul_P(PGM_P s, int val) __ATTR_CONST__;
extern int strcmp_P(const char *, PGM_P) __ATTR_PURE__;
extern char *strcpy_P(char *, PGM_P);
extern int strcasecmp_P(const char *, PGM_P) __ATTR_PURE__;
extern char *strcasestr_P(const char *, PGM_P) __ATTR_PURE__;
extern size_t strcspn_P(const char *s, PGM_P reject) __ATTR_PURE__;
extern size_t strlcat_P (char *, PGM_P, size_t );
extern size_t strlcpy_P (char *, PGM_P, size_t );
extern size_t strlen_P(PGM_P) __ATTR_CONST__; /* program memory can't change */
extern size_t strnlen_P(PGM_P, size_t) __ATTR_CONST__; /* program memory can't change */
extern int strncmp_P(const char *, PGM_P, size_t) __ATTR_PURE__;
extern int strncasecmp_P(const char *, PGM_P, size_t) __ATTR_PURE__;
extern char *strncat_P(char *, PGM_P, size_t);
extern char *strncpy_P(char *, PGM_P, size_t);
extern char *strpbrk_P(const char *s, PGM_P accept) __ATTR_PURE__;
extern PGM_P strrchr_P(PGM_P s, int val) __ATTR_CONST__;
extern char *strsep_P(char **sp, PGM_P delim);
extern size_t strspn_P(const char *s, PGM_P accept) __ATTR_PURE__;
extern char *strstr_P(const char *, PGM_P) __ATTR_PURE__;

#ifdef __cplusplus
}
#endif

#endif /* __PGMSPACE_H_ */