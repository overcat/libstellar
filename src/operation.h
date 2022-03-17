#ifndef OPERATION_H
#define OPERATION_H
#include "asset.h"
#include "keypair.h"
#include "liquidity_pool_asset.h"
#include "muxed_account.h"
#include "price.h"
#include "stellarxdr.h"
#include "strkey.h"
#include <stdbool.h>

enum OperationType {
  CREATE_ACCOUNT = 0,              // done
  PAYMENT = 1,                     // done
  PATH_PAYMENT_STRICT_RECEIVE = 2, // done
  MANAGE_SELL_OFFER = 3,           // done
  CREATE_PASSIVE_SELL_OFFER = 4,   // done
  SET_OPTIONS = 5,
  CHANGE_TRUST = 6,
  ALLOW_TRUST = 7,               // done
  ACCOUNT_MERGE = 8,             // done
  INFLATION = 9,                 // done
  MANAGE_DATA = 10,              // done
  BUMP_SEQUENCE = 11,            // done
  MANAGE_BUY_OFFER = 12,         // done
  PATH_PAYMENT_STRICT_SEND = 13, // done
  CREATE_CLAIMABLE_BALANCE = 14,
  CLAIM_CLAIMABLE_BALANCE = 15,          // done
  BEGIN_SPONSORING_FUTURE_RESERVES = 16, // done
  END_SPONSORING_FUTURE_RESERVES = 17,   // done
  REVOKE_SPONSORSHIP = 18,
  CLAWBACK = 19,
  CLAWBACK_CLAIMABLE_BALANCE = 20, // done
  SET_TRUST_LINE_FLAGS = 21,       // done
  LIQUIDITY_POOL_DEPOSIT = 22,     // done
  LIQUIDITY_POOL_WITHDRAW = 23,    // done
};

enum TrustLineEntryFlag {
  TRUST_LINE_ENTRY_ALLOW_TRUST_OP_UNAUTHORIZED_FLAG =
      0, // The account can hold a balance but cannot receive payments, send
         // payments, maintain offers or manage offers
  TRUST_LINE_ENTRY_ALLOW_TRUST_OP_AUTHORIZED_FLAG =
      1, // The account can hold a balance, receive payments, send
         // payments, maintain offers or manage offers
  TRUST_LINE_ENTRY_ALLOW_TRUST_OP_AUTHORIZED_TO_MAINTAIN_LIABILITIES_FLAG =
      2, // The account can hold a balance and maintain offers but cannot
         // receive payments, send payments or manage offers
};

enum TrustLineFlags {
  TRUST_LINE_ALLOW_TRUST_OP_AUTHORIZED_FLAG =
      1, // The account can hold a balance, receive payments, send
         // payments, maintain offers or manage offers
  TRUST_LINE_ALLOW_TRUST_OP_AUTHORIZED_TO_MAINTAIN_LIABILITIES_FLAG =
      2, // The account can hold a balance and maintain offers but cannot
         // receive payments, send payments or manage offers
  TRUST_LINE_CLAWBACK_ENABLED_FLAG =
      4 // issuer has specified that it may clawback its credit, and that
        // claimable balances created with its credit may also be clawed back
};

struct CreateAccountOp {
  char *destination;       // account to create
  int64_t startingBalance; // amount they end up with
};

struct PaymentOp {
  char *destination;  // recipient of the payment
  struct Asset asset; // what they end up with
  int64_t amount;     // amount they end up with
};

struct PathPaymentStrictReceiveOp {
  struct Asset sendAsset; // asset we pay with
  int64_t sendMax;        // the maximum amount of sendAsset to
                          // send (excluding fees).
                          // The operation will fail if can't be met

  struct MuxedAccount destination; // recipient of the payment
  struct Asset destAsset;          // what they end up with
  int64_t destAmount;              // amount they end up with
  uint8_t pathLen;                 // TODO: rename -> pathLength
  struct Asset path[5]; // additional hops it must go through to get there
};

struct ManageSellOfferOp {
  struct Asset selling;
  struct Asset buying;
  int64_t amount; // amount being sold. if set to 0, delete the offer
  struct Price
      price;       // price of thing being sold in terms of what you are buying
  int64_t offerID; // 0=create a new offer, otherwise edit an existing offer
};

struct CreatePassiveSellOfferOp {
  struct Asset selling; // A
  struct Asset buying;  // B
  int64_t amount;       // amount taker gets
  struct Price price;   // cost of A in terms of B
};

struct AllowTrustOp {
  char trustor[57];
  char assetCode[13];                // TODO: check
  enum TrustLineEntryFlag authorize; // fixme
};

struct ManageDataOp {
  char dataName[65];
  uint8_t dataValueLength;
  uint8_t dataValue[64];
};

struct PathPaymentStrictSendOp {
  struct Asset sendAsset; // asset we pay with
  int64_t sendAmount;     // amount of sendAsset to send (excluding fees)

  struct MuxedAccount destination; // recipient of the payment
  struct Asset destAsset;          // what they end up with
  int64_t destMin;                 // the minimum amount of dest asset to
                                   // be received
                                   // The operation will fail if it can't be met
  uint8_t pathLen;
  struct Asset path[5]; // additional hops it must go through to get there
};

struct BumpSequenceOp {
  int64_t bump_to;
};

struct ManageBuyOfferOp {
  struct Asset selling;
  struct Asset buying;
  int64_t buyAmount; // amount being bought. if set to 0, delete the offer
  struct Price
      price; // price of thing being bought in terms of what you are selling
  int64_t offerID; // 0=create a new offer, otherwise edit an existing offer
};

struct AccountMergeOp {
  struct MuxedAccount destination;
};

struct BeginSponsoringFutureReservesOp {
  char sponsoredID[57];
};

struct ClaimClaimableBalanceOp {
  char balanceID[73];
};

struct SetTrustLineFlagsOp {
  char trustor[57];
  struct Asset asset;
  uint32_t clearFlags; // which flags to clear
  uint32_t setFlags;   // which flags to set
};

struct ClawbackClaimableBalanceOp {
  char balanceID[73];
};

struct LiquidityPoolDepositOp {
  char liquidityPoolID[65];
  int64_t maxAmountA;    // maximum amount of first asset to deposit
  int64_t maxAmountB;    // maximum amount of second asset to deposit
  struct Price minPrice; // minimum depositA/depositB
  struct Price maxPrice; // maximum depositA/depositB
};

struct LiquidityPoolWithdrawOp {
  char liquidityPoolID[65];
  int64_t amount;     // amount of pool shares to withdraw
  int64_t minAmountA; // minimum amount of first asset to withdraw
  int64_t minAmountB; // minimum amount of second asset to withdraw
};

enum ChangeTrustAssetType { CHANGE_TRUST_ASSET_TYPE_ASSET = 0, CHANGE_TRUST_ASSET_TYPE_LIQUIDITY_POOL_ASSET = 1 };
struct ChangeTrustOp {
  enum ChangeTrustAssetType assetType;
  union {
    struct Asset asset;
    struct LiquidityPoolAsset liquidityPoolAsset;
  } line;
  // if limit is set to 0, deletes the trust line
  int64_t limit;
};

struct Operation {
  bool source_account_present;
  struct MuxedAccount source_account;
  enum OperationType type;
  union {
    struct CreateAccountOp createAccountOp;
    struct PaymentOp paymentOp;
    struct PathPaymentStrictReceiveOp pathPaymentStrictReceiveOp;
    struct ManageSellOfferOp manageSellOfferOp;
    struct CreatePassiveSellOfferOp createPassiveSellOfferOp;
    struct PathPaymentStrictSendOp pathPaymentStrictSendOp;
    struct BumpSequenceOp bump_sequence_op;
    struct ManageBuyOfferOp manageBuyOfferOp;
    struct AllowTrustOp allowTrustOp;
    struct ManageDataOp manageDataOp;
    struct AccountMergeOp accountMergeOp;
    struct BeginSponsoringFutureReservesOp beginSponsoringFutureReservesOp;
    struct ClaimClaimableBalanceOp claimClaimableBalanceOp;
    struct SetTrustLineFlagsOp setTrustLineFlagsOp;
    struct ClawbackClaimableBalanceOp clawbackClaimableBalanceOp;
    struct LiquidityPoolDepositOp liquidityPoolDepositOp;
    struct LiquidityPoolWithdrawOp liquidityPoolWithdrawOp;
    struct ChangeTrustOp changeTrustOp;
  };
};

bool operation_to_xdr_object(const struct Operation *in,
                             stellarxdr_Operation *out);

bool operation_from_xdr_object(const stellarxdr_Operation *in,
                               struct Operation *out);

// TODO: remove
bool operation_to_xdr(const struct Operation *in, char **buf, size_t *buf_size);
#endif // OPERATION_H
