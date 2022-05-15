#include "fee_bump_transaction.h"

bool fee_bump_transaction_to_xdr_object(const struct FeeBumpTransaction *in,
                                        stellarxdr_FeeBumpTransaction *out) {
  if (in->baseFee <= in->innerTransaction.transaction.base_fee) {
    return false;
  }
  uint32_t fee =
      (in->innerTransaction.transaction.operations_len + 1) * in->baseFee;
  out->fee = fee;
  if (!muxed_account_to_xdr_object(&in->feeSource, &out->feeSource)) {
    return false;
  }
  stellarxdr_TransactionEnvelope transactionEnvelope;
  if (!transaction_envelope_to_xdr_object(&in->innerTransaction,
                                          &transactionEnvelope)) {
    return false;
  }

  stellarxdr_FeeBumpTransactionInnerTx innerTx = {
      .type = stellarxdr_ENVELOPE_TYPE_TX,
      .stellarxdr_FeeBumpTransactionInnerTx_u = {
          .v1 = transactionEnvelope.stellarxdr_TransactionEnvelope_u.v1}};
  stellarxdr_FeeBumpTransactionExt ext = {.v = 0};
  out->ext = ext;
  out->innerTx = innerTx;
  return true;
};

bool fee_bump_transaction_from_xdr_object(
    const stellarxdr_FeeBumpTransaction *in, struct FeeBumpTransaction *out,
    char *networkPassphrase) {
  out->baseFee = in->fee / (in->innerTx.stellarxdr_FeeBumpTransactionInnerTx_u
                                .v1.tx.operations.operations_len +
                            1);
  if (!muxed_account_from_xdr_object(&in->feeSource, &out->feeSource)) {
    return false;
  }

  stellarxdr_TransactionEnvelope stellarxdrTransactionEnvelope = {
      .type = stellarxdr_ENVELOPE_TYPE_TX,
      .stellarxdr_TransactionEnvelope_u = {
          .v1 = in->innerTx.stellarxdr_FeeBumpTransactionInnerTx_u.v1}};
  if (!transaction_envelope_from_xdr_object(&stellarxdrTransactionEnvelope,
                                            &out->innerTransaction,
                                            networkPassphrase)) {
    return false;
  }
  return true;
};