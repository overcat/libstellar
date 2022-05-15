#include "signer_key.h"

bool signer_key_to_xdr_object(const struct SignerKey *in,
                              stellarxdr_SignerKey *out) {
  switch (in->signerKeyType) {
  case SIGNER_KEY_TYPE_ED25519:
    out->type = stellarxdr_SIGNER_KEY_TYPE_ED25519;
    memcpy(out->stellarxdr_SignerKey_u.ed25519, in->signerKey.ed25519, 32);
    break;
  case SIGNER_KEY_TYPE_PRE_AUTH_TX:
    out->type = stellarxdr_SIGNER_KEY_TYPE_PRE_AUTH_TX;
    memcpy(out->stellarxdr_SignerKey_u.preAuthTx, in->signerKey.preAuthTx, 32);
    break;
  case SIGNER_KEY_TYPE_HASH_X:
    out->type = stellarxdr_SIGNER_KEY_TYPE_HASH_X;
    memcpy(out->stellarxdr_SignerKey_u.hashX, in->signerKey.hashX, 32);
    break;
  default:
    return false;
  }
  return true;
};

bool signer_key_from_xdr_object(const stellarxdr_SignerKey *in,
                                struct SignerKey *out) {
  switch (in->type) {
  case stellarxdr_SIGNER_KEY_TYPE_ED25519:
    out->signerKeyType = SIGNER_KEY_TYPE_ED25519;
    memcpy(out->signerKey.ed25519, in->stellarxdr_SignerKey_u.ed25519, 32);
    break;
  case stellarxdr_SIGNER_KEY_TYPE_PRE_AUTH_TX:
    out->signerKeyType = SIGNER_KEY_TYPE_PRE_AUTH_TX;

    memcpy(out->signerKey.preAuthTx, in->stellarxdr_SignerKey_u.preAuthTx, 32);
    break;
  case stellarxdr_SIGNER_KEY_TYPE_HASH_X:
    out->signerKeyType = SIGNER_KEY_TYPE_HASH_X;
    memcpy(out->signerKey.hashX, in->stellarxdr_SignerKey_u.hashX, 32);
    break;
  default:
    return false;
  }
  return true;
};
