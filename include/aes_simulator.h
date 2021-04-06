
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdint.h>

const uint8_t s3g_poly = 0xA9;
const uint8_t aes_poly = 0x1B;

enum algortihm
{
  AES,
  S3G
};

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

  if (/* argc < 4  */ 0)
  {
    std::cout << "ERROR: wrong execution input\n";
    std::cout << "USAGE: " << argv[0] << " <aes/s3g> <num1> <num2> [trace]\n";
    return 1;
  }

  /* CASES */

  return 0;
}