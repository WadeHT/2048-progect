#include <cstdlib>
unsigned int Rand2Or4(double Prob)
{
	return (rand()/(RAND_MAX+1.0) <= Prob)?2:4;
}
void RandPos(int &x,int &y,int size)
{
	x = rand()%size;
	y = rand()%size;
}