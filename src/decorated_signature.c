#include "decorated_signature.h"

bool decorated_signature_to_xdr_object(const struct DecoratedSignature *in,
                                       stellarxdr_DecoratedSignature *out) {
  memcpy(out->hint, in->signatureHint, 4);
  out->signature.stellarxdr_Signature_len = 64;
  out->signature.stellarxdr_Signature_val = malloc(64);
  memcpy(out->signature.stellarxdr_Signature_val, in->signature, 64);
  return true;
};

bool decorated_signature_from_xdr_object(
    const stellarxdr_DecoratedSignature *in, struct DecoratedSignature *out) {
  memcpy(out->signatureHint, in->hint, 4);
  memcpy(out->signature, in->signature.stellarxdr_Signature_val, 64);
  return true;
};