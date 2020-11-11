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
	ifstream in;
	int generate_num;	//����ʽ������
	vector<string> generate_raw;	//��¼ԭʼ����ʽ
	int symbol_num = 0;		//���ŵ�����
	unordered_map<string, int> symbols;		//��¼���еķ���
	set<int> nonter;		//���ս��
	vector<string> symbols_hash;
	vector<pair<int, vector<int> > >  generate;		//��ʽ����������ʽ--�����ִ������
	unordered_map<pair<int, int>, int,hashfunc> table;		//������
	vector<string> errors;
	vector< set<int>> first, follow;
	vector<int> stack_;
	int stack_cur;
	string input;

	inline void error(string message) {
		errors.push_back(message);
	}
	void check_token(string &token);
	void get_generate();
	void create_table();
	void handle_generate_raw();
	void get_next_token(string &s, int &cur);
	void first_and_follow_set();
	void dfs_first(int symbol, vector<int> &finished, vector<int> &has__e);
public:
	SyntacticAna(string &name);
	void show_res();
	void solve();

};