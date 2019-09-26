//#include "generator.h"
#include<sstream>
#include<iostream>
#include <cstdlib>
#include <cstring>
#include<iomanip>

//namespace phz_check_hu{
	template<typename T>
	void LogSeq(std::vector<T>& cards) {
#ifndef NDEBUG
			std::ostringstream oss;
			oss <<"[";
			int index = 0;
			for (auto v : cards) {
				++index;
				oss << std::setw(2) << int(v) << "," ;
			}
			oss << "]";
			std::cout<< oss.str() << "\n";
#endif
	}
	enum{
		__Base = 0,
		__Peng = 1,
		__27A = 2,
		__Shun = 3,
		__aaA = 4,
		__AAa = 5,
		__Dui = 6,
	};
	const char * _desc[] = {
		"",
		"Peng:%d\n",
		"27A:%d\n",
		"Shun:%d\n",
		"aaA:%d\n",
		"AAa:%d\n",
		"Dui:%d\n"
	};
	char record[20][7] = {0,};
	bool Check(std::vector<char>& t, char lst, int & total) {
		for (int i=0;i<20;++i) {
			if (t[i] == 3 && record[i][0] == 0) {
				do {
					std::vector<char> tmp(t);
					tmp[i] = 0;
					total -= 3;
					record[i][0] = 1;
					if (Check(tmp, lst,total)) {
						record[i][__Peng] = 1;
						printf("Peng:Check:3:%d\n", (i+1));
						return true;
					}
					total += 3;
					tmp[i] = 3;
				} while(0);
			}
		}
		for (int i=0;i<10;++i) {
			if ( i == 1) {
				if (record[11][0] < 3) {
					if (t[11] > 0 && t[16] > 0 && t[19] > 0) {
						record[11][0] = 2;
						std::vector<char> tmp(t);
						tmp[11] -- ;
						tmp[16] --;
						tmp[19] --;
						int tnt = total -3;
						if (Check(tmp, lst, tnt)) {
							record[11][__27A] ++;
							printf("27A:Check:3:%d\n", (i+11));
							return true;
						}
					}
				}
				if ( record[1][0] < 3) {//27a
					if (t[1] > 0 && t[6] > 0 && t[9] > 0) {
						record[1][0] = 2;
						std::vector<char> tmp(t);
						tmp[1] -- ;
						tmp[6] --;
						tmp[9] --;
						int tnt = total -3;
						if (Check(tmp, lst, tnt)) {
							record[1][__27A] ++;
							printf("27A:Check:3:%d\n", (i+1));
							return true;
						}
					}
				}
			}
			if (i < 7 ) {
				if (record[i+10][0] < 4) {
					if (t[i + 10] > 0 && t[i+11] > 0 && t[i+12] > 0) {
						std::vector<char> tmp(t);
						tmp[i+ 10] -- ;
						tmp[i+ 11] --;
						tmp[i+ 12] --;
						record[i+10][0] = 3;
						int tnt = total -3;
						if (Check(tmp, lst, tnt)) {
							record[i+10][__Shun] ++;
							printf("shun:Check:3:%d\n", (i+11));
							return true;
						}
					}
				}
				if (record[i][0] < 4) {
					if (t[i] > 0 && t[i+1] > 0 && t[i+2] > 0) {
						std::vector<char> tmp(t);
						tmp[i+ 0] -- ;
						tmp[i+ 1] --;
						tmp[i+ 2] --;
						record[i][0] = 3;
						int tnt = total -3;
						if (Check(tmp, lst, tnt)) {
							record[i][__Shun] ++;
							printf("shun:Check:3:%d\n", (i+1));
							return true;
						}
					}
				}
			}
			if (t[i] + t[i+10] >= 3){
				if (t[i] >= 2 && record[i][0] < 5) {
					record[i][0] = 4;
					std::vector<char> tmp(t);
					tmp[i] -= 2;
					tmp[i+ 10] --;
					int tnt = total -3;
					if (Check(tmp, lst, tnt)) {
						record[i][__aaA] ++;
						printf("aaA:Check:3:%d\n", (i+1));
						return true;
					}
				}
				if (t[i+10] >= 2 && record[i][0] < 6) {
					record[i][0] = 4;
					std::vector<char> tmp(t);
					tmp[i] --;
					tmp[i+ 10] -= 2;
					int tnt = total -3;
					if (Check(tmp, lst, tnt)) {
						record[i][__AAa] ++;
						printf("AAa:Check:3:%d\n", (i+1));
						return true;
					}
				}
			}
			if (t[i] + t[i+10] != 0) {
				return false;
			}
		}

		if (total == 0) return true;
		return false;
	}
	int main()
	{
		//beardGenerator gen;
		//gen.Reset(0,3);
		//std::vector<char> cards;
		//gen.GetCard(cards);
		//std::vector<group> players;
		//players.resize(4);
		//for (int i=0;i<20;++i) {
		//	players[0].add(cards[3*i + 0]);
		//	players[1].add(cards[3*i + 1]);
		//	players[2].add(cards[3*i + 2]);
		//}
		//players[0].add(cards[60]);
		//players[3].data.insert(players[3].data.end(), cards.begin() + 61, cards.end());
		std::vector<char> c = { 3,2,1,0,0,0,1,0,0,1,
			2,1,1,0,0,0,0,4,0,2};
		char lst = 1;
		int total = 0;
		for (int i=0;i<20;++i) {
			if (c[i] == 4) {
				c[i] = 0;
				printf("TiPao:Check:4:%d\n", (i+1));
				continue;
			}
			if (c[i] == 3 && lst != (i+1)) {
				total -= 3;
				c[i] = 0;
				printf("Kan:Check:3:%d\n", (i+1));
				continue;
			}
			total += c[i];
		}
		int mod = total %3;
		printf("%d\n", total);
		bool bFind = false;
		switch(mod)
		{
			case 0:
				{
					std::vector<char> tmp(c);
					int ttl = total;
					if (Check(tmp, lst, ttl)) {
						bFind = true;
						printf("succ:Check\n");
						break;
					} else {
						printf("fail:\n");
					}
				}
				break;
			case 2:
				{
					for ( int i=0;i<20;++i) {
						if (c[i] == 2 || (c[i] == 3 && lst != 0 && lst == (i+1))) {
							if (i == 19) {
								printf("loop:%d\n", i);
							}
							int ttl = total - 2;
							std::vector<char> tmp(c);
							tmp[i] -= 2;
							memset(record, 0x00, sizeof(record));
							if (Check(tmp, lst, ttl)) {
								record[i][__Dui] ++;
								bFind = true;
								printf("Dui:Check:%d\n", (i+1));
								break;
							}
						}
					}
					if (!bFind ) {
						printf("fail:\n");
					}
				}
				break;
			default:
				break;
		}
		if (bFind) {
			for (int i=0;i<20;++i) {
				for (int j=1;j<7;++j) {
					for (int z=0;z<record[i][j];++z) {
						printf(_desc[j], i+1);
					}
				}
			}
			return 0;
		}
	}
//}
