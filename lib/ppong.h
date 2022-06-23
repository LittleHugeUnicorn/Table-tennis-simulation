#pragma once
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include "cmd_opts.h"
using namespace std;
struct PlayerLevel{
    float first_sev_scr; //����ֱ�ӵ÷���
    float atk_hit; //����ʱ�����ʣ�δ��������ּӷ֣���������жԷ������ж���
    float nor_hit; //�ǽ���ʱ������
    float atk_catch; //�ܽ���ʱ����ɹ���
    float nor_catch; //�ܷǽ���ʱ����ɹ���
    float sevatk_usg; //��������ʹ���ʣ������ڶ��壩
    float sevctratk_usg; //���򷴹�ʹ���ʣ������ڶ��壩
    float cthatk_usg; //��������ʹ���ʣ��Է���һ�壩
    int stalemate_lv; //���״̬�����������������������״̬ʤ�ʣ�
    int syn_lv; //�ۺ�������
    float addi_hit=1; //����״̬���������������ʵļӳɱ���
    float addi_cth=1; //����״̬���������Խ���ɹ��ʵļӳɱ���
    int power=100; //����ʣ��
};

//������,���ݳ�ԱСд��ͷ����Ա������д��ͷ
class Game{
    public:
    int calcmod;
    int one_game;//1Ϊ11���ƣ�2Ϊ21����
    int whole_game;//3456����������ʤ/�����ʤ/�߾���ʤ/��һ��
    bool demo; //�Ƿ���ʾÿһ�־������
    char strindex[2]={'A','B'};
    PlayerLevel plr[2]; //˫����Ա���Ϊ0/1

    private:
    int og_score[2];//С�ȷ�
    int wg_score[2];//��ȷ�
    int plr_hold; //���򷽣�plr_hold=1-plr_holdʵ����Ȩ������
    int plr_sev; //���򷽣�ͬ��ʵ����Ȩ������ 
    int plr_alrsev; //��ǰ�����ѷ������
    int plr_firsev; //�����׷��򷽣�ÿ�ֿ�ʼͬ��ʵ�ֽ�������һ�������

    //�������,����prob������Ϊ��ĸ���,������������
    bool Random(float prob);

    //�жϱ����Ƿ����,��������true�����
    bool Checkover();

    //������,phit->(1-phit)
    //mod=0Ϊ����ǽ�������,1Ϊ��һ�巢��,2Ϊ����,3Ϊ����,4Ϊ���򷴹�,5Ϊ�ӷ���
    void Hit(int phit,int mod);

    //����������Ա�ӵ�����˼�����̣��������Ժ����Hit���Ƿ�ӵ�������һ��Hit�м��㣩
    //mod=0Ϊ����ǽ�������,1Ϊ�ӵ��Է�����,2Ϊ�ӵ��Է�����,3Ϊ�ӵ��Է�����,4Ϊ�ӵ��Է����򷴹�
    void Catch(int pcth,int mod);

    //��ֺ���
    void Stalemate();

    //����ѡ������״��+
    //����ı�ѡ��״̬�ĺ���
    void MoodandRand();
    /*����Ӱ��
    �����ڷֲ�ﵽ�ٽ�ֵ����Ϊ4��ʱ���������
    ���ȷ���1/8���ʷ��ɣ������ʡ��������½���
    ʧ�ܷ���1/2���ʷ�׷��������������*/

    public:
    Game(int a=1,int b=4,int cm=1):one_game(a),whole_game(b),calcmod(cm)
    {
        memset(og_score,0,sizeof(og_score));
        memset(wg_score,0,sizeof(wg_score));
        demo=false;
    }
    //ģ����� 
    int Simulation(); 

    //����������ֵ   
    void CalcsynLevel(PlayerLevel &p);                                                                          
};

float RandomVal(float l,float r); //��������ɣ�����һ��l-r����(0<l<r<1)