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

// 5. Set Options
bool set_options_to_xdr_object(const struct SetOptionsOp *in,
                               stellarxdr_OperationBody *out) {
  out->type = stellarxdr_SET_OPTIONS;
  if (in->inflationDestPresent) {
    struct Keypair keypair;
    keypair_from_address(&keypair, in->inflationDest);
    out->stellarxdr_OperationBody_u.setOptionsOp.inflationDest =
        malloc(sizeof(stellarxdr_PublicKey));
    stellarxdr_PublicKey publicKey = {.type =
                                          stellarxdr_PUBLIC_KEY_TYPE_ED25519};
    memcpy(publicKey.stellarxdr_PublicKey_u.ed25519, keypair.public_key, 32);
    memcpy(out->stellarxdr_OperationBody_u.setOptionsOp.inflationDest,
           &publicKey, sizeof(stellarxdr_PublicKey));
  } else {
    out->stellarxdr_OperationBody_u.setOptionsOp.inflationDest = NULL;
  }
  if (in->clearFlagsPresent) {
    out->stellarxdr_OperationBody_u.setOptionsOp.clearFlags =
        malloc(sizeof(stellarxdr_uint32));
    *out->stellarxdr_OperationBody_u.setOptionsOp.clearFlags = in->clearFlags;
  } else {
    out->stellarxdr_OperationBody_u.setOptionsOp.clearFlags = NULL;
  }

  if (in->setFlagsPresent) {
    out->stellarxdr_OperationBody_u.setOptionsOp.setFlags =
        malloc(sizeof(stellarxdr_uint32));
    *out->stellarxdr_OperationBody_u.setOptionsOp.setFlags = in->setFlags;
  } else {
    out->stellarxdr_OperationBody_u.setOptionsOp.setFlags = NULL;
  }

  if (in->masterWeightPresent) {
    out->stellarxdr_OperationBody_u.setOptionsOp.masterWeight =
        malloc(sizeof(stellarxdr_uint32));
    *out->stellarxdr_OperationBody_u.setOptionsOp.masterWeight =
        in->masterWeight;
  } else {
    out->stellarxdr_OperationBody_u.setOptionsOp.masterWeight = NULL;
  }

  if (in->lowThresholdPresent) {
    out->stellarxdr_OperationBody_u.setOptionsOp.lowThreshold =
        malloc(sizeof(stellarxdr_uint32));
    *out->stellarxdr_OperationBody_u.setOptionsOp.lowThreshold =
        in->lowThreshold;
  } else {
    out->stellarxdr_OperationBody_u.setOptionsOp.lowThreshold = NULL;
  }

  if (in->medThresholdPresent) {
    out->stellarxdr_OperationBody_u.setOptionsOp.medThreshold =
        malloc(sizeof(stellarxdr_uint32));
    *out->stellarxdr_OperationBody_u.setOptionsOp.medThreshold =
        in->medThreshold;
  } else {
    out->stellarxdr_OperationBody_u.setOptionsOp.medThreshold = NULL;
  }
  if (in->highThresholdPresent) {
    out->stellarxdr_OperationBody_u.setOptionsOp.highThreshold =
        malloc(sizeof(stellarxdr_uint32));
    *out->stellarxdr_OperationBody_u.setOptionsOp.highThreshold =
        in->highThreshold;
  } else {
    out->stellarxdr_OperationBody_u.setOptionsOp.highThreshold = NULL;
  }
  if (in->homeDomainPresent) {
    out->stellarxdr_OperationBody_u.setOptionsOp.homeDomain =
        malloc(sizeof(stellarxdr_string32));
    *out->stellarxdr_OperationBody_u.setOptionsOp.homeDomain =
        malloc(strlen(in->homeDomain) + 1);
    strcpy(*out->stellarxdr_OperationBody_u.setOptionsOp.homeDomain,
           in->homeDomain);
  } else {
    out->stellarxdr_OperationBody_u.setOptionsOp.homeDomain = NULL;
  }
  if (in->signerPresent) {
    out->stellarxdr_OperationBody_u.setOptionsOp.signer =
        malloc(sizeof(stellarxdr_Signer));
    if (!signer_to_xdr_object(
            &in->signer, out->stellarxdr_OperationBody_u.setOptionsOp.signer)) {
      return false;
    }
  } else {
    out->stellarxdr_OperationBody_u.setOptionsOp.signer = NULL;
  }
  return true;
}

bool set_options_from_xdr_object(const stellarxdr_OperationBody *in,
                                 struct SetOptionsOp *out) {
  if (in->stellarxdr_OperationBody_u.setOptionsOp.inflationDest) {
    out->inflationDestPresent = true;
    if (!encode_ed25519_public_key(
            &in->stellarxdr_OperationBody_u.setOptionsOp.inflationDest
                 ->stellarxdr_PublicKey_u.ed25519,
            out->inflationDest)) {
      return false;
    }
  } else {
    out->inflationDestPresent = false;
  }
  if (in->stellarxdr_OperationBody_u.setOptionsOp.clearFlags) {
    out->clearFlagsPresent = true;
    out->clearFlags = *in->stellarxdr_OperationBody_u.setOptionsOp.clearFlags;
  } else {
    out->clearFlagsPresent = false;
  }
  if (in->stellarxdr_OperationBody_u.setOptionsOp.setFlags) {
    out->setFlagsPresent = true;
    out->setFlags = *in->stellarxdr_OperationBody_u.setOptionsOp.setFlags;
  } else {
    out->setFlagsPresent = false;
  }
  if (in->stellarxdr_OperationBody_u.setOptionsOp.masterWeight) {
    out->masterWeightPresent = true;
    out->masterWeight =
        *in->stellarxdr_OperationBody_u.setOptionsOp.masterWeight;
  } else {
    out->masterWeightPresent = false;
  }
  if (in->stellarxdr_OperationBody_u.setOptionsOp.lowThreshold) {
    out->lowThresholdPresent = true;
    out->lowThreshold =
        *in->stellarxdr_OperationBody_u.setOptionsOp.lowThreshold;
  } else {
    out->lowThresholdPresent = false;
  }
  if (in->stellarxdr_OperationBody_u.setOptionsOp.medThreshold) {
    out->medThresholdPresent = true;
    out->medThreshold =
        *in->stellarxdr_OperationBody_u.setOptionsOp.medThreshold;
  } else {
    out->medThresholdPresent = false;
  }
  if (in->stellarxdr_OperationBody_u.setOptionsOp.highThreshold) {
    out->highThresholdPresent = true;
    out->highThreshold =
        *in->stellarxdr_OperationBody_u.setOptionsOp.highThreshold;
  } else {
    out->highThresholdPresent = false;
  }
  if (in->stellarxdr_OperationBody_u.setOptionsOp.homeDomain) {
    if (strlen(*in->stellarxdr_OperationBody_u.setOptionsOp.homeDomain)) {
      out->homeDomainPresent = true;
      strcpy(out->homeDomain,
             *in->stellarxdr_OperationBody_u.setOptionsOp.homeDomain);
    } else {
      out->homeDomainPresent = false;
    }
  } else {
    out->homeDomainPresent = false;
  }
  if (in->stellarxdr_OperationBody_u.setOptionsOp.signer) {
    out->signerPresent = true;
    if (!signer_from_xdr_object(
            in->stellarxdr_OperationBody_u.setOptionsOp.signer, &out->signer)) {
      return false;
    }
  } else {
    out->signerPresent = false;
  }
  return true;
}

// 6. Allow Trust
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

// 7. Change Trust
bool change_trust_to_xdr_object(const struct ChangeTrustOp *in,
                                stellarxdr_OperationBody *out) {
  out->type = stellarxdr_CHANGE_TRUST;
  out->stellarxdr_OperationBody_u.changeTrustOp.limit = in->limit;
  switch (in->assetType) {
  case CHANGE_TRUST_ASSET_TYPE_ASSET:
    if (!asset_to_change_trust_asset_xdr_object(
            &in->line.asset,
            &out->stellarxdr_OperationBody_u.changeTrustOp.line)) {
      return false;
    }
    break;
  case CHANGE_TRUST_ASSET_TYPE_LIQUIDITY_POOL_ASSET:
    if (!liquidity_pool_asset_to_change_trust_asset_xdr_object(
            &in->line.liquidityPoolAsset,
            &out->stellarxdr_OperationBody_u.changeTrustOp.line)) {
      return false;
    }
    break;
  }
  return true;
}

bool change_trust_from_xdr_object(const stellarxdr_OperationBody *in,
                                  struct ChangeTrustOp *out) {
  out->limit = in->stellarxdr_OperationBody_u.changeTrustOp.limit;
  switch (in->stellarxdr_OperationBody_u.changeTrustOp.line.type) {
  case stellarxdr_ASSET_TYPE_NATIVE:
  case stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4:
  case stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12:
    if (!asset_from_change_trust_asset_xdr_object(
            &in->stellarxdr_OperationBody_u.changeTrustOp.line,
            &out->line.asset)) {
      return false;
    }
    out->assetType = CHANGE_TRUST_ASSET_TYPE_ASSET;
    break;
  case stellarxdr_ASSET_TYPE_POOL_SHARE:
    if (!liquidity_pool_asset_from_change_trust_asset_xdr_object(
            &in->stellarxdr_OperationBody_u.changeTrustOp.line,
            &out->line.liquidityPoolAsset)) {
      return false;
    }
    out->assetType = CHANGE_TRUST_ASSET_TYPE_LIQUIDITY_POOL_ASSET;
    break;
  default:
    return false;
  }
  return true;
}

// 8. Account Merge
bool account_merge_to_xdr_object(const struct AccountMergeOp *in,
                                 stellarxdr_OperationBody *out) {
  out->type = stellarxdr_ACCOUNT_MERGE;
  if (!muxed_account_to_xdr_object(
          &in->destination, &out->stellarxdr_OperationBody_u.destination)) {
    return false;
  }
  return true;
}

bool account_merge_from_xdr_object(const stellarxdr_OperationBody *in,
                                   struct AccountMergeOp *out) {
  if (!muxed_account_from_xdr_object(
          &in->stellarxdr_OperationBody_u.destination, &out->destination)) {
    return false;
  }
  return true;
}

// 9. Inflation
bool inflation_to_xdr_object(stellarxdr_OperationBody *out) {
  out->type = stellarxdr_INFLATION;
  return true;
}

// 10. Manage Data
bool manage_data_to_xdr_object(const struct ManageDataOp *in,
                               stellarxdr_OperationBody *out) {
  out->type = stellarxdr_MANAGE_DATA;
  unsigned long dataNameLength = strlen(in->dataName);
  out->stellarxdr_OperationBody_u.manageDataOp.dataName =
      malloc(dataNameLength);
  memcpy(out->stellarxdr_OperationBody_u.manageDataOp.dataName, in->dataName,
         dataNameLength);

  if (in->dataValueLength != 0) {
    stellarxdr_DataValue stellarxdrDataValue;
    stellarxdrDataValue.stellarxdr_DataValue_len = in->dataValueLength;
    stellarxdrDataValue.stellarxdr_DataValue_val = malloc(in->dataValueLength);
    memcpy(stellarxdrDataValue.stellarxdr_DataValue_val, in->dataValue,
           in->dataValueLength);
    out->stellarxdr_OperationBody_u.manageDataOp.dataValue =
        malloc(sizeof(stellarxdr_DataValue));
    memcpy(out->stellarxdr_OperationBody_u.manageDataOp.dataValue,
           &stellarxdrDataValue, sizeof(stellarxdr_DataValue));
  }
  return true;
}

bool manage_data_from_xdr_object(const stellarxdr_OperationBody *in,
                                 struct ManageDataOp *out) {
  memcpy(out->dataName, in->stellarxdr_OperationBody_u.manageDataOp.dataName,
         64);
  out->dataName[64] = '\0';
  if (in->stellarxdr_OperationBody_u.manageDataOp.dataValue == NULL) {
    out->dataValueLength = 0;
  } else {
    out->dataValueLength = in->stellarxdr_OperationBody_u.manageDataOp
                               .dataValue->stellarxdr_DataValue_len;
    memcpy(out->dataValue,
           in->stellarxdr_OperationBody_u.manageDataOp.dataValue
               ->stellarxdr_DataValue_val,
           out->dataValueLength);
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

// 15. Claim Claimable Balance
bool claim_claimable_balance_to_xdr_object(
    const struct ClaimClaimableBalanceOp *in, stellarxdr_OperationBody *out) {
  out->type = stellarxdr_CLAIM_CLAIMABLE_BALANCE;

  // 36
  if (strlen(in->balanceID) != 72) {
    return false;
  }

  unsigned char decodedId[36];
  for (size_t i = 0, j = 0; j < 36; i += 2, j++)
    decodedId[j] = (in->balanceID[i] % 32 + 9) % 25 * 16 +
                   (in->balanceID[i + 1] % 32 + 9) % 25;
  // TODO: support other type
  out->stellarxdr_OperationBody_u.claimClaimableBalanceOp.balanceID.type =
      stellarxdr_CLAIMABLE_BALANCE_ID_TYPE_V0;
  for (size_t i = 0; i < 32; i++) {
    out->stellarxdr_OperationBody_u.claimClaimableBalanceOp.balanceID
        .stellarxdr_ClaimableBalanceID_u.v0[i] = decodedId[i + 4];
  }
  return true;
}

bool claim_claimable_balance_from_xdr_object(
    const stellarxdr_OperationBody *in, struct ClaimClaimableBalanceOp *out) {
  unsigned char encodeId[36];
  encodeId[0] =
      in->stellarxdr_OperationBody_u.claimClaimableBalanceOp.balanceID.type >>
      24;
  encodeId[1] =
      in->stellarxdr_OperationBody_u.claimClaimableBalanceOp.balanceID.type >>
      16;
  encodeId[2] =
      in->stellarxdr_OperationBody_u.claimClaimableBalanceOp.balanceID.type >>
      8;
  encodeId[3] =
      in->stellarxdr_OperationBody_u.claimClaimableBalanceOp.balanceID.type;

  for (size_t i = 0; i < 32; i++) {
    encodeId[i + 4] = in->stellarxdr_OperationBody_u.claimClaimableBalanceOp
                          .balanceID.stellarxdr_ClaimableBalanceID_u.v0[i];
  }

  for (size_t i = 0; i < 36; i++) {
    sprintf(out->balanceID + (i * 2), "%.2x", encodeId[i]);
  }
  out->balanceID[72] = '\0';
  return true;
}

// 16. Begin Sponsoring Future Reserves
bool begin_sponsoring_future_reserves_to_xdr_object(
    const struct BeginSponsoringFutureReservesOp *in,
    stellarxdr_OperationBody *out) {
  out->type = stellarxdr_BEGIN_SPONSORING_FUTURE_RESERVES;
  struct Keypair keypair;
  keypair_from_address(&keypair, in->sponsoredID);
  stellarxdr_AccountID accountId;
  keypair_xdr_account_id(&keypair, &accountId);
  out->stellarxdr_OperationBody_u.beginSponsoringFutureReservesOp.sponsoredID =
      accountId;
  return true;
}

bool begin_sponsoring_future_reserves_from_xdr_object(
    const stellarxdr_OperationBody *in,
    struct BeginSponsoringFutureReservesOp *out) {
  if (!encode_ed25519_public_key(
          &in->stellarxdr_OperationBody_u.beginSponsoringFutureReservesOp
               .sponsoredID.stellarxdr_PublicKey_u.ed25519,
          out->sponsoredID)) {
    return false;
  }
  return true;
}

// 17. End Sponsoring Future Reserves
bool end_sponsoring_future_reserves_to_xdr_object(
    stellarxdr_OperationBody *out) {
  out->type = stellarxdr_END_SPONSORING_FUTURE_RESERVES;
  return true;
}

// 20. Clawback Claimable Balance
bool clawback_claimable_balance_to_xdr_object(
    const struct ClawbackClaimableBalanceOp *in,
    stellarxdr_OperationBody *out) {
  out->type = stellarxdr_CLAWBACK_CLAIMABLE_BALANCE;

  // 36
  if (strlen(in->balanceID) != 72) {
    return false;
  }

  unsigned char decodedId[36];
  for (size_t i = 0, j = 0; j < 36; i += 2, j++)
    decodedId[j] = (in->balanceID[i] % 32 + 9) % 25 * 16 +
                   (in->balanceID[i + 1] % 32 + 9) % 25;
  // TODO: support other type
  out->stellarxdr_OperationBody_u.clawbackClaimableBalanceOp.balanceID.type =
      stellarxdr_CLAIMABLE_BALANCE_ID_TYPE_V0;
  for (size_t i = 0; i < 32; i++) {
    out->stellarxdr_OperationBody_u.clawbackClaimableBalanceOp.balanceID
        .stellarxdr_ClaimableBalanceID_u.v0[i] = decodedId[i + 4];
  }
  return true;
}

bool clawback_claimable_balance_from_xdr_object(
    const stellarxdr_OperationBody *in,
    struct ClawbackClaimableBalanceOp *out) {
  unsigned char encodeId[36];
  encodeId[0] = in->stellarxdr_OperationBody_u.clawbackClaimableBalanceOp
                    .balanceID.type >>
                24;
  encodeId[1] = in->stellarxdr_OperationBody_u.clawbackClaimableBalanceOp
                    .balanceID.type >>
                16;
  encodeId[2] = in->stellarxdr_OperationBody_u.clawbackClaimableBalanceOp
                    .balanceID.type >>
                8;
  encodeId[3] =
      in->stellarxdr_OperationBody_u.clawbackClaimableBalanceOp.balanceID.type;

  for (size_t i = 0; i < 32; i++) {
    encodeId[i + 4] = in->stellarxdr_OperationBody_u.clawbackClaimableBalanceOp
                          .balanceID.stellarxdr_ClaimableBalanceID_u.v0[i];
  }

  for (size_t i = 0; i < 36; i++) {
    sprintf(out->balanceID + (i * 2), "%.2x", encodeId[i]);
  }
  out->balanceID[72] = '\0';
  return true;
}

// 21. Set Trust Line Flags
bool set_trust_line_flags_to_xdr_object(const struct SetTrustLineFlagsOp *in,
                                        stellarxdr_OperationBody *out) {
  out->type = stellarxdr_SET_TRUST_LINE_FLAGS;
  struct Keypair keypair;
  keypair_from_address(&keypair, in->trustor);
  stellarxdr_AccountID accountId;
  keypair_xdr_account_id(&keypair, &accountId);
  out->stellarxdr_OperationBody_u.setTrustLineFlagsOp.trustor = accountId;

  if (!asset_to_xdr_object(
          &in->asset,
          &out->stellarxdr_OperationBody_u.setTrustLineFlagsOp.asset)) {
    return false;
  }

  out->stellarxdr_OperationBody_u.setTrustLineFlagsOp.setFlags = in->setFlags;
  out->stellarxdr_OperationBody_u.setTrustLineFlagsOp.clearFlags =
      in->clearFlags;
  return true;
}

bool set_trust_line_flags_from_xdr_object(const stellarxdr_OperationBody *in,
                                          struct SetTrustLineFlagsOp *out) {
  if (!encode_ed25519_public_key(
          &in->stellarxdr_OperationBody_u.setTrustLineFlagsOp.trustor
               .stellarxdr_PublicKey_u.ed25519,
          out->trustor)) {
    return false;
  }

  if (!asset_from_xdr_object(
          &in->stellarxdr_OperationBody_u.setTrustLineFlagsOp.asset,
          &out->asset)) {
    return false;
  }

  out->setFlags = in->stellarxdr_OperationBody_u.setTrustLineFlagsOp.setFlags;
  out->clearFlags =
      in->stellarxdr_OperationBody_u.setTrustLineFlagsOp.clearFlags;
  return true;
}

// 22. Liquidity Pool Deposit
bool liquidity_pool_deposit_to_xdr_object(
    const struct LiquidityPoolDepositOp *in, stellarxdr_OperationBody *out) {
  out->type = stellarxdr_LIQUIDITY_POOL_DEPOSIT;
  out->stellarxdr_OperationBody_u.liquidityPoolDepositOp.maxAmountA =
      in->maxAmountA;
  out->stellarxdr_OperationBody_u.liquidityPoolDepositOp.maxAmountB =
      in->maxAmountB;
  if (!price_to_xdr_object(
          &in->maxPrice,
          &out->stellarxdr_OperationBody_u.liquidityPoolDepositOp.maxPrice)) {
    return false;
  }
  if (!price_to_xdr_object(
          &in->minPrice,
          &out->stellarxdr_OperationBody_u.liquidityPoolDepositOp.minPrice)) {
    return false;
  }
  for (size_t i = 0, j = 0; j < 32; i += 2, j++)
    out->stellarxdr_OperationBody_u.liquidityPoolDepositOp.liquidityPoolID[j] =
        (in->liquidityPoolID[i] % 32 + 9) % 25 * 16 +
        (in->liquidityPoolID[i + 1] % 32 + 9) % 25;
  return true;
}

bool liquidity_pool_deposit_from_xdr_object(
    const stellarxdr_OperationBody *in, struct LiquidityPoolDepositOp *out) {
  out->maxAmountA =
      in->stellarxdr_OperationBody_u.liquidityPoolDepositOp.maxAmountA;
  out->maxAmountB =
      in->stellarxdr_OperationBody_u.liquidityPoolDepositOp.maxAmountB;
  if (!price_from_xdr_object(
          &in->stellarxdr_OperationBody_u.liquidityPoolDepositOp.maxPrice,
          &out->maxPrice)) {
    return false;
  }
  if (!price_from_xdr_object(
          &in->stellarxdr_OperationBody_u.liquidityPoolDepositOp.minPrice,
          &out->minPrice)) {
    return false;
  }
  for (size_t i = 0; i < 32; i++) {
    sprintf(out->liquidityPoolID + (i * 2), "%.2x",
            (unsigned char)in->stellarxdr_OperationBody_u.liquidityPoolDepositOp
                .liquidityPoolID[i]);
  }
  out->liquidityPoolID[64] = '\0';
  return true;
}

// 23. Liquidity Pool Withdraw
bool liquidity_pool_withdraw_to_xdr_object(
    const struct LiquidityPoolWithdrawOp *in, stellarxdr_OperationBody *out) {
  out->type = stellarxdr_LIQUIDITY_POOL_WITHDRAW;
  out->stellarxdr_OperationBody_u.liquidityPoolWithdrawOp.amount = in->amount;
  out->stellarxdr_OperationBody_u.liquidityPoolWithdrawOp.minAmountA =
      in->minAmountA;
  out->stellarxdr_OperationBody_u.liquidityPoolWithdrawOp.minAmountB =
      in->minAmountB;
  for (size_t i = 0, j = 0; j < 32; i += 2, j++)
    out->stellarxdr_OperationBody_u.liquidityPoolWithdrawOp.liquidityPoolID[j] =
        (in->liquidityPoolID[i] % 32 + 9) % 25 * 16 +
        (in->liquidityPoolID[i + 1] % 32 + 9) % 25;
  return true;
}

bool liquidity_pool_withdraw_from_xdr_object(
    const stellarxdr_OperationBody *in, struct LiquidityPoolWithdrawOp *out) {
  out->amount = in->stellarxdr_OperationBody_u.liquidityPoolWithdrawOp.amount;
  out->minAmountA =
      in->stellarxdr_OperationBody_u.liquidityPoolWithdrawOp.minAmountA;
  out->minAmountB =
      in->stellarxdr_OperationBody_u.liquidityPoolWithdrawOp.minAmountB;
  for (size_t i = 0; i < 32; i++) {
    sprintf(out->liquidityPoolID + (i * 2), "%.2x",
            (unsigned char)in->stellarxdr_OperationBody_u
                .liquidityPoolWithdrawOp.liquidityPoolID[i]);
  }
  out->liquidityPoolID[64] = '\0';
  return true;
}

bool operation_to_xdr_object(const struct Operation *in,
                             stellarxdr_Operation *out) {
  stellarxdr_OperationBody operation_body;
  bool opSuccess;
  switch (in->type) {
  case CREATE_ACCOUNT:
    opSuccess =
        create_account_to_xdr_object(&in->createAccountOp, &operation_body);
    break;
  case PAYMENT:
    opSuccess = payment_to_xdr_object(&in->paymentOp, &operation_body);
    break;
  case PATH_PAYMENT_STRICT_RECEIVE:
    opSuccess = path_payment_strict_receive_to_xdr_object(
        &in->pathPaymentStrictReceiveOp, &operation_body);
    break;
  case MANAGE_SELL_OFFER:
    opSuccess = manage_sell_offer_to_xdr_object(&in->manageSellOfferOp,
                                                &operation_body);
    break;
  case CREATE_PASSIVE_SELL_OFFER:
    opSuccess = create_passive_sell_offer_to_xdr_object(
        &in->createPassiveSellOfferOp, &operation_body);
    break;
  case SET_OPTIONS:
    opSuccess = set_options_to_xdr_object(&in->setOptionsOp, &operation_body);
    break;
  case CHANGE_TRUST:
    opSuccess = change_trust_to_xdr_object(&in->changeTrustOp, &operation_body);
    break;
  case ALLOW_TRUST:
    opSuccess = allow_trust_to_xdr_object(&in->allowTrustOp, &operation_body);
    break;
  case ACCOUNT_MERGE:
    opSuccess =
        account_merge_to_xdr_object(&in->accountMergeOp, &operation_body);
    break;
  case INFLATION:
    opSuccess = inflation_to_xdr_object(&operation_body);
    break;
  case MANAGE_DATA:
    opSuccess = manage_data_to_xdr_object(&in->manageDataOp, &operation_body);
    break;
  case BUMP_SEQUENCE:
    opSuccess =
        bump_sequence_to_xdr_object(&in->bump_sequence_op, &operation_body);
    break;
  case MANAGE_BUY_OFFER:
    opSuccess =
        manage_buy_offer_to_xdr_object(&in->manageBuyOfferOp, &operation_body);
    break;
  case PATH_PAYMENT_STRICT_SEND:
    opSuccess = path_payment_strict_send_to_xdr_object(
        &in->pathPaymentStrictSendOp, &operation_body);
    break;
  case CREATE_CLAIMABLE_BALANCE:
    break;
  case CLAIM_CLAIMABLE_BALANCE:
    opSuccess = claim_claimable_balance_to_xdr_object(
        &in->claimClaimableBalanceOp, &operation_body);
    break;
  case BEGIN_SPONSORING_FUTURE_RESERVES:
    opSuccess = begin_sponsoring_future_reserves_to_xdr_object(
        &in->beginSponsoringFutureReservesOp, &operation_body);
    break;
  case END_SPONSORING_FUTURE_RESERVES:
    opSuccess = end_sponsoring_future_reserves_to_xdr_object(&operation_body);
    break;
  case REVOKE_SPONSORSHIP:
    break;
  case CLAWBACK:
    break;
  case CLAWBACK_CLAIMABLE_BALANCE:
    opSuccess = clawback_claimable_balance_to_xdr_object(
        &in->clawbackClaimableBalanceOp, &operation_body);
    break;
  case SET_TRUST_LINE_FLAGS:
    opSuccess = set_trust_line_flags_to_xdr_object(&in->setTrustLineFlagsOp,
                                                   &operation_body);
    break;
  case LIQUIDITY_POOL_DEPOSIT:
    opSuccess = liquidity_pool_deposit_to_xdr_object(
        &in->liquidityPoolDepositOp, &operation_body);
    break;
  case LIQUIDITY_POOL_WITHDRAW:
    opSuccess = liquidity_pool_withdraw_to_xdr_object(
        &in->liquidityPoolWithdrawOp, &operation_body);
    break;
  default:
    return false;
  }
  if (!opSuccess) {
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
  bool opSuccess;
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
    opSuccess =
        create_account_from_xdr_object(&in->body, &out->createAccountOp);
    break;
  case stellarxdr_PAYMENT:
    out->type = PAYMENT;
    opSuccess = payment_from_xdr_object(&in->body, &out->paymentOp);
    break;
  case stellarxdr_PATH_PAYMENT_STRICT_RECEIVE:
    out->type = PATH_PAYMENT_STRICT_RECEIVE;
    opSuccess = path_payment_strict_receive_from_xdr_object(
        &in->body, &out->pathPaymentStrictReceiveOp);
    break;
  case stellarxdr_MANAGE_SELL_OFFER:
    out->type = MANAGE_SELL_OFFER;
    opSuccess =
        manage_sell_offer_from_xdr_object(&in->body, &out->manageSellOfferOp);
    break;
  case stellarxdr_CREATE_PASSIVE_SELL_OFFER:
    out->type = CREATE_PASSIVE_SELL_OFFER;
    opSuccess = create_passive_sell_offer_from_xdr_object(
        &in->body, &out->createPassiveSellOfferOp);
    break;
  case stellarxdr_SET_OPTIONS:
    out->type = SET_OPTIONS;
    opSuccess = set_options_from_xdr_object(&in->body, &out->setOptionsOp);
    break;
  case stellarxdr_CHANGE_TRUST:
    out->type = CHANGE_TRUST;
    opSuccess = change_trust_from_xdr_object(&in->body, &out->changeTrustOp);
    break;
  case stellarxdr_ALLOW_TRUST:
    out->type = ALLOW_TRUST;
    opSuccess = allow_trust_from_xdr_object(&in->body, &out->allowTrustOp);
    break;
  case stellarxdr_ACCOUNT_MERGE:
    out->type = ACCOUNT_MERGE;
    opSuccess = account_merge_from_xdr_object(&in->body, &out->accountMergeOp);
    break;
  case stellarxdr_INFLATION:
    opSuccess = true;
    out->type = INFLATION;
    break;
  case stellarxdr_MANAGE_DATA:
    out->type = MANAGE_DATA;
    opSuccess = manage_data_from_xdr_object(&in->body, &out->manageDataOp);
    break;
  case stellarxdr_BUMP_SEQUENCE:
    out->type = BUMP_SEQUENCE;
    opSuccess =
        bump_sequence_from_xdr_object(&in->body, &out->bump_sequence_op);
    break;
  case stellarxdr_MANAGE_BUY_OFFER:
    out->type = MANAGE_BUY_OFFER;
    opSuccess =
        manage_buy_offer_from_xdr_object(&in->body, &out->manageBuyOfferOp);
    break;
  case stellarxdr_PATH_PAYMENT_STRICT_SEND:
    out->type = PATH_PAYMENT_STRICT_SEND;
    opSuccess = path_payment_strict_send_from_xdr_object(
        &in->body, &out->pathPaymentStrictSendOp);
    break;
  case stellarxdr_CREATE_CLAIMABLE_BALANCE:
    break;
  case stellarxdr_CLAIM_CLAIMABLE_BALANCE:
    out->type = CLAIM_CLAIMABLE_BALANCE;
    opSuccess = claim_claimable_balance_from_xdr_object(
        &in->body, &out->claimClaimableBalanceOp);
    break;
  case stellarxdr_BEGIN_SPONSORING_FUTURE_RESERVES:
    out->type = BEGIN_SPONSORING_FUTURE_RESERVES;
    opSuccess = begin_sponsoring_future_reserves_from_xdr_object(
        &in->body, &out->beginSponsoringFutureReservesOp);
    break;
  case stellarxdr_END_SPONSORING_FUTURE_RESERVES:
    out->type = END_SPONSORING_FUTURE_RESERVES;
    opSuccess = true;
    break;
  case stellarxdr_REVOKE_SPONSORSHIP:
    break;
  case stellarxdr_CLAWBACK:
    break;
  case stellarxdr_CLAWBACK_CLAIMABLE_BALANCE:
    out->type = CLAWBACK_CLAIMABLE_BALANCE;
    opSuccess = clawback_claimable_balance_from_xdr_object(
        &in->body, &out->clawbackClaimableBalanceOp);
    break;
  case stellarxdr_SET_TRUST_LINE_FLAGS:
    out->type = SET_TRUST_LINE_FLAGS;
    opSuccess = set_trust_line_flags_from_xdr_object(&in->body,
                                                     &out->setTrustLineFlagsOp);
    break;
  case stellarxdr_LIQUIDITY_POOL_DEPOSIT:
    out->type = LIQUIDITY_POOL_DEPOSIT;
    opSuccess = liquidity_pool_deposit_from_xdr_object(
        &in->body, &out->liquidityPoolDepositOp);
    break;
  case stellarxdr_LIQUIDITY_POOL_WITHDRAW:
    out->type = LIQUIDITY_POOL_WITHDRAW;
    opSuccess = liquidity_pool_withdraw_from_xdr_object(
        &in->body, &out->liquidityPoolWithdrawOp);
    break;
  default:
    return false;
  }
  if (!opSuccess) {
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