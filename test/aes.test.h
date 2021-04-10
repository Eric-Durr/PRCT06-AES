#include "../include/Catch2/catch.h"
#include "../include/aes.h"

SCENARIO("Testing AES private methods")
{
  GIVEN("a key bytes matrix and an input bytes matrix")
  {
    byte_grid_t key = {
        {0x00, 0x04, 0x08, 0x0c},
        {0x01, 0x05, 0x09, 0x0d},
        {0x02, 0x06, 0x0a, 0x0e},
        {0x03, 0x07, 0x0b, 0x0f},
    };
    byte_grid_t input = {
        {0x00, 0x44, 0x88, 0xcc},
        {0x11, 0x55, 0x99, 0xdd},
        {0x22, 0x66, 0xaa, 0xee},
        {0x33, 0x77, 0xbb, 0xff},
    };
    WHEN("Creating an 128 bit AES object")
    {
      AES_128 testing_private(input, key);
      THEN("The round key attribute is the first round key")
      {
        CHECK(testing_private.round_key() == byte_grid_t{
                                                 {0x00, 0x40, 0x80, 0xc0},
                                                 {0x10, 0x50, 0x90, 0xd0},
                                                 {0x20, 0x60, 0xa0, 0xe0},
                                                 {0x30, 0x70, 0xb0, 0xf0},
                                             });
      }
      AND_THEN("Sub_bytes generates the expected matrix")
      {
        byte_grid_t sub = testing_private.subs_bytes(testing_private.round_key());
        CHECK(sub == byte_grid_t{{0x63, 0x09, 0xcd, 0xba},
                                 {0xca, 0x53, 0x60, 0x70},
                                 {0xb7, 0xd0, 0xe0, 0xe1},
                                 {0x04, 0x51, 0xe7, 0x8c}});
      }
      AND_THEN("shift_rows generates the expected matrix")
      {
        byte_grid_t shi = testing_private
                              .shift_rows(testing_private
                                              .subs_bytes(testing_private.round_key()));

        CHECK(shi == byte_grid_t{{0x63, 0x09, 0xcd, 0xba},
                                 {0x53, 0x60, 0x70, 0xca},
                                 {0xe0, 0xe1, 0xb7, 0xd0},
                                 {0x8c, 0x04, 0x51, 0xe7}});
      }
    }
  }
}
