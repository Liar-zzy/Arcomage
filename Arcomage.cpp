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
class player {			//设置玩家类 
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
	void setname(char *a) {		//玩家姓名 
		strcpy(name, a);
	}
	int getcastle() { return castle; }  //得到各个资源的 量
	int getwall() { return wall; }
	int getbrick() { return brick; }
	int getProducebrick() { return Producebrick; }
	int getjewel() { return jewel; }
	int getProducejewel() { return Producejewel; }
	int getmonster() { return monster; }
	int getProducemonster() { return Producemonster; }

	void setcastle(int n) {	castle = n;}   //改变各个资源的量
	void setwall(int n) {	wall = n;	}
	void setbrick(int n) {	brick = n;	}
	void setProducebrick(int n) {	Producebrick = n;	}	
	void setjewel(int n) {	jewel = n;	}
	void setProducejewel(int n) {	Producejewel = n;	}
	void setmonster(int n) {	monster = n;}
	void setProducemonster(int n) {	Producemonster = n;	}

	void setbaseDate(int castle, int wall, int brick, int Producebrick, int jewel, int Producejewel, int monster, int Producemonster) {//初始化 
		this->castle = castle;
		this->wall = wall;
		this->brick = brick;
		this->Producebrick = Producebrick;
		this->jewel = jewel;
		this->Producejewel = Producejewel;
		this->monster = monster;
		this->Producemonster = Producemonster;
	}
	void Produce_All() {			//用来每回合 生产各个资源 
		brick += Producebrick;
		jewel += Producejewel;
		monster += Producemonster;
	}
	friend class card;
};
class card {		//卡牌类
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
	void show() {		//输出卡牌名字种类花费及作用 
		cout << "<" << name << ">" << "(" << (kind == 'b' ? "砖头" : (kind == 'j' ? "宝石" : "怪物")) << price << ")" << effect;
	}
	int getprice() {return price;	}//返回 花费 
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
	bool Iswall(player &a) {		//判断是否还有墙 以用来攻击 城堡 
		if (a.wall > 0)return true;
		return false;
	}
	void Dealcastle(player &a, int b) {		//处理城堡 
		a.castle += b;
	}
	void Dealwall(player &a, int b) {			//处理墙 
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
	void Dealbrick(player &a, int b) {		//处理砖块 
		a.brick += b;
	}
	void Producebrick(player &a, int b) {			//控制砖块产量 
		a.Producebrick += b;
	}
	void Dealjewel(player &a, int b) {		//处理宝石 
		a.jewel += b;
	}
	void Producejewel(player &a, int b) {	a.Producejewel += b;	}//控制宝石产量
	void Dealmonster(player &a, int b) {	a.monster += b;	}//处理怪物 
	void Producemonster(player &a, int b) {		a.Producemonster += b;	}//控制怪物产量
	void Bothwall(player &a, player &b, int c, int d) {			//对双方造成影响的卡牌 墙 城堡 砖块iuy 
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
void checkAll(player &a, player &b) {	//检测 因为对方出牌使双方 各种材料是否为负数 若负数 则清零 
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
/*---------------------------输出所有内容----------------------------*/
void set_Allcard(card cardnum[87]) {
	//砖块类卡牌
	cardnum[0].set_baseDate("生死抗争", 'b', 0, "双方同时失去8块砖头", true);
	cardnum[1].set_baseDate("幸运宝藏", 'b', 0, "砖头+2，宝石+2，再次出牌", true);
	cardnum[2].set_baseDate("友谊之地", 'b', 1, "城墙+1，再次出牌", true);
	cardnum[3].set_baseDate("伟大矿工", 'b', 3, "砖头产量+1", true);
	cardnum[4].set_baseDate("矿石之脉", 'b', 4, "如果砖头产量少于对手，则砖头产量+2", true);
	cardnum[5].set_baseDate("矮人之矿", 'b', 7, "城墙+4，砖头产量+1", true);
	cardnum[6].set_baseDate("努力工作", 'b', 2, "城墙+5，宝石-6", true);
	cardnum[7].set_baseDate("幻影之手", 'b', 5, "如果砖头产量少于对手，则砖头产量等于对手", true);
	cardnum[8].set_baseDate("基础之墙", 'b', 2, "城墙+3", true);
	cardnum[9].set_baseDate("稳固之墙", 'b', 3, "城墙+4", true);
	cardnum[10].set_baseDate("发明创造", 'b', 2, "双方砖头产量同时+1，你还得到4个宝石", true);
	cardnum[11].set_baseDate("稳固基础", 'b', 3, "如果没有城墙则城墙+6，否则城墙+3", true);
	cardnum[12].set_baseDate("颤动之地", 'b', 7, "双方城墙同时-5，再次出牌", true);
	cardnum[13].set_baseDate("神秘小屋", 'b', 8, "宝石产量+1，再次出牌", true);
	cardnum[14].set_baseDate("山崩地裂", 'b', 0, "双方砖头产量同时-1", true);
	cardnum[15].set_baseDate("雄伟之墙", 'b', 5, "城墙+6", true);
	cardnum[16].set_baseDate("粉碎之锤", 'b', 4, "对手砖头产量-1", true);
	cardnum[17].set_baseDate("完美工具", 'b', 6, "砖头产量+2", true);
	cardnum[18].set_baseDate("矮人之锤", 'b', 0, "砖头产量-1，城墙+10，宝石+5", true);
	cardnum[19].set_baseDate("神奇之石", 'b', 8, "城墙+8", true);
	cardnum[20].set_baseDate("神秘之力", 'b', 9, "城墙+5，怪物产量+1", true);
	cardnum[21].set_baseDate("奇幻宝石", 'b', 9, "城墙+7，宝石+7", true);
	cardnum[22].set_baseDate("幻想乐曲", 'b', 11, "城墙+8，城堡+3", true);
	cardnum[23].set_baseDate("牢不可破", 'b', 13, "城墙+12", true);
	cardnum[24].set_baseDate("完美设计", 'b', 15, "城墙+8，城堡+5", true);
	cardnum[25].set_baseDate("魔幻之墙", 'b', 16, "城墙+15", true);
	cardnum[26].set_baseDate("巨石轰击", 'b', 18, "城墙+6，对手城墙-10", true);
	cardnum[27].set_baseDate("神龙之心", 'b', 24, "城墙+20，城堡+8", true);
	cardnum[28].set_baseDate("死命工作", 'b', 7, "城墙+9，怪物-5", true);
	//宝石类卡牌
	cardnum[29].set_baseDate("蓝色宝石", 'j', 1, "城堡+1，再次出牌", true);
	cardnum[30].set_baseDate("奇幻之烟", 'j', 2, "对手城堡-1，再次出牌", true);
	cardnum[31].set_baseDate("迷幻之手", 'j', 2, "城堡+3", true);
	cardnum[32].set_baseDate("魔法高手", 'j', 3, "宝石产量+1", true);
	cardnum[33].set_baseDate("三棱魔镜", 'j', 2, "换一张牌后再次出牌", true);
	cardnum[34].set_baseDate("怪物缠身", 'j', 5, "城堡+3，这张牌不能换，只能使用", false);
	cardnum[35].set_baseDate("阳光普照", 'j', 4, "城堡+2，对手城堡-2", true);
	cardnum[36].set_baseDate("钻石魔阵", 'j', 6, "宝石产量+1，城堡+3，对手城堡+1", true);
	cardnum[37].set_baseDate("宝石裂痕", 'j', 2, "对手城堡-3", true);
	cardnum[38].set_baseDate("深红宝石", 'j', 3, "城堡+5", true);
	cardnum[39].set_baseDate("水晶之矛", 'j', 4, "对手城堡-5", true);
	cardnum[40].set_baseDate("焚心以火", 'j', 3, "宝石产量+2，城堡-5", true);
	cardnum[41].set_baseDate("忠诚代价", 'j', 7, "宝石产量+1，城堡+3，城墙+3", true);
	cardnum[42].set_baseDate("公平竞争", 'j', 7, "双方宝石产量都等于产量高的一方", true);
	cardnum[43].set_baseDate("神奇翡翠", 'j', 6, "城堡+8", true);
	cardnum[44].set_baseDate("智慧珍珠", 'j', 9, "宝石产量+1，城堡+5", true);
	cardnum[45].set_baseDate("赌命狂徒", 'j', 8, "宝石产量-1，对手城堡-9", true);
	cardnum[46].set_baseDate("崩溃之石", 'j', 7, "城堡+5，对手砖头-6", true);
	cardnum[47].set_baseDate("蓝色水晶", 'j', 10, "城堡+11", true);
	cardnum[48].set_baseDate("生死相斗", 'j', 5, "双方宝石产量同时-1、城堡同时-7", true);
	cardnum[49].set_baseDate("幻火之石", 'j', 13, "城堡+6，对手城堡-4", true);
	cardnum[50].set_baseDate("巨人奴仆", 'j', 4, "城堡+7，砖头-10", true);
	cardnum[51].set_baseDate("水晶护身", 'j', 12, "城堡+8，城墙+3", true);
	cardnum[52].set_baseDate("心领神会", 'j', 14, "城堡+8，怪物产量+1", true);
	cardnum[53].set_baseDate("钻石永恒", 'j', 16, "城堡+15", true);
	cardnum[54].set_baseDate("神圣领域", 'j', 15, "城堡+10，城墙+5，怪物+5", true);
	cardnum[55].set_baseDate("岩浆飞溅", 'j', 17, "城堡+12，对手城堡-6", true);
	cardnum[56].set_baseDate("神龙之眼", 'j', 21, "城堡+20", true);
	cardnum[57].set_baseDate("魔幻宝石", 'j', 8, "城堡+11，城墙-6", true);
	//怪物类卡牌
	cardnum[58].set_baseDate("凶恶蛮牛", 'M', 0, "双方怪物同时-6", true);
	cardnum[59].set_baseDate("幻境仙女", 'M', 1, "2点攻击，再次出牌", true);
	cardnum[60].set_baseDate("狂野蛮族", 'M', 1, "4点攻击，宝石-3", true);
	cardnum[61].set_baseDate("百科全书", 'M', 3, "怪物产量+1", true);
	cardnum[62].set_baseDate("精灵密探", 'M', 2, "换一张牌后再次出牌", true);// 换牌后出牌 
	cardnum[63].set_baseDate("敌我不分", 'M', 3, "6点攻击，己方遭到3点攻击", true);
	cardnum[64].set_baseDate("野蛮箭手", 'M', 4, "对手城堡-3，己方城堡-1", true);
	cardnum[65].set_baseDate("神奇仙女", 'M', 6, "对手城堡-2,再次出牌", true);
	cardnum[66].set_baseDate("食人巨魔", 'M', 3, "5点攻击", true);
	cardnum[67].set_baseDate("矮人工匠", 'M', 5, "4点攻击，城墙+3", true);
	cardnum[68].set_baseDate("灵蛇剧毒", 'M', 6, "对手城堡-4", true);
	cardnum[69].set_baseDate("驯兽专家", 'M', 7, "怪物产量+2", true);
	cardnum[70].set_baseDate("高塔之妖", 'M', 8, "2点攻击，城墙+4，城堡+2", true);
	cardnum[71].set_baseDate("月圆之夜", 'M', 0, "双方怪兽产量同时+1，你再得到3个怪兽", true);
	cardnum[72].set_baseDate("杀手无情", 'M', 5, "6点攻击", true);
	cardnum[73].set_baseDate("嗜血巨魔", 'M', 6, "7点攻击", true);
	cardnum[74].set_baseDate("恶灵魔兽", 'M', 6, "6点攻击，对手怪物-3", true);
	cardnum[75].set_baseDate("恶鬼作怪", 'M', 5, "6点攻击，双方砖头、宝石和怪物同时-5", true);
	cardnum[76].set_baseDate("喷火甲虫", 'M', 8, "对手没有城墙时10点攻击，否则6点攻击", true);
	cardnum[77].set_baseDate("半人半狼", 'M', 9, "9点攻击", true);
	cardnum[78].set_baseDate("冷血杀手", 'M', 11, "对手没有城墙时7点攻击，否则10点攻击", true);
	cardnum[79].set_baseDate("独角神兽", 'M', 9, "宝石产量多于对手时12点攻击，否则8点", true);
	cardnum[80].set_baseDate("精灵射手", 'M', 10, "城墙少于对手时6点攻击，否则对手城堡-6", true);
	cardnum[81].set_baseDate("绝命女妖", 'M', 14, "对手城堡-5、怪物-8", true);
	cardnum[82].set_baseDate("上古魔兽", 'M', 11, "8点攻击，对手砖头产量-1", true);
	cardnum[83].set_baseDate("无影神偷", 'M', 12, "对手宝石-10，砖头-5，你得到其中一半", true);
	cardnum[84].set_baseDate("岩石巨人", 'M', 15, "10点攻击，城墙+4", true);
	cardnum[85].set_baseDate("吸血僵尸", 'M', 17, "10点攻击，对手怪物-5，怪物产量-1", true);
	cardnum[86].set_baseDate("无敌天龙", 'M', 25, "20点攻击，对手宝石-10，怪物产量-1", true);
}
void printAll(player &a, player &b, int round, card cardnum[]) {
	system("cls");
	if (round == 0)round = 1;
	cout << a.name << setw(55)<<setfill(' ') ;
	cout << "回合（" << round << '/' << 30 <<  "）"<<setw(55) ;
	cout << setiosflags(ios::right) << b.name << endl;
	cout << "砖块 " << a.getbrick() << "(+" << a.getProducebrick() << ")     宝石 " << a.getjewel() << "(+" << a.getProducejewel() << ")     怪物 " << a.getmonster() << "(+" << a.getProducemonster() << ")";
	cout << setw(36) << setfill(' ');
	cout << "砖块 " << b.getbrick() << "(+" << b.getProducebrick() << ")     宝石 " << b.getjewel() << "(+" << b.getProducejewel() << ")     怪物 " << b.getmonster() << "(+" << b.getProducemonster() << ")";
	cout << endl;
	cout << setw(30) << setfill(' ') ;
	if (useorgive != 0) {
		if (last_player == 1) {
			cout << b.name;
			if(useorgive==1){
			cout << "上回合出牌：";
			}
			else {
				cout << "上回合弃牌：";
			}
		}
		else {
			cout << a.name;
			if (useorgive == 1) {
				cout << "上回合出牌：";
			}
			else {
				cout << "上回合弃牌：";
			}
		}
		if (round == 0) {
			cout << "无";
		}
		else {
			cardnum[last_handcard].show();
		}
	}
	else {
		cout << "上回合未出牌";
	}
	cout << endl ;
	//输出 T W 
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
	cout << "（" << a.getcastle() << "/" << "50" << ")      ";
	cout << setw(8) << setfill(' ');
	cout << a.getwall() << setw(59) << setfill(' ');
	cout << b.getwall() <<setw(8) << setfill(' ');
	cout<< "(" << b.getcastle() << "/" << "50" << ")" << endl;
	
}
void print_All(player &a, card cardnum[]) {
	cout << endl;
	cout << a.name << "的手牌" << endl;
	for (int i = 0; i <= 5; i++) {			//手牌
		cout << i + 1 << ' ';
		cardnum[a.handcard[i]].show();
		cout << endl;
	}

	cout << a.name << "出牌（可出";
	
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
	cout << "; 可放弃";
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
void AllCard(player &a, player &b, int n,card cardnum[87]) {			// n为卡牌在手牌中的序号
	int x = a.handcard[n-1];
	switch (x) {
		case 0: {						// 卡牌 0 
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
			//再出一次牌 		
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
		
			//再次出牌 
			break;
		}
		case 13: {
				cardnum[13].Dealbrick(a, -8);
				cardnum[13].Producejewel(a, 1);
				Isagain = true;
			//再次出牌

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
			//至此 砖块类卡牌完成 
		}

		case 29: {
				cardnum[29].Dealjewel(a, -cardnum[29].getprice());
				cardnum[29].Dealcastle(a, 1);
				Isagain = true;
			//再次出牌

			break;
		}
		case 30: {
				cardnum[30].Dealjewel(a, -cardnum[30].getprice());
				cardnum[30].Dealwall(b, -1);
				Isagain = true;
			//再次出牌
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
			//再次 出牌
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
				 //至此 宝石类结束
		case 58: {
				cardnum[58].Dealmonster(a, -cardnum[58].getprice());
				cardnum[58].Bothmonster(a, b, -6, -6);
		
			break;
		}
		case 59: {
				cardnum[59].Dealmonster(a, -cardnum[59].getprice());
				cardnum[59].Dealwall(b, 2); 
				Isagain = true;
			//再次出牌
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
				cout << "请输入你想换的牌：(" << n << "除外)";
				int change;
				cin >> change;
				if (!cardnum[a.handcard[change - 1]].getchange()) {
					cout << "此牌不可换，只可打出！" << endl;
					goto once;
				}
				else {
					changeCard(a, cardnum, change);
					Isagain = true;
				}
				//换牌后出牌
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
				//再次出牌
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
				 //至此怪物类卡牌全部结束
	}
	checkAll(a, b);
}
/*------------------------------初始化-------------------------------*/
int Rand() {
	srand((unsigned)time(0));
	return rand() % 87;
}
void initialization(player &a, player &b) {
	srand((unsigned)time(0));
	cout << "请输入玩家一的姓名：";
	char _name[10];
	cin.getline(_name, 10);
	a.setname(_name);
	cout << "请输入玩家二的姓名：";
	cin.getline(_name, 10);
	b.setname(_name);
	for (int i = 0; i <= 5; i++) {		//p1初始化手牌 
		a.handcard[i] = rand() % 87;
	}
	for (int i = 0; i <= 5; i++) {		//p2初始化手牌 
		b.handcard[i] = rand() % 87;
	}

	//导入初始化配置文件
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
/*-----------------------------获胜条件-------------------------------*/
bool winner_resources(player &a, player &b) {		//资源获胜 放在回合开始后 
	if ((a.getbrick() >= winner_resource) && (a.getjewel() >= winner_resource) &&( a.getmonster() >= winner_resource) && (a.getbrick() >= winner_resource )&& (a.getjewel() >= winner_resource )&& (a.getmonster() >= winner_resource))
	{
		cout << "平局" << endl;
		return true;
	}
	if (a.getbrick() >= winner_resource && a.getjewel() >= winner_resource && a.getmonster() >= winner_resource)
	{
		cout << a.name << "胜利" << endl;
		return true;
	}
	if (b.getbrick() >= winner_resource && b.getjewel() >= winner_resource && b.getmonster() >= winner_resource)
	{
		cout << b.name << "胜利" << endl;
		return true;
	}
	return false;
}
bool winner_castle(player &a, player &b) {		//城堡条件 放在回合结束前 
	if ((!a.getcastle() && !b.getcastle()) || (a.getcastle() >= 50 && b.getcastle() >= 50))
	{
		cout << "平局" << endl;
		return true;
	}
	if (!a.getcastle() || b.getcastle() >= 50)
	{
		cout << b.name << "胜利" << endl;
		return true;
	}
	if (!b.getcastle() || a.getcastle() >= 50)
	{
		cout << a.name << "胜利" << endl;
		return true;
	}
	return false;
}
void changeCard(player &a,card cardnum[],int n) {
	a.handcard[n - 1] = Rand();
}
/*-----------------------------开始界面-----------------------------------*/
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
			cout << "平局" << endl;
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
					AllCard(a, b, num, cardnum);//正常调用函数
					changeCard(a, cardnum, num);//调用成功后 此牌换牌
					useorgive = 1;
				} 
				else{
					changeCard(a, cardnum, num);	//完成弃牌（换牌）
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
				AllCard(b, a, num, cardnum);//正常调用函数
				changeCard(b, cardnum, num);//调用成功后 此牌换牌
				useorgive = 1;
			}
			else {
				changeCard(b, cardnum, num);	//完成弃牌（换牌）
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
