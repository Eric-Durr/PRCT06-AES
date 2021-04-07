#include "../include/aes.h"

AES_128::AES_128(const byte_grid_t &block, const byte_grid_t &input_key) {}
void AES_128::generate(void) {}
byte_grid_t AES_128::round(const byte_grid_t &grid, const byte_grid_t &round_key) {}

// private:
byte_grid_t AES_128::round_key(const byte_grid_t &block) {}
byte_grid_t AES_128::sub_bytes(const byte_grid_t &grid) {}
byte_grid_t AES_128::shift_row(const byte_grid_t &grid) {}
byte_grid_t AES_128::mix_column(const byte_grid_t &grid) {}
byte_grid_t AES_128::add_round_key(const byte_grid_t &grid) {}