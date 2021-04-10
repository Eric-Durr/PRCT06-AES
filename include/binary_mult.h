
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdint.h>

#pragma once

const uint8_t s3g_poly = 0xA9;
const uint8_t aes_poly = 0x1B;

enum algortihm
{
  AES,
  S3G
};

/**
 * @brief Adds two uint8_t values which expresses a byte from the LFSR, the result is returned
 * 
 * @param a 
 * @param b 
 * @return uint8_t 
 */

uint8_t byte_add(const uint8_t &a, const uint8_t &b)
{
  return a ^ b;
}

/**
 * @brief Prints the bits in the command line from the uint8_t byte value.
 * The number to print is given as argument.
 * 
 * @param a 
 */

void byte_print(uint8_t a)
{
  int i = 8;
  while (i--)
    putchar((a >> i & 1) + '0');
}

/**
 * @brief byte multiplication function. Two bytes and the algorithm must be provided as arguments.
 * If desired the trace can be shown by giving true as last argument
 * 
 * @param a 
 * @param b 
 * @param option 
 * @param snitch 
 * @return uint8_t 
 * 
 * **usage**
 * ```cpp
 * uint8_t my_aes_result byte_mul(0x57, 0x83, aes) //0b11000001
 * uint8_t my_s3g_result byte_mul(0x57, 0x83, s3g) //0b10010110
 * ```
 * 
 * **Algorithm explained:**
 *  mult of A and B
 * 
 *  1. product result byte initialisation
 * 
 *   is the least significant bit of B equal to 1 ?
 * 
 *     yes -> product byte = A
 *     no  -> product byte = 0
 * 
 *  for 7 times
 *   
 *  2. is the most significant bit of A equal to 1 ?
 * 
 *      yes -> A left shift 1 time and bitwise XOR with algorithm byte
 *      (algorithm byte is chosen previously)
 * 
 *      no -> A left shift 1 time
 * 
 *  3. is the nth bit of B a 1 (distributive)
 *
 *      yes -> bitwise XOR between the product result and A
 */

uint8_t byte_mul(uint8_t &a, uint8_t &b, algortihm option, bool snitch = false)
{

  uint8_t prod;

  (b & (1 << 0)) == 1 ? prod = a : prod = 0x00;

  int k = 0;
  if (snitch)
  {
    std::cout << "STEP " << k << ": \n";
    byte_print(a);
    std::cout << "\n";
  }
  for (int i = 1; i < 8; i++)
  {
    if (((a & (1 << 7)) >> 7) == 0x01)
    {
      a <<= 1;
      if (snitch)
      {
        std::cout << "STEP " << ++k << ": \n";
        byte_print(a);
        std::cout << " + ";
      }
      switch (option)
      {
      case AES:
        a = byte_add(a, aes_poly);
        if (snitch)
        {
          byte_print(aes_poly);
          std::cout << " = ";
          byte_print(a);
          std::cout << "\n";
        }
        break;
      case S3G:
        a = byte_add(a, s3g_poly);
        if (snitch)
        {
          byte_print(s3g_poly);
          std::cout << " = ";
          byte_print(a);
          std::cout << "\n";
        }
        break;
      default:
        break;
      }
    }
    else
    {
      a <<= 1;
      if (snitch)
      {
        std::cout << "STEP " << ++k << ": \n";
        byte_print(a);
        std::cout << "\n";
      }
    }
    if (((b & (1 << i)) >> i) == 0x01)
    {
      prod = byte_add(prod, a);
    }
  }
  return prod;
}
