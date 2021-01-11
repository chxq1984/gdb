%{
#include "Node.h"
#include "DML_gram.tab.h"

extern int yylex();
extern int yyerror(const char * format,...);

struct yy_buffer_state;
#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif
extern void yy_switch_to_buffer (YY_BUFFER_STATE new_buffer);
extern YY_BUFFER_STATE yy_scan_string ( const char *yy_str  );

%}
 
%union
{
	Attribute *attribute;
	OrderNode *orderNode;
	Relation *relation;
	Operator *soperator;
	SelList	*selList;
	FromList *fromList;
	Condition *condision;
	OrderList *orderList;
	GroupList *groupList;
	Query *query;
	Number* rNumber;
	ParaString* pString;
	
	Name* name;
    vector<Name*>* nameList;
    
	string* text;
	int type;
	
	Insert* insert;
	vector<string>* values;
	
	Delete* del;
	
	Update* upd;
	string* attr_index[2];
	map<string, string>* attr_indexs;

	PhyPlanNode* phyNode;
	vector<PhyPlanNode*>* phyNodes; 

	NodeStorage* nodestorage;
}
 
%token LF RF
%token ST FM WH UPT DEL IST VAL INTO SET
%token WHSPLIT T_LT T_LE T_GT T_GE T_EQ T_NE T_NE IN
%token ORDER BY ORTYPE
%token DISTINCT AGGRET
%token EXIT
%token NAME NUMBER PARA_STRING
%token SUBQUERY
%token NATURAL JOIN
%token MULTI EXEC DISCARD

%type<soperator> WHSPLIT T_LT T_LE T_GT T_GE T_EQ T_NE IN
%type<text> ORTYPE AGGRET NAME 
%type<rNumber> NUMBER

%type<query> stmt
%type<soperator> op
%type<selList> st_list st_nodes
%type<fromList> fm_list
%type<condision> wh_list whname whname_list
%type<orderList> order_list order
%type<nameList> name_list
%type<orderNode> order_node
%type<name> table_attr attr_name
%type<pString> para_string
%type<text> insert_value
%type<values> value_list
%type<attr_index> set_value
%type<attr_indexs>set_list
%type<phyNode> delete query update insert dml
%type<phyNodes> dmls
%type<nodestorage> whvalue

%%

command
	: utility
	| dml ';'
	{
		YYACCEPT;
	}
	| dowork ';'
	{
		YYACCEPT;
	}
	| cancelwork ';'
	{
		YYACCEPT;
	}
	;

utility
	: exit
	;
	
dowork
	: MULTI dmls EXEC
	{
		//dmls内即为各物理计划树根节点
		if(PhysicalPlan::canFinish(*$2))
		{
			//说明可以完成事务
			for (PhyPlanNode* root : *$2) 
			{
				//调用执行函数
			}
		}
		else
		{
			cout<<"违反事务"<<endl;
		}
	}
	;

cancelwork
	: MULTI dmls DISCARD
	{
		cout<<"已取消事务"<<endl;
	}
	;

dmls
	: dml
	{	
		$$ = new vector<PhyPlanNode*>;
		$$->push_back($1);
	}
	| dml dmls
	{
		$2->push_back($1);
		$$ = $2;
	}
	;

dml
	: query
	{
		//$$即为物理计划根节点,此处调用执行函数即可
		$$ = $1;
	}
	| delete
	{
		$$ = $1;
	}
	| update
	{
		$$ = $1;
	}
	| insert
	{
		$$ = $1;
	}
	;

exit
	: EXIT ';'
	{
		YYACCEPT;
	}
	;

query
	: stmt
	{
		Query* query = $1;
		query->showInfo();

		
		SqlGrammer sqlgrammer;
		sqlgrammer.root = query->transform2Grammer();
		cout << "-------------------------------"<<endl;
		sqlgrammer.showInfo();
		sqlgrammer.optimiza();
		cout << "-------------------------------"<<endl;

		
		PhysicalPlan physicalPlan;
		physicalPlan.root = sqlgrammer.transform2PhysicPlan();
		physicalPlan.showPlan();
		
		$$ = physicalPlan.root;

		
		cout<<endl;
		//YYACCEPT;
	}
	;

delete
	: DEL FM NAME wh_list
	{
		Delete * del = new Delete();
		del->tableName = *$3;
		del->condition = $4;
		del->showInfo();
		
		//$$ = new Delete();
		//$$->tableName = $3;
		//$$->condition = $4;
		//$$->showInfo();
		
		SqlGrammer sqlgrammer;
		//sqlgrammer.root = $$->transform2Grammer();
		sqlgrammer.root = del->transform2Grammer();
		cout << "-------------------------------"<<endl;
		sqlgrammer.showInfo();
		cout << "-------------------------------"<<endl;
		
		PhysicalPlan physicalPlan;
		physicalPlan.root = sqlgrammer.transform2PhysicPlan();
		physicalPlan.showPlan();
		
		$$ = physicalPlan.root;
		
		cout<<endl;
		//YYACCEPT;
	}
	;

update
	: UPT NAME SET set_list wh_list
	{
		Update* upt = new Update();
		upt->tableName = *$2;
		upt->attr_indexs = *$4;
		upt->condition = $5;
		upt->showInfo();
		
		//$$ = new Update();
		//$$->tableName = $2;
		//$$->attr_indexs = $4;
		//$$->condition = $5;
		//$$->showInfo();
		
		SqlGrammer sqlgrammer;
		//sqlgrammer.root = $$->transform2Grammer();
		sqlgrammer.root = upt->transform2Grammer();
		cout << "-------------------------------"<<endl;
		sqlgrammer.showInfo();
		cout << "-------------------------------"<<endl;
		
		PhysicalPlan physicalPlan;
		physicalPlan.root = sqlgrammer.transform2PhysicPlan();
		physicalPlan.showPlan();
		
		$$ = physicalPlan.root;
		
		cout<<endl;
		//YYACCEPT;
	}
	;

stmt
	: st_list fm_list
	{
		$$ = new Query();
		$$->selList = $1;
		$$->fromList = $2;
	}
	| stmt wh_list
	{
		$1->condition = $2;
		$$ = $1;
	}
	| stmt order
	{
		$1->orderList = $2;
		$$ = $1;
	}
	;


st_list
	: ST st_nodes
	{
		$$ = $2;
	}
	;

st_nodes
	: name_list
	{
		$$ = new SelList();
		for(int m=0;m<$1->size();m++){
			Attribute* attr = new Attribute();
			Name* name = $1->at(m);
			attr->setName(name);
			$$->addAttribute(attr);
		}
	}
	| '*'
	{
		$$ = new SelList();
		Attribute* attr = new Attribute();
		attr->attrName = "*";
		$$->addAttribute(attr);
	}
	| DISTINCT st_nodes
	{
        cout<<"distinct，暂不进行处理"<<endl;
	}
	;


fm_list
	: FM name_list
	{
		$$ = new FromList();
		for(int m=0;m<$2->size();m++){
			Relation* rl = new Relation();
			rl->relationName = $2->at(m)->attrName;
			rl->alias = $2->at(m)->alias;
			$$->addNode(rl);
		}
	}
	| FM LF stmt RF
	{
        cout<<"子查询，暂不进行处理"<<endl;
	}
	;


wh_list
	: WH whname_list
	{
		$$ = $2;
	}
	;


whname_list
	: whname
	{
        //可能有多个condition
		$$ = $1;
	}
	| whname WHSPLIT whname_list 
	{
		Condition* condition = new Condition();
		condition->lCnode = $3;

		condition->soperator = $2;
		condition->rCnode = $1;
		$$ = condition;
	}
	;

whname
	: table_attr op whvalue
	{
        //【】op【】:a=b
		Condition* condition = new Condition();
		$$ = condition;
		Attribute* lattr = new Attribute();
		lattr->setName($1);
		condition->Lattr = lattr;

		int ttype = $3->type;
		if(ttype == NUMBER){
            
			condition->rNumber = $3->rNumber;
            
		}else if(ttype == PARA_STRING){
			
			condition->pString = $3->pString;
			
		}else if(ttype == NAME){

			Attribute* rattr = new Attribute();
			rattr->setName($3->name);
			condition->Rattr = rattr;
            
		}else if(ttype == SUBQUERY){
            //子查询
            condition->query = $3->query;
		}
		condition->soperator = $2;
	}
	;


whvalue
	: table_attr
	{
        //where a=【】,可为表名,数字，子查询
		$$ = new NodeStorage();
		$$->name = $1;
		$$->type = NAME;
	}
	| NUMBER
	{
		$$ = new NodeStorage();
		$$->rNumber = $1;
		$$->type = NUMBER;
	}
	| LF stmt RF
	{
		$$ = new NodeStorage();
		$$->query = $2;
		$$->type = SUBQUERY;

	}
	| para_string
	{
		$$ = new NodeStorage();
		$$->pString = $1;
		$$->type = PARA_STRING;
	}
	;

order
	: ORDER BY order_list
	{
		$$ = $3;
	}
	;

order_list
	: order_node
	{
		//可能有多个排序节点
		$$ = new OrderList();
		$$->addOrderNode($1);
	}
	| order_node ',' order_list	
	{
		$3->addOrderNode($1);
		$$ = $3;
	}
	;

order_node
	: attr_name
	{
		//排序节点,可带rule也可不带
		$$ = new OrderNode();
		$$->attr.setName($1->attrName,$1->tableName);
	}
	| attr_name ORTYPE
	{
		$$ = new OrderNode();
		$$->attr.setName($1->attrName,$1->tableName);
		$$->rule = *$2;
	}
	;

name_list
   : table_attr
   {
		//名字列表
		$$ = new vector<Name*>;
   		$$->push_back($1);
   }
   | table_attr ',' name_list 
   {
		$3->push_back($1);
   		$$ = $3;
   } 
   | table_attr NATURAL JOIN name_list
   {
		Name *name = new Name();
		name->attrName = "@natural@";//@natural@作为指示符
        $4->push_back(name);
        $4->push_back($1);
        $$ = $4;
   }
   ;

table_attr
	: attr_name
	{
		$$ = $1;
	}
	| AGGRET LF attr_name RF
	{
		Name* name = $3;
		name->aggFunc = *$1;
		$$ = name;
	}
	| table_attr NAME
	{
		Name* name = $1;
		name->alias = *$2;
		$$ = name;
	}
	;

attr_name
	: NAME
	{
		Name* name = new Name();
		name->attrName = *$1;
		$$ = name;
	}
	| NAME '.' NAME
	{
		Name* name = new Name();
		name->tableName = *$1;
		name->attrName = *$3;

		$$ = name;
	}
	;
	
insert
	: IST INTO NAME VAL LF value_list RF
	{
		Insert * insert = new Insert();
		insert->attributes = *$6;
		insert->tableName = *$3;
		insert->showInfo();
		
		SqlGrammer sqlgrammer;
		sqlgrammer.root = insert->transform2Grammer();
		cout << "-------------------------------"<<endl;
		sqlgrammer.showInfo();
		cout << "-------------------------------"<<endl;
		
		PhysicalPlan physicalPlan;
		physicalPlan.root = sqlgrammer.transform2PhysicPlan();
		physicalPlan.showPlan();
		
		$$ = physicalPlan.root;

		cout<<endl;
	}
	;

value_list
	: insert_value
	{
		$$ = new vector<string>;
		$$->push_back(*$1);
	}
	| insert_value ',' value_list
	{
		$3->push_back(*$1);
		$$ = $3;
	}
	;

set_list
	: set_value
	{
		$$ = new map<string,string>;
		string **tmp = $1;
		$$->insert(pair<string, string>(*tmp[0], *tmp[1]));
	}
	| set_value ',' set_list
	{
		string **tmp = $1;
		$3->insert(pair<string,string>(*tmp[0],*tmp[1]));
		$$ = $3;
	}
	;

set_value
	: NAME T_EQ insert_value
	{
		string** tmp = $$;
		tmp[0] = $1;
		tmp[1] = $3;
	}
	;  
	
insert_value
	: para_string
	{
		$$ = &$1->parameter;
	}
	| NUMBER
	{
		$$ = &$1->number;
	}
	;

para_string
	: '\'' NAME '\''
	{
		ParaString* pstring = new ParaString();
		pstring->parameter = "\'" + *$2 +"\'";
        $$ = pstring;
	}
	;

op
	: T_LT
	{
		$$ = $1;
	}
	| T_LE
	{
		$$ = $1;
	}
	| T_GT
	{
		$$ = $1;
	}
	| T_GE
	{
		$$ = $1;
	}
	| T_EQ
	{
		$$ = $1;
	}
	| T_NE
	{
		$$ = $1;
	}
	| IN
	{
		$$ = $1;
	}
	;
 
%%

int parser_dml_sql(string sql){

	yy_switch_to_buffer(yy_scan_string(sql.c_str()));
	if(yyparse())
		return -1;
	else{
		return 1;
	}
}

string getInputSql(){
	//获取输入的sql语句
	string sql;
	getline(cin, sql);
	while (sql.back() != ';') {
		string tmp;
		getline(cin, tmp);
		sql += " " + tmp;
	}
	return sql;
}