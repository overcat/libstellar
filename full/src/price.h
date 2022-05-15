#ifndef PRICE_H
#define PRICE_H

#include "stellarxdr.h"
#include <stdbool.h>

struct Price {
  int32_t n;
  int32_t d;
};

bool price_to_xdr_object(const struct Price *in, stellarxdr_Price *out);

bool price_from_xdr_object(const stellarxdr_Price *in, struct Price *out);

#endif
