#ifndef DECORATED_SIGNATURE_H
#define DECORATED_SIGNATURE_H

#include "stdbool.h"
#include "stellarxdr.h"
#include "strkey.h"

struct DecoratedSignature {
  uint8_t signatureHint[4];
  uint8_t signature[64];
};

bool decorated_signature_to_xdr_object(const struct DecoratedSignature *in,
                                 stellarxdr_DecoratedSignature *out);

bool decorated_signature_from_xdr_object(const stellarxdr_DecoratedSignature *in,
                                   struct DecoratedSignature *out);
#endif // DECORATED_SIGNATURE_H
