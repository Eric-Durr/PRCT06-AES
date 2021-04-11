
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

void long_byte_print(uint8_t a)
{
  int i = 32;
  while (i--)
    putchar((a >> i & 1) + '0');
}

uint8_t gf2n_multiply(uint8_t a, uint8_t b)
{
  uint8_t p = 0;
  uint8_t carry;
  int i;
  for (i = 0; i < 8; i++)
  {
    if (b & 1)
      p ^= a;
    carry = a & 0x80;
    a = a << 1;
    if (carry)
      a ^= 0x1b;
    b = b >> 1;
  }
  return p;
}
