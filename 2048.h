#ifndef _c2048
#define _c2048

#include <iostream>
#include <cstring>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip> 
#include <cstdio>
#include <cmath>
#include <algorithm> 


#define Size 4
#define Prob2 0.9
using namespace std;
class c2048
{
	friend ostream &operator<<(ostream&,const c2048&);
	friend class agt;
	unsigned int board[Size][Size];
public:
	vector<char>action()const;
	c2048();
	~c2048();
	c2048(const c2048&);
	unsigned int score()const;
	c2048& start();
	c2048&  move(char);
	c2048&  after(char);
	bool isLegal(char);
	bool end();
	c2048&  addNum();
	bool canAddNum();
	unsigned int reward(char action)const;
};

#endif