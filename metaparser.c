/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 1 "metaparser.y"
  #
#include <stdio.h>
#include <assert.h>
#include "metaparser.h"
#include "metadef.h"
#line 14 "metaparser.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    MetaTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is MetaTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    MetaARG_SDECL     A static variable declaration for the %extra_argument
**    MetaARG_PDECL     A parameter declaration for the %extra_argument
**    MetaARG_STORE     Code to store %extra_argument into yypParser
**    MetaARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 53
#define YYACTIONTYPE unsigned char
#define MetaTOKENTYPE const char*
typedef union {
  int yyinit;
  MetaTOKENTYPE yy0;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define MetaARG_SDECL
#define MetaARG_PDECL
#define MetaARG_FETCH
#define MetaARG_STORE
#define YYNSTATE 83
#define YYNRULE 48
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
#define YY_ACTTAB_COUNT (140)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */     4,    6,   63,   77,   76,   68,   66,    3,    8,   82,
 /*    10 */    81,   52,   45,   34,   57,   56,   55,   13,   52,   45,
 /*    20 */    34,   57,   56,   55,   13,   59,   45,   34,   57,   56,
 /*    30 */    55,   13,   20,   23,   21,   22,   45,  132,    7,   82,
 /*    40 */    81,   43,   44,   12,   70,   23,   21,   28,   74,   73,
 /*    50 */    72,   71,   23,   21,   36,   12,   49,    5,   45,   83,
 /*    60 */     5,   69,   12,   42,   14,   45,   64,   15,   50,   19,
 /*    70 */    42,   78,   77,   76,   79,   24,   18,   33,   39,   53,
 /*    80 */    32,   61,   15,  108,   60,   54,  108,   17,   29,   41,
 /*    90 */    32,   37,   11,   50,   24,   18,    9,   35,   35,   10,
 /*   100 */     2,   40,   51,   39,   12,   58,    9,   38,   65,    1,
 /*   110 */    19,    5,   80,   75,   27,   16,   67,   17,   62,   35,
 /*   120 */   133,  133,   46,   30,  133,  133,   48,  133,  133,  133,
 /*   130 */   133,   47,   31,  133,   26,  133,  133,  133,  133,   25,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    33,   36,   37,   38,   39,   42,   43,   33,   30,   31,
 /*    10 */    32,   44,   45,   46,   47,   48,   49,   50,   44,   45,
 /*    20 */    46,   47,   48,   49,   50,   44,   45,   46,   47,   48,
 /*    30 */    49,   50,    8,    1,    2,   11,   45,   29,   30,   31,
 /*    40 */    32,   50,    7,   11,   12,    1,    2,   34,   24,   25,
 /*    50 */    26,   27,    1,    2,   34,   11,   10,   13,   45,    0,
 /*    60 */    13,   12,   11,   50,   41,   45,   43,   20,    9,   20,
 /*    70 */    50,   37,   38,   39,   14,   15,   16,   46,   19,   48,
 /*    80 */    40,   10,   20,   20,   22,   10,   23,   17,   18,   20,
 /*    90 */    40,   51,   23,    9,   15,   16,   21,   10,   10,   12,
 /*   100 */    11,   51,   14,   19,   11,   10,   21,   10,   35,   13,
 /*   110 */    20,   13,   35,   35,   40,   35,   35,   17,   10,   10,
 /*   120 */    52,   52,   40,   40,   52,   52,   40,   52,   52,   52,
 /*   130 */    52,   40,   40,   52,   40,   52,   52,   52,   52,   40,
};
#define YY_SHIFT_USE_DFLT (-1)
#define YY_SHIFT_COUNT (50)
#define YY_SHIFT_MIN   (0)
#define YY_SHIFT_MAX   (109)
static const signed char yy_shift_ofst[] = {
 /*     0 */    84,  109,  109,   88,   87,   79,   60,   59,   84,  108,
 /*    10 */   108,   24,   24,   75,   70,  108,  100,   24,   24,   24,
 /*    20 */    24,   24,   24,   24,   24,   44,   44,   44,   47,   98,
 /*    30 */    32,   51,   51,   69,   69,   63,   62,   49,   96,   97,
 /*    40 */    90,   95,   85,   85,   71,   35,   93,   93,   93,   89,
 /*    50 */    46,
};
#define YY_REDUCE_USE_DFLT (-38)
#define YY_REDUCE_COUNT (29)
#define YY_REDUCE_MIN   (-37)
#define YY_REDUCE_MAX   (99)
static const signed char yy_reduce_ofst[] = {
 /*     0 */     8,  -26,  -33,  -19,  -19,  -35,   34,  -22,  -22,   20,
 /*    10 */    13,   50,   40,   31,  -37,   -9,   23,   99,   94,   92,
 /*    20 */    91,   86,   83,   82,   74,   81,   80,   78,   77,   73,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */    87,  103,  103,  131,  131,   90,  131,  131,   84,  131,
 /*    10 */   131,  131,  131,  131,  131,  131,   98,  131,  131,  131,
 /*    20 */   131,  131,  131,  131,  131,  131,  131,  131,  131,  131,
 /*    30 */   131,  130,  129,  118,  131,  106,  131,  131,  131,  131,
 /*    40 */   119,  131,  115,  116,  131,  113,  125,  127,  126,  131,
 /*    50 */   131,  102,  104,  117,  108,  112,  111,  110,  109,  105,
 /*    60 */   114,  107,  106,   91,   99,  101,  100,   97,   96,  128,
 /*    70 */   124,  123,  122,  121,  120,   95,   94,   93,   92,   89,
 /*    80 */    88,   86,   85,
};

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  MetaARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void MetaTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "PLUS",          "MINUS",         "MUL",         
  "DIV",           "OR",            "AND",           "DOT",         
  "NOT",           "KW_FUNC",       "ID",            "LPARENTHESES",
  "RPARENTHESES",  "LBRACE",        "RBRACE",        "KW_WHILE",    
  "KW_IF",         "KW_ELIF",       "KW_ELSE",       "KW_STRUCT",   
  "COMMA",         "LBRACKET",      "RBRACKET",      "EQ",          
  "KW_NULL",       "TOK_STRING",    "TOK_INT",       "TOK_ID",      
  "error",         "prog",          "prog_block",    "struct_decl", 
  "func_decl",     "var_decl_list",  "var_type_list",  "statement_block",
  "statement_list",  "statement",     "while_stmt",    "if_stmt",     
  "value",         "elif_block_list",  "else_block",    "elif_block",  
  "var_decl",      "id_chain",      "id_list",       "var_typed_assigned_decl",
  "var_untyped_assigned_decl",  "var_typed_unassigned_decl",  "var_type",      "value_list",  
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "prog ::= prog_block",
 /*   1 */ "prog_block ::= prog_block prog_block",
 /*   2 */ "prog_block ::= struct_decl",
 /*   3 */ "prog_block ::= func_decl",
 /*   4 */ "prog_block ::=",
 /*   5 */ "func_decl ::= KW_FUNC ID LPARENTHESES var_decl_list RPARENTHESES var_type_list statement_block",
 /*   6 */ "statement_block ::= LBRACE statement_list RBRACE",
 /*   7 */ "statement_list ::=",
 /*   8 */ "statement_list ::= statement",
 /*   9 */ "statement_list ::= statement_list statement",
 /*  10 */ "statement ::= while_stmt",
 /*  11 */ "statement ::= if_stmt",
 /*  12 */ "while_stmt ::= KW_WHILE value statement_block",
 /*  13 */ "if_stmt ::= KW_IF value statement_block elif_block_list else_block",
 /*  14 */ "elif_block ::= KW_ELIF value statement_block",
 /*  15 */ "elif_block_list ::=",
 /*  16 */ "elif_block_list ::= elif_block",
 /*  17 */ "elif_block_list ::= elif_block_list elif_block",
 /*  18 */ "else_block ::= KW_ELSE statement_block",
 /*  19 */ "struct_decl ::= KW_STRUCT ID LBRACE var_decl_list RBRACE",
 /*  20 */ "var_decl_list ::=",
 /*  21 */ "var_decl_list ::= var_decl",
 /*  22 */ "var_decl_list ::= var_decl_list var_decl",
 /*  23 */ "id_chain ::= ID",
 /*  24 */ "id_chain ::= id_chain DOT ID",
 /*  25 */ "id_list ::= ID",
 /*  26 */ "id_list ::= id_list COMMA ID",
 /*  27 */ "var_decl ::= var_typed_assigned_decl",
 /*  28 */ "var_decl ::= var_untyped_assigned_decl",
 /*  29 */ "var_decl ::= var_typed_unassigned_decl",
 /*  30 */ "var_type ::= id_chain",
 /*  31 */ "var_type ::= var_type LBRACKET var_type_list RBRACKET",
 /*  32 */ "var_type_list ::= var_type",
 /*  33 */ "var_type_list ::= var_type_list COMMA var_type",
 /*  34 */ "var_typed_assigned_decl ::= var_type var_untyped_assigned_decl",
 /*  35 */ "var_typed_unassigned_decl ::= var_type id_list",
 /*  36 */ "var_untyped_assigned_decl ::= id_list EQ value_list",
 /*  37 */ "value ::= KW_NULL",
 /*  38 */ "value ::= TOK_STRING",
 /*  39 */ "value ::= TOK_INT",
 /*  40 */ "value ::= TOK_ID",
 /*  41 */ "value ::= LPARENTHESES value RPARENTHESES",
 /*  42 */ "value ::= value PLUS value",
 /*  43 */ "value ::= value MINUS value",
 /*  44 */ "value ::= NOT value",
 /*  45 */ "value ::= value LPARENTHESES value_list RPARENTHESES",
 /*  46 */ "value_list ::= value",
 /*  47 */ "value_list ::= value_list COMMA value",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Meta and MetaFree.
*/
void *MetaAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  MetaARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from MetaAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void MetaFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int MetaStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_COUNT
   || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   MetaARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
   MetaARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 29, 1 },
  { 30, 2 },
  { 30, 1 },
  { 30, 1 },
  { 30, 0 },
  { 32, 7 },
  { 35, 3 },
  { 36, 0 },
  { 36, 1 },
  { 36, 2 },
  { 37, 1 },
  { 37, 1 },
  { 38, 3 },
  { 39, 5 },
  { 43, 3 },
  { 41, 0 },
  { 41, 1 },
  { 41, 2 },
  { 42, 2 },
  { 31, 5 },
  { 33, 0 },
  { 33, 1 },
  { 33, 2 },
  { 45, 1 },
  { 45, 3 },
  { 46, 1 },
  { 46, 3 },
  { 44, 1 },
  { 44, 1 },
  { 44, 1 },
  { 50, 1 },
  { 50, 4 },
  { 34, 1 },
  { 34, 3 },
  { 47, 2 },
  { 49, 2 },
  { 48, 3 },
  { 40, 1 },
  { 40, 1 },
  { 40, 1 },
  { 40, 1 },
  { 40, 3 },
  { 40, 3 },
  { 40, 3 },
  { 40, 2 },
  { 40, 4 },
  { 51, 1 },
  { 51, 3 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  MetaARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      default:
      /* (0) prog ::= prog_block */ yytestcase(yyruleno==0);
      /* (1) prog_block ::= prog_block prog_block */ yytestcase(yyruleno==1);
      /* (2) prog_block ::= struct_decl */ yytestcase(yyruleno==2);
      /* (3) prog_block ::= func_decl */ yytestcase(yyruleno==3);
      /* (4) prog_block ::= */ yytestcase(yyruleno==4);
      /* (5) func_decl ::= KW_FUNC ID LPARENTHESES var_decl_list RPARENTHESES var_type_list statement_block */ yytestcase(yyruleno==5);
      /* (6) statement_block ::= LBRACE statement_list RBRACE */ yytestcase(yyruleno==6);
      /* (7) statement_list ::= */ yytestcase(yyruleno==7);
      /* (8) statement_list ::= statement */ yytestcase(yyruleno==8);
      /* (9) statement_list ::= statement_list statement */ yytestcase(yyruleno==9);
      /* (10) statement ::= while_stmt */ yytestcase(yyruleno==10);
      /* (11) statement ::= if_stmt */ yytestcase(yyruleno==11);
      /* (12) while_stmt ::= KW_WHILE value statement_block */ yytestcase(yyruleno==12);
      /* (13) if_stmt ::= KW_IF value statement_block elif_block_list else_block */ yytestcase(yyruleno==13);
      /* (14) elif_block ::= KW_ELIF value statement_block */ yytestcase(yyruleno==14);
      /* (15) elif_block_list ::= */ yytestcase(yyruleno==15);
      /* (16) elif_block_list ::= elif_block */ yytestcase(yyruleno==16);
      /* (17) elif_block_list ::= elif_block_list elif_block */ yytestcase(yyruleno==17);
      /* (18) else_block ::= KW_ELSE statement_block */ yytestcase(yyruleno==18);
      /* (19) struct_decl ::= KW_STRUCT ID LBRACE var_decl_list RBRACE */ yytestcase(yyruleno==19);
      /* (20) var_decl_list ::= */ yytestcase(yyruleno==20);
      /* (21) var_decl_list ::= var_decl */ yytestcase(yyruleno==21);
      /* (22) var_decl_list ::= var_decl_list var_decl */ yytestcase(yyruleno==22);
      /* (23) id_chain ::= ID */ yytestcase(yyruleno==23);
      /* (24) id_chain ::= id_chain DOT ID */ yytestcase(yyruleno==24);
      /* (25) id_list ::= ID */ yytestcase(yyruleno==25);
      /* (26) id_list ::= id_list COMMA ID */ yytestcase(yyruleno==26);
      /* (27) var_decl ::= var_typed_assigned_decl */ yytestcase(yyruleno==27);
      /* (28) var_decl ::= var_untyped_assigned_decl */ yytestcase(yyruleno==28);
      /* (29) var_decl ::= var_typed_unassigned_decl */ yytestcase(yyruleno==29);
      /* (30) var_type ::= id_chain */ yytestcase(yyruleno==30);
      /* (31) var_type ::= var_type LBRACKET var_type_list RBRACKET */ yytestcase(yyruleno==31);
      /* (32) var_type_list ::= var_type */ yytestcase(yyruleno==32);
      /* (33) var_type_list ::= var_type_list COMMA var_type */ yytestcase(yyruleno==33);
      /* (34) var_typed_assigned_decl ::= var_type var_untyped_assigned_decl */ yytestcase(yyruleno==34);
      /* (35) var_typed_unassigned_decl ::= var_type id_list */ yytestcase(yyruleno==35);
      /* (36) var_untyped_assigned_decl ::= id_list EQ value_list */ yytestcase(yyruleno==36);
      /* (37) value ::= KW_NULL */ yytestcase(yyruleno==37);
      /* (38) value ::= TOK_STRING */ yytestcase(yyruleno==38);
      /* (39) value ::= TOK_INT */ yytestcase(yyruleno==39);
      /* (40) value ::= TOK_ID */ yytestcase(yyruleno==40);
      /* (41) value ::= LPARENTHESES value RPARENTHESES */ yytestcase(yyruleno==41);
      /* (42) value ::= value PLUS value */ yytestcase(yyruleno==42);
      /* (43) value ::= value MINUS value */ yytestcase(yyruleno==43);
      /* (44) value ::= NOT value */ yytestcase(yyruleno==44);
      /* (45) value ::= value LPARENTHESES value_list RPARENTHESES */ yytestcase(yyruleno==45);
      /* (46) value_list ::= value */ yytestcase(yyruleno==46);
      /* (47) value_list ::= value_list COMMA value */ yytestcase(yyruleno==47);
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  MetaARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  MetaARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  MetaARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 10 "metaparser.y"

    fprintf(stderr, "Error parsing command\n");
#line 899 "metaparser.c"
  MetaARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  MetaARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  MetaARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "MetaAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Meta(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  MetaTOKENTYPE yyminor       /* The value for the token */
  MetaARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  MetaARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
