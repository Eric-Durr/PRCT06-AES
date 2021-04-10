#ifndef AES_128_H__
#define AES_128_H__

#include "s_box.h"
#include "binary_mult.h"

class AES_128
{
    byte_grid_t
        inp_block_,
        input_key_,
        round_key_;
    const unsigned sz_ = 128;

public:
    AES_128(const byte_grid_t &block, const byte_grid_t &input_key);
    ~AES_128(void){};
    byte_grid_t generate(void);
    byte_grid_t round(const byte_grid_t &grid, const byte_grid_t &round_key);
    const byte_grid_t &round_key(void) const { return this->round_key_; }

    byte_grid_t sub_bytes(const byte_grid_t &grid);
    byte_grid_t shift_row(const byte_grid_t &grid);
    byte_grid_t mix_column(const byte_grid_t &grid);

private:
    byte_grid_t add_round_key(const byte_grid_t &grid, const byte_grid_t &key);
    uint8_t hig_4_bits(uint8_t byte) const { return (byte & 0xf0) >> 4; };
    uint8_t low_4_bits(uint8_t byte) const { return (byte & 0x0f); };
};

#endif /* AES_128_H__ */
