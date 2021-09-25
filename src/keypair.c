#include "keypair.h"
#include "strkey.h"
#include "vendor/ed25519/ed25519.h"

bool keypair_from_seed(struct Keypair *keypair, const uint8_t *seed) {
  memcpy(keypair->seed, seed, 32);
  uint8_t _private_key[64];
  ed25519_create_keypair(keypair->public_key, _private_key, keypair->seed);
  keypair->can_sign = true;
  return true;
}

bool keypair_from_secret(struct Keypair *keypair, const char *secret) {
  uint8_t seed[32];
  if (!decode_ed25519_secret_seed(secret, seed)) {
    return false;
  }
  return keypair_from_seed(keypair, seed);
}

bool keypair_from_address(struct Keypair *keypair, const char *address) {
  if (!decode_ed25519_public_key(address, keypair->public_key)) {
    return false;
  }
  keypair->can_sign = false;
  return true;
}

bool keypair_random(struct Keypair *keypair) {
  uint8_t seed[32];
  if (ed25519_create_seed(seed) != 0) {
    return false;
  }
  return keypair_from_seed(keypair, seed);
}

bool keypair_address(const struct Keypair *keypair, char *address) {
  return encode_ed25519_public_key(keypair->public_key, address);
}

bool keypair_secret(const struct Keypair *keypair, char *secret) {
  if (!keypair->can_sign) {
    return false;
  }
  return encode_ed25519_secret_seed(keypair->seed, secret);
}