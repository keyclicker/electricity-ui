#include <Scheme.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>

int main()
{
	std::system("color 0A");

	std::ifstream cin("input.txt");
	std::ofstream cout("output.txt");

		try
		{
			Scheme s(cin);
			s.run(cout);
		}
		catch(std::logic_error& e)
		{
			std::cerr << e.what() << " => computing terminated\n";
		}

    return 0;
}
