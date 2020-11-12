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
	set<int> termi;
	int __e;
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
	void check_token(string &token);	//���token�Ƿ������symbols�� �����������
	void get_generate();//���ļ���������ʽ
	void create_table();//��������ʽ��FIRST��FOLLOW�����������
	void handle_generate_raw();//��������ԭʼ����ʽ
	void get_next_token(string &s, int &cur);//�﷨������ ��ȡ�����ַ�������һ���ַ�
	void first_and_follow_set();//�������з��ս����FIRST��FOLLOW��
	void reconstruct_generate_raw();//����ݹ�����¹�������ʽ
	void handle_recursion();//������ݹ�
	void show_table_and_generate();//���Ŵ�����ǰ�������ʽ�ͷ�����
	
public:
	SyntacticAna(string &name);
	//���캯�� ����Ϊ�ļ��� ���캯������ɶ�������ʽ ������ݹ� ��FIRST��FOLLOW�� ��������� 
	//����Input�ַ�������
	void show_res();//����
	void show_errors();
	void solve();//���з��Ŵ�����

};