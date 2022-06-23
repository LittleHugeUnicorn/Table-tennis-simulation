#include "cmd_opts.h"
using namespace std;

static const HANDLE __hout = GetStdHandle(STD_OUTPUT_HANDLE);		//ȡ��׼����豸��Ӧ�ľ��
static const HANDLE __hin  = GetStdHandle(STD_INPUT_HANDLE);		//ȡ��׼�����豸��Ӧ�ľ��

void copts_setconsoletitle(const char *title)
{
	SetConsoleTitleA(title);
}
void copts_cls(void){
    system("cls");
}
void copts_fixconsolesize(void){
    SetWindowLongPtrA(
        GetConsoleWindow(),
        GWL_STYLE,
        GetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE) 
        & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX );
}
void copts_gotoxy(const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(__hout, coord);
}
void copts_printxy(const int &X,const int &Y,string str)
{
    copts_gotoxy(X,Y);
    cout<<str;
}
void copts_printspace(const int &X,const int &Y,const int &rpt)
{
    copts_gotoxy(X,Y);
    for(int i=1;i<=rpt;i++) cout<<' ';
}
void copts_printline(const int &X,const int &Y,const int &rpt)
{
    copts_gotoxy(X,Y);
    for(int i=1;i<=rpt;i++) cout<<'-';
}
void copts_setconsoleborder(int set_cols, int set_lines, int set_buffer_cols, int set_buffer_lines)
{
	/* ȡ��ǰϵͳ����Ĵ��ڵ��������ֵ */
	COORD max_coord;
	max_coord = GetLargestConsoleWindowSize(__hout); /* .X �� .Y �ֱ��Ǵ��ڵ��к��е����ֵ */
	/* ���ô��ڵ����д�С����0��ʼ��0 ~ lines-1, 0 ~ cols-1��*/
	SMALL_RECT rect;
	rect.Top = 0;
	rect.Bottom = set_lines - 1;
	rect.Left = 0;
	rect.Right = set_cols - 1;
	/* ���û����������д�С(ȱʡ��С�ڴ���ֵ���봰��ֵһ��) */
	COORD cr;
	cr.X = (set_buffer_cols == -1 || set_buffer_cols < set_cols) ? set_cols : set_buffer_cols;		//δ�����������ֵС��set_cols����set_cols��δ��������
	cr.Y = (set_buffer_lines == -1 || set_buffer_lines < set_lines) ? set_lines : set_buffer_lines;	//δ�����������ֵС��set_lines����set_lines��δ��������
	/* ȡ��ǰ���ڼ��������Ĵ�С */
	int cur_cols, cur_lines, cur_buffer_cols, cur_buffer_lines;
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(__hout, &binfo);

	cur_cols = binfo.srWindow.Right - binfo.srWindow.Left + 1;	//�ɼ����ڵ�����
	cur_lines = binfo.srWindow.Bottom - binfo.srWindow.Top + 1;	//�ɼ����ڵ�����
	cur_buffer_cols = binfo.dwSize.X;							//������������
	cur_buffer_lines = binfo.dwSize.Y;							//������������

	copts_cls();
	/* ���ô��ڴ�Сʱ���ֻ���������ֵҪȷ������ֵ */
	if (cr.X <= cur_buffer_cols) {
		if (cr.Y <= cur_buffer_lines) {
			SetConsoleWindowInfo(__hout, true, &rect);//���ô���
			SetConsoleScreenBufferSize(__hout, cr);//���û�����
		}
		else {
			COORD tmpcr;
			tmpcr.X = cur_buffer_cols;
			tmpcr.Y = cr.Y;
			SetConsoleScreenBufferSize(__hout, tmpcr);//���û�����

			SetConsoleWindowInfo(__hout, true, &rect);//���ô���
			SetConsoleScreenBufferSize(__hout, cr);//���û�����
		}
	}
	else {
		if (cr.Y >= cur_buffer_lines) {
			SetConsoleScreenBufferSize(__hout, cr);//���û�����
			SetConsoleWindowInfo(__hout, true, &rect);//���ô���
		}
		else {
			COORD tmpcr;
			tmpcr.X = cr.X;
			tmpcr.Y = cur_buffer_lines;
			SetConsoleScreenBufferSize(__hout, tmpcr);//���û�����

			SetConsoleWindowInfo(__hout, true, &rect);//���ô���
			SetConsoleScreenBufferSize(__hout, cr);//���û�����
		}
	}
	return;
}

void copts_hidecursor(){
	CONSOLE_CURSOR_INFO tmp;
	tmp.bVisible = 0;
	tmp.dwSize = 1;
	SetConsoleCursorInfo(__hout, &tmp);
}

void copts_showcursor(){
	CONSOLE_CURSOR_INFO tmp;
	tmp.bVisible = 1;
	tmp.dwSize = 25;
	SetConsoleCursorInfo(__hout, &tmp);
}