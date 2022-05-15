#ifndef SIGNER_H
#define SIGNER_H

#include "signer_key.h"
#include "stellarxdr.h"
#include <stdbool.h>

struct Signer {
  struct SignerKey key;
  uint32_t weight;
};

bool signer_to_xdr_object(const struct Signer *in, stellarxdr_Signer *out);

bool signer_from_xdr_object(const stellarxdr_Signer *in, struct Signer *out);

#endif
