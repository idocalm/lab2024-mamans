/*
  The motivation behind setting a fixed array with 16 elements.
    - The naive approach would be to simplify use an array with size 127,
    and assign the numbers based on their decimal values. For example,
    we would simply do values[127] = 1, if we wish to init a new number with
    value 127. or values[55] = 1 for the number 55.

    - Instead, because we need to represent 128 different numbers, understanding
    that if the architecture uses for example 8 bits per int, we ONLY need
    an array of size 16 to represent all values (16 * 8 = 128), and



*/


typedef struct set {
  int values[16];
  int size;
} set;
