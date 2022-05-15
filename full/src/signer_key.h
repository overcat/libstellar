#ifndef SIGNER_KEY_H
#define SIGNER_KEY_H

#include "stellarxdr.h"
#include <stdbool.h>

enum SignerKeyType {
  SIGNER_KEY_TYPE_ED25519 = 0,
  SIGNER_KEY_TYPE_PRE_AUTH_TX = 1,
  SIGNER_KEY_TYPE_HASH_X = 2,
};

struct SignerKey {
  enum SignerKeyType signerKeyType;
  union {
    unsigned char ed25519[32];
    unsigned char preAuthTx[32];
    unsigned char hashX[32];
  } signerKey;
};

bool signer_key_to_xdr_object(const struct SignerKey *in,
                              stellarxdr_SignerKey *out);

bool signer_key_from_xdr_object(const stellarxdr_SignerKey *in,
                                struct SignerKey *out);

#endif
