#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "sais.h"


int main(int argc, char* argv[]) {
  std::string ifile = argv[1];
  std::string ofile = argv[2];

  std::ifstream ip(ifile);
  std::string genome;
  std::string line;
  for (std::string line; std::getline(ip, line); ) {
	  if (line.length() > 0 and line[0] != '>') {
		  std::transform(line.begin(), line.end(), line.begin(), ::toupper);
		  genome.append(line);
	  }
  }
  ip.close();

  genome.push_back('$');
  int* sa = new int[genome.length()];
  auto r = sais(reinterpret_cast<const unsigned char*>(genome.data()), sa, static_cast<int>(genome.length()));

  std::ofstream of(ofile, std::ios::out | std::ios::binary);
  uint32_t length = static_cast<uint32_t>(genome.length());
  of.write(reinterpret_cast<char*>(&length), sizeof(length));
  of.write(const_cast<char*>(genome.data()), genome.length());
  of.write(reinterpret_cast<char*>(sa), sizeof(int)*genome.length());
  of.close();

  delete [] sa;
  return 0;
}