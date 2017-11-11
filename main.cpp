#include <Scheme.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <Debug.hpp>

const std::string FILENAME = "main";
const std::ios_base::openmode OPENMODE =
	std::ios_base::out;

int main()
{
	std::system("color 0A");

	std::ifstream cin(FILENAME + ".in");
	std::ofstream cout(FILENAME + ".out");

		try
		{
			Scheme s(cin);
			s.run(cout);
		}
		catch(std::logic_error& e)
		{
			Debug() << e.what() << " => computing terminated\n";
		}
		catch(std::exception& e)
		{
			Debug() << e.what() << "\n";
		}

	cin.close();
	cout.close();

    return 0;
}
