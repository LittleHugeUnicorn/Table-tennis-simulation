#include "ppong.h"

bool Game::Random(float prob){
    float ran;
    ran= rand()/double(RAND_MAX+1);
    if(ran<=prob) return true;
    else return false;
}

int Game::Simulation(){
    memset(og_score,0,sizeof(og_score));
    memset(wg_score,0,sizeof(wg_score));
    int wggoal; //wggoalΪһ��������������Ӯ������
    int oggoal; //oggoalΪһ�ֱ�����������ӮС����
    switch (whole_game){
        case 3:wggoal=2;break;
        case 4:wggoal=3;break;
        case 5:wggoal=4;break;
        case 6:wggoal=1;break;
    }
    switch (one_game){
        case 1:oggoal=11;break;
        case 2:wggoal=21;break;
    }
    //������ʼ��ǩ������һ�ַ���
        Random(0.5)?plr_sev=0:plr_sev=1;
        plr_alrsev=0;
        plr_firsev=plr_sev;
    //һ��������ʼ
    while(wg_score[0]<wggoal&&wg_score[1]<wggoal)
    {   
        //���С�ȷ�
        memset(og_score,0,sizeof(og_score));
        //�����þ��׷��򷽣���һ��ҳ���������ڸ�����Ȳ�Ӱ�죩
        plr_firsev=1-plr_firsev;
        plr_sev=plr_firsev;
        //һ�ֱ�����ʼ
        MoodandRand();
        while(!Checkover()){
            if(demo){
                copts_cls();
                printf("������������11����\n");
                Sleep(500);
            } 
            Hit(plr_sev,1); //����
            //�����Ƿ���ķ���
            if(og_score[0]>=oggoal-1 && og_score[1]>=oggoal-1) plr_sev=1-plr_sev;
            else{
                plr_alrsev++;
                if(plr_alrsev==2){
                    plr_sev=1-plr_sev;
                    plr_alrsev=0;
                }
            }
            MoodandRand();
        }
        //һ�ֱ�������
    }
    //һ����������
    if(demo){
        copts_cls();
        printf("�������� С�ȷ� %d : %d\n\n",og_score[0],og_score[1]);
    }
    if (wg_score[0]==wggoal) 
        {if (demo)printf("����ʤ��Ϊ:ѡ��A\n");
        return 0;}
    else 
        {if(demo)printf("����ʤ��Ϊ:ѡ��B\n");
        return 1;}
}

void Game::Hit(int phit,int mod){
    //demoģʽ���
    if(demo){
        switch(mod){
            case 0:{printf("\nѡ�� %c �ǽ����ش򣬽������ ",strindex[phit]);Sleep(300);break;}
            case 1:{printf("\nѡ�� %c ���� ",strindex[phit]);Sleep(300);break;}
            case 2:{printf("\nѡ�� %c �������� ",strindex[phit]);Sleep(300);break;}
            case 3:{printf("\nѡ�� %c �������� ",strindex[phit]);Sleep(300);break;}
            case 4:{printf("\nѡ�� %c ���򷴹� ",strindex[phit]);Sleep(300);break;}
            case 5:{printf("\nѡ�� %c �ӷ��� ",strindex[phit]);Sleep(300);break;}
        }
    }

    if (mod==1){ //��һ�巢��
        if(Random(plr[phit].first_sev_scr)) 
            {og_score[phit]++; 
            if(demo){printf("ֱ�ӵ÷�---��ǰС�ȷ� %d : %d \n",og_score[0],og_score[1]);Sleep(1100);}
            return;}
    }
    //�Ƿ�����,������δ����
    if(mod>=2&&mod<=4){
        if(!Random(plr[phit].atk_hit*plr[phit].addi_hit)) 
        {og_score[1-phit]++;
        if(demo){printf("���磬�Է��÷�---��ǰС�ȷ� %d : %d \n",og_score[0],og_score[1]);Sleep(1100);}
        return;}
    }
    else if(!Random(plr[phit].nor_hit*plr[phit].addi_hit)) 
        {og_score[1-phit]++;
        if(demo){printf("���磬�Է��÷�---��ǰС�ȷ� %d : %d \n",og_score[0],og_score[1]);Sleep(1100);}
        return;}
    //���к�ת�����ֵ�Catch
    Catch(1-phit,mod);
    return;
}

void Game::Catch(int pcth,int mod){
    //�Ƿ��ס��������δ��ס
    if(mod>=2&&mod<=4){
        if(!Random(plr[pcth].atk_catch*plr[pcth].addi_cth)) 
        {og_score[1-pcth]++; 
        if(demo){printf("����δ��ס�������÷�---��ǰС�ȷ� %d : %d \n",og_score[0],og_score[1]);Sleep(1100);}
        return;}
    }
    else if(!Random(plr[pcth].nor_catch*plr[pcth].addi_cth)) 
        {og_score[1-pcth]++; 
        if(demo){printf("����δ��ס�������÷�---��ǰС�ȷ� %d : %d \n",og_score[0],og_score[1]);Sleep(1100);}
        return;}
    //��ס���ж϶Բ�
    if(demo) printf("\n");
    switch (mod){
        case 0:{Stalemate(); return;}
        case 1:{ //�ӵ��Է�����
            if(Random(plr[pcth].cthatk_usg)) Hit(pcth,2);//����
            else Hit(pcth,5); //�ӷ���
            break;
        }
        case 2:{ //�ӵ��Է�����
            if(Random(plr[pcth].sevctratk_usg)) Hit(pcth,4);//���򷴹�
            else Hit(pcth,0); //�������
            break;
        }
        case 3: Hit(pcth,0); break;
        case 4: Hit(pcth,0); break;
        case 5:{ //�ӵ��Է��ӷ���
            if(Random(plr[pcth].sevatk_usg)) Hit(pcth,3);//��������
            else Hit(pcth,0); //�������
            break;
        }
    }
}

void Game::Stalemate(){
    int a=plr[0].stalemate_lv,b=plr[1].stalemate_lv;
    if(Random(a/(float)(a+b))) 
        {og_score[0]++;
        if(demo){printf("\n\n��ֽ�����ѡ��A�÷�---��ǰС�ȷ� %d : %d \n",og_score[0],og_score[1]);Sleep(1100);}
        }
    else 
        {og_score[1]++;
        if(demo){printf("\n\n��ֽ�����ѡ��B�÷�---��ǰС�ȷ� %d : %d \n",og_score[0],og_score[1]);Sleep(1100);}
        }
    return;
}

bool Game::Checkover(){
    int t;
    if(abs(og_score[0]-og_score[1])<=1||
        (og_score[0]>og_score[1]?og_score[0]:og_score[1])<(one_game==1?11:21))
    return false;
    t=(og_score[0]>og_score[1]?0:1);
    wg_score[t]++;
    if(demo){
        printf("\n���ֽ��� С�ȷ� %d : %d\n\n����ʤ��Ϊ:ѡ��%c\n"
            ,og_score[0],og_score[1],strindex[t]);
        Sleep(1500);
    }
    return true;
} 

void Game::MoodandRand(){
    plr[0].addi_hit=RandomVal(0.95,1.1);
    plr[1].addi_hit=RandomVal(0.95,1.1);
    plr[0].addi_cth=RandomVal(0.95,1.1);
    plr[1].addi_cth=RandomVal(0.95,1.1);
    for(int i=0;i<=1;i++){
        if(plr[i].addi_hit*plr[i].atk_hit>=1||plr[i].addi_hit*plr[i].nor_hit>=1)
        plr[i].addi_hit=1;
        if(plr[i].addi_cth*plr[i].atk_catch>=1||plr[i].addi_cth*plr[i].nor_catch>=1)
        plr[i].addi_cth=1;
    }
    if (!(abs(og_score[0]-og_score[1])<=1||
        (og_score[0]>og_score[1]?og_score[0]:og_score[1])<(one_game==1?11:21)))
        return;
    int plead=(og_score[0]>og_score[1]?0:1);
    if (og_score[plead]-og_score[1-plead]>=3){
        if(Random(0.125)){ 
            if(demo){printf("\n�ֲ�ϴ����ȷ�ѡ�� %c �������� (��һ������ʡ���������΢�½�)\n",strindex[plead]); Sleep(1500);}
            plr[plead].addi_hit-=RandomVal(0,0.25);
            plr[plead].addi_cth-=RandomVal(0,0.25);
        }
        if(Random(0.333)){
            if(demo) {printf("\n���ѡ�� %c ��ֲ�и,����ֱ׷ (��һ����������΢����)\n",strindex[1-plead]); Sleep(1500);}
            plr[1-plead].addi_hit+=RandomVal(0,0.2);
            PlayerLevel &backw=plr[1-plead];
            if(backw.addi_hit*backw.atk_hit>=1||backw.addi_hit*backw.nor_hit>=1)
            backw.addi_hit=0.99/(backw.nor_hit>backw.atk_hit?backw.nor_hit:backw.atk_hit);
        }
    }
}

void Game::CalcsynLevel(PlayerLevel &p){
    int tot=0;
    tot+=p.first_sev_scr*100;
    tot+=p.nor_hit*150;
    tot+=(p.atk_catch*360+p.nor_catch*240);
    tot+=(p.sevatk_usg*p.atk_hit*150);
    tot+=(p.sevctratk_usg*p.atk_hit*150);
    tot+=(p.cthatk_usg*p.atk_hit*150);
    tot+=p.stalemate_lv*2;
    p.syn_lv=tot;
    return;
}

float RandomVal(float l,float r){
    int ran;
    int L=(int)(l*1000),R=(int)(r*1000);
    ran=rand()%(R-L+1)+L;
    return (ran/1000.00);
}