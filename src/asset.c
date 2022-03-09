#include "asset.h"

bool asset_to_xdr_object(const struct Asset *in, stellarxdr_Asset *out) {
  if (in->type == ASSET_TYPE_NATIVE) {
    out->type = stellarxdr_ASSET_TYPE_NATIVE;
    return true;
  }

  struct Keypair keypair;
  keypair_from_address(&keypair, in->issuer);
  stellarxdr_AccountID accountId;
  keypair_xdr_account_id(&keypair, &accountId);

  switch (in->type) {
  case ASSET_TYPE_CREDIT_ALPHANUM4:
    out->type = stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4;
    memset(out->stellarxdr_Asset_u.alphaNum4.assetCode, 0, 4);
    memcpy(out->stellarxdr_Asset_u.alphaNum4.assetCode, in->code,
           strlen(in->code));
    memcpy(&out->stellarxdr_Asset_u.alphaNum4.issuer, &accountId,
           sizeof(stellarxdr_AccountID));
    break;
  case ASSET_TYPE_CREDIT_ALPHANUM12:
    out->type = stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12;
    memset(out->stellarxdr_Asset_u.alphaNum12.assetCode, 0, 12);
    memcpy(out->stellarxdr_Asset_u.alphaNum12.assetCode, in->code,
           strlen(in->code));
    memcpy(&out->stellarxdr_Asset_u.alphaNum12.issuer, &accountId,
           sizeof(stellarxdr_AccountID));
    break;
  default:
    return false;
  }
  return true;
};

bool asset_from_xdr_object(const stellarxdr_Asset *in, struct Asset *out) {
  if (in->type == stellarxdr_ASSET_TYPE_NATIVE) {
    out->type = ASSET_TYPE_NATIVE;
    return true;
  }
  out->issuer = malloc(ED25519_PUBLIC_KEY_LENGTH + 1);
  switch (in->type) {
  case stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4:
    out->type = ASSET_TYPE_CREDIT_ALPHANUM4;
    if (!encode_ed25519_public_key(&in->stellarxdr_Asset_u.alphaNum4.issuer
                                        .stellarxdr_PublicKey_u.ed25519,
                                   out->issuer)) {
      return false;
    }
    out->code = malloc(strlen(in->stellarxdr_Asset_u.alphaNum4.assetCode) + 1);
    memcpy(out->code, in->stellarxdr_Asset_u.alphaNum4.assetCode,
           strlen(in->stellarxdr_Asset_u.alphaNum4.assetCode));

    break;
  case stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12:
    out->type = ASSET_TYPE_CREDIT_ALPHANUM12;
    if (!encode_ed25519_public_key(&in->stellarxdr_Asset_u.alphaNum12.issuer
                                        .stellarxdr_PublicKey_u.ed25519,
                                   out->issuer)) {
      return false;
    }
    out->code = malloc(strlen(in->stellarxdr_Asset_u.alphaNum12.assetCode) + 1);
    memcpy(out->code, in->stellarxdr_Asset_u.alphaNum12.assetCode,
           strlen(in->stellarxdr_Asset_u.alphaNum12.assetCode));
    break;
  default:
    return false;
  }
  return true;
};