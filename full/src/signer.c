#include "signer.h"

bool signer_to_xdr_object(const struct Signer *in, stellarxdr_Signer *out) {
  out->weight = in->weight;
  if (!signer_key_to_xdr_object(&in->key, &out->key)) {
    return false;
  }
  return true;
};

bool signer_from_xdr_object(const stellarxdr_Signer *in, struct Signer *out) {
  out->weight = in->weight;
  if (!signer_key_from_xdr_object(&in->key, &out->key)) {
    return false;
  }
  return true;
};