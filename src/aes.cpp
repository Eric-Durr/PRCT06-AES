#include "../include/aes.h"
#include "../include/binary_mult.h"

AES_128::AES_128(const byte_grid_t &block, const byte_grid_t &input_key)
{
  this->inp_block_ = block;
  this->input_key_ = input_key;
  this->round_key_ = this->add_round_key(this->inp_block_,
                                         this->input_key_);
}

/*!
 * @brief generates encripted block by aplying the AES instruction 
   round key -> +9 rounds -> out
 * */
byte_grid_t AES_128::generate(void)
{

  // // init round (add round key)
  // this->add_round_key(this->inp_block_, this->input_key_);
  // byte_grid_t cyper_output = this->round_key_;

  // // 9 rounds of byte sub -> shift row -> mix column -> add round key
  // for (int i = 0; i < 9; ++i)
}

/*!
 * @brief generates only one round of the AES sequence of instructions
 *
 * 1. sub_bytes
 * 2. shift_row
 * 3. mix_column
 * 4. add_round_key
 * 
 * @returns modified grid
 * */
byte_grid_t AES_128::round(const byte_grid_t &grid, const byte_grid_t &round_key)
{
}

/*!
 * @brief Private method that applies the substitution according to the defined S_BOX  
 * for AES 
 * 
 * It usses the private methods low_4_bits(const uint8_t& byte) and hig_4_bits(const uint8_t& byte)
 * to generate the eexpected output value.  
 * 
 * @returns substituted bytes grid
 * */
byte_grid_t AES_128::subs_bytes(const byte_grid_t &grid)
{
  byte_grid_t out = {{}, {}, {}, {}};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      out[i].push_back(S_BOX[hig_4_bits(grid[i][j])][low_4_bits(grid[i][j])]);
  return out;
}

/*!
 * @brief Private method that applies the row shifting to the given grid (which comes from sub_bytes())
 * 
 * The method shifts N times the current row elements, N refers to the actual row number
 * 
 * ```
 *  [n1 n5 n9  n13] << x0        [n1  n5  n9  n13]
 *  [n2 n6 n10 n14] << x1   -->  [n6  n10 n14 n2 ] 
 *  [n3 n7 n11 n15] << x2        [n11 n15 n3  n7 ]
 *  [n4 n8 n12 n16] << x3        [n16  n4 n8  n12] 
 * ```
 * 
 * @returns shifted bytes grid
 * */
byte_grid_t AES_128::shift_rows(const byte_grid_t &grid)
{

  return byte_grid_t{{grid[0][0], grid[0][1], grid[0][2], grid[0][3]},
                     {grid[1][1], grid[1][2], grid[1][3], grid[1][0]},
                     {grid[2][2], grid[2][3], grid[2][0], grid[2][1]},
                     {grid[3][3], grid[3][0], grid[3][1], grid[3][2]}};
}

/*!
 * @brief Private method that the second part of the permutation to the current block
 * 
 * The method multiplies each column with a base column to create the output block
 * 
 * ```
 *  [02 03 01 01] [c1]   [c'1]
 *  [01 02 03 01] [c2] = [c'2] 
 *  [01 01 02 03] [c3]   [c'3]
 *  [03 01 01 02] [c4]   [c'4] 
 * ```
 * 
 * @returns mixed column bytes grid
 * */
byte_grid_t AES_128::mix_column(const byte_grid_t &grid) {}

/*!
 * @brief Private method that adds the key to the given grid 
 *
 * It usses byte_add(uint8_t A, uint8_t B) function of bitwise XOR to each byte 
 * of both elements
 * 
 * @returns add round key grid
 * */
byte_grid_t AES_128::add_round_key(const byte_grid_t &grid, const byte_grid_t &key)
{
  byte_grid_t aux_grid;
  for (int i = 0; i < 4; ++i)
  {
    std::vector<uint8_t> aux_line;
    for (int j = 0; j < 4; ++j)
      aux_line.push_back(byte_add(grid[i][j], key[i][j]));
    aux_grid.push_back(aux_line);
  }
  return aux_grid;
}