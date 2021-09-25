#ifndef KEYPAIR_H
#define KEYPAIR_H

#include "stellarxdr.h"
#include <stdbool.h>
#include <stdint.h>

struct Keypair {
  uint8_t public_key[32];
  uint8_t seed[32];
  bool can_sign;
};

bool keypair_from_seed(struct Keypair *keypair, const uint8_t *seed);

bool keypair_from_secret(struct Keypair *keypair, const char *secret);

bool keypair_from_address(struct Keypair *keypair, const char *address);

bool keypair_random(struct Keypair *keypair);

bool keypair_address(const struct Keypair *keypair, char *address);

bool keypair_secret(const struct Keypair *keypair, char *secret);

bool keypair_sign(const struct Keypair *keypair, unsigned char *signature,
                  const unsigned char *message, size_t message_len);

bool keypair_verify(const struct Keypair *keypair,
                    const unsigned char *signature,
                    const unsigned char *message, size_t message_len);
#endif
