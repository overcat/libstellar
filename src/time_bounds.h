#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "memo.h"
#include "muxed_account.h"
#include "operation.h"
#include "stellarxdr.h"
#include <stdbool.h>
#include <stdint.h>

struct TimeBounds {
  uint64_t min_time;
  uint64_t max_time;
};

bool time_bounds_to_xdr_object(const struct TimeBounds *in,
                               stellarxdr_TimeBounds *out);

bool time_bounds_from_xdr_object(const stellarxdr_TimeBounds *in,
                                 struct TimeBounds *out);

#endif
