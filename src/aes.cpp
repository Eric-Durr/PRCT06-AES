#include "../include/aes.h"

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

// private:
byte_grid_t AES_128::sub_bytes(const byte_grid_t &grid)
{
  byte_grid_t out = {{}, {}, {}, {}};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      out[i].push_back(S_BOX[hig_4_bits(grid[i][j])][low_4_bits(grid[i][j])]);
  return out;
}
byte_grid_t AES_128::shift_row(const byte_grid_t &grid) {}
byte_grid_t AES_128::mix_column(const byte_grid_t &grid) {}

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