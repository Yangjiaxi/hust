LETTER		[a-zA-Z_]
DIGIT		[0-9]

INTEGER		{DIGIT}+[lLuU]?
FLOAT		({DIGIT}*\.{DIGIT}+)|({DIGIT}+\.)[lLuU]?
CHAR		'([^'\\\n]|\\.){0,1}'
STRING		\"(\\.|[^"\\])*\"
IDENTIFIER	{LETTER}({DIGIT}|{LETTER})*

NEWLINE     \n|(\r\n)
WHITESPACE  [ \t\v\f]

%{
    #include "color.h"
	int n_chars = 0, n_words = 0, n_lines = 0;
	int current_line = 1;
	#define YY_USER_ACTION n_words++; n_chars += yyleng;

	#define ACTION(NAME) printf("[" BOLD_CYAN "%3d" RESET_COLOR "]" RED " | " RESET_COLOR BLUE #NAME RESET_COLOR"\n", current_line);
    #define ACTION_ARG(NAME) printf("[" BOLD_CYAN "%3d" RESET_COLOR "]" RED " | " RESET_COLOR BLUE #NAME RESET_COLOR " [" BOLD_GREEN "%s" RESET_COLOR"]\n" RESET_COLOR, current_line, yytext);
	
%}

%option nodefault
%option noyywrap

%x COMMENT_BLOCK
%x COMMENT_LINE

%%

"/*"                    { BEGIN(COMMENT_BLOCK); }
<COMMENT_BLOCK>"*/"     { BEGIN(INITIAL); }
<COMMENT_BLOCK>\n       { current_line++; }
<COMMENT_BLOCK>.        { }
<COMMENT_BLOCK><<EOF>>  { }

\/\/(.*)    { current_line++; }

{INTEGER}       { ACTION_ARG(LITERAL_INTEGER); }
{FLOAT}         { ACTION_ARG(LITERAL_FLOAT); }
{CHAR}          { ACTION_ARG(LITERAL_CHAR); }
{STRING}        { ACTION_ARG(LITERAL_STRING); }

"int"|"float"|"long"|"char"|"double"|"void"|"short" { ACTION_ARG(KEYWORD_TYPE); }

"return"    { ACTION(KEYWORD_RETURN); }
"break"     { ACTION(KEYWORD_BREAK); }
"continue"  { ACTION(KEYWORD_CONTINUE); }
"for"       { ACTION(KEYWORD_FOR); }
"if"        { ACTION(KEYWORD_IF); }
"else"      { ACTION(KEYWORD_ELSE); }
"while"     { ACTION(KEYWORD_WHILE); }
"do"        { ACTION(KEYWORD_DO); }
"switch"    { ACTION(KEYWORD_SWITCH); }
"case"      { ACTION(KEYWORD_CASE); }
"default"   { ACTION(KEYWORD_DEFAULT); }

{IDENTIFIER}    { ACTION_ARG(IDENTIFIER); }

"+="|"-="|"*="|"/="|"%="|"&="|"|="|"^="|"<<="|">>=" { ACTION_ARG(OPERATOR_COMPOUND_ASSIGNMENT); }

"++"    { ACTION_ARG(OPERATOR_INCREMENT); }
"--"    { ACTION_ARG(OPERATOR_DECREMENT); }

">"|"<"|">="|"<="|"=="|"!=" { ACTION_ARG(OPERATOR_RELATIONAL); }

"="     { ACTION_ARG(OPERATOR_ASSIGNMENT);  }
">>"    { ACTION_ARG(OPERATOR_SHIFT_RIGHT); }
"<<"    { ACTION_ARG(OPERATOR_SHIFT_LEFT); }
"+"     { ACTION_ARG(OPERATOR_PLUS);  }
"-"     { ACTION_ARG(OPERATOR_MINUS);  }
"*"     { ACTION_ARG(OPERATOR_MULTIPLY);  }
"/"     { ACTION_ARG(OPERATOR_DIVIDE);  }
"%"     { ACTION_ARG(OPERATOR_MODULUS);  }
"&&"    { ACTION_ARG(OPERATOR_LOGICAL_AND); }
"&"     { ACTION_ARG(OPERATOR_BITWISE_AND); }
"||"    { ACTION_ARG(OPERATOR_LOGICAL_OR); }
"|"     { ACTION_ARG(OPERATOR_BITWISE_OR); }
"^"     { ACTION_ARG(OPERATOR_BITWISE_XOR); }
"~"     { ACTION_ARG(OPERATOR_BITWISE_NOT); }
"!"     { ACTION_ARG(OPERATOR_LOGICAL_NOT); }

"?"     { ACTION(OPERATOR_QUESTION); }
":"     { ACTION(PUNCTUATOR_COLON); }
"("     { ACTION(PUNCTUATOR_PARENTHESIS_LEFT); }
")"     { ACTION(PUNCTUATOR_PARENTHESIS_RIGHT); }
"{"     { ACTION(PUNCTUATOR_BRACE_LEFT); }
"}"     { ACTION(PUNCTUATOR_BRACE_RIGHT); }
"["     { ACTION(PUNCTUATOR_BRACKET_LEFT); }
"]"     { ACTION(PUNCTUATOR_BRACKET_RIGHT); }
";"     { ACTION(PUNCTUATOR_SEMICOLON); }
","     { ACTION(PUNCTUATOR_COMMA); }

{NEWLINE}       { current_line++; }
{WHITESPACE}    {}

.	{ ACTION_ARG(ERROR); }

%%

int main()
{
	yylex();
	printf("\t# chars: %d\n", n_chars);
	printf("\t# words: %d\n", n_words);
	printf("\t# lines: %d\n", n_lines);
	return 0;
}
