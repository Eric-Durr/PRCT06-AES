
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdint.h>
#include "s_box.h"

/**
 * @brief Checks the program command line input. If the input is the desired returns 0
 * and the main program can proceed.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int filter(int argc, char *argv[])
{

  if (argc < 3)
  {
    std::cout << "ERROR: missing input arguments\n";
    std::cout << "USAGE: " << argv[0] << " <key_file.k> <text_file.txt> [trace]\n";
    return 1;
  }

  /* CASES */

  return 0;
}

byte_grid_t str_to_grid(const std::vector<std::string> &input);