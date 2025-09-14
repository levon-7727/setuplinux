#include <iostream>
#include <stdlib.h>

int main(int argc, char* argv[])
{

	if (argc != 4)
	{
		return 0;
	}
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int c = atoi(argv[3]);

	int min, max;
	if (a > b)
	{
		min = b;
		max = a;
	}
	else
	{
		max = b;
		min = a;
	}
	if (c > max)
	{
		max = c;
	}
	else if (c < min) 
	{
		min = c;
	}
	std::cout<<"min-"<<min<<" max-"<<max;
	return 0;
}
