#pragma once
#include <fstream>
#include <ios>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <set>
using std::ifstream;
using std::string;
using std::unordered_map;
using std::pair;
using std::vector;
using std::cout;
using std::hash;
using std::set;
struct hashfunc
{
	template<typename T, typename U>
	size_t operator() (const pair<T, U> &i) const
	{
		return hash<T>()(i.first) ^ hash<U>()(i.second);
	}
};
class SyntacticAna {
private:
	ifstream in;		//读入文件流
	int generate_num=0;	//生成式的数量
	vector<string> generate_raw;	//记录原始生成式 消左递归后会改为消除左递归后的生成式
	int symbol_num = 0;		//符号的数量 包括终结符、非终结符、ε和$
	unordered_map<string, int> symbols;		//记录所有的符号与int的对应
	set<int> nonter;		//非终结符集合
	set<int> termi;			//终结符集合
	int __e;				//记录ε在symbols中对应的数 
	vector<string> symbols_hash;	//symbols中记录所有符号后 建立所有符号int到string的对应
	vector<pair<int, vector<int> > >  generate;		
	//格式化后所有生成式 pair中第一个int为生成式左边非终结符对应的int,vector<int>为生成式右面所有符号对应的int
	unordered_map<pair<int, int>, int,hashfunc> table;		
	//分析表 pair两个int表示栈顶符号和遇到的符号 第三个int是该情况下采用的生成式编号 int为-1表示synch
	vector<string> errors;	//记录所有错误信息
	vector< set<int>> first, follow;	//记录所有符号的first follow集 vector下标为某符号对应的int
	vector<int> stack_;		//使用vector模拟字符串识别过程中的栈
	int stack_cur;			//记录栈顶位置
	string input;			//读入的要识别的字符串 末尾没有$会自动补上
	int table_conflict = 0;//分析表是否存在问题
	inline void error(string message) {
		errors.push_back(message);
	}
	void check_token(string &token);	//检查token是否存在于symbols中 不存在则加入
	void get_generate();		//从文件读入生成式
	void create_table();		//根据生成式、FIRST、FOLLOW集构造分析表
	void handle_generate_raw();//处理读入的原始生成式
	void handle_recursion();//消除左递归
	void reconstruct_generate_raw();//消左递归后重新构造生成式
	void first_and_follow_set();//计算所有非终结符的FIRST、FOLLOW集
	void show_table_and_generate();//符号串分析前输出生成式和分析表
	void get_next_token(string &s, int &cur);//语法分析中 读取输入字符串的下一个字符
public:
	SyntacticAna(string &name);
	//构造函数 参数为文件名 构造函数中完成读入生成式 消除左递归 求FIRST、FOLLOW集 构造分析表 
	//读入Input字符串操作
	void show_res();//调试
	void show_errors();//输出所有错误
	void solve();//进行符号串分析

};