#include "cmd_opts.h" //����̨��ز���
#include "ppong.h" //ģ�����
#include <ctime>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iomanip>
/* һЩ���ڴ���λ�õĲ��� 
    ���ڴ�С X=90,Y=30
    ����� X=10 ѡ����� X=8
    �Ҳ�˵��� X=40��������ϸ���ã�ѡ�����X=38
    ���Ҳ��� X=65���˸����һ����
    ���� Y=3 
*/
void InitializeWindow(); //���ڳ�ʼ��
void Page_MainMenu(); //���˵�ҳ
void Page_Custom_Paraset(); //�Զ�������������
void Page_Custom_Paraset_RMenu(const int index); //�Զ��������������Ҳ�˵����˺���ֻ������ʾ��
void Page_Custom_Paraset_Input(PlayerLevel &y,int id); //�Զ���ѡ�ֲ�������
bool Page_CustomII();
void Page_Demo(); //��ʾ����I
void Page_DemoII(); //��ʾ����II
void ShowPlrPara(int i); //��ʾѡ�ֲ������Ӻ�����
void Page_Result(); //��ʾ���

string to_string2(float x);//������λС���Ľ�0-1֮���С��תΪ��λ

Game usergame; //�û���������

int main()
{
    InitializeWindow();
    srand(time(NULL));
    while(1){
        Page_MainMenu();
    }
    system("pause");
    return 0;
}

void InitializeWindow(){
    copts_setconsoleborder(90, 30, 90, 30);
    copts_setconsoletitle("ƹ����ʤ�ʼ������");
    copts_fixconsolesize();
    copts_hidecursor();
}

void Page_MainMenu(){
    int keyin;
    copts_cls();
    copts_printxy(10,5,"ƹ����ʤ�ʼ������");
    copts_printxy(10,7,"Developed by Sun Yujie");
    copts_printxy(10,9,"---------------------------------");
    copts_printxy(10,11,"[1] ��ʼ�µ��Զ������");
    copts_printxy(10,13,"[2] Ԥ�������ʾ");
    copts_printxy(10,15,"[ESC] �˳�������");
    copts_printxy(65,29,"Released_1.2.1_20211217");
    while(1){
        keyin=_getch()-48;
        if (keyin==-21) exit(0); //ESC 27-48
        if (keyin==1||keyin==2) break;
    }
        if (keyin==1) Page_Custom_Paraset();
        else if (keyin==2) Page_Demo();
    return;
}

void Page_Custom_Paraset(){
    para:
    int keyin,select_index=1;
    copts_cls();
    copts_printxy(10,3,"[Backspace] ��һ���˵�");
    copts_printxy(65,3,"[ESC] �˳�������");
    copts_printline(10,5,70);
    copts_printxy(10,7,"�������޸��й�ѡ�֡�����������ģ�͵���ز���");
    copts_printxy(10,9,"(�������ѡ��һ���˵��������ּ�ѡ������˵�)");
    copts_printxy(65,27,"[N] ��һ��");
    string Paralist[5]=
        {"","I.ѡ�ֲ���","II.���Ʋ���","III.����ģ��"};
    for(int i=1;i<=3;i++){
        copts_printxy(10,9+2*i,Paralist[i]);  
    }
    copts_printxy(8,9+2*select_index,"> "); 
    Page_Custom_Paraset_RMenu(select_index); 
    while(1){
        keyin=_getch();
        if (keyin==27) exit(0); //ESC 27
        if (keyin==8) return; //�˸� 8
        else if(keyin==78||keyin==110){ //N 78 n 110��ʼ
        usergame.demo=false;
        bool ret;
        ret=Page_CustomII();
        if(ret) goto para;
        else return;
        }
        else if (keyin==(224)){ //�������������б�����
            int dirct;
            dirct=_getch();
            switch (dirct){
            case 72:{
                if(select_index>1) select_index--;
                break;
                }
            case 80:{
                if(select_index<3) select_index++;
                break;
                }   
            }
            for(int i=1;i<=3;i++) copts_printxy(8,9+2*i," ");  
            copts_printxy(8,9+2*select_index,"> "); 
            Page_Custom_Paraset_RMenu(select_index);
        }
        else if(keyin>=48&&keyin<=57){ //���ּ�ѡ������˵�
            switch(select_index){
                case 1:{
                    switch(keyin){
                        case 49:Page_Custom_Paraset_Input(usergame.plr[0],0);goto para;break;
                        case 50:Page_Custom_Paraset_Input(usergame.plr[1],1);goto para;break;
                        case 51:{
                            usergame.plr[1]=usergame.plr[0];
                            goto para;
                            break;
                        }
                    }
                }
                case 2:{
                    if(keyin>=49&&keyin<=50){
                    for(int i=1;i<=2;i++) copts_printxy(38,9+2*i," ");   
                    copts_printxy(38,9+2*(keyin-48),"> ");
                    usergame.one_game=keyin-48;   
                    }
                    else if(keyin>=51&&keyin<=54){
                    for(int i=3;i<=6;i++) copts_printxy(38,9+2*i," ");   
                    copts_printxy(38,9+2*(keyin-48),"> ");   
                    usergame.whole_game=keyin-48;   
                    } 
                    break;
                }
                case 3:break;
            }
        }
    }
}

void Page_Custom_Paraset_RMenu(const int index){
    for(int i=11;i<25;i++) copts_printspace(40,i,52);
    for(int i=11;i<25;i++) copts_printxy(38,i," ");
    switch (index){
        case 1:{
            copts_printxy(40,11,"[1] �޸�ѡ��A��������");
            copts_printxy(40,13,"[2] �޸�ѡ��B��������");
            copts_printxy(40,15,"[3] ʹѡ��B����������Aһ��");
            break;
        }
        case 2:{
            copts_printxy(40,11,"[1] 11����");
            copts_printxy(40,13,"[2] 21����");
            copts_printxy(40,15,"[3] ������ʤ��");
            copts_printxy(40,17,"[4] �����ʤ��");
            copts_printxy(40,19,"[5] �߾���ʤ��");
            copts_printxy(40,21,"[6] һ�ֶ�ʤ��");
            copts_printxy(38,9+2*usergame.one_game,"> ");
            copts_printxy(38,9+2*usergame.whole_game,"> ");
            break;
        }
        case 3:{
            copts_printxy(40,11,"[1] �������");
            copts_printxy(38,9+2*usergame.calcmod,"> ");
            break;
        }
    }
}

void Page_Custom_Paraset_Input(PlayerLevel &y,int id){
    PlayerLevel *p=&y;
    copts_showcursor();
    copts_cls();
    printf("������ѡ��%c�Ĳ���(�뱣֤���ݺϷ������������ж�)\n",usergame.strindex[id]);
    printf("�����뷢��ֱ�ӵ÷���(0<x<1):\n");
    scanf("%f",&p->first_sev_scr);
    printf("���������ʱ������(0<x<1):\n");
    scanf("%f",&p->atk_hit);
    printf("������ǽ���ʱ������(0<x<1):\n");
    scanf("%f",&p->nor_hit);
    printf("�������ܽ�������ɹ���(0<x<1):\n");
    scanf("%f",&p->atk_catch);
    printf("��������ܽ�������ɹ���(0<x<1):\n");
    scanf("%f",&p->nor_catch);
    printf("�����뷢������ʹ����(0<x<1):\n");
    scanf("%f",&p->sevatk_usg);
    printf("�����뷢�򷴹�ʹ����(0<x<1):\n");
    scanf("%f",&p->sevctratk_usg);
    printf("�������������ʹ����(0<x<1):\n");
    scanf("%f",&p->cthatk_usg);
    printf("���������״̬����(0<x<100):\n");
    scanf("%d",&p->stalemate_lv);
    int keyin;
    printf("\n������ɣ������������\n");
    keyin=_getch();
    copts_hidecursor();
    return;
}
bool Page_CustomII(){
    int keyin;
    copts_cls();
    copts_printxy(10,3,"[Backspace] ��һ���˵�");
    copts_printxy(65,3,"[ESC] �˳�������");
    copts_printxy(65,27,"[N] ��ʼ����");
    copts_printline(10,5,70);
    copts_printxy(10,7,"ѡ��A");
    copts_printxy(40,7,"ѡ��B");
    //���������λѡ����ֵ
    PlayerLevel *p;
    for(int i=0;i<=1;i++){
        p=&usergame.plr[i];
        ShowPlrPara(i);
    }
    while(1){
        keyin=_getch();
        if (keyin==27) exit(0); //ESC 27
        if (keyin==8) return 1; //�˸� 8  
        else if(keyin==78||keyin==110){ //N 78 n 110��ʼ
        usergame.demo=false;
        Page_Result();
        return 0;
    }
    }
}
void Page_Demo(){
    int keyin;
    copts_cls();
    copts_printxy(10,3,"[Backspace] ��һ���˵�");
    copts_printxy(65,3,"[ESC] �˳�������");
    copts_printxy(65,27,"[N] ��ʼ����");
    copts_printline(10,5,70);
    copts_printxy(10,7,"��һ�� �������ѡ������ ���Ժ�");
    Sleep(500);
    copts_printxy(10,7,"ѡ��A                         ");
    copts_printxy(40,7,"ѡ��B");
    //���������λѡ����ֵ
    PlayerLevel *p;
    for(int i=0;i<=1;i++){
        p=&usergame.plr[i];
        p->first_sev_scr=RandomVal(0.05,0.16); 
        p->atk_hit=RandomVal(0.65,0.9);
        p->nor_hit=RandomVal(0.9,0.98);
        p->atk_catch=RandomVal(0.65,0.75);
        p->nor_catch=RandomVal(0.9,0.95);
        p->sevatk_usg=RandomVal(0.3,0.55);
        p->sevctratk_usg=RandomVal(0.3,0.55);
        p->cthatk_usg=RandomVal(0.3,0.45);
        p->stalemate_lv=(int)(RandomVal(0.45,0.55)*100);
        ShowPlrPara(i);
    }
    while(1){
        keyin=_getch();
        if (keyin==27) exit(0); //ESC 27
        if (keyin==8) return; //�˸� 8  
        else if(keyin==78||keyin==110){ //N 78 n 110��ʼ
        //Page_DemoII();
        usergame.demo=true;
        Page_DemoII();
        return;
    }
    }
}

void ShowPlrPara(int i){
    PlayerLevel *p=&usergame.plr[i];
    copts_printxy(10+30*i,9,"����÷���:"+to_string2(p->first_sev_scr));
    copts_printxy(10+30*i,10,"����������:"+to_string2(p->atk_hit));
    copts_printxy(10+30*i,11,"�ǽ���������:"+to_string2(p->nor_hit));
    copts_printxy(10+30*i,12,"�ܽ���������:"+to_string2(p->atk_catch));
    copts_printxy(10+30*i,13,"���ܽ���������:"+to_string2(p->nor_catch));
    copts_printxy(10+30*i,14,"����ʹ����:"+to_string2(p->sevatk_usg));
    copts_printxy(10+30*i,15,"���򷴹�ʹ����:"+to_string2(p->sevctratk_usg));
    copts_printxy(10+30*i,16,"����ʹ����:"+to_string2(p->cthatk_usg));
    copts_printxy(10+30*i,17,"��ֵ÷�����:"+to_string(p->stalemate_lv));
    copts_printxy(10+30*i,19,"�ۺ���������:"+to_string(p->syn_lv));

    usergame.CalcsynLevel(*p);
    copts_printxy(10+30*i,19,"�ۺ���������:"+to_string(p->syn_lv));
}

void Page_DemoII(){
    int keyin;
    copts_cls();
    copts_printxy(10,7,"�ڶ��� ģ��һ��������һ�ֶ�ʤ�ƣ�\n");
    Sleep(1000);
    usergame.demo=true;
    usergame.one_game=1;
    usergame.whole_game=6;
    int tmp=usergame.Simulation();
    printf("\n�������������һҳ\n");
    keyin=_getch();
    Page_Result();
    return;
}

void Page_Result(){
    int keyin;
    copts_cls();
    copts_hidecursor();
    if(usergame.demo){
        usergame.one_game=1;
        usergame.whole_game=5;
        copts_printxy(10,7,"������ ģ��һǧ������(11���ƣ��߾���ʤ)");
        Sleep(1000);
        copts_cls();
        copts_gotoxy(0,0);
        usergame.demo=0;
        int tot[2]={0};
        for(int i=1;i<=1000;i++){
            int tmp=usergame.Simulation();
            tot[tmp]++;
            printf("��ģ��%d����������ǰ��ʤ���� %d : %d \n",i,tot[0],tot[1]);
            Sleep(5);
        }
        printf("\n�������������һҳ\n");
        keyin=_getch();
        usergame.one_game=2;
        usergame.whole_game=3;
        copts_cls();
        copts_printxy(10,7,"���Ĳ� ģ��һǧ������(21���ƣ�������ʤ)");
        Sleep(1000);
        copts_cls();
        usergame.demo=0;
        int tot2[2]={0};
        for(int i=1;i<=1000;i++){
            int tmp=usergame.Simulation();
            tot2[tmp]++;
            printf("��ģ��%d����������ǰ��ʤ���� %d : %d \n",i,tot2[0],tot2[1]);
            Sleep(5);
        }
        printf("\n�������������һҳ\n");
        keyin=_getch();
        copts_cls();
        printf("11���ƣ��߾���ʤ���� ��ʤ���� %d : %d \n\n",tot[0],tot[1]);
        printf("ѡ��Aʤ�� : %.2lf %\n",(100*(double)tot[0]/(tot[0]+tot[1])));
        printf("ѡ��Bʤ�� : %.2lf %\n\n",(100*(double)tot[1]/(tot[0]+tot[1])));
        printf("21���ƣ�������ʤ���� ��ʤ���� %d : %d \n\n",tot2[0],tot2[1]);
        printf("ѡ��Aʤ�� : %.2lf %\n",(100*(double)tot2[0]/(tot2[0]+tot2[1])));
        printf("ѡ��Bʤ�� : %.2lf %\n\n",(100*(double)tot2[1]/(tot2[0]+tot2[1])));
        printf("\n�����������\n");
        keyin=_getch();
        return;
    }

    else{
        int tot[2]={0};
        for(int i=1;i<=10000;i++){
            int tmp=usergame.Simulation();
            tot[tmp]++;
            if(i%1000==0) printf("��ģ��%d����������ǰ��ʤ���� %d : %d \n",i,tot[0],tot[1]);
        }  
        Sleep(500); 
        copts_cls();
        if(usergame.one_game==1)printf("������������:\n11���� ");
        else printf("������������:\n21���� ");
        switch (usergame.whole_game){
            case 3:printf("������ʤ\n\n");break;
            case 4:printf("�����ʤ\n\n");break;
            case 5:printf("�߾���ʤ\n\n");break;
            case 6:printf("һ�ֶ�ʤ\n\n");break;
        }
        printf("���ι�ģ��%d����������ʤ���� %d : %d \n",10000,tot[0],tot[1]);
        printf("\nѡ��Aʤ�� : %.2lf %\n",(100*(double)tot[0]/(tot[0]+tot[1])));
        printf("ѡ��Bʤ�� : %.2lf %\n",(100*(double)tot[1]/(tot[0]+tot[1])));
    printf("\n�����������\n");
    keyin=_getch();
    return;
    }
}


string to_string2(float x){
    if(x<0||x>1) return("ERROR");
    if(x==1) return("1.00");
    int a=(int)(x*100);
    if(a<10) return ("0.0"+to_string(a));
    return ("0."+to_string(a));
}