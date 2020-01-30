# Recommended C style and coding rules

This document describes C code style used by [Alexander Kovalchuk](https://github.com/Zamuhrishka) in his projects and libraries.

# General rules

Here are listed most obvious and important general rules. Please check them carefully before you continue with other chapters.

- Use `C99` standard
- Do not use tabs, use spaces instead
- Use `4` spaces per indent level
- Use `1` space between keyword and opening bracket
- Do not use space between function name and opening bracket
```c
int a = sum(4, 3);      /* OK */
int a = sum (4, 3);     /* Wrong */
```

- Never use `__` or `_` prefix for variables/functions/macros/types. This is reserved for C language itself
- Opening curly bracket is always at the next line as keyword (`for`, `while`, `do`, `switch`, `if`, ...)
```c
int a;
for (a = 0; a < 5; ++i) {           /* Wrong */
}
for (a = 0; a < 5; ++i){            /* Wrong */
}
for (a = 0; a < 5; ++i)             /* OK */
{
}
```

- Use single space before and after comparison and assignment operators
```c
int a;
a = 3 + 4;              /* OK */
for (a = 0; a < 5; ++a) /* OK */
a=3+4;                  /* Wrong */
a = 3+4;                /* Wrong */
for (a=0;a<5;++a)       /* Wrong */
```

- Use single space after every comma
```c
func_name(5, 4);        /* OK */
func_name(4,3);         /* Wrong */
```

- Always initialize `static` and `global` variables
```c
static int a;           /* Wrong */
static int b = 4;       /* OK */
static int a = 0;       /* OK */

void my_func(void) 
{
    static int* ptr;    /* Wrong */
    static char abc = 0;/* OK */
}
```

- Declare all local variables of the same type in the same line
```c
void my_func(void) 
{
    char a;             /* OK */
    char a, b;          /* OK */
    char b;             /* Wrong, variable with char type already exists */
}
```

- Declare local variables in order
    1. Custom structures and enumerations
    2. Integer types, wider unsigned type first
    3. Single/Double floating point
```c
int my_func(void) 
{
    /* 1 */
    my_struct_t my;     /* First custom structures */
    my_struct_ptr_t* p; /* Pointers too */

    /* 2 */
    uint32_t a;
    int32_t b;
    uint16_t c;
    int16_t g;
    /* ... */

    /* 3 */
    double d;
    float f;
}
```

- Always declare local variables in beginning of the block, before first executable statement

- Declare counter variables in `for` loop
```c
/* OK */
for (int i = 0; i < 10; ++i)

/* OK, if you need counter variable later */
int i;
for (i = 0; i < 10; ++i) 
{
    if (...) 
    {
        break;
    }
}
if (i == 10) 
{

}

/* Wrong */
int i;
for (i = 0; i < 10; ++i) ...
```

- Avoid variable assignment with function call in declaration, except for single variables
```c
void a(void) 
{
    /* Avoid function calls when declaring variable */
    int a, b = sum(1, 2);
    
    /* Use this */
    int a, b;
    b = sum(1, 2);

    /* This is ok */
    uint8_t a = 3, b = 4;
}
```

- Except `char`, `float` or `double`, always use types declared in `stdint.h` library, eg. `uint8_t` for `unsigned 8-bit`, etc.
- Always compare pointers against `NULL` value
```c
/* OK, compare against NULL */
void* ptr;
if (ptr == NULL || ptr != NULL) 
{

}

/* Wrong */
if (ptr || !ptr) 
{

}
```

- Always use *pre-increment (and decrement respectively)* instead of *post-increment (and decrement respectively)*
```c
int a = 0;
...

a++;            /* Wrong */
++a;            /* OK */

for (int j = 0; j < 10; ++j) {}     /* OK */
```

- Always use `size_t` for length or size variables
- Always use `const` for pointer if function should not modify memory pointed to by `pointer`
- Always use `const` for function parameter or variable, if it should not be modified
```c

/* When d could be modified, data pointed to by d could not be modified */
void my_func(const void* d) 
{

}

/* When d and data pointed to by d both could not be modified */
void my_func(const void* const d) 
{

}

/* Not required, it is advised */
void my_func(const size_t len) 
{

}

/* When d should not be modified inside function, only data pointer to by d could be modified */
void my_func(void* const d) 
{

}
```

- When function may accept pointer of any type, always use `void *`, do not use `uint8_t *`
    - Function must take care of proper casting in implementation
```c
/*
 * To send data, function should not modify memory pointed to by `data` variable
 * thus `const` keyword is important
 *
 * To send generic data (or to write them to file)
 * any type may be passed for data,
 * thus use `void *`
 */
/* OK example */
void send_data(const void* data, size_t len) /* OK */
{ 
    /* Do not cast `void *` or `const void *` */
    const uint8_t* d = data;/* Function handles proper type for internal usage */
}

void send_data(const void* data, int len) /* Wrong */
{    
}
```

- Always compare variable against zero, except if it is treated as `boolean` type
- Never compare `boolean-treated` variables against zero or one. Use NOT (`!`) instead 
```c
size_t length = 5;  /* Counter variable */
uint8_t is_ok = 0;  /* Boolean-treated variable */
if (length)         /* Wrong, length is not treated as boolean */
if (length > 0)     /* OK, length is treated as counter variable containing multi values, not only 0 or 1 */
if (length == 0)    /* OK, length is treated as counter variable containing multi values, not only 0 or 1 */

if (is_ok)          /* OK, variable is treated as boolean */
if (!is_ok)         /* OK, -||- */
if (is_ok == 1)     /* Wrong, never compare boolean variable against 1! */
if (is_ok == 0)     /* Wrong, use ! for negative check */
```

- Always include check for `C++` with `extern` keyword in header file
- Every function must include *doxygen-enabled* comment, even if function is `static`
- Use English names/text for functions, variables, comments
- Never cast function returning `void *`, eg. `uint8_t* ptr = (uint8_t *)func_returning_void_ptr();` as `void *` is safely promoted to any other pointer type
    - Use `uint8_t* ptr = func_returning_void_ptr();` instead
- Always use `<` and `>` for C Standard Library include files, eg. `#include <stdlib.h>`
- Always use `""` for custom libraries, eg. `#include "my_library.h"`
- When casting to pointer type, always add space between type and asterisk, eg. `uint8_t* t = (uint8_t *)var_width_diff_type`
- Always respect code style already used in project or library

# Comments

- For multi-line comments use `space+asterisk` for every line
```c
/*
 * This is multi-line comments,
 * written in 2 lines (ok)
 */
 
/**
 * Wrong, use double-asterisk only for doxygen documentation
 */
 
/*
* Single line comment without space before asterisk (wrong)
*/

/*
 * Single line comment in multi-line configuration (wrong)
 */

/* Single line comment (ok) */
```

- Use `12` indents (`12 * 4` spaces) offset when commenting. If statement is larger than `12` indents, make comment `4-spaces` aligned (examples below)
```c
void my_func(void) 
{
    char a, b;
                                                
    a = call_func_returning_char_a(a);          /* This is comment with 12*4 spaces indent from beginning of line */
    b = call_func_returning_char_a_but_func_name_is_very_long(a);   /* This is comment, aligned to 4-spaces indent */
}
```

# Functions

- Every function which may have access from outside its module, must include function *prototype* (or *declaration*)
- Function name must be lowercase, optionally separated with underscore _ character
```c
/* OK */
void my_func(void);
void myfunc(void);

/* Wrong */
void MYFunc(void);
void myFunc();
```

- When function returns pointer, add space between asterisk and data type
```c
/* OK */
const char * my_func(void);
my_struct_t * my_func(int a, int b);

/* Wrong */
const char *my_func(void);
my_struct_t* my_func(void);
```

- When function returns pointer, asterisk character must include space between type and character (`char *`)
```c
/* OK */
const char * foo(void) 
{
    return "test";
}

/* Wrong */
const char* foo(void) 
{
    return "test";
}
```

# Variables

- Use `camelCase` for variable names
```c
/* OK */
int a;
int myVar;

/* Wrong */
int A; 
int MYVar;
int my_var;
int myvar;
```

- Group local variables together by `type`
```c
void
foo(void) {
    int a, b;   /* OK */
    char a;
    char b;     /* Wrong, char type already exists */
}
```

- Do not declare variable after first executable statement
```c
void foo(void) 
{
    int a;
    a = bar();
    int b;      /* Wrong, there is already executable statement */
}
```

- You may declare new variables inside next indent level
```c
int a, b;
a = foo();
if (a) 
{
    int c, d;   /* OK, c and d are in if-statement scope */
    c = foo();
    int e;      /* Wrong, there was already executable statement inside block */
}
```

- Declare pointer variables with asterisk aligned to type
```c
/* OK */
char* a;

/* Wrong */
char *a;
char * a;
```

- When declaring multiple pointer variables, you may declare them with asterisk aligned to variable name
```c
/* OK */
char *p, *n;
```

# Structures, enumerations, typedefs

- Structure or enumeration may contain `typedef` keyword
- All structure members must be lowercase
- All enumeration members must be uppercase
- Declare every member in its own line, even if they share the same type, eg. do not do `int a, b`
- Structure/enumeration must follow doxygen documentation syntax

When structure is declared, it may use one of `3` different options:

1. When structure is declared with *name only*, it *must not* contain `_t` suffix after its name.
```c
struct struct_name 
{
    char* a;
    char b;
};
```
2. When structure is declared with *typedef only*, it *has to* contain `_t` suffix after its name.
```c
typedef struct 
{
    char* a;
    char b;
} struct_name_t;
```
3. When structure is declared with *name and typedef*, it *must not* contain `_t` for basic name and it *has to* contain `_t` suffix after its name for typedef part.
```c
typedef struct struct_name 
{
    char* a;
    char b;
    char c;
} struct_name_t;
```

Examples of bad declarations and their suggested corrections
```c
/* a and b must be separated to 2 lines */
/* Name of structure with typedef must include _t suffix */
typedef struct 
{
    int a, b;
} a;

/* Corrected version */
typedef struct 
{
    int a;
    int b;
} a_t;

/* Wrong name, it must not include _t suffix */
struct name_t 
{
    int a;
    int b;
};

/* Wrong parameters, must be all uppercase */
typedef enum 
{
    MY_ENUM_TESTA,
    my_enum_testb,
} my_enum_t;
```

- When initializing structure on declaration, use `C99` initialization style
```c
/* OK */
a_t a = 
{
    .a = 4,
    .b = 5,
};

/* Wrong */
a_t a = {1, 2};
```

- When new typedef is introduced for function handles, use `_fn` suffix
```c
/* Function accepts 2 parameters and returns uint8_t */
/* Name of typedef has `_fn` suffix */
typedef uint8_t (*my_func_typedef_fn)(uint8_t p1, const char* p2);
```

# Compound statements

- Every compound statement must include opening and closing curly bracket, even if it includes only `1` nested statement
- Every compound statement must include single indent; when nesting statements, include `1` indent size for each nest
```c
/* OK */
if (c) 
{
    do_a();
} 
else 
{
    do_b();
}

/* Wrong */
if (c)
    do_a();
else
    do_b();
    
/* Wrong */
if (c) do_a();
else do_b();
```

- In case of `do-while` statement, `while` part must be in the same line as closing bracket of `do` part
```c
/* OK */
do 
{
    int a;
    a = do_a();
    do_b(a);
} while (check());

/* Wrong */
do
{
/* ... */
} while (check());

/* Wrong */
do {
/* ... */
}
while (check());
```

- Indentation is required for every opening bracket
```c
if (a) {
    do_a();
} else {
    do_b();
    if (c) {
        do_c();
    }
}
```

- Never do compound statement without curly bracket, even in case of single statement. Examples below show bad practices
```c
if (a) do_b();
else do_c();

if (a) do_a(); else do_b();
```

- Empty `while`, `do-while` or `for` loops must include brackets
```c
/* OK */
while (is_register_bit_set()) {}

/* Wrong */
while (is_register_bit_set());
while (is_register_bit_set()) { }
while (is_register_bit_set()) {
}
```

- If `while` (or `for`, `do-while`, etc) is empty (it can be the case in embedded programming), use empty single-line brackets
```c
/* Wait for bit to be set in embedded hardware unit
uint32_t* addr = HW_PERIPH_REGISTER_ADDR;

/* Wait bit 13 to be ready */
while (*addr & (1 << 13)) {}        /* OK, empty loop contains no spaces inside curly brackets */
while (*addr & (1 << 13)) { }       /* Wrong */
while (*addr & (1 << 13)) {         /* Wrong */

}
while (*addr & (1 << 13));          /* Wrong, curly brackets are missing. Can lead to compiler warnings or unintentional bugs */
```
- Always prefer using loops in this order: `for`, `do-while`, `while`
- Avoid incrementing variables inside loop block if possible, see examples

```c
/* Not recommended */
int a = 0;
while (a < 10) {
    .
    ..
    ...
    ++a;
}

/* Better */
for (int a = 0; a < 10; ++a) {

}

/* Better, if inc may not happen in every cycle */
for (int a = 0; a < 10; ) {
    if (...) {
        ++a;
    }
}
```

### Switch statement

- Add *single indent* for every `case` statement
- Use additional *single indent* for `break` statement in each `case` or `default`
```c
/* OK, every case has single indent */
/* OK, every break has additional indent */
switch (check()) {
    case 0:
        do_a();
        break;
    case 1:
        do_b();
        break;
    default:
        break;
}

/* Wrong, case indent missing */
switch (check()) {
case 0:
    do_a();
    break;
case 1:
    do_b();
    break;
default:
    break;
}

/* Wrong */
switch (check()) {
    case 0:
        do_a();
    break;      /* Wrong, break must have indent as it is under case */
    case 1:
    do_b();     /* Wrong, indent under case is missing */
    break;
    default:
        break;
}
```

- Always include `default` statement
```c
/* OK */
switch (var) {
    case 0: 
        do_job(); 
        break;
    default: break;
}

/* Wrong, default is missing */
switch (var) {
    case 0: 
        do_job(); 
        break;
}
```

- If local variables are required, use curly brackets and put `break` statement inside.
    - Put opening curly bracket in the next line as `case` statement
```c
switch (a) {
    /* OK */
    case 0: 
    {
        int a, b;
        char c;
        a = 5;
        /* ... */
        break;
    }
    
    /* Wrong */
    case 1: {
        int a;
        break;    
    }
    
    /* Wrong */
    case 2: {
        int a;   
    }
    break; 
}
```

# Macros and preprocessor directives

- Always use macros instead of literal constants, specially for numbers
- All macros must be fully uppercase, with optional underscore `_` character, except if they are clearly marked as function which may be in the future replaced with regular function syntax
```c
/* OK */
#define MY_MACRO(x)         ((x) * (x))

/* Wrong */
#define square(x)           ((x) * (x))
```

- Always protect input parameters with parentheses
```c
/* OK */
#define MIN(x, y)           ((x) < (y) ? (x) : (y))

/* Wrong */
#define MIN(x, y)           x < y ? x : y
```

- Always protect final macro evaluation with parenthesis
```c
/* Wrong */
#define MIN(x, y)           (x) < (y) ? (x) : (y)
#define SUM(x, y)           (x) + (y)

/* Imagine result of this equation using wrong SUM implementation */
int x = 5 * SUM(3, 4);      /* Expected result is 5 * 7 = 35 */
int x = 5 * (3) + (4);      /* It is evaluated to this, final result = 19 which is not what we expect */

/* Correct implementation */
#define MIN(x, y)           ((x) < (y) ? (x) : (y))
#define SUM(x, y)           ((x) + (y))
```

- When macro uses multiple statements, protect it using `do-while (0)` statement
```c
typedef struct {
    int px, py;
} point_t;
point_t p;                  /* Define new point */

/* Wrong implementation */

/* Define macro to set point */
#define SET_POINT(p, x, y)  (p)->px = (x); (p)->py = (y)    /* 2 statements. Last one should not implement semicolon */

SET_POINT(&p, 3, 4);        /* Set point to position 3, 4. This evaluates to... */
(&p)->px = (3); (&p)->py = (4); /* ... to this. In this example this is not a problem. */

/* Consider this ugly code, however it is valid by C standard (not recommended) */
if (a)                      /* If a is true */
    if (b)                  /* If b is true */
        SET_POINT(&p, 3, 4);/* Set point to x = 3, y = 4 */
    else
        SET_POINT(&p, 5, 6);/* Set point to x = 5, y = 6 */

/* Evaluates to code below. Do you see the problem? */
if (a)
    if (b) 
        (&p)->px = (3); (&p)->py = (4);
    else
        (&p)->px = (5); (&p)->py = (6);

/* Or if we rewrite it a little */
if (a)
    if (b) 
        (&p)->px = (3);
        (&p)->py = (4);
    else
        (&p)->px = (5);
        (&p)->py = (6);

/*
 * Ask yourself a question: To which `if` statement `else` keyword belongs?
 *
 * Based on first part of code, answer is straight-forward. To inner `if` statement when we check `b` condition
 * Actual answer: Compilation error as `else` belongs nowhere
 */

/* Better and correct implementation of macro */
#define SET_POINT(p, x, y)  do { (p)->px = (x); (p)->py = (y); } while (0)    /* 2 statements. No semicolon after while loop */
/* Or even better */
#define SET_POINT(p, x, y)  do {    \   /* Backslash indicates statement continues in new line */
    (p)->px = (x);                  \
    (p)->py = (y);                  \
} while (0)                             /* 2 statements. No semicolon after while loop */

/* Now original code evaluates to */
if (a)
    if (b) 
        do { (&p)->px = (3); (&p)->py = (4); } while (0);
    else
        do { (&p)->px = (5); (&p)->py = (6); } while (0);

/* Every part of `if` or `else` contains only `1` inner statement (do-while), hence this is valid evaluation */

/* To make code perfect, use brackets for every if-ifelse-else statements */
if (a) {                    /* If a is true */
    if (b) {                /* If b is true */
        SET_POINT(&p, 3, 4);/* Set point to x = 3, y = 4 */
    } else {
        SET_POINT(&p, 5, 6);/* Set point to x = 5, y = 6 */
    }
}
```

- Always write macro documentation as regular function with additional `hideinitializer` doxygen keyword
```c
#define MY_MACRO(x)         ((x) * 2)
```

- Avoid using `#ifdef` or `#ifndef`. Use `defined()` or `!defined()` instead
```c
#ifdef XYZ
/* do something */
#endif /* XYZ */
```

- Always document `if/elif/else/endif` statements
```c
/* OK */
#if defined(XYZ)
/* Do if XYZ defined */
#else /* defined(XYZ) */
/* Do if XYZ not defined */
#endif /* !defined(XYZ) */

/* Wrong */
#if defined(XYZ)
/* Do if XYZ defined */
#else
/* Do if XYZ not defined */
#endif
```

- Do not indent sub statements inside `#if` statement
```c
/* OK */
#if defined(XYZ)
#if defined(ABC)
/* do when ABC defined */
#endif /* defined(ABC) */
#else /* defined(XYZ) */
/* Do when XYZ not defined */
#endif /* !defined(XYZ) */

/* Wrong */
#if defined(XYZ)
    #if defined(ABC)
        /* do when ABC defined */
    #endif /* defined(ABC) */
#else /* defined(XYZ) */
    /* Do when XYZ not defined */
#endif /* !defined(XYZ) */
```

# Documentation

Documented code allows doxygen to parse and general html/pdf/latex output, thus it is very important to do it properly.

- Use doxygen-enabled documentation style for `variables`, `functions` and `structures/enumerations`
- Always use `\` for doxygen, do not use `@`
- Always use `5x4` spaces (`5` tabs) offset from beginning of line for text
```c
/**
 * \brief           Holds pointer to first entry in linked list
 *                  Beginning of this text is 5 tabs (20 spaces) from beginning of line
 */
static
type_t* list;
```

- Every structure/enumeration member must include documentation
- Use `12x4 spaces` offset for beginning of comment
```c
/**
 * \brief           This is point struct
 * \note            This structure is used to calculate all point 
 *                      related stuff
 */
typedef struct {
    int x;                                      /*!< Point X coordinate */
    int y;                                      /*!< Point Y coordinate */
    int size;                                   /*!< Point size.
                                                    Since comment is very big,
                                                    you may go to next line */
} point_t;

/**
 * \brief           Point color enumeration
 */
typedef enum {
    COLOR_RED,                                  /*!< Red color. This comment has 12x4
                                                    spaces offset from beginning of line */
    COLOR_GREEN,                                /*!< Green color */
    COLOR_BLUE,                                 /*!< Blue color */
} point_color_t;
```

- Documentation for functions must be written in function declaration (header file usually) except *static* functions
- Function must include `brief` and all parameters documentation
- Every parameter must be noted if it is `in` or `out` for *input* and *output* respectively
- Function must include `return` parameter if it returns something. This does not apply for `void` functions
- Function can include other doxygen keywords, such as `note` or `warning`
- Use colon `:` between parameter name and its description
```c
/**
 * \brief           Sum `2` numbers
 * \param[in]       a: First number
 * \param[in]       b: Second number
 * \return          Sum of input values
 */
int
sum(int a, int b) {
    return a + b;
}

/**
 * \brief           Sum `2` numbers and write it to pointer
 * \note            This function does not return value, it stores it to pointer instead
 * \param[in]       a: First number
 * \param[in]       b: Second number
 * \param[out]      result: Output variable used to save result
 */
void
void_sum(int a, int b, int* result) {
    *result = a + b;
}
```

- If function returns member of enumeration, use `ref` keyword to specify which one
```c
/**
 * \brief           My enumeration
 */
typedef enum {
    MY_ERR,                                     /*!< Error value */
    MY_OK                                       /*!< OK value */
} my_enum_t;

/**
 * \brief           Check some value
 * \return          \ref MY_OK on success, member of \ref my_enum_t otherwise
 */
my_enum_t
check_value(void) {
    return MY_OK;
}
```

- Use notation (\`NULL\` => `NULL`) for constants or numbers
```c
/**
 * \brief           Get data from input array
 * \param[in]       in: Input data
 * \return          Pointer to output data on success, `NULL` otherwise
 */
const void *
get_data(const void* in) {
    return in;
}
```

- Documentation for macros must include `hideinitializer` doxygen command
```c
/**
 * \brief           Get minimal value between `x` and `y`
 * \param[in]       x: First value
 * \param[in]       y: Second value
 * \return          Minimal value between `x` and `y`
 * \hideinitializer
 */
#define MIN(x, y)       ((x) < (y) ? (x) : (y))
```

# Header/source files

- Leave single empty line at the end of file
- Every file must include doxygen annotation for `file` and `brief` description followed by empty line (when using doxygen)
```c
/**
 * \file            template.h
 * \brief           Template include file
 */
                    /* Here is empty line */
```

- Every file (*header* or *source*) must include license (opening comment includes single asterisk as this must be ignored by doxygen)
- Use the same license as already used by project/library
```c
/**
 * \file            template.h
 * \brief           Template include file
 */

/*
 * Copyright (c) year FirstName LASTNAME
 *  
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of library_name.
 *
 * Author:          FirstName LASTNAME <optional_email@example.com>
 */
```

- Header file must include guard `#ifndef`
- Header file must include `C++` check
- Header file must include only every other header file in order to compile correctly, but not more (.c should include the rest if required)
- Header file must only expose module public variables/types/functions
- Use `extern` for global module variables in header file, define them in source file later
```
/* file.h ... */
#ifndef ...

extern int my_variable; /* This is global variable declaration in header */

#endif 

/* file.c ... */
int my_variable;        /* Actually defined in source */
```
- Never include `.c` files in another `.c` file
- `.c` file should first include corresponding `.h` file, later others, unless otherwise explicitly necessary
- Do not include module private declarations in header file

- Header file example (no license for sake of an example)
```c
/* License comes here */
#ifndef TEMPLATE_HDR_H
#define TEMPLATE_HDR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Include other headers */

/* File content here */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TEMPLATE_HDR_H */
```
