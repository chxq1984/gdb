%{
#include "Node.h"
#include "SqlGlobal.h"
#include "DML_gram.tab.h"

SqlGlobal* sg = SqlGlobal::getInstance();
%}

st              (select|SELECT|Select)
upt             (update|UPDATE|Update)
del             (delete|DELETE|Delete)
ist             (insert|INSERT|Insert)
val             (values|VALUES)
into            (into|INTO)
set             (set|SET)
natural         (natural|NATURAL)
join            (join|JOIN)
multi			(multi)
exec            (exec)
discard         (discard)


fm              (from|FROM|From)
order			(order|ORDER|Order)
by              (by|BY|By)
ortype          (desc|asc)            
wh              (where|WHERE|Where)
whsplit         (and|AND|or|OR|Or|And)
dis				(distinct)
aggret			(sum|max)
exit			(exit)

number          [-]?[0-9]+(\.[0-9]+)?
name            [_a-zA-Z][_0-9a-zA-Z()\.\*]*
whitespace      [ \n\t]

%%

"("			{
				return LF;
			}
			
")"			{
				return RF;
			}

{st}        {
                return ST;
            }

{fm}        {
                return FM;
            }

{wh}        {
                return WH;
            }
{ist}		{
				return IST;
			}
{upt}		{
				return UPT;
			}
{del}		{
				return DEL;
			}
{set}		{
				return SET;
			}
{val}		{
				return VAL;
			}
{into}		{
				return INTO;
			}
            
{whsplit}   {
                yylval.soperator = new Operator();
                yylval.soperator->opName = yytext;
                return WHSPLIT;
            }


"<"         {
                yylval.soperator = new Operator();
                yylval.soperator->opName = yytext;
                return T_LT;
            }

"<="        {
                yylval.soperator = new Operator();
                yylval.soperator->opName = yytext;
                return T_LE;
            }

">"         {
                yylval.soperator = new Operator();
                yylval.soperator->opName = yytext;
                return T_GT;
            }

">="        {
                yylval.soperator = new Operator();
                yylval.soperator->opName = yytext;
                return T_GE;
            }

"="         {
                yylval.soperator = new Operator();
                yylval.soperator->opName = yytext;
                return T_EQ;
            }

"!="        {
                yylval.soperator = new Operator();
                yylval.soperator->opName = yytext;
                return T_NE;
            }

"<>"        {
                yylval.soperator = new Operator();
                yylval.soperator->opName = yytext;
                return T_NE;
            }

"in"		{
                yylval.soperator = new Operator();
                yylval.soperator->opName = yytext;
                return IN;
			}


{whitespace}    ;


{order}    {
                return ORDER;
           }
           
{by}       {
                return BY;
           }
           
{ortype}   {
                yylval.text = new string(yytext);
                return ORTYPE;
           }
           
{dis}      {

				return DISTINCT;
		   }
		   
{aggret}	{
                yylval.text = new string(yytext);
                return AGGRET;
			}
			
{exit}		{
                sg->exit = true;
				return EXIT;
			}	
			
{natural}  {
				return NATURAL;
		   }
		   
{join}	   {
				return JOIN;
		   }	
			
{multi}		{
				return MULTI;
			}
{exec}		{
				return EXEC;
			}
{discard}	{
				return DISCARD;
			}

{name}		{
                yylval.text = new string(yytext);
                return NAME;
            }
            

{number}   {
                yylval.rNumber = new Number();
                yylval.rNumber->number = yytext;
                return NUMBER;
           }
           

[*/+\-=<>':;,.|&()]  {return yytext[0];}

.			;
 
%%
int yyerror(const char * format,...){
	printf("some error\n");
	return 1;
}
 
int yywrap(void)
{  
  return 1;  
} 