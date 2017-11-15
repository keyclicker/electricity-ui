#ifndef DEBUG_HPP_INCLUDED
#define DEBUG_HPP_INCLUDED

#include <string>
#include <fstream>

extern const std::string FILENAME;
extern const std::ios_base::openmode OPENMODE;

std::ofstream& Debug();


#endif
