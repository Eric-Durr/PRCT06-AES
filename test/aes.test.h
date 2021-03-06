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
      THEN("Key is expanded in constructor")
      {
        REQUIRE(testing_private.round_key(0) == key);
        REQUIRE(testing_private.round_key(1) == byte_grid_t{
                                                    {0xd6, 0xd2, 0xda, 0xd6},
                                                    {0xaa, 0xaf, 0xa6, 0xab},
                                                    {0x74, 0x72, 0x78, 0x76},
                                                    {0xfd, 0xfa, 0xf1, 0xfe},
                                                });
        REQUIRE(testing_private.round_key(10) == byte_grid_t{
                                                     {0x13, 0xe3, 0xf3, 0x4d},
                                                     {0x11, 0x94, 0x07, 0x2b},
                                                     {0x1d, 0x4a, 0xa7, 0x30},
                                                     {0x7f, 0x17, 0x8b, 0xc5},
                                                 });
      }
      AND_THEN("The first round key is the original key")
      {
        CHECK(testing_private.round_key(0) == byte_grid_t{
                                                  {0x00, 0x04, 0x08, 0x0c},
                                                  {0x01, 0x05, 0x09, 0x0d},
                                                  {0x02, 0x06, 0x0a, 0x0e},
                                                  {0x03, 0x07, 0x0b, 0x0f},
                                              });
      }
      AND_THEN("Sub_bytes generates the expected matrix")
      {
        byte_grid_t sub = testing_private
                              .subs_bytes(testing_private
                                              .add_round_key(input, testing_private
                                                                        .round_key(0)));
        CHECK(sub == byte_grid_t{{0x63, 0x09, 0xcd, 0xba},
                                 {0xca, 0x53, 0x60, 0x70},
                                 {0xb7, 0xd0, 0xe0, 0xe1},
                                 {0x04, 0x51, 0xe7, 0x8c}});
      }
      AND_THEN("shift_rows generates the expected matrix")
      {
        byte_grid_t shi = testing_private
                              .shift_rows(testing_private
                                              .subs_bytes(testing_private
                                                              .add_round_key(input, testing_private
                                                                                        .round_key(0))));

        CHECK(shi == byte_grid_t{{0x63, 0x09, 0xcd, 0xba},
                                 {0x53, 0x60, 0x70, 0xca},
                                 {0xe0, 0xe1, 0xb7, 0xd0},
                                 {0x8c, 0x04, 0x51, 0xe7}});
      }
      AND_THEN("mix_column generates the expected matrix")
      {
        byte_grid_t col_test = {
            {0x00, 0x44, 0x88, 0xcc},
            {0x11, 0x55, 0x99, 0xdd},
            {0x22, 0x66, 0xaa, 0xee},
            {0x33, 0x77, 0xbb, 0xff},
        };
        byte_grid_t mix = testing_private.mix_column(col_test);
        // byte_grid_t mix = testing_private
        //                       .mix_column(testing_private
        //                                       .shift_rows(testing_private
        //                                                       .subs_bytes(testing_private
        //                                                                       .add_round_key(input, testing_private
        //                                                                                                 .round_key(0)))));
        // print_byte_grid(mix);
        // CHECK(mix == byte_grid_t{{0x63, 0x09, 0xcd, 0xba},
        //                          {0x53, 0x60, 0x70, 0xca},
        //                          {0xe0, 0xe1, 0xb7, 0xd0},
        //                          {0x8c, 0x04, 0x51, 0xe7}});
      }
    }
  }
}

SCENARIO("testing AES generator")
{
  GIVEN("Key and input matrix")
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

    WHEN("Created AES_128 object")
    {
      AES_128 testing_generator(input, key);
      THEN("AES can be applied")
      {
        byte_grid_t result = testing_generator.generate(true);
        CHECK(result == byte_grid_t{
                            {0x69, 0x6a, 0xd8, 0x70},
                            {0xc4, 0x7b, 0xcd, 0xb4},
                            {0xe0, 0x04, 0xb7, 0xc5},
                            {0xd8, 0x30, 0x80, 0x5a}});
      }
    }
  }
}
