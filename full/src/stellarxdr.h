#ifndef _STELLARXDR_H
#define _STELLARXDR_H

#define RPCGEN_VERSION 199506

#define STELLAR_PROTOCOL 18

#define VERSION_MAJOR 0
#define VERSION_MINOR 18
#define VERSION_PATCH 0

#include <rpc/rpc.h>

// TODO: uint8?
typedef char stellarxdr_Hash[32];
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Hash(XDR *, stellarxdr_Hash);
#elif __STDC__
extern bool_t xdr_stellarxdr_Hash(XDR *, stellarxdr_Hash);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Hash();
#endif /* Old Style C */

typedef char stellarxdr_uint256[32];
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_uint256(XDR *, stellarxdr_uint256);
#elif __STDC__
extern bool_t xdr_stellarxdr_uint256(XDR *, stellarxdr_uint256);
#else  /* Old Style C */
bool_t xdr_stellarxdr_uint256();
#endif /* Old Style C */

typedef u_int stellarxdr_uint32;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_uint32(XDR *, stellarxdr_uint32 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_uint32(XDR *, stellarxdr_uint32 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_uint32();
#endif /* Old Style C */

typedef int stellarxdr_int32;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_int32(XDR *, stellarxdr_int32 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_int32(XDR *, stellarxdr_int32 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_int32();
#endif /* Old Style C */

typedef u_int64_t stellarxdr_uint64;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_uint64(XDR *, stellarxdr_uint64 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_uint64(XDR *, stellarxdr_uint64 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_uint64();
#endif /* Old Style C */

typedef int64_t stellarxdr_int64;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_int64(XDR *, stellarxdr_int64 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_int64(XDR *, stellarxdr_int64 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_int64();
#endif /* Old Style C */

enum stellarxdr_CryptoKeyType {
  stellarxdr_KEY_TYPE_ED25519 = 0,
  stellarxdr_KEY_TYPE_PRE_AUTH_TX = 1,
  stellarxdr_KEY_TYPE_HASH_X = 2,
  stellarxdr_KEY_TYPE_MUXED_ED25519 = 0x100,
};
typedef enum stellarxdr_CryptoKeyType stellarxdr_CryptoKeyType;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_CryptoKeyType(XDR *,
                                               stellarxdr_CryptoKeyType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_CryptoKeyType(XDR *, stellarxdr_CryptoKeyType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_CryptoKeyType();
#endif /* Old Style C */

enum stellarxdr_PublicKeyType {
  stellarxdr_PUBLIC_KEY_TYPE_ED25519 = stellarxdr_KEY_TYPE_ED25519,
};
typedef enum stellarxdr_PublicKeyType stellarxdr_PublicKeyType;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PublicKeyType(XDR *,
                                               stellarxdr_PublicKeyType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PublicKeyType(XDR *, stellarxdr_PublicKeyType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PublicKeyType();
#endif /* Old Style C */

enum stellarxdr_SignerKeyType {
  stellarxdr_SIGNER_KEY_TYPE_ED25519 = stellarxdr_KEY_TYPE_ED25519,
  stellarxdr_SIGNER_KEY_TYPE_PRE_AUTH_TX = stellarxdr_KEY_TYPE_PRE_AUTH_TX,
  stellarxdr_SIGNER_KEY_TYPE_HASH_X = stellarxdr_KEY_TYPE_HASH_X,
};
typedef enum stellarxdr_SignerKeyType stellarxdr_SignerKeyType;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SignerKeyType(XDR *,
                                               stellarxdr_SignerKeyType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SignerKeyType(XDR *, stellarxdr_SignerKeyType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SignerKeyType();
#endif /* Old Style C */

struct stellarxdr_PublicKey {
  stellarxdr_PublicKeyType type;
  union {
    stellarxdr_uint256 ed25519;
  } stellarxdr_PublicKey_u;
};
typedef struct stellarxdr_PublicKey stellarxdr_PublicKey;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PublicKey(XDR *, stellarxdr_PublicKey *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PublicKey(XDR *, stellarxdr_PublicKey *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PublicKey();
#endif /* Old Style C */

struct stellarxdr_SignerKey {
  stellarxdr_SignerKeyType type;
  union {
    stellarxdr_uint256 ed25519;
    stellarxdr_uint256 preAuthTx;
    stellarxdr_uint256 hashX;
  } stellarxdr_SignerKey_u;
};
typedef struct stellarxdr_SignerKey stellarxdr_SignerKey;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SignerKey(XDR *, stellarxdr_SignerKey *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SignerKey(XDR *, stellarxdr_SignerKey *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SignerKey();
#endif /* Old Style C */

typedef struct {
  u_int stellarxdr_Signature_len;
  char *stellarxdr_Signature_val;
} stellarxdr_Signature;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Signature(XDR *, stellarxdr_Signature *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Signature(XDR *, stellarxdr_Signature *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Signature();
#endif /* Old Style C */

typedef char stellarxdr_SignatureHint[4];
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SignatureHint(XDR *, stellarxdr_SignatureHint);
#elif __STDC__
extern bool_t xdr_stellarxdr_SignatureHint(XDR *, stellarxdr_SignatureHint);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SignatureHint();
#endif /* Old Style C */

typedef stellarxdr_PublicKey stellarxdr_NodeID;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_NodeID(XDR *, stellarxdr_NodeID *);
#elif __STDC__
extern bool_t xdr_stellarxdr_NodeID(XDR *, stellarxdr_NodeID *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_NodeID();
#endif /* Old Style C */

struct stellarxdr_Curve25519Secret {
  char key[32];
};
typedef struct stellarxdr_Curve25519Secret stellarxdr_Curve25519Secret;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_Curve25519Secret(XDR *, stellarxdr_Curve25519Secret *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Curve25519Secret(XDR *,
                                              stellarxdr_Curve25519Secret *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Curve25519Secret();
#endif /* Old Style C */

struct stellarxdr_Curve25519Public {
  char key[32];
};
typedef struct stellarxdr_Curve25519Public stellarxdr_Curve25519Public;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_Curve25519Public(XDR *, stellarxdr_Curve25519Public *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Curve25519Public(XDR *,
                                              stellarxdr_Curve25519Public *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Curve25519Public();
#endif /* Old Style C */

struct stellarxdr_HmacSha256Key {
  char key[32];
};
typedef struct stellarxdr_HmacSha256Key stellarxdr_HmacSha256Key;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_HmacSha256Key(XDR *,
                                               stellarxdr_HmacSha256Key *);
#elif __STDC__
extern bool_t xdr_stellarxdr_HmacSha256Key(XDR *, stellarxdr_HmacSha256Key *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_HmacSha256Key();
#endif /* Old Style C */

struct stellarxdr_HmacSha256Mac {
  char mac[32];
};
typedef struct stellarxdr_HmacSha256Mac stellarxdr_HmacSha256Mac;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_HmacSha256Mac(XDR *,
                                               stellarxdr_HmacSha256Mac *);
#elif __STDC__
extern bool_t xdr_stellarxdr_HmacSha256Mac(XDR *, stellarxdr_HmacSha256Mac *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_HmacSha256Mac();
#endif /* Old Style C */

typedef struct {
  u_int stellarxdr_Value_len;
  char *stellarxdr_Value_val;
} stellarxdr_Value;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Value(XDR *, stellarxdr_Value *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Value(XDR *, stellarxdr_Value *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Value();
#endif /* Old Style C */

struct stellarxdr_SCPBallot {
  stellarxdr_uint32 counter;
  stellarxdr_Value value;
};
typedef struct stellarxdr_SCPBallot stellarxdr_SCPBallot;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SCPBallot(XDR *, stellarxdr_SCPBallot *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SCPBallot(XDR *, stellarxdr_SCPBallot *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SCPBallot();
#endif /* Old Style C */

enum stellarxdr_SCPStatementType {
  stellarxdr_SCP_ST_PREPARE = 0,
  stellarxdr_SCP_ST_CONFIRM = 1,
  stellarxdr_SCP_ST_EXTERNALIZE = 2,
  stellarxdr_SCP_ST_NOMINATE = 3,
};
typedef enum stellarxdr_SCPStatementType stellarxdr_SCPStatementType;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_SCPStatementType(XDR *, stellarxdr_SCPStatementType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SCPStatementType(XDR *,
                                              stellarxdr_SCPStatementType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SCPStatementType();
#endif /* Old Style C */

struct stellarxdr_SCPNomination {
  stellarxdr_Hash quorumSetHash;
  struct {
    u_int votes_len;
    stellarxdr_Value *votes_val;
  } votes;
  struct {
    u_int accepted_len;
    stellarxdr_Value *accepted_val;
  } accepted;
};
typedef struct stellarxdr_SCPNomination stellarxdr_SCPNomination;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SCPNomination(XDR *,
                                               stellarxdr_SCPNomination *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SCPNomination(XDR *, stellarxdr_SCPNomination *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SCPNomination();
#endif /* Old Style C */

struct stellarxdr_SCPPrepare {
  stellarxdr_Hash quorumSetHash;
  stellarxdr_SCPBallot ballot;
  stellarxdr_SCPBallot *prepared;
  stellarxdr_SCPBallot *preparedPrime;
  stellarxdr_uint32 nC;
  stellarxdr_uint32 nH;
};
typedef struct stellarxdr_SCPPrepare stellarxdr_SCPPrepare;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SCPPrepare(XDR *, stellarxdr_SCPPrepare *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SCPPrepare(XDR *, stellarxdr_SCPPrepare *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SCPPrepare();
#endif /* Old Style C */

struct stellarxdr_SCPConfirm {
  stellarxdr_SCPBallot ballot;
  stellarxdr_uint32 nPrepared;
  stellarxdr_uint32 nCommit;
  stellarxdr_uint32 nH;
  stellarxdr_Hash quorumSetHash;
};
typedef struct stellarxdr_SCPConfirm stellarxdr_SCPConfirm;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SCPConfirm(XDR *, stellarxdr_SCPConfirm *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SCPConfirm(XDR *, stellarxdr_SCPConfirm *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SCPConfirm();
#endif /* Old Style C */

struct stellarxdr_SCPExternalize {
  stellarxdr_SCPBallot commit;
  stellarxdr_uint32 nH;
  stellarxdr_Hash commitQuorumSetHash;
};
typedef struct stellarxdr_SCPExternalize stellarxdr_SCPExternalize;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SCPExternalize(XDR *,
                                                stellarxdr_SCPExternalize *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SCPExternalize(XDR *, stellarxdr_SCPExternalize *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SCPExternalize();
#endif /* Old Style C */

struct stellarxdr_SCPStatementPledges {
  stellarxdr_SCPStatementType type;
  union {
    stellarxdr_SCPPrepare prepare;
    stellarxdr_SCPConfirm confirm;
    stellarxdr_SCPExternalize externalize;
    stellarxdr_SCPNomination nominate;
  } stellarxdr_SCPStatementPledges_u;
};
typedef struct stellarxdr_SCPStatementPledges stellarxdr_SCPStatementPledges;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_SCPStatementPledges(XDR *, stellarxdr_SCPStatementPledges *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_SCPStatementPledges(XDR *, stellarxdr_SCPStatementPledges *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SCPStatementPledges();
#endif /* Old Style C */

struct stellarxdr_SCPStatement {
  stellarxdr_NodeID nodeID;
  stellarxdr_uint64 slotIndex;
  stellarxdr_SCPStatementPledges pledges;
};
typedef struct stellarxdr_SCPStatement stellarxdr_SCPStatement;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SCPStatement(XDR *, stellarxdr_SCPStatement *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SCPStatement(XDR *, stellarxdr_SCPStatement *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SCPStatement();
#endif /* Old Style C */

struct stellarxdr_SCPEnvelope {
  stellarxdr_SCPStatement statement;
  stellarxdr_Signature signature;
};
typedef struct stellarxdr_SCPEnvelope stellarxdr_SCPEnvelope;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SCPEnvelope(XDR *, stellarxdr_SCPEnvelope *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SCPEnvelope(XDR *, stellarxdr_SCPEnvelope *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SCPEnvelope();
#endif /* Old Style C */

struct stellarxdr_SCPQuorumSet {
  stellarxdr_uint32 threshold;
  struct {
    u_int validators_len;
    stellarxdr_NodeID *validators_val;
  } validators;
  struct {
    u_int innerSets_len;
    struct stellarxdr_SCPQuorumSet *innerSets_val;
  } innerSets;
};
typedef struct stellarxdr_SCPQuorumSet stellarxdr_SCPQuorumSet;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SCPQuorumSet(XDR *, stellarxdr_SCPQuorumSet *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SCPQuorumSet(XDR *, stellarxdr_SCPQuorumSet *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SCPQuorumSet();
#endif /* Old Style C */

typedef stellarxdr_PublicKey stellarxdr_AccountID;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_AccountID(XDR *, stellarxdr_AccountID *);
#elif __STDC__
extern bool_t xdr_stellarxdr_AccountID(XDR *, stellarxdr_AccountID *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AccountID();
#endif /* Old Style C */

typedef char stellarxdr_Thresholds[4];
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Thresholds(XDR *, stellarxdr_Thresholds);
#elif __STDC__
extern bool_t xdr_stellarxdr_Thresholds(XDR *, stellarxdr_Thresholds);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Thresholds();
#endif /* Old Style C */

typedef char *stellarxdr_string32;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_string32(XDR *, stellarxdr_string32 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_string32(XDR *, stellarxdr_string32 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_string32();
#endif /* Old Style C */

typedef char *stellarxdr_string64;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_string64(XDR *, stellarxdr_string64 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_string64(XDR *, stellarxdr_string64 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_string64();
#endif /* Old Style C */

typedef stellarxdr_int64 stellarxdr_SequenceNumber;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SequenceNumber(XDR *,
                                                stellarxdr_SequenceNumber *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SequenceNumber(XDR *, stellarxdr_SequenceNumber *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SequenceNumber();
#endif /* Old Style C */

typedef stellarxdr_uint64 stellarxdr_TimePoint;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TimePoint(XDR *, stellarxdr_TimePoint *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TimePoint(XDR *, stellarxdr_TimePoint *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TimePoint();
#endif /* Old Style C */

typedef struct {
  u_int stellarxdr_DataValue_len;
  char *stellarxdr_DataValue_val;
} stellarxdr_DataValue;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_DataValue(XDR *, stellarxdr_DataValue *);
#elif __STDC__
extern bool_t xdr_stellarxdr_DataValue(XDR *, stellarxdr_DataValue *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_DataValue();
#endif /* Old Style C */

typedef stellarxdr_Hash stellarxdr_PoolID;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PoolID(XDR *, stellarxdr_PoolID);
#elif __STDC__
extern bool_t xdr_stellarxdr_PoolID(XDR *, stellarxdr_PoolID);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PoolID();
#endif /* Old Style C */

typedef char stellarxdr_AssetCode4[4];
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_AssetCode4(XDR *, stellarxdr_AssetCode4);
#elif __STDC__
extern bool_t xdr_stellarxdr_AssetCode4(XDR *, stellarxdr_AssetCode4);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AssetCode4();
#endif /* Old Style C */

typedef char stellarxdr_AssetCode12[12];
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_AssetCode12(XDR *, stellarxdr_AssetCode12);
#elif __STDC__
extern bool_t xdr_stellarxdr_AssetCode12(XDR *, stellarxdr_AssetCode12);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AssetCode12();
#endif /* Old Style C */

enum stellarxdr_AssetType {
  stellarxdr_ASSET_TYPE_NATIVE = 0,
  stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4 = 1,
  stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12 = 2,
  stellarxdr_ASSET_TYPE_POOL_SHARE = 3,
};
typedef enum stellarxdr_AssetType stellarxdr_AssetType;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_AssetType(XDR *, stellarxdr_AssetType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_AssetType(XDR *, stellarxdr_AssetType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AssetType();
#endif /* Old Style C */

struct stellarxdr_AssetCode {
  stellarxdr_AssetType type;
  union {
    stellarxdr_AssetCode4 assetCode4;
    stellarxdr_AssetCode12 assetCode12;
  } stellarxdr_AssetCode_u;
};
typedef struct stellarxdr_AssetCode stellarxdr_AssetCode;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_AssetCode(XDR *, stellarxdr_AssetCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_AssetCode(XDR *, stellarxdr_AssetCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AssetCode();
#endif /* Old Style C */

struct stellarxdr_AlphaNum4 {
  stellarxdr_AssetCode4 assetCode;
  stellarxdr_AccountID issuer;
};
typedef struct stellarxdr_AlphaNum4 stellarxdr_AlphaNum4;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_AlphaNum4(XDR *, stellarxdr_AlphaNum4 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_AlphaNum4(XDR *, stellarxdr_AlphaNum4 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AlphaNum4();
#endif /* Old Style C */

struct stellarxdr_AlphaNum12 {
  stellarxdr_AssetCode12 assetCode;
  stellarxdr_AccountID issuer;
};
typedef struct stellarxdr_AlphaNum12 stellarxdr_AlphaNum12;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_AlphaNum12(XDR *, stellarxdr_AlphaNum12 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_AlphaNum12(XDR *, stellarxdr_AlphaNum12 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AlphaNum12();
#endif /* Old Style C */

struct stellarxdr_Asset {
  stellarxdr_AssetType type;
  union {
    stellarxdr_AlphaNum4 alphaNum4;
    stellarxdr_AlphaNum12 alphaNum12;
  } stellarxdr_Asset_u;
};
typedef struct stellarxdr_Asset stellarxdr_Asset;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Asset(XDR *, stellarxdr_Asset *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Asset(XDR *, stellarxdr_Asset *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Asset();
#endif /* Old Style C */

struct stellarxdr_Price {
  stellarxdr_int32 n;
  stellarxdr_int32 d;
};
typedef struct stellarxdr_Price stellarxdr_Price;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Price(XDR *, stellarxdr_Price *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Price(XDR *, stellarxdr_Price *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Price();
#endif /* Old Style C */

struct stellarxdr_Liabilities {
  stellarxdr_int64 buying;
  stellarxdr_int64 selling;
};
typedef struct stellarxdr_Liabilities stellarxdr_Liabilities;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Liabilities(XDR *, stellarxdr_Liabilities *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Liabilities(XDR *, stellarxdr_Liabilities *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Liabilities();
#endif /* Old Style C */

enum stellarxdr_ThresholdIndexes {
  stellarxdr_THRESHOLD_MASTER_WEIGHT = 0,
  stellarxdr_THRESHOLD_LOW = 1,
  stellarxdr_THRESHOLD_MED = 2,
  stellarxdr_THRESHOLD_HIGH = 3,
};
typedef enum stellarxdr_ThresholdIndexes stellarxdr_ThresholdIndexes;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ThresholdIndexes(XDR *, stellarxdr_ThresholdIndexes *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ThresholdIndexes(XDR *,
                                              stellarxdr_ThresholdIndexes *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ThresholdIndexes();
#endif /* Old Style C */

enum stellarxdr_LedgerEntryType {
  stellarxdr_ACCOUNT = 0,
  stellarxdr_TRUSTLINE = 1,
  stellarxdr_OFFER = 2,
  stellarxdr_DATA = 3,
  stellarxdr_CLAIMABLE_BALANCE = 4,
  stellarxdr_LIQUIDITY_POOL = 5,
};
typedef enum stellarxdr_LedgerEntryType stellarxdr_LedgerEntryType;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerEntryType(XDR *,
                                                 stellarxdr_LedgerEntryType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerEntryType(XDR *,
                                             stellarxdr_LedgerEntryType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerEntryType();
#endif /* Old Style C */

struct stellarxdr_Signer {
  stellarxdr_SignerKey key;
  stellarxdr_uint32 weight;
};
typedef struct stellarxdr_Signer stellarxdr_Signer;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Signer(XDR *, stellarxdr_Signer *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Signer(XDR *, stellarxdr_Signer *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Signer();
#endif /* Old Style C */

enum stellarxdr_AccountFlags {
  stellarxdr_AUTH_REQUIRED_FLAG = 0x1,
  stellarxdr_AUTH_REVOCABLE_FLAG = 0x2,
  stellarxdr_AUTH_IMMUTABLE_FLAG = 0x4,
  stellarxdr_AUTH_CLAWBACK_ENABLED_FLAG = 0x8,
};
typedef enum stellarxdr_AccountFlags stellarxdr_AccountFlags;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_AccountFlags(XDR *, stellarxdr_AccountFlags *);
#elif __STDC__
extern bool_t xdr_stellarxdr_AccountFlags(XDR *, stellarxdr_AccountFlags *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AccountFlags();
#endif /* Old Style C */

#define stellarxdr_MASK_ACCOUNT_FLAGS 0x7
#define stellarxdr_MASK_ACCOUNT_FLAGS_V17 0xF
#define stellarxdr_MAX_SIGNERS 20

typedef stellarxdr_AccountID *stellarxdr_SponsorshipDescriptor;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_SponsorshipDescriptor(XDR *, stellarxdr_SponsorshipDescriptor *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_SponsorshipDescriptor(XDR *, stellarxdr_SponsorshipDescriptor *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SponsorshipDescriptor();
#endif /* Old Style C */

struct stellarxdr_AccountEntryExtensionV2Ext {
  int v;
  union {
  } stellarxdr_AccountEntryExtensionV2Ext_u;
};
typedef struct stellarxdr_AccountEntryExtensionV2Ext
    stellarxdr_AccountEntryExtensionV2Ext;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_AccountEntryExtensionV2Ext(
    XDR *, stellarxdr_AccountEntryExtensionV2Ext *);
#elif __STDC__
extern bool_t xdr_stellarxdr_AccountEntryExtensionV2Ext(
    XDR *, stellarxdr_AccountEntryExtensionV2Ext *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AccountEntryExtensionV2Ext();
#endif /* Old Style C */

struct stellarxdr_AccountEntryExtensionV2 {
  stellarxdr_uint32 numSponsored;
  stellarxdr_uint32 numSponsoring;
  struct {
    u_int signerSponsoringIDs_len;
    stellarxdr_SponsorshipDescriptor *signerSponsoringIDs_val;
  } signerSponsoringIDs;
  stellarxdr_AccountEntryExtensionV2Ext ext;
};
typedef struct stellarxdr_AccountEntryExtensionV2
    stellarxdr_AccountEntryExtensionV2;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_AccountEntryExtensionV2(XDR *,
                                       stellarxdr_AccountEntryExtensionV2 *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_AccountEntryExtensionV2(XDR *,
                                       stellarxdr_AccountEntryExtensionV2 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AccountEntryExtensionV2();
#endif /* Old Style C */

struct stellarxdr_AccountEntryExtensionV1Ext {
  int v;
  union {
    stellarxdr_AccountEntryExtensionV2 v2;
  } stellarxdr_AccountEntryExtensionV1Ext_u;
};
typedef struct stellarxdr_AccountEntryExtensionV1Ext
    stellarxdr_AccountEntryExtensionV1Ext;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_AccountEntryExtensionV1Ext(
    XDR *, stellarxdr_AccountEntryExtensionV1Ext *);
#elif __STDC__
extern bool_t xdr_stellarxdr_AccountEntryExtensionV1Ext(
    XDR *, stellarxdr_AccountEntryExtensionV1Ext *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AccountEntryExtensionV1Ext();
#endif /* Old Style C */

struct stellarxdr_AccountEntryExtensionV1 {
  stellarxdr_Liabilities liabilities;
  stellarxdr_AccountEntryExtensionV1Ext ext;
};
typedef struct stellarxdr_AccountEntryExtensionV1
    stellarxdr_AccountEntryExtensionV1;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_AccountEntryExtensionV1(XDR *,
                                       stellarxdr_AccountEntryExtensionV1 *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_AccountEntryExtensionV1(XDR *,
                                       stellarxdr_AccountEntryExtensionV1 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AccountEntryExtensionV1();
#endif /* Old Style C */

struct stellarxdr_AccountEntryExt {
  int v;
  union {
    stellarxdr_AccountEntryExtensionV1 v1;
  } stellarxdr_AccountEntryExt_u;
};
typedef struct stellarxdr_AccountEntryExt stellarxdr_AccountEntryExt;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_AccountEntryExt(XDR *,
                                                 stellarxdr_AccountEntryExt *);
#elif __STDC__
extern bool_t xdr_stellarxdr_AccountEntryExt(XDR *,
                                             stellarxdr_AccountEntryExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AccountEntryExt();
#endif /* Old Style C */

struct stellarxdr_AccountEntry {
  stellarxdr_AccountID accountID;
  stellarxdr_int64 balance;
  stellarxdr_SequenceNumber seqNum;
  stellarxdr_uint32 numSubEntries;
  stellarxdr_AccountID *inflationDest;
  stellarxdr_uint32 flags;
  stellarxdr_string32 homeDomain;
  stellarxdr_Thresholds thresholds;
  struct {
    u_int signers_len;
    stellarxdr_Signer *signers_val;
  } signers;
  stellarxdr_AccountEntryExt ext;
};
typedef struct stellarxdr_AccountEntry stellarxdr_AccountEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_AccountEntry(XDR *, stellarxdr_AccountEntry *);
#elif __STDC__
extern bool_t xdr_stellarxdr_AccountEntry(XDR *, stellarxdr_AccountEntry *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AccountEntry();
#endif /* Old Style C */

enum stellarxdr_TrustLineFlags {
  stellarxdr_AUTHORIZED_FLAG = 1,
  stellarxdr_AUTHORIZED_TO_MAINTAIN_LIABILITIES_FLAG = 2,
  stellarxdr_TRUSTLINE_CLAWBACK_ENABLED_FLAG = 4,
};
typedef enum stellarxdr_TrustLineFlags stellarxdr_TrustLineFlags;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TrustLineFlags(XDR *,
                                                stellarxdr_TrustLineFlags *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TrustLineFlags(XDR *, stellarxdr_TrustLineFlags *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TrustLineFlags();
#endif /* Old Style C */

#define stellarxdr_MASK_TRUSTLINE_FLAGS 1
#define stellarxdr_MASK_TRUSTLINE_FLAGS_V13 3
#define stellarxdr_MASK_TRUSTLINE_FLAGS_V17 7

enum stellarxdr_LiquidityPoolType {
  stellarxdr_LIQUIDITY_POOL_CONSTANT_PRODUCT = 0,
};
typedef enum stellarxdr_LiquidityPoolType stellarxdr_LiquidityPoolType;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LiquidityPoolType(XDR *, stellarxdr_LiquidityPoolType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LiquidityPoolType(XDR *,
                                               stellarxdr_LiquidityPoolType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LiquidityPoolType();
#endif /* Old Style C */

struct stellarxdr_TrustLineAsset {
  stellarxdr_AssetType type;
  union {
    stellarxdr_AlphaNum4 alphaNum4;
    stellarxdr_AlphaNum12 alphaNum12;
    stellarxdr_PoolID liquidityPoolID;
  } stellarxdr_TrustLineAsset_u;
};
typedef struct stellarxdr_TrustLineAsset stellarxdr_TrustLineAsset;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TrustLineAsset(XDR *,
                                                stellarxdr_TrustLineAsset *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TrustLineAsset(XDR *, stellarxdr_TrustLineAsset *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TrustLineAsset();
#endif /* Old Style C */

struct stellarxdr_TrustLineEntryExtensionV2Ext {
  int v;
  union {
  } stellarxdr_TrustLineEntryExtensionV2Ext_u;
};
typedef struct stellarxdr_TrustLineEntryExtensionV2Ext
    stellarxdr_TrustLineEntryExtensionV2Ext;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TrustLineEntryExtensionV2Ext(
    XDR *, stellarxdr_TrustLineEntryExtensionV2Ext *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TrustLineEntryExtensionV2Ext(
    XDR *, stellarxdr_TrustLineEntryExtensionV2Ext *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TrustLineEntryExtensionV2Ext();
#endif /* Old Style C */

struct stellarxdr_TrustLineEntryExtensionV2 {
  stellarxdr_int32 liquidityPoolUseCount;
  stellarxdr_TrustLineEntryExtensionV2Ext ext;
};
typedef struct stellarxdr_TrustLineEntryExtensionV2
    stellarxdr_TrustLineEntryExtensionV2;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TrustLineEntryExtensionV2(
    XDR *, stellarxdr_TrustLineEntryExtensionV2 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TrustLineEntryExtensionV2(
    XDR *, stellarxdr_TrustLineEntryExtensionV2 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TrustLineEntryExtensionV2();
#endif /* Old Style C */

struct stellarxdr_TrustLineEntryV1Ext {
  int v;
  union {
    stellarxdr_TrustLineEntryExtensionV2 v2;
  } stellarxdr_TrustLineEntryV1Ext_u;
};
typedef struct stellarxdr_TrustLineEntryV1Ext stellarxdr_TrustLineEntryV1Ext;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TrustLineEntryV1Ext(XDR *, stellarxdr_TrustLineEntryV1Ext *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_TrustLineEntryV1Ext(XDR *, stellarxdr_TrustLineEntryV1Ext *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TrustLineEntryV1Ext();
#endif /* Old Style C */

struct stellarxdr_TrustLineEntryV1 {
  stellarxdr_Liabilities liabilities;
  stellarxdr_TrustLineEntryV1Ext ext;
};
typedef struct stellarxdr_TrustLineEntryV1 stellarxdr_TrustLineEntryV1;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TrustLineEntryV1(XDR *, stellarxdr_TrustLineEntryV1 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TrustLineEntryV1(XDR *,
                                              stellarxdr_TrustLineEntryV1 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TrustLineEntryV1();
#endif /* Old Style C */

struct stellarxdr_TrustLineEntryExt {
  int v;
  union {
    stellarxdr_TrustLineEntryV1 v1;
  } stellarxdr_TrustLineEntryExt_u;
};
typedef struct stellarxdr_TrustLineEntryExt stellarxdr_TrustLineEntryExt;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TrustLineEntryExt(XDR *, stellarxdr_TrustLineEntryExt *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TrustLineEntryExt(XDR *,
                                               stellarxdr_TrustLineEntryExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TrustLineEntryExt();
#endif /* Old Style C */

struct stellarxdr_TrustLineEntry {
  stellarxdr_AccountID accountID;
  stellarxdr_TrustLineAsset asset;
  stellarxdr_int64 balance;
  stellarxdr_int64 limit;
  stellarxdr_uint32 flags;
  stellarxdr_TrustLineEntryExt ext;
};
typedef struct stellarxdr_TrustLineEntry stellarxdr_TrustLineEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TrustLineEntry(XDR *,
                                                stellarxdr_TrustLineEntry *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TrustLineEntry(XDR *, stellarxdr_TrustLineEntry *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TrustLineEntry();
#endif /* Old Style C */

enum stellarxdr_OfferEntryFlags {
  stellarxdr_PASSIVE_FLAG = 1,
};
typedef enum stellarxdr_OfferEntryFlags stellarxdr_OfferEntryFlags;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_OfferEntryFlags(XDR *,
                                                 stellarxdr_OfferEntryFlags *);
#elif __STDC__
extern bool_t xdr_stellarxdr_OfferEntryFlags(XDR *,
                                             stellarxdr_OfferEntryFlags *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_OfferEntryFlags();
#endif /* Old Style C */

#define stellarxdr_MASK_OFFERENTRY_FLAGS 1

struct stellarxdr_OfferEntryExt {
  int v;
  union {
  } stellarxdr_OfferEntryExt_u;
};
typedef struct stellarxdr_OfferEntryExt stellarxdr_OfferEntryExt;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_OfferEntryExt(XDR *,
                                               stellarxdr_OfferEntryExt *);
#elif __STDC__
extern bool_t xdr_stellarxdr_OfferEntryExt(XDR *, stellarxdr_OfferEntryExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_OfferEntryExt();
#endif /* Old Style C */

struct stellarxdr_OfferEntry {
  stellarxdr_AccountID sellerID;
  stellarxdr_int64 offerID;
  stellarxdr_Asset selling;
  stellarxdr_Asset buying;
  stellarxdr_int64 amount;
  stellarxdr_Price price;
  stellarxdr_uint32 flags;
  stellarxdr_OfferEntryExt ext;
};
typedef struct stellarxdr_OfferEntry stellarxdr_OfferEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_OfferEntry(XDR *, stellarxdr_OfferEntry *);
#elif __STDC__
extern bool_t xdr_stellarxdr_OfferEntry(XDR *, stellarxdr_OfferEntry *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_OfferEntry();
#endif /* Old Style C */

struct stellarxdr_DataEntryExt {
  int v;
  union {
  } stellarxdr_DataEntryExt_u;
};
typedef struct stellarxdr_DataEntryExt stellarxdr_DataEntryExt;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_DataEntryExt(XDR *, stellarxdr_DataEntryExt *);
#elif __STDC__
extern bool_t xdr_stellarxdr_DataEntryExt(XDR *, stellarxdr_DataEntryExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_DataEntryExt();
#endif /* Old Style C */

struct stellarxdr_DataEntry {
  stellarxdr_AccountID accountID;
  stellarxdr_string64 dataName;
  stellarxdr_DataValue dataValue;
  stellarxdr_DataEntryExt ext;
};
typedef struct stellarxdr_DataEntry stellarxdr_DataEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_DataEntry(XDR *, stellarxdr_DataEntry *);
#elif __STDC__
extern bool_t xdr_stellarxdr_DataEntry(XDR *, stellarxdr_DataEntry *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_DataEntry();
#endif /* Old Style C */

enum stellarxdr_ClaimPredicateType {
  stellarxdr_CLAIM_PREDICATE_UNCONDITIONAL = 0,
  stellarxdr_CLAIM_PREDICATE_AND = 1,
  stellarxdr_CLAIM_PREDICATE_OR = 2,
  stellarxdr_CLAIM_PREDICATE_NOT = 3,
  stellarxdr_CLAIM_PREDICATE_BEFORE_ABSOLUTE_TIME = 4,
  stellarxdr_CLAIM_PREDICATE_BEFORE_RELATIVE_TIME = 5,
};
typedef enum stellarxdr_ClaimPredicateType stellarxdr_ClaimPredicateType;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ClaimPredicateType(XDR *, stellarxdr_ClaimPredicateType *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ClaimPredicateType(XDR *, stellarxdr_ClaimPredicateType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimPredicateType();
#endif /* Old Style C */

struct stellarxdr_ClaimPredicate {
  stellarxdr_ClaimPredicateType type;
  union {
    struct {
      u_int andPredicates_len;
      struct stellarxdr_ClaimPredicate *andPredicates_val;
    } andPredicates;
    struct {
      u_int orPredicates_len;
      struct stellarxdr_ClaimPredicate *orPredicates_val;
    } orPredicates;
    struct stellarxdr_ClaimPredicate *notPredicate;
    stellarxdr_int64 absBefore;
    stellarxdr_int64 relBefore;
  } stellarxdr_ClaimPredicate_u;
};
typedef struct stellarxdr_ClaimPredicate stellarxdr_ClaimPredicate;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClaimPredicate(XDR *,
                                                stellarxdr_ClaimPredicate *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClaimPredicate(XDR *, stellarxdr_ClaimPredicate *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimPredicate();
#endif /* Old Style C */

enum stellarxdr_ClaimantType {
  stellarxdr_CLAIMANT_TYPE_V0 = 0,
};
typedef enum stellarxdr_ClaimantType stellarxdr_ClaimantType;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClaimantType(XDR *, stellarxdr_ClaimantType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClaimantType(XDR *, stellarxdr_ClaimantType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimantType();
#endif /* Old Style C */

struct stellarxdr_ClaimantV0 {
  stellarxdr_AccountID destination;
  stellarxdr_ClaimPredicate predicate;
};
typedef struct stellarxdr_ClaimantV0 stellarxdr_ClaimantV0;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClaimantV0(XDR *, stellarxdr_ClaimantV0 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClaimantV0(XDR *, stellarxdr_ClaimantV0 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimantV0();
#endif /* Old Style C */

struct stellarxdr_Claimant {
  stellarxdr_ClaimantType type;
  union {
    stellarxdr_ClaimantV0 v0;
  } stellarxdr_Claimant_u;
};
typedef struct stellarxdr_Claimant stellarxdr_Claimant;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Claimant(XDR *, stellarxdr_Claimant *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Claimant(XDR *, stellarxdr_Claimant *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Claimant();
#endif /* Old Style C */

enum stellarxdr_ClaimableBalanceIDType {
  stellarxdr_CLAIMABLE_BALANCE_ID_TYPE_V0 = 0,
};
typedef enum stellarxdr_ClaimableBalanceIDType
    stellarxdr_ClaimableBalanceIDType;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ClaimableBalanceIDType(XDR *,
                                      stellarxdr_ClaimableBalanceIDType *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ClaimableBalanceIDType(XDR *,
                                      stellarxdr_ClaimableBalanceIDType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimableBalanceIDType();
#endif /* Old Style C */

struct stellarxdr_ClaimableBalanceID {
  stellarxdr_ClaimableBalanceIDType type;
  union {
    stellarxdr_Hash v0;
  } stellarxdr_ClaimableBalanceID_u;
};
typedef struct stellarxdr_ClaimableBalanceID stellarxdr_ClaimableBalanceID;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ClaimableBalanceID(XDR *, stellarxdr_ClaimableBalanceID *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ClaimableBalanceID(XDR *, stellarxdr_ClaimableBalanceID *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimableBalanceID();
#endif /* Old Style C */

enum stellarxdr_ClaimableBalanceFlags {
  stellarxdr_CLAIMABLE_BALANCE_CLAWBACK_ENABLED_FLAG = 0x1,
};
typedef enum stellarxdr_ClaimableBalanceFlags stellarxdr_ClaimableBalanceFlags;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ClaimableBalanceFlags(XDR *, stellarxdr_ClaimableBalanceFlags *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ClaimableBalanceFlags(XDR *, stellarxdr_ClaimableBalanceFlags *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimableBalanceFlags();
#endif /* Old Style C */

#define stellarxdr_MASK_CLAIMABLE_BALANCE_FLAGS 0x1

struct stellarxdr_ClaimableBalanceEntryExtensionV1Ext {
  int v;
  union {
  } stellarxdr_ClaimableBalanceEntryExtensionV1Ext_u;
};
typedef struct stellarxdr_ClaimableBalanceEntryExtensionV1Ext
    stellarxdr_ClaimableBalanceEntryExtensionV1Ext;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClaimableBalanceEntryExtensionV1Ext(
    XDR *, stellarxdr_ClaimableBalanceEntryExtensionV1Ext *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClaimableBalanceEntryExtensionV1Ext(
    XDR *, stellarxdr_ClaimableBalanceEntryExtensionV1Ext *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimableBalanceEntryExtensionV1Ext();
#endif /* Old Style C */

struct stellarxdr_ClaimableBalanceEntryExtensionV1 {
  stellarxdr_ClaimableBalanceEntryExtensionV1Ext ext;
  stellarxdr_uint32 flags;
};
typedef struct stellarxdr_ClaimableBalanceEntryExtensionV1
    stellarxdr_ClaimableBalanceEntryExtensionV1;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClaimableBalanceEntryExtensionV1(
    XDR *, stellarxdr_ClaimableBalanceEntryExtensionV1 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClaimableBalanceEntryExtensionV1(
    XDR *, stellarxdr_ClaimableBalanceEntryExtensionV1 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimableBalanceEntryExtensionV1();
#endif /* Old Style C */

struct stellarxdr_ClaimableBalanceEntryExt {
  int v;
  union {
    stellarxdr_ClaimableBalanceEntryExtensionV1 v1;
  } stellarxdr_ClaimableBalanceEntryExt_u;
};
typedef struct stellarxdr_ClaimableBalanceEntryExt
    stellarxdr_ClaimableBalanceEntryExt;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ClaimableBalanceEntryExt(XDR *,
                                        stellarxdr_ClaimableBalanceEntryExt *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ClaimableBalanceEntryExt(XDR *,
                                        stellarxdr_ClaimableBalanceEntryExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimableBalanceEntryExt();
#endif /* Old Style C */

struct stellarxdr_ClaimableBalanceEntry {
  stellarxdr_ClaimableBalanceID balanceID;
  struct {
    u_int claimants_len;
    stellarxdr_Claimant *claimants_val;
  } claimants;
  stellarxdr_Asset asset;
  stellarxdr_int64 amount;
  stellarxdr_ClaimableBalanceEntryExt ext;
};
typedef struct stellarxdr_ClaimableBalanceEntry
    stellarxdr_ClaimableBalanceEntry;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ClaimableBalanceEntry(XDR *, stellarxdr_ClaimableBalanceEntry *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ClaimableBalanceEntry(XDR *, stellarxdr_ClaimableBalanceEntry *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimableBalanceEntry();
#endif /* Old Style C */

struct stellarxdr_LiquidityPoolConstantProductParameters {
  stellarxdr_Asset assetA;
  stellarxdr_Asset assetB;
  stellarxdr_int32 fee;
};
typedef struct stellarxdr_LiquidityPoolConstantProductParameters
    stellarxdr_LiquidityPoolConstantProductParameters;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LiquidityPoolConstantProductParameters(
    XDR *, stellarxdr_LiquidityPoolConstantProductParameters *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LiquidityPoolConstantProductParameters(
    XDR *, stellarxdr_LiquidityPoolConstantProductParameters *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LiquidityPoolConstantProductParameters();
#endif /* Old Style C */

struct stellarxdr_LiquidityPoolEntryConstantProduct {
  stellarxdr_LiquidityPoolConstantProductParameters params;
  stellarxdr_int64 reserveA;
  stellarxdr_int64 reserveB;
  stellarxdr_int64 totalPoolShares;
  stellarxdr_int64 poolSharesTrustLineCount;
};
typedef struct stellarxdr_LiquidityPoolEntryConstantProduct
    stellarxdr_LiquidityPoolEntryConstantProduct;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LiquidityPoolEntryConstantProduct(
    XDR *, stellarxdr_LiquidityPoolEntryConstantProduct *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LiquidityPoolEntryConstantProduct(
    XDR *, stellarxdr_LiquidityPoolEntryConstantProduct *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LiquidityPoolEntryConstantProduct();
#endif /* Old Style C */

struct stellarxdr_LiquidityPoolEntryBody {
  stellarxdr_LiquidityPoolType type;
  union {
    stellarxdr_LiquidityPoolEntryConstantProduct constantProduct;
  } stellarxdr_LiquidityPoolEntryBody_u;
};
typedef struct stellarxdr_LiquidityPoolEntryBody
    stellarxdr_LiquidityPoolEntryBody;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LiquidityPoolEntryBody(XDR *,
                                      stellarxdr_LiquidityPoolEntryBody *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_LiquidityPoolEntryBody(XDR *,
                                      stellarxdr_LiquidityPoolEntryBody *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LiquidityPoolEntryBody();
#endif /* Old Style C */

struct stellarxdr_LiquidityPoolEntry {
  stellarxdr_PoolID liquidityPoolID;
  stellarxdr_LiquidityPoolEntryBody body;
};
typedef struct stellarxdr_LiquidityPoolEntry stellarxdr_LiquidityPoolEntry;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LiquidityPoolEntry(XDR *, stellarxdr_LiquidityPoolEntry *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_LiquidityPoolEntry(XDR *, stellarxdr_LiquidityPoolEntry *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LiquidityPoolEntry();
#endif /* Old Style C */

struct stellarxdr_LedgerEntryExtensionV1Ext {
  int v;
  union {
  } stellarxdr_LedgerEntryExtensionV1Ext_u;
};
typedef struct stellarxdr_LedgerEntryExtensionV1Ext
    stellarxdr_LedgerEntryExtensionV1Ext;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerEntryExtensionV1Ext(
    XDR *, stellarxdr_LedgerEntryExtensionV1Ext *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerEntryExtensionV1Ext(
    XDR *, stellarxdr_LedgerEntryExtensionV1Ext *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerEntryExtensionV1Ext();
#endif /* Old Style C */

struct stellarxdr_LedgerEntryExtensionV1 {
  stellarxdr_SponsorshipDescriptor sponsoringID;
  stellarxdr_LedgerEntryExtensionV1Ext ext;
};
typedef struct stellarxdr_LedgerEntryExtensionV1
    stellarxdr_LedgerEntryExtensionV1;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LedgerEntryExtensionV1(XDR *,
                                      stellarxdr_LedgerEntryExtensionV1 *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_LedgerEntryExtensionV1(XDR *,
                                      stellarxdr_LedgerEntryExtensionV1 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerEntryExtensionV1();
#endif /* Old Style C */

struct stellarxdr_LedgerEntryData {
  stellarxdr_LedgerEntryType type;
  union {
    stellarxdr_AccountEntry account;
    stellarxdr_TrustLineEntry trustLine;
    stellarxdr_OfferEntry offer;
    stellarxdr_DataEntry data;
    stellarxdr_ClaimableBalanceEntry claimableBalance;
    stellarxdr_LiquidityPoolEntry liquidityPool;
  } stellarxdr_LedgerEntryData_u;
};
typedef struct stellarxdr_LedgerEntryData stellarxdr_LedgerEntryData;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerEntryData(XDR *,
                                                 stellarxdr_LedgerEntryData *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerEntryData(XDR *,
                                             stellarxdr_LedgerEntryData *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerEntryData();
#endif /* Old Style C */

struct stellarxdr_LedgerEntryExt {
  int v;
  union {
    stellarxdr_LedgerEntryExtensionV1 v1;
  } stellarxdr_LedgerEntryExt_u;
};
typedef struct stellarxdr_LedgerEntryExt stellarxdr_LedgerEntryExt;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerEntryExt(XDR *,
                                                stellarxdr_LedgerEntryExt *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerEntryExt(XDR *, stellarxdr_LedgerEntryExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerEntryExt();
#endif /* Old Style C */

struct stellarxdr_LedgerEntry {
  stellarxdr_uint32 lastModifiedLedgerSeq;
  stellarxdr_LedgerEntryData data;
  stellarxdr_LedgerEntryExt ext;
};
typedef struct stellarxdr_LedgerEntry stellarxdr_LedgerEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerEntry(XDR *, stellarxdr_LedgerEntry *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerEntry(XDR *, stellarxdr_LedgerEntry *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerEntry();
#endif /* Old Style C */

struct stellarxdr_LedgerKeyAccount {
  stellarxdr_AccountID accountID;
};
typedef struct stellarxdr_LedgerKeyAccount stellarxdr_LedgerKeyAccount;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LedgerKeyAccount(XDR *, stellarxdr_LedgerKeyAccount *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerKeyAccount(XDR *,
                                              stellarxdr_LedgerKeyAccount *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerKeyAccount();
#endif /* Old Style C */

struct stellarxdr_LedgerKeyTrustLine {
  stellarxdr_AccountID accountID;
  stellarxdr_TrustLineAsset asset;
};
typedef struct stellarxdr_LedgerKeyTrustLine stellarxdr_LedgerKeyTrustLine;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LedgerKeyTrustLine(XDR *, stellarxdr_LedgerKeyTrustLine *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_LedgerKeyTrustLine(XDR *, stellarxdr_LedgerKeyTrustLine *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerKeyTrustLine();
#endif /* Old Style C */

struct stellarxdr_LedgerKeyOffer {
  stellarxdr_AccountID sellerID;
  stellarxdr_int64 offerID;
};
typedef struct stellarxdr_LedgerKeyOffer stellarxdr_LedgerKeyOffer;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerKeyOffer(XDR *,
                                                stellarxdr_LedgerKeyOffer *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerKeyOffer(XDR *, stellarxdr_LedgerKeyOffer *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerKeyOffer();
#endif /* Old Style C */

struct stellarxdr_LedgerKeyData {
  stellarxdr_AccountID accountID;
  stellarxdr_string64 dataName;
};
typedef struct stellarxdr_LedgerKeyData stellarxdr_LedgerKeyData;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerKeyData(XDR *,
                                               stellarxdr_LedgerKeyData *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerKeyData(XDR *, stellarxdr_LedgerKeyData *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerKeyData();
#endif /* Old Style C */

struct stellarxdr_LedgerKeyClaimableBalance {
  stellarxdr_ClaimableBalanceID balanceID;
};
typedef struct stellarxdr_LedgerKeyClaimableBalance
    stellarxdr_LedgerKeyClaimableBalance;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerKeyClaimableBalance(
    XDR *, stellarxdr_LedgerKeyClaimableBalance *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerKeyClaimableBalance(
    XDR *, stellarxdr_LedgerKeyClaimableBalance *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerKeyClaimableBalance();
#endif /* Old Style C */

struct stellarxdr_LedgerKeyLiquidityPool {
  stellarxdr_PoolID liquidityPoolID;
};
typedef struct stellarxdr_LedgerKeyLiquidityPool
    stellarxdr_LedgerKeyLiquidityPool;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LedgerKeyLiquidityPool(XDR *,
                                      stellarxdr_LedgerKeyLiquidityPool *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_LedgerKeyLiquidityPool(XDR *,
                                      stellarxdr_LedgerKeyLiquidityPool *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerKeyLiquidityPool();
#endif /* Old Style C */

struct stellarxdr_LedgerKey {
  stellarxdr_LedgerEntryType type;
  union {
    stellarxdr_LedgerKeyAccount account;
    stellarxdr_LedgerKeyTrustLine trustLine;
    stellarxdr_LedgerKeyOffer offer;
    stellarxdr_LedgerKeyData data;
    stellarxdr_LedgerKeyClaimableBalance claimableBalance;
    stellarxdr_LedgerKeyLiquidityPool liquidityPool;
  } stellarxdr_LedgerKey_u;
};
typedef struct stellarxdr_LedgerKey stellarxdr_LedgerKey;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerKey(XDR *, stellarxdr_LedgerKey *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerKey(XDR *, stellarxdr_LedgerKey *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerKey();
#endif /* Old Style C */

enum stellarxdr_EnvelopeType {
  stellarxdr_ENVELOPE_TYPE_TX_V0 = 0,
  stellarxdr_ENVELOPE_TYPE_SCP = 1,
  stellarxdr_ENVELOPE_TYPE_TX = 2,
  stellarxdr_ENVELOPE_TYPE_AUTH = 3,
  stellarxdr_ENVELOPE_TYPE_SCPVALUE = 4,
  stellarxdr_ENVELOPE_TYPE_TX_FEE_BUMP = 5,
  stellarxdr_ENVELOPE_TYPE_OP_ID = 6,
};
typedef enum stellarxdr_EnvelopeType stellarxdr_EnvelopeType;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_EnvelopeType(XDR *, stellarxdr_EnvelopeType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_EnvelopeType(XDR *, stellarxdr_EnvelopeType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_EnvelopeType();
#endif /* Old Style C */

struct stellarxdr_LiquidityPoolParameters {
  stellarxdr_LiquidityPoolType type;
  union {
    stellarxdr_LiquidityPoolConstantProductParameters constantProduct;
  } stellarxdr_LiquidityPoolParameters_u;
};
typedef struct stellarxdr_LiquidityPoolParameters
    stellarxdr_LiquidityPoolParameters;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LiquidityPoolParameters(XDR *,
                                       stellarxdr_LiquidityPoolParameters *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_LiquidityPoolParameters(XDR *,
                                       stellarxdr_LiquidityPoolParameters *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LiquidityPoolParameters();
#endif /* Old Style C */

struct stellarxdr_MuxedAccountMed25519 {
  stellarxdr_uint64 id;
  stellarxdr_uint256 ed25519;
};
typedef struct stellarxdr_MuxedAccountMed25519 stellarxdr_MuxedAccountMed25519;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_MuxedAccountMed25519(XDR *, stellarxdr_MuxedAccountMed25519 *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_MuxedAccountMed25519(XDR *, stellarxdr_MuxedAccountMed25519 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_MuxedAccountMed25519();
#endif /* Old Style C */

struct stellarxdr_MuxedAccount {
  stellarxdr_CryptoKeyType type;
  union {
    stellarxdr_uint256 ed25519;
    stellarxdr_MuxedAccountMed25519 med25519;
  } stellarxdr_MuxedAccount_u;
};
typedef struct stellarxdr_MuxedAccount stellarxdr_MuxedAccount;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_MuxedAccount(XDR *, stellarxdr_MuxedAccount *);
#elif __STDC__
extern bool_t xdr_stellarxdr_MuxedAccount(XDR *, stellarxdr_MuxedAccount *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_MuxedAccount();
#endif /* Old Style C */

struct stellarxdr_DecoratedSignature {
  stellarxdr_SignatureHint hint;
  stellarxdr_Signature signature;
};
typedef struct stellarxdr_DecoratedSignature stellarxdr_DecoratedSignature;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_DecoratedSignature(XDR *, stellarxdr_DecoratedSignature *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_DecoratedSignature(XDR *, stellarxdr_DecoratedSignature *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_DecoratedSignature();
#endif /* Old Style C */

enum stellarxdr_OperationType {
  stellarxdr_CREATE_ACCOUNT = 0,
  stellarxdr_PAYMENT = 1,
  stellarxdr_PATH_PAYMENT_STRICT_RECEIVE = 2,
  stellarxdr_MANAGE_SELL_OFFER = 3,
  stellarxdr_CREATE_PASSIVE_SELL_OFFER = 4,
  stellarxdr_SET_OPTIONS = 5,
  stellarxdr_CHANGE_TRUST = 6,
  stellarxdr_ALLOW_TRUST = 7,
  stellarxdr_ACCOUNT_MERGE = 8,
  stellarxdr_INFLATION = 9,
  stellarxdr_MANAGE_DATA = 10,
  stellarxdr_BUMP_SEQUENCE = 11,
  stellarxdr_MANAGE_BUY_OFFER = 12,
  stellarxdr_PATH_PAYMENT_STRICT_SEND = 13,
  stellarxdr_CREATE_CLAIMABLE_BALANCE = 14,
  stellarxdr_CLAIM_CLAIMABLE_BALANCE = 15,
  stellarxdr_BEGIN_SPONSORING_FUTURE_RESERVES = 16,
  stellarxdr_END_SPONSORING_FUTURE_RESERVES = 17,
  stellarxdr_REVOKE_SPONSORSHIP = 18,
  stellarxdr_CLAWBACK = 19,
  stellarxdr_CLAWBACK_CLAIMABLE_BALANCE = 20,
  stellarxdr_SET_TRUST_LINE_FLAGS = 21,
  stellarxdr_LIQUIDITY_POOL_DEPOSIT = 22,
  stellarxdr_LIQUIDITY_POOL_WITHDRAW = 23,
};
typedef enum stellarxdr_OperationType stellarxdr_OperationType;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_OperationType(XDR *,
                                               stellarxdr_OperationType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_OperationType(XDR *, stellarxdr_OperationType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_OperationType();
#endif /* Old Style C */

struct stellarxdr_CreateAccountOp {
  stellarxdr_AccountID destination;
  stellarxdr_int64 startingBalance;
};
typedef struct stellarxdr_CreateAccountOp stellarxdr_CreateAccountOp;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_CreateAccountOp(XDR *,
                                                 stellarxdr_CreateAccountOp *);
#elif __STDC__
extern bool_t xdr_stellarxdr_CreateAccountOp(XDR *,
                                             stellarxdr_CreateAccountOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_CreateAccountOp();
#endif /* Old Style C */

struct stellarxdr_PaymentOp {
  stellarxdr_MuxedAccount destination;
  stellarxdr_Asset asset;
  stellarxdr_int64 amount;
};
typedef struct stellarxdr_PaymentOp stellarxdr_PaymentOp;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PaymentOp(XDR *, stellarxdr_PaymentOp *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PaymentOp(XDR *, stellarxdr_PaymentOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PaymentOp();
#endif /* Old Style C */

struct stellarxdr_PathPaymentStrictReceiveOp {
  stellarxdr_Asset sendAsset;
  stellarxdr_int64 sendMax;
  stellarxdr_MuxedAccount destination;
  stellarxdr_Asset destAsset;
  stellarxdr_int64 destAmount;
  struct {
    u_int path_len;
    stellarxdr_Asset *path_val;
  } path;
};
typedef struct stellarxdr_PathPaymentStrictReceiveOp
    stellarxdr_PathPaymentStrictReceiveOp;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PathPaymentStrictReceiveOp(
    XDR *, stellarxdr_PathPaymentStrictReceiveOp *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PathPaymentStrictReceiveOp(
    XDR *, stellarxdr_PathPaymentStrictReceiveOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PathPaymentStrictReceiveOp();
#endif /* Old Style C */

struct stellarxdr_PathPaymentStrictSendOp {
  stellarxdr_Asset sendAsset;
  stellarxdr_int64 sendAmount;
  stellarxdr_MuxedAccount destination;
  stellarxdr_Asset destAsset;
  stellarxdr_int64 destMin;
  struct {
    u_int path_len;
    stellarxdr_Asset *path_val;
  } path;
};
typedef struct stellarxdr_PathPaymentStrictSendOp
    stellarxdr_PathPaymentStrictSendOp;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_PathPaymentStrictSendOp(XDR *,
                                       stellarxdr_PathPaymentStrictSendOp *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_PathPaymentStrictSendOp(XDR *,
                                       stellarxdr_PathPaymentStrictSendOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PathPaymentStrictSendOp();
#endif /* Old Style C */

struct stellarxdr_ManageSellOfferOp {
  stellarxdr_Asset selling;
  stellarxdr_Asset buying;
  stellarxdr_int64 amount;
  stellarxdr_Price price;
  stellarxdr_int64 offerID;
};
typedef struct stellarxdr_ManageSellOfferOp stellarxdr_ManageSellOfferOp;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ManageSellOfferOp(XDR *, stellarxdr_ManageSellOfferOp *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ManageSellOfferOp(XDR *,
                                               stellarxdr_ManageSellOfferOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ManageSellOfferOp();
#endif /* Old Style C */

struct stellarxdr_ManageBuyOfferOp {
  stellarxdr_Asset selling;
  stellarxdr_Asset buying;
  stellarxdr_int64 buyAmount;
  stellarxdr_Price price;
  stellarxdr_int64 offerID;
};
typedef struct stellarxdr_ManageBuyOfferOp stellarxdr_ManageBuyOfferOp;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ManageBuyOfferOp(XDR *, stellarxdr_ManageBuyOfferOp *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ManageBuyOfferOp(XDR *,
                                              stellarxdr_ManageBuyOfferOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ManageBuyOfferOp();
#endif /* Old Style C */

struct stellarxdr_CreatePassiveSellOfferOp {
  stellarxdr_Asset selling;
  stellarxdr_Asset buying;
  stellarxdr_int64 amount;
  stellarxdr_Price price;
};
typedef struct stellarxdr_CreatePassiveSellOfferOp
    stellarxdr_CreatePassiveSellOfferOp;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_CreatePassiveSellOfferOp(XDR *,
                                        stellarxdr_CreatePassiveSellOfferOp *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_CreatePassiveSellOfferOp(XDR *,
                                        stellarxdr_CreatePassiveSellOfferOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_CreatePassiveSellOfferOp();
#endif /* Old Style C */

struct stellarxdr_SetOptionsOp {
  stellarxdr_AccountID *inflationDest;
  stellarxdr_uint32 *clearFlags;
  stellarxdr_uint32 *setFlags;
  stellarxdr_uint32 *masterWeight;
  stellarxdr_uint32 *lowThreshold;
  stellarxdr_uint32 *medThreshold;
  stellarxdr_uint32 *highThreshold;
  stellarxdr_string32 *homeDomain;
  stellarxdr_Signer *signer;
};
typedef struct stellarxdr_SetOptionsOp stellarxdr_SetOptionsOp;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SetOptionsOp(XDR *, stellarxdr_SetOptionsOp *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SetOptionsOp(XDR *, stellarxdr_SetOptionsOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SetOptionsOp();
#endif /* Old Style C */

struct stellarxdr_ChangeTrustAsset {
  stellarxdr_AssetType type;
  union {
    stellarxdr_AlphaNum4 alphaNum4;
    stellarxdr_AlphaNum12 alphaNum12;
    stellarxdr_LiquidityPoolParameters liquidityPool;
  } stellarxdr_ChangeTrustAsset_u;
};
typedef struct stellarxdr_ChangeTrustAsset stellarxdr_ChangeTrustAsset;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ChangeTrustAsset(XDR *, stellarxdr_ChangeTrustAsset *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ChangeTrustAsset(XDR *,
                                              stellarxdr_ChangeTrustAsset *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ChangeTrustAsset();
#endif /* Old Style C */

struct stellarxdr_ChangeTrustOp {
  stellarxdr_ChangeTrustAsset line;
  stellarxdr_int64 limit;
};
typedef struct stellarxdr_ChangeTrustOp stellarxdr_ChangeTrustOp;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ChangeTrustOp(XDR *,
                                               stellarxdr_ChangeTrustOp *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ChangeTrustOp(XDR *, stellarxdr_ChangeTrustOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ChangeTrustOp();
#endif /* Old Style C */

struct stellarxdr_AllowTrustOp {
  stellarxdr_AccountID trustor;
  stellarxdr_AssetCode asset;
  stellarxdr_uint32 authorize;
};
typedef struct stellarxdr_AllowTrustOp stellarxdr_AllowTrustOp;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_AllowTrustOp(XDR *, stellarxdr_AllowTrustOp *);
#elif __STDC__
extern bool_t xdr_stellarxdr_AllowTrustOp(XDR *, stellarxdr_AllowTrustOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AllowTrustOp();
#endif /* Old Style C */

struct stellarxdr_ManageDataOp {
  stellarxdr_string64 dataName;
  stellarxdr_DataValue *dataValue;
};
typedef struct stellarxdr_ManageDataOp stellarxdr_ManageDataOp;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ManageDataOp(XDR *, stellarxdr_ManageDataOp *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ManageDataOp(XDR *, stellarxdr_ManageDataOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ManageDataOp();
#endif /* Old Style C */

struct stellarxdr_BumpSequenceOp {
  stellarxdr_SequenceNumber bumpTo;
};
typedef struct stellarxdr_BumpSequenceOp stellarxdr_BumpSequenceOp;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_BumpSequenceOp(XDR *,
                                                stellarxdr_BumpSequenceOp *);
#elif __STDC__
extern bool_t xdr_stellarxdr_BumpSequenceOp(XDR *, stellarxdr_BumpSequenceOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_BumpSequenceOp();
#endif /* Old Style C */

struct stellarxdr_CreateClaimableBalanceOp {
  stellarxdr_Asset asset;
  stellarxdr_int64 amount;
  struct {
    u_int claimants_len;
    stellarxdr_Claimant *claimants_val;
  } claimants;
};
typedef struct stellarxdr_CreateClaimableBalanceOp
    stellarxdr_CreateClaimableBalanceOp;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_CreateClaimableBalanceOp(XDR *,
                                        stellarxdr_CreateClaimableBalanceOp *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_CreateClaimableBalanceOp(XDR *,
                                        stellarxdr_CreateClaimableBalanceOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_CreateClaimableBalanceOp();
#endif /* Old Style C */

struct stellarxdr_ClaimClaimableBalanceOp {
  stellarxdr_ClaimableBalanceID balanceID;
};
typedef struct stellarxdr_ClaimClaimableBalanceOp
    stellarxdr_ClaimClaimableBalanceOp;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ClaimClaimableBalanceOp(XDR *,
                                       stellarxdr_ClaimClaimableBalanceOp *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ClaimClaimableBalanceOp(XDR *,
                                       stellarxdr_ClaimClaimableBalanceOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimClaimableBalanceOp();
#endif /* Old Style C */

struct stellarxdr_BeginSponsoringFutureReservesOp {
  stellarxdr_AccountID sponsoredID;
};
typedef struct stellarxdr_BeginSponsoringFutureReservesOp
    stellarxdr_BeginSponsoringFutureReservesOp;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_BeginSponsoringFutureReservesOp(
    XDR *, stellarxdr_BeginSponsoringFutureReservesOp *);
#elif __STDC__
extern bool_t xdr_stellarxdr_BeginSponsoringFutureReservesOp(
    XDR *, stellarxdr_BeginSponsoringFutureReservesOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_BeginSponsoringFutureReservesOp();
#endif /* Old Style C */

enum stellarxdr_RevokeSponsorshipType {
  stellarxdr_REVOKE_SPONSORSHIP_LEDGER_ENTRY = 0,
  stellarxdr_REVOKE_SPONSORSHIP_SIGNER = 1,
};
typedef enum stellarxdr_RevokeSponsorshipType stellarxdr_RevokeSponsorshipType;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_RevokeSponsorshipType(XDR *, stellarxdr_RevokeSponsorshipType *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_RevokeSponsorshipType(XDR *, stellarxdr_RevokeSponsorshipType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_RevokeSponsorshipType();
#endif /* Old Style C */

struct stellarxdr_RevokeSponsorshipOpSigner {
  stellarxdr_AccountID accountID;
  stellarxdr_SignerKey signerKey;
};
typedef struct stellarxdr_RevokeSponsorshipOpSigner
    stellarxdr_RevokeSponsorshipOpSigner;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_RevokeSponsorshipOpSigner(
    XDR *, stellarxdr_RevokeSponsorshipOpSigner *);
#elif __STDC__
extern bool_t xdr_stellarxdr_RevokeSponsorshipOpSigner(
    XDR *, stellarxdr_RevokeSponsorshipOpSigner *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_RevokeSponsorshipOpSigner();
#endif /* Old Style C */

struct stellarxdr_RevokeSponsorshipOp {
  stellarxdr_RevokeSponsorshipType type;
  union {
    stellarxdr_LedgerKey ledgerKey;
    stellarxdr_RevokeSponsorshipOpSigner signer;
  } stellarxdr_RevokeSponsorshipOp_u;
};
typedef struct stellarxdr_RevokeSponsorshipOp stellarxdr_RevokeSponsorshipOp;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_RevokeSponsorshipOp(XDR *, stellarxdr_RevokeSponsorshipOp *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_RevokeSponsorshipOp(XDR *, stellarxdr_RevokeSponsorshipOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_RevokeSponsorshipOp();
#endif /* Old Style C */

struct stellarxdr_ClawbackOp {
  stellarxdr_Asset asset;
  stellarxdr_MuxedAccount from;
  stellarxdr_int64 amount;
};
typedef struct stellarxdr_ClawbackOp stellarxdr_ClawbackOp;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClawbackOp(XDR *, stellarxdr_ClawbackOp *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClawbackOp(XDR *, stellarxdr_ClawbackOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClawbackOp();
#endif /* Old Style C */

struct stellarxdr_ClawbackClaimableBalanceOp {
  stellarxdr_ClaimableBalanceID balanceID;
};
typedef struct stellarxdr_ClawbackClaimableBalanceOp
    stellarxdr_ClawbackClaimableBalanceOp;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClawbackClaimableBalanceOp(
    XDR *, stellarxdr_ClawbackClaimableBalanceOp *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClawbackClaimableBalanceOp(
    XDR *, stellarxdr_ClawbackClaimableBalanceOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClawbackClaimableBalanceOp();
#endif /* Old Style C */

struct stellarxdr_SetTrustLineFlagsOp {
  stellarxdr_AccountID trustor;
  stellarxdr_Asset asset;
  stellarxdr_uint32 clearFlags;
  stellarxdr_uint32 setFlags;
};
typedef struct stellarxdr_SetTrustLineFlagsOp stellarxdr_SetTrustLineFlagsOp;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_SetTrustLineFlagsOp(XDR *, stellarxdr_SetTrustLineFlagsOp *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_SetTrustLineFlagsOp(XDR *, stellarxdr_SetTrustLineFlagsOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SetTrustLineFlagsOp();
#endif /* Old Style C */

#define LIQUIDITY_POOL_FEE_V18 30

struct stellarxdr_LiquidityPoolDepositOp {
  stellarxdr_PoolID liquidityPoolID;
  stellarxdr_int64 maxAmountA;
  stellarxdr_int64 maxAmountB;
  stellarxdr_Price minPrice;
  stellarxdr_Price maxPrice;
};
typedef struct stellarxdr_LiquidityPoolDepositOp
    stellarxdr_LiquidityPoolDepositOp;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LiquidityPoolDepositOp(XDR *,
                                      stellarxdr_LiquidityPoolDepositOp *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_LiquidityPoolDepositOp(XDR *,
                                      stellarxdr_LiquidityPoolDepositOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LiquidityPoolDepositOp();
#endif /* Old Style C */

struct stellarxdr_LiquidityPoolWithdrawOp {
  stellarxdr_PoolID liquidityPoolID;
  stellarxdr_int64 amount;
  stellarxdr_int64 minAmountA;
  stellarxdr_int64 minAmountB;
};
typedef struct stellarxdr_LiquidityPoolWithdrawOp
    stellarxdr_LiquidityPoolWithdrawOp;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LiquidityPoolWithdrawOp(XDR *,
                                       stellarxdr_LiquidityPoolWithdrawOp *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_LiquidityPoolWithdrawOp(XDR *,
                                       stellarxdr_LiquidityPoolWithdrawOp *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LiquidityPoolWithdrawOp();
#endif /* Old Style C */

struct stellarxdr_OperationBody {
  stellarxdr_OperationType type;
  union {
    stellarxdr_CreateAccountOp createAccountOp;
    stellarxdr_PaymentOp paymentOp;
    stellarxdr_PathPaymentStrictReceiveOp pathPaymentStrictReceiveOp;
    stellarxdr_ManageSellOfferOp manageSellOfferOp;
    stellarxdr_CreatePassiveSellOfferOp createPassiveSellOfferOp;
    stellarxdr_SetOptionsOp setOptionsOp;
    stellarxdr_ChangeTrustOp changeTrustOp;
    stellarxdr_AllowTrustOp allowTrustOp;
    stellarxdr_MuxedAccount destination;
    stellarxdr_ManageDataOp manageDataOp;
    stellarxdr_BumpSequenceOp bumpSequenceOp;
    stellarxdr_ManageBuyOfferOp manageBuyOfferOp;
    stellarxdr_PathPaymentStrictSendOp pathPaymentStrictSendOp;
    stellarxdr_CreateClaimableBalanceOp createClaimableBalanceOp;
    stellarxdr_ClaimClaimableBalanceOp claimClaimableBalanceOp;
    stellarxdr_BeginSponsoringFutureReservesOp beginSponsoringFutureReservesOp;
    stellarxdr_RevokeSponsorshipOp revokeSponsorshipOp;
    stellarxdr_ClawbackOp clawbackOp;
    stellarxdr_ClawbackClaimableBalanceOp clawbackClaimableBalanceOp;
    stellarxdr_SetTrustLineFlagsOp setTrustLineFlagsOp;
    stellarxdr_LiquidityPoolDepositOp liquidityPoolDepositOp;
    stellarxdr_LiquidityPoolWithdrawOp liquidityPoolWithdrawOp;
  } stellarxdr_OperationBody_u;
};
typedef struct stellarxdr_OperationBody stellarxdr_OperationBody;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_OperationBody(XDR *,
                                               stellarxdr_OperationBody *);
#elif __STDC__
extern bool_t xdr_stellarxdr_OperationBody(XDR *, stellarxdr_OperationBody *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_OperationBody();
#endif /* Old Style C */

struct stellarxdr_Operation {
  stellarxdr_MuxedAccount *sourceAccount;
  stellarxdr_OperationBody body;
};
typedef struct stellarxdr_Operation stellarxdr_Operation;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Operation(XDR *, stellarxdr_Operation *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Operation(XDR *, stellarxdr_Operation *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Operation();
#endif /* Old Style C */

struct stellarxdr_EnvelopeTypeOperationID {
  stellarxdr_AccountID sourceAccount;
  stellarxdr_SequenceNumber seqNum;
  stellarxdr_uint32 opNum;
};
typedef struct stellarxdr_EnvelopeTypeOperationID
    stellarxdr_EnvelopeTypeOperationID;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_EnvelopeTypeOperationID(XDR *,
                                       stellarxdr_EnvelopeTypeOperationID *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_EnvelopeTypeOperationID(XDR *,
                                       stellarxdr_EnvelopeTypeOperationID *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_EnvelopeTypeOperationID();
#endif /* Old Style C */

struct stellarxdr_OperationID {
  stellarxdr_EnvelopeType type;
  union {
    stellarxdr_EnvelopeTypeOperationID id;
  } stellarxdr_OperationID_u;
};
typedef struct stellarxdr_OperationID stellarxdr_OperationID;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_OperationID(XDR *, stellarxdr_OperationID *);
#elif __STDC__
extern bool_t xdr_stellarxdr_OperationID(XDR *, stellarxdr_OperationID *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_OperationID();
#endif /* Old Style C */

enum stellarxdr_MemoType {
  stellarxdr_MEMO_NONE = 0,
  stellarxdr_MEMO_TEXT = 1,
  stellarxdr_MEMO_ID = 2,
  stellarxdr_MEMO_HASH = 3,
  stellarxdr_MEMO_RETURN = 4,
};
typedef enum stellarxdr_MemoType stellarxdr_MemoType;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_MemoType(XDR *, stellarxdr_MemoType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_MemoType(XDR *, stellarxdr_MemoType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_MemoType();
#endif /* Old Style C */

struct stellarxdr_Memo {
  stellarxdr_MemoType type;
  union {
    char *text;
    stellarxdr_uint64 id;
    stellarxdr_Hash hash;
    stellarxdr_Hash retHash;
  } stellarxdr_Memo_u;
};
typedef struct stellarxdr_Memo stellarxdr_Memo;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Memo(XDR *, stellarxdr_Memo *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Memo(XDR *, stellarxdr_Memo *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Memo();
#endif /* Old Style C */

struct stellarxdr_TimeBounds {
  stellarxdr_TimePoint minTime;
  stellarxdr_TimePoint maxTime;
};
typedef struct stellarxdr_TimeBounds stellarxdr_TimeBounds;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TimeBounds(XDR *, stellarxdr_TimeBounds *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TimeBounds(XDR *, stellarxdr_TimeBounds *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TimeBounds();
#endif /* Old Style C */

#define stellarxdr_MAX_OPS_PER_TX 100

struct stellarxdr_TransactionV0Ext {
  int v;
  union {
  } stellarxdr_TransactionV0Ext_u;
};
typedef struct stellarxdr_TransactionV0Ext stellarxdr_TransactionV0Ext;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TransactionV0Ext(XDR *, stellarxdr_TransactionV0Ext *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TransactionV0Ext(XDR *,
                                              stellarxdr_TransactionV0Ext *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionV0Ext();
#endif /* Old Style C */

struct stellarxdr_TransactionV0 {
  stellarxdr_uint256 sourceAccountEd25519;
  stellarxdr_uint32 fee;
  stellarxdr_SequenceNumber seqNum;
  stellarxdr_TimeBounds *timeBounds;
  stellarxdr_Memo memo;
  struct {
    u_int operations_len;
    stellarxdr_Operation *operations_val;
  } operations;
  stellarxdr_TransactionV0Ext ext;
};
typedef struct stellarxdr_TransactionV0 stellarxdr_TransactionV0;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TransactionV0(XDR *,
                                               stellarxdr_TransactionV0 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TransactionV0(XDR *, stellarxdr_TransactionV0 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionV0();
#endif /* Old Style C */

struct stellarxdr_TransactionV0Envelope {
  stellarxdr_TransactionV0 tx;
  struct {
    u_int signatures_len;
    stellarxdr_DecoratedSignature *signatures_val;
  } signatures;
};
typedef struct stellarxdr_TransactionV0Envelope
    stellarxdr_TransactionV0Envelope;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TransactionV0Envelope(XDR *, stellarxdr_TransactionV0Envelope *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_TransactionV0Envelope(XDR *, stellarxdr_TransactionV0Envelope *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionV0Envelope();
#endif /* Old Style C */

struct stellarxdr_TransactionExt {
  int v;
  union {
  } stellarxdr_TransactionExt_u;
};
typedef struct stellarxdr_TransactionExt stellarxdr_TransactionExt;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TransactionExt(XDR *,
                                                stellarxdr_TransactionExt *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TransactionExt(XDR *, stellarxdr_TransactionExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionExt();
#endif /* Old Style C */

struct stellarxdr_Transaction {
  stellarxdr_MuxedAccount sourceAccount;
  stellarxdr_uint32 fee;
  stellarxdr_SequenceNumber seqNum;
  stellarxdr_TimeBounds *timeBounds;
  stellarxdr_Memo memo;
  struct {
    u_int operations_len;
    stellarxdr_Operation *operations_val;
  } operations;
  stellarxdr_TransactionExt ext;
};
typedef struct stellarxdr_Transaction stellarxdr_Transaction;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Transaction(XDR *, stellarxdr_Transaction *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Transaction(XDR *, stellarxdr_Transaction *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Transaction();
#endif /* Old Style C */

struct stellarxdr_TransactionV1Envelope {
  stellarxdr_Transaction tx;
  struct {
    u_int signatures_len;
    stellarxdr_DecoratedSignature *signatures_val;
  } signatures;
};
typedef struct stellarxdr_TransactionV1Envelope
    stellarxdr_TransactionV1Envelope;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TransactionV1Envelope(XDR *, stellarxdr_TransactionV1Envelope *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_TransactionV1Envelope(XDR *, stellarxdr_TransactionV1Envelope *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionV1Envelope();
#endif /* Old Style C */

struct stellarxdr_FeeBumpTransactionInnerTx {
  stellarxdr_EnvelopeType type;
  union {
    stellarxdr_TransactionV1Envelope v1;
  } stellarxdr_FeeBumpTransactionInnerTx_u;
};
typedef struct stellarxdr_FeeBumpTransactionInnerTx
    stellarxdr_FeeBumpTransactionInnerTx;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_FeeBumpTransactionInnerTx(
    XDR *, stellarxdr_FeeBumpTransactionInnerTx *);
#elif __STDC__
extern bool_t xdr_stellarxdr_FeeBumpTransactionInnerTx(
    XDR *, stellarxdr_FeeBumpTransactionInnerTx *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_FeeBumpTransactionInnerTx();
#endif /* Old Style C */

struct stellarxdr_FeeBumpTransactionExt {
  int v;
  union {
  } stellarxdr_FeeBumpTransactionExt_u;
};
typedef struct stellarxdr_FeeBumpTransactionExt
    stellarxdr_FeeBumpTransactionExt;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_FeeBumpTransactionExt(XDR *, stellarxdr_FeeBumpTransactionExt *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_FeeBumpTransactionExt(XDR *, stellarxdr_FeeBumpTransactionExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_FeeBumpTransactionExt();
#endif /* Old Style C */

struct stellarxdr_FeeBumpTransaction {
  stellarxdr_MuxedAccount feeSource;
  stellarxdr_int64 fee;
  stellarxdr_FeeBumpTransactionInnerTx innerTx;
  stellarxdr_FeeBumpTransactionExt ext;
};
typedef struct stellarxdr_FeeBumpTransaction stellarxdr_FeeBumpTransaction;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_FeeBumpTransaction(XDR *, stellarxdr_FeeBumpTransaction *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_FeeBumpTransaction(XDR *, stellarxdr_FeeBumpTransaction *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_FeeBumpTransaction();
#endif /* Old Style C */

struct stellarxdr_FeeBumpTransactionEnvelope {
  stellarxdr_FeeBumpTransaction tx;
  struct {
    u_int signatures_len;
    stellarxdr_DecoratedSignature *signatures_val;
  } signatures;
};
typedef struct stellarxdr_FeeBumpTransactionEnvelope
    stellarxdr_FeeBumpTransactionEnvelope;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_FeeBumpTransactionEnvelope(
    XDR *, stellarxdr_FeeBumpTransactionEnvelope *);
#elif __STDC__
extern bool_t xdr_stellarxdr_FeeBumpTransactionEnvelope(
    XDR *, stellarxdr_FeeBumpTransactionEnvelope *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_FeeBumpTransactionEnvelope();
#endif /* Old Style C */

struct stellarxdr_TransactionEnvelope {
  stellarxdr_EnvelopeType type;
  union {
    stellarxdr_TransactionV0Envelope v0;
    stellarxdr_TransactionV1Envelope v1;
    stellarxdr_FeeBumpTransactionEnvelope feeBump;
  } stellarxdr_TransactionEnvelope_u;
};
typedef struct stellarxdr_TransactionEnvelope stellarxdr_TransactionEnvelope;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TransactionEnvelope(XDR *, stellarxdr_TransactionEnvelope *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_TransactionEnvelope(XDR *, stellarxdr_TransactionEnvelope *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionEnvelope();
#endif /* Old Style C */

struct stellarxdr_TransactionSignaturePayloadTaggedTransaction {
  stellarxdr_EnvelopeType type;
  union {
    stellarxdr_Transaction tx;
    stellarxdr_FeeBumpTransaction feeBump;
  } stellarxdr_TransactionSignaturePayloadTaggedTransaction_u;
};
typedef struct stellarxdr_TransactionSignaturePayloadTaggedTransaction
    stellarxdr_TransactionSignaturePayloadTaggedTransaction;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TransactionSignaturePayloadTaggedTransaction(
    XDR *, stellarxdr_TransactionSignaturePayloadTaggedTransaction *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TransactionSignaturePayloadTaggedTransaction(
    XDR *, stellarxdr_TransactionSignaturePayloadTaggedTransaction *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionSignaturePayloadTaggedTransaction();
#endif /* Old Style C */

struct stellarxdr_TransactionSignaturePayload {
  stellarxdr_Hash networkId;
  stellarxdr_TransactionSignaturePayloadTaggedTransaction taggedTransaction;
};
typedef struct stellarxdr_TransactionSignaturePayload
    stellarxdr_TransactionSignaturePayload;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TransactionSignaturePayload(
    XDR *, stellarxdr_TransactionSignaturePayload *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TransactionSignaturePayload(
    XDR *, stellarxdr_TransactionSignaturePayload *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionSignaturePayload();
#endif /* Old Style C */

enum stellarxdr_ClaimAtomType {
  stellarxdr_CLAIM_ATOM_TYPE_V0 = 0,
  stellarxdr_CLAIM_ATOM_TYPE_ORDER_BOOK = 1,
  stellarxdr_CLAIM_ATOM_TYPE_LIQUIDITY_POOL = 2,
};
typedef enum stellarxdr_ClaimAtomType stellarxdr_ClaimAtomType;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClaimAtomType(XDR *,
                                               stellarxdr_ClaimAtomType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClaimAtomType(XDR *, stellarxdr_ClaimAtomType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimAtomType();
#endif /* Old Style C */

struct stellarxdr_ClaimOfferAtomV0 {
  stellarxdr_uint256 sellerEd25519;
  stellarxdr_int64 offerID;
  stellarxdr_Asset assetSold;
  stellarxdr_int64 amountSold;
  stellarxdr_Asset assetBought;
  stellarxdr_int64 amountBought;
};
typedef struct stellarxdr_ClaimOfferAtomV0 stellarxdr_ClaimOfferAtomV0;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ClaimOfferAtomV0(XDR *, stellarxdr_ClaimOfferAtomV0 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClaimOfferAtomV0(XDR *,
                                              stellarxdr_ClaimOfferAtomV0 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimOfferAtomV0();
#endif /* Old Style C */

struct stellarxdr_ClaimOfferAtom {
  stellarxdr_AccountID sellerID;
  stellarxdr_int64 offerID;
  stellarxdr_Asset assetSold;
  stellarxdr_int64 amountSold;
  stellarxdr_Asset assetBought;
  stellarxdr_int64 amountBought;
};
typedef struct stellarxdr_ClaimOfferAtom stellarxdr_ClaimOfferAtom;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClaimOfferAtom(XDR *,
                                                stellarxdr_ClaimOfferAtom *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClaimOfferAtom(XDR *, stellarxdr_ClaimOfferAtom *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimOfferAtom();
#endif /* Old Style C */

struct stellarxdr_ClaimLiquidityAtom {
  stellarxdr_PoolID liquidityPoolID;
  stellarxdr_Asset assetSold;
  stellarxdr_int64 amountSold;
  stellarxdr_Asset assetBought;
  stellarxdr_int64 amountBought;
};
typedef struct stellarxdr_ClaimLiquidityAtom stellarxdr_ClaimLiquidityAtom;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ClaimLiquidityAtom(XDR *, stellarxdr_ClaimLiquidityAtom *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ClaimLiquidityAtom(XDR *, stellarxdr_ClaimLiquidityAtom *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimLiquidityAtom();
#endif /* Old Style C */

struct stellarxdr_ClaimAtom {
  stellarxdr_ClaimAtomType type;
  union {
    stellarxdr_ClaimOfferAtomV0 v0;
    stellarxdr_ClaimOfferAtom orderBook;
    stellarxdr_ClaimLiquidityAtom liquidityPool;
  } stellarxdr_ClaimAtom_u;
};
typedef struct stellarxdr_ClaimAtom stellarxdr_ClaimAtom;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClaimAtom(XDR *, stellarxdr_ClaimAtom *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClaimAtom(XDR *, stellarxdr_ClaimAtom *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimAtom();
#endif /* Old Style C */

enum stellarxdr_CreateAccountResultCode {
  stellarxdr_CREATE_ACCOUNT_SUCCESS = 0,
  stellarxdr_CREATE_ACCOUNT_MALFORMED = -1,
  stellarxdr_CREATE_ACCOUNT_UNDERFUNDED = -2,
  stellarxdr_CREATE_ACCOUNT_LOW_RESERVE = -3,
  stellarxdr_CREATE_ACCOUNT_ALREADY_EXIST = -4,
};
typedef enum stellarxdr_CreateAccountResultCode
    stellarxdr_CreateAccountResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_CreateAccountResultCode(XDR *,
                                       stellarxdr_CreateAccountResultCode *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_CreateAccountResultCode(XDR *,
                                       stellarxdr_CreateAccountResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_CreateAccountResultCode();
#endif /* Old Style C */

struct stellarxdr_CreateAccountResult {
  stellarxdr_CreateAccountResultCode code;
  union {
  } stellarxdr_CreateAccountResult_u;
};
typedef struct stellarxdr_CreateAccountResult stellarxdr_CreateAccountResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_CreateAccountResult(XDR *, stellarxdr_CreateAccountResult *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_CreateAccountResult(XDR *, stellarxdr_CreateAccountResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_CreateAccountResult();
#endif /* Old Style C */

enum stellarxdr_PaymentResultCode {
  stellarxdr_PAYMENT_SUCCESS = 0,
  stellarxdr_PAYMENT_MALFORMED = -1,
  stellarxdr_PAYMENT_UNDERFUNDED = -2,
  stellarxdr_PAYMENT_SRC_NO_TRUST = -3,
  stellarxdr_PAYMENT_SRC_NOT_AUTHORIZED = -4,
  stellarxdr_PAYMENT_NO_DESTINATION = -5,
  stellarxdr_PAYMENT_NO_TRUST = -6,
  stellarxdr_PAYMENT_NOT_AUTHORIZED = -7,
  stellarxdr_PAYMENT_LINE_FULL = -8,
  stellarxdr_PAYMENT_NO_ISSUER = -9,
};
typedef enum stellarxdr_PaymentResultCode stellarxdr_PaymentResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_PaymentResultCode(XDR *, stellarxdr_PaymentResultCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PaymentResultCode(XDR *,
                                               stellarxdr_PaymentResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PaymentResultCode();
#endif /* Old Style C */

struct stellarxdr_PaymentResult {
  stellarxdr_PaymentResultCode code;
  union {
  } stellarxdr_PaymentResult_u;
};
typedef struct stellarxdr_PaymentResult stellarxdr_PaymentResult;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PaymentResult(XDR *,
                                               stellarxdr_PaymentResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PaymentResult(XDR *, stellarxdr_PaymentResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PaymentResult();
#endif /* Old Style C */

enum stellarxdr_PathPaymentStrictReceiveResultCode {
  stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_SUCCESS = 0,
  stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_MALFORMED = -1,
  stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_UNDERFUNDED = -2,
  stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_SRC_NO_TRUST = -3,
  stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_SRC_NOT_AUTHORIZED = -4,
  stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_NO_DESTINATION = -5,
  stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_NO_TRUST = -6,
  stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_NOT_AUTHORIZED = -7,
  stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_LINE_FULL = -8,
  stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_NO_ISSUER = -9,
  stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_TOO_FEW_OFFERS = -10,
  stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_OFFER_CROSS_SELF = -11,
  stellarxdr_PATH_PAYMENT_STRICT_RECEIVE_OVER_SENDMAX = -12,
};
typedef enum stellarxdr_PathPaymentStrictReceiveResultCode
    stellarxdr_PathPaymentStrictReceiveResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PathPaymentStrictReceiveResultCode(
    XDR *, stellarxdr_PathPaymentStrictReceiveResultCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PathPaymentStrictReceiveResultCode(
    XDR *, stellarxdr_PathPaymentStrictReceiveResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PathPaymentStrictReceiveResultCode();
#endif /* Old Style C */

struct stellarxdr_SimplePaymentResult {
  stellarxdr_AccountID destination;
  stellarxdr_Asset asset;
  stellarxdr_int64 amount;
};
typedef struct stellarxdr_SimplePaymentResult stellarxdr_SimplePaymentResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_SimplePaymentResult(XDR *, stellarxdr_SimplePaymentResult *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_SimplePaymentResult(XDR *, stellarxdr_SimplePaymentResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SimplePaymentResult();
#endif /* Old Style C */

struct stellarxdr_PathPaymentStrictReceiveResultSuccess {
  struct {
    u_int offers_len;
    stellarxdr_ClaimAtom *offers_val;
  } offers;
  stellarxdr_SimplePaymentResult last;
};
typedef struct stellarxdr_PathPaymentStrictReceiveResultSuccess
    stellarxdr_PathPaymentStrictReceiveResultSuccess;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PathPaymentStrictReceiveResultSuccess(
    XDR *, stellarxdr_PathPaymentStrictReceiveResultSuccess *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PathPaymentStrictReceiveResultSuccess(
    XDR *, stellarxdr_PathPaymentStrictReceiveResultSuccess *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PathPaymentStrictReceiveResultSuccess();
#endif /* Old Style C */

struct stellarxdr_PathPaymentStrictReceiveResult {
  stellarxdr_PathPaymentStrictReceiveResultCode code;
  union {
    stellarxdr_PathPaymentStrictReceiveResultSuccess success;
    stellarxdr_Asset noIssuer;
  } stellarxdr_PathPaymentStrictReceiveResult_u;
};
typedef struct stellarxdr_PathPaymentStrictReceiveResult
    stellarxdr_PathPaymentStrictReceiveResult;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PathPaymentStrictReceiveResult(
    XDR *, stellarxdr_PathPaymentStrictReceiveResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PathPaymentStrictReceiveResult(
    XDR *, stellarxdr_PathPaymentStrictReceiveResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PathPaymentStrictReceiveResult();
#endif /* Old Style C */

enum stellarxdr_PathPaymentStrictSendResultCode {
  stellarxdr_PATH_PAYMENT_STRICT_SEND_SUCCESS = 0,
  stellarxdr_PATH_PAYMENT_STRICT_SEND_MALFORMED = -1,
  stellarxdr_PATH_PAYMENT_STRICT_SEND_UNDERFUNDED = -2,
  stellarxdr_PATH_PAYMENT_STRICT_SEND_SRC_NO_TRUST = -3,
  stellarxdr_PATH_PAYMENT_STRICT_SEND_SRC_NOT_AUTHORIZED = -4,
  stellarxdr_PATH_PAYMENT_STRICT_SEND_NO_DESTINATION = -5,
  stellarxdr_PATH_PAYMENT_STRICT_SEND_NO_TRUST = -6,
  stellarxdr_PATH_PAYMENT_STRICT_SEND_NOT_AUTHORIZED = -7,
  stellarxdr_PATH_PAYMENT_STRICT_SEND_LINE_FULL = -8,
  stellarxdr_PATH_PAYMENT_STRICT_SEND_NO_ISSUER = -9,
  stellarxdr_PATH_PAYMENT_STRICT_SEND_TOO_FEW_OFFERS = -10,
  stellarxdr_PATH_PAYMENT_STRICT_SEND_OFFER_CROSS_SELF = -11,
  stellarxdr_PATH_PAYMENT_STRICT_SEND_UNDER_DESTMIN = -12,
};
typedef enum stellarxdr_PathPaymentStrictSendResultCode
    stellarxdr_PathPaymentStrictSendResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PathPaymentStrictSendResultCode(
    XDR *, stellarxdr_PathPaymentStrictSendResultCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PathPaymentStrictSendResultCode(
    XDR *, stellarxdr_PathPaymentStrictSendResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PathPaymentStrictSendResultCode();
#endif /* Old Style C */

struct stellarxdr_PathPaymentStrictSendResultSuccess {
  struct {
    u_int offers_len;
    stellarxdr_ClaimAtom *offers_val;
  } offers;
  stellarxdr_SimplePaymentResult last;
};
typedef struct stellarxdr_PathPaymentStrictSendResultSuccess
    stellarxdr_PathPaymentStrictSendResultSuccess;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PathPaymentStrictSendResultSuccess(
    XDR *, stellarxdr_PathPaymentStrictSendResultSuccess *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PathPaymentStrictSendResultSuccess(
    XDR *, stellarxdr_PathPaymentStrictSendResultSuccess *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PathPaymentStrictSendResultSuccess();
#endif /* Old Style C */

struct stellarxdr_PathPaymentStrictSendResult {
  stellarxdr_PathPaymentStrictSendResultCode code;
  union {
    stellarxdr_PathPaymentStrictSendResultSuccess success;
    stellarxdr_Asset noIssuer;
  } stellarxdr_PathPaymentStrictSendResult_u;
};
typedef struct stellarxdr_PathPaymentStrictSendResult
    stellarxdr_PathPaymentStrictSendResult;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PathPaymentStrictSendResult(
    XDR *, stellarxdr_PathPaymentStrictSendResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PathPaymentStrictSendResult(
    XDR *, stellarxdr_PathPaymentStrictSendResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PathPaymentStrictSendResult();
#endif /* Old Style C */

enum stellarxdr_ManageSellOfferResultCode {
  stellarxdr_MANAGE_SELL_OFFER_SUCCESS = 0,
  stellarxdr_MANAGE_SELL_OFFER_MALFORMED = -1,
  stellarxdr_MANAGE_SELL_OFFER_SELL_NO_TRUST = -2,
  stellarxdr_MANAGE_SELL_OFFER_BUY_NO_TRUST = -3,
  stellarxdr_MANAGE_SELL_OFFER_SELL_NOT_AUTHORIZED = -4,
  stellarxdr_MANAGE_SELL_OFFER_BUY_NOT_AUTHORIZED = -5,
  stellarxdr_MANAGE_SELL_OFFER_LINE_FULL = -6,
  stellarxdr_MANAGE_SELL_OFFER_UNDERFUNDED = -7,
  stellarxdr_MANAGE_SELL_OFFER_CROSS_SELF = -8,
  stellarxdr_MANAGE_SELL_OFFER_SELL_NO_ISSUER = -9,
  stellarxdr_MANAGE_SELL_OFFER_BUY_NO_ISSUER = -10,
  stellarxdr_MANAGE_SELL_OFFER_NOT_FOUND = -11,
  stellarxdr_MANAGE_SELL_OFFER_LOW_RESERVE = -12,
};
typedef enum stellarxdr_ManageSellOfferResultCode
    stellarxdr_ManageSellOfferResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ManageSellOfferResultCode(
    XDR *, stellarxdr_ManageSellOfferResultCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ManageSellOfferResultCode(
    XDR *, stellarxdr_ManageSellOfferResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ManageSellOfferResultCode();
#endif /* Old Style C */

enum stellarxdr_ManageOfferEffect {
  stellarxdr_MANAGE_OFFER_CREATED = 0,
  stellarxdr_MANAGE_OFFER_UPDATED = 1,
  stellarxdr_MANAGE_OFFER_DELETED = 2,
};
typedef enum stellarxdr_ManageOfferEffect stellarxdr_ManageOfferEffect;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ManageOfferEffect(XDR *, stellarxdr_ManageOfferEffect *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ManageOfferEffect(XDR *,
                                               stellarxdr_ManageOfferEffect *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ManageOfferEffect();
#endif /* Old Style C */

struct stellarxdr_ManageOfferSuccessResultOffer {
  stellarxdr_ManageOfferEffect effect;
  union {
    stellarxdr_OfferEntry offer;
  } stellarxdr_ManageOfferSuccessResultOffer_u;
};
typedef struct stellarxdr_ManageOfferSuccessResultOffer
    stellarxdr_ManageOfferSuccessResultOffer;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ManageOfferSuccessResultOffer(
    XDR *, stellarxdr_ManageOfferSuccessResultOffer *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ManageOfferSuccessResultOffer(
    XDR *, stellarxdr_ManageOfferSuccessResultOffer *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ManageOfferSuccessResultOffer();
#endif /* Old Style C */

struct stellarxdr_ManageOfferSuccessResult {
  struct {
    u_int offersClaimed_len;
    stellarxdr_ClaimAtom *offersClaimed_val;
  } offersClaimed;
  stellarxdr_ManageOfferSuccessResultOffer offer;
};
typedef struct stellarxdr_ManageOfferSuccessResult
    stellarxdr_ManageOfferSuccessResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ManageOfferSuccessResult(XDR *,
                                        stellarxdr_ManageOfferSuccessResult *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ManageOfferSuccessResult(XDR *,
                                        stellarxdr_ManageOfferSuccessResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ManageOfferSuccessResult();
#endif /* Old Style C */

struct stellarxdr_ManageSellOfferResult {
  stellarxdr_ManageSellOfferResultCode code;
  union {
    stellarxdr_ManageOfferSuccessResult success;
  } stellarxdr_ManageSellOfferResult_u;
};
typedef struct stellarxdr_ManageSellOfferResult
    stellarxdr_ManageSellOfferResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ManageSellOfferResult(XDR *, stellarxdr_ManageSellOfferResult *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ManageSellOfferResult(XDR *, stellarxdr_ManageSellOfferResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ManageSellOfferResult();
#endif /* Old Style C */

enum stellarxdr_ManageBuyOfferResultCode {
  stellarxdr_MANAGE_BUY_OFFER_SUCCESS = 0,
  stellarxdr_MANAGE_BUY_OFFER_MALFORMED = -1,
  stellarxdr_MANAGE_BUY_OFFER_SELL_NO_TRUST = -2,
  stellarxdr_MANAGE_BUY_OFFER_BUY_NO_TRUST = -3,
  stellarxdr_MANAGE_BUY_OFFER_SELL_NOT_AUTHORIZED = -4,
  stellarxdr_MANAGE_BUY_OFFER_BUY_NOT_AUTHORIZED = -5,
  stellarxdr_MANAGE_BUY_OFFER_LINE_FULL = -6,
  stellarxdr_MANAGE_BUY_OFFER_UNDERFUNDED = -7,
  stellarxdr_MANAGE_BUY_OFFER_CROSS_SELF = -8,
  stellarxdr_MANAGE_BUY_OFFER_SELL_NO_ISSUER = -9,
  stellarxdr_MANAGE_BUY_OFFER_BUY_NO_ISSUER = -10,
  stellarxdr_MANAGE_BUY_OFFER_NOT_FOUND = -11,
  stellarxdr_MANAGE_BUY_OFFER_LOW_RESERVE = -12,
};
typedef enum stellarxdr_ManageBuyOfferResultCode
    stellarxdr_ManageBuyOfferResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ManageBuyOfferResultCode(XDR *,
                                        stellarxdr_ManageBuyOfferResultCode *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ManageBuyOfferResultCode(XDR *,
                                        stellarxdr_ManageBuyOfferResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ManageBuyOfferResultCode();
#endif /* Old Style C */

struct stellarxdr_ManageBuyOfferResult {
  stellarxdr_ManageBuyOfferResultCode code;
  union {
    stellarxdr_ManageOfferSuccessResult success;
  } stellarxdr_ManageBuyOfferResult_u;
};
typedef struct stellarxdr_ManageBuyOfferResult stellarxdr_ManageBuyOfferResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ManageBuyOfferResult(XDR *, stellarxdr_ManageBuyOfferResult *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ManageBuyOfferResult(XDR *, stellarxdr_ManageBuyOfferResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ManageBuyOfferResult();
#endif /* Old Style C */

enum stellarxdr_SetOptionsResultCode {
  stellarxdr_SET_OPTIONS_SUCCESS = 0,
  stellarxdr_SET_OPTIONS_LOW_RESERVE = -1,
  stellarxdr_SET_OPTIONS_TOO_MANY_SIGNERS = -2,
  stellarxdr_SET_OPTIONS_BAD_FLAGS = -3,
  stellarxdr_SET_OPTIONS_INVALID_INFLATION = -4,
  stellarxdr_SET_OPTIONS_CANT_CHANGE = -5,
  stellarxdr_SET_OPTIONS_UNKNOWN_FLAG = -6,
  stellarxdr_SET_OPTIONS_THRESHOLD_OUT_OF_RANGE = -7,
  stellarxdr_SET_OPTIONS_BAD_SIGNER = -8,
  stellarxdr_SET_OPTIONS_INVALID_HOME_DOMAIN = -9,
  stellarxdr_SET_OPTIONS_AUTH_REVOCABLE_REQUIRED = -10,
};
typedef enum stellarxdr_SetOptionsResultCode stellarxdr_SetOptionsResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_SetOptionsResultCode(XDR *, stellarxdr_SetOptionsResultCode *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_SetOptionsResultCode(XDR *, stellarxdr_SetOptionsResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SetOptionsResultCode();
#endif /* Old Style C */

struct stellarxdr_SetOptionsResult {
  stellarxdr_SetOptionsResultCode code;
  union {
  } stellarxdr_SetOptionsResult_u;
};
typedef struct stellarxdr_SetOptionsResult stellarxdr_SetOptionsResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_SetOptionsResult(XDR *, stellarxdr_SetOptionsResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SetOptionsResult(XDR *,
                                              stellarxdr_SetOptionsResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SetOptionsResult();
#endif /* Old Style C */

enum stellarxdr_ChangeTrustResultCode {
  stellarxdr_CHANGE_TRUST_SUCCESS = 0,
  stellarxdr_CHANGE_TRUST_MALFORMED = -1,
  stellarxdr_CHANGE_TRUST_NO_ISSUER = -2,
  stellarxdr_CHANGE_TRUST_INVALID_LIMIT = -3,
  stellarxdr_CHANGE_TRUST_LOW_RESERVE = -4,
  stellarxdr_CHANGE_TRUST_SELF_NOT_ALLOWED = -5,
  stellarxdr_CHANGE_TRUST_TRUST_LINE_MISSING = -6,
  stellarxdr_CHANGE_TRUST_CANNOT_DELETE = -7,
  stellarxdr_CHANGE_TRUST_NOT_AUTH_MAINTAIN_LIABILITIES = -8,
};
typedef enum stellarxdr_ChangeTrustResultCode stellarxdr_ChangeTrustResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ChangeTrustResultCode(XDR *, stellarxdr_ChangeTrustResultCode *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ChangeTrustResultCode(XDR *, stellarxdr_ChangeTrustResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ChangeTrustResultCode();
#endif /* Old Style C */

struct stellarxdr_ChangeTrustResult {
  stellarxdr_ChangeTrustResultCode code;
  union {
  } stellarxdr_ChangeTrustResult_u;
};
typedef struct stellarxdr_ChangeTrustResult stellarxdr_ChangeTrustResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ChangeTrustResult(XDR *, stellarxdr_ChangeTrustResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ChangeTrustResult(XDR *,
                                               stellarxdr_ChangeTrustResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ChangeTrustResult();
#endif /* Old Style C */

enum stellarxdr_AllowTrustResultCode {
  stellarxdr_ALLOW_TRUST_SUCCESS = 0,
  stellarxdr_ALLOW_TRUST_MALFORMED = -1,
  stellarxdr_ALLOW_TRUST_NO_TRUST_LINE = -2,
  stellarxdr_ALLOW_TRUST_TRUST_NOT_REQUIRED = -3,
  stellarxdr_ALLOW_TRUST_CANT_REVOKE = -4,
  stellarxdr_ALLOW_TRUST_SELF_NOT_ALLOWED = -5,
};
typedef enum stellarxdr_AllowTrustResultCode stellarxdr_AllowTrustResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_AllowTrustResultCode(XDR *, stellarxdr_AllowTrustResultCode *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_AllowTrustResultCode(XDR *, stellarxdr_AllowTrustResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AllowTrustResultCode();
#endif /* Old Style C */

struct stellarxdr_AllowTrustResult {
  stellarxdr_AllowTrustResultCode code;
  union {
  } stellarxdr_AllowTrustResult_u;
};
typedef struct stellarxdr_AllowTrustResult stellarxdr_AllowTrustResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_AllowTrustResult(XDR *, stellarxdr_AllowTrustResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_AllowTrustResult(XDR *,
                                              stellarxdr_AllowTrustResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AllowTrustResult();
#endif /* Old Style C */

enum stellarxdr_AccountMergeResultCode {
  stellarxdr_ACCOUNT_MERGE_SUCCESS = 0,
  stellarxdr_ACCOUNT_MERGE_MALFORMED = -1,
  stellarxdr_ACCOUNT_MERGE_NO_ACCOUNT = -2,
  stellarxdr_ACCOUNT_MERGE_IMMUTABLE_SET = -3,
  stellarxdr_ACCOUNT_MERGE_HAS_SUB_ENTRIES = -4,
  stellarxdr_ACCOUNT_MERGE_SEQNUM_TOO_FAR = -5,
  stellarxdr_ACCOUNT_MERGE_DEST_FULL = -6,
  stellarxdr_ACCOUNT_MERGE_IS_SPONSOR = -7,
};
typedef enum stellarxdr_AccountMergeResultCode
    stellarxdr_AccountMergeResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_AccountMergeResultCode(XDR *,
                                      stellarxdr_AccountMergeResultCode *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_AccountMergeResultCode(XDR *,
                                      stellarxdr_AccountMergeResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AccountMergeResultCode();
#endif /* Old Style C */

struct stellarxdr_AccountMergeResult {
  stellarxdr_AccountMergeResultCode code;
  union {
    stellarxdr_int64 sourceAccountBalance;
  } stellarxdr_AccountMergeResult_u;
};
typedef struct stellarxdr_AccountMergeResult stellarxdr_AccountMergeResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_AccountMergeResult(XDR *, stellarxdr_AccountMergeResult *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_AccountMergeResult(XDR *, stellarxdr_AccountMergeResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AccountMergeResult();
#endif /* Old Style C */

enum stellarxdr_InflationResultCode {
  stellarxdr_INFLATION_SUCCESS = 0,
  stellarxdr_INFLATION_NOT_TIME = -1,
};
typedef enum stellarxdr_InflationResultCode stellarxdr_InflationResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_InflationResultCode(XDR *, stellarxdr_InflationResultCode *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_InflationResultCode(XDR *, stellarxdr_InflationResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_InflationResultCode();
#endif /* Old Style C */

struct stellarxdr_InflationPayout {
  stellarxdr_AccountID destination;
  stellarxdr_int64 amount;
};
typedef struct stellarxdr_InflationPayout stellarxdr_InflationPayout;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_InflationPayout(XDR *,
                                                 stellarxdr_InflationPayout *);
#elif __STDC__
extern bool_t xdr_stellarxdr_InflationPayout(XDR *,
                                             stellarxdr_InflationPayout *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_InflationPayout();
#endif /* Old Style C */

struct stellarxdr_InflationResult {
  stellarxdr_InflationResultCode code;
  union {
    struct {
      u_int payouts_len;
      stellarxdr_InflationPayout *payouts_val;
    } payouts;
  } stellarxdr_InflationResult_u;
};
typedef struct stellarxdr_InflationResult stellarxdr_InflationResult;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_InflationResult(XDR *,
                                                 stellarxdr_InflationResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_InflationResult(XDR *,
                                             stellarxdr_InflationResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_InflationResult();
#endif /* Old Style C */

enum stellarxdr_ManageDataResultCode {
  stellarxdr_MANAGE_DATA_SUCCESS = 0,
  stellarxdr_MANAGE_DATA_NOT_SUPPORTED_YET = -1,
  stellarxdr_MANAGE_DATA_NAME_NOT_FOUND = -2,
  stellarxdr_MANAGE_DATA_LOW_RESERVE = -3,
  stellarxdr_MANAGE_DATA_INVALID_NAME = -4,
};
typedef enum stellarxdr_ManageDataResultCode stellarxdr_ManageDataResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ManageDataResultCode(XDR *, stellarxdr_ManageDataResultCode *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ManageDataResultCode(XDR *, stellarxdr_ManageDataResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ManageDataResultCode();
#endif /* Old Style C */

struct stellarxdr_ManageDataResult {
  stellarxdr_ManageDataResultCode code;
  union {
  } stellarxdr_ManageDataResult_u;
};
typedef struct stellarxdr_ManageDataResult stellarxdr_ManageDataResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ManageDataResult(XDR *, stellarxdr_ManageDataResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ManageDataResult(XDR *,
                                              stellarxdr_ManageDataResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ManageDataResult();
#endif /* Old Style C */

enum stellarxdr_BumpSequenceResultCode {
  stellarxdr_BUMP_SEQUENCE_SUCCESS = 0,
  stellarxdr_BUMP_SEQUENCE_BAD_SEQ = -1,
};
typedef enum stellarxdr_BumpSequenceResultCode
    stellarxdr_BumpSequenceResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_BumpSequenceResultCode(XDR *,
                                      stellarxdr_BumpSequenceResultCode *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_BumpSequenceResultCode(XDR *,
                                      stellarxdr_BumpSequenceResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_BumpSequenceResultCode();
#endif /* Old Style C */

struct stellarxdr_BumpSequenceResult {
  stellarxdr_BumpSequenceResultCode code;
  union {
  } stellarxdr_BumpSequenceResult_u;
};
typedef struct stellarxdr_BumpSequenceResult stellarxdr_BumpSequenceResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_BumpSequenceResult(XDR *, stellarxdr_BumpSequenceResult *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_BumpSequenceResult(XDR *, stellarxdr_BumpSequenceResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_BumpSequenceResult();
#endif /* Old Style C */

enum stellarxdr_CreateClaimableBalanceResultCode {
  stellarxdr_CREATE_CLAIMABLE_BALANCE_SUCCESS = 0,
  stellarxdr_CREATE_CLAIMABLE_BALANCE_MALFORMED = -1,
  stellarxdr_CREATE_CLAIMABLE_BALANCE_LOW_RESERVE = -2,
  stellarxdr_CREATE_CLAIMABLE_BALANCE_NO_TRUST = -3,
  stellarxdr_CREATE_CLAIMABLE_BALANCE_NOT_AUTHORIZED = -4,
  stellarxdr_CREATE_CLAIMABLE_BALANCE_UNDERFUNDED = -5,
};
typedef enum stellarxdr_CreateClaimableBalanceResultCode
    stellarxdr_CreateClaimableBalanceResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_CreateClaimableBalanceResultCode(
    XDR *, stellarxdr_CreateClaimableBalanceResultCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_CreateClaimableBalanceResultCode(
    XDR *, stellarxdr_CreateClaimableBalanceResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_CreateClaimableBalanceResultCode();
#endif /* Old Style C */

struct stellarxdr_CreateClaimableBalanceResult {
  stellarxdr_CreateClaimableBalanceResultCode code;
  union {
    stellarxdr_ClaimableBalanceID balanceID;
  } stellarxdr_CreateClaimableBalanceResult_u;
};
typedef struct stellarxdr_CreateClaimableBalanceResult
    stellarxdr_CreateClaimableBalanceResult;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_CreateClaimableBalanceResult(
    XDR *, stellarxdr_CreateClaimableBalanceResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_CreateClaimableBalanceResult(
    XDR *, stellarxdr_CreateClaimableBalanceResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_CreateClaimableBalanceResult();
#endif /* Old Style C */

enum stellarxdr_ClaimClaimableBalanceResultCode {
  stellarxdr_CLAIM_CLAIMABLE_BALANCE_SUCCESS = 0,
  stellarxdr_CLAIM_CLAIMABLE_BALANCE_DOES_NOT_EXIST = -1,
  stellarxdr_CLAIM_CLAIMABLE_BALANCE_CANNOT_CLAIM = -2,
  stellarxdr_CLAIM_CLAIMABLE_BALANCE_LINE_FULL = -3,
  stellarxdr_CLAIM_CLAIMABLE_BALANCE_NO_TRUST = -4,
  stellarxdr_CLAIM_CLAIMABLE_BALANCE_NOT_AUTHORIZED = -5,
};
typedef enum stellarxdr_ClaimClaimableBalanceResultCode
    stellarxdr_ClaimClaimableBalanceResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClaimClaimableBalanceResultCode(
    XDR *, stellarxdr_ClaimClaimableBalanceResultCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClaimClaimableBalanceResultCode(
    XDR *, stellarxdr_ClaimClaimableBalanceResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimClaimableBalanceResultCode();
#endif /* Old Style C */

struct stellarxdr_ClaimClaimableBalanceResult {
  stellarxdr_ClaimClaimableBalanceResultCode code;
  union {
  } stellarxdr_ClaimClaimableBalanceResult_u;
};
typedef struct stellarxdr_ClaimClaimableBalanceResult
    stellarxdr_ClaimClaimableBalanceResult;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClaimClaimableBalanceResult(
    XDR *, stellarxdr_ClaimClaimableBalanceResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClaimClaimableBalanceResult(
    XDR *, stellarxdr_ClaimClaimableBalanceResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClaimClaimableBalanceResult();
#endif /* Old Style C */

enum stellarxdr_BeginSponsoringFutureReservesResultCode {
  stellarxdr_BEGIN_SPONSORING_FUTURE_RESERVES_SUCCESS = 0,
  stellarxdr_BEGIN_SPONSORING_FUTURE_RESERVES_MALFORMED = -1,
  stellarxdr_BEGIN_SPONSORING_FUTURE_RESERVES_ALREADY_SPONSORED = -2,
  stellarxdr_BEGIN_SPONSORING_FUTURE_RESERVES_RECURSIVE = -3,
};
typedef enum stellarxdr_BeginSponsoringFutureReservesResultCode
    stellarxdr_BeginSponsoringFutureReservesResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_BeginSponsoringFutureReservesResultCode(
    XDR *, stellarxdr_BeginSponsoringFutureReservesResultCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_BeginSponsoringFutureReservesResultCode(
    XDR *, stellarxdr_BeginSponsoringFutureReservesResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_BeginSponsoringFutureReservesResultCode();
#endif /* Old Style C */

struct stellarxdr_BeginSponsoringFutureReservesResult {
  stellarxdr_BeginSponsoringFutureReservesResultCode code;
  union {
  } stellarxdr_BeginSponsoringFutureReservesResult_u;
};
typedef struct stellarxdr_BeginSponsoringFutureReservesResult
    stellarxdr_BeginSponsoringFutureReservesResult;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_BeginSponsoringFutureReservesResult(
    XDR *, stellarxdr_BeginSponsoringFutureReservesResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_BeginSponsoringFutureReservesResult(
    XDR *, stellarxdr_BeginSponsoringFutureReservesResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_BeginSponsoringFutureReservesResult();
#endif /* Old Style C */

enum stellarxdr_EndSponsoringFutureReservesResultCode {
  stellarxdr_END_SPONSORING_FUTURE_RESERVES_SUCCESS = 0,
  stellarxdr_END_SPONSORING_FUTURE_RESERVES_NOT_SPONSORED = -1,
};
typedef enum stellarxdr_EndSponsoringFutureReservesResultCode
    stellarxdr_EndSponsoringFutureReservesResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_EndSponsoringFutureReservesResultCode(
    XDR *, stellarxdr_EndSponsoringFutureReservesResultCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_EndSponsoringFutureReservesResultCode(
    XDR *, stellarxdr_EndSponsoringFutureReservesResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_EndSponsoringFutureReservesResultCode();
#endif /* Old Style C */

struct stellarxdr_EndSponsoringFutureReservesResult {
  stellarxdr_EndSponsoringFutureReservesResultCode code;
  union {
  } stellarxdr_EndSponsoringFutureReservesResult_u;
};
typedef struct stellarxdr_EndSponsoringFutureReservesResult
    stellarxdr_EndSponsoringFutureReservesResult;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_EndSponsoringFutureReservesResult(
    XDR *, stellarxdr_EndSponsoringFutureReservesResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_EndSponsoringFutureReservesResult(
    XDR *, stellarxdr_EndSponsoringFutureReservesResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_EndSponsoringFutureReservesResult();
#endif /* Old Style C */

enum stellarxdr_RevokeSponsorshipResultCode {
  stellarxdr_REVOKE_SPONSORSHIP_SUCCESS = 0,
  stellarxdr_REVOKE_SPONSORSHIP_DOES_NOT_EXIST = -1,
  stellarxdr_REVOKE_SPONSORSHIP_NOT_SPONSOR = -2,
  stellarxdr_REVOKE_SPONSORSHIP_LOW_RESERVE = -3,
  stellarxdr_REVOKE_SPONSORSHIP_ONLY_TRANSFERABLE = -4,
  stellarxdr_REVOKE_SPONSORSHIP_MALFORMED = -5,
};
typedef enum stellarxdr_RevokeSponsorshipResultCode
    stellarxdr_RevokeSponsorshipResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_RevokeSponsorshipResultCode(
    XDR *, stellarxdr_RevokeSponsorshipResultCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_RevokeSponsorshipResultCode(
    XDR *, stellarxdr_RevokeSponsorshipResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_RevokeSponsorshipResultCode();
#endif /* Old Style C */

struct stellarxdr_RevokeSponsorshipResult {
  stellarxdr_RevokeSponsorshipResultCode code;
  union {
  } stellarxdr_RevokeSponsorshipResult_u;
};
typedef struct stellarxdr_RevokeSponsorshipResult
    stellarxdr_RevokeSponsorshipResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_RevokeSponsorshipResult(XDR *,
                                       stellarxdr_RevokeSponsorshipResult *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_RevokeSponsorshipResult(XDR *,
                                       stellarxdr_RevokeSponsorshipResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_RevokeSponsorshipResult();
#endif /* Old Style C */

enum stellarxdr_ClawbackResultCode {
  stellarxdr_CLAWBACK_SUCCESS = 0,
  stellarxdr_CLAWBACK_MALFORMED = -1,
  stellarxdr_CLAWBACK_NOT_CLAWBACK_ENABLED = -2,
  stellarxdr_CLAWBACK_NO_TRUST = -3,
  stellarxdr_CLAWBACK_UNDERFUNDED = -4,
};
typedef enum stellarxdr_ClawbackResultCode stellarxdr_ClawbackResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_ClawbackResultCode(XDR *, stellarxdr_ClawbackResultCode *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_ClawbackResultCode(XDR *, stellarxdr_ClawbackResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClawbackResultCode();
#endif /* Old Style C */

struct stellarxdr_ClawbackResult {
  stellarxdr_ClawbackResultCode code;
  union {
  } stellarxdr_ClawbackResult_u;
};
typedef struct stellarxdr_ClawbackResult stellarxdr_ClawbackResult;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClawbackResult(XDR *,
                                                stellarxdr_ClawbackResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClawbackResult(XDR *, stellarxdr_ClawbackResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClawbackResult();
#endif /* Old Style C */

enum stellarxdr_ClawbackClaimableBalanceResultCode {
  stellarxdr_CLAWBACK_CLAIMABLE_BALANCE_SUCCESS = 0,
  stellarxdr_CLAWBACK_CLAIMABLE_BALANCE_DOES_NOT_EXIST = -1,
  stellarxdr_CLAWBACK_CLAIMABLE_BALANCE_NOT_ISSUER = -2,
  stellarxdr_CLAWBACK_CLAIMABLE_BALANCE_NOT_CLAWBACK_ENABLED = -3,
};
typedef enum stellarxdr_ClawbackClaimableBalanceResultCode
    stellarxdr_ClawbackClaimableBalanceResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClawbackClaimableBalanceResultCode(
    XDR *, stellarxdr_ClawbackClaimableBalanceResultCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClawbackClaimableBalanceResultCode(
    XDR *, stellarxdr_ClawbackClaimableBalanceResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClawbackClaimableBalanceResultCode();
#endif /* Old Style C */

struct stellarxdr_ClawbackClaimableBalanceResult {
  stellarxdr_ClawbackClaimableBalanceResultCode code;
  union {
  } stellarxdr_ClawbackClaimableBalanceResult_u;
};
typedef struct stellarxdr_ClawbackClaimableBalanceResult
    stellarxdr_ClawbackClaimableBalanceResult;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ClawbackClaimableBalanceResult(
    XDR *, stellarxdr_ClawbackClaimableBalanceResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ClawbackClaimableBalanceResult(
    XDR *, stellarxdr_ClawbackClaimableBalanceResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ClawbackClaimableBalanceResult();
#endif /* Old Style C */

enum stellarxdr_SetTrustLineFlagsResultCode {
  stellarxdr_SET_TRUST_LINE_FLAGS_SUCCESS = 0,
  stellarxdr_SET_TRUST_LINE_FLAGS_MALFORMED = -1,
  stellarxdr_SET_TRUST_LINE_FLAGS_NO_TRUST_LINE = -2,
  stellarxdr_SET_TRUST_LINE_FLAGS_CANT_REVOKE = -3,
  stellarxdr_SET_TRUST_LINE_FLAGS_INVALID_STATE = -4,
};
typedef enum stellarxdr_SetTrustLineFlagsResultCode
    stellarxdr_SetTrustLineFlagsResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SetTrustLineFlagsResultCode(
    XDR *, stellarxdr_SetTrustLineFlagsResultCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SetTrustLineFlagsResultCode(
    XDR *, stellarxdr_SetTrustLineFlagsResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SetTrustLineFlagsResultCode();
#endif /* Old Style C */

struct stellarxdr_SetTrustLineFlagsResult {
  stellarxdr_SetTrustLineFlagsResultCode code;
  union {
  } stellarxdr_SetTrustLineFlagsResult_u;
};
typedef struct stellarxdr_SetTrustLineFlagsResult
    stellarxdr_SetTrustLineFlagsResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_SetTrustLineFlagsResult(XDR *,
                                       stellarxdr_SetTrustLineFlagsResult *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_SetTrustLineFlagsResult(XDR *,
                                       stellarxdr_SetTrustLineFlagsResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SetTrustLineFlagsResult();
#endif /* Old Style C */

enum stellarxdr_LiquidityPoolDepositResultCode {
  stellarxdr_LIQUIDITY_POOL_DEPOSIT_SUCCESS = 0,
  stellarxdr_LIQUIDITY_POOL_DEPOSIT_MALFORMED = -1,
  stellarxdr_LIQUIDITY_POOL_DEPOSIT_NO_TRUST = -2,
  stellarxdr_LIQUIDITY_POOL_DEPOSIT_NOT_AUTHORIZED = -3,
  stellarxdr_LIQUIDITY_POOL_DEPOSIT_UNDERFUNDED = -4,
  stellarxdr_LIQUIDITY_POOL_DEPOSIT_LINE_FULL = -5,
  stellarxdr_LIQUIDITY_POOL_DEPOSIT_BAD_PRICE = -6,
  stellarxdr_LIQUIDITY_POOL_DEPOSIT_POOL_FULL = -7,
};
typedef enum stellarxdr_LiquidityPoolDepositResultCode
    stellarxdr_LiquidityPoolDepositResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LiquidityPoolDepositResultCode(
    XDR *, stellarxdr_LiquidityPoolDepositResultCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LiquidityPoolDepositResultCode(
    XDR *, stellarxdr_LiquidityPoolDepositResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LiquidityPoolDepositResultCode();
#endif /* Old Style C */

struct stellarxdr_LiquidityPoolDepositResult {
  stellarxdr_LiquidityPoolDepositResultCode code;
  union {
  } stellarxdr_LiquidityPoolDepositResult_u;
};
typedef struct stellarxdr_LiquidityPoolDepositResult
    stellarxdr_LiquidityPoolDepositResult;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LiquidityPoolDepositResult(
    XDR *, stellarxdr_LiquidityPoolDepositResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LiquidityPoolDepositResult(
    XDR *, stellarxdr_LiquidityPoolDepositResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LiquidityPoolDepositResult();
#endif /* Old Style C */

enum stellarxdr_LiquidityPoolWithdrawResultCode {
  stellarxdr_LIQUIDITY_POOL_WITHDRAW_SUCCESS = 0,
  stellarxdr_LIQUIDITY_POOL_WITHDRAW_MALFORMED = -1,
  stellarxdr_LIQUIDITY_POOL_WITHDRAW_NO_TRUST = -2,
  stellarxdr_LIQUIDITY_POOL_WITHDRAW_UNDERFUNDED = -3,
  stellarxdr_LIQUIDITY_POOL_WITHDRAW_LINE_FULL = -4,
  stellarxdr_LIQUIDITY_POOL_WITHDRAW_UNDER_MINIMUM = -5,
};
typedef enum stellarxdr_LiquidityPoolWithdrawResultCode
    stellarxdr_LiquidityPoolWithdrawResultCode;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LiquidityPoolWithdrawResultCode(
    XDR *, stellarxdr_LiquidityPoolWithdrawResultCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LiquidityPoolWithdrawResultCode(
    XDR *, stellarxdr_LiquidityPoolWithdrawResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LiquidityPoolWithdrawResultCode();
#endif /* Old Style C */

struct stellarxdr_LiquidityPoolWithdrawResult {
  stellarxdr_LiquidityPoolWithdrawResultCode code;
  union {
  } stellarxdr_LiquidityPoolWithdrawResult_u;
};
typedef struct stellarxdr_LiquidityPoolWithdrawResult
    stellarxdr_LiquidityPoolWithdrawResult;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LiquidityPoolWithdrawResult(
    XDR *, stellarxdr_LiquidityPoolWithdrawResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LiquidityPoolWithdrawResult(
    XDR *, stellarxdr_LiquidityPoolWithdrawResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LiquidityPoolWithdrawResult();
#endif /* Old Style C */

enum stellarxdr_OperationResultCode {
  stellarxdr_opINNER = 0,
  stellarxdr_opBAD_AUTH = -1,
  stellarxdr_opNO_ACCOUNT = -2,
  stellarxdr_opNOT_SUPPORTED = -3,
  stellarxdr_opTOO_MANY_SUBENTRIES = -4,
  stellarxdr_opEXCEEDED_WORK_LIMIT = -5,
  stellarxdr_opTOO_MANY_SPONSORING = -6,
};
typedef enum stellarxdr_OperationResultCode stellarxdr_OperationResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_OperationResultCode(XDR *, stellarxdr_OperationResultCode *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_OperationResultCode(XDR *, stellarxdr_OperationResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_OperationResultCode();
#endif /* Old Style C */

struct stellarxdr_OperationResultTr {
  stellarxdr_OperationType type;
  union {
    stellarxdr_CreateAccountResult createAccountResult;
    stellarxdr_PaymentResult paymentResult;
    stellarxdr_PathPaymentStrictReceiveResult pathPaymentStrictReceiveResult;
    stellarxdr_ManageSellOfferResult manageSellOfferResult;
    stellarxdr_ManageSellOfferResult createPassiveSellOfferResult;
    stellarxdr_SetOptionsResult setOptionsResult;
    stellarxdr_ChangeTrustResult changeTrustResult;
    stellarxdr_AllowTrustResult allowTrustResult;
    stellarxdr_AccountMergeResult accountMergeResult;
    stellarxdr_InflationResult inflationResult;
    stellarxdr_ManageDataResult manageDataResult;
    stellarxdr_BumpSequenceResult bumpSeqResult;
    stellarxdr_ManageBuyOfferResult manageBuyOfferResult;
    stellarxdr_PathPaymentStrictSendResult pathPaymentStrictSendResult;
    stellarxdr_CreateClaimableBalanceResult createClaimableBalanceResult;
    stellarxdr_ClaimClaimableBalanceResult claimClaimableBalanceResult;
    stellarxdr_BeginSponsoringFutureReservesResult
        beginSponsoringFutureReservesResult;
    stellarxdr_EndSponsoringFutureReservesResult
        endSponsoringFutureReservesResult;
    stellarxdr_RevokeSponsorshipResult revokeSponsorshipResult;
    stellarxdr_ClawbackResult clawbackResult;
    stellarxdr_ClawbackClaimableBalanceResult clawbackClaimableBalanceResult;
    stellarxdr_SetTrustLineFlagsResult setTrustLineFlagsResult;
    stellarxdr_LiquidityPoolDepositResult liquidityPoolDepositResult;
    stellarxdr_LiquidityPoolWithdrawResult liquidityPoolWithdrawResult;
  } stellarxdr_OperationResultTr_u;
};
typedef struct stellarxdr_OperationResultTr stellarxdr_OperationResultTr;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_OperationResultTr(XDR *, stellarxdr_OperationResultTr *);
#elif __STDC__
extern bool_t xdr_stellarxdr_OperationResultTr(XDR *,
                                               stellarxdr_OperationResultTr *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_OperationResultTr();
#endif /* Old Style C */

struct stellarxdr_OperationResult {
  stellarxdr_OperationResultCode code;
  union {
    stellarxdr_OperationResultTr tr;
  } stellarxdr_OperationResult_u;
};
typedef struct stellarxdr_OperationResult stellarxdr_OperationResult;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_OperationResult(XDR *,
                                                 stellarxdr_OperationResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_OperationResult(XDR *,
                                             stellarxdr_OperationResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_OperationResult();
#endif /* Old Style C */

enum stellarxdr_TransactionResultCode {
  stellarxdr_txFEE_BUMP_INNER_SUCCESS = 1,
  stellarxdr_txSUCCESS = 0,
  stellarxdr_txFAILED = -1,
  stellarxdr_txTOO_EARLY = -2,
  stellarxdr_txTOO_LATE = -3,
  stellarxdr_txMISSING_OPERATION = -4,
  stellarxdr_txBAD_SEQ = -5,
  stellarxdr_txBAD_AUTH = -6,
  stellarxdr_txINSUFFICIENT_BALANCE = -7,
  stellarxdr_txNO_ACCOUNT = -8,
  stellarxdr_txINSUFFICIENT_FEE = -9,
  stellarxdr_txBAD_AUTH_EXTRA = -10,
  stellarxdr_txINTERNAL_ERROR = -11,
  stellarxdr_txNOT_SUPPORTED = -12,
  stellarxdr_txFEE_BUMP_INNER_FAILED = -13,
  stellarxdr_txBAD_SPONSORSHIP = -14,
};
typedef enum stellarxdr_TransactionResultCode stellarxdr_TransactionResultCode;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TransactionResultCode(XDR *, stellarxdr_TransactionResultCode *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_TransactionResultCode(XDR *, stellarxdr_TransactionResultCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionResultCode();
#endif /* Old Style C */

struct stellarxdr_InnerTransactionResultResult {
  stellarxdr_TransactionResultCode code;
  union {
    struct {
      u_int results_len;
      stellarxdr_OperationResult *results_val;
    } results;
  } stellarxdr_InnerTransactionResultResult_u;
};
typedef struct stellarxdr_InnerTransactionResultResult
    stellarxdr_InnerTransactionResultResult;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_InnerTransactionResultResult(
    XDR *, stellarxdr_InnerTransactionResultResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_InnerTransactionResultResult(
    XDR *, stellarxdr_InnerTransactionResultResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_InnerTransactionResultResult();
#endif /* Old Style C */

struct stellarxdr_InnerTransactionResultExt {
  int v;
  union {
  } stellarxdr_InnerTransactionResultExt_u;
};
typedef struct stellarxdr_InnerTransactionResultExt
    stellarxdr_InnerTransactionResultExt;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_InnerTransactionResultExt(
    XDR *, stellarxdr_InnerTransactionResultExt *);
#elif __STDC__
extern bool_t xdr_stellarxdr_InnerTransactionResultExt(
    XDR *, stellarxdr_InnerTransactionResultExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_InnerTransactionResultExt();
#endif /* Old Style C */

struct stellarxdr_InnerTransactionResult {
  stellarxdr_int64 feeCharged;
  stellarxdr_InnerTransactionResultResult result;
  stellarxdr_InnerTransactionResultExt ext;
};
typedef struct stellarxdr_InnerTransactionResult
    stellarxdr_InnerTransactionResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_InnerTransactionResult(XDR *,
                                      stellarxdr_InnerTransactionResult *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_InnerTransactionResult(XDR *,
                                      stellarxdr_InnerTransactionResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_InnerTransactionResult();
#endif /* Old Style C */

struct stellarxdr_InnerTransactionResultPair {
  stellarxdr_Hash transactionHash;
  stellarxdr_InnerTransactionResult result;
};
typedef struct stellarxdr_InnerTransactionResultPair
    stellarxdr_InnerTransactionResultPair;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_InnerTransactionResultPair(
    XDR *, stellarxdr_InnerTransactionResultPair *);
#elif __STDC__
extern bool_t xdr_stellarxdr_InnerTransactionResultPair(
    XDR *, stellarxdr_InnerTransactionResultPair *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_InnerTransactionResultPair();
#endif /* Old Style C */

struct stellarxdr_TransactionResultResult {
  stellarxdr_TransactionResultCode code;
  union {
    stellarxdr_InnerTransactionResultPair innerResultPair;
    struct {
      u_int results_len;
      stellarxdr_OperationResult *results_val;
    } results;
  } stellarxdr_TransactionResultResult_u;
};
typedef struct stellarxdr_TransactionResultResult
    stellarxdr_TransactionResultResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TransactionResultResult(XDR *,
                                       stellarxdr_TransactionResultResult *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_TransactionResultResult(XDR *,
                                       stellarxdr_TransactionResultResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionResultResult();
#endif /* Old Style C */

struct stellarxdr_TransactionResultExt {
  int v;
  union {
  } stellarxdr_TransactionResultExt_u;
};
typedef struct stellarxdr_TransactionResultExt stellarxdr_TransactionResultExt;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TransactionResultExt(XDR *, stellarxdr_TransactionResultExt *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_TransactionResultExt(XDR *, stellarxdr_TransactionResultExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionResultExt();
#endif /* Old Style C */

struct stellarxdr_TransactionResult {
  stellarxdr_int64 feeCharged;
  stellarxdr_TransactionResultResult result;
  stellarxdr_TransactionResultExt ext;
};
typedef struct stellarxdr_TransactionResult stellarxdr_TransactionResult;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TransactionResult(XDR *, stellarxdr_TransactionResult *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TransactionResult(XDR *,
                                               stellarxdr_TransactionResult *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionResult();
#endif /* Old Style C */

typedef struct {
  u_int stellarxdr_UpgradeType_len;
  char *stellarxdr_UpgradeType_val;
} stellarxdr_UpgradeType;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_UpgradeType(XDR *, stellarxdr_UpgradeType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_UpgradeType(XDR *, stellarxdr_UpgradeType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_UpgradeType();
#endif /* Old Style C */

enum stellarxdr_StellarValueType {
  stellarxdr_STELLAR_VALUE_BASIC = 0,
  stellarxdr_STELLAR_VALUE_SIGNED = 1,
};
typedef enum stellarxdr_StellarValueType stellarxdr_StellarValueType;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_StellarValueType(XDR *, stellarxdr_StellarValueType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_StellarValueType(XDR *,
                                              stellarxdr_StellarValueType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_StellarValueType();
#endif /* Old Style C */

struct stellarxdr_LedgerCloseValueSignature {
  stellarxdr_NodeID nodeID;
  stellarxdr_Signature signature;
};
typedef struct stellarxdr_LedgerCloseValueSignature
    stellarxdr_LedgerCloseValueSignature;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerCloseValueSignature(
    XDR *, stellarxdr_LedgerCloseValueSignature *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerCloseValueSignature(
    XDR *, stellarxdr_LedgerCloseValueSignature *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerCloseValueSignature();
#endif /* Old Style C */

struct stellarxdr_StellarValueExt {
  stellarxdr_StellarValueType v;
  union {
    stellarxdr_LedgerCloseValueSignature lcValueSignature;
  } stellarxdr_StellarValueExt_u;
};
typedef struct stellarxdr_StellarValueExt stellarxdr_StellarValueExt;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_StellarValueExt(XDR *,
                                                 stellarxdr_StellarValueExt *);
#elif __STDC__
extern bool_t xdr_stellarxdr_StellarValueExt(XDR *,
                                             stellarxdr_StellarValueExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_StellarValueExt();
#endif /* Old Style C */

struct stellarxdr_StellarValue {
  stellarxdr_Hash txSetHash;
  stellarxdr_TimePoint closeTime;
  struct {
    u_int upgrades_len;
    stellarxdr_UpgradeType *upgrades_val;
  } upgrades;
  stellarxdr_StellarValueExt ext;
};
typedef struct stellarxdr_StellarValue stellarxdr_StellarValue;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_StellarValue(XDR *, stellarxdr_StellarValue *);
#elif __STDC__
extern bool_t xdr_stellarxdr_StellarValue(XDR *, stellarxdr_StellarValue *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_StellarValue();
#endif /* Old Style C */

struct stellarxdr_LedgerHeaderExt {
  int v;
  union {
  } stellarxdr_LedgerHeaderExt_u;
};
typedef struct stellarxdr_LedgerHeaderExt stellarxdr_LedgerHeaderExt;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerHeaderExt(XDR *,
                                                 stellarxdr_LedgerHeaderExt *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerHeaderExt(XDR *,
                                             stellarxdr_LedgerHeaderExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerHeaderExt();
#endif /* Old Style C */

struct stellarxdr_LedgerHeader {
  stellarxdr_uint32 ledgerVersion;
  stellarxdr_Hash previousLedgerHash;
  stellarxdr_StellarValue scpValue;
  stellarxdr_Hash txSetResultHash;
  stellarxdr_Hash bucketListHash;
  stellarxdr_uint32 ledgerSeq;
  stellarxdr_int64 totalCoins;
  stellarxdr_int64 feePool;
  stellarxdr_uint32 inflationSeq;
  stellarxdr_uint64 idPool;
  stellarxdr_uint32 baseFee;
  stellarxdr_uint32 baseReserve;
  stellarxdr_uint32 maxTxSetSize;
  stellarxdr_Hash skipList[4];
  stellarxdr_LedgerHeaderExt ext;
};
typedef struct stellarxdr_LedgerHeader stellarxdr_LedgerHeader;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerHeader(XDR *, stellarxdr_LedgerHeader *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerHeader(XDR *, stellarxdr_LedgerHeader *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerHeader();
#endif /* Old Style C */

enum stellarxdr_LedgerUpgradeType {
  stellarxdr_LEDGER_UPGRADE_VERSION = 1,
  stellarxdr_LEDGER_UPGRADE_BASE_FEE = 2,
  stellarxdr_LEDGER_UPGRADE_MAX_TX_SET_SIZE = 3,
  stellarxdr_LEDGER_UPGRADE_BASE_RESERVE = 4,
};
typedef enum stellarxdr_LedgerUpgradeType stellarxdr_LedgerUpgradeType;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LedgerUpgradeType(XDR *, stellarxdr_LedgerUpgradeType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerUpgradeType(XDR *,
                                               stellarxdr_LedgerUpgradeType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerUpgradeType();
#endif /* Old Style C */

struct stellarxdr_LedgerUpgrade {
  stellarxdr_LedgerUpgradeType type;
  union {
    stellarxdr_uint32 newLedgerVersion;
    stellarxdr_uint32 newBaseFee;
    stellarxdr_uint32 newMaxTxSetSize;
    stellarxdr_uint32 newBaseReserve;
  } stellarxdr_LedgerUpgrade_u;
};
typedef struct stellarxdr_LedgerUpgrade stellarxdr_LedgerUpgrade;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerUpgrade(XDR *,
                                               stellarxdr_LedgerUpgrade *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerUpgrade(XDR *, stellarxdr_LedgerUpgrade *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerUpgrade();
#endif /* Old Style C */

enum stellarxdr_BucketEntryType {
  stellarxdr_METAENTRY = -1,
  stellarxdr_LIVEENTRY = 0,
  stellarxdr_DEADENTRY = 1,
  stellarxdr_INITENTRY = 2,
};
typedef enum stellarxdr_BucketEntryType stellarxdr_BucketEntryType;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_BucketEntryType(XDR *,
                                                 stellarxdr_BucketEntryType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_BucketEntryType(XDR *,
                                             stellarxdr_BucketEntryType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_BucketEntryType();
#endif /* Old Style C */

struct stellarxdr_BucketMetadataExt {
  int v;
  union {
  } stellarxdr_BucketMetadataExt_u;
};
typedef struct stellarxdr_BucketMetadataExt stellarxdr_BucketMetadataExt;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_BucketMetadataExt(XDR *, stellarxdr_BucketMetadataExt *);
#elif __STDC__
extern bool_t xdr_stellarxdr_BucketMetadataExt(XDR *,
                                               stellarxdr_BucketMetadataExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_BucketMetadataExt();
#endif /* Old Style C */

struct stellarxdr_BucketMetadata {
  stellarxdr_uint32 ledgerVersion;
  stellarxdr_BucketMetadataExt ext;
};
typedef struct stellarxdr_BucketMetadata stellarxdr_BucketMetadata;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_BucketMetadata(XDR *,
                                                stellarxdr_BucketMetadata *);
#elif __STDC__
extern bool_t xdr_stellarxdr_BucketMetadata(XDR *, stellarxdr_BucketMetadata *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_BucketMetadata();
#endif /* Old Style C */

struct stellarxdr_BucketEntry {
  stellarxdr_BucketEntryType type;
  union {
    stellarxdr_LedgerEntry liveEntry;
    stellarxdr_LedgerKey deadEntry;
    stellarxdr_BucketMetadata metaEntry;
  } stellarxdr_BucketEntry_u;
};
typedef struct stellarxdr_BucketEntry stellarxdr_BucketEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_BucketEntry(XDR *, stellarxdr_BucketEntry *);
#elif __STDC__
extern bool_t xdr_stellarxdr_BucketEntry(XDR *, stellarxdr_BucketEntry *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_BucketEntry();
#endif /* Old Style C */

struct stellarxdr_TransactionSet {
  stellarxdr_Hash previousLedgerHash;
  struct {
    u_int txs_len;
    stellarxdr_TransactionEnvelope *txs_val;
  } txs;
};
typedef struct stellarxdr_TransactionSet stellarxdr_TransactionSet;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TransactionSet(XDR *,
                                                stellarxdr_TransactionSet *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TransactionSet(XDR *, stellarxdr_TransactionSet *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionSet();
#endif /* Old Style C */

struct stellarxdr_TransactionResultPair {
  stellarxdr_Hash transactionHash;
  stellarxdr_TransactionResult result;
};
typedef struct stellarxdr_TransactionResultPair
    stellarxdr_TransactionResultPair;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TransactionResultPair(XDR *, stellarxdr_TransactionResultPair *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_TransactionResultPair(XDR *, stellarxdr_TransactionResultPair *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionResultPair();
#endif /* Old Style C */

struct stellarxdr_TransactionResultSet {
  struct {
    u_int results_len;
    stellarxdr_TransactionResultPair *results_val;
  } results;
};
typedef struct stellarxdr_TransactionResultSet stellarxdr_TransactionResultSet;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TransactionResultSet(XDR *, stellarxdr_TransactionResultSet *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_TransactionResultSet(XDR *, stellarxdr_TransactionResultSet *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionResultSet();
#endif /* Old Style C */

struct stellarxdr_TransactionHistoryEntryExt {
  int v;
  union {
  } stellarxdr_TransactionHistoryEntryExt_u;
};
typedef struct stellarxdr_TransactionHistoryEntryExt
    stellarxdr_TransactionHistoryEntryExt;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TransactionHistoryEntryExt(
    XDR *, stellarxdr_TransactionHistoryEntryExt *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TransactionHistoryEntryExt(
    XDR *, stellarxdr_TransactionHistoryEntryExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionHistoryEntryExt();
#endif /* Old Style C */

struct stellarxdr_TransactionHistoryEntry {
  stellarxdr_uint32 ledgerSeq;
  stellarxdr_TransactionSet txSet;
  stellarxdr_TransactionHistoryEntryExt ext;
};
typedef struct stellarxdr_TransactionHistoryEntry
    stellarxdr_TransactionHistoryEntry;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TransactionHistoryEntry(XDR *,
                                       stellarxdr_TransactionHistoryEntry *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_TransactionHistoryEntry(XDR *,
                                       stellarxdr_TransactionHistoryEntry *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionHistoryEntry();
#endif /* Old Style C */

struct stellarxdr_TransactionHistoryResultEntryExt {
  int v;
  union {
  } stellarxdr_TransactionHistoryResultEntryExt_u;
};
typedef struct stellarxdr_TransactionHistoryResultEntryExt
    stellarxdr_TransactionHistoryResultEntryExt;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TransactionHistoryResultEntryExt(
    XDR *, stellarxdr_TransactionHistoryResultEntryExt *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TransactionHistoryResultEntryExt(
    XDR *, stellarxdr_TransactionHistoryResultEntryExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionHistoryResultEntryExt();
#endif /* Old Style C */

struct stellarxdr_TransactionHistoryResultEntry {
  stellarxdr_uint32 ledgerSeq;
  stellarxdr_TransactionResultSet txResultSet;
  stellarxdr_TransactionHistoryResultEntryExt ext;
};
typedef struct stellarxdr_TransactionHistoryResultEntry
    stellarxdr_TransactionHistoryResultEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TransactionHistoryResultEntry(
    XDR *, stellarxdr_TransactionHistoryResultEntry *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TransactionHistoryResultEntry(
    XDR *, stellarxdr_TransactionHistoryResultEntry *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionHistoryResultEntry();
#endif /* Old Style C */

struct stellarxdr_LedgerHeaderHistoryEntryExt {
  int v;
  union {
  } stellarxdr_LedgerHeaderHistoryEntryExt_u;
};
typedef struct stellarxdr_LedgerHeaderHistoryEntryExt
    stellarxdr_LedgerHeaderHistoryEntryExt;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerHeaderHistoryEntryExt(
    XDR *, stellarxdr_LedgerHeaderHistoryEntryExt *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerHeaderHistoryEntryExt(
    XDR *, stellarxdr_LedgerHeaderHistoryEntryExt *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerHeaderHistoryEntryExt();
#endif /* Old Style C */

struct stellarxdr_LedgerHeaderHistoryEntry {
  stellarxdr_Hash hash;
  stellarxdr_LedgerHeader header;
  stellarxdr_LedgerHeaderHistoryEntryExt ext;
};
typedef struct stellarxdr_LedgerHeaderHistoryEntry
    stellarxdr_LedgerHeaderHistoryEntry;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LedgerHeaderHistoryEntry(XDR *,
                                        stellarxdr_LedgerHeaderHistoryEntry *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_LedgerHeaderHistoryEntry(XDR *,
                                        stellarxdr_LedgerHeaderHistoryEntry *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerHeaderHistoryEntry();
#endif /* Old Style C */

struct stellarxdr_LedgerSCPMessages {
  stellarxdr_uint32 ledgerSeq;
  struct {
    u_int messages_len;
    stellarxdr_SCPEnvelope *messages_val;
  } messages;
};
typedef struct stellarxdr_LedgerSCPMessages stellarxdr_LedgerSCPMessages;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LedgerSCPMessages(XDR *, stellarxdr_LedgerSCPMessages *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerSCPMessages(XDR *,
                                               stellarxdr_LedgerSCPMessages *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerSCPMessages();
#endif /* Old Style C */

struct stellarxdr_SCPHistoryEntryV0 {
  struct {
    u_int quorumSets_len;
    stellarxdr_SCPQuorumSet *quorumSets_val;
  } quorumSets;
  stellarxdr_LedgerSCPMessages ledgerMessages;
};
typedef struct stellarxdr_SCPHistoryEntryV0 stellarxdr_SCPHistoryEntryV0;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_SCPHistoryEntryV0(XDR *, stellarxdr_SCPHistoryEntryV0 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SCPHistoryEntryV0(XDR *,
                                               stellarxdr_SCPHistoryEntryV0 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SCPHistoryEntryV0();
#endif /* Old Style C */

struct stellarxdr_SCPHistoryEntry {
  int v;
  union {
    stellarxdr_SCPHistoryEntryV0 v0;
  } stellarxdr_SCPHistoryEntry_u;
};
typedef struct stellarxdr_SCPHistoryEntry stellarxdr_SCPHistoryEntry;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SCPHistoryEntry(XDR *,
                                                 stellarxdr_SCPHistoryEntry *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SCPHistoryEntry(XDR *,
                                             stellarxdr_SCPHistoryEntry *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SCPHistoryEntry();
#endif /* Old Style C */

enum stellarxdr_LedgerEntryChangeType {
  stellarxdr_LEDGER_ENTRY_CREATED = 0,
  stellarxdr_LEDGER_ENTRY_UPDATED = 1,
  stellarxdr_LEDGER_ENTRY_REMOVED = 2,
  stellarxdr_LEDGER_ENTRY_STATE = 3,
};
typedef enum stellarxdr_LedgerEntryChangeType stellarxdr_LedgerEntryChangeType;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LedgerEntryChangeType(XDR *, stellarxdr_LedgerEntryChangeType *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_LedgerEntryChangeType(XDR *, stellarxdr_LedgerEntryChangeType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerEntryChangeType();
#endif /* Old Style C */

struct stellarxdr_LedgerEntryChange {
  stellarxdr_LedgerEntryChangeType type;
  union {
    stellarxdr_LedgerEntry created;
    stellarxdr_LedgerEntry updated;
    stellarxdr_LedgerKey removed;
    stellarxdr_LedgerEntry state;
  } stellarxdr_LedgerEntryChange_u;
};
typedef struct stellarxdr_LedgerEntryChange stellarxdr_LedgerEntryChange;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LedgerEntryChange(XDR *, stellarxdr_LedgerEntryChange *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerEntryChange(XDR *,
                                               stellarxdr_LedgerEntryChange *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerEntryChange();
#endif /* Old Style C */

typedef struct {
  u_int stellarxdr_LedgerEntryChanges_len;
  stellarxdr_LedgerEntryChange *stellarxdr_LedgerEntryChanges_val;
} stellarxdr_LedgerEntryChanges;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LedgerEntryChanges(XDR *, stellarxdr_LedgerEntryChanges *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_LedgerEntryChanges(XDR *, stellarxdr_LedgerEntryChanges *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerEntryChanges();
#endif /* Old Style C */

struct stellarxdr_OperationMeta {
  stellarxdr_LedgerEntryChanges changes;
};
typedef struct stellarxdr_OperationMeta stellarxdr_OperationMeta;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_OperationMeta(XDR *,
                                               stellarxdr_OperationMeta *);
#elif __STDC__
extern bool_t xdr_stellarxdr_OperationMeta(XDR *, stellarxdr_OperationMeta *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_OperationMeta();
#endif /* Old Style C */

struct stellarxdr_TransactionMetaV1 {
  stellarxdr_LedgerEntryChanges txChanges;
  struct {
    u_int operations_len;
    stellarxdr_OperationMeta *operations_val;
  } operations;
};
typedef struct stellarxdr_TransactionMetaV1 stellarxdr_TransactionMetaV1;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TransactionMetaV1(XDR *, stellarxdr_TransactionMetaV1 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TransactionMetaV1(XDR *,
                                               stellarxdr_TransactionMetaV1 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionMetaV1();
#endif /* Old Style C */

struct stellarxdr_TransactionMetaV2 {
  stellarxdr_LedgerEntryChanges txChangesBefore;
  struct {
    u_int operations_len;
    stellarxdr_OperationMeta *operations_val;
  } operations;
  stellarxdr_LedgerEntryChanges txChangesAfter;
};
typedef struct stellarxdr_TransactionMetaV2 stellarxdr_TransactionMetaV2;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TransactionMetaV2(XDR *, stellarxdr_TransactionMetaV2 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TransactionMetaV2(XDR *,
                                               stellarxdr_TransactionMetaV2 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionMetaV2();
#endif /* Old Style C */

struct stellarxdr_TransactionMeta {
  int v;
  union {
    struct {
      u_int operations_len;
      stellarxdr_OperationMeta *operations_val;
    } operations;
    stellarxdr_TransactionMetaV1 v1;
    stellarxdr_TransactionMetaV2 v2;
  } stellarxdr_TransactionMeta_u;
};
typedef struct stellarxdr_TransactionMeta stellarxdr_TransactionMeta;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_TransactionMeta(XDR *,
                                                 stellarxdr_TransactionMeta *);
#elif __STDC__
extern bool_t xdr_stellarxdr_TransactionMeta(XDR *,
                                             stellarxdr_TransactionMeta *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionMeta();
#endif /* Old Style C */

struct stellarxdr_TransactionResultMeta {
  stellarxdr_TransactionResultPair result;
  stellarxdr_LedgerEntryChanges feeProcessing;
  stellarxdr_TransactionMeta txApplyProcessing;
};
typedef struct stellarxdr_TransactionResultMeta
    stellarxdr_TransactionResultMeta;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TransactionResultMeta(XDR *, stellarxdr_TransactionResultMeta *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_TransactionResultMeta(XDR *, stellarxdr_TransactionResultMeta *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TransactionResultMeta();
#endif /* Old Style C */

struct stellarxdr_UpgradeEntryMeta {
  stellarxdr_LedgerUpgrade upgrade;
  stellarxdr_LedgerEntryChanges changes;
};
typedef struct stellarxdr_UpgradeEntryMeta stellarxdr_UpgradeEntryMeta;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_UpgradeEntryMeta(XDR *, stellarxdr_UpgradeEntryMeta *);
#elif __STDC__
extern bool_t xdr_stellarxdr_UpgradeEntryMeta(XDR *,
                                              stellarxdr_UpgradeEntryMeta *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_UpgradeEntryMeta();
#endif /* Old Style C */

struct stellarxdr_LedgerCloseMetaV0 {
  stellarxdr_LedgerHeaderHistoryEntry ledgerHeader;
  stellarxdr_TransactionSet txSet;
  struct {
    u_int txProcessing_len;
    stellarxdr_TransactionResultMeta *txProcessing_val;
  } txProcessing;
  struct {
    u_int upgradesProcessing_len;
    stellarxdr_UpgradeEntryMeta *upgradesProcessing_val;
  } upgradesProcessing;
  struct {
    u_int scpInfo_len;
    stellarxdr_SCPHistoryEntry *scpInfo_val;
  } scpInfo;
};
typedef struct stellarxdr_LedgerCloseMetaV0 stellarxdr_LedgerCloseMetaV0;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_LedgerCloseMetaV0(XDR *, stellarxdr_LedgerCloseMetaV0 *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerCloseMetaV0(XDR *,
                                               stellarxdr_LedgerCloseMetaV0 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerCloseMetaV0();
#endif /* Old Style C */

struct stellarxdr_LedgerCloseMeta {
  int v;
  union {
    stellarxdr_LedgerCloseMetaV0 v0;
  } stellarxdr_LedgerCloseMeta_u;
};
typedef struct stellarxdr_LedgerCloseMeta stellarxdr_LedgerCloseMeta;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_LedgerCloseMeta(XDR *,
                                                 stellarxdr_LedgerCloseMeta *);
#elif __STDC__
extern bool_t xdr_stellarxdr_LedgerCloseMeta(XDR *,
                                             stellarxdr_LedgerCloseMeta *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_LedgerCloseMeta();
#endif /* Old Style C */

enum stellarxdr_ErrorCode {
  stellarxdr_ERR_MISC = 0,
  stellarxdr_ERR_DATA = 1,
  stellarxdr_ERR_CONF = 2,
  stellarxdr_ERR_AUTH = 3,
  stellarxdr_ERR_LOAD = 4,
};
typedef enum stellarxdr_ErrorCode stellarxdr_ErrorCode;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_ErrorCode(XDR *, stellarxdr_ErrorCode *);
#elif __STDC__
extern bool_t xdr_stellarxdr_ErrorCode(XDR *, stellarxdr_ErrorCode *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_ErrorCode();
#endif /* Old Style C */

struct stellarxdr_Error {
  stellarxdr_ErrorCode code;
  char *msg;
};
typedef struct stellarxdr_Error stellarxdr_Error;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Error(XDR *, stellarxdr_Error *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Error(XDR *, stellarxdr_Error *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Error();
#endif /* Old Style C */

struct stellarxdr_AuthCert {
  stellarxdr_Curve25519Public pubkey;
  stellarxdr_uint64 expiration;
  stellarxdr_Signature sig;
};
typedef struct stellarxdr_AuthCert stellarxdr_AuthCert;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_AuthCert(XDR *, stellarxdr_AuthCert *);
#elif __STDC__
extern bool_t xdr_stellarxdr_AuthCert(XDR *, stellarxdr_AuthCert *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AuthCert();
#endif /* Old Style C */

struct stellarxdr_Hello {
  stellarxdr_uint32 ledgerVersion;
  stellarxdr_uint32 overlayVersion;
  stellarxdr_uint32 overlayMinVersion;
  stellarxdr_Hash networkID;
  char *versionStr;
  int listeningPort;
  stellarxdr_NodeID peerID;
  stellarxdr_AuthCert cert;
  stellarxdr_uint256 nonce;
};
typedef struct stellarxdr_Hello stellarxdr_Hello;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Hello(XDR *, stellarxdr_Hello *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Hello(XDR *, stellarxdr_Hello *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Hello();
#endif /* Old Style C */

struct stellarxdr_Auth {
  int unused;
};
typedef struct stellarxdr_Auth stellarxdr_Auth;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_Auth(XDR *, stellarxdr_Auth *);
#elif __STDC__
extern bool_t xdr_stellarxdr_Auth(XDR *, stellarxdr_Auth *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_Auth();
#endif /* Old Style C */

enum stellarxdr_IPAddrType {
  stellarxdr_IPv4 = 0,
  stellarxdr_IPv6 = 1,
};
typedef enum stellarxdr_IPAddrType stellarxdr_IPAddrType;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_IPAddrType(XDR *, stellarxdr_IPAddrType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_IPAddrType(XDR *, stellarxdr_IPAddrType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_IPAddrType();
#endif /* Old Style C */

struct stellarxdr_PeerAddressIP {
  stellarxdr_IPAddrType type;
  union {
    char ipv4[4];
    char ipv6[16];
  } stellarxdr_PeerAddressIP_u;
};
typedef struct stellarxdr_PeerAddressIP stellarxdr_PeerAddressIP;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PeerAddressIP(XDR *,
                                               stellarxdr_PeerAddressIP *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PeerAddressIP(XDR *, stellarxdr_PeerAddressIP *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PeerAddressIP();
#endif /* Old Style C */

struct stellarxdr_PeerAddress {
  stellarxdr_PeerAddressIP ip;
  stellarxdr_uint32 port;
  stellarxdr_uint32 numFailures;
};
typedef struct stellarxdr_PeerAddress stellarxdr_PeerAddress;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PeerAddress(XDR *, stellarxdr_PeerAddress *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PeerAddress(XDR *, stellarxdr_PeerAddress *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PeerAddress();
#endif /* Old Style C */

enum stellarxdr_MessageType {
  stellarxdr_ERROR_MSG = 0,
  stellarxdr_AUTH = 2,
  stellarxdr_DONT_HAVE = 3,
  stellarxdr_GET_PEERS = 4,
  stellarxdr_PEERS = 5,
  stellarxdr_GET_TX_SET = 6,
  stellarxdr_TX_SET = 7,
  stellarxdr_TRANSACTION = 8,
  stellarxdr_GET_SCP_QUORUMSET = 9,
  stellarxdr_SCP_QUORUMSET = 10,
  stellarxdr_SCP_MESSAGE = 11,
  stellarxdr_GET_SCP_STATE = 12,
  stellarxdr_HELLO = 13,
  stellarxdr_SURVEY_REQUEST = 14,
  stellarxdr_SURVEY_RESPONSE = 15,
};
typedef enum stellarxdr_MessageType stellarxdr_MessageType;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_MessageType(XDR *, stellarxdr_MessageType *);
#elif __STDC__
extern bool_t xdr_stellarxdr_MessageType(XDR *, stellarxdr_MessageType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_MessageType();
#endif /* Old Style C */

struct stellarxdr_DontHave {
  stellarxdr_MessageType type;
  stellarxdr_uint256 reqHash;
};
typedef struct stellarxdr_DontHave stellarxdr_DontHave;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_DontHave(XDR *, stellarxdr_DontHave *);
#elif __STDC__
extern bool_t xdr_stellarxdr_DontHave(XDR *, stellarxdr_DontHave *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_DontHave();
#endif /* Old Style C */

enum stellarxdr_SurveyMessageCommandType {
  stellarxdr_SURVEY_TOPOLOGY = 0,
};
typedef enum stellarxdr_SurveyMessageCommandType
    stellarxdr_SurveyMessageCommandType;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_SurveyMessageCommandType(XDR *,
                                        stellarxdr_SurveyMessageCommandType *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_SurveyMessageCommandType(XDR *,
                                        stellarxdr_SurveyMessageCommandType *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SurveyMessageCommandType();
#endif /* Old Style C */

struct stellarxdr_SurveyRequestMessage {
  stellarxdr_NodeID surveyorPeerID;
  stellarxdr_NodeID surveyedPeerID;
  stellarxdr_uint32 ledgerNum;
  stellarxdr_Curve25519Public encryptionKey;
  stellarxdr_SurveyMessageCommandType commandType;
};
typedef struct stellarxdr_SurveyRequestMessage stellarxdr_SurveyRequestMessage;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_SurveyRequestMessage(XDR *, stellarxdr_SurveyRequestMessage *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_SurveyRequestMessage(XDR *, stellarxdr_SurveyRequestMessage *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SurveyRequestMessage();
#endif /* Old Style C */

struct stellarxdr_SignedSurveyRequestMessage {
  stellarxdr_Signature requestSignature;
  stellarxdr_SurveyRequestMessage request;
};
typedef struct stellarxdr_SignedSurveyRequestMessage
    stellarxdr_SignedSurveyRequestMessage;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SignedSurveyRequestMessage(
    XDR *, stellarxdr_SignedSurveyRequestMessage *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SignedSurveyRequestMessage(
    XDR *, stellarxdr_SignedSurveyRequestMessage *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SignedSurveyRequestMessage();
#endif /* Old Style C */

typedef struct {
  u_int stellarxdr_EncryptedBody_len;
  char *stellarxdr_EncryptedBody_val;
} stellarxdr_EncryptedBody;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_EncryptedBody(XDR *,
                                               stellarxdr_EncryptedBody *);
#elif __STDC__
extern bool_t xdr_stellarxdr_EncryptedBody(XDR *, stellarxdr_EncryptedBody *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_EncryptedBody();
#endif /* Old Style C */

struct stellarxdr_SurveyResponseMessage {
  stellarxdr_NodeID surveyorPeerID;
  stellarxdr_NodeID surveyedPeerID;
  stellarxdr_uint32 ledgerNum;
  stellarxdr_SurveyMessageCommandType commandType;
  stellarxdr_EncryptedBody encryptedBody;
};
typedef struct stellarxdr_SurveyResponseMessage
    stellarxdr_SurveyResponseMessage;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_SurveyResponseMessage(XDR *, stellarxdr_SurveyResponseMessage *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_SurveyResponseMessage(XDR *, stellarxdr_SurveyResponseMessage *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SurveyResponseMessage();
#endif /* Old Style C */

struct stellarxdr_SignedSurveyResponseMessage {
  stellarxdr_Signature responseSignature;
  stellarxdr_SurveyResponseMessage response;
};
typedef struct stellarxdr_SignedSurveyResponseMessage
    stellarxdr_SignedSurveyResponseMessage;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_SignedSurveyResponseMessage(
    XDR *, stellarxdr_SignedSurveyResponseMessage *);
#elif __STDC__
extern bool_t xdr_stellarxdr_SignedSurveyResponseMessage(
    XDR *, stellarxdr_SignedSurveyResponseMessage *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SignedSurveyResponseMessage();
#endif /* Old Style C */

struct stellarxdr_PeerStats {
  stellarxdr_NodeID id;
  char *versionStr;
  stellarxdr_uint64 messagesRead;
  stellarxdr_uint64 messagesWritten;
  stellarxdr_uint64 bytesRead;
  stellarxdr_uint64 bytesWritten;
  stellarxdr_uint64 secondsConnected;
  stellarxdr_uint64 uniqueFloodBytesRecv;
  stellarxdr_uint64 duplicateFloodBytesRecv;
  stellarxdr_uint64 uniqueFetchBytesRecv;
  stellarxdr_uint64 duplicateFetchBytesRecv;
  stellarxdr_uint64 uniqueFloodMessageRecv;
  stellarxdr_uint64 duplicateFloodMessageRecv;
  stellarxdr_uint64 uniqueFetchMessageRecv;
  stellarxdr_uint64 duplicateFetchMessageRecv;
};
typedef struct stellarxdr_PeerStats stellarxdr_PeerStats;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PeerStats(XDR *, stellarxdr_PeerStats *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PeerStats(XDR *, stellarxdr_PeerStats *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PeerStats();
#endif /* Old Style C */

typedef struct {
  u_int stellarxdr_PeerStatList_len;
  stellarxdr_PeerStats *stellarxdr_PeerStatList_val;
} stellarxdr_PeerStatList;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_PeerStatList(XDR *, stellarxdr_PeerStatList *);
#elif __STDC__
extern bool_t xdr_stellarxdr_PeerStatList(XDR *, stellarxdr_PeerStatList *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_PeerStatList();
#endif /* Old Style C */

struct stellarxdr_TopologyResponseBody {
  stellarxdr_PeerStatList inboundPeers;
  stellarxdr_PeerStatList outboundPeers;
  stellarxdr_uint32 totalInboundPeerCount;
  stellarxdr_uint32 totalOutboundPeerCount;
};
typedef struct stellarxdr_TopologyResponseBody stellarxdr_TopologyResponseBody;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_TopologyResponseBody(XDR *, stellarxdr_TopologyResponseBody *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_TopologyResponseBody(XDR *, stellarxdr_TopologyResponseBody *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_TopologyResponseBody();
#endif /* Old Style C */

struct stellarxdr_SurveyResponseBody {
  stellarxdr_SurveyMessageCommandType type;
  union {
    stellarxdr_TopologyResponseBody topologyResponseBody;
  } stellarxdr_SurveyResponseBody_u;
};
typedef struct stellarxdr_SurveyResponseBody stellarxdr_SurveyResponseBody;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_SurveyResponseBody(XDR *, stellarxdr_SurveyResponseBody *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_SurveyResponseBody(XDR *, stellarxdr_SurveyResponseBody *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_SurveyResponseBody();
#endif /* Old Style C */

struct stellarxdr_StellarMessage {
  stellarxdr_MessageType type;
  union {
    stellarxdr_Error error;
    stellarxdr_Hello hello;
    stellarxdr_Auth auth;
    stellarxdr_DontHave dontHave;
    struct {
      u_int peers_len;
      stellarxdr_PeerAddress *peers_val;
    } peers;
    stellarxdr_uint256 txSetHash;
    stellarxdr_TransactionSet txSet;
    stellarxdr_TransactionEnvelope transaction;
    stellarxdr_SignedSurveyRequestMessage signedSurveyRequestMessage;
    stellarxdr_SignedSurveyResponseMessage signedSurveyResponseMessage;
    stellarxdr_uint256 qSetHash;
    stellarxdr_SCPQuorumSet qSet;
    stellarxdr_SCPEnvelope envelope;
    stellarxdr_uint32 getSCPLedgerSeq;
  } stellarxdr_StellarMessage_u;
};
typedef struct stellarxdr_StellarMessage stellarxdr_StellarMessage;
#ifdef __cplusplus
extern "C" bool_t xdr_stellarxdr_StellarMessage(XDR *,
                                                stellarxdr_StellarMessage *);
#elif __STDC__
extern bool_t xdr_stellarxdr_StellarMessage(XDR *, stellarxdr_StellarMessage *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_StellarMessage();
#endif /* Old Style C */

struct stellarxdr_AuthenticatedMessageV0 {
  stellarxdr_uint64 sequence;
  stellarxdr_StellarMessage message;
  stellarxdr_HmacSha256Mac mac;
};
typedef struct stellarxdr_AuthenticatedMessageV0
    stellarxdr_AuthenticatedMessageV0;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_AuthenticatedMessageV0(XDR *,
                                      stellarxdr_AuthenticatedMessageV0 *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_AuthenticatedMessageV0(XDR *,
                                      stellarxdr_AuthenticatedMessageV0 *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AuthenticatedMessageV0();
#endif /* Old Style C */

struct stellarxdr_AuthenticatedMessage {
  stellarxdr_uint32 v;
  union {
    stellarxdr_AuthenticatedMessageV0 v0;
  } stellarxdr_AuthenticatedMessage_u;
};
typedef struct stellarxdr_AuthenticatedMessage stellarxdr_AuthenticatedMessage;
#ifdef __cplusplus
extern "C" bool_t
xdr_stellarxdr_AuthenticatedMessage(XDR *, stellarxdr_AuthenticatedMessage *);
#elif __STDC__
extern bool_t
xdr_stellarxdr_AuthenticatedMessage(XDR *, stellarxdr_AuthenticatedMessage *);
#else  /* Old Style C */
bool_t xdr_stellarxdr_AuthenticatedMessage();
#endif /* Old Style C */

#endif /* !_STELLARXDR_H */
