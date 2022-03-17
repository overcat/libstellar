#ifndef FEE_BUMP_TRANSACTION_H
#define FEE_BUMP_TRANSACTION_H

#include "muxed_account.h"
#include "stellarxdr.h"
#include "transaction_envelope.h"
#include <stdbool.h>
#include <stdint.h>

struct FeeBumpTransaction {
  struct MuxedAccount feeSource;
  uint32_t baseFee;
  struct TransactionEnvelope innerTransaction;
};

bool fee_bump_transaction_to_xdr_object(const struct FeeBumpTransaction *in,
                                        stellarxdr_FeeBumpTransaction *out);

bool fee_bump_transaction_from_xdr_object(
    const stellarxdr_FeeBumpTransaction *in, struct FeeBumpTransaction *out,
    char *networkPassphrase);
#endif
