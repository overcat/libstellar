#include "transaction.h"

bool transaction_to_xdr_object(const struct Transaction *in,
                               stellarxdr_Transaction *out) {
  stellarxdr_MuxedAccount muxed_account_xdr;
  if (!muxed_account_to_xdr_object(&in->source_account, &muxed_account_xdr)) {
    return false;
  }
  stellarxdr_Memo memo_xdr;
  if (!memo_to_xdr_object(&in->memo, &memo_xdr)) {
    return false;
  }
  out->sourceAccount = muxed_account_xdr;
  out->memo = memo_xdr;
  out->fee = in->base_fee * in->operations_len;
  out->seqNum = in->sequence_number;
  if (in->time_bounds == NULL) {
    out->timeBounds = NULL;
  } else {
    stellarxdr_TimeBounds *time_bounds_xdr =
        malloc(sizeof(stellarxdr_TimeBounds));
    if (time_bounds_xdr == NULL) {
      return false;
    }
    if (!time_bounds_to_xdr_object(in->time_bounds, time_bounds_xdr)) {
      return false;
    }
    out->timeBounds = time_bounds_xdr;
  }
  out->operations.operations_len = in->operations_len;
  stellarxdr_Operation *operations_xdr =
      malloc(in->operations_len * sizeof(stellarxdr_Operation));
  if (operations_xdr == NULL) {
    return false;
  }
  for (int i = 0; i < in->operations_len; i++) {
    stellarxdr_Operation operation_xdr;
    if (!operation_to_xdr_object(in->operations + i, &operation_xdr)) {
      return false;
    }
    *(operations_xdr + i) = operation_xdr;
  }
  out->operations.operations_val = operations_xdr;
  stellarxdr_TransactionExt ext = {.v = 0};
  out->ext = ext;
  return true;
}

bool transaction_from_xdr_object(const stellarxdr_Transaction *in,
                                 struct Transaction *out) {
  struct MuxedAccount source_account;
  if (!muxed_account_from_xdr_object(&in->sourceAccount, &source_account)) {
    return false;
  }
  struct Memo memo;
  if (!memo_from_xdr_object(&in->memo, &memo)) {
    return false;
  }
  out->source_account = source_account;
  out->memo = memo;
  out->sequence_number = in->seqNum;
  if (in->timeBounds == NULL) {
    out->time_bounds = NULL;
  } else {
    struct TimeBounds *time_bounds = malloc(sizeof(struct TimeBounds));
    if (time_bounds == NULL) {
      return false;
    }
    if (!time_bounds_from_xdr_object(in->timeBounds, time_bounds)) {
      return false;
    }
    out->time_bounds = time_bounds;
  }
  out->base_fee = in->fee / in->operations.operations_len;
  out->operations_len = in->operations.operations_len;
  struct Operation *operations =
      malloc(in->operations.operations_len * sizeof(struct Operation));
  if (operations == NULL) {
    return false;
  }
  for (int i = 0; i < in->operations.operations_len; i++) {
    struct Operation operation;
    if (!operation_from_xdr_object(in->operations.operations_val + i,
                                   &operation)) {
      return false;
    }
    *(operations + i) = operation;
  }
  out->operations = operations;
  return true;
}

