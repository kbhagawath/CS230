#include "bits.h"
#include "cache.h"

int get_set(Cache *cache, address_type address) {
  // TODO:
  //  Extract the set bits from a 32-bit address.
  //
  int t = 32 - ( cache->block_bits + cache->set_bits);
  int shift = (cache->block_bits + t);
  unsigned int s = ((address << t) >> shift);
  return s;
}

int get_line(Cache *cache, address_type address) {
  // TODO:
  // Extract the tag bits from a 32-bit address.
  //
  int shift = (cache->block_bits + cache->set_bits);
  unsigned int l = (address >> shift);
  return l;
}

int get_byte(Cache *cache, address_type address) {
  // TODO
  // Extract the block offset (byte index) bits from a 32-bit address.
  //
  int shift = 32 - cache->block_bits;
  unsigned int b = ((address << shift) >> shift);
  return b;
}
