#include <iostream>
#include "Element.h"
using namespace std;

int main()
{
	vector<Element> El(8);

	for (int i = 0; i < 6; i++)
	{
		El[i] = Element("Res" + to_string(i));
	}

	for (int i = 6; i < 8; i++)
	{
		El[i] = Element("Node" + to_string(i));
	}

	El[0] >> El[6];

	El[6] >> El[1];
	El[6] >> El[4];

	El[1] >> El[2];
	El[2] >> El[3];
	El[3] >> El[7];

	El[4] >> El[5];
	El[5] >> El[7];

	El[7] >> El[0];


	getAllPath(El[0], El[5]);

	system("pause");
}