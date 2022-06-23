/*���ڿ���̨����ز���*/
#pragma once
#include <string>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
/*******************************************************
  �������ƣ�copts_setconsoletitle
  ��    �ܣ�����cmd���ڱ���
*******************************************************/
void copts_setconsoletitle(const char *title);

/*******************************************************
  �������ƣ�copts_fixedconsolesize
  ��    �ܣ����ر�������󻯰�ť����ֹ�߿��϶��ı䴰�ڴ�С
*******************************************************/
void copts_fixconsolesize(void);

/*******************************************************
  �������ƣ�copts_cls
  ��    �ܣ�����
*******************************************************/
void copts_cls(void);

/*******************************************************
  �������ƣ�copts_gotoxy
  ��    �ܣ�������ƶ���ָ��λ��
  ���������const int X       ��X�����꣨�У�
			const int Y       ��Y�����꣨�У�
  ˵    ������Ļ���Ͻ�����Ϊ(0,0)����cmd���ڵĴ�Сδ������������£�Win10Ϊ��
			����x�ᣬ��Ӧ��(0-119)
			����y�ᣬ��Ӧ��(0-29)
*******************************************************/
void copts_gotoxy(const int X, const int Y);

/*******************************************************
  �������ƣ�copts_printxy
  ��    �ܣ���ָ��λ�����ָ����ɫ�ַ���
  ���������const int &X��const int &Y ����
         const string &str ����ַ���
*******************************************************/
void copts_printxy(const int &X,const int &Y,std::string str);

/*******************************************************
  �������ƣ�copts_printspace
  ��    �ܣ���ָ��λ������ո�
  ���������const int &X��const int &Y ����
         const int &rpt ������������ȣ�
*******************************************************/
void copts_printspace(const int &X,const int &Y,const int &rpt);

/*******************************************************
  �������ƣ�copts_printline
  ��    �ܣ���ָ��λ�����һ����
  ���������const int &X��const int &Y ����
         const int &rpt ������������ȣ�
*******************************************************/
void copts_printline(const int &X,const int &Y,const int &rpt);

/*******************************************************
  �������ƣ�copts_setconsoleborder
  ��    �ܣ��ı�cmd���ڵĴ�С���������Ĵ�С
  ���������const int cols     ���µ�����
		   const int lines        ���µ�����
		   const int buffer_cols  ���µĻ���������
		   const int buffer_lines ���µĻ���������
  ˵    �������������û������������ô��ڴ�С��
*******************************************************/
void copts_setconsoleborder(int set_cols, int set_lines, int set_buffer_cols, int set_buffer_lines);

/*******************************************************
  �������ƣ�copts_hidecursor
  ��    �ܣ����ع��
*******************************************************/
void copts_hidecursor();

/*******************************************************
  �������ƣ�copts_hidecursor
  ��    �ܣ���ʾ��꣨���ߣ�
*******************************************************/
void copts_showcursor();
