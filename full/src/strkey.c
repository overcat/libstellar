#include "strkey.h"

#include <stdbool.h>

#include "stellarxdr.h"
#include "vendor/base32/base32.h"
#include "vendor/crc16/crc16.h"

bool encode_check(const uint8_t *in, char *out, uint8_t version_byte) {
  uint8_t buffer[35];
  buffer[0] = version_byte;
  for (int i = 0; i < 32; i++) {
    buffer[i + 1] = in[i];
  }
  unsigned short crc = crc16((char *)buffer, 33);
  buffer[33] = crc;
  buffer[34] = crc >> 8;
  if (base32_encode(buffer, 35, (uint8_t *)out, 56) == -1) {
    return false;
  }
  out[56] = '\0';
  return true;
}

bool decode_check(const char *in, uint8_t *out, uint8_t expected_version_byte) {
  uint8_t decode_raw_data[35];
  uint8_t decode_version_byte;
  uint8_t decode_payload[33];
  if (base32_decode((unsigned char *)in, decode_raw_data, 56) == -1) {
    return false;
  }
  decode_version_byte = decode_raw_data[0];
  for (int i = 0; i < 33; i++) {
    decode_payload[i] = decode_raw_data[i];
  }
  for (int i = 0; i < 32; i++) {
    out[i] = decode_raw_data[i + 1];
  }
  if (decode_version_byte != expected_version_byte) {
    return false;
  }
  unsigned short expected_checksum =
      ((unsigned short)decode_raw_data[34] << 8) | decode_raw_data[33];
  unsigned short checksum = crc16((char *)decode_payload, 33);
  if (expected_checksum != checksum) {
    return false;
  }
  return true;
}

bool encode_ed25519_public_key(const uint8_t *in, char *out) {
  return encode_check(in, out, ED25519_PUBLIC_KEY);
}

bool decode_ed25519_public_key(const char *in, uint8_t *out) {
  return decode_check(in, out, ED25519_PUBLIC_KEY);
}

bool encode_ed25519_secret_seed(const uint8_t *in, char *out) {
  return encode_check(in, out, ED25519_SECRET_SEED);
}

bool decode_ed25519_secret_seed(const char *in, uint8_t *out) {
  return decode_check(in, out, ED25519_SECRET_SEED);
}

bool encode_pre_auth_tx(const uint8_t *in, char *out) {
  return encode_check(in, out, PRE_AUTH_TX);
}

bool decode_pre_auth_tx(const char *in, uint8_t *out) {
  return decode_check(in, out, PRE_AUTH_TX);
}

bool encode_sha256_hash(const uint8_t *in, char *out) {
  return encode_check(in, out, SHA256_HASH);
}

bool decode_sha256_hash(const char *in, uint8_t *out) {
  return decode_check(in, out, SHA256_HASH);
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

bool decode_med25519_public_key(const char *in,
                                stellarxdr_MuxedAccountMed25519 *out) {
  uint8_t decode_raw_data[43];
  uint8_t decode_version_byte;
  uint8_t decode_payload[41];
  uint8_t decode_ed25519_data[32];
  u_int64_t decode_id = 0;
  if (base32_decode((unsigned char *)in, decode_raw_data, 69) == -1) {
    return false;
  }
  decode_version_byte = decode_raw_data[0];
  for (int i = 0; i < 41; i++) {
    decode_payload[i] = decode_raw_data[i];
  }
  for (int i = 0; i < 32; i++) {
    decode_ed25519_data[i] = decode_raw_data[i + 1];
  }
  for (int i = 0; i < 8; i++) {
    decode_id += decode_raw_data[33 + i] << 8 * (7 - i);
  }
  out->id = decode_id;
  memcpy(out->ed25519, decode_ed25519_data, 32);
  if (decode_version_byte != MED25519_PUBLIC_KEY) {
    return false;
  }
  unsigned short expected_checksum =
      ((unsigned short)decode_raw_data[42] << 8) | decode_raw_data[41];
  unsigned short checksum = crc16((char *)decode_payload, 41);
  if (expected_checksum != checksum) {
    return false;
  }
  return true;
}