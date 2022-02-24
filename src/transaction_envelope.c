#include "transaction_envelope.h"

bool transaction_envelope_to_xdr_object(const struct TransactionEnvelope *in,
                                        stellarxdr_TransactionEnvelope *out) {
  stellarxdr_Transaction stellarxdrTransaction;
  transaction_to_xdr_object(&in->transaction, &stellarxdrTransaction);

  out->type = stellarxdr_ENVELOPE_TYPE_TX;
  out->stellarxdr_TransactionEnvelope_u.v1.tx = stellarxdrTransaction;
  out->stellarxdr_TransactionEnvelope_u.v1.signatures.signatures_len =
      in->signatures_len;
  out->stellarxdr_TransactionEnvelope_u.v1.signatures.signatures_val =
      malloc(in->signatures_len * sizeof(stellarxdr_DecoratedSignature));
  for (int i = 0; i < in->signatures_len; i++) {
    struct stellarxdr_DecoratedSignature stellarxdrDecoratedSignature;
    if (!decorated_signature_to_xdr_object(in->signatures + i,
                                           &stellarxdrDecoratedSignature)) {
      return false;
    }
    // memcpy?
    *(out->stellarxdr_TransactionEnvelope_u.v1.signatures.signatures_val + i) =
        stellarxdrDecoratedSignature;
  }
  return true;
};

bool transaction_envelope_from_xdr_object(
    const stellarxdr_TransactionEnvelope *in, struct TransactionEnvelope *out) {
  out->signatures_len =
      in->stellarxdr_TransactionEnvelope_u.v1.signatures.signatures_len;
  struct Transaction transaction;
  if (!transaction_from_xdr_object(&in->stellarxdr_TransactionEnvelope_u.v1.tx,
                                   &transaction)) {
    return false;
  }
  out->signatures =
      malloc(out->signatures_len * sizeof(struct DecoratedSignature));
  for (int i = 0; i < out->signatures_len; i++) {
    struct DecoratedSignature decoratedSignature;
    if (!decorated_signature_from_xdr_object(
            in->stellarxdr_TransactionEnvelope_u.v1.signatures.signatures_val +
                i,
            &decoratedSignature)) {
      return false;
    }
    // memcpy?
    *(out->signatures + i) = decoratedSignature;
  }
  return true;
  //    out->transaction = transaction_from_xdr_object()
};