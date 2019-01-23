#include "2048.h"
#include "funcs.cpp"
c2048::c2048(){srand(time(NULL));}
c2048::c2048(const c2048 &origin)
{
	memcpy(board,origin.board,sizeof board);
}
c2048::~c2048(){}
unsigned int c2048::score()const
{
	unsigned int Score = 0;
	for(int i=0;i<Size;i++)	for(int j=0;j<Size;j++)	Score += board[i][j]*(int)(log2(board[i][j])-1);
	return Score;
}
c2048& c2048::start()
{
	memset(board,0,sizeof board);
	int x0,x1,y0,y1;
	RandPos(x0,y0,Size);
	board[x0][y0] = Rand2Or4(Prob2);
	do RandPos(x1,y1,Size);while(x1==x0 && y1==y0);
	board[x1][y1] = Rand2Or4(Prob2);
	return *this;
}
c2048&  c2048::move(char act)
{
	after(act);
	if(canAddNum())addNum();
	return *this;
}
c2048&  c2048::after(char act)
{
	if(act < 'a')act +='a'-'A';
	unsigned int rawTemp[Size];
	int k;
	switch(act)
	{
		case 'w':
			for(int j=0;j<Size;j++)
				for(int i=1;i<Size;i++)
					if(board[i][j])
						for(k=0;k<i;k++)
							if(!board[k][j])
							{
								if(k!=0 && board[k-1][j] == board[i][j]) board[k-1][j] <<= 1;
								else board[k][j] = board[i][j];
								board[i][j] = 0;
								break;
							}
							else if(board[i-1][j] == board[i][j])
							{
								board[i-1][j] <<= 1;
								board[i][j] = 0;
								break;
							}
			break;
		case 'a':
			for(int i=0;i<Size;i++)
				for(int j=1;j<Size;j++)
					if(board[i][j])
						for(k=0;k<j;k++)
							if(!board[i][k])
							{
								if(k!=0 && board[i][k-1] == board[i][j])board[i][k-1] <<= 1;
								else board[i][k] = board[i][j];
								board[i][j] = 0;
								break;
							}
							else if(board[i][j-1] == board[i][j])
							{
								board[i][j-1] <<= 1;
								board[i][j] = 0;
								break;
							}
			break;
		case 's':
			for(int j=0;j<Size;j++)
				for(int i=Size-2;i>=0;i--)
					if(board[i][j])
						for(k=Size-1;k>i;k--)
							if(!board[k][j])
							{
								if(Size-1!=k && board[k+1][j] == board[i][j]) board[k+1][j] <<= 1;
								else board[k][j] = board[i][j] ;
								board[i][j] = 0;
								break;
							}
							else if(board[i][j] == board[i+1][j])
							{
								board[i+1][j] <<= 1;
								board[i][j] = 0;
								break;
							}
			break;
		case 'd':
			for(int i=0;i<Size;i++)
				for(int j=Size-2;j>=0;j--)
					if(board[i][j])
						for(k=Size-1;k>j;k--)
							if(!board[i][k])
							{
								if(Size-1!=k && board[i][k+1] == board[i][j])board[i][k+1] <<= 1;
								else board[i][k] = board[i][j];
								board[i][j] = 0;
								break;
							}
							else if(board[i][j] == board[i][j+1])
							{
								board[i][j+1] <<= 1;
								board[i][j] = 0;
								break;
							}
			break;
	}
	return *this;
}
bool c2048::isLegal(char act)
{
	if(act == 'w' || act == 'a' || act == 's' || act == 'd' || act == 'W' || act == 'A' || act == 'S' || act == 'D')return true;
	return false;
}
bool c2048::end()
{
	if(canAddNum())return false;
	for(int i=0;i<Size-1;i++)
		for(int j=0;j<Size-1;j++)
			if(board[i][j] == board[i+1][j] || board[i][j] == board[i][j+1])return false;
	for(int i=0;i<Size-1;i++)if(board[i][Size-1] == board[i+1][Size-1] || board[Size-1][i] == board[Size-1][i+1] )return false;
	return true;
}
c2048&  c2048::addNum()
{
	int x,y;
	do RandPos(x,y,Size);while(board[x][y]);
	board[x][y] = Rand2Or4(Prob2);
	return *this;
}
bool c2048::canAddNum()
{
	for(int i=0;i<Size;i++)for(int j=0;j<Size;j++)if(!board[i][j])return true;
	return false;
}

vector<char> c2048::action()const
{
	vector<char>tmp;
	for(int i=0;i<Size;i++)for(int j=0;j<Size;j++)
		if(!board[i][j])
		{
			tmp.push_back('w');
			tmp.push_back('s');
			tmp.push_back('a');
			tmp.push_back('d');
			return tmp;
		}
	for(int i=0;i<Size-1;i++)
		for(int j=0;j<Size-1;j++)
		{
			if(board[i][j] == board[i+1][j] && (find(tmp.begin(),tmp.end(),'w') == tmp.end()) )
			{
				tmp.push_back('w');
				tmp.push_back('s');
			}
			if(board[i][j] == board[i][j+1] && (find(tmp.begin(),tmp.end(),'a') == tmp.end()) )
			{
				tmp.push_back('a');
				tmp.push_back('d');
			}
			if(tmp.size() == 4)return tmp;
		}
	for(int i=0;i<Size-1;i++)
	{
		if(board[i][Size-1] == board[i+1][Size-1] && (find(tmp.begin(),tmp.end(),'w') == tmp.end()))
		{
			tmp.push_back('w');
			tmp.push_back('s');
		}
		if(board[Size-1][i] == board[Size-1][i+1] && (find(tmp.begin(),tmp.end(),'a') == tmp.end()))
		{
			tmp.push_back('a');
			tmp.push_back('d');
		}
		if(tmp.size() == 4)return tmp;
	}
	return tmp;
}
ostream &operator<<(ostream &out,const c2048 &game)
{
	//system ("cls"); 
	out<<setw(22)<<"score: "<<game.score()<<endl<<endl;
	for(int i=0;i<Size;i++)
	{
		for(int j=0;j<Size;j++)out<<setw(8)<<game.board[i][j];
		out<<endl;
	}
	return out;
}
unsigned int c2048::reward(char action)const
{
	c2048 state(*this);
	return state.after(action).score() - this->score();
}
