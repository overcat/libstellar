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

// 3. Path Payment Strict Receive
bool path_payment_strict_receive_to_xdr_object(
    const struct PathPaymentStrictReceiveOp *in,
    stellarxdr_OperationBody *out) {
  out->type = stellarxdr_PATH_PAYMENT_STRICT_RECEIVE;

  if (!asset_to_xdr_object(&in->sendAsset,
                           &out->stellarxdr_OperationBody_u
                                .pathPaymentStrictReceiveOp.sendAsset)) {
    return false;
  }
  out->stellarxdr_OperationBody_u.pathPaymentStrictReceiveOp.sendMax =
      in->sendMax;
  if (!muxed_account_to_xdr_object(
          &in->destination, &out->stellarxdr_OperationBody_u
                                 .pathPaymentStrictReceiveOp.destination)) {
    return false;
  }
  if (!asset_to_xdr_object(&in->destAsset,
                           &out->stellarxdr_OperationBody_u
                                .pathPaymentStrictReceiveOp.destAsset)) {
    return false;
  }
  out->stellarxdr_OperationBody_u.pathPaymentStrictReceiveOp.destAmount =
      in->destAmount;
  out->stellarxdr_OperationBody_u.pathPaymentStrictReceiveOp.path.path_len =
      in->pathLen;
  out->stellarxdr_OperationBody_u.pathPaymentStrictReceiveOp.path.path_val =
      malloc(in->pathLen * sizeof(stellarxdr_Asset));
  for (int i = 0; i < in->pathLen; i++) {
    if (!asset_to_xdr_object(&in->path[i],
                             out->stellarxdr_OperationBody_u
                                     .pathPaymentStrictReceiveOp.path.path_val +
                                 i)) {
      return false;
    }
  }

  return true;
}

bool path_payment_strict_receive_from_xdr_object(
    const stellarxdr_OperationBody *in,
    struct PathPaymentStrictReceiveOp *out) {

  if (!asset_from_xdr_object(
          &in->stellarxdr_OperationBody_u.pathPaymentStrictReceiveOp.sendAsset,
          &out->sendAsset)) {
    return false;
  }
  out->sendMax =
      in->stellarxdr_OperationBody_u.pathPaymentStrictReceiveOp.sendMax;
  if (!asset_from_xdr_object(
          &in->stellarxdr_OperationBody_u.pathPaymentStrictReceiveOp.destAsset,
          &out->destAsset)) {
    return false;
  }
  if (!muxed_account_from_xdr_object(
          &in->stellarxdr_OperationBody_u.pathPaymentStrictReceiveOp
               .destination,
          &out->destination)) {
    return false;
  }
  out->destAmount =
      in->stellarxdr_OperationBody_u.pathPaymentStrictReceiveOp.destAmount;
  out->pathLen =
      in->stellarxdr_OperationBody_u.pathPaymentStrictReceiveOp.path.path_len;
  for (int i = 0; i < out->pathLen; i++) {
    if (!asset_from_xdr_object(
            in->stellarxdr_OperationBody_u.pathPaymentStrictReceiveOp.path
                    .path_val +
                i,
            &out->path[i])) {
      return false;
    }
  }
  return true;
}

// 4. Manage Sell Offer
bool manage_sell_offer_to_xdr_object(const struct ManageSellOfferOp *in,
                                     stellarxdr_OperationBody *out) {
  out->type = stellarxdr_MANAGE_SELL_OFFER;

  if (!asset_to_xdr_object(
          &in->selling,
          &out->stellarxdr_OperationBody_u.manageSellOfferOp.selling)) {
    return false;
  }
  if (!asset_to_xdr_object(
          &in->buying,
          &out->stellarxdr_OperationBody_u.manageSellOfferOp.buying)) {
    return false;
  }
  out->stellarxdr_OperationBody_u.manageSellOfferOp.amount = in->amount;
  if (!price_to_xdr_object(
          &in->price,
          &out->stellarxdr_OperationBody_u.manageSellOfferOp.price)) {
    return false;
  }
  out->stellarxdr_OperationBody_u.manageSellOfferOp.offerID = in->offerID;
  return true;
}

bool manage_sell_offer_from_xdr_object(const stellarxdr_OperationBody *in,
                                       struct ManageSellOfferOp *out) {
  if (!asset_from_xdr_object(
          &in->stellarxdr_OperationBody_u.manageSellOfferOp.selling,
          &out->selling)) {
    return false;
  }
  if (!asset_from_xdr_object(
          &in->stellarxdr_OperationBody_u.manageSellOfferOp.buying,
          &out->buying)) {
    return false;
  }
  out->amount = in->stellarxdr_OperationBody_u.manageSellOfferOp.amount;
  if (!price_from_xdr_object(
          &in->stellarxdr_OperationBody_u.manageSellOfferOp.price,
          &out->price)) {
    return false;
  }
  out->offerID = in->stellarxdr_OperationBody_u.manageSellOfferOp.offerID;
  return true;
}

// 5. Create Passive Sell Offer
bool create_passive_sell_offer_to_xdr_object(
    const struct CreatePassiveSellOfferOp *in, stellarxdr_OperationBody *out) {
  out->type = stellarxdr_CREATE_PASSIVE_SELL_OFFER;

  if (!asset_to_xdr_object(
          &in->selling,
          &out->stellarxdr_OperationBody_u.createPassiveSellOfferOp.selling)) {
    return false;
  }
  if (!asset_to_xdr_object(
          &in->buying,
          &out->stellarxdr_OperationBody_u.createPassiveSellOfferOp.buying)) {
    return false;
  }
  out->stellarxdr_OperationBody_u.createPassiveSellOfferOp.amount = in->amount;
  if (!price_to_xdr_object(
          &in->price,
          &out->stellarxdr_OperationBody_u.createPassiveSellOfferOp.price)) {
    return false;
  }
  return true;
}

bool create_passive_sell_offer_from_xdr_object(
    const stellarxdr_OperationBody *in, struct CreatePassiveSellOfferOp *out) {
  if (!asset_from_xdr_object(
          &in->stellarxdr_OperationBody_u.createPassiveSellOfferOp.selling,
          &out->selling)) {
    return false;
  }
  if (!asset_from_xdr_object(
          &in->stellarxdr_OperationBody_u.createPassiveSellOfferOp.buying,
          &out->buying)) {
    return false;
  }
  out->amount = in->stellarxdr_OperationBody_u.createPassiveSellOfferOp.amount;
  if (!price_from_xdr_object(
          &in->stellarxdr_OperationBody_u.createPassiveSellOfferOp.price,
          &out->price)) {
    return false;
  }
  return true;
}

// 7. Allow Trust
bool allow_trust_to_xdr_object(const struct AllowTrustOp *in,
                               stellarxdr_OperationBody *out) {
  out->type = stellarxdr_ALLOW_TRUST;
  if (strlen(in->assetCode) <= 4) {
    out->stellarxdr_OperationBody_u.allowTrustOp.asset.type =
        stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4;
    for (int i = 0; i < 4; i++) {
      if (i < strlen(in->assetCode)) {
        out->stellarxdr_OperationBody_u.allowTrustOp.asset
            .stellarxdr_AssetCode_u.assetCode4[i] = in->assetCode[i];
      } else {
        out->stellarxdr_OperationBody_u.allowTrustOp.asset
            .stellarxdr_AssetCode_u.assetCode4[i] = '\0';
      }
    }
  } else {
    out->stellarxdr_OperationBody_u.allowTrustOp.asset.type =
        stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12;
    for (int i = 0; i < 12; i++) {
      if (i < strlen(in->assetCode)) {
        out->stellarxdr_OperationBody_u.allowTrustOp.asset
            .stellarxdr_AssetCode_u.assetCode4[i] = in->assetCode[i];
      } else {
        out->stellarxdr_OperationBody_u.allowTrustOp.asset
            .stellarxdr_AssetCode_u.assetCode4[i] = '\0';
      }
    }
  }
  out->stellarxdr_OperationBody_u.allowTrustOp.authorize = in->authorize;

  struct Keypair keypair;
  keypair_from_address(&keypair, in->trustor);
  stellarxdr_AccountID accountId;
  keypair_xdr_account_id(&keypair, &accountId);
  out->stellarxdr_OperationBody_u.allowTrustOp.trustor = accountId;
  return true;
}

bool allow_trust_from_xdr_object(const stellarxdr_OperationBody *in,
                                 struct AllowTrustOp *out) {
  out->authorize = in->stellarxdr_OperationBody_u.allowTrustOp.authorize;
  if (!encode_ed25519_public_key(&in->stellarxdr_OperationBody_u.allowTrustOp
                                      .trustor.stellarxdr_PublicKey_u.ed25519,
                                 out->trustor)) {
    return false;
  }
  switch (in->stellarxdr_OperationBody_u.allowTrustOp.asset.type) {
  case stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4:
    memcpy(out->assetCode,
           in->stellarxdr_OperationBody_u.allowTrustOp.asset
               .stellarxdr_AssetCode_u.assetCode4,
           4);
    out->assetCode[4] = '\0';
    break;
  case stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12:
    memcpy(out->assetCode,
           in->stellarxdr_OperationBody_u.allowTrustOp.asset
               .stellarxdr_AssetCode_u.assetCode4,
           12);
    out->assetCode[12] = '\0';
    break;
  default:
    return false;
  }
  return true;
}

// 9. Inflation
bool inflation_to_xdr_object(stellarxdr_OperationBody *out) {
  out->type = stellarxdr_INFLATION;
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

// 12. Manage Buy Offer
bool manage_buy_offer_to_xdr_object(const struct ManageBuyOfferOp *in,
                                    stellarxdr_OperationBody *out) {
  out->type = stellarxdr_MANAGE_BUY_OFFER;

  if (!asset_to_xdr_object(
          &in->selling,
          &out->stellarxdr_OperationBody_u.manageBuyOfferOp.selling)) {
    return false;
  }
  if (!asset_to_xdr_object(
          &in->buying,
          &out->stellarxdr_OperationBody_u.manageBuyOfferOp.buying)) {
    return false;
  }
  out->stellarxdr_OperationBody_u.manageBuyOfferOp.buyAmount = in->buyAmount;
  if (!price_to_xdr_object(
          &in->price,
          &out->stellarxdr_OperationBody_u.manageBuyOfferOp.price)) {
    return false;
  }
  out->stellarxdr_OperationBody_u.manageBuyOfferOp.offerID = in->offerID;
  return true;
}

bool manage_buy_offer_from_xdr_object(const stellarxdr_OperationBody *in,
                                      struct ManageBuyOfferOp *out) {
  if (!asset_from_xdr_object(
          &in->stellarxdr_OperationBody_u.manageBuyOfferOp.selling,
          &out->selling)) {
    return false;
  }
  if (!asset_from_xdr_object(
          &in->stellarxdr_OperationBody_u.manageBuyOfferOp.buying,
          &out->buying)) {
    return false;
  }
  out->buyAmount = in->stellarxdr_OperationBody_u.manageBuyOfferOp.buyAmount;
  if (!price_from_xdr_object(
          &in->stellarxdr_OperationBody_u.manageBuyOfferOp.price,
          &out->price)) {
    return false;
  }
  out->offerID = in->stellarxdr_OperationBody_u.manageBuyOfferOp.offerID;
  return true;
}

// 13. Path Payment Strict Send
bool path_payment_strict_send_to_xdr_object(
    const struct PathPaymentStrictSendOp *in, stellarxdr_OperationBody *out) {
  out->type = stellarxdr_PATH_PAYMENT_STRICT_SEND;

  if (!asset_to_xdr_object(
          &in->sendAsset,
          &out->stellarxdr_OperationBody_u.pathPaymentStrictSendOp.sendAsset)) {
    return false;
  }
  out->stellarxdr_OperationBody_u.pathPaymentStrictSendOp.sendAmount =
      in->sendAmount;
  if (!muxed_account_to_xdr_object(&in->destination,
                                   &out->stellarxdr_OperationBody_u
                                        .pathPaymentStrictSendOp.destination)) {
    return false;
  }
  if (!asset_to_xdr_object(
          &in->destAsset,
          &out->stellarxdr_OperationBody_u.pathPaymentStrictSendOp.destAsset)) {
    return false;
  }
  out->stellarxdr_OperationBody_u.pathPaymentStrictSendOp.destMin = in->destMin;
  out->stellarxdr_OperationBody_u.pathPaymentStrictSendOp.path.path_len =
      in->pathLen;
  out->stellarxdr_OperationBody_u.pathPaymentStrictSendOp.path.path_val =
      malloc(in->pathLen * sizeof(stellarxdr_Asset));
  for (int i = 0; i < in->pathLen; i++) {
    if (!asset_to_xdr_object(&in->path[i],
                             out->stellarxdr_OperationBody_u
                                     .pathPaymentStrictSendOp.path.path_val +
                                 i)) {
      return false;
    }
  }

  return true;
}

bool path_payment_strict_send_from_xdr_object(
    const stellarxdr_OperationBody *in, struct PathPaymentStrictSendOp *out) {

  if (!asset_from_xdr_object(
          &in->stellarxdr_OperationBody_u.pathPaymentStrictSendOp.sendAsset,
          &out->sendAsset)) {
    return false;
  }
  out->sendAmount =
      in->stellarxdr_OperationBody_u.pathPaymentStrictSendOp.sendAmount;
  if (!asset_from_xdr_object(
          &in->stellarxdr_OperationBody_u.pathPaymentStrictSendOp.destAsset,
          &out->destAsset)) {
    return false;
  }
  if (!muxed_account_from_xdr_object(
          &in->stellarxdr_OperationBody_u.pathPaymentStrictSendOp.destination,
          &out->destination)) {
    return false;
  }
  out->destMin = in->stellarxdr_OperationBody_u.pathPaymentStrictSendOp.destMin;
  out->pathLen =
      in->stellarxdr_OperationBody_u.pathPaymentStrictSendOp.path.path_len;
  for (int i = 0; i < out->pathLen; i++) {
    if (!asset_from_xdr_object(in->stellarxdr_OperationBody_u
                                       .pathPaymentStrictSendOp.path.path_val +
                                   i,
                               &out->path[i])) {
      return false;
    }
  }
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
    path_payment_strict_receive_to_xdr_object(&in->pathPaymentStrictReceiveOp,
                                              &operation_body);
    break;
  case MANAGE_SELL_OFFER:
    manage_sell_offer_to_xdr_object(&in->manageSellOfferOp, &operation_body);
    break;
  case CREATE_PASSIVE_SELL_OFFER:
    create_passive_sell_offer_to_xdr_object(&in->createPassiveSellOfferOp,
                                            &operation_body);
    break;
  case SET_OPTIONS:
    break;
  case CHANGE_TRUST:
    break;
  case ALLOW_TRUST:
    allow_trust_to_xdr_object(&in->allowTrustOp, &operation_body);
    break;
  case ACCOUNT_MERGE:
    break;
  case INFLATION:
    inflation_to_xdr_object(&operation_body);
    break;
  case MANAGE_DATA:
    break;
  case BUMP_SEQUENCE:
    bump_sequence_to_xdr_object(&in->bump_sequence_op, &operation_body);
    break;
  case MANAGE_BUY_OFFER:
    manage_buy_offer_to_xdr_object(&in->manageBuyOfferOp, &operation_body);
    break;
  case PATH_PAYMENT_STRICT_SEND:
    path_payment_strict_send_to_xdr_object(&in->pathPaymentStrictSendOp,
                                           &operation_body);
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
    out->type = PATH_PAYMENT_STRICT_RECEIVE;
    path_payment_strict_receive_from_xdr_object(
        &in->body, &out->pathPaymentStrictReceiveOp);
    break;
  case stellarxdr_MANAGE_SELL_OFFER:
    out->type = MANAGE_SELL_OFFER;
    manage_sell_offer_from_xdr_object(&in->body, &out->manageSellOfferOp);
    break;
  case stellarxdr_CREATE_PASSIVE_SELL_OFFER:
    out->type = CREATE_PASSIVE_SELL_OFFER;
    create_passive_sell_offer_from_xdr_object(&in->body,
                                              &out->createPassiveSellOfferOp);
    break;
  case stellarxdr_SET_OPTIONS:
    break;
  case stellarxdr_CHANGE_TRUST:
    break;
  case stellarxdr_ALLOW_TRUST:
    out->type = ALLOW_TRUST;
    allow_trust_from_xdr_object(&in->body, &out->allowTrustOp);
    break;
  case stellarxdr_ACCOUNT_MERGE:
    break;
  case stellarxdr_INFLATION:
    out->type = INFLATION;
    break;
  case stellarxdr_MANAGE_DATA:
    break;
  case stellarxdr_BUMP_SEQUENCE:
    out->type = BUMP_SEQUENCE;
    bump_sequence_from_xdr_object(&in->body, &out->bump_sequence_op);
    break;
  case stellarxdr_MANAGE_BUY_OFFER:
    out->type = MANAGE_BUY_OFFER;
    manage_buy_offer_from_xdr_object(&in->body, &out->manageBuyOfferOp);
    break;
  case stellarxdr_PATH_PAYMENT_STRICT_SEND:
    out->type = PATH_PAYMENT_STRICT_SEND;
    path_payment_strict_send_from_xdr_object(&in->body,
                                             &out->pathPaymentStrictSendOp);
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