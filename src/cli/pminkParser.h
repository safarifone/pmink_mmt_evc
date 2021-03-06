/** \file
 *  This C header file was generated by $ANTLR version 3.2 Sep 23, 2009 12:02:23
 *
 *     -  From the grammar source file : /secure/pmink/src/cli/pmink.g
 *     -                            On : 2012-06-25 21:59:48
 *     -                for the parser : pminkParserParser *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The parser pminkParser has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 * 
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef ppminkParser, which is returned from a call to pminkParserNew().
 *
 * The methods in ppminkParser are  as follows:
 *
 *  - pminkParser_input_return      ppminkParser->input(ppminkParser)
 *  - pminkParser_typesDefinition_return      ppminkParser->typesDefinition(ppminkParser)
 *  - pminkParser_typeItem_return      ppminkParser->typeItem(ppminkParser)
 *  - pminkParser_configDefinition_return      ppminkParser->configDefinition(ppminkParser)
 *  - pminkParser_configDef_return      ppminkParser->configDef(ppminkParser)
 *  - pminkParser_configBlock_return      ppminkParser->configBlock(ppminkParser)
 *  - pminkParser_configItem_return      ppminkParser->configItem(ppminkParser)
 *  - pminkParser_itemDesc_return      ppminkParser->itemDesc(ppminkParser)
 *  - pminkParser_itemType_return      ppminkParser->itemType(ppminkParser)
 *  - pminkParser_notifiedDaemon_return      ppminkParser->notifiedDaemon(ppminkParser)
 *  - pminkParser_lineParser_return      ppminkParser->lineParser(ppminkParser)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD licence"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_pminkParser_H
#define _pminkParser_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */
 
#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct pminkParser_Ctx_struct pminkParser, * ppminkParser;



#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule 
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif

/* ========================
 * BACKTRACKING IS ENABLED
 * ========================
 */
typedef struct pminkParser_input_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    pminkParser_input_return;

typedef struct pminkParser_typesDefinition_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    pminkParser_typesDefinition_return;

typedef struct pminkParser_typeItem_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    pminkParser_typeItem_return;

typedef struct pminkParser_configDefinition_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    pminkParser_configDefinition_return;

typedef struct pminkParser_configDef_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    pminkParser_configDef_return;

typedef struct pminkParser_configBlock_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    pminkParser_configBlock_return;

typedef struct pminkParser_configItem_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    pminkParser_configItem_return;

typedef struct pminkParser_itemDesc_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    pminkParser_itemDesc_return;

typedef struct pminkParser_itemType_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    pminkParser_itemType_return;

typedef struct pminkParser_notifiedDaemon_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    pminkParser_notifiedDaemon_return;

typedef struct pminkParser_lineParser_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    pminkParser_lineParser_return;



/** Context tracking structure for pminkParser
 */
struct pminkParser_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_PARSER   pParser;


     pminkParser_input_return (*input)	(struct pminkParser_Ctx_struct * ctx);
     pminkParser_typesDefinition_return (*typesDefinition)	(struct pminkParser_Ctx_struct * ctx);
     pminkParser_typeItem_return (*typeItem)	(struct pminkParser_Ctx_struct * ctx);
     pminkParser_configDefinition_return (*configDefinition)	(struct pminkParser_Ctx_struct * ctx);
     pminkParser_configDef_return (*configDef)	(struct pminkParser_Ctx_struct * ctx);
     pminkParser_configBlock_return (*configBlock)	(struct pminkParser_Ctx_struct * ctx);
     pminkParser_configItem_return (*configItem)	(struct pminkParser_Ctx_struct * ctx);
     pminkParser_itemDesc_return (*itemDesc)	(struct pminkParser_Ctx_struct * ctx);
     pminkParser_itemType_return (*itemType)	(struct pminkParser_Ctx_struct * ctx);
     pminkParser_notifiedDaemon_return (*notifiedDaemon)	(struct pminkParser_Ctx_struct * ctx);
     pminkParser_lineParser_return (*lineParser)	(struct pminkParser_Ctx_struct * ctx);
    // Delegated rules
    const char * (*getGrammarFileName)();
    void	    (*free)   (struct pminkParser_Ctx_struct * ctx);
    /* @headerFile.members() */
    pANTLR3_BASE_TREE_ADAPTOR	adaptor;
    pANTLR3_VECTOR_FACTORY		vectors;
    /* End @headerFile.members() */
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API ppminkParser pminkParserNew         (pANTLR3_COMMON_TOKEN_STREAM instream);
ANTLR3_API ppminkParser pminkParserNewSSD      (pANTLR3_COMMON_TOKEN_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the parser will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif 
#define NOTIFIED_DAEMON      125
#define MODULE_ID      104
#define NODE_COMPONENT      117
#define SEQUENCE_LITERAL      36
#define STAR      5
#define IDENTIFIER_NODE      107
#define LETTER      143
#define RELATIVE_OID_LITERAL      90
#define REGEX      131
#define ABSENT_LITERAL      57
#define DEFINITION_NODE      110
#define EOF      -1
#define AUTOMATIC_LITERAL      75
#define DOUBLE_DOT      11
#define DEFAULT_LITERAL      38
#define ASSIGN_OP      6
#define IDENTIFIER_LITERAL      89
#define BIT_LITERAL      32
#define REAL_LITERAL      29
#define PATTERN_LITERAL      58
#define OCTET_LITERAL      34
#define R_PARAN      26
#define TRUE_LITERAL      8
#define APOSTROPHE      13
#define CHOICE_LITERAL      82
#define COMMENT      100
#define FALSE_SMALL_LITERAL      20
#define APPLICATION_LITERAL      84
#define TYPE_ROOT      128
#define OPTIONAL_LITERAL      37
#define LESS_THAN_SLASH      17
#define ITEM_TYPE      123
#define LINE_COMMENT      138
#define IMPLICIT_LITERAL      74
#define ITEM_ID      124
#define NUMBER      133
#define L_BRACE      22
#define ELLIPSIS      12
#define CHARACTER_LITERAL      91
#define POWER      45
#define NULL_LITERAL      35
#define SEMI_COLON      67
#define DEFINITIONS_NODE      106
#define TYPE_ITEM      127
#define UNION_LITERAL      47
#define PLUS_INFINITY_LITERAL      30
#define ABSTRACT_SYNTAX_LITERAL      60
#define EXCEPT_LITERAL      44
#define INSTANCE_LITERAL      66
#define COMPONENT_LITERAL      55
#define CONFIG_LITERAL      101
#define END_LITERAL      78
#define ENUMERATED_LITERAL      28
#define INCLUDES_LITERAL      49
#define WS      136
#define BSTRING      139
#define EMBEDDED_LITERAL      86
#define CLASS_LITERAL      61
#define DOUBLE_L_BRACKET      79
#define SCRIPT_LITERAL      97
#define SL_COMMENT      146
#define PTRN_LITERAL      99
#define LESS_THAN      15
#define JavaIDDigit      144
#define SYNTAX_LITERAL      63
#define TYPES_LITERAL      102
#define EXPORTS_LITERAL      69
#define SET_LITERAL      41
#define CSTRING      130
#define IMPORTS_NODE      112
#define BEGIN_LITERAL      77
#define ALL_LITERAL      43
#define EscapeSequence      142
#define METHOD_LITERAL      98
#define ITEM_DESC      126
#define L_BRACKET      64
#define CONFIG_ROOT      120
#define TAG_DESCRIPTOR      115
#define MODULE_VERSION      105
#define NODE_INFO      113
#define TAGS_LITERAL      73
#define Exponent      137
#define FALSE_LITERAL      9
#define PRESENT_LITERAL      56
#define DEFINITIONS_LITERAL      76
#define EXTENSIBILITY_LITERAL      70
#define OBJECT_LITERAL      88
#define EXPLICIT_LITERAL      72
#define NODE_NAME      119
#define COMPONENTS_LITERAL      39
#define EXTENSTIONENDMARKER      134
#define ML_COMMENT      145
#define TYPE_IDENTIFIER_LITERAL      59
#define A_ROND_DOT      94
#define COMMA      24
#define TRUE_SMALL_LITERAL      19
#define IDENTIFIER      132
#define ENCODED_LITERAL      95
#define BY_LITERAL      93
#define PRIVATE_LITERAL      85
#define PIPE      46
#define A_ROND      4
#define DIGIT      135
#define DOT      10
#define TAG_DEFINITIONS      116
#define L_PARAN      25
#define TYPE_NODE      109
#define UNIQUE_LITERAL      62
#define UNIVERSAL_LITERAL      83
#define MINUS_INFINITY_LITERAL      31
#define MIN_LITERAL      50
#define CONST_LITERAL      96
#define GREATER_THAN      16
#define LINE_ROOT      129
#define HSTRING      141
#define WITH_LITERAL      54
#define IMPORTS_LITERAL      68
#define AMPERSAND      14
#define R_BRACE      23
#define SIZE_LITERAL      52
#define MINUS      27
#define R_BRACKET      65
#define IMPLIED_LITERAL      71
#define FROM_LITERAL      53
#define BOOLEAN_LITERAL      7
#define COLON      81
#define PDV_LITERAL      87
#define EXPORTS_NODE      111
#define SHASH_GREATER_THEN      18
#define CONFIG_ITEM      121
#define TAG_SPECIFIC      118
#define VALUE_NODE      108
#define CONTAINING_LITERAL      33
#define EXCLAM      42
#define BODY_NODE      114
#define CONSTRAINED_LITERAL      92
#define IA5_STRING_LITERAL      21
#define CONFIG_BLOCK      122
#define INTERSECTION_LITERAL      48
#define MODULE_ROOT      103
#define OF_LITERAL      40
#define MAX_LITERAL      51
#define DOUBLE_R_BRACKET      80
#define HEXDIGIT      140
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for pminkParser
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
