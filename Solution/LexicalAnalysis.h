#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>

#define BUFFER_SIZE 4096
using std::ifstream;
using std::ios;
using std::string;
using std::cout;
using std::stoi;
using std::stod;
using std::vector;
using std::pair;
using std::unordered_set;
using std::set;
class LexicalAna {
private:
	ifstream file;
	char C=0;
	string token;
	int state=0;
	int end = 0;	//whileѭ��������־
	int note_line = 0, note_lines = 0;		//�Ƿ���ʶ��ע���л�ע�Ϳ�״̬
	char str_token;//ʶ���ַ������õı�� �����Ż���˫����
	char buff1[BUFFER_SIZE+1], buff2[BUFFER_SIZE+1];		//����������
	int buff_status = -1,cur, letter_new_line = 0,tem_letter_new_line;
		//������״̬ �������±� ��ǰ�ַ�������λ��
	
	int letters = 0, lines = 0;//ͳ�����ַ��� ����
	int counts[4] = { 0 };//���ڼ��� id num ������ �ַ���
	vector<pair<string, string>> table;	//��������ʶ����Ķ�Ԫ��
	unordered_set<string> symbol_table;	//�����ʶ��
	vector<string> errors;		//���������Ϣ
	//������
	set<string> keys = { "auto","break","case","char","const","continue","default",
		"do","double","else","enum","extern","float","for","goto","if","int","long",
		"register","return","short","signed","sizeof","static","struct","switch",
		"typedef","union","unsigned","void","volatile","while","NULL"};
	void _getchar();
	void retract();
	inline bool is_letter() {
		return ((C >= 'a'&&C <= 'z') || (C >= 'A'&&C <= 'Z') || C=='_');
	}
	inline bool is_digit() {
		return C >= '0'&&C <= '9';
	}
	inline void cat() {
		token += C;
	}
	void error(string str);	//����
public:
	LexicalAna(string file_name) {	//���캯������Ϊ�ļ�·��
		buff1[BUFFER_SIZE] = buff2[BUFFER_SIZE] = '\0';
		file.open(file_name, ios::in);
	}
	bool open_success() {	//�����ļ��Ƿ�򿪳ɹ�
		return file.is_open();
	}
	void run();			//���дʷ�����
	void show_res();	//����ʷ��������
};