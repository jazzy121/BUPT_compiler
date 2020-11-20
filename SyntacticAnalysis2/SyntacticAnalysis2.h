#pragma once
#include <fstream>
#include <ios>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <set>
#include <queue>
using std::ifstream;
using std::string;
using std::unordered_map;
using std::pair;
using std::vector;
using std::cout;
using std::hash;
using std::set;
using std::queue;
struct hashfunc
{
	template<typename T, typename U>
	size_t operator() (const pair<T, U> &i) const
	{
		return hash<T>()(i.first) ^ hash<U>()(i.second);
	}
};

class SyntacticAna2 {
private:
	ifstream in;		//�����ļ���
	int generate_num = 0;	//����ʽ������
	vector<string> generate_raw;	//��¼ԭʼ����ʽ ����ݹ����Ϊ������ݹ�������ʽ
	int symbol_num = 0;		//���ŵ����� �����ս�������ս�����ź�$
	unordered_map<string, int> symbols;		//��¼���еķ�����int�Ķ�Ӧ
	set<int> nonter;		//���ս������
	set<int> termi;			//�ս������
	int __e,__$;				//��¼����symbols�ж�Ӧ���� 
	vector<string> symbols_hash;	//symbols�м�¼���з��ź� �������з���int��string�Ķ�Ӧ
	vector<pair<int, vector<int> > >  generate;
	//��ʽ������������ʽ pair�е�һ��intΪ����ʽ��߷��ս����Ӧ��int,vector<int>Ϊ����ʽ�������з��Ŷ�Ӧ��int
	unordered_map<pair<int, int>,pair< int,int>, hashfunc> table;
	//������ pair����int��ʾջ�����ź������ķ��� ������intΪģʽ 1S 2R 3goto 4ACC���ĸ�����ʽ��״̬ intΪ-1��ʾsynch
	vector<string> errors;	//��¼���д�����Ϣ
	vector< set<int>> first, follow;	//��¼���з��ŵ�first follow�� vector�±�Ϊĳ���Ŷ�Ӧ��int
	vector<int> stack_;		//ʹ��vectorģ���ַ���ʶ������е�ջ
	int stack_cur;			//��¼ջ��λ��
	string input;			//�����Ҫʶ����ַ��� ĩβû��$���Զ�����
	vector<vector<pair<vector<int>, set<int> > > >  dfa;	
	//����ÿһ��Ԫ�ض���һ����Ŀ�� ��Ŀ����ÿһ��Ԫ�ض���һ����Ŀ pair��fisrtΪһ��vector<int>
	//ΪLR(0)��Ŀÿ���ַ���Ӧ������ ����.Ϊ-1 pair��second������ǰ���ַ����е��ַ��ķ���
	unordered_map<pair<int,int>,int,hashfunc> relation;	//������Ŀ����ת�Ʒ�ʽ pairΪ��ǰ��Ŀ�Ͷ����ķ��� ������intΪת�Ժ����Ŀ�����
	int table_conflict = 0;
	inline void error(string message) {
		errors.push_back(message);
	}
	void check_token(string &token);	//���token�Ƿ������symbols�� �����������
	void get_generate();		//���ļ���������ʽ
	void create_dfa();
	void create_table();		//��������ʽ��FIRST��FOLLOW�����������
	void handle_generate_raw();//��������ԭʼ����ʽ
	void reconstruct_generate_raw();//����ݹ�����¹�������ʽ
	void first_and_follow_set();//�������з��ս����FIRST��FOLLOW��
	void show_table_and_generate();//���Ŵ�����ǰ�������ʽ�ͷ�����
	void get_next_token(string &s, int &cur);//�﷨������ ��ȡ�����ַ�������һ���ַ�
	void out_dfa(vector<pair<vector<int>, set<int> > > &tem);	//���һ����Ŀ������Ϣ
	void closure(vector<pair<vector<int>, set<int> > > &closure);	//���㵱ǰ��Ŀ���ıհ�
	int closure_check(pair<vector<int>, set<int>> &tem, vector<pair<vector<int>, set<int> > > &closure); 
	//��鵱ǰԪ���Ƿ���հ���Ԫ���ظ� ����ֵΪ0-size������Ժϲ� -1�ظ� -2�µ�
	void generate_to_vector(pair<vector<int>, set<int>> &tem,int i);
	int check_vector_vector(vector<pair<vector<int>, set<int> > > &tem);//-1���� 0-n�ظ� 
public:
	SyntacticAna2(string &name);
	//���캯�� ����Ϊ�ļ��� ���캯������ɶ�������ʽ ������ݹ� ��FIRST��FOLLOW�� ��������� 
	//����Input�ַ�������
	void show_res();//����
	void show_errors();//������д���
	void solve();//���з��Ŵ�����
};