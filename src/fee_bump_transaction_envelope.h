#ifndef FEE_BUMP_TRANSACTION_ENVELOPE_H
#define FEE_BUMP_TRANSACTION_ENVELOPE_H

#include "fee_bump_transaction.h"
#include "stellarxdr.h"
#include <stdbool.h>
#include <stdint.h>

struct FeeBumpTransactionEnvelope {
  struct FeeBumpTransaction transaction;
  char *networkPassphrase;
  uint8_t signatures_len;
  struct DecoratedSignature *signatures;
};

bool fee_bump_transaction_envelope_to_xdr_object(
    const struct FeeBumpTransactionEnvelope *in,
    stellarxdr_TransactionEnvelope *out);

bool fee_bump_transaction_envelope_from_xdr_object(
    const stellarxdr_TransactionEnvelope *in,
    struct FeeBumpTransactionEnvelope *out, char *networkPassphrase);

bool fee_bump_transaction_envelope_hash(
    struct FeeBumpTransactionEnvelope *feeBumpTransactionEnvelope,
    unsigned char *hash);

bool fee_bump_transaction_envelope_sign(
    const struct Keypair *signer,
    struct FeeBumpTransactionEnvelope *feeBumpTransactionEnvelope);
#endif
