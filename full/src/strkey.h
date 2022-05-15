#ifndef STRKEY_H
#define STRKEY_H

#include "stellarxdr.h"
#include <stdbool.h>
#include <stdint.h>

static const char *MUXED_ACCOUNT_STARTING_LETTER = "M";
static const char *ED25519_PUBLIC_KEY_ACCOUNT_STARTING_LETTER = "G";

static const uint8_t ED25519_PUBLIC_KEY_LENGTH = 56;
static const uint8_t ED25519_SECRET_SEED_LENGTH = 56;
static const uint8_t PRE_AUTH_TX_LENGTH = 56;
static const uint8_t SHA256_HASH_LENGTH = 56;
static const uint8_t MED25519_PUBLIC_KEY_LENGTH = 69;

enum CryptoKeyType {
  KEY_TYPE_ED25519 = 0,
  KEY_TYPE_PRE_AUTH_TX = 1,
  KEY_TYPE_HASH_X = 2,
  KEY_TYPE_MUXED_ED25519 = 0x100,
};

enum VersionByte {
  ED25519_PUBLIC_KEY = 6 << 3,   // Base32-encodes to 'G...'
  ED25519_SECRET_SEED = 18 << 3, // Base32-encodes to 'S...'
  MED25519_PUBLIC_KEY = 12 << 3, // Base32-encodes to 'M...'
  PRE_AUTH_TX = 19 << 3,         // Base32-encodes to 'T...'
  SHA256_HASH = 23 << 3,         // Base32-encodes to 'X...'
};

bool encode_ed25519_public_key(const uint8_t *in, char *out);

bool decode_ed25519_public_key(const char *in, uint8_t *out);

bool encode_med25519_public_key(const stellarxdr_MuxedAccountMed25519 *in,
                                char *out);

bool decode_med25519_public_key(const char *in,
                                stellarxdr_MuxedAccountMed25519 *out);

bool encode_ed25519_secret_seed(const uint8_t *in, char *out);

bool decode_ed25519_secret_seed(const char *in, uint8_t *out);

bool encode_pre_auth_tx(const uint8_t *in, char *out);

bool decode_pre_auth_tx(const char *in, uint8_t *out);

bool encode_sha256_hash(const uint8_t *in, char *out);

bool decode_sha256_hash(const char *in, uint8_t *out);

#endif
