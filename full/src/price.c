#include "price.h"

bool price_to_xdr_object(const struct Price *in, stellarxdr_Price *out) {
  out->n = in->n;
  out->d = in->d;
  return true;
}

bool price_from_xdr_object(const stellarxdr_Price *in, struct Price *out) {
  out->n = in->n;
  out->d = in->d;
  return true;
}
