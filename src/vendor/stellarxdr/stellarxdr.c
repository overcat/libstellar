#include "stellarxdr.h"

bool_t xdr_Hash(XDR *xdrs, Hash objp) {
  if (!xdr_opaque(xdrs, objp, 32))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_uint256(XDR *xdrs, uint256 objp) {
  if (!xdr_opaque(xdrs, objp, 32))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_uint32(XDR *xdrs, uint32 *objp) {
  if (!xdr_u_int(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_int32(XDR *xdrs, int32 *objp) {
  if (!xdr_int(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_uint64(XDR *xdrs, uint64 *objp) {
  if (!xdr_u_int64_t(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_int64(XDR *xdrs, int64 *objp) {
  if (!xdr_int64_t(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_CryptoKeyType(XDR *xdrs, CryptoKeyType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_PublicKeyType(XDR *xdrs, PublicKeyType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SignerKeyType(XDR *xdrs, SignerKeyType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_PublicKey(XDR *xdrs, PublicKey *objp) {
  if (!xdr_PublicKeyType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case PUBLIC_KEY_TYPE_ED25519:
    if (!xdr_uint256(xdrs, objp->PublicKey_u.ed25519))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_SignerKey(XDR *xdrs, SignerKey *objp) {
  if (!xdr_SignerKeyType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case SIGNER_KEY_TYPE_ED25519:
    if (!xdr_uint256(xdrs, objp->SignerKey_u.ed25519))
      return (FALSE);
    break;
  case SIGNER_KEY_TYPE_PRE_AUTH_TX:
    if (!xdr_uint256(xdrs, objp->SignerKey_u.preAuthTx))
      return (FALSE);
    break;
  case SIGNER_KEY_TYPE_HASH_X:
    if (!xdr_uint256(xdrs, objp->SignerKey_u.hashX))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_Signature(XDR *xdrs, Signature *objp) {
  if (!xdr_bytes(xdrs, (char **)&objp->Signature_val,
                 (u_int *)&objp->Signature_len, 64))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SignatureHint(XDR *xdrs, SignatureHint objp) {
  if (!xdr_opaque(xdrs, objp, 4))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_NodeID(XDR *xdrs, NodeID *objp) {
  if (!xdr_PublicKey(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_Curve25519Secret(XDR *xdrs, Curve25519Secret *objp) {
  if (!xdr_opaque(xdrs, objp->key, 32))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_Curve25519Public(XDR *xdrs, Curve25519Public *objp) {
  if (!xdr_opaque(xdrs, objp->key, 32))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_HmacSha256Key(XDR *xdrs, HmacSha256Key *objp) {
  if (!xdr_opaque(xdrs, objp->key, 32))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_HmacSha256Mac(XDR *xdrs, HmacSha256Mac *objp) {
  if (!xdr_opaque(xdrs, objp->mac, 32))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_Value(XDR *xdrs, Value *objp) {
  if (!xdr_bytes(xdrs, (char **)&objp->Value_val, (u_int *)&objp->Value_len,
                 ~0))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SCPBallot(XDR *xdrs, SCPBallot *objp) {
  if (!xdr_uint32(xdrs, &objp->counter))
    return (FALSE);
  if (!xdr_Value(xdrs, &objp->value))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SCPStatementType(XDR *xdrs, SCPStatementType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SCPNomination(XDR *xdrs, SCPNomination *objp) {
  if (!xdr_Hash(xdrs, objp->quorumSetHash))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->votes.votes_val,
                 (u_int *)&objp->votes.votes_len, ~0, sizeof(Value),
                 (xdrproc_t)xdr_Value))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->accepted.accepted_val,
                 (u_int *)&objp->accepted.accepted_len, ~0, sizeof(Value),
                 (xdrproc_t)xdr_Value))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SCPPrepare(XDR *xdrs, SCPPrepare *objp) {
  if (!xdr_Hash(xdrs, objp->quorumSetHash))
    return (FALSE);
  if (!xdr_SCPBallot(xdrs, &objp->ballot))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->prepared, sizeof(SCPBallot),
                   (xdrproc_t)xdr_SCPBallot))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->preparedPrime, sizeof(SCPBallot),
                   (xdrproc_t)xdr_SCPBallot))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->nC))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->nH))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SCPConfirm(XDR *xdrs, SCPConfirm *objp) {
  if (!xdr_SCPBallot(xdrs, &objp->ballot))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->nPrepared))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->nCommit))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->nH))
    return (FALSE);
  if (!xdr_Hash(xdrs, objp->quorumSetHash))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SCPExternalize(XDR *xdrs, SCPExternalize *objp) {
  if (!xdr_SCPBallot(xdrs, &objp->commit))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->nH))
    return (FALSE);
  if (!xdr_Hash(xdrs, objp->commitQuorumSetHash))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SCPStatementPledges(XDR *xdrs, SCPStatementPledges *objp) {
  if (!xdr_SCPStatementType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case SCP_ST_PREPARE:
    if (!xdr_SCPPrepare(xdrs, &objp->SCPStatementPledges_u.prepare))
      return (FALSE);
    break;
  case SCP_ST_CONFIRM:
    if (!xdr_SCPConfirm(xdrs, &objp->SCPStatementPledges_u.confirm))
      return (FALSE);
    break;
  case SCP_ST_EXTERNALIZE:
    if (!xdr_SCPExternalize(xdrs, &objp->SCPStatementPledges_u.externalize))
      return (FALSE);
    break;
  case SCP_ST_NOMINATE:
    if (!xdr_SCPNomination(xdrs, &objp->SCPStatementPledges_u.nominate))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_SCPStatement(XDR *xdrs, SCPStatement *objp) {
  if (!xdr_NodeID(xdrs, &objp->nodeID))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->slotIndex))
    return (FALSE);
  if (!xdr_SCPStatementPledges(xdrs, &objp->pledges))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SCPEnvelope(XDR *xdrs, SCPEnvelope *objp) {
  if (!xdr_SCPStatement(xdrs, &objp->statement))
    return (FALSE);
  if (!xdr_Signature(xdrs, &objp->signature))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SCPQuorumSet(XDR *xdrs, SCPQuorumSet *objp) {
  if (!xdr_uint32(xdrs, &objp->threshold))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->validators.validators_val,
                 (u_int *)&objp->validators.validators_len, ~0, sizeof(NodeID),
                 (xdrproc_t)xdr_NodeID))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->innerSets.innerSets_val,
                 (u_int *)&objp->innerSets.innerSets_len, ~0,
                 sizeof(SCPQuorumSet), (xdrproc_t)xdr_SCPQuorumSet))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AccountID(XDR *xdrs, AccountID *objp) {
  if (!xdr_PublicKey(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_Thresholds(XDR *xdrs, Thresholds objp) {
  if (!xdr_opaque(xdrs, objp, 4))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_string32(XDR *xdrs, string32 *objp) {
  if (!xdr_string(xdrs, objp, 32))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_string64(XDR *xdrs, string64 *objp) {
  if (!xdr_string(xdrs, objp, 64))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SequenceNumber(XDR *xdrs, SequenceNumber *objp) {
  if (!xdr_int64(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TimePoint(XDR *xdrs, TimePoint *objp) {
  if (!xdr_uint64(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_DataValue(XDR *xdrs, DataValue *objp) {
  if (!xdr_bytes(xdrs, (char **)&objp->DataValue_val,
                 (u_int *)&objp->DataValue_len, 64))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_PoolID(XDR *xdrs, PoolID objp) {
  if (!xdr_Hash(xdrs, objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AssetCode4(XDR *xdrs, AssetCode4 objp) {
  if (!xdr_opaque(xdrs, objp, 4))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AssetCode12(XDR *xdrs, AssetCode12 objp) {
  if (!xdr_opaque(xdrs, objp, 12))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AssetType(XDR *xdrs, AssetType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AssetCode(XDR *xdrs, AssetCode *objp) {
  if (!xdr_AssetType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case ASSET_TYPE_CREDIT_ALPHANUM4:
    if (!xdr_AssetCode4(xdrs, objp->AssetCode_u.assetCode4))
      return (FALSE);
    break;
  case ASSET_TYPE_CREDIT_ALPHANUM12:
    if (!xdr_AssetCode12(xdrs, objp->AssetCode_u.assetCode12))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_AlphaNum4(XDR *xdrs, AlphaNum4 *objp) {
  if (!xdr_AssetCode4(xdrs, objp->assetCode))
    return (FALSE);
  if (!xdr_AccountID(xdrs, &objp->issuer))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AlphaNum12(XDR *xdrs, AlphaNum12 *objp) {
  if (!xdr_AssetCode12(xdrs, objp->assetCode))
    return (FALSE);
  if (!xdr_AccountID(xdrs, &objp->issuer))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_Asset(XDR *xdrs, Asset *objp) {
  if (!xdr_AssetType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case ASSET_TYPE_NATIVE:
    break;
  case ASSET_TYPE_CREDIT_ALPHANUM4:
    if (!xdr_AlphaNum4(xdrs, &objp->Asset_u.alphaNum4))
      return (FALSE);
    break;
  case ASSET_TYPE_CREDIT_ALPHANUM12:
    if (!xdr_AlphaNum12(xdrs, &objp->Asset_u.alphaNum12))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_Price(XDR *xdrs, Price *objp) {
  if (!xdr_int32(xdrs, &objp->n))
    return (FALSE);
  if (!xdr_int32(xdrs, &objp->d))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_Liabilities(XDR *xdrs, Liabilities *objp) {
  if (!xdr_int64(xdrs, &objp->buying))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->selling))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ThresholdIndexes(XDR *xdrs, ThresholdIndexes *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerEntryType(XDR *xdrs, LedgerEntryType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_Signer(XDR *xdrs, Signer *objp) {
  if (!xdr_SignerKey(xdrs, &objp->key))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->weight))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AccountFlags(XDR *xdrs, AccountFlags *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SponsorshipDescriptor(XDR *xdrs, SponsorshipDescriptor *objp) {
  if (!xdr_pointer(xdrs, (char **)objp, sizeof(AccountID),
                   (xdrproc_t)xdr_AccountID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AccountEntryExtensionV2Ext(XDR *xdrs,
                                      AccountEntryExtensionV2Ext *objp) {
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

bool_t xdr_AccountEntryExtensionV2(XDR *xdrs, AccountEntryExtensionV2 *objp) {
  if (!xdr_uint32(xdrs, &objp->numSponsored))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->numSponsoring))
    return (FALSE);
  if (!xdr_array(xdrs,
                 (char **)&objp->signerSponsoringIDs.signerSponsoringIDs_val,
                 (u_int *)&objp->signerSponsoringIDs.signerSponsoringIDs_len,
                 MAX_SIGNERS, sizeof(SponsorshipDescriptor),
                 (xdrproc_t)xdr_SponsorshipDescriptor))
    return (FALSE);
  if (!xdr_AccountEntryExtensionV2Ext(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AccountEntryExtensionV1Ext(XDR *xdrs,
                                      AccountEntryExtensionV1Ext *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  case 2:
    if (!xdr_AccountEntryExtensionV2(xdrs,
                                     &objp->AccountEntryExtensionV1Ext_u.v2))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_AccountEntryExtensionV1(XDR *xdrs, AccountEntryExtensionV1 *objp) {
  if (!xdr_Liabilities(xdrs, &objp->liabilities))
    return (FALSE);
  if (!xdr_AccountEntryExtensionV1Ext(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AccountEntryExt(XDR *xdrs, AccountEntryExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  case 1:
    if (!xdr_AccountEntryExtensionV1(xdrs, &objp->AccountEntryExt_u.v1))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_AccountEntry(XDR *xdrs, AccountEntry *objp) {
  if (!xdr_AccountID(xdrs, &objp->accountID))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->balance))
    return (FALSE);
  if (!xdr_SequenceNumber(xdrs, &objp->seqNum))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->numSubEntries))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->inflationDest, sizeof(AccountID),
                   (xdrproc_t)xdr_AccountID))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->flags))
    return (FALSE);
  if (!xdr_string32(xdrs, &objp->homeDomain))
    return (FALSE);
  if (!xdr_Thresholds(xdrs, objp->thresholds))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->signers.signers_val,
                 (u_int *)&objp->signers.signers_len, MAX_SIGNERS,
                 sizeof(Signer), (xdrproc_t)xdr_Signer))
    return (FALSE);
  if (!xdr_AccountEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TrustLineFlags(XDR *xdrs, TrustLineFlags *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LiquidityPoolType(XDR *xdrs, LiquidityPoolType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TrustLineAsset(XDR *xdrs, TrustLineAsset *objp) {
  if (!xdr_AssetType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case ASSET_TYPE_NATIVE:
    break;
  case ASSET_TYPE_CREDIT_ALPHANUM4:
    if (!xdr_AlphaNum4(xdrs, &objp->TrustLineAsset_u.alphaNum4))
      return (FALSE);
    break;
  case ASSET_TYPE_CREDIT_ALPHANUM12:
    if (!xdr_AlphaNum12(xdrs, &objp->TrustLineAsset_u.alphaNum12))
      return (FALSE);
    break;
  case ASSET_TYPE_POOL_SHARE:
    if (!xdr_PoolID(xdrs, objp->TrustLineAsset_u.liquidityPoolID))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_TrustLineEntryExtensionV2Ext(XDR *xdrs,
                                        TrustLineEntryExtensionV2Ext *objp) {
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

bool_t xdr_TrustLineEntryExtensionV2(XDR *xdrs,
                                     TrustLineEntryExtensionV2 *objp) {
  if (!xdr_int32(xdrs, &objp->liquidityPoolUseCount))
    return (FALSE);
  if (!xdr_TrustLineEntryExtensionV2Ext(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TrustLineEntryV1Ext(XDR *xdrs, TrustLineEntryV1Ext *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  case 2:
    if (!xdr_TrustLineEntryExtensionV2(xdrs, &objp->TrustLineEntryV1Ext_u.v2))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_TrustLineEntryV1(XDR *xdrs, TrustLineEntryV1 *objp) {
  if (!xdr_Liabilities(xdrs, &objp->liabilities))
    return (FALSE);
  if (!xdr_TrustLineEntryV1Ext(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TrustLineEntryExt(XDR *xdrs, TrustLineEntryExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  case 1:
    if (!xdr_TrustLineEntryV1(xdrs, &objp->TrustLineEntryExt_u.v1))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_TrustLineEntry(XDR *xdrs, TrustLineEntry *objp) {
  if (!xdr_AccountID(xdrs, &objp->accountID))
    return (FALSE);
  if (!xdr_TrustLineAsset(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->balance))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->limit))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->flags))
    return (FALSE);
  if (!xdr_TrustLineEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_OfferEntryFlags(XDR *xdrs, OfferEntryFlags *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_OfferEntryExt(XDR *xdrs, OfferEntryExt *objp) {
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

bool_t xdr_OfferEntry(XDR *xdrs, OfferEntry *objp) {
  if (!xdr_AccountID(xdrs, &objp->sellerID))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->offerID))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->selling))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->buying))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amount))
    return (FALSE);
  if (!xdr_Price(xdrs, &objp->price))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->flags))
    return (FALSE);
  if (!xdr_OfferEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_DataEntryExt(XDR *xdrs, DataEntryExt *objp) {
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

bool_t xdr_DataEntry(XDR *xdrs, DataEntry *objp) {
  if (!xdr_AccountID(xdrs, &objp->accountID))
    return (FALSE);
  if (!xdr_string64(xdrs, &objp->dataName))
    return (FALSE);
  if (!xdr_DataValue(xdrs, &objp->dataValue))
    return (FALSE);
  if (!xdr_DataEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClaimPredicateType(XDR *xdrs, ClaimPredicateType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClaimPredicate(XDR *xdrs, ClaimPredicate *objp) {
  if (!xdr_ClaimPredicateType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case CLAIM_PREDICATE_UNCONDITIONAL:
    break;
  case CLAIM_PREDICATE_AND:
    if (!xdr_array(
            xdrs,
            (char **)&objp->ClaimPredicate_u.andPredicates.andPredicates_val,
            (u_int *)&objp->ClaimPredicate_u.andPredicates.andPredicates_len, 2,
            sizeof(ClaimPredicate), (xdrproc_t)xdr_ClaimPredicate))
      return (FALSE);
    break;
  case CLAIM_PREDICATE_OR:
    if (!xdr_array(
            xdrs,
            (char **)&objp->ClaimPredicate_u.orPredicates.orPredicates_val,
            (u_int *)&objp->ClaimPredicate_u.orPredicates.orPredicates_len, 2,
            sizeof(ClaimPredicate), (xdrproc_t)xdr_ClaimPredicate))
      return (FALSE);
    break;
  case CLAIM_PREDICATE_NOT:
    if (!xdr_pointer(xdrs, (char **)&objp->ClaimPredicate_u.notPredicate,
                     sizeof(ClaimPredicate), (xdrproc_t)xdr_ClaimPredicate))
      return (FALSE);
    break;
  case CLAIM_PREDICATE_BEFORE_ABSOLUTE_TIME:
    if (!xdr_int64(xdrs, &objp->ClaimPredicate_u.absBefore))
      return (FALSE);
    break;
  case CLAIM_PREDICATE_BEFORE_RELATIVE_TIME:
    if (!xdr_int64(xdrs, &objp->ClaimPredicate_u.relBefore))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_ClaimantType(XDR *xdrs, ClaimantType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClaimantV0(XDR *xdrs, ClaimantV0 *objp) {
  if (!xdr_AccountID(xdrs, &objp->destination))
    return (FALSE);
  if (!xdr_ClaimPredicate(xdrs, &objp->predicate))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_Claimant(XDR *xdrs, Claimant *objp) {
  if (!xdr_ClaimantType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case CLAIMANT_TYPE_V0:
    if (!xdr_ClaimantV0(xdrs, &objp->Claimant_u.v0))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_ClaimableBalanceIDType(XDR *xdrs, ClaimableBalanceIDType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClaimableBalanceID(XDR *xdrs, ClaimableBalanceID *objp) {
  if (!xdr_ClaimableBalanceIDType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case CLAIMABLE_BALANCE_ID_TYPE_V0:
    if (!xdr_Hash(xdrs, objp->ClaimableBalanceID_u.v0))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_ClaimableBalanceFlags(XDR *xdrs, ClaimableBalanceFlags *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClaimableBalanceEntryExtensionV1Ext(
    XDR *xdrs, ClaimableBalanceEntryExtensionV1Ext *objp) {
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
xdr_ClaimableBalanceEntryExtensionV1(XDR *xdrs,
                                     ClaimableBalanceEntryExtensionV1 *objp) {
  if (!xdr_ClaimableBalanceEntryExtensionV1Ext(xdrs, &objp->ext))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->flags))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClaimableBalanceEntryExt(XDR *xdrs, ClaimableBalanceEntryExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  case 1:
    if (!xdr_ClaimableBalanceEntryExtensionV1(
            xdrs, &objp->ClaimableBalanceEntryExt_u.v1))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_ClaimableBalanceEntry(XDR *xdrs, ClaimableBalanceEntry *objp) {
  if (!xdr_ClaimableBalanceID(xdrs, &objp->balanceID))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->claimants.claimants_val,
                 (u_int *)&objp->claimants.claimants_len, 10, sizeof(Claimant),
                 (xdrproc_t)xdr_Claimant))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amount))
    return (FALSE);
  if (!xdr_ClaimableBalanceEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LiquidityPoolConstantProductParameters(
    XDR *xdrs, LiquidityPoolConstantProductParameters *objp) {
  if (!xdr_Asset(xdrs, &objp->assetA))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->assetB))
    return (FALSE);
  if (!xdr_int32(xdrs, &objp->fee))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_LiquidityPoolEntryConstantProduct(XDR *xdrs,
                                      LiquidityPoolEntryConstantProduct *objp) {
  if (!xdr_LiquidityPoolConstantProductParameters(xdrs, &objp->params))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->reserveA))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->reserveB))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->totalPoolShares))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->poolSharesTrustLineCount))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LiquidityPoolEntryBody(XDR *xdrs, LiquidityPoolEntryBody *objp) {
  if (!xdr_LiquidityPoolType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case LIQUIDITY_POOL_CONSTANT_PRODUCT:
    if (!xdr_LiquidityPoolEntryConstantProduct(
            xdrs, &objp->LiquidityPoolEntryBody_u.constantProduct))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_LiquidityPoolEntry(XDR *xdrs, LiquidityPoolEntry *objp) {
  if (!xdr_PoolID(xdrs, objp->liquidityPoolID))
    return (FALSE);
  if (!xdr_LiquidityPoolEntryBody(xdrs, &objp->body))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerEntryExtensionV1Ext(XDR *xdrs,
                                     LedgerEntryExtensionV1Ext *objp) {
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

bool_t xdr_LedgerEntryExtensionV1(XDR *xdrs, LedgerEntryExtensionV1 *objp) {
  if (!xdr_SponsorshipDescriptor(xdrs, &objp->sponsoringID))
    return (FALSE);
  if (!xdr_LedgerEntryExtensionV1Ext(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerEntryData(XDR *xdrs, LedgerEntryData *objp) {
  if (!xdr_LedgerEntryType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case ACCOUNT:
    if (!xdr_AccountEntry(xdrs, &objp->LedgerEntryData_u.account))
      return (FALSE);
    break;
  case TRUSTLINE:
    if (!xdr_TrustLineEntry(xdrs, &objp->LedgerEntryData_u.trustLine))
      return (FALSE);
    break;
  case OFFER:
    if (!xdr_OfferEntry(xdrs, &objp->LedgerEntryData_u.offer))
      return (FALSE);
    break;
  case DATA:
    if (!xdr_DataEntry(xdrs, &objp->LedgerEntryData_u.data))
      return (FALSE);
    break;
  case CLAIMABLE_BALANCE:
    if (!xdr_ClaimableBalanceEntry(xdrs,
                                   &objp->LedgerEntryData_u.claimableBalance))
      return (FALSE);
    break;
  case LIQUIDITY_POOL:
    if (!xdr_LiquidityPoolEntry(xdrs, &objp->LedgerEntryData_u.liquidityPool))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_LedgerEntryExt(XDR *xdrs, LedgerEntryExt *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    break;
  case 1:
    if (!xdr_LedgerEntryExtensionV1(xdrs, &objp->LedgerEntryExt_u.v1))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_LedgerEntry(XDR *xdrs, LedgerEntry *objp) {
  if (!xdr_uint32(xdrs, &objp->lastModifiedLedgerSeq))
    return (FALSE);
  if (!xdr_LedgerEntryData(xdrs, &objp->data))
    return (FALSE);
  if (!xdr_LedgerEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerKeyAccount(XDR *xdrs, LedgerKeyAccount *objp) {
  if (!xdr_AccountID(xdrs, &objp->accountID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerKeyTrustLine(XDR *xdrs, LedgerKeyTrustLine *objp) {
  if (!xdr_AccountID(xdrs, &objp->accountID))
    return (FALSE);
  if (!xdr_TrustLineAsset(xdrs, &objp->asset))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerKeyOffer(XDR *xdrs, LedgerKeyOffer *objp) {
  if (!xdr_AccountID(xdrs, &objp->sellerID))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->offerID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerKeyData(XDR *xdrs, LedgerKeyData *objp) {
  if (!xdr_AccountID(xdrs, &objp->accountID))
    return (FALSE);
  if (!xdr_string64(xdrs, &objp->dataName))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerKeyClaimableBalance(XDR *xdrs,
                                     LedgerKeyClaimableBalance *objp) {
  if (!xdr_ClaimableBalanceID(xdrs, &objp->balanceID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerKeyLiquidityPool(XDR *xdrs, LedgerKeyLiquidityPool *objp) {
  if (!xdr_PoolID(xdrs, objp->liquidityPoolID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerKey(XDR *xdrs, LedgerKey *objp) {
  if (!xdr_LedgerEntryType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case ACCOUNT:
    if (!xdr_LedgerKeyAccount(xdrs, &objp->LedgerKey_u.account))
      return (FALSE);
    break;
  case TRUSTLINE:
    if (!xdr_LedgerKeyTrustLine(xdrs, &objp->LedgerKey_u.trustLine))
      return (FALSE);
    break;
  case OFFER:
    if (!xdr_LedgerKeyOffer(xdrs, &objp->LedgerKey_u.offer))
      return (FALSE);
    break;
  case DATA:
    if (!xdr_LedgerKeyData(xdrs, &objp->LedgerKey_u.data))
      return (FALSE);
    break;
  case CLAIMABLE_BALANCE:
    if (!xdr_LedgerKeyClaimableBalance(xdrs,
                                       &objp->LedgerKey_u.claimableBalance))
      return (FALSE);
    break;
  case LIQUIDITY_POOL:
    if (!xdr_LedgerKeyLiquidityPool(xdrs, &objp->LedgerKey_u.liquidityPool))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_EnvelopeType(XDR *xdrs, EnvelopeType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LiquidityPoolParameters(XDR *xdrs, LiquidityPoolParameters *objp) {
  if (!xdr_LiquidityPoolType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case LIQUIDITY_POOL_CONSTANT_PRODUCT:
    if (!xdr_LiquidityPoolConstantProductParameters(
            xdrs, &objp->LiquidityPoolParameters_u.constantProduct))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_MuxedAccountMed25519(XDR *xdrs, MuxedAccountMed25519 *objp) {
  if (!xdr_uint64(xdrs, &objp->id))
    return (FALSE);
  if (!xdr_uint256(xdrs, objp->ed25519))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_MuxedAccount(XDR *xdrs, MuxedAccount *objp) {
  if (!xdr_CryptoKeyType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case KEY_TYPE_ED25519:
    if (!xdr_uint256(xdrs, objp->MuxedAccount_u.ed25519))
      return (FALSE);
    break;
  case KEY_TYPE_MUXED_ED25519:
    if (!xdr_MuxedAccountMed25519(xdrs, &objp->MuxedAccount_u.med25519))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_DecoratedSignature(XDR *xdrs, DecoratedSignature *objp) {
  if (!xdr_SignatureHint(xdrs, objp->hint))
    return (FALSE);
  if (!xdr_Signature(xdrs, &objp->signature))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_OperationType(XDR *xdrs, OperationType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_CreateAccountOp(XDR *xdrs, CreateAccountOp *objp) {
  if (!xdr_AccountID(xdrs, &objp->destination))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->startingBalance))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_PaymentOp(XDR *xdrs, PaymentOp *objp) {
  if (!xdr_MuxedAccount(xdrs, &objp->destination))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amount))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_PathPaymentStrictReceiveOp(XDR *xdrs,
                                      PathPaymentStrictReceiveOp *objp) {
  if (!xdr_Asset(xdrs, &objp->sendAsset))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->sendMax))
    return (FALSE);
  if (!xdr_MuxedAccount(xdrs, &objp->destination))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->destAsset))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->destAmount))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->path.path_val,
                 (u_int *)&objp->path.path_len, 5, sizeof(Asset),
                 (xdrproc_t)xdr_Asset))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_PathPaymentStrictSendOp(XDR *xdrs, PathPaymentStrictSendOp *objp) {
  if (!xdr_Asset(xdrs, &objp->sendAsset))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->sendAmount))
    return (FALSE);
  if (!xdr_MuxedAccount(xdrs, &objp->destination))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->destAsset))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->destMin))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->path.path_val,
                 (u_int *)&objp->path.path_len, 5, sizeof(Asset),
                 (xdrproc_t)xdr_Asset))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ManageSellOfferOp(XDR *xdrs, ManageSellOfferOp *objp) {
  if (!xdr_Asset(xdrs, &objp->selling))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->buying))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amount))
    return (FALSE);
  if (!xdr_Price(xdrs, &objp->price))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->offerID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ManageBuyOfferOp(XDR *xdrs, ManageBuyOfferOp *objp) {
  if (!xdr_Asset(xdrs, &objp->selling))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->buying))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->buyAmount))
    return (FALSE);
  if (!xdr_Price(xdrs, &objp->price))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->offerID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_CreatePassiveSellOfferOp(XDR *xdrs, CreatePassiveSellOfferOp *objp) {
  if (!xdr_Asset(xdrs, &objp->selling))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->buying))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amount))
    return (FALSE);
  if (!xdr_Price(xdrs, &objp->price))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SetOptionsOp(XDR *xdrs, SetOptionsOp *objp) {
  if (!xdr_pointer(xdrs, (char **)&objp->inflationDest, sizeof(AccountID),
                   (xdrproc_t)xdr_AccountID))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->clearFlags, sizeof(uint32),
                   (xdrproc_t)xdr_uint32))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->setFlags, sizeof(uint32),
                   (xdrproc_t)xdr_uint32))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->masterWeight, sizeof(uint32),
                   (xdrproc_t)xdr_uint32))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->lowThreshold, sizeof(uint32),
                   (xdrproc_t)xdr_uint32))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->medThreshold, sizeof(uint32),
                   (xdrproc_t)xdr_uint32))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->highThreshold, sizeof(uint32),
                   (xdrproc_t)xdr_uint32))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->homeDomain, sizeof(string32),
                   (xdrproc_t)xdr_string32))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->signer, sizeof(Signer),
                   (xdrproc_t)xdr_Signer))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ChangeTrustAsset(XDR *xdrs, ChangeTrustAsset *objp) {
  if (!xdr_AssetType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case ASSET_TYPE_NATIVE:
    break;
  case ASSET_TYPE_CREDIT_ALPHANUM4:
    if (!xdr_AlphaNum4(xdrs, &objp->ChangeTrustAsset_u.alphaNum4))
      return (FALSE);
    break;
  case ASSET_TYPE_CREDIT_ALPHANUM12:
    if (!xdr_AlphaNum12(xdrs, &objp->ChangeTrustAsset_u.alphaNum12))
      return (FALSE);
    break;
  case ASSET_TYPE_POOL_SHARE:
    if (!xdr_LiquidityPoolParameters(xdrs,
                                     &objp->ChangeTrustAsset_u.liquidityPool))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_ChangeTrustOp(XDR *xdrs, ChangeTrustOp *objp) {
  if (!xdr_ChangeTrustAsset(xdrs, &objp->line))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->limit))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AllowTrustOp(XDR *xdrs, AllowTrustOp *objp) {
  if (!xdr_AccountID(xdrs, &objp->trustor))
    return (FALSE);
  if (!xdr_AssetCode(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->authorize))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ManageDataOp(XDR *xdrs, ManageDataOp *objp) {
  if (!xdr_string64(xdrs, &objp->dataName))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->dataValue, sizeof(DataValue),
                   (xdrproc_t)xdr_DataValue))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_BumpSequenceOp(XDR *xdrs, BumpSequenceOp *objp) {
  if (!xdr_SequenceNumber(xdrs, &objp->bumpTo))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_CreateClaimableBalanceOp(XDR *xdrs, CreateClaimableBalanceOp *objp) {
  if (!xdr_Asset(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amount))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->claimants.claimants_val,
                 (u_int *)&objp->claimants.claimants_len, 10, sizeof(Claimant),
                 (xdrproc_t)xdr_Claimant))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClaimClaimableBalanceOp(XDR *xdrs, ClaimClaimableBalanceOp *objp) {
  if (!xdr_ClaimableBalanceID(xdrs, &objp->balanceID))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_BeginSponsoringFutureReservesOp(XDR *xdrs,
                                    BeginSponsoringFutureReservesOp *objp) {
  if (!xdr_AccountID(xdrs, &objp->sponsoredID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_RevokeSponsorshipType(XDR *xdrs, RevokeSponsorshipType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_RevokeSponsorshipOpSigner(XDR *xdrs,
                                     RevokeSponsorshipOpSigner *objp) {
  if (!xdr_AccountID(xdrs, &objp->accountID))
    return (FALSE);
  if (!xdr_SignerKey(xdrs, &objp->signerKey))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_RevokeSponsorshipOp(XDR *xdrs, RevokeSponsorshipOp *objp) {
  if (!xdr_RevokeSponsorshipType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case REVOKE_SPONSORSHIP_LEDGER_ENTRY:
    if (!xdr_LedgerKey(xdrs, &objp->RevokeSponsorshipOp_u.ledgerKey))
      return (FALSE);
    break;
  case REVOKE_SPONSORSHIP_SIGNER:
    if (!xdr_RevokeSponsorshipOpSigner(xdrs,
                                       &objp->RevokeSponsorshipOp_u.signer))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_ClawbackOp(XDR *xdrs, ClawbackOp *objp) {
  if (!xdr_Asset(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_MuxedAccount(xdrs, &objp->from_))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amount))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClawbackClaimableBalanceOp(XDR *xdrs,
                                      ClawbackClaimableBalanceOp *objp) {
  if (!xdr_ClaimableBalanceID(xdrs, &objp->balanceID))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SetTrustLineFlagsOp(XDR *xdrs, SetTrustLineFlagsOp *objp) {
  if (!xdr_AccountID(xdrs, &objp->trustor))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->clearFlags))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->setFlags))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LiquidityPoolDepositOp(XDR *xdrs, LiquidityPoolDepositOp *objp) {
  if (!xdr_PoolID(xdrs, objp->liquidityPoolID))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->maxAmountA))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->maxAmountB))
    return (FALSE);
  if (!xdr_Price(xdrs, &objp->minPrice))
    return (FALSE);
  if (!xdr_Price(xdrs, &objp->maxPrice))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LiquidityPoolWithdrawOp(XDR *xdrs, LiquidityPoolWithdrawOp *objp) {
  if (!xdr_PoolID(xdrs, objp->liquidityPoolID))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amount))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->minAmountA))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->minAmountB))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_OperationBody(XDR *xdrs, OperationBody *objp) {
  if (!xdr_OperationType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case CREATE_ACCOUNT:
    if (!xdr_CreateAccountOp(xdrs, &objp->OperationBody_u.createAccountOp))
      return (FALSE);
    break;
  case PAYMENT:
    if (!xdr_PaymentOp(xdrs, &objp->OperationBody_u.paymentOp))
      return (FALSE);
    break;
  case PATH_PAYMENT_STRICT_RECEIVE:
    if (!xdr_PathPaymentStrictReceiveOp(
            xdrs, &objp->OperationBody_u.pathPaymentStrictReceiveOp))
      return (FALSE);
    break;
  case MANAGE_SELL_OFFER:
    if (!xdr_ManageSellOfferOp(xdrs, &objp->OperationBody_u.manageSellOfferOp))
      return (FALSE);
    break;
  case CREATE_PASSIVE_SELL_OFFER:
    if (!xdr_CreatePassiveSellOfferOp(
            xdrs, &objp->OperationBody_u.createPassiveSellOfferOp))
      return (FALSE);
    break;
  case SET_OPTIONS:
    if (!xdr_SetOptionsOp(xdrs, &objp->OperationBody_u.setOptionsOp))
      return (FALSE);
    break;
  case CHANGE_TRUST:
    if (!xdr_ChangeTrustOp(xdrs, &objp->OperationBody_u.changeTrustOp))
      return (FALSE);
    break;
  case ALLOW_TRUST:
    if (!xdr_AllowTrustOp(xdrs, &objp->OperationBody_u.allowTrustOp))
      return (FALSE);
    break;
  case ACCOUNT_MERGE:
    if (!xdr_MuxedAccount(xdrs, &objp->OperationBody_u.destination))
      return (FALSE);
    break;
  case INFLATION:
    break;
  case MANAGE_DATA:
    if (!xdr_ManageDataOp(xdrs, &objp->OperationBody_u.manageDataOp))
      return (FALSE);
    break;
  case BUMP_SEQUENCE:
    if (!xdr_BumpSequenceOp(xdrs, &objp->OperationBody_u.bumpSequenceOp))
      return (FALSE);
    break;
  case MANAGE_BUY_OFFER:
    if (!xdr_ManageBuyOfferOp(xdrs, &objp->OperationBody_u.manageBuyOfferOp))
      return (FALSE);
    break;
  case PATH_PAYMENT_STRICT_SEND:
    if (!xdr_PathPaymentStrictSendOp(
            xdrs, &objp->OperationBody_u.pathPaymentStrictSendOp))
      return (FALSE);
    break;
  case CREATE_CLAIMABLE_BALANCE:
    if (!xdr_CreateClaimableBalanceOp(
            xdrs, &objp->OperationBody_u.createClaimableBalanceOp))
      return (FALSE);
    break;
  case CLAIM_CLAIMABLE_BALANCE:
    if (!xdr_ClaimClaimableBalanceOp(
            xdrs, &objp->OperationBody_u.claimClaimableBalanceOp))
      return (FALSE);
    break;
  case BEGIN_SPONSORING_FUTURE_RESERVES:
    if (!xdr_BeginSponsoringFutureReservesOp(
            xdrs, &objp->OperationBody_u.beginSponsoringFutureReservesOp))
      return (FALSE);
    break;
  case END_SPONSORING_FUTURE_RESERVES:
    break;
  case REVOKE_SPONSORSHIP:
    if (!xdr_RevokeSponsorshipOp(xdrs,
                                 &objp->OperationBody_u.revokeSponsorshipOp))
      return (FALSE);
    break;
  case CLAWBACK:
    if (!xdr_ClawbackOp(xdrs, &objp->OperationBody_u.clawbackOp))
      return (FALSE);
    break;
  case CLAWBACK_CLAIMABLE_BALANCE:
    if (!xdr_ClawbackClaimableBalanceOp(
            xdrs, &objp->OperationBody_u.clawbackClaimableBalanceOp))
      return (FALSE);
    break;
  case SET_TRUST_LINE_FLAGS:
    if (!xdr_SetTrustLineFlagsOp(xdrs,
                                 &objp->OperationBody_u.setTrustLineFlagsOp))
      return (FALSE);
    break;
  case LIQUIDITY_POOL_DEPOSIT:
    if (!xdr_LiquidityPoolDepositOp(
            xdrs, &objp->OperationBody_u.liquidityPoolDepositOp))
      return (FALSE);
    break;
  case LIQUIDITY_POOL_WITHDRAW:
    if (!xdr_LiquidityPoolWithdrawOp(
            xdrs, &objp->OperationBody_u.liquidityPoolWithdrawOp))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_Operation(XDR *xdrs, Operation *objp) {
  if (!xdr_pointer(xdrs, (char **)&objp->sourceAccount, sizeof(MuxedAccount),
                   (xdrproc_t)xdr_MuxedAccount))
    return (FALSE);
  if (!xdr_OperationBody(xdrs, &objp->body))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_EnvelopeTypeOperationID(XDR *xdrs, EnvelopeTypeOperationID *objp) {
  if (!xdr_AccountID(xdrs, &objp->sourceAccount))
    return (FALSE);
  if (!xdr_SequenceNumber(xdrs, &objp->seqNum))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->opNum))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_OperationID(XDR *xdrs, OperationID *objp) {
  if (!xdr_EnvelopeType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case ENVELOPE_TYPE_OP_ID:
    if (!xdr_EnvelopeTypeOperationID(xdrs, &objp->OperationID_u.id))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_MemoType(XDR *xdrs, MemoType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_Memo(XDR *xdrs, Memo *objp) {
  if (!xdr_MemoType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case MEMO_NONE:
    break;
  case MEMO_TEXT:
    if (!xdr_string(xdrs, &objp->Memo_u.text, 28))
      return (FALSE);
    break;
  case MEMO_ID:
    if (!xdr_uint64(xdrs, &objp->Memo_u.id))
      return (FALSE);
    break;
  case MEMO_HASH:
    if (!xdr_Hash(xdrs, objp->Memo_u.hash))
      return (FALSE);
    break;
  case MEMO_RETURN:
    if (!xdr_Hash(xdrs, objp->Memo_u.retHash))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_TimeBounds(XDR *xdrs, TimeBounds *objp) {
  if (!xdr_TimePoint(xdrs, &objp->minTime))
    return (FALSE);
  if (!xdr_TimePoint(xdrs, &objp->maxTime))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TransactionV0Ext(XDR *xdrs, TransactionV0Ext *objp) {
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

bool_t xdr_TransactionV0(XDR *xdrs, TransactionV0 *objp) {
  if (!xdr_uint256(xdrs, objp->sourceAccountEd25519))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->fee))
    return (FALSE);
  if (!xdr_SequenceNumber(xdrs, &objp->seqNum))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->timeBounds, sizeof(TimeBounds),
                   (xdrproc_t)xdr_TimeBounds))
    return (FALSE);
  if (!xdr_Memo(xdrs, &objp->memo))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->operations.operations_val,
                 (u_int *)&objp->operations.operations_len, MAX_OPS_PER_TX,
                 sizeof(Operation), (xdrproc_t)xdr_Operation))
    return (FALSE);
  if (!xdr_TransactionV0Ext(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TransactionV0Envelope(XDR *xdrs, TransactionV0Envelope *objp) {
  if (!xdr_TransactionV0(xdrs, &objp->tx))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->signatures.signatures_val,
                 (u_int *)&objp->signatures.signatures_len, 20,
                 sizeof(DecoratedSignature), (xdrproc_t)xdr_DecoratedSignature))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TransactionExt(XDR *xdrs, TransactionExt *objp) {
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

bool_t xdr_Transaction(XDR *xdrs, Transaction *objp) {
  if (!xdr_MuxedAccount(xdrs, &objp->sourceAccount))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->fee))
    return (FALSE);
  if (!xdr_SequenceNumber(xdrs, &objp->seqNum))
    return (FALSE);
  if (!xdr_pointer(xdrs, (char **)&objp->timeBounds, sizeof(TimeBounds),
                   (xdrproc_t)xdr_TimeBounds))
    return (FALSE);
  if (!xdr_Memo(xdrs, &objp->memo))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->operations.operations_val,
                 (u_int *)&objp->operations.operations_len, MAX_OPS_PER_TX,
                 sizeof(Operation), (xdrproc_t)xdr_Operation))
    return (FALSE);
  if (!xdr_TransactionExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TransactionV1Envelope(XDR *xdrs, TransactionV1Envelope *objp) {
  if (!xdr_Transaction(xdrs, &objp->tx))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->signatures.signatures_val,
                 (u_int *)&objp->signatures.signatures_len, 20,
                 sizeof(DecoratedSignature), (xdrproc_t)xdr_DecoratedSignature))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_FeeBumpTransactionInnerTx(XDR *xdrs,
                                     FeeBumpTransactionInnerTx *objp) {
  if (!xdr_EnvelopeType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case ENVELOPE_TYPE_TX:
    if (!xdr_TransactionV1Envelope(xdrs, &objp->FeeBumpTransactionInnerTx_u.v1))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_FeeBumpTransactionExt(XDR *xdrs, FeeBumpTransactionExt *objp) {
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

bool_t xdr_FeeBumpTransaction(XDR *xdrs, FeeBumpTransaction *objp) {
  if (!xdr_MuxedAccount(xdrs, &objp->feeSource))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->fee))
    return (FALSE);
  if (!xdr_FeeBumpTransactionInnerTx(xdrs, &objp->innerTx))
    return (FALSE);
  if (!xdr_FeeBumpTransactionExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_FeeBumpTransactionEnvelope(XDR *xdrs,
                                      FeeBumpTransactionEnvelope *objp) {
  if (!xdr_FeeBumpTransaction(xdrs, &objp->tx))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->signatures.signatures_val,
                 (u_int *)&objp->signatures.signatures_len, 20,
                 sizeof(DecoratedSignature), (xdrproc_t)xdr_DecoratedSignature))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TransactionEnvelope(XDR *xdrs, TransactionEnvelope *objp) {
  if (!xdr_EnvelopeType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case ENVELOPE_TYPE_TX_V0:
    if (!xdr_TransactionV0Envelope(xdrs, &objp->TransactionEnvelope_u.v0))
      return (FALSE);
    break;
  case ENVELOPE_TYPE_TX:
    if (!xdr_TransactionV1Envelope(xdrs, &objp->TransactionEnvelope_u.v1))
      return (FALSE);
    break;
  case ENVELOPE_TYPE_TX_FEE_BUMP:
    if (!xdr_FeeBumpTransactionEnvelope(xdrs,
                                        &objp->TransactionEnvelope_u.feeBump))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_TransactionSignaturePayloadTaggedTransaction(
    XDR *xdrs, TransactionSignaturePayloadTaggedTransaction *objp) {
  if (!xdr_EnvelopeType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case ENVELOPE_TYPE_TX:
    if (!xdr_Transaction(
            xdrs, &objp->TransactionSignaturePayloadTaggedTransaction_u.tx))
      return (FALSE);
    break;
  case ENVELOPE_TYPE_TX_FEE_BUMP:
    if (!xdr_FeeBumpTransaction(
            xdrs,
            &objp->TransactionSignaturePayloadTaggedTransaction_u.feeBump))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_TransactionSignaturePayload(XDR *xdrs,
                                       TransactionSignaturePayload *objp) {
  if (!xdr_Hash(xdrs, objp->networkId))
    return (FALSE);
  if (!xdr_TransactionSignaturePayloadTaggedTransaction(
          xdrs, &objp->taggedTransaction))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClaimAtomType(XDR *xdrs, ClaimAtomType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClaimOfferAtomV0(XDR *xdrs, ClaimOfferAtomV0 *objp) {
  if (!xdr_uint256(xdrs, objp->sellerEd25519))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->offerID))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->assetSold))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amountSold))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->assetBought))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amountBought))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClaimOfferAtom(XDR *xdrs, ClaimOfferAtom *objp) {
  if (!xdr_AccountID(xdrs, &objp->sellerID))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->offerID))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->assetSold))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amountSold))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->assetBought))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amountBought))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClaimLiquidityAtom(XDR *xdrs, ClaimLiquidityAtom *objp) {
  if (!xdr_PoolID(xdrs, objp->liquidityPoolID))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->assetSold))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amountSold))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->assetBought))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amountBought))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClaimAtom(XDR *xdrs, ClaimAtom *objp) {
  if (!xdr_ClaimAtomType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case CLAIM_ATOM_TYPE_V0:
    if (!xdr_ClaimOfferAtomV0(xdrs, &objp->ClaimAtom_u.v0))
      return (FALSE);
    break;
  case CLAIM_ATOM_TYPE_ORDER_BOOK:
    if (!xdr_ClaimOfferAtom(xdrs, &objp->ClaimAtom_u.orderBook))
      return (FALSE);
    break;
  case CLAIM_ATOM_TYPE_LIQUIDITY_POOL:
    if (!xdr_ClaimLiquidityAtom(xdrs, &objp->ClaimAtom_u.liquidityPool))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_CreateAccountResultCode(XDR *xdrs, CreateAccountResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_CreateAccountResult(XDR *xdrs, CreateAccountResult *objp) {
  if (!xdr_CreateAccountResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case CREATE_ACCOUNT_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_PaymentResultCode(XDR *xdrs, PaymentResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_PaymentResult(XDR *xdrs, PaymentResult *objp) {
  if (!xdr_PaymentResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case PAYMENT_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_PathPaymentStrictReceiveResultCode(
    XDR *xdrs, PathPaymentStrictReceiveResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SimplePaymentResult(XDR *xdrs, SimplePaymentResult *objp) {
  if (!xdr_AccountID(xdrs, &objp->destination))
    return (FALSE);
  if (!xdr_Asset(xdrs, &objp->asset))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amount))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_PathPaymentStrictReceiveResultSuccess(
    XDR *xdrs, PathPaymentStrictReceiveResultSuccess *objp) {
  if (!xdr_array(xdrs, (char **)&objp->offers.offers_val,
                 (u_int *)&objp->offers.offers_len, ~0, sizeof(ClaimAtom),
                 (xdrproc_t)xdr_ClaimAtom))
    return (FALSE);
  if (!xdr_SimplePaymentResult(xdrs, &objp->last))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_PathPaymentStrictReceiveResult(XDR *xdrs,
                                   PathPaymentStrictReceiveResult *objp) {
  if (!xdr_PathPaymentStrictReceiveResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case PATH_PAYMENT_STRICT_RECEIVE_SUCCESS:
    if (!xdr_PathPaymentStrictReceiveResultSuccess(
            xdrs, &objp->PathPaymentStrictReceiveResult_u.success))
      return (FALSE);
    break;
  case PATH_PAYMENT_STRICT_RECEIVE_NO_ISSUER:
    if (!xdr_Asset(xdrs, &objp->PathPaymentStrictReceiveResult_u.noIssuer))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_PathPaymentStrictSendResultCode(XDR *xdrs,
                                    PathPaymentStrictSendResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_PathPaymentStrictSendResultSuccess(
    XDR *xdrs, PathPaymentStrictSendResultSuccess *objp) {
  if (!xdr_array(xdrs, (char **)&objp->offers.offers_val,
                 (u_int *)&objp->offers.offers_len, ~0, sizeof(ClaimAtom),
                 (xdrproc_t)xdr_ClaimAtom))
    return (FALSE);
  if (!xdr_SimplePaymentResult(xdrs, &objp->last))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_PathPaymentStrictSendResult(XDR *xdrs,
                                       PathPaymentStrictSendResult *objp) {
  if (!xdr_PathPaymentStrictSendResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case PATH_PAYMENT_STRICT_SEND_SUCCESS:
    if (!xdr_PathPaymentStrictSendResultSuccess(
            xdrs, &objp->PathPaymentStrictSendResult_u.success))
      return (FALSE);
    break;
  case PATH_PAYMENT_STRICT_SEND_NO_ISSUER:
    if (!xdr_Asset(xdrs, &objp->PathPaymentStrictSendResult_u.noIssuer))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_ManageSellOfferResultCode(XDR *xdrs,
                                     ManageSellOfferResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ManageOfferEffect(XDR *xdrs, ManageOfferEffect *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ManageOfferSuccessResultOffer(XDR *xdrs,
                                         ManageOfferSuccessResultOffer *objp) {
  if (!xdr_ManageOfferEffect(xdrs, &objp->effect))
    return (FALSE);
  switch (objp->effect) {
  case MANAGE_OFFER_CREATED:
  case MANAGE_OFFER_UPDATED:
    if (!xdr_OfferEntry(xdrs, &objp->ManageOfferSuccessResultOffer_u.offer))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_ManageOfferSuccessResult(XDR *xdrs, ManageOfferSuccessResult *objp) {
  if (!xdr_array(xdrs, (char **)&objp->offersClaimed.offersClaimed_val,
                 (u_int *)&objp->offersClaimed.offersClaimed_len, ~0,
                 sizeof(ClaimAtom), (xdrproc_t)xdr_ClaimAtom))
    return (FALSE);
  if (!xdr_ManageOfferSuccessResultOffer(xdrs, &objp->offer))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ManageSellOfferResult(XDR *xdrs, ManageSellOfferResult *objp) {
  if (!xdr_ManageSellOfferResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case MANAGE_SELL_OFFER_SUCCESS:
    if (!xdr_ManageOfferSuccessResult(xdrs,
                                      &objp->ManageSellOfferResult_u.success))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_ManageBuyOfferResultCode(XDR *xdrs, ManageBuyOfferResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ManageBuyOfferResult(XDR *xdrs, ManageBuyOfferResult *objp) {
  if (!xdr_ManageBuyOfferResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case MANAGE_BUY_OFFER_SUCCESS:
    if (!xdr_ManageOfferSuccessResult(xdrs,
                                      &objp->ManageBuyOfferResult_u.success))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_SetOptionsResultCode(XDR *xdrs, SetOptionsResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SetOptionsResult(XDR *xdrs, SetOptionsResult *objp) {
  if (!xdr_SetOptionsResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case SET_OPTIONS_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_ChangeTrustResultCode(XDR *xdrs, ChangeTrustResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ChangeTrustResult(XDR *xdrs, ChangeTrustResult *objp) {
  if (!xdr_ChangeTrustResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case CHANGE_TRUST_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_AllowTrustResultCode(XDR *xdrs, AllowTrustResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AllowTrustResult(XDR *xdrs, AllowTrustResult *objp) {
  if (!xdr_AllowTrustResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case ALLOW_TRUST_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_AccountMergeResultCode(XDR *xdrs, AccountMergeResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AccountMergeResult(XDR *xdrs, AccountMergeResult *objp) {
  if (!xdr_AccountMergeResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case ACCOUNT_MERGE_SUCCESS:
    if (!xdr_int64(xdrs, &objp->AccountMergeResult_u.sourceAccountBalance))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_InflationResultCode(XDR *xdrs, InflationResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_InflationPayout(XDR *xdrs, InflationPayout *objp) {
  if (!xdr_AccountID(xdrs, &objp->destination))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->amount))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_InflationResult(XDR *xdrs, InflationResult *objp) {
  if (!xdr_InflationResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case INFLATION_SUCCESS:
    if (!xdr_array(xdrs, (char **)&objp->InflationResult_u.payouts.payouts_val,
                   (u_int *)&objp->InflationResult_u.payouts.payouts_len, ~0,
                   sizeof(InflationPayout), (xdrproc_t)xdr_InflationPayout))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_ManageDataResultCode(XDR *xdrs, ManageDataResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ManageDataResult(XDR *xdrs, ManageDataResult *objp) {
  if (!xdr_ManageDataResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case MANAGE_DATA_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_BumpSequenceResultCode(XDR *xdrs, BumpSequenceResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_BumpSequenceResult(XDR *xdrs, BumpSequenceResult *objp) {
  if (!xdr_BumpSequenceResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case BUMP_SEQUENCE_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_CreateClaimableBalanceResultCode(XDR *xdrs,
                                     CreateClaimableBalanceResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_CreateClaimableBalanceResult(XDR *xdrs,
                                        CreateClaimableBalanceResult *objp) {
  if (!xdr_CreateClaimableBalanceResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case CREATE_CLAIMABLE_BALANCE_SUCCESS:
    if (!xdr_ClaimableBalanceID(
            xdrs, &objp->CreateClaimableBalanceResult_u.balanceID))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_ClaimClaimableBalanceResultCode(XDR *xdrs,
                                    ClaimClaimableBalanceResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClaimClaimableBalanceResult(XDR *xdrs,
                                       ClaimClaimableBalanceResult *objp) {
  if (!xdr_ClaimClaimableBalanceResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case CLAIM_CLAIMABLE_BALANCE_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_BeginSponsoringFutureReservesResultCode(
    XDR *xdrs, BeginSponsoringFutureReservesResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_BeginSponsoringFutureReservesResult(
    XDR *xdrs, BeginSponsoringFutureReservesResult *objp) {
  if (!xdr_BeginSponsoringFutureReservesResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case BEGIN_SPONSORING_FUTURE_RESERVES_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_EndSponsoringFutureReservesResultCode(
    XDR *xdrs, EndSponsoringFutureReservesResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_EndSponsoringFutureReservesResult(XDR *xdrs,
                                      EndSponsoringFutureReservesResult *objp) {
  if (!xdr_EndSponsoringFutureReservesResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case END_SPONSORING_FUTURE_RESERVES_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_RevokeSponsorshipResultCode(XDR *xdrs,
                                       RevokeSponsorshipResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_RevokeSponsorshipResult(XDR *xdrs, RevokeSponsorshipResult *objp) {
  if (!xdr_RevokeSponsorshipResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case REVOKE_SPONSORSHIP_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_ClawbackResultCode(XDR *xdrs, ClawbackResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_ClawbackResult(XDR *xdrs, ClawbackResult *objp) {
  if (!xdr_ClawbackResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case CLAWBACK_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_ClawbackClaimableBalanceResultCode(
    XDR *xdrs, ClawbackClaimableBalanceResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_ClawbackClaimableBalanceResult(XDR *xdrs,
                                   ClawbackClaimableBalanceResult *objp) {
  if (!xdr_ClawbackClaimableBalanceResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case CLAWBACK_CLAIMABLE_BALANCE_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_SetTrustLineFlagsResultCode(XDR *xdrs,
                                       SetTrustLineFlagsResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SetTrustLineFlagsResult(XDR *xdrs, SetTrustLineFlagsResult *objp) {
  if (!xdr_SetTrustLineFlagsResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case SET_TRUST_LINE_FLAGS_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_LiquidityPoolDepositResultCode(XDR *xdrs,
                                   LiquidityPoolDepositResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LiquidityPoolDepositResult(XDR *xdrs,
                                      LiquidityPoolDepositResult *objp) {
  if (!xdr_LiquidityPoolDepositResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case LIQUIDITY_POOL_DEPOSIT_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t
xdr_LiquidityPoolWithdrawResultCode(XDR *xdrs,
                                    LiquidityPoolWithdrawResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LiquidityPoolWithdrawResult(XDR *xdrs,
                                       LiquidityPoolWithdrawResult *objp) {
  if (!xdr_LiquidityPoolWithdrawResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case LIQUIDITY_POOL_WITHDRAW_SUCCESS:
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_OperationResultCode(XDR *xdrs, OperationResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_OperationResultTr(XDR *xdrs, OperationResultTr *objp) {
  if (!xdr_OperationType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case CREATE_ACCOUNT:
    if (!xdr_CreateAccountResult(
            xdrs, &objp->OperationResultTr_u.createAccountResult))
      return (FALSE);
    break;
  case PAYMENT:
    if (!xdr_PaymentResult(xdrs, &objp->OperationResultTr_u.paymentResult))
      return (FALSE);
    break;
  case PATH_PAYMENT_STRICT_RECEIVE:
    if (!xdr_PathPaymentStrictReceiveResult(
            xdrs, &objp->OperationResultTr_u.pathPaymentStrictReceiveResult))
      return (FALSE);
    break;
  case MANAGE_SELL_OFFER:
    if (!xdr_ManageSellOfferResult(
            xdrs, &objp->OperationResultTr_u.manageSellOfferResult))
      return (FALSE);
    break;
  case CREATE_PASSIVE_SELL_OFFER:
    if (!xdr_ManageSellOfferResult(
            xdrs, &objp->OperationResultTr_u.createPassiveSellOfferResult))
      return (FALSE);
    break;
  case SET_OPTIONS:
    if (!xdr_SetOptionsResult(xdrs,
                              &objp->OperationResultTr_u.setOptionsResult))
      return (FALSE);
    break;
  case CHANGE_TRUST:
    if (!xdr_ChangeTrustResult(xdrs,
                               &objp->OperationResultTr_u.changeTrustResult))
      return (FALSE);
    break;
  case ALLOW_TRUST:
    if (!xdr_AllowTrustResult(xdrs,
                              &objp->OperationResultTr_u.allowTrustResult))
      return (FALSE);
    break;
  case ACCOUNT_MERGE:
    if (!xdr_AccountMergeResult(xdrs,
                                &objp->OperationResultTr_u.accountMergeResult))
      return (FALSE);
    break;
  case INFLATION:
    if (!xdr_InflationResult(xdrs, &objp->OperationResultTr_u.inflationResult))
      return (FALSE);
    break;
  case MANAGE_DATA:
    if (!xdr_ManageDataResult(xdrs,
                              &objp->OperationResultTr_u.manageDataResult))
      return (FALSE);
    break;
  case BUMP_SEQUENCE:
    if (!xdr_BumpSequenceResult(xdrs, &objp->OperationResultTr_u.bumpSeqResult))
      return (FALSE);
    break;
  case MANAGE_BUY_OFFER:
    if (!xdr_ManageBuyOfferResult(
            xdrs, &objp->OperationResultTr_u.manageBuyOfferResult))
      return (FALSE);
    break;
  case PATH_PAYMENT_STRICT_SEND:
    if (!xdr_PathPaymentStrictSendResult(
            xdrs, &objp->OperationResultTr_u.pathPaymentStrictSendResult))
      return (FALSE);
    break;
  case CREATE_CLAIMABLE_BALANCE:
    if (!xdr_CreateClaimableBalanceResult(
            xdrs, &objp->OperationResultTr_u.createClaimableBalanceResult))
      return (FALSE);
    break;
  case CLAIM_CLAIMABLE_BALANCE:
    if (!xdr_ClaimClaimableBalanceResult(
            xdrs, &objp->OperationResultTr_u.claimClaimableBalanceResult))
      return (FALSE);
    break;
  case BEGIN_SPONSORING_FUTURE_RESERVES:
    if (!xdr_BeginSponsoringFutureReservesResult(
            xdrs,
            &objp->OperationResultTr_u.beginSponsoringFutureReservesResult))
      return (FALSE);
    break;
  case END_SPONSORING_FUTURE_RESERVES:
    if (!xdr_EndSponsoringFutureReservesResult(
            xdrs, &objp->OperationResultTr_u.endSponsoringFutureReservesResult))
      return (FALSE);
    break;
  case REVOKE_SPONSORSHIP:
    if (!xdr_RevokeSponsorshipResult(
            xdrs, &objp->OperationResultTr_u.revokeSponsorshipResult))
      return (FALSE);
    break;
  case CLAWBACK:
    if (!xdr_ClawbackResult(xdrs, &objp->OperationResultTr_u.clawbackResult))
      return (FALSE);
    break;
  case CLAWBACK_CLAIMABLE_BALANCE:
    if (!xdr_ClawbackClaimableBalanceResult(
            xdrs, &objp->OperationResultTr_u.clawbackClaimableBalanceResult))
      return (FALSE);
    break;
  case SET_TRUST_LINE_FLAGS:
    if (!xdr_SetTrustLineFlagsResult(
            xdrs, &objp->OperationResultTr_u.setTrustLineFlagsResult))
      return (FALSE);
    break;
  case LIQUIDITY_POOL_DEPOSIT:
    if (!xdr_LiquidityPoolDepositResult(
            xdrs, &objp->OperationResultTr_u.liquidityPoolDepositResult))
      return (FALSE);
    break;
  case LIQUIDITY_POOL_WITHDRAW:
    if (!xdr_LiquidityPoolWithdrawResult(
            xdrs, &objp->OperationResultTr_u.liquidityPoolWithdrawResult))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_OperationResult(XDR *xdrs, OperationResult *objp) {
  if (!xdr_OperationResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case opINNER:
    if (!xdr_OperationResultTr(xdrs, &objp->OperationResult_u.tr))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_TransactionResultCode(XDR *xdrs, TransactionResultCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_InnerTransactionResultResult(XDR *xdrs,
                                        InnerTransactionResultResult *objp) {
  if (!xdr_TransactionResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case txSUCCESS:
  case txFAILED:
    if (!xdr_array(
            xdrs,
            (char **)&objp->InnerTransactionResultResult_u.results.results_val,
            (u_int *)&objp->InnerTransactionResultResult_u.results.results_len,
            ~0, sizeof(OperationResult), (xdrproc_t)xdr_OperationResult))
      return (FALSE);
    break;
  case txTOO_EARLY:
  case txTOO_LATE:
  case txMISSING_OPERATION:
  case txBAD_SEQ:
  case txBAD_AUTH:
  case txINSUFFICIENT_BALANCE:
  case txNO_ACCOUNT:
  case txINSUFFICIENT_FEE:
  case txBAD_AUTH_EXTRA:
  case txINTERNAL_ERROR:
  case txNOT_SUPPORTED:
  case txBAD_SPONSORSHIP:
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_InnerTransactionResultExt(XDR *xdrs,
                                     InnerTransactionResultExt *objp) {
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

bool_t xdr_InnerTransactionResult(XDR *xdrs, InnerTransactionResult *objp) {
  if (!xdr_int64(xdrs, &objp->feeCharged))
    return (FALSE);
  if (!xdr_InnerTransactionResultResult(xdrs, &objp->result))
    return (FALSE);
  if (!xdr_InnerTransactionResultExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_InnerTransactionResultPair(XDR *xdrs,
                                      InnerTransactionResultPair *objp) {
  if (!xdr_Hash(xdrs, objp->transactionHash))
    return (FALSE);
  if (!xdr_InnerTransactionResult(xdrs, &objp->result))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TransactionResultResult(XDR *xdrs, TransactionResultResult *objp) {
  if (!xdr_TransactionResultCode(xdrs, &objp->code))
    return (FALSE);
  switch (objp->code) {
  case txFEE_BUMP_INNER_SUCCESS:
  case txFEE_BUMP_INNER_FAILED:
    if (!xdr_InnerTransactionResultPair(
            xdrs, &objp->TransactionResultResult_u.innerResultPair))
      return (FALSE);
    break;
  case txSUCCESS:
  case txFAILED:
    if (!xdr_array(
            xdrs, (char **)&objp->TransactionResultResult_u.results.results_val,
            (u_int *)&objp->TransactionResultResult_u.results.results_len, ~0,
            sizeof(OperationResult), (xdrproc_t)xdr_OperationResult))
      return (FALSE);
    break;
  default:
    break;
  }
  return (TRUE);
}

bool_t xdr_TransactionResultExt(XDR *xdrs, TransactionResultExt *objp) {
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

bool_t xdr_TransactionResult(XDR *xdrs, TransactionResult *objp) {
  if (!xdr_int64(xdrs, &objp->feeCharged))
    return (FALSE);
  if (!xdr_TransactionResultResult(xdrs, &objp->result))
    return (FALSE);
  if (!xdr_TransactionResultExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_UpgradeType(XDR *xdrs, UpgradeType *objp) {
  if (!xdr_bytes(xdrs, (char **)&objp->UpgradeType_val,
                 (u_int *)&objp->UpgradeType_len, 128))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_StellarValueType(XDR *xdrs, StellarValueType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerCloseValueSignature(XDR *xdrs,
                                     LedgerCloseValueSignature *objp) {
  if (!xdr_NodeID(xdrs, &objp->nodeID))
    return (FALSE);
  if (!xdr_Signature(xdrs, &objp->signature))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_StellarValueExt(XDR *xdrs, StellarValueExt *objp) {
  if (!xdr_StellarValueType(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case STELLAR_VALUE_BASIC:
    break;
  case STELLAR_VALUE_SIGNED:
    if (!xdr_LedgerCloseValueSignature(
            xdrs, &objp->StellarValueExt_u.lcValueSignature))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_StellarValue(XDR *xdrs, StellarValue *objp) {
  if (!xdr_Hash(xdrs, objp->txSetHash))
    return (FALSE);
  if (!xdr_TimePoint(xdrs, &objp->closeTime))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->upgrades.upgrades_val,
                 (u_int *)&objp->upgrades.upgrades_len, 6, sizeof(UpgradeType),
                 (xdrproc_t)xdr_UpgradeType))
    return (FALSE);
  if (!xdr_StellarValueExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerHeaderExt(XDR *xdrs, LedgerHeaderExt *objp) {
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

bool_t xdr_LedgerHeader(XDR *xdrs, LedgerHeader *objp) {
  if (!xdr_uint32(xdrs, &objp->ledgerVersion))
    return (FALSE);
  if (!xdr_Hash(xdrs, objp->previousLedgerHash))
    return (FALSE);
  if (!xdr_StellarValue(xdrs, &objp->scpValue))
    return (FALSE);
  if (!xdr_Hash(xdrs, objp->txSetResultHash))
    return (FALSE);
  if (!xdr_Hash(xdrs, objp->bucketListHash))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->ledgerSeq))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->totalCoins))
    return (FALSE);
  if (!xdr_int64(xdrs, &objp->feePool))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->inflationSeq))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->idPool))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->baseFee))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->baseReserve))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->maxTxSetSize))
    return (FALSE);
  if (!xdr_vector(xdrs, (char *)objp->skipList, 4, sizeof(Hash),
                  (xdrproc_t)xdr_Hash))
    return (FALSE);
  if (!xdr_LedgerHeaderExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerUpgradeType(XDR *xdrs, LedgerUpgradeType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerUpgrade(XDR *xdrs, LedgerUpgrade *objp) {
  if (!xdr_LedgerUpgradeType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case LEDGER_UPGRADE_VERSION:
    if (!xdr_uint32(xdrs, &objp->LedgerUpgrade_u.newLedgerVersion))
      return (FALSE);
    break;
  case LEDGER_UPGRADE_BASE_FEE:
    if (!xdr_uint32(xdrs, &objp->LedgerUpgrade_u.newBaseFee))
      return (FALSE);
    break;
  case LEDGER_UPGRADE_MAX_TX_SET_SIZE:
    if (!xdr_uint32(xdrs, &objp->LedgerUpgrade_u.newMaxTxSetSize))
      return (FALSE);
    break;
  case LEDGER_UPGRADE_BASE_RESERVE:
    if (!xdr_uint32(xdrs, &objp->LedgerUpgrade_u.newBaseReserve))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_BucketEntryType(XDR *xdrs, BucketEntryType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_BucketMetadataExt(XDR *xdrs, BucketMetadataExt *objp) {
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

bool_t xdr_BucketMetadata(XDR *xdrs, BucketMetadata *objp) {
  if (!xdr_uint32(xdrs, &objp->ledgerVersion))
    return (FALSE);
  if (!xdr_BucketMetadataExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_BucketEntry(XDR *xdrs, BucketEntry *objp) {
  if (!xdr_BucketEntryType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case LIVEENTRY:
  case INITENTRY:
    if (!xdr_LedgerEntry(xdrs, &objp->BucketEntry_u.liveEntry))
      return (FALSE);
    break;
  case DEADENTRY:
    if (!xdr_LedgerKey(xdrs, &objp->BucketEntry_u.deadEntry))
      return (FALSE);
    break;
  case METAENTRY:
    if (!xdr_BucketMetadata(xdrs, &objp->BucketEntry_u.metaEntry))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_TransactionSet(XDR *xdrs, TransactionSet *objp) {
  if (!xdr_Hash(xdrs, objp->previousLedgerHash))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->txs.txs_val, (u_int *)&objp->txs.txs_len,
                 ~0, sizeof(TransactionEnvelope),
                 (xdrproc_t)xdr_TransactionEnvelope))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TransactionResultPair(XDR *xdrs, TransactionResultPair *objp) {
  if (!xdr_Hash(xdrs, objp->transactionHash))
    return (FALSE);
  if (!xdr_TransactionResult(xdrs, &objp->result))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TransactionResultSet(XDR *xdrs, TransactionResultSet *objp) {
  if (!xdr_array(xdrs, (char **)&objp->results.results_val,
                 (u_int *)&objp->results.results_len, ~0,
                 sizeof(TransactionResultPair),
                 (xdrproc_t)xdr_TransactionResultPair))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TransactionHistoryEntryExt(XDR *xdrs,
                                      TransactionHistoryEntryExt *objp) {
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

bool_t xdr_TransactionHistoryEntry(XDR *xdrs, TransactionHistoryEntry *objp) {
  if (!xdr_uint32(xdrs, &objp->ledgerSeq))
    return (FALSE);
  if (!xdr_TransactionSet(xdrs, &objp->txSet))
    return (FALSE);
  if (!xdr_TransactionHistoryEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t
xdr_TransactionHistoryResultEntryExt(XDR *xdrs,
                                     TransactionHistoryResultEntryExt *objp) {
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

bool_t xdr_TransactionHistoryResultEntry(XDR *xdrs,
                                         TransactionHistoryResultEntry *objp) {
  if (!xdr_uint32(xdrs, &objp->ledgerSeq))
    return (FALSE);
  if (!xdr_TransactionResultSet(xdrs, &objp->txResultSet))
    return (FALSE);
  if (!xdr_TransactionHistoryResultEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerHeaderHistoryEntryExt(XDR *xdrs,
                                       LedgerHeaderHistoryEntryExt *objp) {
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

bool_t xdr_LedgerHeaderHistoryEntry(XDR *xdrs, LedgerHeaderHistoryEntry *objp) {
  if (!xdr_Hash(xdrs, objp->hash))
    return (FALSE);
  if (!xdr_LedgerHeader(xdrs, &objp->header))
    return (FALSE);
  if (!xdr_LedgerHeaderHistoryEntryExt(xdrs, &objp->ext))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerSCPMessages(XDR *xdrs, LedgerSCPMessages *objp) {
  if (!xdr_uint32(xdrs, &objp->ledgerSeq))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->messages.messages_val,
                 (u_int *)&objp->messages.messages_len, ~0, sizeof(SCPEnvelope),
                 (xdrproc_t)xdr_SCPEnvelope))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SCPHistoryEntryV0(XDR *xdrs, SCPHistoryEntryV0 *objp) {
  if (!xdr_array(xdrs, (char **)&objp->quorumSets.quorumSets_val,
                 (u_int *)&objp->quorumSets.quorumSets_len, ~0,
                 sizeof(SCPQuorumSet), (xdrproc_t)xdr_SCPQuorumSet))
    return (FALSE);
  if (!xdr_LedgerSCPMessages(xdrs, &objp->ledgerMessages))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SCPHistoryEntry(XDR *xdrs, SCPHistoryEntry *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    if (!xdr_SCPHistoryEntryV0(xdrs, &objp->SCPHistoryEntry_u.v0))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_LedgerEntryChangeType(XDR *xdrs, LedgerEntryChangeType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerEntryChange(XDR *xdrs, LedgerEntryChange *objp) {
  if (!xdr_LedgerEntryChangeType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case LEDGER_ENTRY_CREATED:
    if (!xdr_LedgerEntry(xdrs, &objp->LedgerEntryChange_u.created))
      return (FALSE);
    break;
  case LEDGER_ENTRY_UPDATED:
    if (!xdr_LedgerEntry(xdrs, &objp->LedgerEntryChange_u.updated))
      return (FALSE);
    break;
  case LEDGER_ENTRY_REMOVED:
    if (!xdr_LedgerKey(xdrs, &objp->LedgerEntryChange_u.removed))
      return (FALSE);
    break;
  case LEDGER_ENTRY_STATE:
    if (!xdr_LedgerEntry(xdrs, &objp->LedgerEntryChange_u.state))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_LedgerEntryChanges(XDR *xdrs, LedgerEntryChanges *objp) {
  if (!xdr_array(xdrs, (char **)&objp->LedgerEntryChanges_val,
                 (u_int *)&objp->LedgerEntryChanges_len, ~0,
                 sizeof(LedgerEntryChange), (xdrproc_t)xdr_LedgerEntryChange))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_OperationMeta(XDR *xdrs, OperationMeta *objp) {
  if (!xdr_LedgerEntryChanges(xdrs, &objp->changes))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TransactionMetaV1(XDR *xdrs, TransactionMetaV1 *objp) {
  if (!xdr_LedgerEntryChanges(xdrs, &objp->txChanges))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->operations.operations_val,
                 (u_int *)&objp->operations.operations_len, ~0,
                 sizeof(OperationMeta), (xdrproc_t)xdr_OperationMeta))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TransactionMetaV2(XDR *xdrs, TransactionMetaV2 *objp) {
  if (!xdr_LedgerEntryChanges(xdrs, &objp->txChangesBefore))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->operations.operations_val,
                 (u_int *)&objp->operations.operations_len, ~0,
                 sizeof(OperationMeta), (xdrproc_t)xdr_OperationMeta))
    return (FALSE);
  if (!xdr_LedgerEntryChanges(xdrs, &objp->txChangesAfter))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TransactionMeta(XDR *xdrs, TransactionMeta *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    if (!xdr_array(xdrs,
                   (char **)&objp->TransactionMeta_u.operations.operations_val,
                   (u_int *)&objp->TransactionMeta_u.operations.operations_len,
                   ~0, sizeof(OperationMeta), (xdrproc_t)xdr_OperationMeta))
      return (FALSE);
    break;
  case 1:
    if (!xdr_TransactionMetaV1(xdrs, &objp->TransactionMeta_u.v1))
      return (FALSE);
    break;
  case 2:
    if (!xdr_TransactionMetaV2(xdrs, &objp->TransactionMeta_u.v2))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_TransactionResultMeta(XDR *xdrs, TransactionResultMeta *objp) {
  if (!xdr_TransactionResultPair(xdrs, &objp->result))
    return (FALSE);
  if (!xdr_LedgerEntryChanges(xdrs, &objp->feeProcessing))
    return (FALSE);
  if (!xdr_TransactionMeta(xdrs, &objp->txApplyProcessing))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_UpgradeEntryMeta(XDR *xdrs, UpgradeEntryMeta *objp) {
  if (!xdr_LedgerUpgrade(xdrs, &objp->upgrade))
    return (FALSE);
  if (!xdr_LedgerEntryChanges(xdrs, &objp->changes))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerCloseMetaV0(XDR *xdrs, LedgerCloseMetaV0 *objp) {
  if (!xdr_LedgerHeaderHistoryEntry(xdrs, &objp->ledgerHeader))
    return (FALSE);
  if (!xdr_TransactionSet(xdrs, &objp->txSet))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->txProcessing.txProcessing_val,
                 (u_int *)&objp->txProcessing.txProcessing_len, ~0,
                 sizeof(TransactionResultMeta),
                 (xdrproc_t)xdr_TransactionResultMeta))
    return (FALSE);
  if (!xdr_array(xdrs,
                 (char **)&objp->upgradesProcessing.upgradesProcessing_val,
                 (u_int *)&objp->upgradesProcessing.upgradesProcessing_len, ~0,
                 sizeof(UpgradeEntryMeta), (xdrproc_t)xdr_UpgradeEntryMeta))
    return (FALSE);
  if (!xdr_array(xdrs, (char **)&objp->scpInfo.scpInfo_val,
                 (u_int *)&objp->scpInfo.scpInfo_len, ~0,
                 sizeof(SCPHistoryEntry), (xdrproc_t)xdr_SCPHistoryEntry))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_LedgerCloseMeta(XDR *xdrs, LedgerCloseMeta *objp) {
  if (!xdr_int(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    if (!xdr_LedgerCloseMetaV0(xdrs, &objp->LedgerCloseMeta_u.v0))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_ErrorCode(XDR *xdrs, ErrorCode *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_Error(XDR *xdrs, Error *objp) {
  if (!xdr_ErrorCode(xdrs, &objp->code))
    return (FALSE);
  if (!xdr_string(xdrs, &objp->msg, 100))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AuthCert(XDR *xdrs, AuthCert *objp) {
  if (!xdr_Curve25519Public(xdrs, &objp->pubkey))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->expiration))
    return (FALSE);
  if (!xdr_Signature(xdrs, &objp->sig))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_Hello(XDR *xdrs, Hello *objp) {
  if (!xdr_uint32(xdrs, &objp->ledgerVersion))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->overlayVersion))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->overlayMinVersion))
    return (FALSE);
  if (!xdr_Hash(xdrs, objp->networkID))
    return (FALSE);
  if (!xdr_string(xdrs, &objp->versionStr, 100))
    return (FALSE);
  if (!xdr_int(xdrs, &objp->listeningPort))
    return (FALSE);
  if (!xdr_NodeID(xdrs, &objp->peerID))
    return (FALSE);
  if (!xdr_AuthCert(xdrs, &objp->cert))
    return (FALSE);
  if (!xdr_uint256(xdrs, objp->nonce))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_Auth(XDR *xdrs, Auth *objp) {
  if (!xdr_int(xdrs, &objp->unused))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_IPAddrType(XDR *xdrs, IPAddrType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_PeerAddressIP(XDR *xdrs, PeerAddressIP *objp) {
  if (!xdr_IPAddrType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case IPv4:
    if (!xdr_opaque(xdrs, objp->PeerAddressIP_u.ipv4, 4))
      return (FALSE);
    break;
  case IPv6:
    if (!xdr_opaque(xdrs, objp->PeerAddressIP_u.ipv6, 16))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_PeerAddress(XDR *xdrs, PeerAddress *objp) {
  if (!xdr_PeerAddressIP(xdrs, &objp->ip))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->port))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->numFailures))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_MessageType(XDR *xdrs, MessageType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_DontHave(XDR *xdrs, DontHave *objp) {
  if (!xdr_MessageType(xdrs, &objp->type))
    return (FALSE);
  if (!xdr_uint256(xdrs, objp->reqHash))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SurveyMessageCommandType(XDR *xdrs, SurveyMessageCommandType *objp) {
  if (!xdr_enum(xdrs, (enum_t *)objp))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SurveyRequestMessage(XDR *xdrs, SurveyRequestMessage *objp) {
  if (!xdr_NodeID(xdrs, &objp->surveyorPeerID))
    return (FALSE);
  if (!xdr_NodeID(xdrs, &objp->surveyedPeerID))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->ledgerNum))
    return (FALSE);
  if (!xdr_Curve25519Public(xdrs, &objp->encryptionKey))
    return (FALSE);
  if (!xdr_SurveyMessageCommandType(xdrs, &objp->commandType))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SignedSurveyRequestMessage(XDR *xdrs,
                                      SignedSurveyRequestMessage *objp) {
  if (!xdr_Signature(xdrs, &objp->requestSignature))
    return (FALSE);
  if (!xdr_SurveyRequestMessage(xdrs, &objp->request))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_EncryptedBody(XDR *xdrs, EncryptedBody *objp) {
  if (!xdr_bytes(xdrs, (char **)&objp->EncryptedBody_val,
                 (u_int *)&objp->EncryptedBody_len, 64000))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SurveyResponseMessage(XDR *xdrs, SurveyResponseMessage *objp) {
  if (!xdr_NodeID(xdrs, &objp->surveyorPeerID))
    return (FALSE);
  if (!xdr_NodeID(xdrs, &objp->surveyedPeerID))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->ledgerNum))
    return (FALSE);
  if (!xdr_SurveyMessageCommandType(xdrs, &objp->commandType))
    return (FALSE);
  if (!xdr_EncryptedBody(xdrs, &objp->encryptedBody))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SignedSurveyResponseMessage(XDR *xdrs,
                                       SignedSurveyResponseMessage *objp) {
  if (!xdr_Signature(xdrs, &objp->responseSignature))
    return (FALSE);
  if (!xdr_SurveyResponseMessage(xdrs, &objp->response))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_PeerStats(XDR *xdrs, PeerStats *objp) {
  if (!xdr_NodeID(xdrs, &objp->id))
    return (FALSE);
  if (!xdr_string(xdrs, &objp->versionStr, 100))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->messagesRead))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->messagesWritten))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->bytesRead))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->bytesWritten))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->secondsConnected))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->uniqueFloodBytesRecv))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->duplicateFloodBytesRecv))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->uniqueFetchBytesRecv))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->duplicateFetchBytesRecv))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->uniqueFloodMessageRecv))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->duplicateFloodMessageRecv))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->uniqueFetchMessageRecv))
    return (FALSE);
  if (!xdr_uint64(xdrs, &objp->duplicateFetchMessageRecv))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_PeerStatList(XDR *xdrs, PeerStatList *objp) {
  if (!xdr_array(xdrs, (char **)&objp->PeerStatList_val,
                 (u_int *)&objp->PeerStatList_len, 25, sizeof(PeerStats),
                 (xdrproc_t)xdr_PeerStats))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_TopologyResponseBody(XDR *xdrs, TopologyResponseBody *objp) {
  if (!xdr_PeerStatList(xdrs, &objp->inboundPeers))
    return (FALSE);
  if (!xdr_PeerStatList(xdrs, &objp->outboundPeers))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->totalInboundPeerCount))
    return (FALSE);
  if (!xdr_uint32(xdrs, &objp->totalOutboundPeerCount))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_SurveyResponseBody(XDR *xdrs, SurveyResponseBody *objp) {
  if (!xdr_SurveyMessageCommandType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case SURVEY_TOPOLOGY:
    if (!xdr_TopologyResponseBody(
            xdrs, &objp->SurveyResponseBody_u.topologyResponseBody))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_StellarMessage(XDR *xdrs, StellarMessage *objp) {
  if (!xdr_MessageType(xdrs, &objp->type))
    return (FALSE);
  switch (objp->type) {
  case ERROR_MSG:
    if (!xdr_Error(xdrs, &objp->StellarMessage_u.error))
      return (FALSE);
    break;
  case HELLO:
    if (!xdr_Hello(xdrs, &objp->StellarMessage_u.hello))
      return (FALSE);
    break;
  case AUTH_:
    if (!xdr_Auth(xdrs, &objp->StellarMessage_u.auth))
      return (FALSE);
    break;
  case DONT_HAVE:
    if (!xdr_DontHave(xdrs, &objp->StellarMessage_u.dontHave))
      return (FALSE);
    break;
  case GET_PEERS:
    break;
  case PEERS:
    if (!xdr_array(xdrs, (char **)&objp->StellarMessage_u.peers.peers_val,
                   (u_int *)&objp->StellarMessage_u.peers.peers_len, 100,
                   sizeof(PeerAddress), (xdrproc_t)xdr_PeerAddress))
      return (FALSE);
    break;
  case GET_TX_SET:
    if (!xdr_uint256(xdrs, objp->StellarMessage_u.txSetHash))
      return (FALSE);
    break;
  case TX_SET:
    if (!xdr_TransactionSet(xdrs, &objp->StellarMessage_u.txSet))
      return (FALSE);
    break;
  case TRANSACTION:
    if (!xdr_TransactionEnvelope(xdrs, &objp->StellarMessage_u.transaction))
      return (FALSE);
    break;
  case SURVEY_REQUEST:
    if (!xdr_SignedSurveyRequestMessage(
            xdrs, &objp->StellarMessage_u.signedSurveyRequestMessage))
      return (FALSE);
    break;
  case SURVEY_RESPONSE:
    if (!xdr_SignedSurveyResponseMessage(
            xdrs, &objp->StellarMessage_u.signedSurveyResponseMessage))
      return (FALSE);
    break;
  case GET_SCP_QUORUMSET:
    if (!xdr_uint256(xdrs, objp->StellarMessage_u.qSetHash))
      return (FALSE);
    break;
  case SCP_QUORUMSET:
    if (!xdr_SCPQuorumSet(xdrs, &objp->StellarMessage_u.qSet))
      return (FALSE);
    break;
  case SCP_MESSAGE:
    if (!xdr_SCPEnvelope(xdrs, &objp->StellarMessage_u.envelope))
      return (FALSE);
    break;
  case GET_SCP_STATE:
    if (!xdr_uint32(xdrs, &objp->StellarMessage_u.getSCPLedgerSeq))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}

bool_t xdr_AuthenticatedMessageV0(XDR *xdrs, AuthenticatedMessageV0 *objp) {
  if (!xdr_uint64(xdrs, &objp->sequence))
    return (FALSE);
  if (!xdr_StellarMessage(xdrs, &objp->message))
    return (FALSE);
  if (!xdr_HmacSha256Mac(xdrs, &objp->mac))
    return (FALSE);
  return (TRUE);
}

bool_t xdr_AuthenticatedMessage(XDR *xdrs, AuthenticatedMessage *objp) {
  if (!xdr_uint32(xdrs, &objp->v))
    return (FALSE);
  switch (objp->v) {
  case 0:
    if (!xdr_AuthenticatedMessageV0(xdrs, &objp->AuthenticatedMessage_u.v0))
      return (FALSE);
    break;
  default:
    return (FALSE);
  }
  return (TRUE);
}
