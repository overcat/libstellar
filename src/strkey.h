#ifndef STRKEY_H
#define STRKEY_H

#include "stellarxdr.h"
#include <stdbool.h>
#include <stdint.h>

static const uint8_t ED25519_PUBLIC_KEY_LENGTH = 56;
static const uint8_t ED25519_SECRET_SEED_LENGTH = 56;
static const uint8_t PRE_AUTH_TX_LENGTH = 56;
static const uint8_t SHA256_HASH_LENGTH = 56;
static const uint8_t MED25519_PUBLIC_KEY_LENGTH = 69;

enum VersionByte {
  ED25519_PUBLIC_KEY = 6 << 3,   // Base32-encodes to 'G...'
  ED25519_SECRET_SEED = 18 << 3, // Base32-encodes to 'S...'
  MED25519_PUBLIC_KEY = 12 << 3, // Base32-encodes to 'M...'
  PRE_AUTH_TX = 19 << 3,         // Base32-encodes to 'T...'
  SHA256_HASH = 23 << 3,         // Base32-encodes to 'X...'
};

bool encode_ed25519_public_key(const uint8_t *in, char *out);

bool encode_med25519_public_key(const stellarxdr_MuxedAccountMed25519 *in,
                                char *out);

bool encode_ed25519_secret_seed(const uint8_t *in, char *out);

bool encode_pre_auth_tx(const uint8_t *in, char *out);

bool encode_sha256_hash(const uint8_t *in, char *out);

#endif
