#ifndef OPERATION_H
#define OPERATION_H
#include "asset.h"
#include "keypair.h"
#include "muxed_account.h"
#include "price.h"
#include "stellarxdr.h"
#include "strkey.h"
#include <stdbool.h>

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
  uint8_t pathLen;
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
  };
};

bool operation_to_xdr_object(const struct Operation *in,
                             stellarxdr_Operation *out);

bool operation_from_xdr_object(const stellarxdr_Operation *in,
                               struct Operation *out);

// TODO: remove
bool operation_to_xdr(const struct Operation *in, char **buf, size_t *buf_size);
#endif // OPERATION_H
