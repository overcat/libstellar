#include "strkey.h"

#include <stdbool.h>

#include "vendor/base32/base32.h"
#include "vendor/crc16/crc16.h"
#include "stellarxdr.h"

bool encode_key(const uint8_t *in, char *out, uint8_t version_byte) {
  uint8_t buffer[35];
  buffer[0] = version_byte;
  for (int i = 0; i < 32; i++) {
    buffer[i + 1] = in[i];
  }
  unsigned short crc = crc16((char *)buffer, 33);
  buffer[33] = crc;
  buffer[34] = crc >> 8;
  if (!base32_encode(buffer, 35, (uint8_t *)out, 56)) {
    return false;
  }
  out[56] = '\0';
  return true;
}

bool encode_ed25519_public_key(const uint8_t *in, char *out) {
  return encode_key(in, out, ED25519_PUBLIC_KEY);
}

bool encode_ed25519_secret_seed(const uint8_t *in, char *out) {
  return encode_key(in, out, ED25519_SECRET_SEED);
}

bool encode_pre_auth_tx(const uint8_t *in, char *out) {
  return encode_key(in, out, PRE_AUTH_TX);
}

bool encode_sha256_hash(const uint8_t *in, char *out) {
  return encode_key(in, out, SHA256_HASH);
}

bool encode_med25519_public_key(const stellarxdr_MuxedAccountMed25519 *in,
                                char *out) {
  uint8_t buffer[43];
  buffer[0] = MED25519_PUBLIC_KEY;
  int i;
  for (i = 0; i < 32; i++) {
    buffer[i + 1] = in->ed25519[i];
  }
  for (i = 0; i < 8; i++) {
    buffer[33 + i] = in->id >> 8 * (7 - i);
  }
  unsigned short crc = crc16((char *)buffer, 41);
  buffer[41] = crc;
  buffer[42] = crc >> 8;
  if (!base32_encode(buffer, 43, (uint8_t *)out, 69)) {
    return false;
  }
  out[69] = '\0';
  return true;
}
