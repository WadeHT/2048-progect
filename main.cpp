#include <iostream>
#include <fstream>
#include "agent.cpp"
#include "2048.h"
#include <vector>
#define useagent 1
#define enlearn 1
using namespace std;
int main()
{
	c2048 game;
	agt agent;
	char move;
	int eva = 0,eeva=0;
	for(int i=1;i;i++)
	{
		/*cout<<*/game.start();
		while(!game.end())
		{	
			if(!useagent)while(cin>>move && !game.isLegal(move));
			if(useagent)move = agent.bestmove(game);
			if(useagent && enlearn)agent.learning(game,move);
			//cout<<setw(24)<<move<<endl<<endl;
			/*cout<<*/game.move(move);
			//agent.test();
		}
		//cout<<game<<endl<<setw(24)<<"game over"<<endl;
		eva += game.score();
		
		if(i%100 == 0)
		{
			cout<<eva/100<<endl;
			eeva += eva;
			eva = 0;
		}
		if(i%1000 == 0)
		{
			agent.test();
			cout<<"***"<<eeva/1000<<endl<<endl;
			eeva = 0;
		}
	}
	return 0;
}
