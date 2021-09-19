#ifndef _STELLAR_H_RPCGEN
#define _STELLAR_H_RPCGEN

#define RPCGEN_VERSION 199506

#define STELLAR_PROTOCOL 18

#define VERSION_MAJOR 0
#define VERSION_MINOR 18
#define VERSION_PATCH 0

#include <rpc/rpc.h>

typedef char Hash[32];
#ifdef __cplusplus
extern "C" bool_t xdr_Hash(XDR *, Hash);
#elif __STDC__
extern bool_t xdr_Hash(XDR *, Hash);
#else  /* Old Style C */
bool_t xdr_Hash();
#endif /* Old Style C */

typedef char uint256[32];
#ifdef __cplusplus
extern "C" bool_t xdr_uint256(XDR *, uint256);
#elif __STDC__
extern bool_t xdr_uint256(XDR *, uint256);
#else  /* Old Style C */
bool_t xdr_uint256();
#endif /* Old Style C */

typedef u_int uint32;
#ifdef __cplusplus
extern "C" bool_t xdr_uint32(XDR *, uint32 *);
#elif __STDC__
extern bool_t xdr_uint32(XDR *, uint32 *);
#else  /* Old Style C */
bool_t xdr_uint32();
#endif /* Old Style C */

typedef int int32;
#ifdef __cplusplus
extern "C" bool_t xdr_int32(XDR *, int32 *);
#elif __STDC__
extern bool_t xdr_int32(XDR *, int32 *);
#else  /* Old Style C */
bool_t xdr_int32();
#endif /* Old Style C */

typedef u_int64_t uint64;
#ifdef __cplusplus
extern "C" bool_t xdr_uint64(XDR *, uint64 *);
#elif __STDC__
extern bool_t xdr_uint64(XDR *, uint64 *);
#else  /* Old Style C */
bool_t xdr_uint64();
#endif /* Old Style C */

typedef int64_t int64;
#ifdef __cplusplus
extern "C" bool_t xdr_int64(XDR *, int64 *);
#elif __STDC__
extern bool_t xdr_int64(XDR *, int64 *);
#else  /* Old Style C */
bool_t xdr_int64();
#endif /* Old Style C */

enum CryptoKeyType {
  KEY_TYPE_ED25519 = 0,
  KEY_TYPE_PRE_AUTH_TX = 1,
  KEY_TYPE_HASH_X = 2,
  KEY_TYPE_MUXED_ED25519 = 0x100,
};
typedef enum CryptoKeyType CryptoKeyType;
#ifdef __cplusplus
extern "C" bool_t xdr_CryptoKeyType(XDR *, CryptoKeyType *);
#elif __STDC__
extern bool_t xdr_CryptoKeyType(XDR *, CryptoKeyType *);
#else  /* Old Style C */
bool_t xdr_CryptoKeyType();
#endif /* Old Style C */

enum PublicKeyType {
  PUBLIC_KEY_TYPE_ED25519 = KEY_TYPE_ED25519,
};
typedef enum PublicKeyType PublicKeyType;
#ifdef __cplusplus
extern "C" bool_t xdr_PublicKeyType(XDR *, PublicKeyType *);
#elif __STDC__
extern bool_t xdr_PublicKeyType(XDR *, PublicKeyType *);
#else  /* Old Style C */
bool_t xdr_PublicKeyType();
#endif /* Old Style C */

enum SignerKeyType {
  SIGNER_KEY_TYPE_ED25519 = KEY_TYPE_ED25519,
  SIGNER_KEY_TYPE_PRE_AUTH_TX = KEY_TYPE_PRE_AUTH_TX,
  SIGNER_KEY_TYPE_HASH_X = KEY_TYPE_HASH_X,
};
typedef enum SignerKeyType SignerKeyType;
#ifdef __cplusplus
extern "C" bool_t xdr_SignerKeyType(XDR *, SignerKeyType *);
#elif __STDC__
extern bool_t xdr_SignerKeyType(XDR *, SignerKeyType *);
#else  /* Old Style C */
bool_t xdr_SignerKeyType();
#endif /* Old Style C */

struct PublicKey {
  PublicKeyType type;
  union {
    uint256 ed25519;
  } PublicKey_u;
};
typedef struct PublicKey PublicKey;
#ifdef __cplusplus
extern "C" bool_t xdr_PublicKey(XDR *, PublicKey *);
#elif __STDC__
extern bool_t xdr_PublicKey(XDR *, PublicKey *);
#else  /* Old Style C */
bool_t xdr_PublicKey();
#endif /* Old Style C */

struct SignerKey {
  SignerKeyType type;
  union {
    uint256 ed25519;
    uint256 preAuthTx;
    uint256 hashX;
  } SignerKey_u;
};
typedef struct SignerKey SignerKey;
#ifdef __cplusplus
extern "C" bool_t xdr_SignerKey(XDR *, SignerKey *);
#elif __STDC__
extern bool_t xdr_SignerKey(XDR *, SignerKey *);
#else  /* Old Style C */
bool_t xdr_SignerKey();
#endif /* Old Style C */

typedef struct {
  u_int Signature_len;
  char *Signature_val;
} Signature;
#ifdef __cplusplus
extern "C" bool_t xdr_Signature(XDR *, Signature *);
#elif __STDC__
extern bool_t xdr_Signature(XDR *, Signature *);
#else  /* Old Style C */
bool_t xdr_Signature();
#endif /* Old Style C */

typedef char SignatureHint[4];
#ifdef __cplusplus
extern "C" bool_t xdr_SignatureHint(XDR *, SignatureHint);
#elif __STDC__
extern bool_t xdr_SignatureHint(XDR *, SignatureHint);
#else  /* Old Style C */
bool_t xdr_SignatureHint();
#endif /* Old Style C */

typedef PublicKey NodeID;
#ifdef __cplusplus
extern "C" bool_t xdr_NodeID(XDR *, NodeID *);
#elif __STDC__
extern bool_t xdr_NodeID(XDR *, NodeID *);
#else  /* Old Style C */
bool_t xdr_NodeID();
#endif /* Old Style C */

struct Curve25519Secret {
  char key[32];
};
typedef struct Curve25519Secret Curve25519Secret;
#ifdef __cplusplus
extern "C" bool_t xdr_Curve25519Secret(XDR *, Curve25519Secret *);
#elif __STDC__
extern bool_t xdr_Curve25519Secret(XDR *, Curve25519Secret *);
#else  /* Old Style C */
bool_t xdr_Curve25519Secret();
#endif /* Old Style C */

struct Curve25519Public {
  char key[32];
};
typedef struct Curve25519Public Curve25519Public;
#ifdef __cplusplus
extern "C" bool_t xdr_Curve25519Public(XDR *, Curve25519Public *);
#elif __STDC__
extern bool_t xdr_Curve25519Public(XDR *, Curve25519Public *);
#else  /* Old Style C */
bool_t xdr_Curve25519Public();
#endif /* Old Style C */

struct HmacSha256Key {
  char key[32];
};
typedef struct HmacSha256Key HmacSha256Key;
#ifdef __cplusplus
extern "C" bool_t xdr_HmacSha256Key(XDR *, HmacSha256Key *);
#elif __STDC__
extern bool_t xdr_HmacSha256Key(XDR *, HmacSha256Key *);
#else  /* Old Style C */
bool_t xdr_HmacSha256Key();
#endif /* Old Style C */

struct HmacSha256Mac {
  char mac[32];
};
typedef struct HmacSha256Mac HmacSha256Mac;
#ifdef __cplusplus
extern "C" bool_t xdr_HmacSha256Mac(XDR *, HmacSha256Mac *);
#elif __STDC__
extern bool_t xdr_HmacSha256Mac(XDR *, HmacSha256Mac *);
#else  /* Old Style C */
bool_t xdr_HmacSha256Mac();
#endif /* Old Style C */

typedef struct {
  u_int Value_len;
  char *Value_val;
} Value;
#ifdef __cplusplus
extern "C" bool_t xdr_Value(XDR *, Value *);
#elif __STDC__
extern bool_t xdr_Value(XDR *, Value *);
#else  /* Old Style C */
bool_t xdr_Value();
#endif /* Old Style C */

struct SCPBallot {
  uint32 counter;
  Value value;
};
typedef struct SCPBallot SCPBallot;
#ifdef __cplusplus
extern "C" bool_t xdr_SCPBallot(XDR *, SCPBallot *);
#elif __STDC__
extern bool_t xdr_SCPBallot(XDR *, SCPBallot *);
#else  /* Old Style C */
bool_t xdr_SCPBallot();
#endif /* Old Style C */

enum SCPStatementType {
  SCP_ST_PREPARE = 0,
  SCP_ST_CONFIRM = 1,
  SCP_ST_EXTERNALIZE = 2,
  SCP_ST_NOMINATE = 3,
};
typedef enum SCPStatementType SCPStatementType;
#ifdef __cplusplus
extern "C" bool_t xdr_SCPStatementType(XDR *, SCPStatementType *);
#elif __STDC__
extern bool_t xdr_SCPStatementType(XDR *, SCPStatementType *);
#else  /* Old Style C */
bool_t xdr_SCPStatementType();
#endif /* Old Style C */

struct SCPNomination {
  Hash quorumSetHash;
  struct {
    u_int votes_len;
    Value *votes_val;
  } votes;
  struct {
    u_int accepted_len;
    Value *accepted_val;
  } accepted;
};
typedef struct SCPNomination SCPNomination;
#ifdef __cplusplus
extern "C" bool_t xdr_SCPNomination(XDR *, SCPNomination *);
#elif __STDC__
extern bool_t xdr_SCPNomination(XDR *, SCPNomination *);
#else  /* Old Style C */
bool_t xdr_SCPNomination();
#endif /* Old Style C */

struct SCPPrepare {
  Hash quorumSetHash;
  SCPBallot ballot;
  SCPBallot *prepared;
  SCPBallot *preparedPrime;
  uint32 nC;
  uint32 nH;
};
typedef struct SCPPrepare SCPPrepare;
#ifdef __cplusplus
extern "C" bool_t xdr_SCPPrepare(XDR *, SCPPrepare *);
#elif __STDC__
extern bool_t xdr_SCPPrepare(XDR *, SCPPrepare *);
#else  /* Old Style C */
bool_t xdr_SCPPrepare();
#endif /* Old Style C */

struct SCPConfirm {
  SCPBallot ballot;
  uint32 nPrepared;
  uint32 nCommit;
  uint32 nH;
  Hash quorumSetHash;
};
typedef struct SCPConfirm SCPConfirm;
#ifdef __cplusplus
extern "C" bool_t xdr_SCPConfirm(XDR *, SCPConfirm *);
#elif __STDC__
extern bool_t xdr_SCPConfirm(XDR *, SCPConfirm *);
#else  /* Old Style C */
bool_t xdr_SCPConfirm();
#endif /* Old Style C */

struct SCPExternalize {
  SCPBallot commit;
  uint32 nH;
  Hash commitQuorumSetHash;
};
typedef struct SCPExternalize SCPExternalize;
#ifdef __cplusplus
extern "C" bool_t xdr_SCPExternalize(XDR *, SCPExternalize *);
#elif __STDC__
extern bool_t xdr_SCPExternalize(XDR *, SCPExternalize *);
#else  /* Old Style C */
bool_t xdr_SCPExternalize();
#endif /* Old Style C */

struct SCPStatementPledges {
  SCPStatementType type;
  union {
    SCPPrepare prepare;
    SCPConfirm confirm;
    SCPExternalize externalize;
    SCPNomination nominate;
  } SCPStatementPledges_u;
};
typedef struct SCPStatementPledges SCPStatementPledges;
#ifdef __cplusplus
extern "C" bool_t xdr_SCPStatementPledges(XDR *, SCPStatementPledges *);
#elif __STDC__
extern bool_t xdr_SCPStatementPledges(XDR *, SCPStatementPledges *);
#else  /* Old Style C */
bool_t xdr_SCPStatementPledges();
#endif /* Old Style C */

struct SCPStatement {
  NodeID nodeID;
  uint64 slotIndex;
  SCPStatementPledges pledges;
};
typedef struct SCPStatement SCPStatement;
#ifdef __cplusplus
extern "C" bool_t xdr_SCPStatement(XDR *, SCPStatement *);
#elif __STDC__
extern bool_t xdr_SCPStatement(XDR *, SCPStatement *);
#else  /* Old Style C */
bool_t xdr_SCPStatement();
#endif /* Old Style C */

struct SCPEnvelope {
  SCPStatement statement;
  Signature signature;
};
typedef struct SCPEnvelope SCPEnvelope;
#ifdef __cplusplus
extern "C" bool_t xdr_SCPEnvelope(XDR *, SCPEnvelope *);
#elif __STDC__
extern bool_t xdr_SCPEnvelope(XDR *, SCPEnvelope *);
#else  /* Old Style C */
bool_t xdr_SCPEnvelope();
#endif /* Old Style C */

struct SCPQuorumSet {
  uint32 threshold;
  struct {
    u_int validators_len;
    NodeID *validators_val;
  } validators;
  struct {
    u_int innerSets_len;
    struct SCPQuorumSet *innerSets_val;
  } innerSets;
};
typedef struct SCPQuorumSet SCPQuorumSet;
#ifdef __cplusplus
extern "C" bool_t xdr_SCPQuorumSet(XDR *, SCPQuorumSet *);
#elif __STDC__
extern bool_t xdr_SCPQuorumSet(XDR *, SCPQuorumSet *);
#else  /* Old Style C */
bool_t xdr_SCPQuorumSet();
#endif /* Old Style C */

typedef PublicKey AccountID;
#ifdef __cplusplus
extern "C" bool_t xdr_AccountID(XDR *, AccountID *);
#elif __STDC__
extern bool_t xdr_AccountID(XDR *, AccountID *);
#else  /* Old Style C */
bool_t xdr_AccountID();
#endif /* Old Style C */

typedef char Thresholds[4];
#ifdef __cplusplus
extern "C" bool_t xdr_Thresholds(XDR *, Thresholds);
#elif __STDC__
extern bool_t xdr_Thresholds(XDR *, Thresholds);
#else  /* Old Style C */
bool_t xdr_Thresholds();
#endif /* Old Style C */

typedef char *string32;
#ifdef __cplusplus
extern "C" bool_t xdr_string32(XDR *, string32 *);
#elif __STDC__
extern bool_t xdr_string32(XDR *, string32 *);
#else  /* Old Style C */
bool_t xdr_string32();
#endif /* Old Style C */

typedef char *string64;
#ifdef __cplusplus
extern "C" bool_t xdr_string64(XDR *, string64 *);
#elif __STDC__
extern bool_t xdr_string64(XDR *, string64 *);
#else  /* Old Style C */
bool_t xdr_string64();
#endif /* Old Style C */

typedef int64 SequenceNumber;
#ifdef __cplusplus
extern "C" bool_t xdr_SequenceNumber(XDR *, SequenceNumber *);
#elif __STDC__
extern bool_t xdr_SequenceNumber(XDR *, SequenceNumber *);
#else  /* Old Style C */
bool_t xdr_SequenceNumber();
#endif /* Old Style C */

typedef uint64 TimePoint;
#ifdef __cplusplus
extern "C" bool_t xdr_TimePoint(XDR *, TimePoint *);
#elif __STDC__
extern bool_t xdr_TimePoint(XDR *, TimePoint *);
#else  /* Old Style C */
bool_t xdr_TimePoint();
#endif /* Old Style C */

typedef struct {
  u_int DataValue_len;
  char *DataValue_val;
} DataValue;
#ifdef __cplusplus
extern "C" bool_t xdr_DataValue(XDR *, DataValue *);
#elif __STDC__
extern bool_t xdr_DataValue(XDR *, DataValue *);
#else  /* Old Style C */
bool_t xdr_DataValue();
#endif /* Old Style C */

typedef Hash PoolID;
#ifdef __cplusplus
extern "C" bool_t xdr_PoolID(XDR *, PoolID);
#elif __STDC__
extern bool_t xdr_PoolID(XDR *, PoolID);
#else  /* Old Style C */
bool_t xdr_PoolID();
#endif /* Old Style C */

typedef char AssetCode4[4];
#ifdef __cplusplus
extern "C" bool_t xdr_AssetCode4(XDR *, AssetCode4);
#elif __STDC__
extern bool_t xdr_AssetCode4(XDR *, AssetCode4);
#else  /* Old Style C */
bool_t xdr_AssetCode4();
#endif /* Old Style C */

typedef char AssetCode12[12];
#ifdef __cplusplus
extern "C" bool_t xdr_AssetCode12(XDR *, AssetCode12);
#elif __STDC__
extern bool_t xdr_AssetCode12(XDR *, AssetCode12);
#else  /* Old Style C */
bool_t xdr_AssetCode12();
#endif /* Old Style C */

enum AssetType {
  ASSET_TYPE_NATIVE = 0,
  ASSET_TYPE_CREDIT_ALPHANUM4 = 1,
  ASSET_TYPE_CREDIT_ALPHANUM12 = 2,
  ASSET_TYPE_POOL_SHARE = 3,
};
typedef enum AssetType AssetType;
#ifdef __cplusplus
extern "C" bool_t xdr_AssetType(XDR *, AssetType *);
#elif __STDC__
extern bool_t xdr_AssetType(XDR *, AssetType *);
#else  /* Old Style C */
bool_t xdr_AssetType();
#endif /* Old Style C */

struct AssetCode {
  AssetType type;
  union {
    AssetCode4 assetCode4;
    AssetCode12 assetCode12;
  } AssetCode_u;
};
typedef struct AssetCode AssetCode;
#ifdef __cplusplus
extern "C" bool_t xdr_AssetCode(XDR *, AssetCode *);
#elif __STDC__
extern bool_t xdr_AssetCode(XDR *, AssetCode *);
#else  /* Old Style C */
bool_t xdr_AssetCode();
#endif /* Old Style C */

struct AlphaNum4 {
  AssetCode4 assetCode;
  AccountID issuer;
};
typedef struct AlphaNum4 AlphaNum4;
#ifdef __cplusplus
extern "C" bool_t xdr_AlphaNum4(XDR *, AlphaNum4 *);
#elif __STDC__
extern bool_t xdr_AlphaNum4(XDR *, AlphaNum4 *);
#else  /* Old Style C */
bool_t xdr_AlphaNum4();
#endif /* Old Style C */

struct AlphaNum12 {
  AssetCode12 assetCode;
  AccountID issuer;
};
typedef struct AlphaNum12 AlphaNum12;
#ifdef __cplusplus
extern "C" bool_t xdr_AlphaNum12(XDR *, AlphaNum12 *);
#elif __STDC__
extern bool_t xdr_AlphaNum12(XDR *, AlphaNum12 *);
#else  /* Old Style C */
bool_t xdr_AlphaNum12();
#endif /* Old Style C */

struct Asset {
  AssetType type;
  union {
    AlphaNum4 alphaNum4;
    AlphaNum12 alphaNum12;
  } Asset_u;
};
typedef struct Asset Asset;
#ifdef __cplusplus
extern "C" bool_t xdr_Asset(XDR *, Asset *);
#elif __STDC__
extern bool_t xdr_Asset(XDR *, Asset *);
#else  /* Old Style C */
bool_t xdr_Asset();
#endif /* Old Style C */

struct Price {
  int32 n;
  int32 d;
};
typedef struct Price Price;
#ifdef __cplusplus
extern "C" bool_t xdr_Price(XDR *, Price *);
#elif __STDC__
extern bool_t xdr_Price(XDR *, Price *);
#else  /* Old Style C */
bool_t xdr_Price();
#endif /* Old Style C */

struct Liabilities {
  int64 buying;
  int64 selling;
};
typedef struct Liabilities Liabilities;
#ifdef __cplusplus
extern "C" bool_t xdr_Liabilities(XDR *, Liabilities *);
#elif __STDC__
extern bool_t xdr_Liabilities(XDR *, Liabilities *);
#else  /* Old Style C */
bool_t xdr_Liabilities();
#endif /* Old Style C */

enum ThresholdIndexes {
  THRESHOLD_MASTER_WEIGHT = 0,
  THRESHOLD_LOW = 1,
  THRESHOLD_MED = 2,
  THRESHOLD_HIGH = 3,
};
typedef enum ThresholdIndexes ThresholdIndexes;
#ifdef __cplusplus
extern "C" bool_t xdr_ThresholdIndexes(XDR *, ThresholdIndexes *);
#elif __STDC__
extern bool_t xdr_ThresholdIndexes(XDR *, ThresholdIndexes *);
#else  /* Old Style C */
bool_t xdr_ThresholdIndexes();
#endif /* Old Style C */

enum LedgerEntryType {
  ACCOUNT = 0,
  TRUSTLINE = 1,
  OFFER = 2,
  DATA = 3,
  CLAIMABLE_BALANCE = 4,
  LIQUIDITY_POOL = 5,
};
typedef enum LedgerEntryType LedgerEntryType;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerEntryType(XDR *, LedgerEntryType *);
#elif __STDC__
extern bool_t xdr_LedgerEntryType(XDR *, LedgerEntryType *);
#else  /* Old Style C */
bool_t xdr_LedgerEntryType();
#endif /* Old Style C */

struct Signer {
  SignerKey key;
  uint32 weight;
};
typedef struct Signer Signer;
#ifdef __cplusplus
extern "C" bool_t xdr_Signer(XDR *, Signer *);
#elif __STDC__
extern bool_t xdr_Signer(XDR *, Signer *);
#else  /* Old Style C */
bool_t xdr_Signer();
#endif /* Old Style C */

enum AccountFlags {
  AUTH_REQUIRED_FLAG = 0x1,
  AUTH_REVOCABLE_FLAG = 0x2,
  AUTH_IMMUTABLE_FLAG = 0x4,
  AUTH_CLAWBACK_ENABLED_FLAG = 0x8,
};
typedef enum AccountFlags AccountFlags;
#ifdef __cplusplus
extern "C" bool_t xdr_AccountFlags(XDR *, AccountFlags *);
#elif __STDC__
extern bool_t xdr_AccountFlags(XDR *, AccountFlags *);
#else  /* Old Style C */
bool_t xdr_AccountFlags();
#endif /* Old Style C */

#define MASK_ACCOUNT_FLAGS 0x7
#define MASK_ACCOUNT_FLAGS_V17 0xF
#define MAX_SIGNERS 20

typedef AccountID *SponsorshipDescriptor;
#ifdef __cplusplus
extern "C" bool_t xdr_SponsorshipDescriptor(XDR *, SponsorshipDescriptor *);
#elif __STDC__
extern bool_t xdr_SponsorshipDescriptor(XDR *, SponsorshipDescriptor *);
#else  /* Old Style C */
bool_t xdr_SponsorshipDescriptor();
#endif /* Old Style C */

struct AccountEntryExtensionV2Ext {
  int v;
  union {
  } AccountEntryExtensionV2Ext_u;
};
typedef struct AccountEntryExtensionV2Ext AccountEntryExtensionV2Ext;
#ifdef __cplusplus
extern "C" bool_t xdr_AccountEntryExtensionV2Ext(XDR *,
                                                 AccountEntryExtensionV2Ext *);
#elif __STDC__
extern bool_t xdr_AccountEntryExtensionV2Ext(XDR *,
                                             AccountEntryExtensionV2Ext *);
#else  /* Old Style C */
bool_t xdr_AccountEntryExtensionV2Ext();
#endif /* Old Style C */

struct AccountEntryExtensionV2 {
  uint32 numSponsored;
  uint32 numSponsoring;
  struct {
    u_int signerSponsoringIDs_len;
    SponsorshipDescriptor *signerSponsoringIDs_val;
  } signerSponsoringIDs;
  AccountEntryExtensionV2Ext ext;
};
typedef struct AccountEntryExtensionV2 AccountEntryExtensionV2;
#ifdef __cplusplus
extern "C" bool_t xdr_AccountEntryExtensionV2(XDR *, AccountEntryExtensionV2 *);
#elif __STDC__
extern bool_t xdr_AccountEntryExtensionV2(XDR *, AccountEntryExtensionV2 *);
#else  /* Old Style C */
bool_t xdr_AccountEntryExtensionV2();
#endif /* Old Style C */

struct AccountEntryExtensionV1Ext {
  int v;
  union {
    AccountEntryExtensionV2 v2;
  } AccountEntryExtensionV1Ext_u;
};
typedef struct AccountEntryExtensionV1Ext AccountEntryExtensionV1Ext;
#ifdef __cplusplus
extern "C" bool_t xdr_AccountEntryExtensionV1Ext(XDR *,
                                                 AccountEntryExtensionV1Ext *);
#elif __STDC__
extern bool_t xdr_AccountEntryExtensionV1Ext(XDR *,
                                             AccountEntryExtensionV1Ext *);
#else  /* Old Style C */
bool_t xdr_AccountEntryExtensionV1Ext();
#endif /* Old Style C */

struct AccountEntryExtensionV1 {
  Liabilities liabilities;
  AccountEntryExtensionV1Ext ext;
};
typedef struct AccountEntryExtensionV1 AccountEntryExtensionV1;
#ifdef __cplusplus
extern "C" bool_t xdr_AccountEntryExtensionV1(XDR *, AccountEntryExtensionV1 *);
#elif __STDC__
extern bool_t xdr_AccountEntryExtensionV1(XDR *, AccountEntryExtensionV1 *);
#else  /* Old Style C */
bool_t xdr_AccountEntryExtensionV1();
#endif /* Old Style C */

struct AccountEntryExt {
  int v;
  union {
    AccountEntryExtensionV1 v1;
  } AccountEntryExt_u;
};
typedef struct AccountEntryExt AccountEntryExt;
#ifdef __cplusplus
extern "C" bool_t xdr_AccountEntryExt(XDR *, AccountEntryExt *);
#elif __STDC__
extern bool_t xdr_AccountEntryExt(XDR *, AccountEntryExt *);
#else  /* Old Style C */
bool_t xdr_AccountEntryExt();
#endif /* Old Style C */

struct AccountEntry {
  AccountID accountID;
  int64 balance;
  SequenceNumber seqNum;
  uint32 numSubEntries;
  AccountID *inflationDest;
  uint32 flags;
  string32 homeDomain;
  Thresholds thresholds;
  struct {
    u_int signers_len;
    Signer *signers_val;
  } signers;
  AccountEntryExt ext;
};
typedef struct AccountEntry AccountEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_AccountEntry(XDR *, AccountEntry *);
#elif __STDC__
extern bool_t xdr_AccountEntry(XDR *, AccountEntry *);
#else  /* Old Style C */
bool_t xdr_AccountEntry();
#endif /* Old Style C */

enum TrustLineFlags {
  AUTHORIZED_FLAG = 1,
  AUTHORIZED_TO_MAINTAIN_LIABILITIES_FLAG = 2,
  TRUSTLINE_CLAWBACK_ENABLED_FLAG = 4,
};
typedef enum TrustLineFlags TrustLineFlags;
#ifdef __cplusplus
extern "C" bool_t xdr_TrustLineFlags(XDR *, TrustLineFlags *);
#elif __STDC__
extern bool_t xdr_TrustLineFlags(XDR *, TrustLineFlags *);
#else  /* Old Style C */
bool_t xdr_TrustLineFlags();
#endif /* Old Style C */

#define MASK_TRUSTLINE_FLAGS 1
#define MASK_TRUSTLINE_FLAGS_V13 3
#define MASK_TRUSTLINE_FLAGS_V17 7

enum LiquidityPoolType {
  LIQUIDITY_POOL_CONSTANT_PRODUCT = 0,
};
typedef enum LiquidityPoolType LiquidityPoolType;
#ifdef __cplusplus
extern "C" bool_t xdr_LiquidityPoolType(XDR *, LiquidityPoolType *);
#elif __STDC__
extern bool_t xdr_LiquidityPoolType(XDR *, LiquidityPoolType *);
#else  /* Old Style C */
bool_t xdr_LiquidityPoolType();
#endif /* Old Style C */

struct TrustLineAsset {
  AssetType type;
  union {
    AlphaNum4 alphaNum4;
    AlphaNum12 alphaNum12;
    PoolID liquidityPoolID;
  } TrustLineAsset_u;
};
typedef struct TrustLineAsset TrustLineAsset;
#ifdef __cplusplus
extern "C" bool_t xdr_TrustLineAsset(XDR *, TrustLineAsset *);
#elif __STDC__
extern bool_t xdr_TrustLineAsset(XDR *, TrustLineAsset *);
#else  /* Old Style C */
bool_t xdr_TrustLineAsset();
#endif /* Old Style C */

struct TrustLineEntryExtensionV2Ext {
  int v;
  union {
  } TrustLineEntryExtensionV2Ext_u;
};
typedef struct TrustLineEntryExtensionV2Ext TrustLineEntryExtensionV2Ext;
#ifdef __cplusplus
extern "C" bool_t
xdr_TrustLineEntryExtensionV2Ext(XDR *, TrustLineEntryExtensionV2Ext *);
#elif __STDC__
extern bool_t xdr_TrustLineEntryExtensionV2Ext(XDR *,
                                               TrustLineEntryExtensionV2Ext *);
#else  /* Old Style C */
bool_t xdr_TrustLineEntryExtensionV2Ext();
#endif /* Old Style C */

struct TrustLineEntryExtensionV2 {
  int32 liquidityPoolUseCount;
  TrustLineEntryExtensionV2Ext ext;
};
typedef struct TrustLineEntryExtensionV2 TrustLineEntryExtensionV2;
#ifdef __cplusplus
extern "C" bool_t xdr_TrustLineEntryExtensionV2(XDR *,
                                                TrustLineEntryExtensionV2 *);
#elif __STDC__
extern bool_t xdr_TrustLineEntryExtensionV2(XDR *, TrustLineEntryExtensionV2 *);
#else  /* Old Style C */
bool_t xdr_TrustLineEntryExtensionV2();
#endif /* Old Style C */

struct TrustLineEntryV1Ext {
  int v;
  union {
    TrustLineEntryExtensionV2 v2;
  } TrustLineEntryV1Ext_u;
};
typedef struct TrustLineEntryV1Ext TrustLineEntryV1Ext;
#ifdef __cplusplus
extern "C" bool_t xdr_TrustLineEntryV1Ext(XDR *, TrustLineEntryV1Ext *);
#elif __STDC__
extern bool_t xdr_TrustLineEntryV1Ext(XDR *, TrustLineEntryV1Ext *);
#else  /* Old Style C */
bool_t xdr_TrustLineEntryV1Ext();
#endif /* Old Style C */

struct TrustLineEntryV1 {
  Liabilities liabilities;
  TrustLineEntryV1Ext ext;
};
typedef struct TrustLineEntryV1 TrustLineEntryV1;
#ifdef __cplusplus
extern "C" bool_t xdr_TrustLineEntryV1(XDR *, TrustLineEntryV1 *);
#elif __STDC__
extern bool_t xdr_TrustLineEntryV1(XDR *, TrustLineEntryV1 *);
#else  /* Old Style C */
bool_t xdr_TrustLineEntryV1();
#endif /* Old Style C */

struct TrustLineEntryExt {
  int v;
  union {
    TrustLineEntryV1 v1;
  } TrustLineEntryExt_u;
};
typedef struct TrustLineEntryExt TrustLineEntryExt;
#ifdef __cplusplus
extern "C" bool_t xdr_TrustLineEntryExt(XDR *, TrustLineEntryExt *);
#elif __STDC__
extern bool_t xdr_TrustLineEntryExt(XDR *, TrustLineEntryExt *);
#else  /* Old Style C */
bool_t xdr_TrustLineEntryExt();
#endif /* Old Style C */

struct TrustLineEntry {
  AccountID accountID;
  TrustLineAsset asset;
  int64 balance;
  int64 limit;
  uint32 flags;
  TrustLineEntryExt ext;
};
typedef struct TrustLineEntry TrustLineEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_TrustLineEntry(XDR *, TrustLineEntry *);
#elif __STDC__
extern bool_t xdr_TrustLineEntry(XDR *, TrustLineEntry *);
#else  /* Old Style C */
bool_t xdr_TrustLineEntry();
#endif /* Old Style C */

enum OfferEntryFlags {
  PASSIVE_FLAG = 1,
};
typedef enum OfferEntryFlags OfferEntryFlags;
#ifdef __cplusplus
extern "C" bool_t xdr_OfferEntryFlags(XDR *, OfferEntryFlags *);
#elif __STDC__
extern bool_t xdr_OfferEntryFlags(XDR *, OfferEntryFlags *);
#else  /* Old Style C */
bool_t xdr_OfferEntryFlags();
#endif /* Old Style C */

#define MASK_OFFERENTRY_FLAGS 1

struct OfferEntryExt {
  int v;
  union {
  } OfferEntryExt_u;
};
typedef struct OfferEntryExt OfferEntryExt;
#ifdef __cplusplus
extern "C" bool_t xdr_OfferEntryExt(XDR *, OfferEntryExt *);
#elif __STDC__
extern bool_t xdr_OfferEntryExt(XDR *, OfferEntryExt *);
#else  /* Old Style C */
bool_t xdr_OfferEntryExt();
#endif /* Old Style C */

struct OfferEntry {
  AccountID sellerID;
  int64 offerID;
  Asset selling;
  Asset buying;
  int64 amount;
  Price price;
  uint32 flags;
  OfferEntryExt ext;
};
typedef struct OfferEntry OfferEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_OfferEntry(XDR *, OfferEntry *);
#elif __STDC__
extern bool_t xdr_OfferEntry(XDR *, OfferEntry *);
#else  /* Old Style C */
bool_t xdr_OfferEntry();
#endif /* Old Style C */

struct DataEntryExt {
  int v;
  union {
  } DataEntryExt_u;
};
typedef struct DataEntryExt DataEntryExt;
#ifdef __cplusplus
extern "C" bool_t xdr_DataEntryExt(XDR *, DataEntryExt *);
#elif __STDC__
extern bool_t xdr_DataEntryExt(XDR *, DataEntryExt *);
#else  /* Old Style C */
bool_t xdr_DataEntryExt();
#endif /* Old Style C */

struct DataEntry {
  AccountID accountID;
  string64 dataName;
  DataValue dataValue;
  DataEntryExt ext;
};
typedef struct DataEntry DataEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_DataEntry(XDR *, DataEntry *);
#elif __STDC__
extern bool_t xdr_DataEntry(XDR *, DataEntry *);
#else  /* Old Style C */
bool_t xdr_DataEntry();
#endif /* Old Style C */

enum ClaimPredicateType {
  CLAIM_PREDICATE_UNCONDITIONAL = 0,
  CLAIM_PREDICATE_AND = 1,
  CLAIM_PREDICATE_OR = 2,
  CLAIM_PREDICATE_NOT = 3,
  CLAIM_PREDICATE_BEFORE_ABSOLUTE_TIME = 4,
  CLAIM_PREDICATE_BEFORE_RELATIVE_TIME = 5,
};
typedef enum ClaimPredicateType ClaimPredicateType;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimPredicateType(XDR *, ClaimPredicateType *);
#elif __STDC__
extern bool_t xdr_ClaimPredicateType(XDR *, ClaimPredicateType *);
#else  /* Old Style C */
bool_t xdr_ClaimPredicateType();
#endif /* Old Style C */

struct ClaimPredicate {
  ClaimPredicateType type;
  union {
    struct {
      u_int andPredicates_len;
      struct ClaimPredicate *andPredicates_val;
    } andPredicates;
    struct {
      u_int orPredicates_len;
      struct ClaimPredicate *orPredicates_val;
    } orPredicates;
    struct ClaimPredicate *notPredicate;
    int64 absBefore;
    int64 relBefore;
  } ClaimPredicate_u;
};
typedef struct ClaimPredicate ClaimPredicate;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimPredicate(XDR *, ClaimPredicate *);
#elif __STDC__
extern bool_t xdr_ClaimPredicate(XDR *, ClaimPredicate *);
#else  /* Old Style C */
bool_t xdr_ClaimPredicate();
#endif /* Old Style C */

enum ClaimantType {
  CLAIMANT_TYPE_V0 = 0,
};
typedef enum ClaimantType ClaimantType;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimantType(XDR *, ClaimantType *);
#elif __STDC__
extern bool_t xdr_ClaimantType(XDR *, ClaimantType *);
#else  /* Old Style C */
bool_t xdr_ClaimantType();
#endif /* Old Style C */

struct ClaimantV0 {
  AccountID destination;
  ClaimPredicate predicate;
};
typedef struct ClaimantV0 ClaimantV0;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimantV0(XDR *, ClaimantV0 *);
#elif __STDC__
extern bool_t xdr_ClaimantV0(XDR *, ClaimantV0 *);
#else  /* Old Style C */
bool_t xdr_ClaimantV0();
#endif /* Old Style C */

struct Claimant {
  ClaimantType type;
  union {
    ClaimantV0 v0;
  } Claimant_u;
};
typedef struct Claimant Claimant;
#ifdef __cplusplus
extern "C" bool_t xdr_Claimant(XDR *, Claimant *);
#elif __STDC__
extern bool_t xdr_Claimant(XDR *, Claimant *);
#else  /* Old Style C */
bool_t xdr_Claimant();
#endif /* Old Style C */

enum ClaimableBalanceIDType {
  CLAIMABLE_BALANCE_ID_TYPE_V0 = 0,
};
typedef enum ClaimableBalanceIDType ClaimableBalanceIDType;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimableBalanceIDType(XDR *, ClaimableBalanceIDType *);
#elif __STDC__
extern bool_t xdr_ClaimableBalanceIDType(XDR *, ClaimableBalanceIDType *);
#else  /* Old Style C */
bool_t xdr_ClaimableBalanceIDType();
#endif /* Old Style C */

struct ClaimableBalanceID {
  ClaimableBalanceIDType type;
  union {
    Hash v0;
  } ClaimableBalanceID_u;
};
typedef struct ClaimableBalanceID ClaimableBalanceID;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimableBalanceID(XDR *, ClaimableBalanceID *);
#elif __STDC__
extern bool_t xdr_ClaimableBalanceID(XDR *, ClaimableBalanceID *);
#else  /* Old Style C */
bool_t xdr_ClaimableBalanceID();
#endif /* Old Style C */

enum ClaimableBalanceFlags {
  CLAIMABLE_BALANCE_CLAWBACK_ENABLED_FLAG = 0x1,
};
typedef enum ClaimableBalanceFlags ClaimableBalanceFlags;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimableBalanceFlags(XDR *, ClaimableBalanceFlags *);
#elif __STDC__
extern bool_t xdr_ClaimableBalanceFlags(XDR *, ClaimableBalanceFlags *);
#else  /* Old Style C */
bool_t xdr_ClaimableBalanceFlags();
#endif /* Old Style C */

#define MASK_CLAIMABLE_BALANCE_FLAGS 0x1

struct ClaimableBalanceEntryExtensionV1Ext {
  int v;
  union {
  } ClaimableBalanceEntryExtensionV1Ext_u;
};
typedef struct ClaimableBalanceEntryExtensionV1Ext
    ClaimableBalanceEntryExtensionV1Ext;
#ifdef __cplusplus
extern "C" bool_t
xdr_ClaimableBalanceEntryExtensionV1Ext(XDR *,
                                        ClaimableBalanceEntryExtensionV1Ext *);
#elif __STDC__
extern bool_t
xdr_ClaimableBalanceEntryExtensionV1Ext(XDR *,
                                        ClaimableBalanceEntryExtensionV1Ext *);
#else  /* Old Style C */
bool_t xdr_ClaimableBalanceEntryExtensionV1Ext();
#endif /* Old Style C */

struct ClaimableBalanceEntryExtensionV1 {
  ClaimableBalanceEntryExtensionV1Ext ext;
  uint32 flags;
};
typedef struct ClaimableBalanceEntryExtensionV1
    ClaimableBalanceEntryExtensionV1;
#ifdef __cplusplus
extern "C" bool_t
xdr_ClaimableBalanceEntryExtensionV1(XDR *, ClaimableBalanceEntryExtensionV1 *);
#elif __STDC__
extern bool_t
xdr_ClaimableBalanceEntryExtensionV1(XDR *, ClaimableBalanceEntryExtensionV1 *);
#else  /* Old Style C */
bool_t xdr_ClaimableBalanceEntryExtensionV1();
#endif /* Old Style C */

struct ClaimableBalanceEntryExt {
  int v;
  union {
    ClaimableBalanceEntryExtensionV1 v1;
  } ClaimableBalanceEntryExt_u;
};
typedef struct ClaimableBalanceEntryExt ClaimableBalanceEntryExt;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimableBalanceEntryExt(XDR *,
                                               ClaimableBalanceEntryExt *);
#elif __STDC__
extern bool_t xdr_ClaimableBalanceEntryExt(XDR *, ClaimableBalanceEntryExt *);
#else  /* Old Style C */
bool_t xdr_ClaimableBalanceEntryExt();
#endif /* Old Style C */

struct ClaimableBalanceEntry {
  ClaimableBalanceID balanceID;
  struct {
    u_int claimants_len;
    Claimant *claimants_val;
  } claimants;
  Asset asset;
  int64 amount;
  ClaimableBalanceEntryExt ext;
};
typedef struct ClaimableBalanceEntry ClaimableBalanceEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimableBalanceEntry(XDR *, ClaimableBalanceEntry *);
#elif __STDC__
extern bool_t xdr_ClaimableBalanceEntry(XDR *, ClaimableBalanceEntry *);
#else  /* Old Style C */
bool_t xdr_ClaimableBalanceEntry();
#endif /* Old Style C */

struct LiquidityPoolConstantProductParameters {
  Asset assetA;
  Asset assetB;
  int32 fee;
};
typedef struct LiquidityPoolConstantProductParameters
    LiquidityPoolConstantProductParameters;
#ifdef __cplusplus
extern "C" bool_t xdr_LiquidityPoolConstantProductParameters(
    XDR *, LiquidityPoolConstantProductParameters *);
#elif __STDC__
extern bool_t xdr_LiquidityPoolConstantProductParameters(
    XDR *, LiquidityPoolConstantProductParameters *);
#else  /* Old Style C */
bool_t xdr_LiquidityPoolConstantProductParameters();
#endif /* Old Style C */

struct LiquidityPoolEntryConstantProduct {
  LiquidityPoolConstantProductParameters params;
  int64 reserveA;
  int64 reserveB;
  int64 totalPoolShares;
  int64 poolSharesTrustLineCount;
};
typedef struct LiquidityPoolEntryConstantProduct
    LiquidityPoolEntryConstantProduct;
#ifdef __cplusplus
extern "C" bool_t
xdr_LiquidityPoolEntryConstantProduct(XDR *,
                                      LiquidityPoolEntryConstantProduct *);
#elif __STDC__
extern bool_t
xdr_LiquidityPoolEntryConstantProduct(XDR *,
                                      LiquidityPoolEntryConstantProduct *);
#else  /* Old Style C */
bool_t xdr_LiquidityPoolEntryConstantProduct();
#endif /* Old Style C */

struct LiquidityPoolEntryBody {
  LiquidityPoolType type;
  union {
    LiquidityPoolEntryConstantProduct constantProduct;
  } LiquidityPoolEntryBody_u;
};
typedef struct LiquidityPoolEntryBody LiquidityPoolEntryBody;
#ifdef __cplusplus
extern "C" bool_t xdr_LiquidityPoolEntryBody(XDR *, LiquidityPoolEntryBody *);
#elif __STDC__
extern bool_t xdr_LiquidityPoolEntryBody(XDR *, LiquidityPoolEntryBody *);
#else  /* Old Style C */
bool_t xdr_LiquidityPoolEntryBody();
#endif /* Old Style C */

struct LiquidityPoolEntry {
  PoolID liquidityPoolID;
  LiquidityPoolEntryBody body;
};
typedef struct LiquidityPoolEntry LiquidityPoolEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_LiquidityPoolEntry(XDR *, LiquidityPoolEntry *);
#elif __STDC__
extern bool_t xdr_LiquidityPoolEntry(XDR *, LiquidityPoolEntry *);
#else  /* Old Style C */
bool_t xdr_LiquidityPoolEntry();
#endif /* Old Style C */

struct LedgerEntryExtensionV1Ext {
  int v;
  union {
  } LedgerEntryExtensionV1Ext_u;
};
typedef struct LedgerEntryExtensionV1Ext LedgerEntryExtensionV1Ext;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerEntryExtensionV1Ext(XDR *,
                                                LedgerEntryExtensionV1Ext *);
#elif __STDC__
extern bool_t xdr_LedgerEntryExtensionV1Ext(XDR *, LedgerEntryExtensionV1Ext *);
#else  /* Old Style C */
bool_t xdr_LedgerEntryExtensionV1Ext();
#endif /* Old Style C */

struct LedgerEntryExtensionV1 {
  SponsorshipDescriptor sponsoringID;
  LedgerEntryExtensionV1Ext ext;
};
typedef struct LedgerEntryExtensionV1 LedgerEntryExtensionV1;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerEntryExtensionV1(XDR *, LedgerEntryExtensionV1 *);
#elif __STDC__
extern bool_t xdr_LedgerEntryExtensionV1(XDR *, LedgerEntryExtensionV1 *);
#else  /* Old Style C */
bool_t xdr_LedgerEntryExtensionV1();
#endif /* Old Style C */

struct LedgerEntryData {
  LedgerEntryType type;
  union {
    AccountEntry account;
    TrustLineEntry trustLine;
    OfferEntry offer;
    DataEntry data;
    ClaimableBalanceEntry claimableBalance;
    LiquidityPoolEntry liquidityPool;
  } LedgerEntryData_u;
};
typedef struct LedgerEntryData LedgerEntryData;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerEntryData(XDR *, LedgerEntryData *);
#elif __STDC__
extern bool_t xdr_LedgerEntryData(XDR *, LedgerEntryData *);
#else  /* Old Style C */
bool_t xdr_LedgerEntryData();
#endif /* Old Style C */

struct LedgerEntryExt {
  int v;
  union {
    LedgerEntryExtensionV1 v1;
  } LedgerEntryExt_u;
};
typedef struct LedgerEntryExt LedgerEntryExt;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerEntryExt(XDR *, LedgerEntryExt *);
#elif __STDC__
extern bool_t xdr_LedgerEntryExt(XDR *, LedgerEntryExt *);
#else  /* Old Style C */
bool_t xdr_LedgerEntryExt();
#endif /* Old Style C */

struct LedgerEntry {
  uint32 lastModifiedLedgerSeq;
  LedgerEntryData data;
  LedgerEntryExt ext;
};
typedef struct LedgerEntry LedgerEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerEntry(XDR *, LedgerEntry *);
#elif __STDC__
extern bool_t xdr_LedgerEntry(XDR *, LedgerEntry *);
#else  /* Old Style C */
bool_t xdr_LedgerEntry();
#endif /* Old Style C */

struct LedgerKeyAccount {
  AccountID accountID;
};
typedef struct LedgerKeyAccount LedgerKeyAccount;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerKeyAccount(XDR *, LedgerKeyAccount *);
#elif __STDC__
extern bool_t xdr_LedgerKeyAccount(XDR *, LedgerKeyAccount *);
#else  /* Old Style C */
bool_t xdr_LedgerKeyAccount();
#endif /* Old Style C */

struct LedgerKeyTrustLine {
  AccountID accountID;
  TrustLineAsset asset;
};
typedef struct LedgerKeyTrustLine LedgerKeyTrustLine;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerKeyTrustLine(XDR *, LedgerKeyTrustLine *);
#elif __STDC__
extern bool_t xdr_LedgerKeyTrustLine(XDR *, LedgerKeyTrustLine *);
#else  /* Old Style C */
bool_t xdr_LedgerKeyTrustLine();
#endif /* Old Style C */

struct LedgerKeyOffer {
  AccountID sellerID;
  int64 offerID;
};
typedef struct LedgerKeyOffer LedgerKeyOffer;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerKeyOffer(XDR *, LedgerKeyOffer *);
#elif __STDC__
extern bool_t xdr_LedgerKeyOffer(XDR *, LedgerKeyOffer *);
#else  /* Old Style C */
bool_t xdr_LedgerKeyOffer();
#endif /* Old Style C */

struct LedgerKeyData {
  AccountID accountID;
  string64 dataName;
};
typedef struct LedgerKeyData LedgerKeyData;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerKeyData(XDR *, LedgerKeyData *);
#elif __STDC__
extern bool_t xdr_LedgerKeyData(XDR *, LedgerKeyData *);
#else  /* Old Style C */
bool_t xdr_LedgerKeyData();
#endif /* Old Style C */

struct LedgerKeyClaimableBalance {
  ClaimableBalanceID balanceID;
};
typedef struct LedgerKeyClaimableBalance LedgerKeyClaimableBalance;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerKeyClaimableBalance(XDR *,
                                                LedgerKeyClaimableBalance *);
#elif __STDC__
extern bool_t xdr_LedgerKeyClaimableBalance(XDR *, LedgerKeyClaimableBalance *);
#else  /* Old Style C */
bool_t xdr_LedgerKeyClaimableBalance();
#endif /* Old Style C */

struct LedgerKeyLiquidityPool {
  PoolID liquidityPoolID;
};
typedef struct LedgerKeyLiquidityPool LedgerKeyLiquidityPool;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerKeyLiquidityPool(XDR *, LedgerKeyLiquidityPool *);
#elif __STDC__
extern bool_t xdr_LedgerKeyLiquidityPool(XDR *, LedgerKeyLiquidityPool *);
#else  /* Old Style C */
bool_t xdr_LedgerKeyLiquidityPool();
#endif /* Old Style C */

struct LedgerKey {
  LedgerEntryType type;
  union {
    LedgerKeyAccount account;
    LedgerKeyTrustLine trustLine;
    LedgerKeyOffer offer;
    LedgerKeyData data;
    LedgerKeyClaimableBalance claimableBalance;
    LedgerKeyLiquidityPool liquidityPool;
  } LedgerKey_u;
};
typedef struct LedgerKey LedgerKey;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerKey(XDR *, LedgerKey *);
#elif __STDC__
extern bool_t xdr_LedgerKey(XDR *, LedgerKey *);
#else  /* Old Style C */
bool_t xdr_LedgerKey();
#endif /* Old Style C */

enum EnvelopeType {
  ENVELOPE_TYPE_TX_V0 = 0,
  ENVELOPE_TYPE_SCP = 1,
  ENVELOPE_TYPE_TX = 2,
  ENVELOPE_TYPE_AUTH = 3,
  ENVELOPE_TYPE_SCPVALUE = 4,
  ENVELOPE_TYPE_TX_FEE_BUMP = 5,
  ENVELOPE_TYPE_OP_ID = 6,
};
typedef enum EnvelopeType EnvelopeType;
#ifdef __cplusplus
extern "C" bool_t xdr_EnvelopeType(XDR *, EnvelopeType *);
#elif __STDC__
extern bool_t xdr_EnvelopeType(XDR *, EnvelopeType *);
#else  /* Old Style C */
bool_t xdr_EnvelopeType();
#endif /* Old Style C */

struct LiquidityPoolParameters {
  LiquidityPoolType type;
  union {
    LiquidityPoolConstantProductParameters constantProduct;
  } LiquidityPoolParameters_u;
};
typedef struct LiquidityPoolParameters LiquidityPoolParameters;
#ifdef __cplusplus
extern "C" bool_t xdr_LiquidityPoolParameters(XDR *, LiquidityPoolParameters *);
#elif __STDC__
extern bool_t xdr_LiquidityPoolParameters(XDR *, LiquidityPoolParameters *);
#else  /* Old Style C */
bool_t xdr_LiquidityPoolParameters();
#endif /* Old Style C */

struct MuxedAccountMed25519 {
  uint64 id;
  uint256 ed25519;
};
typedef struct MuxedAccountMed25519 MuxedAccountMed25519;
#ifdef __cplusplus
extern "C" bool_t xdr_MuxedAccountMed25519(XDR *, MuxedAccountMed25519 *);
#elif __STDC__
extern bool_t xdr_MuxedAccountMed25519(XDR *, MuxedAccountMed25519 *);
#else  /* Old Style C */
bool_t xdr_MuxedAccountMed25519();
#endif /* Old Style C */

struct MuxedAccount {
  CryptoKeyType type;
  union {
    uint256 ed25519;
    MuxedAccountMed25519 med25519;
  } MuxedAccount_u;
};
typedef struct MuxedAccount MuxedAccount;
#ifdef __cplusplus
extern "C" bool_t xdr_MuxedAccount(XDR *, MuxedAccount *);
#elif __STDC__
extern bool_t xdr_MuxedAccount(XDR *, MuxedAccount *);
#else  /* Old Style C */
bool_t xdr_MuxedAccount();
#endif /* Old Style C */

struct DecoratedSignature {
  SignatureHint hint;
  Signature signature;
};
typedef struct DecoratedSignature DecoratedSignature;
#ifdef __cplusplus
extern "C" bool_t xdr_DecoratedSignature(XDR *, DecoratedSignature *);
#elif __STDC__
extern bool_t xdr_DecoratedSignature(XDR *, DecoratedSignature *);
#else  /* Old Style C */
bool_t xdr_DecoratedSignature();
#endif /* Old Style C */

enum OperationType {
  CREATE_ACCOUNT = 0,
  PAYMENT = 1,
  PATH_PAYMENT_STRICT_RECEIVE = 2,
  MANAGE_SELL_OFFER = 3,
  CREATE_PASSIVE_SELL_OFFER = 4,
  SET_OPTIONS = 5,
  CHANGE_TRUST = 6,
  ALLOW_TRUST = 7,
  ACCOUNT_MERGE = 8,
  INFLATION = 9,
  MANAGE_DATA = 10,
  BUMP_SEQUENCE = 11,
  MANAGE_BUY_OFFER = 12,
  PATH_PAYMENT_STRICT_SEND = 13,
  CREATE_CLAIMABLE_BALANCE = 14,
  CLAIM_CLAIMABLE_BALANCE = 15,
  BEGIN_SPONSORING_FUTURE_RESERVES = 16,
  END_SPONSORING_FUTURE_RESERVES = 17,
  REVOKE_SPONSORSHIP = 18,
  CLAWBACK = 19,
  CLAWBACK_CLAIMABLE_BALANCE = 20,
  SET_TRUST_LINE_FLAGS = 21,
  LIQUIDITY_POOL_DEPOSIT = 22,
  LIQUIDITY_POOL_WITHDRAW = 23,
};
typedef enum OperationType OperationType;
#ifdef __cplusplus
extern "C" bool_t xdr_OperationType(XDR *, OperationType *);
#elif __STDC__
extern bool_t xdr_OperationType(XDR *, OperationType *);
#else  /* Old Style C */
bool_t xdr_OperationType();
#endif /* Old Style C */

struct CreateAccountOp {
  AccountID destination;
  int64 startingBalance;
};
typedef struct CreateAccountOp CreateAccountOp;
#ifdef __cplusplus
extern "C" bool_t xdr_CreateAccountOp(XDR *, CreateAccountOp *);
#elif __STDC__
extern bool_t xdr_CreateAccountOp(XDR *, CreateAccountOp *);
#else  /* Old Style C */
bool_t xdr_CreateAccountOp();
#endif /* Old Style C */

struct PaymentOp {
  MuxedAccount destination;
  Asset asset;
  int64 amount;
};
typedef struct PaymentOp PaymentOp;
#ifdef __cplusplus
extern "C" bool_t xdr_PaymentOp(XDR *, PaymentOp *);
#elif __STDC__
extern bool_t xdr_PaymentOp(XDR *, PaymentOp *);
#else  /* Old Style C */
bool_t xdr_PaymentOp();
#endif /* Old Style C */

struct PathPaymentStrictReceiveOp {
  Asset sendAsset;
  int64 sendMax;
  MuxedAccount destination;
  Asset destAsset;
  int64 destAmount;
  struct {
    u_int path_len;
    Asset *path_val;
  } path;
};
typedef struct PathPaymentStrictReceiveOp PathPaymentStrictReceiveOp;
#ifdef __cplusplus
extern "C" bool_t xdr_PathPaymentStrictReceiveOp(XDR *,
                                                 PathPaymentStrictReceiveOp *);
#elif __STDC__
extern bool_t xdr_PathPaymentStrictReceiveOp(XDR *,
                                             PathPaymentStrictReceiveOp *);
#else  /* Old Style C */
bool_t xdr_PathPaymentStrictReceiveOp();
#endif /* Old Style C */

struct PathPaymentStrictSendOp {
  Asset sendAsset;
  int64 sendAmount;
  MuxedAccount destination;
  Asset destAsset;
  int64 destMin;
  struct {
    u_int path_len;
    Asset *path_val;
  } path;
};
typedef struct PathPaymentStrictSendOp PathPaymentStrictSendOp;
#ifdef __cplusplus
extern "C" bool_t xdr_PathPaymentStrictSendOp(XDR *, PathPaymentStrictSendOp *);
#elif __STDC__
extern bool_t xdr_PathPaymentStrictSendOp(XDR *, PathPaymentStrictSendOp *);
#else  /* Old Style C */
bool_t xdr_PathPaymentStrictSendOp();
#endif /* Old Style C */

struct ManageSellOfferOp {
  Asset selling;
  Asset buying;
  int64 amount;
  Price price;
  int64 offerID;
};
typedef struct ManageSellOfferOp ManageSellOfferOp;
#ifdef __cplusplus
extern "C" bool_t xdr_ManageSellOfferOp(XDR *, ManageSellOfferOp *);
#elif __STDC__
extern bool_t xdr_ManageSellOfferOp(XDR *, ManageSellOfferOp *);
#else  /* Old Style C */
bool_t xdr_ManageSellOfferOp();
#endif /* Old Style C */

struct ManageBuyOfferOp {
  Asset selling;
  Asset buying;
  int64 buyAmount;
  Price price;
  int64 offerID;
};
typedef struct ManageBuyOfferOp ManageBuyOfferOp;
#ifdef __cplusplus
extern "C" bool_t xdr_ManageBuyOfferOp(XDR *, ManageBuyOfferOp *);
#elif __STDC__
extern bool_t xdr_ManageBuyOfferOp(XDR *, ManageBuyOfferOp *);
#else  /* Old Style C */
bool_t xdr_ManageBuyOfferOp();
#endif /* Old Style C */

struct CreatePassiveSellOfferOp {
  Asset selling;
  Asset buying;
  int64 amount;
  Price price;
};
typedef struct CreatePassiveSellOfferOp CreatePassiveSellOfferOp;
#ifdef __cplusplus
extern "C" bool_t xdr_CreatePassiveSellOfferOp(XDR *,
                                               CreatePassiveSellOfferOp *);
#elif __STDC__
extern bool_t xdr_CreatePassiveSellOfferOp(XDR *, CreatePassiveSellOfferOp *);
#else  /* Old Style C */
bool_t xdr_CreatePassiveSellOfferOp();
#endif /* Old Style C */

struct SetOptionsOp {
  AccountID *inflationDest;
  uint32 *clearFlags;
  uint32 *setFlags;
  uint32 *masterWeight;
  uint32 *lowThreshold;
  uint32 *medThreshold;
  uint32 *highThreshold;
  string32 *homeDomain;
  Signer *signer;
};
typedef struct SetOptionsOp SetOptionsOp;
#ifdef __cplusplus
extern "C" bool_t xdr_SetOptionsOp(XDR *, SetOptionsOp *);
#elif __STDC__
extern bool_t xdr_SetOptionsOp(XDR *, SetOptionsOp *);
#else  /* Old Style C */
bool_t xdr_SetOptionsOp();
#endif /* Old Style C */

struct ChangeTrustAsset {
  AssetType type;
  union {
    AlphaNum4 alphaNum4;
    AlphaNum12 alphaNum12;
    LiquidityPoolParameters liquidityPool;
  } ChangeTrustAsset_u;
};
typedef struct ChangeTrustAsset ChangeTrustAsset;
#ifdef __cplusplus
extern "C" bool_t xdr_ChangeTrustAsset(XDR *, ChangeTrustAsset *);
#elif __STDC__
extern bool_t xdr_ChangeTrustAsset(XDR *, ChangeTrustAsset *);
#else  /* Old Style C */
bool_t xdr_ChangeTrustAsset();
#endif /* Old Style C */

struct ChangeTrustOp {
  ChangeTrustAsset line;
  int64 limit;
};
typedef struct ChangeTrustOp ChangeTrustOp;
#ifdef __cplusplus
extern "C" bool_t xdr_ChangeTrustOp(XDR *, ChangeTrustOp *);
#elif __STDC__
extern bool_t xdr_ChangeTrustOp(XDR *, ChangeTrustOp *);
#else  /* Old Style C */
bool_t xdr_ChangeTrustOp();
#endif /* Old Style C */

struct AllowTrustOp {
  AccountID trustor;
  AssetCode asset;
  uint32 authorize;
};
typedef struct AllowTrustOp AllowTrustOp;
#ifdef __cplusplus
extern "C" bool_t xdr_AllowTrustOp(XDR *, AllowTrustOp *);
#elif __STDC__
extern bool_t xdr_AllowTrustOp(XDR *, AllowTrustOp *);
#else  /* Old Style C */
bool_t xdr_AllowTrustOp();
#endif /* Old Style C */

struct ManageDataOp {
  string64 dataName;
  DataValue *dataValue;
};
typedef struct ManageDataOp ManageDataOp;
#ifdef __cplusplus
extern "C" bool_t xdr_ManageDataOp(XDR *, ManageDataOp *);
#elif __STDC__
extern bool_t xdr_ManageDataOp(XDR *, ManageDataOp *);
#else  /* Old Style C */
bool_t xdr_ManageDataOp();
#endif /* Old Style C */

struct BumpSequenceOp {
  SequenceNumber bumpTo;
};
typedef struct BumpSequenceOp BumpSequenceOp;
#ifdef __cplusplus
extern "C" bool_t xdr_BumpSequenceOp(XDR *, BumpSequenceOp *);
#elif __STDC__
extern bool_t xdr_BumpSequenceOp(XDR *, BumpSequenceOp *);
#else  /* Old Style C */
bool_t xdr_BumpSequenceOp();
#endif /* Old Style C */

struct CreateClaimableBalanceOp {
  Asset asset;
  int64 amount;
  struct {
    u_int claimants_len;
    Claimant *claimants_val;
  } claimants;
};
typedef struct CreateClaimableBalanceOp CreateClaimableBalanceOp;
#ifdef __cplusplus
extern "C" bool_t xdr_CreateClaimableBalanceOp(XDR *,
                                               CreateClaimableBalanceOp *);
#elif __STDC__
extern bool_t xdr_CreateClaimableBalanceOp(XDR *, CreateClaimableBalanceOp *);
#else  /* Old Style C */
bool_t xdr_CreateClaimableBalanceOp();
#endif /* Old Style C */

struct ClaimClaimableBalanceOp {
  ClaimableBalanceID balanceID;
};
typedef struct ClaimClaimableBalanceOp ClaimClaimableBalanceOp;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimClaimableBalanceOp(XDR *, ClaimClaimableBalanceOp *);
#elif __STDC__
extern bool_t xdr_ClaimClaimableBalanceOp(XDR *, ClaimClaimableBalanceOp *);
#else  /* Old Style C */
bool_t xdr_ClaimClaimableBalanceOp();
#endif /* Old Style C */

struct BeginSponsoringFutureReservesOp {
  AccountID sponsoredID;
};
typedef struct BeginSponsoringFutureReservesOp BeginSponsoringFutureReservesOp;
#ifdef __cplusplus
extern "C" bool_t
xdr_BeginSponsoringFutureReservesOp(XDR *, BeginSponsoringFutureReservesOp *);
#elif __STDC__
extern bool_t
xdr_BeginSponsoringFutureReservesOp(XDR *, BeginSponsoringFutureReservesOp *);
#else  /* Old Style C */
bool_t xdr_BeginSponsoringFutureReservesOp();
#endif /* Old Style C */

enum RevokeSponsorshipType {
  REVOKE_SPONSORSHIP_LEDGER_ENTRY = 0,
  REVOKE_SPONSORSHIP_SIGNER = 1,
};
typedef enum RevokeSponsorshipType RevokeSponsorshipType;
#ifdef __cplusplus
extern "C" bool_t xdr_RevokeSponsorshipType(XDR *, RevokeSponsorshipType *);
#elif __STDC__
extern bool_t xdr_RevokeSponsorshipType(XDR *, RevokeSponsorshipType *);
#else  /* Old Style C */
bool_t xdr_RevokeSponsorshipType();
#endif /* Old Style C */

struct RevokeSponsorshipOpSigner {
  AccountID accountID;
  SignerKey signerKey;
};
typedef struct RevokeSponsorshipOpSigner RevokeSponsorshipOpSigner;
#ifdef __cplusplus
extern "C" bool_t xdr_RevokeSponsorshipOpSigner(XDR *,
                                                RevokeSponsorshipOpSigner *);
#elif __STDC__
extern bool_t xdr_RevokeSponsorshipOpSigner(XDR *, RevokeSponsorshipOpSigner *);
#else  /* Old Style C */
bool_t xdr_RevokeSponsorshipOpSigner();
#endif /* Old Style C */

struct RevokeSponsorshipOp {
  RevokeSponsorshipType type;
  union {
    LedgerKey ledgerKey;
    RevokeSponsorshipOpSigner signer;
  } RevokeSponsorshipOp_u;
};
typedef struct RevokeSponsorshipOp RevokeSponsorshipOp;
#ifdef __cplusplus
extern "C" bool_t xdr_RevokeSponsorshipOp(XDR *, RevokeSponsorshipOp *);
#elif __STDC__
extern bool_t xdr_RevokeSponsorshipOp(XDR *, RevokeSponsorshipOp *);
#else  /* Old Style C */
bool_t xdr_RevokeSponsorshipOp();
#endif /* Old Style C */

struct ClawbackOp {
  Asset asset;
  MuxedAccount from_;
  int64 amount;
};
typedef struct ClawbackOp ClawbackOp;
#ifdef __cplusplus
extern "C" bool_t xdr_ClawbackOp(XDR *, ClawbackOp *);
#elif __STDC__
extern bool_t xdr_ClawbackOp(XDR *, ClawbackOp *);
#else  /* Old Style C */
bool_t xdr_ClawbackOp();
#endif /* Old Style C */

struct ClawbackClaimableBalanceOp {
  ClaimableBalanceID balanceID;
};
typedef struct ClawbackClaimableBalanceOp ClawbackClaimableBalanceOp;
#ifdef __cplusplus
extern "C" bool_t xdr_ClawbackClaimableBalanceOp(XDR *,
                                                 ClawbackClaimableBalanceOp *);
#elif __STDC__
extern bool_t xdr_ClawbackClaimableBalanceOp(XDR *,
                                             ClawbackClaimableBalanceOp *);
#else  /* Old Style C */
bool_t xdr_ClawbackClaimableBalanceOp();
#endif /* Old Style C */

struct SetTrustLineFlagsOp {
  AccountID trustor;
  Asset asset;
  uint32 clearFlags;
  uint32 setFlags;
};
typedef struct SetTrustLineFlagsOp SetTrustLineFlagsOp;
#ifdef __cplusplus
extern "C" bool_t xdr_SetTrustLineFlagsOp(XDR *, SetTrustLineFlagsOp *);
#elif __STDC__
extern bool_t xdr_SetTrustLineFlagsOp(XDR *, SetTrustLineFlagsOp *);
#else  /* Old Style C */
bool_t xdr_SetTrustLineFlagsOp();
#endif /* Old Style C */

#define LIQUIDITY_POOL_FEE_V18 30

struct LiquidityPoolDepositOp {
  PoolID liquidityPoolID;
  int64 maxAmountA;
  int64 maxAmountB;
  Price minPrice;
  Price maxPrice;
};
typedef struct LiquidityPoolDepositOp LiquidityPoolDepositOp;
#ifdef __cplusplus
extern "C" bool_t xdr_LiquidityPoolDepositOp(XDR *, LiquidityPoolDepositOp *);
#elif __STDC__
extern bool_t xdr_LiquidityPoolDepositOp(XDR *, LiquidityPoolDepositOp *);
#else  /* Old Style C */
bool_t xdr_LiquidityPoolDepositOp();
#endif /* Old Style C */

struct LiquidityPoolWithdrawOp {
  PoolID liquidityPoolID;
  int64 amount;
  int64 minAmountA;
  int64 minAmountB;
};
typedef struct LiquidityPoolWithdrawOp LiquidityPoolWithdrawOp;
#ifdef __cplusplus
extern "C" bool_t xdr_LiquidityPoolWithdrawOp(XDR *, LiquidityPoolWithdrawOp *);
#elif __STDC__
extern bool_t xdr_LiquidityPoolWithdrawOp(XDR *, LiquidityPoolWithdrawOp *);
#else  /* Old Style C */
bool_t xdr_LiquidityPoolWithdrawOp();
#endif /* Old Style C */

struct OperationBody {
  OperationType type;
  union {
    CreateAccountOp createAccountOp;
    PaymentOp paymentOp;
    PathPaymentStrictReceiveOp pathPaymentStrictReceiveOp;
    ManageSellOfferOp manageSellOfferOp;
    CreatePassiveSellOfferOp createPassiveSellOfferOp;
    SetOptionsOp setOptionsOp;
    ChangeTrustOp changeTrustOp;
    AllowTrustOp allowTrustOp;
    MuxedAccount destination;
    ManageDataOp manageDataOp;
    BumpSequenceOp bumpSequenceOp;
    ManageBuyOfferOp manageBuyOfferOp;
    PathPaymentStrictSendOp pathPaymentStrictSendOp;
    CreateClaimableBalanceOp createClaimableBalanceOp;
    ClaimClaimableBalanceOp claimClaimableBalanceOp;
    BeginSponsoringFutureReservesOp beginSponsoringFutureReservesOp;
    RevokeSponsorshipOp revokeSponsorshipOp;
    ClawbackOp clawbackOp;
    ClawbackClaimableBalanceOp clawbackClaimableBalanceOp;
    SetTrustLineFlagsOp setTrustLineFlagsOp;
    LiquidityPoolDepositOp liquidityPoolDepositOp;
    LiquidityPoolWithdrawOp liquidityPoolWithdrawOp;
  } OperationBody_u;
};
typedef struct OperationBody OperationBody;
#ifdef __cplusplus
extern "C" bool_t xdr_OperationBody(XDR *, OperationBody *);
#elif __STDC__
extern bool_t xdr_OperationBody(XDR *, OperationBody *);
#else  /* Old Style C */
bool_t xdr_OperationBody();
#endif /* Old Style C */

struct Operation {
  MuxedAccount *sourceAccount;
  OperationBody body;
};
typedef struct Operation Operation;
#ifdef __cplusplus
extern "C" bool_t xdr_Operation(XDR *, Operation *);
#elif __STDC__
extern bool_t xdr_Operation(XDR *, Operation *);
#else  /* Old Style C */
bool_t xdr_Operation();
#endif /* Old Style C */

struct EnvelopeTypeOperationID {
  AccountID sourceAccount;
  SequenceNumber seqNum;
  uint32 opNum;
};
typedef struct EnvelopeTypeOperationID EnvelopeTypeOperationID;
#ifdef __cplusplus
extern "C" bool_t xdr_EnvelopeTypeOperationID(XDR *, EnvelopeTypeOperationID *);
#elif __STDC__
extern bool_t xdr_EnvelopeTypeOperationID(XDR *, EnvelopeTypeOperationID *);
#else  /* Old Style C */
bool_t xdr_EnvelopeTypeOperationID();
#endif /* Old Style C */

struct OperationID {
  EnvelopeType type;
  union {
    EnvelopeTypeOperationID id;
  } OperationID_u;
};
typedef struct OperationID OperationID;
#ifdef __cplusplus
extern "C" bool_t xdr_OperationID(XDR *, OperationID *);
#elif __STDC__
extern bool_t xdr_OperationID(XDR *, OperationID *);
#else  /* Old Style C */
bool_t xdr_OperationID();
#endif /* Old Style C */

enum MemoType {
  MEMO_NONE = 0,
  MEMO_TEXT = 1,
  MEMO_ID = 2,
  MEMO_HASH = 3,
  MEMO_RETURN = 4,
};
typedef enum MemoType MemoType;
#ifdef __cplusplus
extern "C" bool_t xdr_MemoType(XDR *, MemoType *);
#elif __STDC__
extern bool_t xdr_MemoType(XDR *, MemoType *);
#else  /* Old Style C */
bool_t xdr_MemoType();
#endif /* Old Style C */

struct Memo {
  MemoType type;
  union {
    char *text;
    uint64 id;
    Hash hash;
    Hash retHash;
  } Memo_u;
};
typedef struct Memo Memo;
#ifdef __cplusplus
extern "C" bool_t xdr_Memo(XDR *, Memo *);
#elif __STDC__
extern bool_t xdr_Memo(XDR *, Memo *);
#else  /* Old Style C */
bool_t xdr_Memo();
#endif /* Old Style C */

struct TimeBounds {
  TimePoint minTime;
  TimePoint maxTime;
};
typedef struct TimeBounds TimeBounds;
#ifdef __cplusplus
extern "C" bool_t xdr_TimeBounds(XDR *, TimeBounds *);
#elif __STDC__
extern bool_t xdr_TimeBounds(XDR *, TimeBounds *);
#else  /* Old Style C */
bool_t xdr_TimeBounds();
#endif /* Old Style C */

#define MAX_OPS_PER_TX 100

struct TransactionV0Ext {
  int v;
  union {
  } TransactionV0Ext_u;
};
typedef struct TransactionV0Ext TransactionV0Ext;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionV0Ext(XDR *, TransactionV0Ext *);
#elif __STDC__
extern bool_t xdr_TransactionV0Ext(XDR *, TransactionV0Ext *);
#else  /* Old Style C */
bool_t xdr_TransactionV0Ext();
#endif /* Old Style C */

struct TransactionV0 {
  uint256 sourceAccountEd25519;
  uint32 fee;
  SequenceNumber seqNum;
  TimeBounds *timeBounds;
  Memo memo;
  struct {
    u_int operations_len;
    Operation *operations_val;
  } operations;
  TransactionV0Ext ext;
};
typedef struct TransactionV0 TransactionV0;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionV0(XDR *, TransactionV0 *);
#elif __STDC__
extern bool_t xdr_TransactionV0(XDR *, TransactionV0 *);
#else  /* Old Style C */
bool_t xdr_TransactionV0();
#endif /* Old Style C */

struct TransactionV0Envelope {
  TransactionV0 tx;
  struct {
    u_int signatures_len;
    DecoratedSignature *signatures_val;
  } signatures;
};
typedef struct TransactionV0Envelope TransactionV0Envelope;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionV0Envelope(XDR *, TransactionV0Envelope *);
#elif __STDC__
extern bool_t xdr_TransactionV0Envelope(XDR *, TransactionV0Envelope *);
#else  /* Old Style C */
bool_t xdr_TransactionV0Envelope();
#endif /* Old Style C */

struct TransactionExt {
  int v;
  union {
  } TransactionExt_u;
};
typedef struct TransactionExt TransactionExt;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionExt(XDR *, TransactionExt *);
#elif __STDC__
extern bool_t xdr_TransactionExt(XDR *, TransactionExt *);
#else  /* Old Style C */
bool_t xdr_TransactionExt();
#endif /* Old Style C */

struct Transaction {
  MuxedAccount sourceAccount;
  uint32 fee;
  SequenceNumber seqNum;
  TimeBounds *timeBounds;
  Memo memo;
  struct {
    u_int operations_len;
    Operation *operations_val;
  } operations;
  TransactionExt ext;
};
typedef struct Transaction Transaction;
#ifdef __cplusplus
extern "C" bool_t xdr_Transaction(XDR *, Transaction *);
#elif __STDC__
extern bool_t xdr_Transaction(XDR *, Transaction *);
#else  /* Old Style C */
bool_t xdr_Transaction();
#endif /* Old Style C */

struct TransactionV1Envelope {
  Transaction tx;
  struct {
    u_int signatures_len;
    DecoratedSignature *signatures_val;
  } signatures;
};
typedef struct TransactionV1Envelope TransactionV1Envelope;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionV1Envelope(XDR *, TransactionV1Envelope *);
#elif __STDC__
extern bool_t xdr_TransactionV1Envelope(XDR *, TransactionV1Envelope *);
#else  /* Old Style C */
bool_t xdr_TransactionV1Envelope();
#endif /* Old Style C */

struct FeeBumpTransactionInnerTx {
  EnvelopeType type;
  union {
    TransactionV1Envelope v1;
  } FeeBumpTransactionInnerTx_u;
};
typedef struct FeeBumpTransactionInnerTx FeeBumpTransactionInnerTx;
#ifdef __cplusplus
extern "C" bool_t xdr_FeeBumpTransactionInnerTx(XDR *,
                                                FeeBumpTransactionInnerTx *);
#elif __STDC__
extern bool_t xdr_FeeBumpTransactionInnerTx(XDR *, FeeBumpTransactionInnerTx *);
#else  /* Old Style C */
bool_t xdr_FeeBumpTransactionInnerTx();
#endif /* Old Style C */

struct FeeBumpTransactionExt {
  int v;
  union {
  } FeeBumpTransactionExt_u;
};
typedef struct FeeBumpTransactionExt FeeBumpTransactionExt;
#ifdef __cplusplus
extern "C" bool_t xdr_FeeBumpTransactionExt(XDR *, FeeBumpTransactionExt *);
#elif __STDC__
extern bool_t xdr_FeeBumpTransactionExt(XDR *, FeeBumpTransactionExt *);
#else  /* Old Style C */
bool_t xdr_FeeBumpTransactionExt();
#endif /* Old Style C */

struct FeeBumpTransaction {
  MuxedAccount feeSource;
  int64 fee;
  FeeBumpTransactionInnerTx innerTx;
  FeeBumpTransactionExt ext;
};
typedef struct FeeBumpTransaction FeeBumpTransaction;
#ifdef __cplusplus
extern "C" bool_t xdr_FeeBumpTransaction(XDR *, FeeBumpTransaction *);
#elif __STDC__
extern bool_t xdr_FeeBumpTransaction(XDR *, FeeBumpTransaction *);
#else  /* Old Style C */
bool_t xdr_FeeBumpTransaction();
#endif /* Old Style C */

struct FeeBumpTransactionEnvelope {
  FeeBumpTransaction tx;
  struct {
    u_int signatures_len;
    DecoratedSignature *signatures_val;
  } signatures;
};
typedef struct FeeBumpTransactionEnvelope FeeBumpTransactionEnvelope;
#ifdef __cplusplus
extern "C" bool_t xdr_FeeBumpTransactionEnvelope(XDR *,
                                                 FeeBumpTransactionEnvelope *);
#elif __STDC__
extern bool_t xdr_FeeBumpTransactionEnvelope(XDR *,
                                             FeeBumpTransactionEnvelope *);
#else  /* Old Style C */
bool_t xdr_FeeBumpTransactionEnvelope();
#endif /* Old Style C */

struct TransactionEnvelope {
  EnvelopeType type;
  union {
    TransactionV0Envelope v0;
    TransactionV1Envelope v1;
    FeeBumpTransactionEnvelope feeBump;
  } TransactionEnvelope_u;
};
typedef struct TransactionEnvelope TransactionEnvelope;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionEnvelope(XDR *, TransactionEnvelope *);
#elif __STDC__
extern bool_t xdr_TransactionEnvelope(XDR *, TransactionEnvelope *);
#else  /* Old Style C */
bool_t xdr_TransactionEnvelope();
#endif /* Old Style C */

struct TransactionSignaturePayloadTaggedTransaction {
  EnvelopeType type;
  union {
    Transaction tx;
    FeeBumpTransaction feeBump;
  } TransactionSignaturePayloadTaggedTransaction_u;
};
typedef struct TransactionSignaturePayloadTaggedTransaction
    TransactionSignaturePayloadTaggedTransaction;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionSignaturePayloadTaggedTransaction(
    XDR *, TransactionSignaturePayloadTaggedTransaction *);
#elif __STDC__
extern bool_t xdr_TransactionSignaturePayloadTaggedTransaction(
    XDR *, TransactionSignaturePayloadTaggedTransaction *);
#else  /* Old Style C */
bool_t xdr_TransactionSignaturePayloadTaggedTransaction();
#endif /* Old Style C */

struct TransactionSignaturePayload {
  Hash networkId;
  TransactionSignaturePayloadTaggedTransaction taggedTransaction;
};
typedef struct TransactionSignaturePayload TransactionSignaturePayload;
#ifdef __cplusplus
extern "C" bool_t
xdr_TransactionSignaturePayload(XDR *, TransactionSignaturePayload *);
#elif __STDC__
extern bool_t xdr_TransactionSignaturePayload(XDR *,
                                              TransactionSignaturePayload *);
#else  /* Old Style C */
bool_t xdr_TransactionSignaturePayload();
#endif /* Old Style C */

enum ClaimAtomType {
  CLAIM_ATOM_TYPE_V0 = 0,
  CLAIM_ATOM_TYPE_ORDER_BOOK = 1,
  CLAIM_ATOM_TYPE_LIQUIDITY_POOL = 2,
};
typedef enum ClaimAtomType ClaimAtomType;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimAtomType(XDR *, ClaimAtomType *);
#elif __STDC__
extern bool_t xdr_ClaimAtomType(XDR *, ClaimAtomType *);
#else  /* Old Style C */
bool_t xdr_ClaimAtomType();
#endif /* Old Style C */

struct ClaimOfferAtomV0 {
  uint256 sellerEd25519;
  int64 offerID;
  Asset assetSold;
  int64 amountSold;
  Asset assetBought;
  int64 amountBought;
};
typedef struct ClaimOfferAtomV0 ClaimOfferAtomV0;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimOfferAtomV0(XDR *, ClaimOfferAtomV0 *);
#elif __STDC__
extern bool_t xdr_ClaimOfferAtomV0(XDR *, ClaimOfferAtomV0 *);
#else  /* Old Style C */
bool_t xdr_ClaimOfferAtomV0();
#endif /* Old Style C */

struct ClaimOfferAtom {
  AccountID sellerID;
  int64 offerID;
  Asset assetSold;
  int64 amountSold;
  Asset assetBought;
  int64 amountBought;
};
typedef struct ClaimOfferAtom ClaimOfferAtom;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimOfferAtom(XDR *, ClaimOfferAtom *);
#elif __STDC__
extern bool_t xdr_ClaimOfferAtom(XDR *, ClaimOfferAtom *);
#else  /* Old Style C */
bool_t xdr_ClaimOfferAtom();
#endif /* Old Style C */

struct ClaimLiquidityAtom {
  PoolID liquidityPoolID;
  Asset assetSold;
  int64 amountSold;
  Asset assetBought;
  int64 amountBought;
};
typedef struct ClaimLiquidityAtom ClaimLiquidityAtom;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimLiquidityAtom(XDR *, ClaimLiquidityAtom *);
#elif __STDC__
extern bool_t xdr_ClaimLiquidityAtom(XDR *, ClaimLiquidityAtom *);
#else  /* Old Style C */
bool_t xdr_ClaimLiquidityAtom();
#endif /* Old Style C */

struct ClaimAtom {
  ClaimAtomType type;
  union {
    ClaimOfferAtomV0 v0;
    ClaimOfferAtom orderBook;
    ClaimLiquidityAtom liquidityPool;
  } ClaimAtom_u;
};
typedef struct ClaimAtom ClaimAtom;
#ifdef __cplusplus
extern "C" bool_t xdr_ClaimAtom(XDR *, ClaimAtom *);
#elif __STDC__
extern bool_t xdr_ClaimAtom(XDR *, ClaimAtom *);
#else  /* Old Style C */
bool_t xdr_ClaimAtom();
#endif /* Old Style C */

enum CreateAccountResultCode {
  CREATE_ACCOUNT_SUCCESS = 0,
  CREATE_ACCOUNT_MALFORMED = -1,
  CREATE_ACCOUNT_UNDERFUNDED = -2,
  CREATE_ACCOUNT_LOW_RESERVE = -3,
  CREATE_ACCOUNT_ALREADY_EXIST = -4,
};
typedef enum CreateAccountResultCode CreateAccountResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_CreateAccountResultCode(XDR *, CreateAccountResultCode *);
#elif __STDC__
extern bool_t xdr_CreateAccountResultCode(XDR *, CreateAccountResultCode *);
#else  /* Old Style C */
bool_t xdr_CreateAccountResultCode();
#endif /* Old Style C */

struct CreateAccountResult {
  CreateAccountResultCode code;
  union {
  } CreateAccountResult_u;
};
typedef struct CreateAccountResult CreateAccountResult;
#ifdef __cplusplus
extern "C" bool_t xdr_CreateAccountResult(XDR *, CreateAccountResult *);
#elif __STDC__
extern bool_t xdr_CreateAccountResult(XDR *, CreateAccountResult *);
#else  /* Old Style C */
bool_t xdr_CreateAccountResult();
#endif /* Old Style C */

enum PaymentResultCode {
  PAYMENT_SUCCESS = 0,
  PAYMENT_MALFORMED = -1,
  PAYMENT_UNDERFUNDED = -2,
  PAYMENT_SRC_NO_TRUST = -3,
  PAYMENT_SRC_NOT_AUTHORIZED = -4,
  PAYMENT_NO_DESTINATION = -5,
  PAYMENT_NO_TRUST = -6,
  PAYMENT_NOT_AUTHORIZED = -7,
  PAYMENT_LINE_FULL = -8,
  PAYMENT_NO_ISSUER = -9,
};
typedef enum PaymentResultCode PaymentResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_PaymentResultCode(XDR *, PaymentResultCode *);
#elif __STDC__
extern bool_t xdr_PaymentResultCode(XDR *, PaymentResultCode *);
#else  /* Old Style C */
bool_t xdr_PaymentResultCode();
#endif /* Old Style C */

struct PaymentResult {
  PaymentResultCode code;
  union {
  } PaymentResult_u;
};
typedef struct PaymentResult PaymentResult;
#ifdef __cplusplus
extern "C" bool_t xdr_PaymentResult(XDR *, PaymentResult *);
#elif __STDC__
extern bool_t xdr_PaymentResult(XDR *, PaymentResult *);
#else  /* Old Style C */
bool_t xdr_PaymentResult();
#endif /* Old Style C */

enum PathPaymentStrictReceiveResultCode {
  PATH_PAYMENT_STRICT_RECEIVE_SUCCESS = 0,
  PATH_PAYMENT_STRICT_RECEIVE_MALFORMED = -1,
  PATH_PAYMENT_STRICT_RECEIVE_UNDERFUNDED = -2,
  PATH_PAYMENT_STRICT_RECEIVE_SRC_NO_TRUST = -3,
  PATH_PAYMENT_STRICT_RECEIVE_SRC_NOT_AUTHORIZED = -4,
  PATH_PAYMENT_STRICT_RECEIVE_NO_DESTINATION = -5,
  PATH_PAYMENT_STRICT_RECEIVE_NO_TRUST = -6,
  PATH_PAYMENT_STRICT_RECEIVE_NOT_AUTHORIZED = -7,
  PATH_PAYMENT_STRICT_RECEIVE_LINE_FULL = -8,
  PATH_PAYMENT_STRICT_RECEIVE_NO_ISSUER = -9,
  PATH_PAYMENT_STRICT_RECEIVE_TOO_FEW_OFFERS = -10,
  PATH_PAYMENT_STRICT_RECEIVE_OFFER_CROSS_SELF = -11,
  PATH_PAYMENT_STRICT_RECEIVE_OVER_SENDMAX = -12,
};
typedef enum PathPaymentStrictReceiveResultCode
    PathPaymentStrictReceiveResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_PathPaymentStrictReceiveResultCode(XDR *,
                                       PathPaymentStrictReceiveResultCode *);
#elif __STDC__
extern bool_t
xdr_PathPaymentStrictReceiveResultCode(XDR *,
                                       PathPaymentStrictReceiveResultCode *);
#else  /* Old Style C */
bool_t xdr_PathPaymentStrictReceiveResultCode();
#endif /* Old Style C */

struct SimplePaymentResult {
  AccountID destination;
  Asset asset;
  int64 amount;
};
typedef struct SimplePaymentResult SimplePaymentResult;
#ifdef __cplusplus
extern "C" bool_t xdr_SimplePaymentResult(XDR *, SimplePaymentResult *);
#elif __STDC__
extern bool_t xdr_SimplePaymentResult(XDR *, SimplePaymentResult *);
#else  /* Old Style C */
bool_t xdr_SimplePaymentResult();
#endif /* Old Style C */

struct PathPaymentStrictReceiveResultSuccess {
  struct {
    u_int offers_len;
    ClaimAtom *offers_val;
  } offers;
  SimplePaymentResult last;
};
typedef struct PathPaymentStrictReceiveResultSuccess
    PathPaymentStrictReceiveResultSuccess;
#ifdef __cplusplus
extern "C" bool_t xdr_PathPaymentStrictReceiveResultSuccess(
    XDR *, PathPaymentStrictReceiveResultSuccess *);
#elif __STDC__
extern bool_t xdr_PathPaymentStrictReceiveResultSuccess(
    XDR *, PathPaymentStrictReceiveResultSuccess *);
#else  /* Old Style C */
bool_t xdr_PathPaymentStrictReceiveResultSuccess();
#endif /* Old Style C */

struct PathPaymentStrictReceiveResult {
  PathPaymentStrictReceiveResultCode code;
  union {
    PathPaymentStrictReceiveResultSuccess success;
    Asset noIssuer;
  } PathPaymentStrictReceiveResult_u;
};
typedef struct PathPaymentStrictReceiveResult PathPaymentStrictReceiveResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_PathPaymentStrictReceiveResult(XDR *, PathPaymentStrictReceiveResult *);
#elif __STDC__
extern bool_t
xdr_PathPaymentStrictReceiveResult(XDR *, PathPaymentStrictReceiveResult *);
#else  /* Old Style C */
bool_t xdr_PathPaymentStrictReceiveResult();
#endif /* Old Style C */

enum PathPaymentStrictSendResultCode {
  PATH_PAYMENT_STRICT_SEND_SUCCESS = 0,
  PATH_PAYMENT_STRICT_SEND_MALFORMED = -1,
  PATH_PAYMENT_STRICT_SEND_UNDERFUNDED = -2,
  PATH_PAYMENT_STRICT_SEND_SRC_NO_TRUST = -3,
  PATH_PAYMENT_STRICT_SEND_SRC_NOT_AUTHORIZED = -4,
  PATH_PAYMENT_STRICT_SEND_NO_DESTINATION = -5,
  PATH_PAYMENT_STRICT_SEND_NO_TRUST = -6,
  PATH_PAYMENT_STRICT_SEND_NOT_AUTHORIZED = -7,
  PATH_PAYMENT_STRICT_SEND_LINE_FULL = -8,
  PATH_PAYMENT_STRICT_SEND_NO_ISSUER = -9,
  PATH_PAYMENT_STRICT_SEND_TOO_FEW_OFFERS = -10,
  PATH_PAYMENT_STRICT_SEND_OFFER_CROSS_SELF = -11,
  PATH_PAYMENT_STRICT_SEND_UNDER_DESTMIN = -12,
};
typedef enum PathPaymentStrictSendResultCode PathPaymentStrictSendResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_PathPaymentStrictSendResultCode(XDR *, PathPaymentStrictSendResultCode *);
#elif __STDC__
extern bool_t
xdr_PathPaymentStrictSendResultCode(XDR *, PathPaymentStrictSendResultCode *);
#else  /* Old Style C */
bool_t xdr_PathPaymentStrictSendResultCode();
#endif /* Old Style C */

struct PathPaymentStrictSendResultSuccess {
  struct {
    u_int offers_len;
    ClaimAtom *offers_val;
  } offers;
  SimplePaymentResult last;
};
typedef struct PathPaymentStrictSendResultSuccess
    PathPaymentStrictSendResultSuccess;
#ifdef __cplusplus
extern "C" bool_t
xdr_PathPaymentStrictSendResultSuccess(XDR *,
                                       PathPaymentStrictSendResultSuccess *);
#elif __STDC__
extern bool_t
xdr_PathPaymentStrictSendResultSuccess(XDR *,
                                       PathPaymentStrictSendResultSuccess *);
#else  /* Old Style C */
bool_t xdr_PathPaymentStrictSendResultSuccess();
#endif /* Old Style C */

struct PathPaymentStrictSendResult {
  PathPaymentStrictSendResultCode code;
  union {
    PathPaymentStrictSendResultSuccess success;
    Asset noIssuer;
  } PathPaymentStrictSendResult_u;
};
typedef struct PathPaymentStrictSendResult PathPaymentStrictSendResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_PathPaymentStrictSendResult(XDR *, PathPaymentStrictSendResult *);
#elif __STDC__
extern bool_t xdr_PathPaymentStrictSendResult(XDR *,
                                              PathPaymentStrictSendResult *);
#else  /* Old Style C */
bool_t xdr_PathPaymentStrictSendResult();
#endif /* Old Style C */

enum ManageSellOfferResultCode {
  MANAGE_SELL_OFFER_SUCCESS = 0,
  MANAGE_SELL_OFFER_MALFORMED = -1,
  MANAGE_SELL_OFFER_SELL_NO_TRUST = -2,
  MANAGE_SELL_OFFER_BUY_NO_TRUST = -3,
  MANAGE_SELL_OFFER_SELL_NOT_AUTHORIZED = -4,
  MANAGE_SELL_OFFER_BUY_NOT_AUTHORIZED = -5,
  MANAGE_SELL_OFFER_LINE_FULL = -6,
  MANAGE_SELL_OFFER_UNDERFUNDED = -7,
  MANAGE_SELL_OFFER_CROSS_SELF = -8,
  MANAGE_SELL_OFFER_SELL_NO_ISSUER = -9,
  MANAGE_SELL_OFFER_BUY_NO_ISSUER = -10,
  MANAGE_SELL_OFFER_NOT_FOUND = -11,
  MANAGE_SELL_OFFER_LOW_RESERVE = -12,
};
typedef enum ManageSellOfferResultCode ManageSellOfferResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_ManageSellOfferResultCode(XDR *,
                                                ManageSellOfferResultCode *);
#elif __STDC__
extern bool_t xdr_ManageSellOfferResultCode(XDR *, ManageSellOfferResultCode *);
#else  /* Old Style C */
bool_t xdr_ManageSellOfferResultCode();
#endif /* Old Style C */

enum ManageOfferEffect {
  MANAGE_OFFER_CREATED = 0,
  MANAGE_OFFER_UPDATED = 1,
  MANAGE_OFFER_DELETED = 2,
};
typedef enum ManageOfferEffect ManageOfferEffect;
#ifdef __cplusplus
extern "C" bool_t xdr_ManageOfferEffect(XDR *, ManageOfferEffect *);
#elif __STDC__
extern bool_t xdr_ManageOfferEffect(XDR *, ManageOfferEffect *);
#else  /* Old Style C */
bool_t xdr_ManageOfferEffect();
#endif /* Old Style C */

struct ManageOfferSuccessResultOffer {
  ManageOfferEffect effect;
  union {
    OfferEntry offer;
  } ManageOfferSuccessResultOffer_u;
};
typedef struct ManageOfferSuccessResultOffer ManageOfferSuccessResultOffer;
#ifdef __cplusplus
extern "C" bool_t
xdr_ManageOfferSuccessResultOffer(XDR *, ManageOfferSuccessResultOffer *);
#elif __STDC__
extern bool_t
xdr_ManageOfferSuccessResultOffer(XDR *, ManageOfferSuccessResultOffer *);
#else  /* Old Style C */
bool_t xdr_ManageOfferSuccessResultOffer();
#endif /* Old Style C */

struct ManageOfferSuccessResult {
  struct {
    u_int offersClaimed_len;
    ClaimAtom *offersClaimed_val;
  } offersClaimed;
  ManageOfferSuccessResultOffer offer;
};
typedef struct ManageOfferSuccessResult ManageOfferSuccessResult;
#ifdef __cplusplus
extern "C" bool_t xdr_ManageOfferSuccessResult(XDR *,
                                               ManageOfferSuccessResult *);
#elif __STDC__
extern bool_t xdr_ManageOfferSuccessResult(XDR *, ManageOfferSuccessResult *);
#else  /* Old Style C */
bool_t xdr_ManageOfferSuccessResult();
#endif /* Old Style C */

struct ManageSellOfferResult {
  ManageSellOfferResultCode code;
  union {
    ManageOfferSuccessResult success;
  } ManageSellOfferResult_u;
};
typedef struct ManageSellOfferResult ManageSellOfferResult;
#ifdef __cplusplus
extern "C" bool_t xdr_ManageSellOfferResult(XDR *, ManageSellOfferResult *);
#elif __STDC__
extern bool_t xdr_ManageSellOfferResult(XDR *, ManageSellOfferResult *);
#else  /* Old Style C */
bool_t xdr_ManageSellOfferResult();
#endif /* Old Style C */

enum ManageBuyOfferResultCode {
  MANAGE_BUY_OFFER_SUCCESS = 0,
  MANAGE_BUY_OFFER_MALFORMED = -1,
  MANAGE_BUY_OFFER_SELL_NO_TRUST = -2,
  MANAGE_BUY_OFFER_BUY_NO_TRUST = -3,
  MANAGE_BUY_OFFER_SELL_NOT_AUTHORIZED = -4,
  MANAGE_BUY_OFFER_BUY_NOT_AUTHORIZED = -5,
  MANAGE_BUY_OFFER_LINE_FULL = -6,
  MANAGE_BUY_OFFER_UNDERFUNDED = -7,
  MANAGE_BUY_OFFER_CROSS_SELF = -8,
  MANAGE_BUY_OFFER_SELL_NO_ISSUER = -9,
  MANAGE_BUY_OFFER_BUY_NO_ISSUER = -10,
  MANAGE_BUY_OFFER_NOT_FOUND = -11,
  MANAGE_BUY_OFFER_LOW_RESERVE = -12,
};
typedef enum ManageBuyOfferResultCode ManageBuyOfferResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_ManageBuyOfferResultCode(XDR *,
                                               ManageBuyOfferResultCode *);
#elif __STDC__
extern bool_t xdr_ManageBuyOfferResultCode(XDR *, ManageBuyOfferResultCode *);
#else  /* Old Style C */
bool_t xdr_ManageBuyOfferResultCode();
#endif /* Old Style C */

struct ManageBuyOfferResult {
  ManageBuyOfferResultCode code;
  union {
    ManageOfferSuccessResult success;
  } ManageBuyOfferResult_u;
};
typedef struct ManageBuyOfferResult ManageBuyOfferResult;
#ifdef __cplusplus
extern "C" bool_t xdr_ManageBuyOfferResult(XDR *, ManageBuyOfferResult *);
#elif __STDC__
extern bool_t xdr_ManageBuyOfferResult(XDR *, ManageBuyOfferResult *);
#else  /* Old Style C */
bool_t xdr_ManageBuyOfferResult();
#endif /* Old Style C */

enum SetOptionsResultCode {
  SET_OPTIONS_SUCCESS = 0,
  SET_OPTIONS_LOW_RESERVE = -1,
  SET_OPTIONS_TOO_MANY_SIGNERS = -2,
  SET_OPTIONS_BAD_FLAGS = -3,
  SET_OPTIONS_INVALID_INFLATION = -4,
  SET_OPTIONS_CANT_CHANGE = -5,
  SET_OPTIONS_UNKNOWN_FLAG = -6,
  SET_OPTIONS_THRESHOLD_OUT_OF_RANGE = -7,
  SET_OPTIONS_BAD_SIGNER = -8,
  SET_OPTIONS_INVALID_HOME_DOMAIN = -9,
  SET_OPTIONS_AUTH_REVOCABLE_REQUIRED = -10,
};
typedef enum SetOptionsResultCode SetOptionsResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_SetOptionsResultCode(XDR *, SetOptionsResultCode *);
#elif __STDC__
extern bool_t xdr_SetOptionsResultCode(XDR *, SetOptionsResultCode *);
#else  /* Old Style C */
bool_t xdr_SetOptionsResultCode();
#endif /* Old Style C */

struct SetOptionsResult {
  SetOptionsResultCode code;
  union {
  } SetOptionsResult_u;
};
typedef struct SetOptionsResult SetOptionsResult;
#ifdef __cplusplus
extern "C" bool_t xdr_SetOptionsResult(XDR *, SetOptionsResult *);
#elif __STDC__
extern bool_t xdr_SetOptionsResult(XDR *, SetOptionsResult *);
#else  /* Old Style C */
bool_t xdr_SetOptionsResult();
#endif /* Old Style C */

enum ChangeTrustResultCode {
  CHANGE_TRUST_SUCCESS = 0,
  CHANGE_TRUST_MALFORMED = -1,
  CHANGE_TRUST_NO_ISSUER = -2,
  CHANGE_TRUST_INVALID_LIMIT = -3,
  CHANGE_TRUST_LOW_RESERVE = -4,
  CHANGE_TRUST_SELF_NOT_ALLOWED = -5,
  CHANGE_TRUST_TRUST_LINE_MISSING = -6,
  CHANGE_TRUST_CANNOT_DELETE = -7,
  CHANGE_TRUST_NOT_AUTH_MAINTAIN_LIABILITIES = -8,
};
typedef enum ChangeTrustResultCode ChangeTrustResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_ChangeTrustResultCode(XDR *, ChangeTrustResultCode *);
#elif __STDC__
extern bool_t xdr_ChangeTrustResultCode(XDR *, ChangeTrustResultCode *);
#else  /* Old Style C */
bool_t xdr_ChangeTrustResultCode();
#endif /* Old Style C */

struct ChangeTrustResult {
  ChangeTrustResultCode code;
  union {
  } ChangeTrustResult_u;
};
typedef struct ChangeTrustResult ChangeTrustResult;
#ifdef __cplusplus
extern "C" bool_t xdr_ChangeTrustResult(XDR *, ChangeTrustResult *);
#elif __STDC__
extern bool_t xdr_ChangeTrustResult(XDR *, ChangeTrustResult *);
#else  /* Old Style C */
bool_t xdr_ChangeTrustResult();
#endif /* Old Style C */

enum AllowTrustResultCode {
  ALLOW_TRUST_SUCCESS = 0,
  ALLOW_TRUST_MALFORMED = -1,
  ALLOW_TRUST_NO_TRUST_LINE = -2,
  ALLOW_TRUST_TRUST_NOT_REQUIRED = -3,
  ALLOW_TRUST_CANT_REVOKE = -4,
  ALLOW_TRUST_SELF_NOT_ALLOWED = -5,
};
typedef enum AllowTrustResultCode AllowTrustResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_AllowTrustResultCode(XDR *, AllowTrustResultCode *);
#elif __STDC__
extern bool_t xdr_AllowTrustResultCode(XDR *, AllowTrustResultCode *);
#else  /* Old Style C */
bool_t xdr_AllowTrustResultCode();
#endif /* Old Style C */

struct AllowTrustResult {
  AllowTrustResultCode code;
  union {
  } AllowTrustResult_u;
};
typedef struct AllowTrustResult AllowTrustResult;
#ifdef __cplusplus
extern "C" bool_t xdr_AllowTrustResult(XDR *, AllowTrustResult *);
#elif __STDC__
extern bool_t xdr_AllowTrustResult(XDR *, AllowTrustResult *);
#else  /* Old Style C */
bool_t xdr_AllowTrustResult();
#endif /* Old Style C */

enum AccountMergeResultCode {
  ACCOUNT_MERGE_SUCCESS = 0,
  ACCOUNT_MERGE_MALFORMED = -1,
  ACCOUNT_MERGE_NO_ACCOUNT = -2,
  ACCOUNT_MERGE_IMMUTABLE_SET = -3,
  ACCOUNT_MERGE_HAS_SUB_ENTRIES = -4,
  ACCOUNT_MERGE_SEQNUM_TOO_FAR = -5,
  ACCOUNT_MERGE_DEST_FULL = -6,
  ACCOUNT_MERGE_IS_SPONSOR = -7,
};
typedef enum AccountMergeResultCode AccountMergeResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_AccountMergeResultCode(XDR *, AccountMergeResultCode *);
#elif __STDC__
extern bool_t xdr_AccountMergeResultCode(XDR *, AccountMergeResultCode *);
#else  /* Old Style C */
bool_t xdr_AccountMergeResultCode();
#endif /* Old Style C */

struct AccountMergeResult {
  AccountMergeResultCode code;
  union {
    int64 sourceAccountBalance;
  } AccountMergeResult_u;
};
typedef struct AccountMergeResult AccountMergeResult;
#ifdef __cplusplus
extern "C" bool_t xdr_AccountMergeResult(XDR *, AccountMergeResult *);
#elif __STDC__
extern bool_t xdr_AccountMergeResult(XDR *, AccountMergeResult *);
#else  /* Old Style C */
bool_t xdr_AccountMergeResult();
#endif /* Old Style C */

enum InflationResultCode {
  INFLATION_SUCCESS = 0,
  INFLATION_NOT_TIME = -1,
};
typedef enum InflationResultCode InflationResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_InflationResultCode(XDR *, InflationResultCode *);
#elif __STDC__
extern bool_t xdr_InflationResultCode(XDR *, InflationResultCode *);
#else  /* Old Style C */
bool_t xdr_InflationResultCode();
#endif /* Old Style C */

struct InflationPayout {
  AccountID destination;
  int64 amount;
};
typedef struct InflationPayout InflationPayout;
#ifdef __cplusplus
extern "C" bool_t xdr_InflationPayout(XDR *, InflationPayout *);
#elif __STDC__
extern bool_t xdr_InflationPayout(XDR *, InflationPayout *);
#else  /* Old Style C */
bool_t xdr_InflationPayout();
#endif /* Old Style C */

struct InflationResult {
  InflationResultCode code;
  union {
    struct {
      u_int payouts_len;
      InflationPayout *payouts_val;
    } payouts;
  } InflationResult_u;
};
typedef struct InflationResult InflationResult;
#ifdef __cplusplus
extern "C" bool_t xdr_InflationResult(XDR *, InflationResult *);
#elif __STDC__
extern bool_t xdr_InflationResult(XDR *, InflationResult *);
#else  /* Old Style C */
bool_t xdr_InflationResult();
#endif /* Old Style C */

enum ManageDataResultCode {
  MANAGE_DATA_SUCCESS = 0,
  MANAGE_DATA_NOT_SUPPORTED_YET = -1,
  MANAGE_DATA_NAME_NOT_FOUND = -2,
  MANAGE_DATA_LOW_RESERVE = -3,
  MANAGE_DATA_INVALID_NAME = -4,
};
typedef enum ManageDataResultCode ManageDataResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_ManageDataResultCode(XDR *, ManageDataResultCode *);
#elif __STDC__
extern bool_t xdr_ManageDataResultCode(XDR *, ManageDataResultCode *);
#else  /* Old Style C */
bool_t xdr_ManageDataResultCode();
#endif /* Old Style C */

struct ManageDataResult {
  ManageDataResultCode code;
  union {
  } ManageDataResult_u;
};
typedef struct ManageDataResult ManageDataResult;
#ifdef __cplusplus
extern "C" bool_t xdr_ManageDataResult(XDR *, ManageDataResult *);
#elif __STDC__
extern bool_t xdr_ManageDataResult(XDR *, ManageDataResult *);
#else  /* Old Style C */
bool_t xdr_ManageDataResult();
#endif /* Old Style C */

enum BumpSequenceResultCode {
  BUMP_SEQUENCE_SUCCESS = 0,
  BUMP_SEQUENCE_BAD_SEQ = -1,
};
typedef enum BumpSequenceResultCode BumpSequenceResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_BumpSequenceResultCode(XDR *, BumpSequenceResultCode *);
#elif __STDC__
extern bool_t xdr_BumpSequenceResultCode(XDR *, BumpSequenceResultCode *);
#else  /* Old Style C */
bool_t xdr_BumpSequenceResultCode();
#endif /* Old Style C */

struct BumpSequenceResult {
  BumpSequenceResultCode code;
  union {
  } BumpSequenceResult_u;
};
typedef struct BumpSequenceResult BumpSequenceResult;
#ifdef __cplusplus
extern "C" bool_t xdr_BumpSequenceResult(XDR *, BumpSequenceResult *);
#elif __STDC__
extern bool_t xdr_BumpSequenceResult(XDR *, BumpSequenceResult *);
#else  /* Old Style C */
bool_t xdr_BumpSequenceResult();
#endif /* Old Style C */

enum CreateClaimableBalanceResultCode {
  CREATE_CLAIMABLE_BALANCE_SUCCESS = 0,
  CREATE_CLAIMABLE_BALANCE_MALFORMED = -1,
  CREATE_CLAIMABLE_BALANCE_LOW_RESERVE = -2,
  CREATE_CLAIMABLE_BALANCE_NO_TRUST = -3,
  CREATE_CLAIMABLE_BALANCE_NOT_AUTHORIZED = -4,
  CREATE_CLAIMABLE_BALANCE_UNDERFUNDED = -5,
};
typedef enum CreateClaimableBalanceResultCode CreateClaimableBalanceResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_CreateClaimableBalanceResultCode(XDR *, CreateClaimableBalanceResultCode *);
#elif __STDC__
extern bool_t
xdr_CreateClaimableBalanceResultCode(XDR *, CreateClaimableBalanceResultCode *);
#else  /* Old Style C */
bool_t xdr_CreateClaimableBalanceResultCode();
#endif /* Old Style C */

struct CreateClaimableBalanceResult {
  CreateClaimableBalanceResultCode code;
  union {
    ClaimableBalanceID balanceID;
  } CreateClaimableBalanceResult_u;
};
typedef struct CreateClaimableBalanceResult CreateClaimableBalanceResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_CreateClaimableBalanceResult(XDR *, CreateClaimableBalanceResult *);
#elif __STDC__
extern bool_t xdr_CreateClaimableBalanceResult(XDR *,
                                               CreateClaimableBalanceResult *);
#else  /* Old Style C */
bool_t xdr_CreateClaimableBalanceResult();
#endif /* Old Style C */

enum ClaimClaimableBalanceResultCode {
  CLAIM_CLAIMABLE_BALANCE_SUCCESS = 0,
  CLAIM_CLAIMABLE_BALANCE_DOES_NOT_EXIST = -1,
  CLAIM_CLAIMABLE_BALANCE_CANNOT_CLAIM = -2,
  CLAIM_CLAIMABLE_BALANCE_LINE_FULL = -3,
  CLAIM_CLAIMABLE_BALANCE_NO_TRUST = -4,
  CLAIM_CLAIMABLE_BALANCE_NOT_AUTHORIZED = -5,
};
typedef enum ClaimClaimableBalanceResultCode ClaimClaimableBalanceResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_ClaimClaimableBalanceResultCode(XDR *, ClaimClaimableBalanceResultCode *);
#elif __STDC__
extern bool_t
xdr_ClaimClaimableBalanceResultCode(XDR *, ClaimClaimableBalanceResultCode *);
#else  /* Old Style C */
bool_t xdr_ClaimClaimableBalanceResultCode();
#endif /* Old Style C */

struct ClaimClaimableBalanceResult {
  ClaimClaimableBalanceResultCode code;
  union {
  } ClaimClaimableBalanceResult_u;
};
typedef struct ClaimClaimableBalanceResult ClaimClaimableBalanceResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_ClaimClaimableBalanceResult(XDR *, ClaimClaimableBalanceResult *);
#elif __STDC__
extern bool_t xdr_ClaimClaimableBalanceResult(XDR *,
                                              ClaimClaimableBalanceResult *);
#else  /* Old Style C */
bool_t xdr_ClaimClaimableBalanceResult();
#endif /* Old Style C */

enum BeginSponsoringFutureReservesResultCode {
  BEGIN_SPONSORING_FUTURE_RESERVES_SUCCESS = 0,
  BEGIN_SPONSORING_FUTURE_RESERVES_MALFORMED = -1,
  BEGIN_SPONSORING_FUTURE_RESERVES_ALREADY_SPONSORED = -2,
  BEGIN_SPONSORING_FUTURE_RESERVES_RECURSIVE = -3,
};
typedef enum BeginSponsoringFutureReservesResultCode
    BeginSponsoringFutureReservesResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_BeginSponsoringFutureReservesResultCode(
    XDR *, BeginSponsoringFutureReservesResultCode *);
#elif __STDC__
extern bool_t xdr_BeginSponsoringFutureReservesResultCode(
    XDR *, BeginSponsoringFutureReservesResultCode *);
#else  /* Old Style C */
bool_t xdr_BeginSponsoringFutureReservesResultCode();
#endif /* Old Style C */

struct BeginSponsoringFutureReservesResult {
  BeginSponsoringFutureReservesResultCode code;
  union {
  } BeginSponsoringFutureReservesResult_u;
};
typedef struct BeginSponsoringFutureReservesResult
    BeginSponsoringFutureReservesResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_BeginSponsoringFutureReservesResult(XDR *,
                                        BeginSponsoringFutureReservesResult *);
#elif __STDC__
extern bool_t
xdr_BeginSponsoringFutureReservesResult(XDR *,
                                        BeginSponsoringFutureReservesResult *);
#else  /* Old Style C */
bool_t xdr_BeginSponsoringFutureReservesResult();
#endif /* Old Style C */

enum EndSponsoringFutureReservesResultCode {
  END_SPONSORING_FUTURE_RESERVES_SUCCESS = 0,
  END_SPONSORING_FUTURE_RESERVES_NOT_SPONSORED = -1,
};
typedef enum EndSponsoringFutureReservesResultCode
    EndSponsoringFutureReservesResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_EndSponsoringFutureReservesResultCode(
    XDR *, EndSponsoringFutureReservesResultCode *);
#elif __STDC__
extern bool_t xdr_EndSponsoringFutureReservesResultCode(
    XDR *, EndSponsoringFutureReservesResultCode *);
#else  /* Old Style C */
bool_t xdr_EndSponsoringFutureReservesResultCode();
#endif /* Old Style C */

struct EndSponsoringFutureReservesResult {
  EndSponsoringFutureReservesResultCode code;
  union {
  } EndSponsoringFutureReservesResult_u;
};
typedef struct EndSponsoringFutureReservesResult
    EndSponsoringFutureReservesResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_EndSponsoringFutureReservesResult(XDR *,
                                      EndSponsoringFutureReservesResult *);
#elif __STDC__
extern bool_t
xdr_EndSponsoringFutureReservesResult(XDR *,
                                      EndSponsoringFutureReservesResult *);
#else  /* Old Style C */
bool_t xdr_EndSponsoringFutureReservesResult();
#endif /* Old Style C */

enum RevokeSponsorshipResultCode {
  REVOKE_SPONSORSHIP_SUCCESS = 0,
  REVOKE_SPONSORSHIP_DOES_NOT_EXIST = -1,
  REVOKE_SPONSORSHIP_NOT_SPONSOR = -2,
  REVOKE_SPONSORSHIP_LOW_RESERVE = -3,
  REVOKE_SPONSORSHIP_ONLY_TRANSFERABLE = -4,
  REVOKE_SPONSORSHIP_MALFORMED = -5,
};
typedef enum RevokeSponsorshipResultCode RevokeSponsorshipResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_RevokeSponsorshipResultCode(XDR *, RevokeSponsorshipResultCode *);
#elif __STDC__
extern bool_t xdr_RevokeSponsorshipResultCode(XDR *,
                                              RevokeSponsorshipResultCode *);
#else  /* Old Style C */
bool_t xdr_RevokeSponsorshipResultCode();
#endif /* Old Style C */

struct RevokeSponsorshipResult {
  RevokeSponsorshipResultCode code;
  union {
  } RevokeSponsorshipResult_u;
};
typedef struct RevokeSponsorshipResult RevokeSponsorshipResult;
#ifdef __cplusplus
extern "C" bool_t xdr_RevokeSponsorshipResult(XDR *, RevokeSponsorshipResult *);
#elif __STDC__
extern bool_t xdr_RevokeSponsorshipResult(XDR *, RevokeSponsorshipResult *);
#else  /* Old Style C */
bool_t xdr_RevokeSponsorshipResult();
#endif /* Old Style C */

enum ClawbackResultCode {
  CLAWBACK_SUCCESS = 0,
  CLAWBACK_MALFORMED = -1,
  CLAWBACK_NOT_CLAWBACK_ENABLED = -2,
  CLAWBACK_NO_TRUST = -3,
  CLAWBACK_UNDERFUNDED = -4,
};
typedef enum ClawbackResultCode ClawbackResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_ClawbackResultCode(XDR *, ClawbackResultCode *);
#elif __STDC__
extern bool_t xdr_ClawbackResultCode(XDR *, ClawbackResultCode *);
#else  /* Old Style C */
bool_t xdr_ClawbackResultCode();
#endif /* Old Style C */

struct ClawbackResult {
  ClawbackResultCode code;
  union {
  } ClawbackResult_u;
};
typedef struct ClawbackResult ClawbackResult;
#ifdef __cplusplus
extern "C" bool_t xdr_ClawbackResult(XDR *, ClawbackResult *);
#elif __STDC__
extern bool_t xdr_ClawbackResult(XDR *, ClawbackResult *);
#else  /* Old Style C */
bool_t xdr_ClawbackResult();
#endif /* Old Style C */

enum ClawbackClaimableBalanceResultCode {
  CLAWBACK_CLAIMABLE_BALANCE_SUCCESS = 0,
  CLAWBACK_CLAIMABLE_BALANCE_DOES_NOT_EXIST = -1,
  CLAWBACK_CLAIMABLE_BALANCE_NOT_ISSUER = -2,
  CLAWBACK_CLAIMABLE_BALANCE_NOT_CLAWBACK_ENABLED = -3,
};
typedef enum ClawbackClaimableBalanceResultCode
    ClawbackClaimableBalanceResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_ClawbackClaimableBalanceResultCode(XDR *,
                                       ClawbackClaimableBalanceResultCode *);
#elif __STDC__
extern bool_t
xdr_ClawbackClaimableBalanceResultCode(XDR *,
                                       ClawbackClaimableBalanceResultCode *);
#else  /* Old Style C */
bool_t xdr_ClawbackClaimableBalanceResultCode();
#endif /* Old Style C */

struct ClawbackClaimableBalanceResult {
  ClawbackClaimableBalanceResultCode code;
  union {
  } ClawbackClaimableBalanceResult_u;
};
typedef struct ClawbackClaimableBalanceResult ClawbackClaimableBalanceResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_ClawbackClaimableBalanceResult(XDR *, ClawbackClaimableBalanceResult *);
#elif __STDC__
extern bool_t
xdr_ClawbackClaimableBalanceResult(XDR *, ClawbackClaimableBalanceResult *);
#else  /* Old Style C */
bool_t xdr_ClawbackClaimableBalanceResult();
#endif /* Old Style C */

enum SetTrustLineFlagsResultCode {
  SET_TRUST_LINE_FLAGS_SUCCESS = 0,
  SET_TRUST_LINE_FLAGS_MALFORMED = -1,
  SET_TRUST_LINE_FLAGS_NO_TRUST_LINE = -2,
  SET_TRUST_LINE_FLAGS_CANT_REVOKE = -3,
  SET_TRUST_LINE_FLAGS_INVALID_STATE = -4,
};
typedef enum SetTrustLineFlagsResultCode SetTrustLineFlagsResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_SetTrustLineFlagsResultCode(XDR *, SetTrustLineFlagsResultCode *);
#elif __STDC__
extern bool_t xdr_SetTrustLineFlagsResultCode(XDR *,
                                              SetTrustLineFlagsResultCode *);
#else  /* Old Style C */
bool_t xdr_SetTrustLineFlagsResultCode();
#endif /* Old Style C */

struct SetTrustLineFlagsResult {
  SetTrustLineFlagsResultCode code;
  union {
  } SetTrustLineFlagsResult_u;
};
typedef struct SetTrustLineFlagsResult SetTrustLineFlagsResult;
#ifdef __cplusplus
extern "C" bool_t xdr_SetTrustLineFlagsResult(XDR *, SetTrustLineFlagsResult *);
#elif __STDC__
extern bool_t xdr_SetTrustLineFlagsResult(XDR *, SetTrustLineFlagsResult *);
#else  /* Old Style C */
bool_t xdr_SetTrustLineFlagsResult();
#endif /* Old Style C */

enum LiquidityPoolDepositResultCode {
  LIQUIDITY_POOL_DEPOSIT_SUCCESS = 0,
  LIQUIDITY_POOL_DEPOSIT_MALFORMED = -1,
  LIQUIDITY_POOL_DEPOSIT_NO_TRUST = -2,
  LIQUIDITY_POOL_DEPOSIT_NOT_AUTHORIZED = -3,
  LIQUIDITY_POOL_DEPOSIT_UNDERFUNDED = -4,
  LIQUIDITY_POOL_DEPOSIT_LINE_FULL = -5,
  LIQUIDITY_POOL_DEPOSIT_BAD_PRICE = -6,
  LIQUIDITY_POOL_DEPOSIT_POOL_FULL = -7,
};
typedef enum LiquidityPoolDepositResultCode LiquidityPoolDepositResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_LiquidityPoolDepositResultCode(XDR *, LiquidityPoolDepositResultCode *);
#elif __STDC__
extern bool_t
xdr_LiquidityPoolDepositResultCode(XDR *, LiquidityPoolDepositResultCode *);
#else  /* Old Style C */
bool_t xdr_LiquidityPoolDepositResultCode();
#endif /* Old Style C */

struct LiquidityPoolDepositResult {
  LiquidityPoolDepositResultCode code;
  union {
  } LiquidityPoolDepositResult_u;
};
typedef struct LiquidityPoolDepositResult LiquidityPoolDepositResult;
#ifdef __cplusplus
extern "C" bool_t xdr_LiquidityPoolDepositResult(XDR *,
                                                 LiquidityPoolDepositResult *);
#elif __STDC__
extern bool_t xdr_LiquidityPoolDepositResult(XDR *,
                                             LiquidityPoolDepositResult *);
#else  /* Old Style C */
bool_t xdr_LiquidityPoolDepositResult();
#endif /* Old Style C */

enum LiquidityPoolWithdrawResultCode {
  LIQUIDITY_POOL_WITHDRAW_SUCCESS = 0,
  LIQUIDITY_POOL_WITHDRAW_MALFORMED = -1,
  LIQUIDITY_POOL_WITHDRAW_NO_TRUST = -2,
  LIQUIDITY_POOL_WITHDRAW_UNDERFUNDED = -3,
  LIQUIDITY_POOL_WITHDRAW_LINE_FULL = -4,
  LIQUIDITY_POOL_WITHDRAW_UNDER_MINIMUM = -5,
};
typedef enum LiquidityPoolWithdrawResultCode LiquidityPoolWithdrawResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_LiquidityPoolWithdrawResultCode(XDR *, LiquidityPoolWithdrawResultCode *);
#elif __STDC__
extern bool_t
xdr_LiquidityPoolWithdrawResultCode(XDR *, LiquidityPoolWithdrawResultCode *);
#else  /* Old Style C */
bool_t xdr_LiquidityPoolWithdrawResultCode();
#endif /* Old Style C */

struct LiquidityPoolWithdrawResult {
  LiquidityPoolWithdrawResultCode code;
  union {
  } LiquidityPoolWithdrawResult_u;
};
typedef struct LiquidityPoolWithdrawResult LiquidityPoolWithdrawResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_LiquidityPoolWithdrawResult(XDR *, LiquidityPoolWithdrawResult *);
#elif __STDC__
extern bool_t xdr_LiquidityPoolWithdrawResult(XDR *,
                                              LiquidityPoolWithdrawResult *);
#else  /* Old Style C */
bool_t xdr_LiquidityPoolWithdrawResult();
#endif /* Old Style C */

enum OperationResultCode {
  opINNER = 0,
  opBAD_AUTH = -1,
  opNO_ACCOUNT = -2,
  opNOT_SUPPORTED = -3,
  opTOO_MANY_SUBENTRIES = -4,
  opEXCEEDED_WORK_LIMIT = -5,
  opTOO_MANY_SPONSORING = -6,
};
typedef enum OperationResultCode OperationResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_OperationResultCode(XDR *, OperationResultCode *);
#elif __STDC__
extern bool_t xdr_OperationResultCode(XDR *, OperationResultCode *);
#else  /* Old Style C */
bool_t xdr_OperationResultCode();
#endif /* Old Style C */

struct OperationResultTr {
  OperationType type;
  union {
    CreateAccountResult createAccountResult;
    PaymentResult paymentResult;
    PathPaymentStrictReceiveResult pathPaymentStrictReceiveResult;
    ManageSellOfferResult manageSellOfferResult;
    ManageSellOfferResult createPassiveSellOfferResult;
    SetOptionsResult setOptionsResult;
    ChangeTrustResult changeTrustResult;
    AllowTrustResult allowTrustResult;
    AccountMergeResult accountMergeResult;
    InflationResult inflationResult;
    ManageDataResult manageDataResult;
    BumpSequenceResult bumpSeqResult;
    ManageBuyOfferResult manageBuyOfferResult;
    PathPaymentStrictSendResult pathPaymentStrictSendResult;
    CreateClaimableBalanceResult createClaimableBalanceResult;
    ClaimClaimableBalanceResult claimClaimableBalanceResult;
    BeginSponsoringFutureReservesResult beginSponsoringFutureReservesResult;
    EndSponsoringFutureReservesResult endSponsoringFutureReservesResult;
    RevokeSponsorshipResult revokeSponsorshipResult;
    ClawbackResult clawbackResult;
    ClawbackClaimableBalanceResult clawbackClaimableBalanceResult;
    SetTrustLineFlagsResult setTrustLineFlagsResult;
    LiquidityPoolDepositResult liquidityPoolDepositResult;
    LiquidityPoolWithdrawResult liquidityPoolWithdrawResult;
  } OperationResultTr_u;
};
typedef struct OperationResultTr OperationResultTr;
#ifdef __cplusplus
extern "C" bool_t xdr_OperationResultTr(XDR *, OperationResultTr *);
#elif __STDC__
extern bool_t xdr_OperationResultTr(XDR *, OperationResultTr *);
#else  /* Old Style C */
bool_t xdr_OperationResultTr();
#endif /* Old Style C */

struct OperationResult {
  OperationResultCode code;
  union {
    OperationResultTr tr;
  } OperationResult_u;
};
typedef struct OperationResult OperationResult;
#ifdef __cplusplus
extern "C" bool_t xdr_OperationResult(XDR *, OperationResult *);
#elif __STDC__
extern bool_t xdr_OperationResult(XDR *, OperationResult *);
#else  /* Old Style C */
bool_t xdr_OperationResult();
#endif /* Old Style C */

enum TransactionResultCode {
  txFEE_BUMP_INNER_SUCCESS = 1,
  txSUCCESS = 0,
  txFAILED = -1,
  txTOO_EARLY = -2,
  txTOO_LATE = -3,
  txMISSING_OPERATION = -4,
  txBAD_SEQ = -5,
  txBAD_AUTH = -6,
  txINSUFFICIENT_BALANCE = -7,
  txNO_ACCOUNT = -8,
  txINSUFFICIENT_FEE = -9,
  txBAD_AUTH_EXTRA = -10,
  txINTERNAL_ERROR = -11,
  txNOT_SUPPORTED = -12,
  txFEE_BUMP_INNER_FAILED = -13,
  txBAD_SPONSORSHIP = -14,
};
typedef enum TransactionResultCode TransactionResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionResultCode(XDR *, TransactionResultCode *);
#elif __STDC__
extern bool_t xdr_TransactionResultCode(XDR *, TransactionResultCode *);
#else  /* Old Style C */
bool_t xdr_TransactionResultCode();
#endif /* Old Style C */

struct InnerTransactionResultResult {
  TransactionResultCode code;
  union {
    struct {
      u_int results_len;
      OperationResult *results_val;
    } results;
  } InnerTransactionResultResult_u;
};
typedef struct InnerTransactionResultResult InnerTransactionResultResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_InnerTransactionResultResult(XDR *, InnerTransactionResultResult *);
#elif __STDC__
extern bool_t xdr_InnerTransactionResultResult(XDR *,
                                               InnerTransactionResultResult *);
#else  /* Old Style C */
bool_t xdr_InnerTransactionResultResult();
#endif /* Old Style C */

struct InnerTransactionResultExt {
  int v;
  union {
  } InnerTransactionResultExt_u;
};
typedef struct InnerTransactionResultExt InnerTransactionResultExt;
#ifdef __cplusplus
extern "C" bool_t xdr_InnerTransactionResultExt(XDR *,
                                                InnerTransactionResultExt *);
#elif __STDC__
extern bool_t xdr_InnerTransactionResultExt(XDR *, InnerTransactionResultExt *);
#else  /* Old Style C */
bool_t xdr_InnerTransactionResultExt();
#endif /* Old Style C */

struct InnerTransactionResult {
  int64 feeCharged;
  InnerTransactionResultResult result;
  InnerTransactionResultExt ext;
};
typedef struct InnerTransactionResult InnerTransactionResult;
#ifdef __cplusplus
extern "C" bool_t xdr_InnerTransactionResult(XDR *, InnerTransactionResult *);
#elif __STDC__
extern bool_t xdr_InnerTransactionResult(XDR *, InnerTransactionResult *);
#else  /* Old Style C */
bool_t xdr_InnerTransactionResult();
#endif /* Old Style C */

struct InnerTransactionResultPair {
  Hash transactionHash;
  InnerTransactionResult result;
};
typedef struct InnerTransactionResultPair InnerTransactionResultPair;
#ifdef __cplusplus
extern "C" bool_t xdr_InnerTransactionResultPair(XDR *,
                                                 InnerTransactionResultPair *);
#elif __STDC__
extern bool_t xdr_InnerTransactionResultPair(XDR *,
                                             InnerTransactionResultPair *);
#else  /* Old Style C */
bool_t xdr_InnerTransactionResultPair();
#endif /* Old Style C */

struct TransactionResultResult {
  TransactionResultCode code;
  union {
    InnerTransactionResultPair innerResultPair;
    struct {
      u_int results_len;
      OperationResult *results_val;
    } results;
  } TransactionResultResult_u;
};
typedef struct TransactionResultResult TransactionResultResult;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionResultResult(XDR *, TransactionResultResult *);
#elif __STDC__
extern bool_t xdr_TransactionResultResult(XDR *, TransactionResultResult *);
#else  /* Old Style C */
bool_t xdr_TransactionResultResult();
#endif /* Old Style C */

struct TransactionResultExt {
  int v;
  union {
  } TransactionResultExt_u;
};
typedef struct TransactionResultExt TransactionResultExt;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionResultExt(XDR *, TransactionResultExt *);
#elif __STDC__
extern bool_t xdr_TransactionResultExt(XDR *, TransactionResultExt *);
#else  /* Old Style C */
bool_t xdr_TransactionResultExt();
#endif /* Old Style C */

struct TransactionResult {
  int64 feeCharged;
  TransactionResultResult result;
  TransactionResultExt ext;
};
typedef struct TransactionResult TransactionResult;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionResult(XDR *, TransactionResult *);
#elif __STDC__
extern bool_t xdr_TransactionResult(XDR *, TransactionResult *);
#else  /* Old Style C */
bool_t xdr_TransactionResult();
#endif /* Old Style C */

typedef struct {
  u_int UpgradeType_len;
  char *UpgradeType_val;
} UpgradeType;
#ifdef __cplusplus
extern "C" bool_t xdr_UpgradeType(XDR *, UpgradeType *);
#elif __STDC__
extern bool_t xdr_UpgradeType(XDR *, UpgradeType *);
#else  /* Old Style C */
bool_t xdr_UpgradeType();
#endif /* Old Style C */

enum StellarValueType {
  STELLAR_VALUE_BASIC = 0,
  STELLAR_VALUE_SIGNED = 1,
};
typedef enum StellarValueType StellarValueType;
#ifdef __cplusplus
extern "C" bool_t xdr_StellarValueType(XDR *, StellarValueType *);
#elif __STDC__
extern bool_t xdr_StellarValueType(XDR *, StellarValueType *);
#else  /* Old Style C */
bool_t xdr_StellarValueType();
#endif /* Old Style C */

struct LedgerCloseValueSignature {
  NodeID nodeID;
  Signature signature;
};
typedef struct LedgerCloseValueSignature LedgerCloseValueSignature;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerCloseValueSignature(XDR *,
                                                LedgerCloseValueSignature *);
#elif __STDC__
extern bool_t xdr_LedgerCloseValueSignature(XDR *, LedgerCloseValueSignature *);
#else  /* Old Style C */
bool_t xdr_LedgerCloseValueSignature();
#endif /* Old Style C */

struct StellarValueExt {
  StellarValueType v;
  union {
    LedgerCloseValueSignature lcValueSignature;
  } StellarValueExt_u;
};
typedef struct StellarValueExt StellarValueExt;
#ifdef __cplusplus
extern "C" bool_t xdr_StellarValueExt(XDR *, StellarValueExt *);
#elif __STDC__
extern bool_t xdr_StellarValueExt(XDR *, StellarValueExt *);
#else  /* Old Style C */
bool_t xdr_StellarValueExt();
#endif /* Old Style C */

struct StellarValue {
  Hash txSetHash;
  TimePoint closeTime;
  struct {
    u_int upgrades_len;
    UpgradeType *upgrades_val;
  } upgrades;
  StellarValueExt ext;
};
typedef struct StellarValue StellarValue;
#ifdef __cplusplus
extern "C" bool_t xdr_StellarValue(XDR *, StellarValue *);
#elif __STDC__
extern bool_t xdr_StellarValue(XDR *, StellarValue *);
#else  /* Old Style C */
bool_t xdr_StellarValue();
#endif /* Old Style C */

struct LedgerHeaderExt {
  int v;
  union {
  } LedgerHeaderExt_u;
};
typedef struct LedgerHeaderExt LedgerHeaderExt;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerHeaderExt(XDR *, LedgerHeaderExt *);
#elif __STDC__
extern bool_t xdr_LedgerHeaderExt(XDR *, LedgerHeaderExt *);
#else  /* Old Style C */
bool_t xdr_LedgerHeaderExt();
#endif /* Old Style C */

struct LedgerHeader {
  uint32 ledgerVersion;
  Hash previousLedgerHash;
  StellarValue scpValue;
  Hash txSetResultHash;
  Hash bucketListHash;
  uint32 ledgerSeq;
  int64 totalCoins;
  int64 feePool;
  uint32 inflationSeq;
  uint64 idPool;
  uint32 baseFee;
  uint32 baseReserve;
  uint32 maxTxSetSize;
  Hash skipList[4];
  LedgerHeaderExt ext;
};
typedef struct LedgerHeader LedgerHeader;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerHeader(XDR *, LedgerHeader *);
#elif __STDC__
extern bool_t xdr_LedgerHeader(XDR *, LedgerHeader *);
#else  /* Old Style C */
bool_t xdr_LedgerHeader();
#endif /* Old Style C */

enum LedgerUpgradeType {
  LEDGER_UPGRADE_VERSION = 1,
  LEDGER_UPGRADE_BASE_FEE = 2,
  LEDGER_UPGRADE_MAX_TX_SET_SIZE = 3,
  LEDGER_UPGRADE_BASE_RESERVE = 4,
};
typedef enum LedgerUpgradeType LedgerUpgradeType;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerUpgradeType(XDR *, LedgerUpgradeType *);
#elif __STDC__
extern bool_t xdr_LedgerUpgradeType(XDR *, LedgerUpgradeType *);
#else  /* Old Style C */
bool_t xdr_LedgerUpgradeType();
#endif /* Old Style C */

struct LedgerUpgrade {
  LedgerUpgradeType type;
  union {
    uint32 newLedgerVersion;
    uint32 newBaseFee;
    uint32 newMaxTxSetSize;
    uint32 newBaseReserve;
  } LedgerUpgrade_u;
};
typedef struct LedgerUpgrade LedgerUpgrade;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerUpgrade(XDR *, LedgerUpgrade *);
#elif __STDC__
extern bool_t xdr_LedgerUpgrade(XDR *, LedgerUpgrade *);
#else  /* Old Style C */
bool_t xdr_LedgerUpgrade();
#endif /* Old Style C */

enum BucketEntryType {
  METAENTRY = -1,
  LIVEENTRY = 0,
  DEADENTRY = 1,
  INITENTRY = 2,
};
typedef enum BucketEntryType BucketEntryType;
#ifdef __cplusplus
extern "C" bool_t xdr_BucketEntryType(XDR *, BucketEntryType *);
#elif __STDC__
extern bool_t xdr_BucketEntryType(XDR *, BucketEntryType *);
#else  /* Old Style C */
bool_t xdr_BucketEntryType();
#endif /* Old Style C */

struct BucketMetadataExt {
  int v;
  union {
  } BucketMetadataExt_u;
};
typedef struct BucketMetadataExt BucketMetadataExt;
#ifdef __cplusplus
extern "C" bool_t xdr_BucketMetadataExt(XDR *, BucketMetadataExt *);
#elif __STDC__
extern bool_t xdr_BucketMetadataExt(XDR *, BucketMetadataExt *);
#else  /* Old Style C */
bool_t xdr_BucketMetadataExt();
#endif /* Old Style C */

struct BucketMetadata {
  uint32 ledgerVersion;
  BucketMetadataExt ext;
};
typedef struct BucketMetadata BucketMetadata;
#ifdef __cplusplus
extern "C" bool_t xdr_BucketMetadata(XDR *, BucketMetadata *);
#elif __STDC__
extern bool_t xdr_BucketMetadata(XDR *, BucketMetadata *);
#else  /* Old Style C */
bool_t xdr_BucketMetadata();
#endif /* Old Style C */

struct BucketEntry {
  BucketEntryType type;
  union {
    LedgerEntry liveEntry;
    LedgerKey deadEntry;
    BucketMetadata metaEntry;
  } BucketEntry_u;
};
typedef struct BucketEntry BucketEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_BucketEntry(XDR *, BucketEntry *);
#elif __STDC__
extern bool_t xdr_BucketEntry(XDR *, BucketEntry *);
#else  /* Old Style C */
bool_t xdr_BucketEntry();
#endif /* Old Style C */

struct TransactionSet {
  Hash previousLedgerHash;
  struct {
    u_int txs_len;
    TransactionEnvelope *txs_val;
  } txs;
};
typedef struct TransactionSet TransactionSet;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionSet(XDR *, TransactionSet *);
#elif __STDC__
extern bool_t xdr_TransactionSet(XDR *, TransactionSet *);
#else  /* Old Style C */
bool_t xdr_TransactionSet();
#endif /* Old Style C */

struct TransactionResultPair {
  Hash transactionHash;
  TransactionResult result;
};
typedef struct TransactionResultPair TransactionResultPair;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionResultPair(XDR *, TransactionResultPair *);
#elif __STDC__
extern bool_t xdr_TransactionResultPair(XDR *, TransactionResultPair *);
#else  /* Old Style C */
bool_t xdr_TransactionResultPair();
#endif /* Old Style C */

struct TransactionResultSet {
  struct {
    u_int results_len;
    TransactionResultPair *results_val;
  } results;
};
typedef struct TransactionResultSet TransactionResultSet;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionResultSet(XDR *, TransactionResultSet *);
#elif __STDC__
extern bool_t xdr_TransactionResultSet(XDR *, TransactionResultSet *);
#else  /* Old Style C */
bool_t xdr_TransactionResultSet();
#endif /* Old Style C */

struct TransactionHistoryEntryExt {
  int v;
  union {
  } TransactionHistoryEntryExt_u;
};
typedef struct TransactionHistoryEntryExt TransactionHistoryEntryExt;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionHistoryEntryExt(XDR *,
                                                 TransactionHistoryEntryExt *);
#elif __STDC__
extern bool_t xdr_TransactionHistoryEntryExt(XDR *,
                                             TransactionHistoryEntryExt *);
#else  /* Old Style C */
bool_t xdr_TransactionHistoryEntryExt();
#endif /* Old Style C */

struct TransactionHistoryEntry {
  uint32 ledgerSeq;
  TransactionSet txSet;
  TransactionHistoryEntryExt ext;
};
typedef struct TransactionHistoryEntry TransactionHistoryEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionHistoryEntry(XDR *, TransactionHistoryEntry *);
#elif __STDC__
extern bool_t xdr_TransactionHistoryEntry(XDR *, TransactionHistoryEntry *);
#else  /* Old Style C */
bool_t xdr_TransactionHistoryEntry();
#endif /* Old Style C */

struct TransactionHistoryResultEntryExt {
  int v;
  union {
  } TransactionHistoryResultEntryExt_u;
};
typedef struct TransactionHistoryResultEntryExt
    TransactionHistoryResultEntryExt;
#ifdef __cplusplus
extern "C" bool_t
xdr_TransactionHistoryResultEntryExt(XDR *, TransactionHistoryResultEntryExt *);
#elif __STDC__
extern bool_t
xdr_TransactionHistoryResultEntryExt(XDR *, TransactionHistoryResultEntryExt *);
#else  /* Old Style C */
bool_t xdr_TransactionHistoryResultEntryExt();
#endif /* Old Style C */

struct TransactionHistoryResultEntry {
  uint32 ledgerSeq;
  TransactionResultSet txResultSet;
  TransactionHistoryResultEntryExt ext;
};
typedef struct TransactionHistoryResultEntry TransactionHistoryResultEntry;
#ifdef __cplusplus
extern "C" bool_t
xdr_TransactionHistoryResultEntry(XDR *, TransactionHistoryResultEntry *);
#elif __STDC__
extern bool_t
xdr_TransactionHistoryResultEntry(XDR *, TransactionHistoryResultEntry *);
#else  /* Old Style C */
bool_t xdr_TransactionHistoryResultEntry();
#endif /* Old Style C */

struct LedgerHeaderHistoryEntryExt {
  int v;
  union {
  } LedgerHeaderHistoryEntryExt_u;
};
typedef struct LedgerHeaderHistoryEntryExt LedgerHeaderHistoryEntryExt;
#ifdef __cplusplus
extern "C" bool_t
xdr_LedgerHeaderHistoryEntryExt(XDR *, LedgerHeaderHistoryEntryExt *);
#elif __STDC__
extern bool_t xdr_LedgerHeaderHistoryEntryExt(XDR *,
                                              LedgerHeaderHistoryEntryExt *);
#else  /* Old Style C */
bool_t xdr_LedgerHeaderHistoryEntryExt();
#endif /* Old Style C */

struct LedgerHeaderHistoryEntry {
  Hash hash;
  LedgerHeader header;
  LedgerHeaderHistoryEntryExt ext;
};
typedef struct LedgerHeaderHistoryEntry LedgerHeaderHistoryEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerHeaderHistoryEntry(XDR *,
                                               LedgerHeaderHistoryEntry *);
#elif __STDC__
extern bool_t xdr_LedgerHeaderHistoryEntry(XDR *, LedgerHeaderHistoryEntry *);
#else  /* Old Style C */
bool_t xdr_LedgerHeaderHistoryEntry();
#endif /* Old Style C */

struct LedgerSCPMessages {
  uint32 ledgerSeq;
  struct {
    u_int messages_len;
    SCPEnvelope *messages_val;
  } messages;
};
typedef struct LedgerSCPMessages LedgerSCPMessages;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerSCPMessages(XDR *, LedgerSCPMessages *);
#elif __STDC__
extern bool_t xdr_LedgerSCPMessages(XDR *, LedgerSCPMessages *);
#else  /* Old Style C */
bool_t xdr_LedgerSCPMessages();
#endif /* Old Style C */

struct SCPHistoryEntryV0 {
  struct {
    u_int quorumSets_len;
    SCPQuorumSet *quorumSets_val;
  } quorumSets;
  LedgerSCPMessages ledgerMessages;
};
typedef struct SCPHistoryEntryV0 SCPHistoryEntryV0;
#ifdef __cplusplus
extern "C" bool_t xdr_SCPHistoryEntryV0(XDR *, SCPHistoryEntryV0 *);
#elif __STDC__
extern bool_t xdr_SCPHistoryEntryV0(XDR *, SCPHistoryEntryV0 *);
#else  /* Old Style C */
bool_t xdr_SCPHistoryEntryV0();
#endif /* Old Style C */

struct SCPHistoryEntry {
  int v;
  union {
    SCPHistoryEntryV0 v0;
  } SCPHistoryEntry_u;
};
typedef struct SCPHistoryEntry SCPHistoryEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_SCPHistoryEntry(XDR *, SCPHistoryEntry *);
#elif __STDC__
extern bool_t xdr_SCPHistoryEntry(XDR *, SCPHistoryEntry *);
#else  /* Old Style C */
bool_t xdr_SCPHistoryEntry();
#endif /* Old Style C */

enum LedgerEntryChangeType {
  LEDGER_ENTRY_CREATED = 0,
  LEDGER_ENTRY_UPDATED = 1,
  LEDGER_ENTRY_REMOVED = 2,
  LEDGER_ENTRY_STATE = 3,
};
typedef enum LedgerEntryChangeType LedgerEntryChangeType;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerEntryChangeType(XDR *, LedgerEntryChangeType *);
#elif __STDC__
extern bool_t xdr_LedgerEntryChangeType(XDR *, LedgerEntryChangeType *);
#else  /* Old Style C */
bool_t xdr_LedgerEntryChangeType();
#endif /* Old Style C */

struct LedgerEntryChange {
  LedgerEntryChangeType type;
  union {
    LedgerEntry created;
    LedgerEntry updated;
    LedgerKey removed;
    LedgerEntry state;
  } LedgerEntryChange_u;
};
typedef struct LedgerEntryChange LedgerEntryChange;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerEntryChange(XDR *, LedgerEntryChange *);
#elif __STDC__
extern bool_t xdr_LedgerEntryChange(XDR *, LedgerEntryChange *);
#else  /* Old Style C */
bool_t xdr_LedgerEntryChange();
#endif /* Old Style C */

typedef struct {
  u_int LedgerEntryChanges_len;
  LedgerEntryChange *LedgerEntryChanges_val;
} LedgerEntryChanges;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerEntryChanges(XDR *, LedgerEntryChanges *);
#elif __STDC__
extern bool_t xdr_LedgerEntryChanges(XDR *, LedgerEntryChanges *);
#else  /* Old Style C */
bool_t xdr_LedgerEntryChanges();
#endif /* Old Style C */

struct OperationMeta {
  LedgerEntryChanges changes;
};
typedef struct OperationMeta OperationMeta;
#ifdef __cplusplus
extern "C" bool_t xdr_OperationMeta(XDR *, OperationMeta *);
#elif __STDC__
extern bool_t xdr_OperationMeta(XDR *, OperationMeta *);
#else  /* Old Style C */
bool_t xdr_OperationMeta();
#endif /* Old Style C */

struct TransactionMetaV1 {
  LedgerEntryChanges txChanges;
  struct {
    u_int operations_len;
    OperationMeta *operations_val;
  } operations;
};
typedef struct TransactionMetaV1 TransactionMetaV1;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionMetaV1(XDR *, TransactionMetaV1 *);
#elif __STDC__
extern bool_t xdr_TransactionMetaV1(XDR *, TransactionMetaV1 *);
#else  /* Old Style C */
bool_t xdr_TransactionMetaV1();
#endif /* Old Style C */

struct TransactionMetaV2 {
  LedgerEntryChanges txChangesBefore;
  struct {
    u_int operations_len;
    OperationMeta *operations_val;
  } operations;
  LedgerEntryChanges txChangesAfter;
};
typedef struct TransactionMetaV2 TransactionMetaV2;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionMetaV2(XDR *, TransactionMetaV2 *);
#elif __STDC__
extern bool_t xdr_TransactionMetaV2(XDR *, TransactionMetaV2 *);
#else  /* Old Style C */
bool_t xdr_TransactionMetaV2();
#endif /* Old Style C */

struct TransactionMeta {
  int v;
  union {
    struct {
      u_int operations_len;
      OperationMeta *operations_val;
    } operations;
    TransactionMetaV1 v1;
    TransactionMetaV2 v2;
  } TransactionMeta_u;
};
typedef struct TransactionMeta TransactionMeta;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionMeta(XDR *, TransactionMeta *);
#elif __STDC__
extern bool_t xdr_TransactionMeta(XDR *, TransactionMeta *);
#else  /* Old Style C */
bool_t xdr_TransactionMeta();
#endif /* Old Style C */

struct TransactionResultMeta {
  TransactionResultPair result;
  LedgerEntryChanges feeProcessing;
  TransactionMeta txApplyProcessing;
};
typedef struct TransactionResultMeta TransactionResultMeta;
#ifdef __cplusplus
extern "C" bool_t xdr_TransactionResultMeta(XDR *, TransactionResultMeta *);
#elif __STDC__
extern bool_t xdr_TransactionResultMeta(XDR *, TransactionResultMeta *);
#else  /* Old Style C */
bool_t xdr_TransactionResultMeta();
#endif /* Old Style C */

struct UpgradeEntryMeta {
  LedgerUpgrade upgrade;
  LedgerEntryChanges changes;
};
typedef struct UpgradeEntryMeta UpgradeEntryMeta;
#ifdef __cplusplus
extern "C" bool_t xdr_UpgradeEntryMeta(XDR *, UpgradeEntryMeta *);
#elif __STDC__
extern bool_t xdr_UpgradeEntryMeta(XDR *, UpgradeEntryMeta *);
#else  /* Old Style C */
bool_t xdr_UpgradeEntryMeta();
#endif /* Old Style C */

struct LedgerCloseMetaV0 {
  LedgerHeaderHistoryEntry ledgerHeader;
  TransactionSet txSet;
  struct {
    u_int txProcessing_len;
    TransactionResultMeta *txProcessing_val;
  } txProcessing;
  struct {
    u_int upgradesProcessing_len;
    UpgradeEntryMeta *upgradesProcessing_val;
  } upgradesProcessing;
  struct {
    u_int scpInfo_len;
    SCPHistoryEntry *scpInfo_val;
  } scpInfo;
};
typedef struct LedgerCloseMetaV0 LedgerCloseMetaV0;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerCloseMetaV0(XDR *, LedgerCloseMetaV0 *);
#elif __STDC__
extern bool_t xdr_LedgerCloseMetaV0(XDR *, LedgerCloseMetaV0 *);
#else  /* Old Style C */
bool_t xdr_LedgerCloseMetaV0();
#endif /* Old Style C */

struct LedgerCloseMeta {
  int v;
  union {
    LedgerCloseMetaV0 v0;
  } LedgerCloseMeta_u;
};
typedef struct LedgerCloseMeta LedgerCloseMeta;
#ifdef __cplusplus
extern "C" bool_t xdr_LedgerCloseMeta(XDR *, LedgerCloseMeta *);
#elif __STDC__
extern bool_t xdr_LedgerCloseMeta(XDR *, LedgerCloseMeta *);
#else  /* Old Style C */
bool_t xdr_LedgerCloseMeta();
#endif /* Old Style C */

enum ErrorCode {
  ERR_MISC = 0,
  ERR_DATA = 1,
  ERR_CONF = 2,
  ERR_AUTH = 3,
  ERR_LOAD = 4,
};
typedef enum ErrorCode ErrorCode;
#ifdef __cplusplus
extern "C" bool_t xdr_ErrorCode(XDR *, ErrorCode *);
#elif __STDC__
extern bool_t xdr_ErrorCode(XDR *, ErrorCode *);
#else  /* Old Style C */
bool_t xdr_ErrorCode();
#endif /* Old Style C */

struct Error {
  ErrorCode code;
  char *msg;
};
typedef struct Error Error;
#ifdef __cplusplus
extern "C" bool_t xdr_Error(XDR *, Error *);
#elif __STDC__
extern bool_t xdr_Error(XDR *, Error *);
#else  /* Old Style C */
bool_t xdr_Error();
#endif /* Old Style C */

struct AuthCert {
  Curve25519Public pubkey;
  uint64 expiration;
  Signature sig;
};
typedef struct AuthCert AuthCert;
#ifdef __cplusplus
extern "C" bool_t xdr_AuthCert(XDR *, AuthCert *);
#elif __STDC__
extern bool_t xdr_AuthCert(XDR *, AuthCert *);
#else  /* Old Style C */
bool_t xdr_AuthCert();
#endif /* Old Style C */

struct Hello {
  uint32 ledgerVersion;
  uint32 overlayVersion;
  uint32 overlayMinVersion;
  Hash networkID;
  char *versionStr;
  int listeningPort;
  NodeID peerID;
  AuthCert cert;
  uint256 nonce;
};
typedef struct Hello Hello;
#ifdef __cplusplus
extern "C" bool_t xdr_Hello(XDR *, Hello *);
#elif __STDC__
extern bool_t xdr_Hello(XDR *, Hello *);
#else  /* Old Style C */
bool_t xdr_Hello();
#endif /* Old Style C */

struct Auth {
  int unused;
};
typedef struct Auth Auth;
#ifdef __cplusplus
extern "C" bool_t xdr_Auth(XDR *, Auth *);
#elif __STDC__
extern bool_t xdr_Auth(XDR *, Auth *);
#else  /* Old Style C */
bool_t xdr_Auth();
#endif /* Old Style C */

enum IPAddrType {
  IPv4 = 0,
  IPv6 = 1,
};
typedef enum IPAddrType IPAddrType;
#ifdef __cplusplus
extern "C" bool_t xdr_IPAddrType(XDR *, IPAddrType *);
#elif __STDC__
extern bool_t xdr_IPAddrType(XDR *, IPAddrType *);
#else  /* Old Style C */
bool_t xdr_IPAddrType();
#endif /* Old Style C */

struct PeerAddressIP {
  IPAddrType type;
  union {
    char ipv4[4];
    char ipv6[16];
  } PeerAddressIP_u;
};
typedef struct PeerAddressIP PeerAddressIP;
#ifdef __cplusplus
extern "C" bool_t xdr_PeerAddressIP(XDR *, PeerAddressIP *);
#elif __STDC__
extern bool_t xdr_PeerAddressIP(XDR *, PeerAddressIP *);
#else  /* Old Style C */
bool_t xdr_PeerAddressIP();
#endif /* Old Style C */

struct PeerAddress {
  PeerAddressIP ip;
  uint32 port;
  uint32 numFailures;
};
typedef struct PeerAddress PeerAddress;
#ifdef __cplusplus
extern "C" bool_t xdr_PeerAddress(XDR *, PeerAddress *);
#elif __STDC__
extern bool_t xdr_PeerAddress(XDR *, PeerAddress *);
#else  /* Old Style C */
bool_t xdr_PeerAddress();
#endif /* Old Style C */

enum MessageType {
  ERROR_MSG = 0,
  AUTH_ = 2,
  DONT_HAVE = 3,
  GET_PEERS = 4,
  PEERS = 5,
  GET_TX_SET = 6,
  TX_SET = 7,
  TRANSACTION = 8,
  GET_SCP_QUORUMSET = 9,
  SCP_QUORUMSET = 10,
  SCP_MESSAGE = 11,
  GET_SCP_STATE = 12,
  HELLO = 13,
  SURVEY_REQUEST = 14,
  SURVEY_RESPONSE = 15,
};
typedef enum MessageType MessageType;
#ifdef __cplusplus
extern "C" bool_t xdr_MessageType(XDR *, MessageType *);
#elif __STDC__
extern bool_t xdr_MessageType(XDR *, MessageType *);
#else  /* Old Style C */
bool_t xdr_MessageType();
#endif /* Old Style C */

struct DontHave {
  MessageType type;
  uint256 reqHash;
};
typedef struct DontHave DontHave;
#ifdef __cplusplus
extern "C" bool_t xdr_DontHave(XDR *, DontHave *);
#elif __STDC__
extern bool_t xdr_DontHave(XDR *, DontHave *);
#else  /* Old Style C */
bool_t xdr_DontHave();
#endif /* Old Style C */

enum SurveyMessageCommandType {
  SURVEY_TOPOLOGY = 0,
};
typedef enum SurveyMessageCommandType SurveyMessageCommandType;
#ifdef __cplusplus
extern "C" bool_t xdr_SurveyMessageCommandType(XDR *,
                                               SurveyMessageCommandType *);
#elif __STDC__
extern bool_t xdr_SurveyMessageCommandType(XDR *, SurveyMessageCommandType *);
#else  /* Old Style C */
bool_t xdr_SurveyMessageCommandType();
#endif /* Old Style C */

struct SurveyRequestMessage {
  NodeID surveyorPeerID;
  NodeID surveyedPeerID;
  uint32 ledgerNum;
  Curve25519Public encryptionKey;
  SurveyMessageCommandType commandType;
};
typedef struct SurveyRequestMessage SurveyRequestMessage;
#ifdef __cplusplus
extern "C" bool_t xdr_SurveyRequestMessage(XDR *, SurveyRequestMessage *);
#elif __STDC__
extern bool_t xdr_SurveyRequestMessage(XDR *, SurveyRequestMessage *);
#else  /* Old Style C */
bool_t xdr_SurveyRequestMessage();
#endif /* Old Style C */

struct SignedSurveyRequestMessage {
  Signature requestSignature;
  SurveyRequestMessage request;
};
typedef struct SignedSurveyRequestMessage SignedSurveyRequestMessage;
#ifdef __cplusplus
extern "C" bool_t xdr_SignedSurveyRequestMessage(XDR *,
                                                 SignedSurveyRequestMessage *);
#elif __STDC__
extern bool_t xdr_SignedSurveyRequestMessage(XDR *,
                                             SignedSurveyRequestMessage *);
#else  /* Old Style C */
bool_t xdr_SignedSurveyRequestMessage();
#endif /* Old Style C */

typedef struct {
  u_int EncryptedBody_len;
  char *EncryptedBody_val;
} EncryptedBody;
#ifdef __cplusplus
extern "C" bool_t xdr_EncryptedBody(XDR *, EncryptedBody *);
#elif __STDC__
extern bool_t xdr_EncryptedBody(XDR *, EncryptedBody *);
#else  /* Old Style C */
bool_t xdr_EncryptedBody();
#endif /* Old Style C */

struct SurveyResponseMessage {
  NodeID surveyorPeerID;
  NodeID surveyedPeerID;
  uint32 ledgerNum;
  SurveyMessageCommandType commandType;
  EncryptedBody encryptedBody;
};
typedef struct SurveyResponseMessage SurveyResponseMessage;
#ifdef __cplusplus
extern "C" bool_t xdr_SurveyResponseMessage(XDR *, SurveyResponseMessage *);
#elif __STDC__
extern bool_t xdr_SurveyResponseMessage(XDR *, SurveyResponseMessage *);
#else  /* Old Style C */
bool_t xdr_SurveyResponseMessage();
#endif /* Old Style C */

struct SignedSurveyResponseMessage {
  Signature responseSignature;
  SurveyResponseMessage response;
};
typedef struct SignedSurveyResponseMessage SignedSurveyResponseMessage;
#ifdef __cplusplus
extern "C" bool_t
xdr_SignedSurveyResponseMessage(XDR *, SignedSurveyResponseMessage *);
#elif __STDC__
extern bool_t xdr_SignedSurveyResponseMessage(XDR *,
                                              SignedSurveyResponseMessage *);
#else  /* Old Style C */
bool_t xdr_SignedSurveyResponseMessage();
#endif /* Old Style C */

struct PeerStats {
  NodeID id;
  char *versionStr;
  uint64 messagesRead;
  uint64 messagesWritten;
  uint64 bytesRead;
  uint64 bytesWritten;
  uint64 secondsConnected;
  uint64 uniqueFloodBytesRecv;
  uint64 duplicateFloodBytesRecv;
  uint64 uniqueFetchBytesRecv;
  uint64 duplicateFetchBytesRecv;
  uint64 uniqueFloodMessageRecv;
  uint64 duplicateFloodMessageRecv;
  uint64 uniqueFetchMessageRecv;
  uint64 duplicateFetchMessageRecv;
};
typedef struct PeerStats PeerStats;
#ifdef __cplusplus
extern "C" bool_t xdr_PeerStats(XDR *, PeerStats *);
#elif __STDC__
extern bool_t xdr_PeerStats(XDR *, PeerStats *);
#else  /* Old Style C */
bool_t xdr_PeerStats();
#endif /* Old Style C */

typedef struct {
  u_int PeerStatList_len;
  PeerStats *PeerStatList_val;
} PeerStatList;
#ifdef __cplusplus
extern "C" bool_t xdr_PeerStatList(XDR *, PeerStatList *);
#elif __STDC__
extern bool_t xdr_PeerStatList(XDR *, PeerStatList *);
#else  /* Old Style C */
bool_t xdr_PeerStatList();
#endif /* Old Style C */

struct TopologyResponseBody {
  PeerStatList inboundPeers;
  PeerStatList outboundPeers;
  uint32 totalInboundPeerCount;
  uint32 totalOutboundPeerCount;
};
typedef struct TopologyResponseBody TopologyResponseBody;
#ifdef __cplusplus
extern "C" bool_t xdr_TopologyResponseBody(XDR *, TopologyResponseBody *);
#elif __STDC__
extern bool_t xdr_TopologyResponseBody(XDR *, TopologyResponseBody *);
#else  /* Old Style C */
bool_t xdr_TopologyResponseBody();
#endif /* Old Style C */

struct SurveyResponseBody {
  SurveyMessageCommandType type;
  union {
    TopologyResponseBody topologyResponseBody;
  } SurveyResponseBody_u;
};
typedef struct SurveyResponseBody SurveyResponseBody;
#ifdef __cplusplus
extern "C" bool_t xdr_SurveyResponseBody(XDR *, SurveyResponseBody *);
#elif __STDC__
extern bool_t xdr_SurveyResponseBody(XDR *, SurveyResponseBody *);
#else  /* Old Style C */
bool_t xdr_SurveyResponseBody();
#endif /* Old Style C */

struct StellarMessage {
  MessageType type;
  union {
    Error error;
    Hello hello;
    Auth auth;
    DontHave dontHave;
    struct {
      u_int peers_len;
      PeerAddress *peers_val;
    } peers;
    uint256 txSetHash;
    TransactionSet txSet;
    TransactionEnvelope transaction;
    SignedSurveyRequestMessage signedSurveyRequestMessage;
    SignedSurveyResponseMessage signedSurveyResponseMessage;
    uint256 qSetHash;
    SCPQuorumSet qSet;
    SCPEnvelope envelope;
    uint32 getSCPLedgerSeq;
  } StellarMessage_u;
};
typedef struct StellarMessage StellarMessage;
#ifdef __cplusplus
extern "C" bool_t xdr_StellarMessage(XDR *, StellarMessage *);
#elif __STDC__
extern bool_t xdr_StellarMessage(XDR *, StellarMessage *);
#else  /* Old Style C */
bool_t xdr_StellarMessage();
#endif /* Old Style C */

struct AuthenticatedMessageV0 {
  uint64 sequence;
  StellarMessage message;
  HmacSha256Mac mac;
};
typedef struct AuthenticatedMessageV0 AuthenticatedMessageV0;
#ifdef __cplusplus
extern "C" bool_t xdr_AuthenticatedMessageV0(XDR *, AuthenticatedMessageV0 *);
#elif __STDC__
extern bool_t xdr_AuthenticatedMessageV0(XDR *, AuthenticatedMessageV0 *);
#else  /* Old Style C */
bool_t xdr_AuthenticatedMessageV0();
#endif /* Old Style C */

struct AuthenticatedMessage {
  uint32 v;
  union {
    AuthenticatedMessageV0 v0;
  } AuthenticatedMessage_u;
};
typedef struct AuthenticatedMessage AuthenticatedMessage;
#ifdef __cplusplus
extern "C" bool_t xdr_AuthenticatedMessage(XDR *, AuthenticatedMessage *);
#elif __STDC__
extern bool_t xdr_AuthenticatedMessage(XDR *, AuthenticatedMessage *);
#else  /* Old Style C */
bool_t xdr_AuthenticatedMessage();
#endif /* Old Style C */

#endif /* !_STELLAR_H_RPCGEN */
