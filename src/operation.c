#include "operation.h"
#include "muxed_account.h"
// 11. Bump Sequence
bool bump_sequence_to_xdr_object(const struct BumpSequenceOp *in,
                                 stellarxdr_OperationBody *out) {
  out->type = stellarxdr_BUMP_SEQUENCE;
  out->stellarxdr_OperationBody_u.bumpSequenceOp.bumpTo = in->bump_to;
  return true;
}

bool bump_sequence_from_xdr_object(const stellarxdr_OperationBody *in,
                                   struct BumpSequenceOp *out) {
  out->bump_to = in->stellarxdr_OperationBody_u.bumpSequenceOp.bumpTo;
  return true;
}

bool operation_to_xdr_object(const struct Operation *in,
                             stellarxdr_Operation *out) {
  stellarxdr_OperationBody operation_body;
  switch (in->type) {
  case CREATE_ACCOUNT:
    break;
  case PAYMENT:
    break;
  case PATH_PAYMENT_STRICT_RECEIVE:
    break;
  case MANAGE_SELL_OFFER:
    break;
  case CREATE_PASSIVE_SELL_OFFER:
    break;
  case SET_OPTIONS:
    break;
  case CHANGE_TRUST:
    break;
  case ALLOW_TRUST:
    break;
  case ACCOUNT_MERGE:
    break;
  case INFLATION:
    break;
  case MANAGE_DATA:
    break;
  case BUMP_SEQUENCE:
    bump_sequence_to_xdr_object(&in->bump_sequence_op, &operation_body);
    break;
  case MANAGE_BUY_OFFER:
    break;
  case PATH_PAYMENT_STRICT_SEND:
    break;
  case CREATE_CLAIMABLE_BALANCE:
    break;
  case CLAIM_CLAIMABLE_BALANCE:
    break;
  case BEGIN_SPONSORING_FUTURE_RESERVES:
    break;
  case END_SPONSORING_FUTURE_RESERVES:
    break;
  case REVOKE_SPONSORSHIP:
    break;
  case CLAWBACK:
    break;
  case CLAWBACK_CLAIMABLE_BALANCE:
    break;
  case SET_TRUST_LINE_FLAGS:
    break;
  case LIQUIDITY_POOL_DEPOSIT:
    break;
  case LIQUIDITY_POOL_WITHDRAW:
    break;
  default:
    return false;
  }
  if (in->source_account_present) {
    if (!muxed_account_to_xdr_object(&in->source_account, out->sourceAccount)) {
      return false;
    }
  } else {
    out->sourceAccount = NULL;
  }
  out->body = operation_body;
  return true;
}

bool operation_from_xdr_object(const stellarxdr_Operation *in,
                               struct Operation *out) {
  if (in->sourceAccount == NULL) {
    out->source_account_present = false;
  } else {
    out->source_account_present = true;
    if (!muxed_account_from_xdr_object(in->sourceAccount,
                                       &out->source_account)) {
      return false;
    }
  }
  switch (in->body.type) {
  case stellarxdr_CREATE_ACCOUNT:
    break;
  case stellarxdr_PAYMENT:
    break;
  case stellarxdr_PATH_PAYMENT_STRICT_RECEIVE:
    break;
  case stellarxdr_MANAGE_SELL_OFFER:
    break;
  case stellarxdr_CREATE_PASSIVE_SELL_OFFER:
    break;
  case stellarxdr_SET_OPTIONS:
    break;
  case stellarxdr_CHANGE_TRUST:
    break;
  case stellarxdr_ALLOW_TRUST:
    break;
  case stellarxdr_ACCOUNT_MERGE:
    break;
  case stellarxdr_INFLATION:
    break;
  case stellarxdr_MANAGE_DATA:
    break;
  case stellarxdr_BUMP_SEQUENCE:
    out->type = BUMP_SEQUENCE;
    bump_sequence_from_xdr_object(&in->body, &out->bump_sequence_op);
    break;
  case stellarxdr_MANAGE_BUY_OFFER:
    break;
  case stellarxdr_PATH_PAYMENT_STRICT_SEND:
    break;
  case stellarxdr_CREATE_CLAIMABLE_BALANCE:
    break;
  case stellarxdr_CLAIM_CLAIMABLE_BALANCE:
    break;
  case stellarxdr_BEGIN_SPONSORING_FUTURE_RESERVES:
    break;
  case stellarxdr_END_SPONSORING_FUTURE_RESERVES:
    break;
  case stellarxdr_REVOKE_SPONSORSHIP:
    break;
  case stellarxdr_CLAWBACK:
    break;
  case stellarxdr_CLAWBACK_CLAIMABLE_BALANCE:
    break;
  case stellarxdr_SET_TRUST_LINE_FLAGS:
    break;
  case stellarxdr_LIQUIDITY_POOL_DEPOSIT:
    break;
  case stellarxdr_LIQUIDITY_POOL_WITHDRAW:
    break;
  default:
    return false;
  }
  return true;
}

// TODO: remove
bool operation_to_xdr(const struct Operation *in, char **buf,
                      size_t *buf_size) {
  stellarxdr_Operation operation_xdr;
  operation_to_xdr_object(in, &operation_xdr);
  FILE *fp = open_memstream(buf, buf_size);
  XDR xdr;
  xdrstdio_create(&xdr, fp, XDR_ENCODE);
  if (!xdr_stellarxdr_Operation(&xdr, &operation_xdr)) {
    fclose(fp);
    return false;
  }
  fclose(fp);
  return true;
}