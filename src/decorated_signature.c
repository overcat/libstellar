#include "decorated_signature.h"

bool decorated_signature_to_xdr_object(const struct DecoratedSignature *in,
                                       stellarxdr_DecoratedSignature *out) {
  memcpy(out->hint, in->signatureHint);
  memcpy(out->signature, in->signature);
  return true;
};

bool decorated_signature_from_xdr_object(
    const stellarxdr_DecoratedSignature *in, struct DecoratedSignature *out) {
  memcpy(out->signatureHint, in->hint);
  memcpy(out->signature, in->signature);
  return true;
};