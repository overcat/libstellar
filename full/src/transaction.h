#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "memo.h"
#include "muxed_account.h"
#include "operation.h"
#include "stellarxdr.h"
#include "time_bounds.h"
#include <stdbool.h>
#include <stdint.h>

struct Transaction {
  struct MuxedAccount source_account;
  uint32_t base_fee;
  int64_t sequence_number;
  struct TimeBounds *time_bounds;
  struct Memo memo;
  uint8_t operations_len;
  struct Operation *operations;
};

bool transaction_to_xdr_object(const struct Transaction *in,
                               stellarxdr_Transaction *out);

bool transaction_from_xdr_object(const stellarxdr_Transaction *in,
                                 struct Transaction *out);
#endif
