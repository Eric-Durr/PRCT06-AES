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
    void generate(void);
    byte_grid_t round(const byte_grid_t &grid, const byte_grid_t &round_key);

    // private:
    byte_grid_t round_key(const byte_grid_t &block);
    byte_grid_t sub_bytes(const byte_grid_t &grid);
    byte_grid_t shift_row(const byte_grid_t &grid);
    byte_grid_t mix_column(const byte_grid_t &grid);
    byte_grid_t add_round_key(const byte_grid_t &grid);
};

#endif /* AES_128_H__ */
