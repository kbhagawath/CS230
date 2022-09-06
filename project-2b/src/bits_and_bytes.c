#include <stdio.h>

void print_it() {
  printf("Bit operations are fun!\n");
}

void print_int() {
  int x = 10, y = 13;
  printf("x = %d\n", x);
  printf("y = %d\n", y);
  printf("size of signed int in bytes is %zu.\n", sizeof(x));
  printf("size of signed int in bits is %zu.\n", sizeof(x) * 8);
  printf("%d + %d = %d.\n", x, y, x+y);
}

void print_float() {
  float x = 10, y = 13;
  printf("x = %f\n", x);
  printf("y = %f\n", y);
  printf("size of single float in bytes is %zu.\n", sizeof(x));
  printf("size of single float in bits is %zu.\n", sizeof(x) * 8);
  printf("%f + %f = %f.\n", x, y, x+y);
  printf("%f + %f = %.f.\n", x, y, x+y);
}

void print_char() {
  char c = 'C';
  char a = 65;

  printf("c = %c\n", c);
  printf("a = %c\n", a);
  printf("CAFEBABE\n");
  printf("number of bytes: %zu.\n", ( sizeof("CAFEBABE") ) );
}

void packing_bytes() {
  unsigned char b3 = 202;
  unsigned char b2 = 254;
  unsigned char b1 = 186;
  unsigned char b0 = 190;
  unsigned int u = 0, temp = 0;

  temp = (b3 & 255)<< 24;
  u = u | temp;
  temp = 0;

  temp = (b2 & 255)<< 16;
  u = u | temp;
  temp = 0;

  temp = (b1 & 255)<< 8;
  u = u | temp;
  temp = 0;

  temp = (b0 & 255);
  u = u | temp;
  temp = 0;

  printf("%X\n", u);
}

void unpacking_bytes() {
  unsigned int i1 = 1835098984u;
  unsigned int i2 = 1768842611u;

  printf("%c", i1>>24);
  printf("%c", i1>>16);
  printf("%c", i1>>8);
  printf("%c", i1);
  printf("%c", i2>>24);
  printf("%c", i2>>16);
  printf("%c", i2>>8);
  printf("%c\n", i2);
  
}

void print_bits() {
  unsigned char a = 181;
  signed char b = -75;
  for ( int i = 7; i >= 0; i-- ){
    printf("%x",(a>>i)&1);
  }
  printf("\n");
  for ( int i = 7; i >= 0; i-- ){
    printf("%x",(b>>i)&1);
  }
  printf("\n");
}

void extracting_fields() {
  unsigned int var = 0xCAFEBABE;
  unsigned int x0,x1,x2,x3,x4,x5,x6,x7,x8,x9;

  x0 = var >> 29;
  x1 = (var << 3) >> 28;
  x2 = (var << 7) >> 28;
  x3 = (var << 11) >> 29;
  x4 = (var << 14) >> 29;
  x5 = (var << 17) >> 28;
  x6 = (var << 21) >> 28;
  x7 = (var << 25) >> 29;
  x8 = (var << 28) >> 30;
  x9 = (var << 30) >> 30;

  printf("%d %d %d %d %d %d %d %d %d %d\n", x0, x1, x2, x3, x4, x5, x6, x7, x8, x9);
}

void updating_fields() {
  unsigned int var = 17512807u;
  var = var & 0xFFC3FFFF;
  var = var | (8 << 18);

  var = var & 0xFFFF83FF;
  var = var | (17 << 10);

  printf("%08x\n", var);
}
