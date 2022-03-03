#ifndef TRANSACTION_ENVELOPE_H
#define TRANSACTION_ENVELOPE_H

#include "decorated_signature.h"
#include "keypair.h"
#include "network.h"
#include "stellarxdr.h"
#include "transaction.h"
#include "vendor/sha256/sha256.h"
#include <stdbool.h>
#include <stdint.h>

struct TransactionEnvelope {
  struct Transaction transaction;
  char *networkPassphrase;
  uint8_t signatures_len;
  struct DecoratedSignature *signatures;
};

bool transaction_envelope_to_xdr_object(const struct TransactionEnvelope *in,
                                        stellarxdr_TransactionEnvelope *out);

bool transaction_envelope_from_xdr_object(
    const stellarxdr_TransactionEnvelope *in, struct TransactionEnvelope *out);

bool transaction_envelope_hash(struct TransactionEnvelope *transactionEnvelope,
                               char *hash);

bool transaction_envelope_sign(const struct Keypair *signer,
                               struct TransactionEnvelope *TransactionEnvelope);
#endif
