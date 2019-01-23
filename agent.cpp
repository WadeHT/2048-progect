#include "2048.h"
#include <fstream>
#include <cstring>
#include <map>
#include <algorithm> 
#include <utility>
#define bsize 4
#define nvector 8
#define alpha 0.9
#define learningRate 0.4
using namespace std;
template<int ssize>
struct Tuple
{
	unsigned int arr[ssize],size;
	Tuple():size(ssize)
	{
		memset(arr,0,sizeof arr);
	}
	bool operator!=(const Tuple& right)
	{
		for(int i=0;i<size;i++)if(right.arr[i] != arr[i])return true;
		return false;
	}
	bool operator==(const Tuple& right)const
	{
		for(int i=0;i<size;i++)if(right.arr[i] != arr[i])return false;
		return true;
	}
	Tuple& operator=(const Tuple& right)const
	{
		memcpy(arr,right.arr,sizeof arr);
	}
	Tuple& operator=(const unsigned int right[])
	{
		memcpy(arr,right,sizeof arr);
	}
	bool operator<(const Tuple& right)const
	{
		for(int i=0;i<ssize;i++)if(arr[i]<right.arr[i])return true;
		return false;
	}
	friend ostream& operator<<(ostream &out,const Tuple<ssize>& tup)
	{
		for(int i=0;i<ssize;i++)out<<setw(4)<<tup.arr[i]<<" ";
		return out;
	}
};
template<int ssize>
void createTuple(Tuple<ssize> arr[],const unsigned int board[][ssize])
{
	for(int i=0;i<ssize;i++)arr[i] = board[i];
	for(int i=0;i<ssize;i++)for(int j=0;j<(ssize>>1);j++)arr[i+ssize].arr[j] = board[j][i];
}
class agt
{
	map<Tuple<bsize>,double> features;
	Tuple<bsize> s[nvector];
public:
	agt(){}
	
	const char bestmove(const c2048& state)
	{
		double score = 0,evalue;
		char next = 'w';
		for(char act: state.action())
		{
			if(score < (evalue = evaluate(state,act)) )
			{
				score = evalue;
				next = act;
			}
		}
		return next;
	}
	double evaluate(c2048 state,char act)
	{
		return state.reward(act) + value(state.after(act));
	}
	double value(const c2048& state)
	{
		double val = 0;
		createTuple(s,state.board);
		for(int i=0;i<nvector;i++)if(features.find(s[i]) != features.end())val += features[s[i]];//
		return val;
	}
	agt &learning(c2048 state0,char act)
	{
		c2048 state1(state0);
		state1.after(act);
		createTuple(s,state0.board);
		for(int i=0;i<nvector;i++)if(features.find(s[i]) == features.end())features[s[i]] = 0;
		double delta = state0.reward(act) - value(state0) + value(state1);
		for(auto &f: features)f.second += delta * learningRate / features.size();//
	}	
	void test()
	{
		ofstream fs;fs.open("log.txt");
		for(auto f:features)fs<<f.first<<" weight: "<<f.second<<endl;//
		fs<<endl<<endl;
	}
};

