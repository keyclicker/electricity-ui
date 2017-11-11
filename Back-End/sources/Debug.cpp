#include <Debug.hpp>

std::ofstream& Debug()
{
	static std::ofstream output(FILENAME + ".log",
								OPENMODE);

	static std::size_t counter = 0;

	return output;
}
