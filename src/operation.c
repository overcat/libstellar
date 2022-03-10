#include "operation.h"
#include "muxed_account.h"
// 1. Create Account
bool create_account_to_xdr_object(const struct CreateAccountOp *in,
                                  stellarxdr_OperationBody *out) {
  out->type = stellarxdr_CREATE_ACCOUNT;

  struct Keypair keypair;
  keypair_from_address(&keypair, in->destination);
  stellarxdr_AccountID accountId;
  keypair_xdr_account_id(&keypair, &accountId);

  out->stellarxdr_OperationBody_u.createAccountOp.destination = accountId;
  out->stellarxdr_OperationBody_u.createAccountOp.startingBalance =
      in->startingBalance;
  return true;
}

bool create_account_from_xdr_object(const stellarxdr_OperationBody *in,
                                    struct CreateAccountOp *out) {
  out->startingBalance =
      in->stellarxdr_OperationBody_u.createAccountOp.startingBalance;
  char k[ED25519_PUBLIC_KEY_LENGTH + 1];
  if (!encode_ed25519_public_key(
          &in->stellarxdr_OperationBody_u.createAccountOp.destination
               .stellarxdr_PublicKey_u.ed25519,
          k)) {
    return false;
  }
  out->destination = malloc(ED25519_PUBLIC_KEY_LENGTH + 1);
  memcpy(out->destination, k, ED25519_PUBLIC_KEY_LENGTH + 1);
  return true;
}

// 2. Payment
bool payment_to_xdr_object(const struct PaymentOp *in,
                           stellarxdr_OperationBody *out) {
  out->type = stellarxdr_PAYMENT;

  stellarxdr_Asset stellarxdrAsset;
  if (!asset_to_xdr_object(&in->asset, &stellarxdrAsset)) {
    return false;
  }

  stellarxdr_MuxedAccount stellarxdrMuxedAccount;
  if (in->destination[0] == 'G') {
    stellarxdrMuxedAccount.type = stellarxdr_KEY_TYPE_ED25519;
    struct Keypair keypair;
    keypair_from_address(&keypair, in->destination);
    memcpy(stellarxdrMuxedAccount.stellarxdr_MuxedAccount_u.ed25519,
           keypair.public_key, 32);
  } else {
    stellarxdrMuxedAccount.type = stellarxdr_KEY_TYPE_MUXED_ED25519;
    if (!decode_med25519_public_key(
            in->destination,
            &stellarxdrMuxedAccount.stellarxdr_MuxedAccount_u.med25519)) {
      return false;
    }
  }

  out->stellarxdr_OperationBody_u.paymentOp.asset = stellarxdrAsset;
  out->stellarxdr_OperationBody_u.paymentOp.destination =
      stellarxdrMuxedAccount;
  out->stellarxdr_OperationBody_u.paymentOp.amount = in->amount;
  return true;
}

bool payment_from_xdr_object(const struct stellarxdr_OperationBody *in,
                             struct PaymentOp *out) {
  out->amount = in->stellarxdr_OperationBody_u.paymentOp.amount;
  struct Asset asset;
  if (!asset_from_xdr_object(&in->stellarxdr_OperationBody_u.paymentOp.asset,
                             &asset)) {
    return false;
  }
  out->asset = asset;
  switch (in->stellarxdr_OperationBody_u.paymentOp.destination.type) {
  case stellarxdr_KEY_TYPE_ED25519:
    out->destination = malloc(ED25519_PUBLIC_KEY_LENGTH + 1);
    if (!encode_ed25519_public_key(
            &in->stellarxdr_OperationBody_u.paymentOp.destination
                 .stellarxdr_MuxedAccount_u.ed25519,
            out->destination)) {
      return false;
    }
    break;
  case stellarxdr_KEY_TYPE_MUXED_ED25519:
    out->destination = malloc(MED25519_PUBLIC_KEY_LENGTH + 1);
    if (!encode_med25519_public_key(
            &in->stellarxdr_OperationBody_u.paymentOp.destination
                 .stellarxdr_MuxedAccount_u.med25519,
            out->destination)) {
      return false;
    }
    break;
  default:
    return false;
  }
  return true;
}

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
    create_account_to_xdr_object(&in->createAccountOp, &operation_body);
    break;
  case PAYMENT:
    payment_to_xdr_object(&in->paymentOp, &operation_body);
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
    out->type = CREATE_ACCOUNT;
    create_account_from_xdr_object(&in->body, &out->createAccountOp);
    break;
  case stellarxdr_PAYMENT:
    out->type = PAYMENT;
    payment_from_xdr_object(&in->body, &out->paymentOp);
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