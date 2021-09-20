#include "stellarxdr.h"

bool_t xdr_stellarxdr_Hash(XDR *xdrs, stellarxdr_Hash objp) {
  if (!xdr_opaque(xdrs, objp, 32))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_uint256(XDR *xdrs, stellarxdr_uint256 objp) {
  if (!xdr_opaque(xdrs, objp, 32))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_uint32(XDR *xdrs, stellarxdr_uint32 *objp) {
  if (!xdr_u_int(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_int32(XDR *xdrs, stellarxdr_int32 *objp) {
  if (!xdr_int(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_uint64(XDR *xdrs, stellarxdr_uint64 *objp) {
  if (!xdr_u_int64_t(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_int64(XDR *xdrs, stellarxdr_int64 *objp) {
  if (!xdr_int64_t(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_CryptoKeyType(XDR *xdrs, stellarxdr_CryptoKeyType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_PublicKeyType(XDR *xdrs, stellarxdr_PublicKeyType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SignerKeyType(XDR *xdrs, stellarxdr_SignerKeyType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_PublicKey(XDR *xdrs, stellarxdr_PublicKey *objp) {
  if (!xdr_stellarxdr_PublicKeyType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_PUBLIC_KEY_TYPE_ED25519:
    if (!xdr_stellarxdr_uint256(xdrs, objp->stellarxdr_PublicKey_u.ed25519))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_SignerKey(XDR *xdrs, stellarxdr_SignerKey *objp) {
  if (!xdr_stellarxdr_SignerKeyType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_SIGNER_KEY_TYPE_ED25519:
    if (!xdr_stellarxdr_uint256(xdrs, objp->stellarxdr_SignerKey_u.ed25519))
      return (FALSE);
    break;
  case stellarxdr_SIGNER_KEY_TYPE_PRE_AUTH_TX:
    if (!xdr_stellarxdr_uint256(xdrs, objp->stellarxdr_SignerKey_u.preAuthTx))
      return (FALSE);
    break;
  case stellarxdr_SIGNER_KEY_TYPE_HASH_X:
    if (!xdr_stellarxdr_uint256(xdrs, objp->stellarxdr_SignerKey_u.hashX))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_Signature(XDR *xdrs, stellarxdr_Signature *objp) {
  if (!xdr_bytes(xdrs, (char **)&objp->stellarxdr_Signature_val,
                 (u_int *)&objp->stellarxdr_Signature_len, 64))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SignatureHint(XDR *xdrs, stellarxdr_SignatureHint objp) {
  if (!xdr_opaque(xdrs, objp, 4))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_NodeID(XDR *xdrs, stellarxdr_NodeID *objp) {
  if (!xdr_stellarxdr_PublicKey(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_Curve25519Secret(XDR *xdrs,
                                       stellarxdr_Curve25519Secret *objp) {
  if (!xdr_opaque(xdrs, objp->key, 32))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_Curve25519Public(XDR *xdrs,
                                       stellarxdr_Curve25519Public *objp) {
  if (!xdr_opaque(xdrs, objp->key, 32))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_HmacSha256Key(XDR *xdrs, stellarxdr_HmacSha256Key *objp) {
  if (!xdr_opaque(xdrs, objp->key, 32))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_HmacSha256Mac(XDR *xdrs, stellarxdr_HmacSha256Mac *objp) {
  if (!xdr_opaque(xdrs, objp->mac, 32))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_Value(XDR *xdrs, stellarxdr_Value *objp) {
  if (!xdr_bytes(xdrs, (char **)&objp->stellarxdr_Value_val,
                 (u_int *)&objp->stellarxdr_Value_len, ~0))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SCPBallot(XDR *xdrs, stellarxdr_SCPBallot *objp) {
  if (!xdr_stellarxdr_uint32(xdrs, &objp->counter))
    return (FALSE);
  if (!xdr_stellarxdr_Value(xdrs, &objp->value))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SCPStatementType(XDR *xdrs,
                                       stellarxdr_SCPStatementType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SCPNomination(XDR *xdrs, stellarxdr_SCPNomination *objp) {
  if (!xdr_stellarxdr_Hash(xdrs, objp->quorumSetHash))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->votes.votes_val,
                 (u_int *)&objp->votes.votes_len, ~0, sizeof(stellarxdr_Value),
                 (xdrproc_t)xdr_stellarxdr_Value))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->accepted.accepted_val,
                 (u_int *)&objp->accepted.accepted_len, ~0,
                 sizeof(stellarxdr_Value), (xdrproc_t)xdr_stellarxdr_Value))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SCPPrepare(XDR *xdrs, stellarxdr_SCPPrepare *objp) {
  if (!xdr_stellarxdr_Hash(xdrs, objp->quorumSetHash))
    return (FALSE);
  if (!xdr_stellarxdr_SCPBallot(xdrs, &objp->ballot))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->prepared, sizeof(stellarxdr_SCPBallot),
                   (xdrproc_t)xdr_stellarxdr_SCPBallot))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->preparedPrime,
                   sizeof(stellarxdr_SCPBallot),
                   (xdrproc_t)xdr_stellarxdr_SCPBallot))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->nC))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->nH))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SCPConfirm(XDR *xdrs, stellarxdr_SCPConfirm *objp) {
  if (!xdr_stellarxdr_SCPBallot(xdrs, &objp->ballot))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->nPrepared))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->nCommit))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->nH))
    return (FALSE);
  if (!xdr_stellarxdr_Hash(xdrs, objp->quorumSetHash))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SCPExternalize(XDR *xdrs,
                                     stellarxdr_SCPExternalize *objp) {
  if (!xdr_stellarxdr_SCPBallot(xdrs, &objp->commit))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->nH))
    return (FALSE);
  if (!xdr_stellarxdr_Hash(xdrs, objp->commitQuorumSetHash))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_SCPStatementPledges(XDR *xdrs,
                                   stellarxdr_SCPStatementPledges *objp) {
  if (!xdr_stellarxdr_SCPStatementType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_SCP_ST_PREPARE:
    if (!xdr_stellarxdr_SCPPrepare(
            xdrs, &objp->stellarxdr_SCPStatementPledges_u.prepare))
      return (FALSE);
    break;
  case stellarxdr_SCP_ST_CONFIRM:
    if (!xdr_stellarxdr_SCPConfirm(
            xdrs, &objp->stellarxdr_SCPStatementPledges_u.confirm))
      return (FALSE);
    break;
  case stellarxdr_SCP_ST_EXTERNALIZE:
    if (!xdr_stellarxdr_SCPExternalize(
            xdrs, &objp->stellarxdr_SCPStatementPledges_u.externalize))
      return (FALSE);
    break;
  case stellarxdr_SCP_ST_NOMINATE:
    if (!xdr_stellarxdr_SCPNomination(
            xdrs, &objp->stellarxdr_SCPStatementPledges_u.nominate))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_SCPStatement(XDR *xdrs, stellarxdr_SCPStatement *objp) {
  if (!xdr_stellarxdr_NodeID(xdrs, &objp->nodeID))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->slotIndex))
    return (FALSE);
  if (!xdr_stellarxdr_SCPStatementPledges(xdrs, &objp->pledges))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SCPEnvelope(XDR *xdrs, stellarxdr_SCPEnvelope *objp) {
  if (!xdr_stellarxdr_SCPStatement(xdrs, &objp->statement))
    return (FALSE);
  if (!xdr_stellarxdr_Signature(xdrs, &objp->signature))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SCPQuorumSet(XDR *xdrs, stellarxdr_SCPQuorumSet *objp) {
  if (!xdr_stellarxdr_uint32(xdrs, &objp->threshold))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->validators.validators_val,
                 (u_int *)&objp->validators.validators_len, ~0,
                 sizeof(stellarxdr_NodeID), (xdrproc_t)xdr_stellarxdr_NodeID))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->innerSets.innerSets_val,
                 (u_int *)&objp->innerSets.innerSets_len, ~0,
                 sizeof(stellarxdr_SCPQuorumSet),
                 (xdrproc_t)xdr_stellarxdr_SCPQuorumSet))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_AccountID(XDR *xdrs, stellarxdr_AccountID *objp) {
  if (!xdr_stellarxdr_PublicKey(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_Thresholds(XDR *xdrs, stellarxdr_Thresholds objp) {
  if (!xdr_opaque(xdrs, objp, 4))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_string32(XDR *xdrs, stellarxdr_string32 *objp) {
  if (!xdr_string(xdrs, objp, 32))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_string64(XDR *xdrs, stellarxdr_string64 *objp) {
  if (!xdr_string(xdrs, objp, 64))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SequenceNumber(XDR *xdrs,
                                     stellarxdr_SequenceNumber *objp) {
  if (!xdr_stellarxdr_int64(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_TimePoint(XDR *xdrs, stellarxdr_TimePoint *objp) {
  if (!xdr_stellarxdr_uint64(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_DataValue(XDR *xdrs, stellarxdr_DataValue *objp) {
  if (!xdr_bytes(xdrs, (char **)&objp->stellarxdr_DataValue_val,
                 (u_int *)&objp->stellarxdr_DataValue_len, 64))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_PoolID(XDR *xdrs, stellarxdr_PoolID objp) {
  if (!xdr_stellarxdr_Hash(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_AssetCode4(XDR *xdrs, stellarxdr_AssetCode4 objp) {
  if (!xdr_opaque(xdrs, objp, 4))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_AssetCode12(XDR *xdrs, stellarxdr_AssetCode12 objp) {
  if (!xdr_opaque(xdrs, objp, 12))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_AssetType(XDR *xdrs, stellarxdr_AssetType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_AssetCode(XDR *xdrs, stellarxdr_AssetCode *objp) {
  if (!xdr_stellarxdr_AssetType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4:
    if (!xdr_stellarxdr_AssetCode4(xdrs,
                                   objp->stellarxdr_AssetCode_u.assetCode4))
      return (FALSE);
    break;
  case stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12:
    if (!xdr_stellarxdr_AssetCode12(xdrs,
                                    objp->stellarxdr_AssetCode_u.assetCode12))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_AlphaNum4(XDR *xdrs, stellarxdr_AlphaNum4 *objp) {
  if (!xdr_stellarxdr_AssetCode4(xdrs, objp->assetCode))
    return (FALSE);
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->issuer))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_AlphaNum12(XDR *xdrs, stellarxdr_AlphaNum12 *objp) {
  if (!xdr_stellarxdr_AssetCode12(xdrs, objp->assetCode))
    return (FALSE);
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->issuer))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_Asset(XDR *xdrs, stellarxdr_Asset *objp) {
  if (!xdr_stellarxdr_AssetType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_ASSET_TYPE_NATIVE:
    break;
  case stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4:
    if (!xdr_stellarxdr_AlphaNum4(xdrs, &objp->stellarxdr_Asset_u.alphaNum4))
      return (FALSE);
    break;
  case stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12:
    if (!xdr_stellarxdr_AlphaNum12(xdrs, &objp->stellarxdr_Asset_u.alphaNum12))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_Price(XDR *xdrs, stellarxdr_Price *objp) {
  if (!xdr_stellarxdr_int32(xdrs, &objp->n))
    return (FALSE);
  if (!xdr_stellarxdr_int32(xdrs, &objp->d))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_Liabilities(XDR *xdrs, stellarxdr_Liabilities *objp) {
  if (!xdr_stellarxdr_int64(xdrs, &objp->buying))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->selling))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ThresholdIndexes(XDR *xdrs,
                                       stellarxdr_ThresholdIndexes *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerEntryType(XDR *xdrs,
                                      stellarxdr_LedgerEntryType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_Signer(XDR *xdrs, stellarxdr_Signer *objp) {
  if (!xdr_stellarxdr_SignerKey(xdrs, &objp->key))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->weight))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_AccountFlags(XDR *xdrs, stellarxdr_AccountFlags *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_SponsorshipDescriptor(XDR *xdrs,
                                     stellarxdr_SponsorshipDescriptor *objp) {
  if (!xdr_pointer(xdrs, (char **)objp, sizeof(stellarxdr_AccountID),
                   (xdrproc_t)xdr_stellarxdr_AccountID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_AccountEntryExtensionV2Ext(
    XDR *xdrs, stellarxdr_AccountEntryExtensionV2Ext *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_AccountEntryExtensionV2(
    XDR *xdrs, stellarxdr_AccountEntryExtensionV2 *objp) {
  if (!xdr_stellarxdr_uint32(xdrs, &objp->numSponsored))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->numSponsoring))
    return (FALSE);
  if (!xdr_array(
          xdrs, (char **)&objp->signerSponsoringIDs.signerSponsoringIDs_val,
          (u_int *)&objp->signerSponsoringIDs.signerSponsoringIDs_len,
          stellarxdr_MAX_SIGNERS, sizeof(stellarxdr_SponsorshipDescriptor),
          (xdrproc_t)xdr_stellarxdr_SponsorshipDescriptor))
    return (FALSE);
  if (!xdr_stellarxdr_AccountEntryExtensionV2Ext(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_AccountEntryExtensionV1Ext(
    XDR *xdrs, stellarxdr_AccountEntryExtensionV1Ext *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  case 2:
    if (!xdr_stellarxdr_AccountEntryExtensionV2(
            xdrs, &objp->stellarxdr_AccountEntryExtensionV1Ext_u.v2))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_AccountEntryExtensionV1(
    XDR *xdrs, stellarxdr_AccountEntryExtensionV1 *objp) {
  if (!xdr_stellarxdr_Liabilities(xdrs, &objp->liabilities))
    return (FALSE);
  if (!xdr_stellarxdr_AccountEntryExtensionV1Ext(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_AccountEntryExt(XDR *xdrs,
                                      stellarxdr_AccountEntryExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  case 1:
    if (!xdr_stellarxdr_AccountEntryExtensionV1(
            xdrs, &objp->stellarxdr_AccountEntryExt_u.v1))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_AccountEntry(XDR *xdrs, stellarxdr_AccountEntry *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->accountID))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->balance))
    return (FALSE);
  if (!xdr_stellarxdr_SequenceNumber(xdrs, &objp->seqNum))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->numSubEntries))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->inflationDest,
                   sizeof(stellarxdr_AccountID),
                   (xdrproc_t)xdr_stellarxdr_AccountID))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->flags))
    return (FALSE);
  if (!xdr_stellarxdr_string32(xdrs, &objp->homeDomain))
    return (FALSE);
  if (!xdr_stellarxdr_Thresholds(xdrs, objp->thresholds))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->signers.signers_val,
                 (u_int *)&objp->signers.signers_len, stellarxdr_MAX_SIGNERS,
                 sizeof(stellarxdr_Signer), (xdrproc_t)xdr_stellarxdr_Signer))
    return (FALSE);
  if (!xdr_stellarxdr_AccountEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_TrustLineFlags(XDR *xdrs,
                                     stellarxdr_TrustLineFlags *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LiquidityPoolType(XDR *xdrs,
                                        stellarxdr_LiquidityPoolType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_TrustLineAsset(XDR *xdrs,
                                     stellarxdr_TrustLineAsset *objp) {
  if (!xdr_stellarxdr_AssetType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_ASSET_TYPE_NATIVE:
    break;
  case stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4:
    if (!xdr_stellarxdr_AlphaNum4(xdrs,
                                  &objp->stellarxdr_TrustLineAsset_u.alphaNum4))
      return (FALSE);
    break;
  case stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12:
    if (!xdr_stellarxdr_AlphaNum12(
            xdrs, &objp->stellarxdr_TrustLineAsset_u.alphaNum12))
      return (FALSE);
    break;
  case stellarxdr_ASSET_TYPE_POOL_SHARE:
    if (!xdr_stellarxdr_PoolID(
            xdrs, objp->stellarxdr_TrustLineAsset_u.liquidityPoolID))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_TrustLineEntryExtensionV2Ext(
    XDR *xdrs, stellarxdr_TrustLineEntryExtensionV2Ext *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_TrustLineEntryExtensionV2(
    XDR *xdrs, stellarxdr_TrustLineEntryExtensionV2 *objp) {
  if (!xdr_stellarxdr_int32(xdrs, &objp->liquidityPoolUseCount))
    return (FALSE);
  if (!xdr_stellarxdr_TrustLineEntryExtensionV2Ext(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_TrustLineEntryV1Ext(XDR *xdrs,
                                   stellarxdr_TrustLineEntryV1Ext *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  case 2:
    if (!xdr_stellarxdr_TrustLineEntryExtensionV2(
            xdrs, &objp->stellarxdr_TrustLineEntryV1Ext_u.v2))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_TrustLineEntryV1(XDR *xdrs,
                                       stellarxdr_TrustLineEntryV1 *objp) {
  if (!xdr_stellarxdr_Liabilities(xdrs, &objp->liabilities))
    return (FALSE);
  if (!xdr_stellarxdr_TrustLineEntryV1Ext(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_TrustLineEntryExt(XDR *xdrs,
                                        stellarxdr_TrustLineEntryExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  case 1:
    if (!xdr_stellarxdr_TrustLineEntryV1(
            xdrs, &objp->stellarxdr_TrustLineEntryExt_u.v1))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_TrustLineEntry(XDR *xdrs,
                                     stellarxdr_TrustLineEntry *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->accountID))
    return (FALSE);
  if (!xdr_stellarxdr_TrustLineAsset(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->balance))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->limit))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->flags))
    return (FALSE);
  if (!xdr_stellarxdr_TrustLineEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_OfferEntryFlags(XDR *xdrs,
                                      stellarxdr_OfferEntryFlags *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_OfferEntryExt(XDR *xdrs, stellarxdr_OfferEntryExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_OfferEntry(XDR *xdrs, stellarxdr_OfferEntry *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->sellerID))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->offerID))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->selling))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->buying))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amount))
    return (FALSE);
  if (!xdr_stellarxdr_Price(xdrs, &objp->price))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->flags))
    return (FALSE);
  if (!xdr_stellarxdr_OfferEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_DataEntryExt(XDR *xdrs, stellarxdr_DataEntryExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_DataEntry(XDR *xdrs, stellarxdr_DataEntry *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->accountID))
    return (FALSE);
  if (!xdr_stellarxdr_string64(xdrs, &objp->dataName))
    return (FALSE);
  if (!xdr_stellarxdr_DataValue(xdrs, &objp->dataValue))
    return (FALSE);
  if (!xdr_stellarxdr_DataEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimPredicateType(XDR *xdrs,
                                         stellarxdr_ClaimPredicateType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimPredicate(XDR *xdrs,
                                     stellarxdr_ClaimPredicate *objp) {
  if (!xdr_stellarxdr_ClaimPredicateType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_CLAIM_PREDICATE_UNCONDITIONAL:
    break;
  case stellarxdr_CLAIM_PREDICATE_AND:
    if (!xdr_array(xdrs,
                   (char **)&objp->stellarxdr_ClaimPredicate_u.andPredicates
                       .andPredicates_val,
                   (u_int *)&objp->stellarxdr_ClaimPredicate_u.andPredicates
                       .andPredicates_len,
                   2, sizeof(stellarxdr_ClaimPredicate),
                   (xdrproc_t)xdr_stellarxdr_ClaimPredicate))
      return (FALSE);
    break;
  case stellarxdr_CLAIM_PREDICATE_OR:
    if (!xdr_array(xdrs,
                   (char **)&objp->stellarxdr_ClaimPredicate_u.orPredicates
                       .orPredicates_val,
                   (u_int *)&objp->stellarxdr_ClaimPredicate_u.orPredicates
                       .orPredicates_len,
                   2, sizeof(stellarxdr_ClaimPredicate),
                   (xdrproc_t)xdr_stellarxdr_ClaimPredicate))
      return (FALSE);
    break;
  case stellarxdr_CLAIM_PREDICATE_NOT:
    if (!xdr_pointer(xdrs,
                     (char **)&objp->stellarxdr_ClaimPredicate_u.notPredicate,
                     sizeof(stellarxdr_ClaimPredicate),
                     (xdrproc_t)xdr_stellarxdr_ClaimPredicate))
      return (FALSE);
    break;
  case stellarxdr_CLAIM_PREDICATE_BEFORE_ABSOLUTE_TIME:
    if (!xdr_stellarxdr_int64(xdrs,
                              &objp->stellarxdr_ClaimPredicate_u.absBefore))
      return (FALSE);
    break;
  case stellarxdr_CLAIM_PREDICATE_BEFORE_RELATIVE_TIME:
    if (!xdr_stellarxdr_int64(xdrs,
                              &objp->stellarxdr_ClaimPredicate_u.relBefore))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimantType(XDR *xdrs, stellarxdr_ClaimantType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimantV0(XDR *xdrs, stellarxdr_ClaimantV0 *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->destination))
    return (FALSE);
  if (!xdr_stellarxdr_ClaimPredicate(xdrs, &objp->predicate))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_Claimant(XDR *xdrs, stellarxdr_Claimant *objp) {
  if (!xdr_stellarxdr_ClaimantType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_CLAIMANT_TYPE_V0:
    if (!xdr_stellarxdr_ClaimantV0(xdrs, &objp->stellarxdr_Claimant_u.v0))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_ClaimableBalanceIDType(XDR *xdrs,
                                      stellarxdr_ClaimableBalanceIDType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimableBalanceID(XDR *xdrs,
                                         stellarxdr_ClaimableBalanceID *objp) {
  if (!xdr_stellarxdr_ClaimableBalanceIDType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_CLAIMABLE_BALANCE_ID_TYPE_V0:
    if (!xdr_stellarxdr_Hash(xdrs, objp->stellarxdr_ClaimableBalanceID_u.v0))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_ClaimableBalanceFlags(XDR *xdrs,
                                     stellarxdr_ClaimableBalanceFlags *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimableBalanceEntryExtensionV1Ext(
    XDR *xdrs, stellarxdr_ClaimableBalanceEntryExtensionV1Ext *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimableBalanceEntryExtensionV1(
    XDR *xdrs, stellarxdr_ClaimableBalanceEntryExtensionV1 *objp) {
  if (!xdr_stellarxdr_ClaimableBalanceEntryExtensionV1Ext(xdrs, &objp->ext))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->flags))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimableBalanceEntryExt(
    XDR *xdrs, stellarxdr_ClaimableBalanceEntryExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  case 1:
    if (!xdr_stellarxdr_ClaimableBalanceEntryExtensionV1(
            xdrs, &objp->stellarxdr_ClaimableBalanceEntryExt_u.v1))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_ClaimableBalanceEntry(XDR *xdrs,
                                     stellarxdr_ClaimableBalanceEntry *objp) {
  if (!xdr_stellarxdr_ClaimableBalanceID(xdrs, &objp->balanceID))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->claimants.claimants_val,
                 (u_int *)&objp->claimants.claimants_len, 10,
                 sizeof(stellarxdr_Claimant),
                 (xdrproc_t)xdr_stellarxdr_Claimant))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amount))
    return (FALSE);
  if (!xdr_stellarxdr_ClaimableBalanceEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LiquidityPoolConstantProductParameters(
    XDR *xdrs, stellarxdr_LiquidityPoolConstantProductParameters *objp) {
  if (!xdr_stellarxdr_Asset(xdrs, &objp->assetA))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->assetB))
    return (FALSE);
  if (!xdr_stellarxdr_int32(xdrs, &objp->fee))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LiquidityPoolEntryConstantProduct(
    XDR *xdrs, stellarxdr_LiquidityPoolEntryConstantProduct *objp) {
  if (!xdr_stellarxdr_LiquidityPoolConstantProductParameters(xdrs,
                                                             &objp->params))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->reserveA))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->reserveB))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->totalPoolShares))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->poolSharesTrustLineCount))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_LiquidityPoolEntryBody(XDR *xdrs,
                                      stellarxdr_LiquidityPoolEntryBody *objp) {
  if (!xdr_stellarxdr_LiquidityPoolType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_LIQUIDITY_POOL_CONSTANT_PRODUCT:
    if (!xdr_stellarxdr_LiquidityPoolEntryConstantProduct(
            xdrs, &objp->stellarxdr_LiquidityPoolEntryBody_u.constantProduct))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_LiquidityPoolEntry(XDR *xdrs,
                                         stellarxdr_LiquidityPoolEntry *objp) {
  if (!xdr_stellarxdr_PoolID(xdrs, objp->liquidityPoolID))
    return (FALSE);
  if (!xdr_stellarxdr_LiquidityPoolEntryBody(xdrs, &objp->body))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerEntryExtensionV1Ext(
    XDR *xdrs, stellarxdr_LedgerEntryExtensionV1Ext *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_LedgerEntryExtensionV1(XDR *xdrs,
                                      stellarxdr_LedgerEntryExtensionV1 *objp) {
  if (!xdr_stellarxdr_SponsorshipDescriptor(xdrs, &objp->sponsoringID))
    return (FALSE);
  if (!xdr_stellarxdr_LedgerEntryExtensionV1Ext(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerEntryData(XDR *xdrs,
                                      stellarxdr_LedgerEntryData *objp) {
  if (!xdr_stellarxdr_LedgerEntryType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_ACCOUNT:
    if (!xdr_stellarxdr_AccountEntry(
            xdrs, &objp->stellarxdr_LedgerEntryData_u.account))
      return (FALSE);
    break;
  case stellarxdr_TRUSTLINE:
    if (!xdr_stellarxdr_TrustLineEntry(
            xdrs, &objp->stellarxdr_LedgerEntryData_u.trustLine))
      return (FALSE);
    break;
  case stellarxdr_OFFER:
    if (!xdr_stellarxdr_OfferEntry(xdrs,
                                   &objp->stellarxdr_LedgerEntryData_u.offer))
      return (FALSE);
    break;
  case stellarxdr_DATA:
    if (!xdr_stellarxdr_DataEntry(xdrs,
                                  &objp->stellarxdr_LedgerEntryData_u.data))
      return (FALSE);
    break;
  case stellarxdr_CLAIMABLE_BALANCE:
    if (!xdr_stellarxdr_ClaimableBalanceEntry(
            xdrs, &objp->stellarxdr_LedgerEntryData_u.claimableBalance))
      return (FALSE);
    break;
  case stellarxdr_LIQUIDITY_POOL:
    if (!xdr_stellarxdr_LiquidityPoolEntry(
            xdrs, &objp->stellarxdr_LedgerEntryData_u.liquidityPool))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerEntryExt(XDR *xdrs,
                                     stellarxdr_LedgerEntryExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  case 1:
    if (!xdr_stellarxdr_LedgerEntryExtensionV1(
            xdrs, &objp->stellarxdr_LedgerEntryExt_u.v1))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerEntry(XDR *xdrs, stellarxdr_LedgerEntry *objp) {
  if (!xdr_stellarxdr_uint32(xdrs, &objp->lastModifiedLedgerSeq))
    return (FALSE);
  if (!xdr_stellarxdr_LedgerEntryData(xdrs, &objp->data))
    return (FALSE);
  if (!xdr_stellarxdr_LedgerEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerKeyAccount(XDR *xdrs,
                                       stellarxdr_LedgerKeyAccount *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->accountID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerKeyTrustLine(XDR *xdrs,
                                         stellarxdr_LedgerKeyTrustLine *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->accountID))
    return (FALSE);
  if (!xdr_stellarxdr_TrustLineAsset(xdrs, &objp->asset))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerKeyOffer(XDR *xdrs,
                                     stellarxdr_LedgerKeyOffer *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->sellerID))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->offerID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerKeyData(XDR *xdrs, stellarxdr_LedgerKeyData *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->accountID))
    return (FALSE);
  if (!xdr_stellarxdr_string64(xdrs, &objp->dataName))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerKeyClaimableBalance(
    XDR *xdrs, stellarxdr_LedgerKeyClaimableBalance *objp) {
  if (!xdr_stellarxdr_ClaimableBalanceID(xdrs, &objp->balanceID))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_LedgerKeyLiquidityPool(XDR *xdrs,
                                      stellarxdr_LedgerKeyLiquidityPool *objp) {
  if (!xdr_stellarxdr_PoolID(xdrs, objp->liquidityPoolID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerKey(XDR *xdrs, stellarxdr_LedgerKey *objp) {
  if (!xdr_stellarxdr_LedgerEntryType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_ACCOUNT:
    if (!xdr_stellarxdr_LedgerKeyAccount(xdrs,
                                         &objp->stellarxdr_LedgerKey_u.account))
      return (FALSE);
    break;
  case stellarxdr_TRUSTLINE:
    if (!xdr_stellarxdr_LedgerKeyTrustLine(
            xdrs, &objp->stellarxdr_LedgerKey_u.trustLine))
      return (FALSE);
    break;
  case stellarxdr_OFFER:
    if (!xdr_stellarxdr_LedgerKeyOffer(xdrs,
                                       &objp->stellarxdr_LedgerKey_u.offer))
      return (FALSE);
    break;
  case stellarxdr_DATA:
    if (!xdr_stellarxdr_LedgerKeyData(xdrs, &objp->stellarxdr_LedgerKey_u.data))
      return (FALSE);
    break;
  case stellarxdr_CLAIMABLE_BALANCE:
    if (!xdr_stellarxdr_LedgerKeyClaimableBalance(
            xdrs, &objp->stellarxdr_LedgerKey_u.claimableBalance))
      return (FALSE);
    break;
  case stellarxdr_LIQUIDITY_POOL:
    if (!xdr_stellarxdr_LedgerKeyLiquidityPool(
            xdrs, &objp->stellarxdr_LedgerKey_u.liquidityPool))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_EnvelopeType(XDR *xdrs, stellarxdr_EnvelopeType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LiquidityPoolParameters(
    XDR *xdrs, stellarxdr_LiquidityPoolParameters *objp) {
  if (!xdr_stellarxdr_LiquidityPoolType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_LIQUIDITY_POOL_CONSTANT_PRODUCT:
    if (!xdr_stellarxdr_LiquidityPoolConstantProductParameters(
            xdrs, &objp->stellarxdr_LiquidityPoolParameters_u.constantProduct))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_MuxedAccountMed25519(XDR *xdrs,
                                    stellarxdr_MuxedAccountMed25519 *objp) {
  if (!xdr_stellarxdr_uint64(xdrs, &objp->id))
    return (FALSE);
  if (!xdr_stellarxdr_uint256(xdrs, objp->ed25519))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_MuxedAccount(XDR *xdrs, stellarxdr_MuxedAccount *objp) {
  if (!xdr_stellarxdr_CryptoKeyType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_KEY_TYPE_ED25519:
    if (!xdr_stellarxdr_uint256(xdrs, objp->stellarxdr_MuxedAccount_u.ed25519))
      return (FALSE);
    break;
  case stellarxdr_KEY_TYPE_MUXED_ED25519:
    if (!xdr_stellarxdr_MuxedAccountMed25519(
            xdrs, &objp->stellarxdr_MuxedAccount_u.med25519))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_DecoratedSignature(XDR *xdrs,
                                         stellarxdr_DecoratedSignature *objp) {
  if (!xdr_stellarxdr_SignatureHint(xdrs, objp->hint))
    return (FALSE);
  if (!xdr_stellarxdr_Signature(xdrs, &objp->signature))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_OperationType(XDR *xdrs, stellarxdr_OperationType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_CreateAccountOp(XDR *xdrs,
                                      stellarxdr_CreateAccountOp *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->destination))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->startingBalance))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_PaymentOp(XDR *xdrs, stellarxdr_PaymentOp *objp) {
  if (!xdr_stellarxdr_MuxedAccount(xdrs, &objp->destination))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amount))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_PathPaymentStrictReceiveOp(
    XDR *xdrs, stellarxdr_PathPaymentStrictReceiveOp *objp) {
  if (!xdr_stellarxdr_Asset(xdrs, &objp->sendAsset))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->sendMax))
    return (FALSE);
  if (!xdr_stellarxdr_MuxedAccount(xdrs, &objp->destination))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->destAsset))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->destAmount))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->path.path_val,
                 (u_int *)&objp->path.path_len, 5, sizeof(stellarxdr_Asset),
                 (xdrproc_t)xdr_stellarxdr_Asset))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_PathPaymentStrictSendOp(
    XDR *xdrs, stellarxdr_PathPaymentStrictSendOp *objp) {
  if (!xdr_stellarxdr_Asset(xdrs, &objp->sendAsset))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->sendAmount))
    return (FALSE);
  if (!xdr_stellarxdr_MuxedAccount(xdrs, &objp->destination))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->destAsset))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->destMin))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->path.path_val,
                 (u_int *)&objp->path.path_len, 5, sizeof(stellarxdr_Asset),
                 (xdrproc_t)xdr_stellarxdr_Asset))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ManageSellOfferOp(XDR *xdrs,
                                        stellarxdr_ManageSellOfferOp *objp) {
  if (!xdr_stellarxdr_Asset(xdrs, &objp->selling))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->buying))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amount))
    return (FALSE);
  if (!xdr_stellarxdr_Price(xdrs, &objp->price))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->offerID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ManageBuyOfferOp(XDR *xdrs,
                                       stellarxdr_ManageBuyOfferOp *objp) {
  if (!xdr_stellarxdr_Asset(xdrs, &objp->selling))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->buying))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->buyAmount))
    return (FALSE);
  if (!xdr_stellarxdr_Price(xdrs, &objp->price))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->offerID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_CreatePassiveSellOfferOp(
    XDR *xdrs, stellarxdr_CreatePassiveSellOfferOp *objp) {
  if (!xdr_stellarxdr_Asset(xdrs, &objp->selling))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->buying))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amount))
    return (FALSE);
  if (!xdr_stellarxdr_Price(xdrs, &objp->price))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SetOptionsOp(XDR *xdrs, stellarxdr_SetOptionsOp *objp) {
  if (!xdr_pointer(xdrs, (char **)&objp->inflationDest,
                   sizeof(stellarxdr_AccountID),
                   (xdrproc_t)xdr_stellarxdr_AccountID))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->clearFlags, sizeof(stellarxdr_uint32),
                   (xdrproc_t)xdr_stellarxdr_uint32))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->setFlags, sizeof(stellarxdr_uint32),
                   (xdrproc_t)xdr_stellarxdr_uint32))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->masterWeight,
                   sizeof(stellarxdr_uint32), (xdrproc_t)xdr_stellarxdr_uint32))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->lowThreshold,
                   sizeof(stellarxdr_uint32), (xdrproc_t)xdr_stellarxdr_uint32))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->medThreshold,
                   sizeof(stellarxdr_uint32), (xdrproc_t)xdr_stellarxdr_uint32))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->highThreshold,
                   sizeof(stellarxdr_uint32), (xdrproc_t)xdr_stellarxdr_uint32))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->homeDomain,
                   sizeof(stellarxdr_string32),
                   (xdrproc_t)xdr_stellarxdr_string32))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->signer, sizeof(stellarxdr_Signer),
                   (xdrproc_t)xdr_stellarxdr_Signer))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ChangeTrustAsset(XDR *xdrs,
                                       stellarxdr_ChangeTrustAsset *objp) {
  if (!xdr_stellarxdr_AssetType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_ASSET_TYPE_NATIVE:
    break;
  case stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4:
    if (!xdr_stellarxdr_AlphaNum4(
            xdrs, &objp->stellarxdr_ChangeTrustAsset_u.alphaNum4))
      return (FALSE);
    break;
  case stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12:
    if (!xdr_stellarxdr_AlphaNum12(
            xdrs, &objp->stellarxdr_ChangeTrustAsset_u.alphaNum12))
      return (FALSE);
    break;
  case stellarxdr_ASSET_TYPE_POOL_SHARE:
    if (!xdr_stellarxdr_LiquidityPoolParameters(
            xdrs, &objp->stellarxdr_ChangeTrustAsset_u.liquidityPool))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_ChangeTrustOp(XDR *xdrs, stellarxdr_ChangeTrustOp *objp) {
  if (!xdr_stellarxdr_ChangeTrustAsset(xdrs, &objp->line))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->limit))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_AllowTrustOp(XDR *xdrs, stellarxdr_AllowTrustOp *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->trustor))
    return (FALSE);
  if (!xdr_stellarxdr_AssetCode(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->authorize))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ManageDataOp(XDR *xdrs, stellarxdr_ManageDataOp *objp) {
  if (!xdr_stellarxdr_string64(xdrs, &objp->dataName))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->dataValue,
                   sizeof(stellarxdr_DataValue),
                   (xdrproc_t)xdr_stellarxdr_DataValue))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_BumpSequenceOp(XDR *xdrs,
                                     stellarxdr_BumpSequenceOp *objp) {
  if (!xdr_stellarxdr_SequenceNumber(xdrs, &objp->bumpTo))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_CreateClaimableBalanceOp(
    XDR *xdrs, stellarxdr_CreateClaimableBalanceOp *objp) {
  if (!xdr_stellarxdr_Asset(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amount))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->claimants.claimants_val,
                 (u_int *)&objp->claimants.claimants_len, 10,
                 sizeof(stellarxdr_Claimant),
                 (xdrproc_t)xdr_stellarxdr_Claimant))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimClaimableBalanceOp(
    XDR *xdrs, stellarxdr_ClaimClaimableBalanceOp *objp) {
  if (!xdr_stellarxdr_ClaimableBalanceID(xdrs, &objp->balanceID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_BeginSponsoringFutureReservesOp(
    XDR *xdrs, stellarxdr_BeginSponsoringFutureReservesOp *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->sponsoredID))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_RevokeSponsorshipType(XDR *xdrs,
                                     stellarxdr_RevokeSponsorshipType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_RevokeSponsorshipOpSigner(
    XDR *xdrs, stellarxdr_RevokeSponsorshipOpSigner *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->accountID))
    return (FALSE);
  if (!xdr_stellarxdr_SignerKey(xdrs, &objp->signerKey))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_RevokeSponsorshipOp(XDR *xdrs,
                                   stellarxdr_RevokeSponsorshipOp *objp) {
  if (!xdr_stellarxdr_RevokeSponsorshipType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_REVOKE_SPONSORSHIP_LEDGER_ENTRY:
    if (!xdr_stellarxdr_LedgerKey(
            xdrs, &objp->stellarxdr_RevokeSponsorshipOp_u.ledgerKey))
      return (FALSE);
    break;
  case stellarxdr_REVOKE_SPONSORSHIP_SIGNER:
    if (!xdr_stellarxdr_RevokeSponsorshipOpSigner(
            xdrs, &objp->stellarxdr_RevokeSponsorshipOp_u.signer))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_ClawbackOp(XDR *xdrs, stellarxdr_ClawbackOp *objp) {
  if (!xdr_stellarxdr_Asset(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_stellarxdr_MuxedAccount(xdrs, &objp->from))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amount))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClawbackClaimableBalanceOp(
    XDR *xdrs, stellarxdr_ClawbackClaimableBalanceOp *objp) {
  if (!xdr_stellarxdr_ClaimableBalanceID(xdrs, &objp->balanceID))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_SetTrustLineFlagsOp(XDR *xdrs,
                                   stellarxdr_SetTrustLineFlagsOp *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->trustor))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->clearFlags))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->setFlags))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_LiquidityPoolDepositOp(XDR *xdrs,
                                      stellarxdr_LiquidityPoolDepositOp *objp) {
  if (!xdr_stellarxdr_PoolID(xdrs, objp->liquidityPoolID))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->maxAmountA))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->maxAmountB))
    return (FALSE);
  if (!xdr_stellarxdr_Price(xdrs, &objp->minPrice))
    return (FALSE);
  if (!xdr_stellarxdr_Price(xdrs, &objp->maxPrice))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LiquidityPoolWithdrawOp(
    XDR *xdrs, stellarxdr_LiquidityPoolWithdrawOp *objp) {
  if (!xdr_stellarxdr_PoolID(xdrs, objp->liquidityPoolID))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amount))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->minAmountA))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->minAmountB))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_OperationBody(XDR *xdrs, stellarxdr_OperationBody *objp) {
  if (!xdr_stellarxdr_OperationType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_CREATE_ACCOUNT:
    if (!xdr_stellarxdr_CreateAccountOp(
            xdrs, &objp->stellarxdr_OperationBody_u.createAccountOp))
      return (FALSE);
    break;
  case stellarxdr_PAYMENT:
    if (!xdr_stellarxdr_PaymentOp(xdrs,
                                  &objp->stellarxdr_OperationBody_u.paymentOp))
      return (FALSE);
    break;
  case stellarxdr_PATH_PAYMENT_STRICT_RECEIVE:
    if (!xdr_stellarxdr_PathPaymentStrictReceiveOp(
            xdrs, &objp->stellarxdr_OperationBody_u.pathPaymentStrictReceiveOp))
      return (FALSE);
    break;
  case stellarxdr_MANAGE_SELL_OFFER:
    if (!xdr_stellarxdr_ManageSellOfferOp(
            xdrs, &objp->stellarxdr_OperationBody_u.manageSellOfferOp))
      return (FALSE);
    break;
  case stellarxdr_CREATE_PASSIVE_SELL_OFFER:
    if (!xdr_stellarxdr_CreatePassiveSellOfferOp(
            xdrs, &objp->stellarxdr_OperationBody_u.createPassiveSellOfferOp))
      return (FALSE);
    break;
  case stellarxdr_SET_OPTIONS:
    if (!xdr_stellarxdr_SetOptionsOp(
            xdrs, &objp->stellarxdr_OperationBody_u.setOptionsOp))
      return (FALSE);
    break;
  case stellarxdr_CHANGE_TRUST:
    if (!xdr_stellarxdr_ChangeTrustOp(
            xdrs, &objp->stellarxdr_OperationBody_u.changeTrustOp))
      return (FALSE);
    break;
  case stellarxdr_ALLOW_TRUST:
    if (!xdr_stellarxdr_AllowTrustOp(
            xdrs, &objp->stellarxdr_OperationBody_u.allowTrustOp))
      return (FALSE);
    break;
  case stellarxdr_ACCOUNT_MERGE:
    if (!xdr_stellarxdr_MuxedAccount(
            xdrs, &objp->stellarxdr_OperationBody_u.destination))
      return (FALSE);
    break;
  case stellarxdr_INFLATION:
    break;
  case stellarxdr_MANAGE_DATA:
    if (!xdr_stellarxdr_ManageDataOp(
            xdrs, &objp->stellarxdr_OperationBody_u.manageDataOp))
      return (FALSE);
    break;
  case stellarxdr_BUMP_SEQUENCE:
    if (!xdr_stellarxdr_BumpSequenceOp(
            xdrs, &objp->stellarxdr_OperationBody_u.bumpSequenceOp))
      return (FALSE);
    break;
  case stellarxdr_MANAGE_BUY_OFFER:
    if (!xdr_stellarxdr_ManageBuyOfferOp(
            xdrs, &objp->stellarxdr_OperationBody_u.manageBuyOfferOp))
      return (FALSE);
    break;
  case stellarxdr_PATH_PAYMENT_STRICT_SEND:
    if (!xdr_stellarxdr_PathPaymentStrictSendOp(
            xdrs, &objp->stellarxdr_OperationBody_u.pathPaymentStrictSendOp))
      return (FALSE);
    break;
  case stellarxdr_CREATE_CLAIMABLE_BALANCE:
    if (!xdr_stellarxdr_CreateClaimableBalanceOp(
            xdrs, &objp->stellarxdr_OperationBody_u.createClaimableBalanceOp))
      return (FALSE);
    break;
  case stellarxdr_CLAIM_CLAIMABLE_BALANCE:
    if (!xdr_stellarxdr_ClaimClaimableBalanceOp(
            xdrs, &objp->stellarxdr_OperationBody_u.claimClaimableBalanceOp))
      return (FALSE);
    break;
  case stellarxdr_BEGIN_SPONSORING_FUTURE_RESERVES:
    if (!xdr_stellarxdr_BeginSponsoringFutureReservesOp(
            xdrs,
            &objp->stellarxdr_OperationBody_u.beginSponsoringFutureReservesOp))
      return (FALSE);
    break;
  case stellarxdr_END_SPONSORING_FUTURE_RESERVES:
    break;
  case stellarxdr_REVOKE_SPONSORSHIP:
    if (!xdr_stellarxdr_RevokeSponsorshipOp(
            xdrs, &objp->stellarxdr_OperationBody_u.revokeSponsorshipOp))
      return (FALSE);
    break;
  case stellarxdr_CLAWBACK:
    if (!xdr_stellarxdr_ClawbackOp(
            xdrs, &objp->stellarxdr_OperationBody_u.clawbackOp))
      return (FALSE);
    break;
  case stellarxdr_CLAWBACK_CLAIMABLE_BALANCE:
    if (!xdr_stellarxdr_ClawbackClaimableBalanceOp(
            xdrs, &objp->stellarxdr_OperationBody_u.clawbackClaimableBalanceOp))
      return (FALSE);
    break;
  case stellarxdr_SET_TRUST_LINE_FLAGS:
    if (!xdr_stellarxdr_SetTrustLineFlagsOp(
            xdrs, &objp->stellarxdr_OperationBody_u.setTrustLineFlagsOp))
      return (FALSE);
    break;
  case stellarxdr_LIQUIDITY_POOL_DEPOSIT:
    if (!xdr_stellarxdr_LiquidityPoolDepositOp(
            xdrs, &objp->stellarxdr_OperationBody_u.liquidityPoolDepositOp))
      return (FALSE);
    break;
  case stellarxdr_LIQUIDITY_POOL_WITHDRAW:
    if (!xdr_stellarxdr_LiquidityPoolWithdrawOp(
            xdrs, &objp->stellarxdr_OperationBody_u.liquidityPoolWithdrawOp))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_Operation(XDR *xdrs, stellarxdr_Operation *objp) {
  if (!xdr_pointer(xdrs, (char **)&objp->sourceAccount,
                   sizeof(stellarxdr_MuxedAccount),
                   (xdrproc_t)xdr_stellarxdr_MuxedAccount))
    return (FALSE);
  if (!xdr_stellarxdr_OperationBody(xdrs, &objp->body))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_EnvelopeTypeOperationID(
    XDR *xdrs, stellarxdr_EnvelopeTypeOperationID *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->sourceAccount))
    return (FALSE);
  if (!xdr_stellarxdr_SequenceNumber(xdrs, &objp->seqNum))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->opNum))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_OperationID(XDR *xdrs, stellarxdr_OperationID *objp) {
  if (!xdr_stellarxdr_EnvelopeType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_ENVELOPE_TYPE_OP_ID:
    if (!xdr_stellarxdr_EnvelopeTypeOperationID(
            xdrs, &objp->stellarxdr_OperationID_u.id))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_MemoType(XDR *xdrs, stellarxdr_MemoType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_Memo(XDR *xdrs, stellarxdr_Memo *objp) {
  if (!xdr_stellarxdr_MemoType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_MEMO_NONE:
    break;
  case stellarxdr_MEMO_TEXT:
    if (!xdr_string(xdrs, &objp->stellarxdr_Memo_u.text, 28))
      return (FALSE);
    break;
  case stellarxdr_MEMO_ID:
    if (!xdr_stellarxdr_uint64(xdrs, &objp->stellarxdr_Memo_u.id))
      return (FALSE);
    break;
  case stellarxdr_MEMO_HASH:
    if (!xdr_stellarxdr_Hash(xdrs, objp->stellarxdr_Memo_u.hash))
      return (FALSE);
    break;
  case stellarxdr_MEMO_RETURN:
    if (!xdr_stellarxdr_Hash(xdrs, objp->stellarxdr_Memo_u.retHash))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_TimeBounds(XDR *xdrs, stellarxdr_TimeBounds *objp) {
  if (!xdr_stellarxdr_TimePoint(xdrs, &objp->minTime))
    return (FALSE);
  if (!xdr_stellarxdr_TimePoint(xdrs, &objp->maxTime))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionV0Ext(XDR *xdrs,
                                       stellarxdr_TransactionV0Ext *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionV0(XDR *xdrs, stellarxdr_TransactionV0 *objp) {
  if (!xdr_stellarxdr_uint256(xdrs, objp->sourceAccountEd25519))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->fee))
    return (FALSE);
  if (!xdr_stellarxdr_SequenceNumber(xdrs, &objp->seqNum))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->timeBounds,
                   sizeof(stellarxdr_TimeBounds),
                   (xdrproc_t)xdr_stellarxdr_TimeBounds))
    return (FALSE);
  if (!xdr_stellarxdr_Memo(xdrs, &objp->memo))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->operations.operations_val,
                 (u_int *)&objp->operations.operations_len,
                 stellarxdr_MAX_OPS_PER_TX, sizeof(stellarxdr_Operation),
                 (xdrproc_t)xdr_stellarxdr_Operation))
    return (FALSE);
  if (!xdr_stellarxdr_TransactionV0Ext(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_TransactionV0Envelope(XDR *xdrs,
                                     stellarxdr_TransactionV0Envelope *objp) {
  if (!xdr_stellarxdr_TransactionV0(xdrs, &objp->tx))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->signatures.signatures_val,
                 (u_int *)&objp->signatures.signatures_len, 20,
                 sizeof(stellarxdr_DecoratedSignature),
                 (xdrproc_t)xdr_stellarxdr_DecoratedSignature))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionExt(XDR *xdrs,
                                     stellarxdr_TransactionExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_Transaction(XDR *xdrs, stellarxdr_Transaction *objp) {
  if (!xdr_stellarxdr_MuxedAccount(xdrs, &objp->sourceAccount))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->fee))
    return (FALSE);
  if (!xdr_stellarxdr_SequenceNumber(xdrs, &objp->seqNum))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->timeBounds,
                   sizeof(stellarxdr_TimeBounds),
                   (xdrproc_t)xdr_stellarxdr_TimeBounds))
    return (FALSE);
  if (!xdr_stellarxdr_Memo(xdrs, &objp->memo))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->operations.operations_val,
                 (u_int *)&objp->operations.operations_len,
                 stellarxdr_MAX_OPS_PER_TX, sizeof(stellarxdr_Operation),
                 (xdrproc_t)xdr_stellarxdr_Operation))
    return (FALSE);
  if (!xdr_stellarxdr_TransactionExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_TransactionV1Envelope(XDR *xdrs,
                                     stellarxdr_TransactionV1Envelope *objp) {
  if (!xdr_stellarxdr_Transaction(xdrs, &objp->tx))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->signatures.signatures_val,
                 (u_int *)&objp->signatures.signatures_len, 20,
                 sizeof(stellarxdr_DecoratedSignature),
                 (xdrproc_t)xdr_stellarxdr_DecoratedSignature))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_FeeBumpTransactionInnerTx(
    XDR *xdrs, stellarxdr_FeeBumpTransactionInnerTx *objp) {
  if (!xdr_stellarxdr_EnvelopeType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_ENVELOPE_TYPE_TX:
    if (!xdr_stellarxdr_TransactionV1Envelope(
            xdrs, &objp->stellarxdr_FeeBumpTransactionInnerTx_u.v1))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_FeeBumpTransactionExt(XDR *xdrs,
                                     stellarxdr_FeeBumpTransactionExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_FeeBumpTransaction(XDR *xdrs,
                                         stellarxdr_FeeBumpTransaction *objp) {
  if (!xdr_stellarxdr_MuxedAccount(xdrs, &objp->feeSource))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->fee))
    return (FALSE);
  if (!xdr_stellarxdr_FeeBumpTransactionInnerTx(xdrs, &objp->innerTx))
    return (FALSE);
  if (!xdr_stellarxdr_FeeBumpTransactionExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_FeeBumpTransactionEnvelope(
    XDR *xdrs, stellarxdr_FeeBumpTransactionEnvelope *objp) {
  if (!xdr_stellarxdr_FeeBumpTransaction(xdrs, &objp->tx))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->signatures.signatures_val,
                 (u_int *)&objp->signatures.signatures_len, 20,
                 sizeof(stellarxdr_DecoratedSignature),
                 (xdrproc_t)xdr_stellarxdr_DecoratedSignature))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_TransactionEnvelope(XDR *xdrs,
                                   stellarxdr_TransactionEnvelope *objp) {
  if (!xdr_stellarxdr_EnvelopeType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_ENVELOPE_TYPE_TX_V0:
    if (!xdr_stellarxdr_TransactionV0Envelope(
            xdrs, &objp->stellarxdr_TransactionEnvelope_u.v0))
      return (FALSE);
    break;
  case stellarxdr_ENVELOPE_TYPE_TX:
    if (!xdr_stellarxdr_TransactionV1Envelope(
            xdrs, &objp->stellarxdr_TransactionEnvelope_u.v1))
      return (FALSE);
    break;
  case stellarxdr_ENVELOPE_TYPE_TX_FEE_BUMP:
    if (!xdr_stellarxdr_FeeBumpTransactionEnvelope(
            xdrs, &objp->stellarxdr_TransactionEnvelope_u.feeBump))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionSignaturePayloadTaggedTransaction(
    XDR *xdrs, stellarxdr_TransactionSignaturePayloadTaggedTransaction *objp) {
  if (!xdr_stellarxdr_EnvelopeType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_ENVELOPE_TYPE_TX:
    if (!xdr_stellarxdr_Transaction(
            xdrs,
            &objp->stellarxdr_TransactionSignaturePayloadTaggedTransaction_u
                 .tx))
      return (FALSE);
    break;
  case stellarxdr_ENVELOPE_TYPE_TX_FEE_BUMP:
    if (!xdr_stellarxdr_FeeBumpTransaction(
            xdrs,
            &objp->stellarxdr_TransactionSignaturePayloadTaggedTransaction_u
                 .feeBump))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionSignaturePayload(
    XDR *xdrs, stellarxdr_TransactionSignaturePayload *objp) {
  if (!xdr_stellarxdr_Hash(xdrs, objp->networkId))
    return (FALSE);
  if (!xdr_stellarxdr_TransactionSignaturePayloadTaggedTransaction(
          xdrs, &objp->taggedTransaction))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimAtomType(XDR *xdrs, stellarxdr_ClaimAtomType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimOfferAtomV0(XDR *xdrs,
                                       stellarxdr_ClaimOfferAtomV0 *objp) {
  if (!xdr_stellarxdr_uint256(xdrs, objp->sellerEd25519))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->offerID))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->assetSold))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amountSold))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->assetBought))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amountBought))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimOfferAtom(XDR *xdrs,
                                     stellarxdr_ClaimOfferAtom *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->sellerID))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->offerID))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->assetSold))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amountSold))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->assetBought))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amountBought))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimLiquidityAtom(XDR *xdrs,
                                         stellarxdr_ClaimLiquidityAtom *objp) {
  if (!xdr_stellarxdr_PoolID(xdrs, objp->liquidityPoolID))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->assetSold))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amountSold))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->assetBought))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amountBought))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimAtom(XDR *xdrs, stellarxdr_ClaimAtom *objp) {
  if (!xdr_stellarxdr_ClaimAtomType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_CLAIM_ATOM_TYPE_V0:
    if (!xdr_stellarxdr_ClaimOfferAtomV0(xdrs,
                                         &objp->stellarxdr_ClaimAtom_u.v0))
      return (FALSE);
    break;
  case stellarxdr_CLAIM_ATOM_TYPE_ORDER_BOOK:
    if (!xdr_stellarxdr_ClaimOfferAtom(xdrs,
                                       &objp->stellarxdr_ClaimAtom_u.orderBook))
      return (FALSE);
    break;
  case stellarxdr_CLAIM_ATOM_TYPE_LIQUIDITY_POOL:
    if (!xdr_stellarxdr_ClaimLiquidityAtom(
            xdrs, &objp->stellarxdr_ClaimAtom_u.liquidityPool))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_CreateAccountResultCode(
    XDR *xdrs, stellarxdr_CreateAccountResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_CreateAccountResult(XDR *xdrs,
                                   stellarxdr_CreateAccountResult *objp) {
  if (!xdr_stellarxdr_CreateAccountResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_CREATE_ACCOUNT_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_PaymentResultCode(XDR *xdrs,
                                        stellarxdr_PaymentResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_PaymentResult(XDR *xdrs, stellarxdr_PaymentResult *objp) {
  if (!xdr_stellarxdr_PaymentResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_PAYMENT_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_PathPaymentStrictReceiveResultCode(
    XDR *xdrs, stellarxdr_PathPaymentStrictReceiveResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_SimplePaymentResult(XDR *xdrs,
                                   stellarxdr_SimplePaymentResult *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->destination))
    return (FALSE);
  if (!xdr_stellarxdr_Asset(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amount))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_PathPaymentStrictReceiveResultSuccess(
    XDR *xdrs, stellarxdr_PathPaymentStrictReceiveResultSuccess *objp) {
  if (!xdr_array(xdrs, (char **)&objp->offers.offers_val,
                 (u_int *)&objp->offers.offers_len, ~0,
                 sizeof(stellarxdr_ClaimAtom),
                 (xdrproc_t)xdr_stellarxdr_ClaimAtom))
    return (FALSE);
  if (!xdr_stellarxdr_SimplePaymentResult(xdrs, &objp->last))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_PathPaymentStrictReceiveResult(
    XDR *xdrs, stellarxdr_PathPaymentStrictReceiveResult *objp) {
  if (!xdr_stellarxdr_PathPaymentStrictReceiveResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_SUCCESS:
    if (!xdr_stellarxdr_PathPaymentStrictReceiveResultSuccess(
            xdrs, &objp->stellarxdr_PathPaymentStrictReceiveResult_u.success))
      return (FALSE);
    break;
  case stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_NO_ISSUER:
    if (!xdr_stellarxdr_Asset(
            xdrs, &objp->stellarxdr_PathPaymentStrictReceiveResult_u.noIssuer))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_PathPaymentStrictSendResultCode(
    XDR *xdrs, stellarxdr_PathPaymentStrictSendResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_PathPaymentStrictSendResultSuccess(
    XDR *xdrs, stellarxdr_PathPaymentStrictSendResultSuccess *objp) {
  if (!xdr_array(xdrs, (char **)&objp->offers.offers_val,
                 (u_int *)&objp->offers.offers_len, ~0,
                 sizeof(stellarxdr_ClaimAtom),
                 (xdrproc_t)xdr_stellarxdr_ClaimAtom))
    return (FALSE);
  if (!xdr_stellarxdr_SimplePaymentResult(xdrs, &objp->last))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_PathPaymentStrictSendResult(
    XDR *xdrs, stellarxdr_PathPaymentStrictSendResult *objp) {
  if (!xdr_stellarxdr_PathPaymentStrictSendResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_PATH_PAYMENT_STRICT_SEND_SUCCESS:
    if (!xdr_stellarxdr_PathPaymentStrictSendResultSuccess(
            xdrs, &objp->stellarxdr_PathPaymentStrictSendResult_u.success))
      return (FALSE);
    break;
  case stellarxdr_PATH_PAYMENT_STRICT_SEND_NO_ISSUER:
    if (!xdr_stellarxdr_Asset(
            xdrs, &objp->stellarxdr_PathPaymentStrictSendResult_u.noIssuer))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_ManageSellOfferResultCode(
    XDR *xdrs, stellarxdr_ManageSellOfferResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ManageOfferEffect(XDR *xdrs,
                                        stellarxdr_ManageOfferEffect *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ManageOfferSuccessResultOffer(
    XDR *xdrs, stellarxdr_ManageOfferSuccessResultOffer *objp) {
  if (!xdr_stellarxdr_ManageOfferEffect(xdrs, &objp->effect))
    return (FALSE);
  switch (objp->effect) {
  case stellarxdr_MANAGE_OFFER_CREATED:
  case stellarxdr_MANAGE_OFFER_UPDATED:
    if (!xdr_stellarxdr_OfferEntry(
            xdrs, &objp->stellarxdr_ManageOfferSuccessResultOffer_u.offer))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_ManageOfferSuccessResult(
    XDR *xdrs, stellarxdr_ManageOfferSuccessResult *objp) {
  if (!xdr_array(xdrs, (char **)&objp->offersClaimed.offersClaimed_val,
                 (u_int *)&objp->offersClaimed.offersClaimed_len, ~0,
                 sizeof(stellarxdr_ClaimAtom),
                 (xdrproc_t)xdr_stellarxdr_ClaimAtom))
    return (FALSE);
  if (!xdr_stellarxdr_ManageOfferSuccessResultOffer(xdrs, &objp->offer))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_ManageSellOfferResult(XDR *xdrs,
                                     stellarxdr_ManageSellOfferResult *objp) {
  if (!xdr_stellarxdr_ManageSellOfferResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_MANAGE_SELL_OFFER_SUCCESS:
    if (!xdr_stellarxdr_ManageOfferSuccessResult(
            xdrs, &objp->stellarxdr_ManageSellOfferResult_u.success))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_ManageBuyOfferResultCode(
    XDR *xdrs, stellarxdr_ManageBuyOfferResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_ManageBuyOfferResult(XDR *xdrs,
                                    stellarxdr_ManageBuyOfferResult *objp) {
  if (!xdr_stellarxdr_ManageBuyOfferResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_MANAGE_BUY_OFFER_SUCCESS:
    if (!xdr_stellarxdr_ManageOfferSuccessResult(
            xdrs, &objp->stellarxdr_ManageBuyOfferResult_u.success))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_SetOptionsResultCode(XDR *xdrs,
                                    stellarxdr_SetOptionsResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SetOptionsResult(XDR *xdrs,
                                       stellarxdr_SetOptionsResult *objp) {
  if (!xdr_stellarxdr_SetOptionsResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_SET_OPTIONS_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_ChangeTrustResultCode(XDR *xdrs,
                                     stellarxdr_ChangeTrustResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ChangeTrustResult(XDR *xdrs,
                                        stellarxdr_ChangeTrustResult *objp) {
  if (!xdr_stellarxdr_ChangeTrustResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_CHANGE_TRUST_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_AllowTrustResultCode(XDR *xdrs,
                                    stellarxdr_AllowTrustResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_AllowTrustResult(XDR *xdrs,
                                       stellarxdr_AllowTrustResult *objp) {
  if (!xdr_stellarxdr_AllowTrustResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_ALLOW_TRUST_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_AccountMergeResultCode(XDR *xdrs,
                                      stellarxdr_AccountMergeResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_AccountMergeResult(XDR *xdrs,
                                         stellarxdr_AccountMergeResult *objp) {
  if (!xdr_stellarxdr_AccountMergeResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_ACCOUNT_MERGE_SUCCESS:
    if (!xdr_stellarxdr_int64(
            xdrs, &objp->stellarxdr_AccountMergeResult_u.sourceAccountBalance))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_InflationResultCode(XDR *xdrs,
                                   stellarxdr_InflationResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_InflationPayout(XDR *xdrs,
                                      stellarxdr_InflationPayout *objp) {
  if (!xdr_stellarxdr_AccountID(xdrs, &objp->destination))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->amount))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_InflationResult(XDR *xdrs,
                                      stellarxdr_InflationResult *objp) {
  if (!xdr_stellarxdr_InflationResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_INFLATION_SUCCESS:
    if (!xdr_array(
            xdrs,
            (char **)&objp->stellarxdr_InflationResult_u.payouts.payouts_val,
            (u_int *)&objp->stellarxdr_InflationResult_u.payouts.payouts_len,
            ~0, sizeof(stellarxdr_InflationPayout),
            (xdrproc_t)xdr_stellarxdr_InflationPayout))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_ManageDataResultCode(XDR *xdrs,
                                    stellarxdr_ManageDataResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ManageDataResult(XDR *xdrs,
                                       stellarxdr_ManageDataResult *objp) {
  if (!xdr_stellarxdr_ManageDataResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_MANAGE_DATA_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_BumpSequenceResultCode(XDR *xdrs,
                                      stellarxdr_BumpSequenceResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_BumpSequenceResult(XDR *xdrs,
                                         stellarxdr_BumpSequenceResult *objp) {
  if (!xdr_stellarxdr_BumpSequenceResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_BUMP_SEQUENCE_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_CreateClaimableBalanceResultCode(
    XDR *xdrs, stellarxdr_CreateClaimableBalanceResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_CreateClaimableBalanceResult(
    XDR *xdrs, stellarxdr_CreateClaimableBalanceResult *objp) {
  if (!xdr_stellarxdr_CreateClaimableBalanceResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_CREATE_CLAIMABLE_BALANCE_SUCCESS:
    if (!xdr_stellarxdr_ClaimableBalanceID(
            xdrs, &objp->stellarxdr_CreateClaimableBalanceResult_u.balanceID))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimClaimableBalanceResultCode(
    XDR *xdrs, stellarxdr_ClaimClaimableBalanceResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClaimClaimableBalanceResult(
    XDR *xdrs, stellarxdr_ClaimClaimableBalanceResult *objp) {
  if (!xdr_stellarxdr_ClaimClaimableBalanceResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_CLAIM_CLAIMABLE_BALANCE_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_BeginSponsoringFutureReservesResultCode(
    XDR *xdrs, stellarxdr_BeginSponsoringFutureReservesResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_BeginSponsoringFutureReservesResult(
    XDR *xdrs, stellarxdr_BeginSponsoringFutureReservesResult *objp) {
  if (!xdr_stellarxdr_BeginSponsoringFutureReservesResultCode(xdrs,
                                                              &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_BEGIN_SPONSORING_FUTURE_RESERVES_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_EndSponsoringFutureReservesResultCode(
    XDR *xdrs, stellarxdr_EndSponsoringFutureReservesResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_EndSponsoringFutureReservesResult(
    XDR *xdrs, stellarxdr_EndSponsoringFutureReservesResult *objp) {
  if (!xdr_stellarxdr_EndSponsoringFutureReservesResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_END_SPONSORING_FUTURE_RESERVES_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_RevokeSponsorshipResultCode(
    XDR *xdrs, stellarxdr_RevokeSponsorshipResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_RevokeSponsorshipResult(
    XDR *xdrs, stellarxdr_RevokeSponsorshipResult *objp) {
  if (!xdr_stellarxdr_RevokeSponsorshipResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_REVOKE_SPONSORSHIP_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_ClawbackResultCode(XDR *xdrs,
                                         stellarxdr_ClawbackResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClawbackResult(XDR *xdrs,
                                     stellarxdr_ClawbackResult *objp) {
  if (!xdr_stellarxdr_ClawbackResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_CLAWBACK_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_ClawbackClaimableBalanceResultCode(
    XDR *xdrs, stellarxdr_ClawbackClaimableBalanceResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_ClawbackClaimableBalanceResult(
    XDR *xdrs, stellarxdr_ClawbackClaimableBalanceResult *objp) {
  if (!xdr_stellarxdr_ClawbackClaimableBalanceResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_CLAWBACK_CLAIMABLE_BALANCE_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_SetTrustLineFlagsResultCode(
    XDR *xdrs, stellarxdr_SetTrustLineFlagsResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SetTrustLineFlagsResult(
    XDR *xdrs, stellarxdr_SetTrustLineFlagsResult *objp) {
  if (!xdr_stellarxdr_SetTrustLineFlagsResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_SET_TRUST_LINE_FLAGS_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_LiquidityPoolDepositResultCode(
    XDR *xdrs, stellarxdr_LiquidityPoolDepositResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LiquidityPoolDepositResult(
    XDR *xdrs, stellarxdr_LiquidityPoolDepositResult *objp) {
  if (!xdr_stellarxdr_LiquidityPoolDepositResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_LIQUIDITY_POOL_DEPOSIT_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_LiquidityPoolWithdrawResultCode(
    XDR *xdrs, stellarxdr_LiquidityPoolWithdrawResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LiquidityPoolWithdrawResult(
    XDR *xdrs, stellarxdr_LiquidityPoolWithdrawResult *objp) {
  if (!xdr_stellarxdr_LiquidityPoolWithdrawResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_LIQUIDITY_POOL_WITHDRAW_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_OperationResultCode(XDR *xdrs,
                                   stellarxdr_OperationResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_OperationResultTr(XDR *xdrs,
                                        stellarxdr_OperationResultTr *objp) {
  if (!xdr_stellarxdr_OperationType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_CREATE_ACCOUNT:
    if (!xdr_stellarxdr_CreateAccountResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u.createAccountResult))
      return (FALSE);
    break;
  case stellarxdr_PAYMENT:
    if (!xdr_stellarxdr_PaymentResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u.paymentResult))
      return (FALSE);
    break;
  case stellarxdr_PATH_PAYMENT_STRICT_RECEIVE:
    if (!xdr_stellarxdr_PathPaymentStrictReceiveResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u
                       .pathPaymentStrictReceiveResult))
      return (FALSE);
    break;
  case stellarxdr_MANAGE_SELL_OFFER:
    if (!xdr_stellarxdr_ManageSellOfferResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u.manageSellOfferResult))
      return (FALSE);
    break;
  case stellarxdr_CREATE_PASSIVE_SELL_OFFER:
    if (!xdr_stellarxdr_ManageSellOfferResult(
            xdrs,
            &objp->stellarxdr_OperationResultTr_u.createPassiveSellOfferResult))
      return (FALSE);
    break;
  case stellarxdr_SET_OPTIONS:
    if (!xdr_stellarxdr_SetOptionsResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u.setOptionsResult))
      return (FALSE);
    break;
  case stellarxdr_CHANGE_TRUST:
    if (!xdr_stellarxdr_ChangeTrustResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u.changeTrustResult))
      return (FALSE);
    break;
  case stellarxdr_ALLOW_TRUST:
    if (!xdr_stellarxdr_AllowTrustResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u.allowTrustResult))
      return (FALSE);
    break;
  case stellarxdr_ACCOUNT_MERGE:
    if (!xdr_stellarxdr_AccountMergeResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u.accountMergeResult))
      return (FALSE);
    break;
  case stellarxdr_INFLATION:
    if (!xdr_stellarxdr_InflationResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u.inflationResult))
      return (FALSE);
    break;
  case stellarxdr_MANAGE_DATA:
    if (!xdr_stellarxdr_ManageDataResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u.manageDataResult))
      return (FALSE);
    break;
  case stellarxdr_BUMP_SEQUENCE:
    if (!xdr_stellarxdr_BumpSequenceResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u.bumpSeqResult))
      return (FALSE);
    break;
  case stellarxdr_MANAGE_BUY_OFFER:
    if (!xdr_stellarxdr_ManageBuyOfferResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u.manageBuyOfferResult))
      return (FALSE);
    break;
  case stellarxdr_PATH_PAYMENT_STRICT_SEND:
    if (!xdr_stellarxdr_PathPaymentStrictSendResult(
            xdrs,
            &objp->stellarxdr_OperationResultTr_u.pathPaymentStrictSendResult))
      return (FALSE);
    break;
  case stellarxdr_CREATE_CLAIMABLE_BALANCE:
    if (!xdr_stellarxdr_CreateClaimableBalanceResult(
            xdrs,
            &objp->stellarxdr_OperationResultTr_u.createClaimableBalanceResult))
      return (FALSE);
    break;
  case stellarxdr_CLAIM_CLAIMABLE_BALANCE:
    if (!xdr_stellarxdr_ClaimClaimableBalanceResult(
            xdrs,
            &objp->stellarxdr_OperationResultTr_u.claimClaimableBalanceResult))
      return (FALSE);
    break;
  case stellarxdr_BEGIN_SPONSORING_FUTURE_RESERVES:
    if (!xdr_stellarxdr_BeginSponsoringFutureReservesResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u
                       .beginSponsoringFutureReservesResult))
      return (FALSE);
    break;
  case stellarxdr_END_SPONSORING_FUTURE_RESERVES:
    if (!xdr_stellarxdr_EndSponsoringFutureReservesResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u
                       .endSponsoringFutureReservesResult))
      return (FALSE);
    break;
  case stellarxdr_REVOKE_SPONSORSHIP:
    if (!xdr_stellarxdr_RevokeSponsorshipResult(
            xdrs,
            &objp->stellarxdr_OperationResultTr_u.revokeSponsorshipResult))
      return (FALSE);
    break;
  case stellarxdr_CLAWBACK:
    if (!xdr_stellarxdr_ClawbackResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u.clawbackResult))
      return (FALSE);
    break;
  case stellarxdr_CLAWBACK_CLAIMABLE_BALANCE:
    if (!xdr_stellarxdr_ClawbackClaimableBalanceResult(
            xdrs, &objp->stellarxdr_OperationResultTr_u
                       .clawbackClaimableBalanceResult))
      return (FALSE);
    break;
  case stellarxdr_SET_TRUST_LINE_FLAGS:
    if (!xdr_stellarxdr_SetTrustLineFlagsResult(
            xdrs,
            &objp->stellarxdr_OperationResultTr_u.setTrustLineFlagsResult))
      return (FALSE);
    break;
  case stellarxdr_LIQUIDITY_POOL_DEPOSIT:
    if (!xdr_stellarxdr_LiquidityPoolDepositResult(
            xdrs,
            &objp->stellarxdr_OperationResultTr_u.liquidityPoolDepositResult))
      return (FALSE);
    break;
  case stellarxdr_LIQUIDITY_POOL_WITHDRAW:
    if (!xdr_stellarxdr_LiquidityPoolWithdrawResult(
            xdrs,
            &objp->stellarxdr_OperationResultTr_u.liquidityPoolWithdrawResult))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_OperationResult(XDR *xdrs,
                                      stellarxdr_OperationResult *objp) {
  if (!xdr_stellarxdr_OperationResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_opINNER:
    if (!xdr_stellarxdr_OperationResultTr(
            xdrs, &objp->stellarxdr_OperationResult_u.tr))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_TransactionResultCode(XDR *xdrs,
                                     stellarxdr_TransactionResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_InnerTransactionResultResult(
    XDR *xdrs, stellarxdr_InnerTransactionResultResult *objp) {
  if (!xdr_stellarxdr_TransactionResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_txSUCCESS:
  case stellarxdr_txFAILED:
    if (!xdr_array(xdrs,
                   (char **)&objp->stellarxdr_InnerTransactionResultResult_u
                       .results.results_val,
                   (u_int *)&objp->stellarxdr_InnerTransactionResultResult_u
                       .results.results_len,
                   ~0, sizeof(stellarxdr_OperationResult),
                   (xdrproc_t)xdr_stellarxdr_OperationResult))
      return (FALSE);
    break;
  case stellarxdr_txTOO_EARLY:
  case stellarxdr_txTOO_LATE:
  case stellarxdr_txMISSING_OPERATION:
  case stellarxdr_txBAD_SEQ:
  case stellarxdr_txBAD_AUTH:
  case stellarxdr_txINSUFFICIENT_BALANCE:
  case stellarxdr_txNO_ACCOUNT:
  case stellarxdr_txINSUFFICIENT_FEE:
  case stellarxdr_txBAD_AUTH_EXTRA:
  case stellarxdr_txINTERNAL_ERROR:
  case stellarxdr_txNOT_SUPPORTED:
  case stellarxdr_txBAD_SPONSORSHIP:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_InnerTransactionResultExt(
    XDR *xdrs, stellarxdr_InnerTransactionResultExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_InnerTransactionResult(XDR *xdrs,
                                      stellarxdr_InnerTransactionResult *objp) {
  if (!xdr_stellarxdr_int64(xdrs, &objp->feeCharged))
    return (FALSE);
  if (!xdr_stellarxdr_InnerTransactionResultResult(xdrs, &objp->result))
    return (FALSE);
  if (!xdr_stellarxdr_InnerTransactionResultExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_InnerTransactionResultPair(
    XDR *xdrs, stellarxdr_InnerTransactionResultPair *objp) {
  if (!xdr_stellarxdr_Hash(xdrs, objp->transactionHash))
    return (FALSE);
  if (!xdr_stellarxdr_InnerTransactionResult(xdrs, &objp->result))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionResultResult(
    XDR *xdrs, stellarxdr_TransactionResultResult *objp) {
  if (!xdr_stellarxdr_TransactionResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case stellarxdr_txFEE_BUMP_INNER_SUCCESS:
  case stellarxdr_txFEE_BUMP_INNER_FAILED:
    if (!xdr_stellarxdr_InnerTransactionResultPair(
            xdrs, &objp->stellarxdr_TransactionResultResult_u.innerResultPair))
      return (FALSE);
    break;
  case stellarxdr_txSUCCESS:
  case stellarxdr_txFAILED:
    if (!xdr_array(xdrs,
                   (char **)&objp->stellarxdr_TransactionResultResult_u.results
                       .results_val,
                   (u_int *)&objp->stellarxdr_TransactionResultResult_u.results
                       .results_len,
                   ~0, sizeof(stellarxdr_OperationResult),
                   (xdrproc_t)xdr_stellarxdr_OperationResult))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_TransactionResultExt(XDR *xdrs,
                                    stellarxdr_TransactionResultExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionResult(XDR *xdrs,
                                        stellarxdr_TransactionResult *objp) {
  if (!xdr_stellarxdr_int64(xdrs, &objp->feeCharged))
    return (FALSE);
  if (!xdr_stellarxdr_TransactionResultResult(xdrs, &objp->result))
    return (FALSE);
  if (!xdr_stellarxdr_TransactionResultExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_UpgradeType(XDR *xdrs, stellarxdr_UpgradeType *objp) {
  if (!xdr_bytes(xdrs, (char **)&objp->stellarxdr_UpgradeType_val,
                 (u_int *)&objp->stellarxdr_UpgradeType_len, 128))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_StellarValueType(XDR *xdrs,
                                       stellarxdr_StellarValueType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerCloseValueSignature(
    XDR *xdrs, stellarxdr_LedgerCloseValueSignature *objp) {
  if (!xdr_stellarxdr_NodeID(xdrs, &objp->nodeID))
    return (FALSE);
  if (!xdr_stellarxdr_Signature(xdrs, &objp->signature))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_StellarValueExt(XDR *xdrs,
                                      stellarxdr_StellarValueExt *objp) {
  if (!xdr_stellarxdr_StellarValueType(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case stellarxdr_STELLAR_VALUE_BASIC:
    break;
  case stellarxdr_STELLAR_VALUE_SIGNED:
    if (!xdr_stellarxdr_LedgerCloseValueSignature(
            xdrs, &objp->stellarxdr_StellarValueExt_u.lcValueSignature))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_StellarValue(XDR *xdrs, stellarxdr_StellarValue *objp) {
  if (!xdr_stellarxdr_Hash(xdrs, objp->txSetHash))
    return (FALSE);
  if (!xdr_stellarxdr_TimePoint(xdrs, &objp->closeTime))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->upgrades.upgrades_val,
                 (u_int *)&objp->upgrades.upgrades_len, 6,
                 sizeof(stellarxdr_UpgradeType),
                 (xdrproc_t)xdr_stellarxdr_UpgradeType))
    return (FALSE);
  if (!xdr_stellarxdr_StellarValueExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerHeaderExt(XDR *xdrs,
                                      stellarxdr_LedgerHeaderExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerHeader(XDR *xdrs, stellarxdr_LedgerHeader *objp) {
  if (!xdr_stellarxdr_uint32(xdrs, &objp->ledgerVersion))
    return (FALSE);
  if (!xdr_stellarxdr_Hash(xdrs, objp->previousLedgerHash))
    return (FALSE);
  if (!xdr_stellarxdr_StellarValue(xdrs, &objp->scpValue))
    return (FALSE);
  if (!xdr_stellarxdr_Hash(xdrs, objp->txSetResultHash))
    return (FALSE);
  if (!xdr_stellarxdr_Hash(xdrs, objp->bucketListHash))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->ledgerSeq))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->totalCoins))
    return (FALSE);
  if (!xdr_stellarxdr_int64(xdrs, &objp->feePool))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->inflationSeq))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->idPool))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->baseFee))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->baseReserve))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->maxTxSetSize))
    return (FALSE);
  if (!xdr_vector(xdrs, (char *)objp->skipList, 4, sizeof(stellarxdr_Hash),
                  (xdrproc_t)xdr_stellarxdr_Hash))
    return (FALSE);
  if (!xdr_stellarxdr_LedgerHeaderExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerUpgradeType(XDR *xdrs,
                                        stellarxdr_LedgerUpgradeType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerUpgrade(XDR *xdrs, stellarxdr_LedgerUpgrade *objp) {
  if (!xdr_stellarxdr_LedgerUpgradeType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_LEDGER_UPGRADE_VERSION:
    if (!xdr_stellarxdr_uint32(
            xdrs, &objp->stellarxdr_LedgerUpgrade_u.newLedgerVersion))
      return (FALSE);
    break;
  case stellarxdr_LEDGER_UPGRADE_BASE_FEE:
    if (!xdr_stellarxdr_uint32(xdrs,
                               &objp->stellarxdr_LedgerUpgrade_u.newBaseFee))
      return (FALSE);
    break;
  case stellarxdr_LEDGER_UPGRADE_MAX_TX_SET_SIZE:
    if (!xdr_stellarxdr_uint32(
            xdrs, &objp->stellarxdr_LedgerUpgrade_u.newMaxTxSetSize))
      return (FALSE);
    break;
  case stellarxdr_LEDGER_UPGRADE_BASE_RESERVE:
    if (!xdr_stellarxdr_uint32(
            xdrs, &objp->stellarxdr_LedgerUpgrade_u.newBaseReserve))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_BucketEntryType(XDR *xdrs,
                                      stellarxdr_BucketEntryType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_BucketMetadataExt(XDR *xdrs,
                                        stellarxdr_BucketMetadataExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_BucketMetadata(XDR *xdrs,
                                     stellarxdr_BucketMetadata *objp) {
  if (!xdr_stellarxdr_uint32(xdrs, &objp->ledgerVersion))
    return (FALSE);
  if (!xdr_stellarxdr_BucketMetadataExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_BucketEntry(XDR *xdrs, stellarxdr_BucketEntry *objp) {
  if (!xdr_stellarxdr_BucketEntryType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_LIVEENTRY:
  case stellarxdr_INITENTRY:
    if (!xdr_stellarxdr_LedgerEntry(xdrs,
                                    &objp->stellarxdr_BucketEntry_u.liveEntry))
      return (FALSE);
    break;
  case stellarxdr_DEADENTRY:
    if (!xdr_stellarxdr_LedgerKey(xdrs,
                                  &objp->stellarxdr_BucketEntry_u.deadEntry))
      return (FALSE);
    break;
  case stellarxdr_METAENTRY:
    if (!xdr_stellarxdr_BucketMetadata(
            xdrs, &objp->stellarxdr_BucketEntry_u.metaEntry))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionSet(XDR *xdrs,
                                     stellarxdr_TransactionSet *objp) {
  if (!xdr_stellarxdr_Hash(xdrs, objp->previousLedgerHash))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->txs.txs_val, (u_int *)&objp->txs.txs_len,
                 ~0, sizeof(stellarxdr_TransactionEnvelope),
                 (xdrproc_t)xdr_stellarxdr_TransactionEnvelope))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_TransactionResultPair(XDR *xdrs,
                                     stellarxdr_TransactionResultPair *objp) {
  if (!xdr_stellarxdr_Hash(xdrs, objp->transactionHash))
    return (FALSE);
  if (!xdr_stellarxdr_TransactionResult(xdrs, &objp->result))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_TransactionResultSet(XDR *xdrs,
                                    stellarxdr_TransactionResultSet *objp) {
  if (!xdr_array(xdrs, (char **)&objp->results.results_val,
                 (u_int *)&objp->results.results_len, ~0,
                 sizeof(stellarxdr_TransactionResultPair),
                 (xdrproc_t)xdr_stellarxdr_TransactionResultPair))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionHistoryEntryExt(
    XDR *xdrs, stellarxdr_TransactionHistoryEntryExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionHistoryEntry(
    XDR *xdrs, stellarxdr_TransactionHistoryEntry *objp) {
  if (!xdr_stellarxdr_uint32(xdrs, &objp->ledgerSeq))
    return (FALSE);
  if (!xdr_stellarxdr_TransactionSet(xdrs, &objp->txSet))
    return (FALSE);
  if (!xdr_stellarxdr_TransactionHistoryEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionHistoryResultEntryExt(
    XDR *xdrs, stellarxdr_TransactionHistoryResultEntryExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionHistoryResultEntry(
    XDR *xdrs, stellarxdr_TransactionHistoryResultEntry *objp) {
  if (!xdr_stellarxdr_uint32(xdrs, &objp->ledgerSeq))
    return (FALSE);
  if (!xdr_stellarxdr_TransactionResultSet(xdrs, &objp->txResultSet))
    return (FALSE);
  if (!xdr_stellarxdr_TransactionHistoryResultEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerHeaderHistoryEntryExt(
    XDR *xdrs, stellarxdr_LedgerHeaderHistoryEntryExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerHeaderHistoryEntry(
    XDR *xdrs, stellarxdr_LedgerHeaderHistoryEntry *objp) {
  if (!xdr_stellarxdr_Hash(xdrs, objp->hash))
    return (FALSE);
  if (!xdr_stellarxdr_LedgerHeader(xdrs, &objp->header))
    return (FALSE);
  if (!xdr_stellarxdr_LedgerHeaderHistoryEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerSCPMessages(XDR *xdrs,
                                        stellarxdr_LedgerSCPMessages *objp) {
  if (!xdr_stellarxdr_uint32(xdrs, &objp->ledgerSeq))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->messages.messages_val,
                 (u_int *)&objp->messages.messages_len, ~0,
                 sizeof(stellarxdr_SCPEnvelope),
                 (xdrproc_t)xdr_stellarxdr_SCPEnvelope))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SCPHistoryEntryV0(XDR *xdrs,
                                        stellarxdr_SCPHistoryEntryV0 *objp) {
  if (!xdr_array(xdrs, (char **)&objp->quorumSets.quorumSets_val,
                 (u_int *)&objp->quorumSets.quorumSets_len, ~0,
                 sizeof(stellarxdr_SCPQuorumSet),
                 (xdrproc_t)xdr_stellarxdr_SCPQuorumSet))
    return (FALSE);
  if (!xdr_stellarxdr_LedgerSCPMessages(xdrs, &objp->ledgerMessages))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SCPHistoryEntry(XDR *xdrs,
                                      stellarxdr_SCPHistoryEntry *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    if (!xdr_stellarxdr_SCPHistoryEntryV0(
            xdrs, &objp->stellarxdr_SCPHistoryEntry_u.v0))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_LedgerEntryChangeType(XDR *xdrs,
                                     stellarxdr_LedgerEntryChangeType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerEntryChange(XDR *xdrs,
                                        stellarxdr_LedgerEntryChange *objp) {
  if (!xdr_stellarxdr_LedgerEntryChangeType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_LEDGER_ENTRY_CREATED:
    if (!xdr_stellarxdr_LedgerEntry(
            xdrs, &objp->stellarxdr_LedgerEntryChange_u.created))
      return (FALSE);
    break;
  case stellarxdr_LEDGER_ENTRY_UPDATED:
    if (!xdr_stellarxdr_LedgerEntry(
            xdrs, &objp->stellarxdr_LedgerEntryChange_u.updated))
      return (FALSE);
    break;
  case stellarxdr_LEDGER_ENTRY_REMOVED:
    if (!xdr_stellarxdr_LedgerKey(
            xdrs, &objp->stellarxdr_LedgerEntryChange_u.removed))
      return (FALSE);
    break;
  case stellarxdr_LEDGER_ENTRY_STATE:
    if (!xdr_stellarxdr_LedgerEntry(
            xdrs, &objp->stellarxdr_LedgerEntryChange_u.state))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerEntryChanges(XDR *xdrs,
                                         stellarxdr_LedgerEntryChanges *objp) {
  if (!xdr_array(xdrs, (char **)&objp->stellarxdr_LedgerEntryChanges_val,
                 (u_int *)&objp->stellarxdr_LedgerEntryChanges_len, ~0,
                 sizeof(stellarxdr_LedgerEntryChange),
                 (xdrproc_t)xdr_stellarxdr_LedgerEntryChange))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_OperationMeta(XDR *xdrs, stellarxdr_OperationMeta *objp) {
  if (!xdr_stellarxdr_LedgerEntryChanges(xdrs, &objp->changes))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionMetaV1(XDR *xdrs,
                                        stellarxdr_TransactionMetaV1 *objp) {
  if (!xdr_stellarxdr_LedgerEntryChanges(xdrs, &objp->txChanges))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->operations.operations_val,
                 (u_int *)&objp->operations.operations_len, ~0,
                 sizeof(stellarxdr_OperationMeta),
                 (xdrproc_t)xdr_stellarxdr_OperationMeta))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionMetaV2(XDR *xdrs,
                                        stellarxdr_TransactionMetaV2 *objp) {
  if (!xdr_stellarxdr_LedgerEntryChanges(xdrs, &objp->txChangesBefore))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->operations.operations_val,
                 (u_int *)&objp->operations.operations_len, ~0,
                 sizeof(stellarxdr_OperationMeta),
                 (xdrproc_t)xdr_stellarxdr_OperationMeta))
    return (FALSE);
  if (!xdr_stellarxdr_LedgerEntryChanges(xdrs, &objp->txChangesAfter))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_TransactionMeta(XDR *xdrs,
                                      stellarxdr_TransactionMeta *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    if (!xdr_array(xdrs,
                   (char **)&objp->stellarxdr_TransactionMeta_u.operations
                       .operations_val,
                   (u_int *)&objp->stellarxdr_TransactionMeta_u.operations
                       .operations_len,
                   ~0, sizeof(stellarxdr_OperationMeta),
                   (xdrproc_t)xdr_stellarxdr_OperationMeta))
      return (FALSE);
    break;
  case 1:
    if (!xdr_stellarxdr_TransactionMetaV1(
            xdrs, &objp->stellarxdr_TransactionMeta_u.v1))
      return (FALSE);
    break;
  case 2:
    if (!xdr_stellarxdr_TransactionMetaV2(
            xdrs, &objp->stellarxdr_TransactionMeta_u.v2))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_TransactionResultMeta(XDR *xdrs,
                                     stellarxdr_TransactionResultMeta *objp) {
  if (!xdr_stellarxdr_TransactionResultPair(xdrs, &objp->result))
    return (FALSE);
  if (!xdr_stellarxdr_LedgerEntryChanges(xdrs, &objp->feeProcessing))
    return (FALSE);
  if (!xdr_stellarxdr_TransactionMeta(xdrs, &objp->txApplyProcessing))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_UpgradeEntryMeta(XDR *xdrs,
                                       stellarxdr_UpgradeEntryMeta *objp) {
  if (!xdr_stellarxdr_LedgerUpgrade(xdrs, &objp->upgrade))
    return (FALSE);
  if (!xdr_stellarxdr_LedgerEntryChanges(xdrs, &objp->changes))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerCloseMetaV0(XDR *xdrs,
                                        stellarxdr_LedgerCloseMetaV0 *objp) {
  if (!xdr_stellarxdr_LedgerHeaderHistoryEntry(xdrs, &objp->ledgerHeader))
    return (FALSE);
  if (!xdr_stellarxdr_TransactionSet(xdrs, &objp->txSet))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->txProcessing.txProcessing_val,
                 (u_int *)&objp->txProcessing.txProcessing_len, ~0,
                 sizeof(stellarxdr_TransactionResultMeta),
                 (xdrproc_t)xdr_stellarxdr_TransactionResultMeta))
    return (FALSE);
  if (!xdr_array(xdrs,
                 (char **)&objp->upgradesProcessing.upgradesProcessing_val,
                 (u_int *)&objp->upgradesProcessing.upgradesProcessing_len, ~0,
                 sizeof(stellarxdr_UpgradeEntryMeta),
                 (xdrproc_t)xdr_stellarxdr_UpgradeEntryMeta))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->scpInfo.scpInfo_val,
                 (u_int *)&objp->scpInfo.scpInfo_len, ~0,
                 sizeof(stellarxdr_SCPHistoryEntry),
                 (xdrproc_t)xdr_stellarxdr_SCPHistoryEntry))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_LedgerCloseMeta(XDR *xdrs,
                                      stellarxdr_LedgerCloseMeta *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    if (!xdr_stellarxdr_LedgerCloseMetaV0(
            xdrs, &objp->stellarxdr_LedgerCloseMeta_u.v0))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_ErrorCode(XDR *xdrs, stellarxdr_ErrorCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_Error(XDR *xdrs, stellarxdr_Error *objp) {
  if (!xdr_stellarxdr_ErrorCode(xdrs, &objp->code))
    return (FALSE);
  if (!xdr_string(xdrs, &objp->msg, 100))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_AuthCert(XDR *xdrs, stellarxdr_AuthCert *objp) {
  if (!xdr_stellarxdr_Curve25519Public(xdrs, &objp->pubkey))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->expiration))
    return (FALSE);
  if (!xdr_stellarxdr_Signature(xdrs, &objp->sig))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_Hello(XDR *xdrs, stellarxdr_Hello *objp) {
  if (!xdr_stellarxdr_uint32(xdrs, &objp->ledgerVersion))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->overlayVersion))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->overlayMinVersion))
    return (FALSE);
  if (!xdr_stellarxdr_Hash(xdrs, objp->networkID))
    return (FALSE);
  if (!xdr_string(xdrs, &objp->versionStr, 100))
    return (FALSE);
  if (!xdr_int(xdrs, &objp->listeningPort))
    return (FALSE);
  if (!xdr_stellarxdr_NodeID(xdrs, &objp->peerID))
    return (FALSE);
  if (!xdr_stellarxdr_AuthCert(xdrs, &objp->cert))
    return (FALSE);
  if (!xdr_stellarxdr_uint256(xdrs, objp->nonce))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_Auth(XDR *xdrs, stellarxdr_Auth *objp) {
  if (!xdr_int(xdrs, &objp->unused))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_IPAddrType(XDR *xdrs, stellarxdr_IPAddrType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_PeerAddressIP(XDR *xdrs, stellarxdr_PeerAddressIP *objp) {
  if (!xdr_stellarxdr_IPAddrType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_IPv4:
    if (!xdr_opaque(xdrs, objp->stellarxdr_PeerAddressIP_u.ipv4, 4))
      return (FALSE);
    break;
  case stellarxdr_IPv6:
    if (!xdr_opaque(xdrs, objp->stellarxdr_PeerAddressIP_u.ipv6, 16))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_PeerAddress(XDR *xdrs, stellarxdr_PeerAddress *objp) {
  if (!xdr_stellarxdr_PeerAddressIP(xdrs, &objp->ip))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->port))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->numFailures))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_MessageType(XDR *xdrs, stellarxdr_MessageType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_DontHave(XDR *xdrs, stellarxdr_DontHave *objp) {
  if (!xdr_stellarxdr_MessageType(xdrs, &objp->type))
    return (FALSE);
  if (!xdr_stellarxdr_uint256(xdrs, objp->reqHash))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SurveyMessageCommandType(
    XDR *xdrs, stellarxdr_SurveyMessageCommandType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_SurveyRequestMessage(XDR *xdrs,
                                    stellarxdr_SurveyRequestMessage *objp) {
  if (!xdr_stellarxdr_NodeID(xdrs, &objp->surveyorPeerID))
    return (FALSE);
  if (!xdr_stellarxdr_NodeID(xdrs, &objp->surveyedPeerID))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->ledgerNum))
    return (FALSE);
  if (!xdr_stellarxdr_Curve25519Public(xdrs, &objp->encryptionKey))
    return (FALSE);
  if (!xdr_stellarxdr_SurveyMessageCommandType(xdrs, &objp->commandType))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SignedSurveyRequestMessage(
    XDR *xdrs, stellarxdr_SignedSurveyRequestMessage *objp) {
  if (!xdr_stellarxdr_Signature(xdrs, &objp->requestSignature))
    return (FALSE);
  if (!xdr_stellarxdr_SurveyRequestMessage(xdrs, &objp->request))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_EncryptedBody(XDR *xdrs, stellarxdr_EncryptedBody *objp) {
  if (!xdr_bytes(xdrs, (char **)&objp->stellarxdr_EncryptedBody_val,
                 (u_int *)&objp->stellarxdr_EncryptedBody_len, 64000))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_SurveyResponseMessage(XDR *xdrs,
                                     stellarxdr_SurveyResponseMessage *objp) {
  if (!xdr_stellarxdr_NodeID(xdrs, &objp->surveyorPeerID))
    return (FALSE);
  if (!xdr_stellarxdr_NodeID(xdrs, &objp->surveyedPeerID))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->ledgerNum))
    return (FALSE);
  if (!xdr_stellarxdr_SurveyMessageCommandType(xdrs, &objp->commandType))
    return (FALSE);
  if (!xdr_stellarxdr_EncryptedBody(xdrs, &objp->encryptedBody))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SignedSurveyResponseMessage(
    XDR *xdrs, stellarxdr_SignedSurveyResponseMessage *objp) {
  if (!xdr_stellarxdr_Signature(xdrs, &objp->responseSignature))
    return (FALSE);
  if (!xdr_stellarxdr_SurveyResponseMessage(xdrs, &objp->response))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_PeerStats(XDR *xdrs, stellarxdr_PeerStats *objp) {
  if (!xdr_stellarxdr_NodeID(xdrs, &objp->id))
    return (FALSE);
  if (!xdr_string(xdrs, &objp->versionStr, 100))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->messagesRead))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->messagesWritten))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->bytesRead))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->bytesWritten))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->secondsConnected))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->uniqueFloodBytesRecv))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->duplicateFloodBytesRecv))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->uniqueFetchBytesRecv))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->duplicateFetchBytesRecv))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->uniqueFloodMessageRecv))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->duplicateFloodMessageRecv))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->uniqueFetchMessageRecv))
    return (FALSE);
  if (!xdr_stellarxdr_uint64(xdrs, &objp->duplicateFetchMessageRecv))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_PeerStatList(XDR *xdrs, stellarxdr_PeerStatList *objp) {
  if (!xdr_array(xdrs, (char **)&objp->stellarxdr_PeerStatList_val,
                 (u_int *)&objp->stellarxdr_PeerStatList_len, 25,
                 sizeof(stellarxdr_PeerStats),
                 (xdrproc_t)xdr_stellarxdr_PeerStats))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_TopologyResponseBody(XDR *xdrs,
                                    stellarxdr_TopologyResponseBody *objp) {
  if (!xdr_stellarxdr_PeerStatList(xdrs, &objp->inboundPeers))
    return (FALSE);
  if (!xdr_stellarxdr_PeerStatList(xdrs, &objp->outboundPeers))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->totalInboundPeerCount))
    return (FALSE);
  if (!xdr_stellarxdr_uint32(xdrs, &objp->totalOutboundPeerCount))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_stellarxdr_SurveyResponseBody(XDR *xdrs,
                                         stellarxdr_SurveyResponseBody *objp) {
  if (!xdr_stellarxdr_SurveyMessageCommandType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_SURVEY_TOPOLOGY:
    if (!xdr_stellarxdr_TopologyResponseBody(
            xdrs, &objp->stellarxdr_SurveyResponseBody_u.topologyResponseBody))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_stellarxdr_StellarMessage(XDR *xdrs,
                                     stellarxdr_StellarMessage *objp) {
  if (!xdr_stellarxdr_MessageType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case stellarxdr_ERROR_MSG:
    if (!xdr_stellarxdr_Error(xdrs, &objp->stellarxdr_StellarMessage_u.error))
      return (FALSE);
    break;
  case stellarxdr_HELLO:
    if (!xdr_stellarxdr_Hello(xdrs, &objp->stellarxdr_StellarMessage_u.hello))
      return (FALSE);
    break;
  case stellarxdr_AUTH:
    if (!xdr_stellarxdr_Auth(xdrs, &objp->stellarxdr_StellarMessage_u.auth))
      return (FALSE);
    break;
  case stellarxdr_DONT_HAVE:
    if (!xdr_stellarxdr_DontHave(xdrs,
                                 &objp->stellarxdr_StellarMessage_u.dontHave))
      return (FALSE);
    break;
  case stellarxdr_GET_PEERS:
    break;
  case stellarxdr_PEERS:
    if (!xdr_array(xdrs,
                   (char **)&objp->stellarxdr_StellarMessage_u.peers.peers_val,
                   (u_int *)&objp->stellarxdr_StellarMessage_u.peers.peers_len,
                   100, sizeof(stellarxdr_PeerAddress),
                   (xdrproc_t)xdr_stellarxdr_PeerAddress))
      return (FALSE);
    break;
  case stellarxdr_GET_TX_SET:
    if (!xdr_stellarxdr_uint256(xdrs,
                                objp->stellarxdr_StellarMessage_u.txSetHash))
      return (FALSE);
    break;
  case stellarxdr_TX_SET:
    if (!xdr_stellarxdr_TransactionSet(
            xdrs, &objp->stellarxdr_StellarMessage_u.txSet))
      return (FALSE);
    break;
  case stellarxdr_TRANSACTION:
    if (!xdr_stellarxdr_TransactionEnvelope(
            xdrs, &objp->stellarxdr_StellarMessage_u.transaction))
      return (FALSE);
    break;
  case stellarxdr_SURVEY_REQUEST:
    if (!xdr_stellarxdr_SignedSurveyRequestMessage(
            xdrs,
            &objp->stellarxdr_StellarMessage_u.signedSurveyRequestMessage))
      return (FALSE);
    break;
  case stellarxdr_SURVEY_RESPONSE:
    if (!xdr_stellarxdr_SignedSurveyResponseMessage(
            xdrs,
            &objp->stellarxdr_StellarMessage_u.signedSurveyResponseMessage))
      return (FALSE);
    break;
  case stellarxdr_GET_SCP_QUORUMSET:
    if (!xdr_stellarxdr_uint256(xdrs,
                                objp->stellarxdr_StellarMessage_u.qSetHash))
      return (FALSE);
    break;
  case stellarxdr_SCP_QUORUMSET:
    if (!xdr_stellarxdr_SCPQuorumSet(xdrs,
                                     &objp->stellarxdr_StellarMessage_u.qSet))
      return (FALSE);
    break;
  case stellarxdr_SCP_MESSAGE:
    if (!xdr_stellarxdr_SCPEnvelope(
            xdrs, &objp->stellarxdr_StellarMessage_u.envelope))
      return (FALSE);
    break;
  case stellarxdr_GET_SCP_STATE:
    if (!xdr_stellarxdr_uint32(
            xdrs, &objp->stellarxdr_StellarMessage_u.getSCPLedgerSeq))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t
xdr_stellarxdr_AuthenticatedMessageV0(XDR *xdrs,
                                      stellarxdr_AuthenticatedMessageV0 *objp) {
  if (!xdr_stellarxdr_uint64(xdrs, &objp->sequence))
    return (FALSE);
  if (!xdr_stellarxdr_StellarMessage(xdrs, &objp->message))
    return (FALSE);
  if (!xdr_stellarxdr_HmacSha256Mac(xdrs, &objp->mac))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_stellarxdr_AuthenticatedMessage(XDR *xdrs,
                                    stellarxdr_AuthenticatedMessage *objp) {
  if (!xdr_stellarxdr_uint32(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    if (!xdr_stellarxdr_AuthenticatedMessageV0(
            xdrs, &objp->stellarxdr_AuthenticatedMessage_u.v0))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}
