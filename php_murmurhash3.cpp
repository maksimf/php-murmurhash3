extern "C" {
  #ifdef HAVE_CONFIG_H
    #include "config.h"
  #endif

  #include "php.h"
  #include "php_murmurhash3.h"
}

#include "MurmurHash3.h"

#define MURMURHASH3_OUTPUT_LENGTH	16


static zend_function_entry murmurhash3_functions[] = {
    PHP_FE(murmurhash3, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry murmurhash3_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_MURMURHASH3_EXTNAME,
    murmurhash3_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_MURMURHASH3_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

extern "C" {
  #ifdef COMPILE_DL_MURMURHASH3
    ZEND_GET_MODULE(murmurhash3)
  #endif
}


// Convert uint8 to hex representation (2 characters)
void c2h(uint8_t c, char *r)
{
  const char *hex = "0123456789abcdef";
  r[0] = hex[c / 16];
  r[1] = hex[c % 16];
}

uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed) {
  uint32_t h = seed;
  if (len > 3) {
    const uint32_t* key_x4 = (const uint32_t*) key;
    size_t i = len >> 2;
    do {
      uint32_t k = *key_x4++;
      k *= 0xcc9e2d51;
      k = (k << 15) | (k >> 17);
      k *= 0x1b873593;
      h ^= k;
      h = (h << 13) | (h >> 19);
      h += (h << 2) + 0xe6546b64;
    } while (--i);
    key = (const uint8_t*) key_x4;
  }
  if (len & 3) {
    size_t i = len & 3;
    uint32_t k = 0;
    key = &key[i - 1];
    do {
      k <<= 8;
      k |= *key--;
    } while (--i);
    k *= 0xcc9e2d51;
    k = (k << 15) | (k >> 17);
    k *= 0x1b873593;
    h ^= k;
  }
  h ^= len;
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;
  return h;
}

PHP_FUNCTION(murmurhash3)
{
    char *key;
    int key_len;
    long seed;

    // Parse the input parameters
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &key, &key_len, &seed) == FAILURE) {
        RETURN_NULL();
    }

    // Calculate the hash
    long result = long(murmur3_32((uint8_t*)key, (size_t)key_len, (uint32_t)seed));

    // Return the result
    RETURN_LONG(result);
}
