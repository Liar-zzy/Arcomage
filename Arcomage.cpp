#include <iostream>
#include <string.h>
#include <cmath>
#include <iomanip>
#include <time.h>
#include <windows.h>
#include <fstream>
using namespace std;
int winner_wall = 0;
int winner_resource = 0;
int winner_round = 0;
int last_handcard = 0;
int last_player = 0;
bool Isagain=false;
int useorgive = 0;
class player {			//��������� 
private:

	int castle;
	int wall;	
	int brick;
	int Producebrick;
	int jewel;
	int Producejewel;
	int monster;
	int Producemonster;
public:
	player() {};
	char name[10];
	int handcard[6];
	void setname(char *a) {		//������� 
		strcpy(name, a);
	}
	int getcastle() { return castle; }  //�õ�������Դ�� ��
	int getwall() { return wall; }
	int getbrick() { return brick; }
	int getProducebrick() { return Producebrick; }
	int getjewel() { return jewel; }
	int getProducejewel() { return Producejewel; }
	int getmonster() { return monster; }
	int getProducemonster() { return Producemonster; }

	void setcastle(int n) {	castle = n;}   //�ı������Դ����
	void setwall(int n) {	wall = n;	}
	void setbrick(int n) {	brick = n;	}
	void setProducebrick(int n) {	Producebrick = n;	}	
	void setjewel(int n) {	jewel = n;	}
	void setProducejewel(int n) {	Producejewel = n;	}
	void setmonster(int n) {	monster = n;}
	void setProducemonster(int n) {	Producemonster = n;	}

	void setbaseDate(int castle, int wall, int brick, int Producebrick, int jewel, int Producejewel, int monster, int Producemonster) {//��ʼ�� 
		this->castle = castle;
		this->wall = wall;
		this->brick = brick;
		this->Producebrick = Producebrick;
		this->jewel = jewel;
		this->Producejewel = Producejewel;
		this->monster = monster;
		this->Producemonster = Producemonster;
	}
	void Produce_All() {			//����ÿ�غ� ����������Դ 
		brick += Producebrick;
		jewel += Producejewel;
		monster += Producemonster;
	}
	friend class card;
};
class card {		//������
private:
	char name[15];
	char kind;
	int price;
	char effect[100];
	bool change;
public:
	card() {};
	void set_baseDate(const char *a, char b, int c,const char *d, bool e) {
		strcpy(name, a);
		kind = b;
		price = c;
		strcpy(effect, d);
		change = e;
	}
	void show() {		//��������������໨�Ѽ����� 
		cout << "<" << name << ">" << "(" << (kind == 'b' ? "שͷ" : (kind == 'j' ? "��ʯ" : "����")) << price << ")" << effect;
	}
	int getprice() {return price;	}//���� ���� 
	bool getchange() {	return change;	}
	bool Isresource(player &a){
		if (kind=='b') {
			if (a.getbrick() >= getprice()) {
				return true;
			}
			return false;
		}
		else if (kind == 'j') {
			if (a.getjewel() >= getprice()) {
				return true;
			}
			return false;
		}
		else  {
			if (a.getmonster() >= getprice()) {
				return true;
			}
			return false;
		}
	}
	bool Iswall(player &a) {		//�ж��Ƿ���ǽ ���������� �Ǳ� 
		if (a.wall > 0)return true;
		return false;
	}
	void Dealcastle(player &a, int b) {		//����Ǳ� 
		a.castle += b;
	}
	void Dealwall(player &a, int b) {			//����ǽ 
			if (b >= 0) {
				a.wall += b;
			}
			else {
				if (abs(b) > a.getwall()) {
					int x;
					x = abs(b) - a.getwall();
					a.wall = 0;
					a.castle -= x;
				}
				else {
					a.wall += b;
				}
			}
		
	}
	void Dealbrick(player &a, int b) {		//����ש�� 
		a.brick += b;
	}
	void Producebrick(player &a, int b) {			//����ש����� 
		a.Producebrick += b;
	}
	void Dealjewel(player &a, int b) {		//����ʯ 
		a.jewel += b;
	}
	void Producejewel(player &a, int b) {	a.Producejewel += b;	}//���Ʊ�ʯ����
	void Dealmonster(player &a, int b) {	a.monster += b;	}//������� 
	void Producemonster(player &a, int b) {		a.Producemonster += b;	}//���ƹ������
	void Bothwall(player &a, player &b, int c, int d) {			//��˫�����Ӱ��Ŀ��� ǽ �Ǳ� ש��iuy 
		a.wall += c;
		b.wall += d;
	}
	void Bothcastle(player &a, player &b, int c, int d) {
		a.castle += c;
		b.castle += d;
	}
	void Bothbrick(player &a, player &b, int c, int d) {
		a.brick += c;
		b.brick += d;
	}
	void Bothmonster(player &a, player &b, int c, int d) {
		a.monster += c;
		b.monster += d;
	}
	void Bothjewel(player &a, player &b, int c, int d) {
		a.jewel += c;
		b.jewel += d;
	}
	void BothProducebrick(player &a, player &b, int c) {
		a.Producebrick += c;
		b.Producebrick += c;
	}
	void CompareProducebrick(player &a, player &b, int c, int d) {
		if (a.getbrick() < b.getbrick()) {
			a.Producebrick += c;
		}
		else {
			a.Producebrick += d;
		}
	}
	void BothProducejewel(player &a, player &b, int c, int d) {
		a.Producejewel += c;
		b.Producejewel += d;
	}
	void CompareProducebrick(player &a, player &b) {
		if (a.brick < b.brick) {
			a.brick = b.brick;
		}
	}
	void CompareProducejewel(player &a, player &b) {
		if (a.Producejewel >= b.Producejewel) {
			b.Producejewel = a.Producejewel;
		}
		else {
			a.Producejewel = b.Producejewel;
		}
	}
	bool IsCompareProducejewel(player &a, player &b) {
		if (a.Producejewel > b.Producejewel)return true;
		return false;
	}
	bool IsComparewall(player &a, player &b) {
		if (a.wall < b.wall)return true;
		return false;
	}
};
void changeCard(player &a, card cardnum[], int n);
void checkAll(player &a, player &b) {	//��� ��Ϊ�Է�����ʹ˫�� ���ֲ����Ƿ�Ϊ���� ������ ������ 
		if (a.getcastle() < 0)a.setcastle(0);
		if (a.getbrick() < 0)a.getbrick();
		if (a.getjewel() < 0)a.setjewel(0);
		if (a.getmonster() < 0)a.setmonster(0);
		if (a.getProducebrick() < 0)a.setProducebrick(0);
		if (a.getProducejewel() < 0)a.setProducejewel(0);
		if (a.getProducemonster() < 0)a.setProducemonster(0);

		if (b.getcastle() < 0)b.setcastle(0);
		if (b.getbrick() < 0)b.getbrick();
		if (b.getjewel() < 0)b.setjewel(0);
		if (b.getmonster() < 0)b.setmonster(0);
		if (b.getProducejewel() < 0)b.setProducejewel(0);
		if (b.getProducemonster() < 0)b.setProducemonster(0);
	
}
/*---------------------------�����������----------------------------*/
void set_Allcard(card cardnum[87]) {
	//ש���࿨��
	cardnum[0].set_baseDate("��������", 'b', 0, "˫��ͬʱʧȥ8��שͷ", true);
	cardnum[1].set_baseDate("���˱���", 'b', 0, "שͷ+2����ʯ+2���ٴγ���", true);
	cardnum[2].set_baseDate("����֮��", 'b', 1, "��ǽ+1���ٴγ���", true);
	cardnum[3].set_baseDate("ΰ���", 'b', 3, "שͷ����+1", true);
	cardnum[4].set_baseDate("��ʯ֮��", 'b', 4, "���שͷ�������ڶ��֣���שͷ����+2", true);
	cardnum[5].set_baseDate("����֮��", 'b', 7, "��ǽ+4��שͷ����+1", true);
	cardnum[6].set_baseDate("Ŭ������", 'b', 2, "��ǽ+5����ʯ-6", true);
	cardnum[7].set_baseDate("��Ӱ֮��", 'b', 5, "���שͷ�������ڶ��֣���שͷ�������ڶ���", true);
	cardnum[8].set_baseDate("����֮ǽ", 'b', 2, "��ǽ+3", true);
	cardnum[9].set_baseDate("�ȹ�֮ǽ", 'b', 3, "��ǽ+4", true);
	cardnum[10].set_baseDate("��������", 'b', 2, "˫��שͷ����ͬʱ+1���㻹�õ�4����ʯ", true);
	cardnum[11].set_baseDate("�ȹ̻���", 'b', 3, "���û�г�ǽ���ǽ+6�������ǽ+3", true);
	cardnum[12].set_baseDate("����֮��", 'b', 7, "˫����ǽͬʱ-5���ٴγ���", true);
	cardnum[13].set_baseDate("����С��", 'b', 8, "��ʯ����+1���ٴγ���", true);
	cardnum[14].set_baseDate("ɽ������", 'b', 0, "˫��שͷ����ͬʱ-1", true);
	cardnum[15].set_baseDate("��ΰ֮ǽ", 'b', 5, "��ǽ+6", true);
	cardnum[16].set_baseDate("����֮��", 'b', 4, "����שͷ����-1", true);
	cardnum[17].set_baseDate("��������", 'b', 6, "שͷ����+2", true);
	cardnum[18].set_baseDate("����֮��", 'b', 0, "שͷ����-1����ǽ+10����ʯ+5", true);
	cardnum[19].set_baseDate("����֮ʯ", 'b', 8, "��ǽ+8", true);
	cardnum[20].set_baseDate("����֮��", 'b', 9, "��ǽ+5���������+1", true);
	cardnum[21].set_baseDate("��ñ�ʯ", 'b', 9, "��ǽ+7����ʯ+7", true);
	cardnum[22].set_baseDate("��������", 'b', 11, "��ǽ+8���Ǳ�+3", true);
	cardnum[23].set_baseDate("�β�����", 'b', 13, "��ǽ+12", true);
	cardnum[24].set_baseDate("�������", 'b', 15, "��ǽ+8���Ǳ�+5", true);
	cardnum[25].set_baseDate("ħ��֮ǽ", 'b', 16, "��ǽ+15", true);
	cardnum[26].set_baseDate("��ʯ���", 'b', 18, "��ǽ+6�����ֳ�ǽ-10", true);
	cardnum[27].set_baseDate("����֮��", 'b', 24, "��ǽ+20���Ǳ�+8", true);
	cardnum[28].set_baseDate("��������", 'b', 7, "��ǽ+9������-5", true);
	//��ʯ�࿨��
	cardnum[29].set_baseDate("��ɫ��ʯ", 'j', 1, "�Ǳ�+1���ٴγ���", true);
	cardnum[30].set_baseDate("���֮��", 'j', 2, "���ֳǱ�-1���ٴγ���", true);
	cardnum[31].set_baseDate("�Ի�֮��", 'j', 2, "�Ǳ�+3", true);
	cardnum[32].set_baseDate("ħ������", 'j', 3, "��ʯ����+1", true);
	cardnum[33].set_baseDate("����ħ��", 'j', 2, "��һ���ƺ��ٴγ���", true);
	cardnum[34].set_baseDate("�������", 'j', 5, "�Ǳ�+3�������Ʋ��ܻ���ֻ��ʹ��", false);
	cardnum[35].set_baseDate("��������", 'j', 4, "�Ǳ�+2�����ֳǱ�-2", true);
	cardnum[36].set_baseDate("��ʯħ��", 'j', 6, "��ʯ����+1���Ǳ�+3�����ֳǱ�+1", true);
	cardnum[37].set_baseDate("��ʯ�Ѻ�", 'j', 2, "���ֳǱ�-3", true);
	cardnum[38].set_baseDate("��챦ʯ", 'j', 3, "�Ǳ�+5", true);
	cardnum[39].set_baseDate("ˮ��֮ì", 'j', 4, "���ֳǱ�-5", true);
	cardnum[40].set_baseDate("�����Ի�", 'j', 3, "��ʯ����+2���Ǳ�-5", true);
	cardnum[41].set_baseDate("�ҳϴ���", 'j', 7, "��ʯ����+1���Ǳ�+3����ǽ+3", true);
	cardnum[42].set_baseDate("��ƽ����", 'j', 7, "˫����ʯ���������ڲ����ߵ�һ��", true);
	cardnum[43].set_baseDate("�������", 'j', 6, "�Ǳ�+8", true);
	cardnum[44].set_baseDate("�ǻ�����", 'j', 9, "��ʯ����+1���Ǳ�+5", true);
	cardnum[45].set_baseDate("������ͽ", 'j', 8, "��ʯ����-1�����ֳǱ�-9", true);
	cardnum[46].set_baseDate("����֮ʯ", 'j', 7, "�Ǳ�+5������שͷ-6", true);
	cardnum[47].set_baseDate("��ɫˮ��", 'j', 10, "�Ǳ�+11", true);
	cardnum[48].set_baseDate("�����භ", 'j', 5, "˫����ʯ����ͬʱ-1���Ǳ�ͬʱ-7", true);
	cardnum[49].set_baseDate("�û�֮ʯ", 'j', 13, "�Ǳ�+6�����ֳǱ�-4", true);
	cardnum[50].set_baseDate("����ū��", 'j', 4, "�Ǳ�+7��שͷ-10", true);
	cardnum[51].set_baseDate("ˮ������", 'j', 12, "�Ǳ�+8����ǽ+3", true);
	cardnum[52].set_baseDate("�������", 'j', 14, "�Ǳ�+8���������+1", true);
	cardnum[53].set_baseDate("��ʯ����", 'j', 16, "�Ǳ�+15", true);
	cardnum[54].set_baseDate("��ʥ����", 'j', 15, "�Ǳ�+10����ǽ+5������+5", true);
	cardnum[55].set_baseDate("�ҽ��ɽ�", 'j', 17, "�Ǳ�+12�����ֳǱ�-6", true);
	cardnum[56].set_baseDate("����֮��", 'j', 21, "�Ǳ�+20", true);
	cardnum[57].set_baseDate("ħ�ñ�ʯ", 'j', 8, "�Ǳ�+11����ǽ-6", true);
	//�����࿨��
	cardnum[58].set_baseDate("�׶���ţ", 'M', 0, "˫������ͬʱ-6", true);
	cardnum[59].set_baseDate("�þ���Ů", 'M', 1, "2�㹥�����ٴγ���", true);
	cardnum[60].set_baseDate("��Ұ����", 'M', 1, "4�㹥������ʯ-3", true);
	cardnum[61].set_baseDate("�ٿ�ȫ��", 'M', 3, "�������+1", true);
	cardnum[62].set_baseDate("������̽", 'M', 2, "��һ���ƺ��ٴγ���", true);// ���ƺ���� 
	cardnum[63].set_baseDate("���Ҳ���", 'M', 3, "6�㹥���������⵽3�㹥��", true);
	cardnum[64].set_baseDate("Ұ������", 'M', 4, "���ֳǱ�-3�������Ǳ�-1", true);
	cardnum[65].set_baseDate("������Ů", 'M', 6, "���ֳǱ�-2,�ٴγ���", true);
	cardnum[66].set_baseDate("ʳ�˾�ħ", 'M', 3, "5�㹥��", true);
	cardnum[67].set_baseDate("���˹���", 'M', 5, "4�㹥������ǽ+3", true);
	cardnum[68].set_baseDate("���߾綾", 'M', 6, "���ֳǱ�-4", true);
	cardnum[69].set_baseDate("ѱ��ר��", 'M', 7, "�������+2", true);
	cardnum[70].set_baseDate("����֮��", 'M', 8, "2�㹥������ǽ+4���Ǳ�+2", true);
	cardnum[71].set_baseDate("��Բ֮ҹ", 'M', 0, "˫�����޲���ͬʱ+1�����ٵõ�3������", true);
	cardnum[72].set_baseDate("ɱ������", 'M', 5, "6�㹥��", true);
	cardnum[73].set_baseDate("��Ѫ��ħ", 'M', 6, "7�㹥��", true);
	cardnum[74].set_baseDate("����ħ��", 'M', 6, "6�㹥�������ֹ���-3", true);
	cardnum[75].set_baseDate("�������", 'M', 5, "6�㹥����˫��שͷ����ʯ�͹���ͬʱ-5", true);
	cardnum[76].set_baseDate("���׳�", 'M', 8, "����û�г�ǽʱ10�㹥��������6�㹥��", true);
	cardnum[77].set_baseDate("���˰���", 'M', 9, "9�㹥��", true);
	cardnum[78].set_baseDate("��Ѫɱ��", 'M', 11, "����û�г�ǽʱ7�㹥��������10�㹥��", true);
	cardnum[79].set_baseDate("��������", 'M', 9, "��ʯ�������ڶ���ʱ12�㹥��������8��", true);
	cardnum[80].set_baseDate("��������", 'M', 10, "��ǽ���ڶ���ʱ6�㹥����������ֳǱ�-6", true);
	cardnum[81].set_baseDate("����Ů��", 'M', 14, "���ֳǱ�-5������-8", true);
	cardnum[82].set_baseDate("�Ϲ�ħ��", 'M', 11, "8�㹥��������שͷ����-1", true);
	cardnum[83].set_baseDate("��Ӱ��͵", 'M', 12, "���ֱ�ʯ-10��שͷ-5����õ�����һ��", true);
	cardnum[84].set_baseDate("��ʯ����", 'M', 15, "10�㹥������ǽ+4", true);
	cardnum[85].set_baseDate("��Ѫ��ʬ", 'M', 17, "10�㹥�������ֹ���-5���������-1", true);
	cardnum[86].set_baseDate("�޵�����", 'M', 25, "20�㹥�������ֱ�ʯ-10���������-1", true);
}
void printAll(player &a, player &b, int round, card cardnum[]) {
	system("cls");
	if (round == 0)round = 1;
	cout << a.name << setw(55)<<setfill(' ') ;
	cout << "�غϣ�" << round << '/' << 30 <<  "��"<<setw(55) ;
	cout << setiosflags(ios::right) << b.name << endl;
	cout << "ש�� " << a.getbrick() << "(+" << a.getProducebrick() << ")     ��ʯ " << a.getjewel() << "(+" << a.getProducejewel() << ")     ���� " << a.getmonster() << "(+" << a.getProducemonster() << ")";
	cout << setw(36) << setfill(' ');
	cout << "ש�� " << b.getbrick() << "(+" << b.getProducebrick() << ")     ��ʯ " << b.getjewel() << "(+" << b.getProducejewel() << ")     ���� " << b.getmonster() << "(+" << b.getProducemonster() << ")";
	cout << endl;
	cout << setw(30) << setfill(' ') ;
	if (useorgive != 0) {
		if (last_player == 1) {
			cout << b.name;
			if(useorgive==1){
			cout << "�ϻغϳ��ƣ�";
			}
			else {
				cout << "�ϻغ����ƣ�";
			}
		}
		else {
			cout << a.name;
			if (useorgive == 1) {
				cout << "�ϻغϳ��ƣ�";
			}
			else {
				cout << "�ϻغ����ƣ�";
			}
		}
		if (round == 0) {
			cout << "��";
		}
		else {
			cardnum[last_handcard].show();
		}
	}
	else {
		cout << "�ϻغ�δ����";
	}
	cout << endl ;
	//��� T W 
	int x;
	int row;
	for (row = 9; row >= 0; row--) {
		cout << setw(10) << setfill(' ');
		int col;
		x = a.getcastle() / 5;
		if (x < row) {
			for (col = 0; col < 5; col++) {
				cout << ' ';
			}
		}
		if (x == row) {
			for (col = 0; col < a.getcastle() % 5; col++) {
				cout << 'T';
			}
			for (; col < 5; col++) {
				cout << ' ';
			}
		}
		if (x > row) {
			for (col = 0; col < 5; col++) {
				cout << 'T';
			}
		}
		cout << setw(10) << setfill(' ');

		x= a.getwall() / 5;
		if (x < row) {
			for (col = 0; col < 5; col++) {
				cout << ' ';
			}
		}
		if (x == row) {
			for (col = 0; col < a.getwall() % 5; col++) {
				cout << 'W';
			}
			for (; col < 5; col++) {
				cout << ' ';
			}
		}
		if (x > row) {
			for (col = 0; col < 5; col++) {
				cout << 'W';
			}
		}
		cout << setw(55) << setfill(' ');

		x = b.getwall() / 5;
		if (x < row) {
			for (col = 0; col < 5; col++) {
				cout << ' ';
			}
		}
		if (x == row) {
			for (col = 0; col < b.getwall() % 5; col++) {
				cout << 'W';
			}
			for (; col < 5; col++) {
				cout << ' ';
			}
		}
		if (x > row) {
			for (col = 0; col < 5; col++) {
				cout << 'W';
			}
		}
		cout << setw(10) << setfill(' ');

		x = b.getcastle() / 5;
		if (x < row) {
			for (col = 0; col < 5; col++) {
				cout << ' ';
			}
		}
		if (x == row) {
			for (col = 0; col < b.getcastle() % 5; col++) {
				cout << 'T';
			}
			for (; col < 5; col++) {
				cout << ' ';
			}
		}
		if (x > row) {
			for (col = 0; col < 5; col++) {
				cout << 'T';
			}
		}
		cout << setw(10) << setfill(' ');
		cout << endl;
	}
	cout << setw(8) << setfill(' ');
	cout << "��" << a.getcastle() << "/" << "50" << ")      ";
	cout << setw(8) << setfill(' ');
	cout << a.getwall() << setw(59) << setfill(' ');
	cout << b.getwall() <<setw(8) << setfill(' ');
	cout<< "(" << b.getcastle() << "/" << "50" << ")" << endl;
	
}
void print_All(player &a, card cardnum[]) {
	cout << endl;
	cout << a.name << "������" << endl;
	for (int i = 0; i <= 5; i++) {			//����
		cout << i + 1 << ' ';
		cardnum[a.handcard[i]].show();
		cout << endl;
	}

	cout << a.name << "���ƣ��ɳ�";
	
	bool temp = false;
	int i;
	for ( i = 0; i <= 5; i++) {
		if (cardnum[a.handcard[i]].Isresource(a)) {
			if (!temp) {
				cout << (i+1);
				temp = true;
			}
			else {
				cout << "," << (i + 1);
			}
		}
	}
	temp = false;
	cout << "; �ɷ���";
	for (int i = 0; i <= 5; i++) {
		if (!cardnum[a.handcard[i]].Isresource(a)) {
			if (!temp) {
				cout << i + 1;
				temp = true;
			}
			else {
				cout << "," << i + 1;
			}
		}
	}
	cout << "):";
}
void AllCard(player &a, player &b, int n,card cardnum[87]) {			// nΪ�����������е����
	int x = a.handcard[n-1];
	switch (x) {
		case 0: {						// ���� 0 
				cardnum[0].Bothbrick(a, b, -8, -8);
			break;
		}

		case 1: {
				cardnum[1].Dealbrick(a, 2);
				cardnum[1].Dealjewel(a, 2);
				Isagain = true;
			break;
		}
		case 2: {
				cardnum[2].Dealbrick(a, -1);
				cardnum[2].Dealwall(a, 1);
				Isagain = true;
			//�ٳ�һ���� 		
			break;
		}
		case 3: {
			cardnum[3].Dealbrick(a, -3);
			cardnum[3].Producebrick(a, 1);
			break;
		}
		case 4: {
				cardnum[4].Dealbrick(a, -4);
				cardnum[4].CompareProducebrick(a, b, 2, 1);
		
			break;
		}
		case 5: {
				cardnum[5].Dealbrick(a, -7);
				cardnum[5].Dealwall(a, 4);
				cardnum[5].Producebrick(a, 1);
		
			break;
		}
		case 6: {
				cardnum[6].Dealbrick(a, -2);
				cardnum[6].Dealwall(a, 5);
				cardnum[6].Dealjewel(a, -6);
		
		
			break;
		}
		case 7: {
				cardnum[7].Dealbrick(a, -5);
				cardnum[7].CompareProducebrick(a, b);
		

			break;
		}
		case 8: {
				cardnum[8].Dealbrick(a, -2);
				cardnum[8].Dealwall(a, 3);
		

			break;
		}
		case 9: {
				cardnum[9].Dealbrick(a, -3);
				cardnum[9].Dealwall(a, 4);
		
	
			break;
		}
		case 10: {
				cardnum[10].Dealbrick(a, -2);
				cardnum[10].BothProducebrick(a, b, 1);
				cardnum[10].Dealjewel(a, 4);
		
			break;
		}
		case 11: {
				cardnum[11].Dealbrick(a, -3);
				if (cardnum[11].Iswall(a)) {
					cardnum[11].Dealwall(a, 3);
				}
				else {
					cardnum[11].Dealwall(a, 6);
				}
		
			break;
		}
		case 12: {
				cardnum[12].Dealbrick(a, -7);
				cardnum[12].Bothwall(a, b, -5, -5);
				Isagain = true;
		
			//�ٴγ��� 
			break;
		}
		case 13: {
				cardnum[13].Dealbrick(a, -8);
				cardnum[13].Producejewel(a, 1);
				Isagain = true;
			//�ٴγ���

			break;
		}
		case 14: {
				cardnum[14].BothProducebrick(a, b, -1);
		
			break;
		}
		case 15: {
				cardnum[15].Dealbrick(a, -5);
				cardnum[15].Dealwall(a, 6);
		
			break;
		}
		case 16: {
				cardnum[16].Dealbrick(a, -4);
				cardnum[16].BothProducebrick(a, b, -1);
		
			break;
		}
		case 17: {
				cardnum[17].Dealbrick(a, -6);
				cardnum[17].Producebrick(a, 2);
		
			break;
		}
		case 18: {
				cardnum[18].Producebrick(a, -1);
				cardnum[18].Dealwall(a, 10);
				cardnum[18].Dealjewel(a, 5);
			break;
		}
		case 19: {
				cardnum[19].Dealbrick(a, -8);
				cardnum[19].Dealwall(a, 8);

			break;
		}
		case 20: {
				cardnum[20].Dealbrick(a, -9);
				cardnum[20].Dealwall(a, 5);
				cardnum[20].Producemonster(a, 1);
			break;
		}
		case 21: {
				cardnum[21].Dealbrick(a, -9);
				cardnum[21].Dealwall(a, 7);
				cardnum[21].Dealjewel(a, 7);
			break;
		}
		case 22: {
				cardnum[22].Dealbrick(a, -11);
				cardnum[21].Dealwall(a, 6);
				cardnum[21].Dealcastle(a, 3);
			break;
		}
		case 23: {
				cardnum[23].Dealbrick(a, -13);
				cardnum[21].Dealwall(a, 12);

			break;
		}
		case 24: {
				cardnum[24].Dealbrick(a, -15);
				cardnum[21].Dealwall(a, 8);
				cardnum[21].Dealcastle(a, 5);
			break;
		}
		case 25: {
				cardnum[25].Dealbrick(a, -16);
				cardnum[25].Dealwall(a, 15);

			break;
		}
		case 26: {
				cardnum[26].Dealbrick(a, -18);
				cardnum[26].Dealwall(a, 6);
				cardnum[26].Dealwall(b, -10);
			break;
		}
		case 27: {
				cardnum[27].Dealbrick(a, -24);
				cardnum[27].Dealwall(a, 20);
				cardnum[27].Dealcastle(a, 8);
			break;
		}
		case 28: {
				cardnum[28].Dealbrick(a, -7);
				cardnum[28].Dealmonster(a, -5);
				cardnum[28].Dealwall(a, 9);

			break;
			//���� ש���࿨����� 
		}

		case 29: {
				cardnum[29].Dealjewel(a, -cardnum[29].getprice());
				cardnum[29].Dealcastle(a, 1);
				Isagain = true;
			//�ٴγ���

			break;
		}
		case 30: {
				cardnum[30].Dealjewel(a, -cardnum[30].getprice());
				cardnum[30].Dealwall(b, -1);
				Isagain = true;
			//�ٴγ���
			break;
		}
		case 31: {
				cardnum[31].Dealjewel(a, -cardnum[31].getprice());
				cardnum[31].Dealcastle(a, 3);
		
			break;
		}
		case 32: {
				cardnum[32].Dealjewel(a, -cardnum[32].getprice());
				cardnum[32].Producejewel(a, 1);

			
			break;
		}
		case 33: {
				cardnum[33].Dealjewel(a, -cardnum[33].getprice());
				changeCard(a, cardnum, n);
				Isagain = true;
			//�ٴ� ����
			break;
		}
		case 34: {
				cardnum[34].Dealjewel(a, -cardnum[34].getprice());
				cardnum[34].Dealcastle(a, 3);

			break;
		}
		case 35: {
				cardnum[35].Dealjewel(a, -cardnum[35].getprice());
				cardnum[35].Bothcastle(a, b, 2, -2);
			break;
		}
		case 36: {
				cardnum[36].Dealjewel(a, -cardnum[36].getprice());
				cardnum[36].Producejewel(a, 1);
				cardnum[36].Bothcastle(a, b, 3, 1);
		
		
			break;
		}
		case 37: {
				cardnum[37].Dealjewel(a, -cardnum[37].getprice());
				cardnum[37].Dealcastle(b, -3);
		
	
			break;
		}
		case 38: {
				cardnum[38].Dealjewel(a, -cardnum[38].getprice());
				cardnum[38].Dealcastle(a, 5);
		
	
			break;
		}
		case 39: {
				cardnum[39].Dealjewel(a, -cardnum[39].getprice());
				cardnum[39].Dealcastle(a, -5);
	

			break;
		}
		case 40: {
				cardnum[40].Dealjewel(a, -cardnum[40].getprice());
				cardnum[40].Producejewel(a, 2);
				cardnum[40].Dealcastle(b, -5);
	
			break;
		}
		case 41: {
				cardnum[41].Dealjewel(a, -cardnum[41].getprice());
				cardnum[41].Producejewel(a, 1);
				cardnum[41].Dealcastle(a, 3);
				cardnum[41].Dealwall(a, 3);
	
			break;
		}
		case 42: {
				cardnum[42].Dealjewel(a, -cardnum[42].getprice());
				cardnum[42].CompareProducejewel(a, b);
		
			break;
		}
		case 43: {
				cardnum[43].Dealjewel(a, -cardnum[43].getprice());
				cardnum[43].Dealcastle(a, 8);
	
			break;
		}
		case 44: {
				cardnum[44].Dealjewel(a, -cardnum[44].getprice());
				cardnum[44].Producejewel(a, 1);
				cardnum[44].Dealcastle(a, 5);
		
			break;
		}
		case 45: {
				cardnum[45].Dealjewel(a, -cardnum[45].getprice());
				cardnum[45].Producejewel(a, -1);
				cardnum[45].Dealcastle(b, -9);
	
			break;
		}
		case 46: {
				cardnum[46].Dealjewel(a, -cardnum[46].getprice());
				cardnum[46].Dealcastle(a, 5);
				cardnum[46].Dealbrick(b, -6);
		
			break;
		}
		case 47: {
				cardnum[47].Dealjewel(a, -cardnum[47].getprice());
				cardnum[47].Dealcastle(a, 11);
	
			break;
		}
		case 48: {
				cardnum[48].Dealjewel(a, -cardnum[48].getprice());
				cardnum[48].Bothcastle(a, b, -7, -7);
				cardnum[48].BothProducejewel(a, b, -1, -1);
	
			break;
		}
		case 49: {
				cardnum[49].Dealjewel(a, -cardnum[49].getprice());
				cardnum[49].Bothcastle(a, b, +6, -4);
		
			break;
		}
		case 50: {
				cardnum[50].Dealjewel(a, -cardnum[50].getprice());
				cardnum[50].Dealcastle(a, 7);
				cardnum[50].Dealbrick(a, -10);
		
			break;
		}
		case 51: {
				cardnum[51].Dealjewel(a, -cardnum[51].getprice());
				cardnum[51].Dealwall(a, 3);
				cardnum[51].Dealcastle(a, 8);
		
			break;
		}
		case 52: {
				cardnum[52].Dealjewel(a, -cardnum[52].getprice());
				cardnum[52].Producemonster(a, 1);
				cardnum[52].Dealcastle(a, 8);
		
			break;
		}
		case 53: {
				cardnum[53].Dealjewel(a, -cardnum[53].getprice());
				cardnum[53].Dealcastle(a, 15);
		
			break;
		}
		case 54: {
				cardnum[54].Dealjewel(a, -cardnum[54].getprice());
				cardnum[54].Dealcastle(a, 10);
				cardnum[54].Dealwall(a, 5);
				cardnum[54].Dealmonster(a, 5);
		
			break;
		}
		case 55: {
				cardnum[55].Dealjewel(a, -cardnum[55].getprice());
				cardnum[55].Bothcastle(a, b, 12, -6);
	
			break;
		}
		case 56: {
				cardnum[56].Dealjewel(a, -cardnum[56].getprice());
				cardnum[56].Dealcastle(a, 20);
	
			break;
		}
		case 57: {
				cardnum[57].Dealjewel(a, -cardnum[57].getprice());
				cardnum[57].Dealcastle(a, 11);
				cardnum[57].Dealwall(a, -6);
		
			break;
		}
				 //���� ��ʯ�����
		case 58: {
				cardnum[58].Dealmonster(a, -cardnum[58].getprice());
				cardnum[58].Bothmonster(a, b, -6, -6);
		
			break;
		}
		case 59: {
				cardnum[59].Dealmonster(a, -cardnum[59].getprice());
				cardnum[59].Dealwall(b, 2); 
				Isagain = true;
			//�ٴγ���
			break;
		}
		case 60: {
				cardnum[60].Dealmonster(a, -cardnum[60].getprice());
				cardnum[60].Dealwall(b, -4);
				cardnum[60].Dealjewel(a, -3);
		
			break;
		}
		case 61: {
				cardnum[61].Dealmonster(a, -cardnum[61].getprice());
				cardnum[61].Producemonster(a, 1);
	
			break;
		}
		case 62: {
				cardnum[62].Dealmonster(a, -cardnum[62].getprice());
				once :
				cout << "���������뻻���ƣ�(" << n << "����)";
				int change;
				cin >> change;
				if (!cardnum[a.handcard[change - 1]].getchange()) {
					cout << "���Ʋ��ɻ���ֻ�ɴ����" << endl;
					goto once;
				}
				else {
					changeCard(a, cardnum, change);
					Isagain = true;
				}
				//���ƺ����
			break;
		}
		case 63: {
				cardnum[63].Dealmonster(a, -cardnum[63].getprice());
				cardnum[63].Dealwall(a, -3);
				cardnum[63].Dealwall(b, -6);
			break;
		}
		case 64: {
				cardnum[64].Dealmonster(a, -cardnum[64].getprice());
				cardnum[64].Dealcastle(a, -1);
				cardnum[64].Dealcastle(b, -3);
			break;
		}
		case 65: {
				cardnum[65].Dealmonster(a, -cardnum[65].getprice());
				cardnum[65].Dealcastle(b, -2);
				Isagain = true;
				//�ٴγ���
			break;
		}
		case 66: {
				cardnum[66].Dealmonster(a, -cardnum[66].getprice());
				cardnum[66].Dealwall(b, -5);
			break;
		}
		case 67: {
				cardnum[67].Dealmonster(a, -cardnum[67].getprice());
				cardnum[67].Dealwall(b, -4);
				cardnum[67].Dealwall(a, 3);
			break;
		}
		case 68: {
				cardnum[68].Dealmonster(a, -cardnum[68].getprice());
				cardnum[68].Dealcastle(b, -4);
			break;
		}
		case 69: {
				cardnum[69].Dealmonster(a, -cardnum[69].getprice());
				cardnum[69].Producemonster(a, 2);
		
			break;
		}
		case 70: {
				cardnum[70].Dealmonster(a, -cardnum[70].getprice());
				cardnum[70].Dealwall(b, -2);
				cardnum[70].Dealwall(a, 4);
				cardnum[70].Dealcastle(a, 2);
			break;
		}
		case 71: {
				cardnum[71].Dealmonster(a, -cardnum[71].getprice());
				cardnum[71].Producemonster(a, 1);
				cardnum[71].Producemonster(b, 1);
				cardnum[71].Dealmonster(a, 3);
			break;
		}
		case 72: {
				cardnum[72].Dealmonster(a, -cardnum[72].getprice());
				cardnum[72].Dealwall(b, -6);
			break;
		}
		case 73: {
				cardnum[73].Dealmonster(a, -cardnum[73].getprice());
				cardnum[73].Dealwall(b, -7);
		
			break;
		}
		case 74: {
				cardnum[74].Dealmonster(a, -cardnum[74].getprice());
				cardnum[74].Dealwall(b, -6);
				cardnum[74].Dealmonster(b, -3);
			break;
		}
		case 75: {
				cardnum[75].Dealmonster(a, -cardnum[75].getprice());
				cardnum[75].Dealwall(b, -6);
				cardnum[75].Bothbrick(a, b, -5, -5);
				cardnum[75].Bothmonster(a, b, -5, -5);
				cardnum[75].Bothjewel(a, b, -5, -5);

			break;
		}
		case 76: {
				cardnum[76].Dealmonster(a, -cardnum[76].getprice());
				if (cardnum[76].Iswall(b)) {
					cardnum[76].Dealwall(b, -6);
				}
				else {
					cardnum[76].Dealcastle(b, -10);
				}
			break;
		}
		case 77: {
				cardnum[77].Dealmonster(a, -cardnum[77].getprice());
				cardnum[77].Dealwall(b, -9);
		
			break;
		}
		case 78: {
				cardnum[78].Dealmonster(a, -cardnum[78].getprice());
				if (cardnum[78].Iswall(b)) {
					cardnum[78].Dealwall(b, -10);
				}
				else {
					cardnum[78].Dealcastle(b, -7);
				}
		
			break;
		}
		case 79: {
				cardnum[79].Dealmonster(a, -cardnum[79].getprice());
				if (cardnum[79].IsCompareProducejewel(a, b)) {
					cardnum[79].Dealwall(b, -12);
				}
				else {
					cardnum[79].Dealwall(b, -8);
				}
			break;
		}
		case 80: {
				cardnum[80].Dealmonster(a, -cardnum[80].getprice());
				if (cardnum[80].IsComparewall(a, b)) {
					cardnum[80].Dealwall(b, -6);
				}
				else {
					cardnum[80].Dealcastle(b, -6);
				}
			break;
		}
		case 81: {
				cardnum[81].Dealmonster(a, -cardnum[81].getprice());
				cardnum[81].Dealcastle(b, -5);
				cardnum[81].Dealmonster(b, -8);
			break;
		}
		case 82: {
				cardnum[82].Dealmonster(a, -cardnum[82].getprice());
				cardnum[82].Dealwall(b, -8);
				cardnum[82].Producebrick(b, -1);

		
			break;
		}
		case 83: {
				cardnum[83].Dealmonster(a, -cardnum[83].getprice());
				cardnum[83].Dealjewel(b, -10);
				cardnum[83].Dealbrick(b, -5);
				cardnum[83].Dealjewel(a, 5);
				cardnum[83].Dealbrick(a, 2);
			break;
		}
		case 84: {
				cardnum[84].Dealmonster(a, -cardnum[84].getprice());
				cardnum[84].Dealwall(b, -10);
				cardnum[84].Dealwall(a, 4);
			break;
		}
		case 85: {
				cardnum[85].Dealmonster(a, -cardnum[85].getprice());
				cardnum[85].Dealwall(b, -10);
				cardnum[85].Dealmonster(b, -5);
				cardnum[85].Producemonster(b, -1);
			break;
		}
		case 86: {
				cardnum[86].Dealmonster(a, -cardnum[86].getprice());
				cardnum[86].Dealwall(b, -20);
				cardnum[86].Dealjewel(b, -10);
				cardnum[86].Producemonster(b, -1);
		
			break;
		}
				 //���˹����࿨��ȫ������
	}
	checkAll(a, b);
}
/*------------------------------��ʼ��-------------------------------*/
int Rand() {
	srand((unsigned)time(0));
	return rand() % 87;
}
void initialization(player &a, player &b) {
	srand((unsigned)time(0));
	cout << "���������һ��������";
	char _name[10];
	cin.getline(_name, 10);
	a.setname(_name);
	cout << "��������Ҷ���������";
	cin.getline(_name, 10);
	b.setname(_name);
	for (int i = 0; i <= 5; i++) {		//p1��ʼ������ 
		a.handcard[i] = rand() % 87;
	}
	for (int i = 0; i <= 5; i++) {		//p2��ʼ������ 
		b.handcard[i] = rand() % 87;
	}

	//�����ʼ�������ļ�
	char room[10];
	int _wall, _castle, _brick, _Producebrick, _jewel, _Producejewel, _monster, _Producemonster;
	ifstream input("Initialization.txt", ios::in);
	if (! input) {
		cout << "Open Initialization file error!" << endl;
		exit(-1);
	}
	input >> room >> _castle >> room >> _wall >> room >> _brick >> room >> _jewel >> room >> _monster >> room >> _Producebrick >> room >> _Producejewel >> room >> _Producemonster >> room >> winner_wall >> room >> winner_resource >> room >> winner_round;
	input.close();
	a.setbaseDate(_castle, _wall, _brick, _Producebrick, _jewel, _Producejewel, _monster, _Producemonster);
	b.setbaseDate(_castle, _wall, _brick, _Producebrick, _jewel, _Producejewel, _monster, _Producemonster);
}
/*-----------------------------��ʤ����-------------------------------*/
bool winner_resources(player &a, player &b) {		//��Դ��ʤ ���ڻغϿ�ʼ�� 
	if ((a.getbrick() >= winner_resource) && (a.getjewel() >= winner_resource) &&( a.getmonster() >= winner_resource) && (a.getbrick() >= winner_resource )&& (a.getjewel() >= winner_resource )&& (a.getmonster() >= winner_resource))
	{
		cout << "ƽ��" << endl;
		return true;
	}
	if (a.getbrick() >= winner_resource && a.getjewel() >= winner_resource && a.getmonster() >= winner_resource)
	{
		cout << a.name << "ʤ��" << endl;
		return true;
	}
	if (b.getbrick() >= winner_resource && b.getjewel() >= winner_resource && b.getmonster() >= winner_resource)
	{
		cout << b.name << "ʤ��" << endl;
		return true;
	}
	return false;
}
bool winner_castle(player &a, player &b) {		//�Ǳ����� ���ڻغϽ���ǰ 
	if ((!a.getcastle() && !b.getcastle()) || (a.getcastle() >= 50 && b.getcastle() >= 50))
	{
		cout << "ƽ��" << endl;
		return true;
	}
	if (!a.getcastle() || b.getcastle() >= 50)
	{
		cout << b.name << "ʤ��" << endl;
		return true;
	}
	if (!b.getcastle() || a.getcastle() >= 50)
	{
		cout << a.name << "ʤ��" << endl;
		return true;
	}
	return false;
}
void changeCard(player &a,card cardnum[],int n) {
	a.handcard[n - 1] = Rand();
}
/*-----------------------------��ʼ����-----------------------------------*/
void start() {
	cout << "";
}
int main() {
	player a;
	player b;
	card cardnum[87];
	set_Allcard(cardnum);
	initialization(a, b);
	int round=1,num;
	while ((round/2) != winner_round) {
		if ((round/2) == winner_round) {
			cout << "ƽ��" << endl;
		}
		if (winner_resources(a, b)) { 
			break; 
		}
		
		if (round % 2) {
			if (!Isagain)a.Produce_All();
			printAll(a, b, (round / 2), cardnum);
				print_All(a, cardnum);
				cin >> num;
				last_handcard = a.handcard[num-1];
				last_player = 0;
				if (cardnum[a.handcard[num - 1]].Isresource(a)) {
					AllCard(a, b, num, cardnum);//�������ú���
					changeCard(a, cardnum, num);//���óɹ��� ���ƻ���
					useorgive = 1;
				} 
				else{
					changeCard(a, cardnum, num);	//������ƣ����ƣ�
					useorgive = 2;
				}
				if (winner_castle(a, b))break;
				if (!Isagain) {
					round++;
				}
				else {
					Isagain = false;
				}
		}
		else {
			if (!Isagain)b.Produce_All();
			printAll(a, b, (round / 2), cardnum);
			print_All(b, cardnum);
			cin >> num;
			last_handcard = b.handcard[num - 1];
			last_player = 1;
			if (cardnum[b.handcard[num - 1]].Isresource(b)) {
				AllCard(b, a, num, cardnum);//�������ú���
				changeCard(b, cardnum, num);//���óɹ��� ���ƻ���
				useorgive = 1;
			}
			else {
				changeCard(b, cardnum, num);	//������ƣ����ƣ�
				useorgive = 2;
			}
			if (winner_castle(b, a))break;
			if (!Isagain) {
				round++;
			}
			else {
				Isagain = false;
			}
		}
	}
	return 0;
}
