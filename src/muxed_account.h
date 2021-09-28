#ifndef MUXED_ACCOUNT_H
#define MUXED_ACCOUNT_H

#include "stdbool.h"
#include "stellarxdr.h"
#include "strkey.h"

struct MuxedAccountMed25519 {
  uint64_t id;
  char *ed25519;
};

struct MuxedAccount {
  enum CryptoKeyType type;
  union {
    char *ed25519;
    struct MuxedAccountMed25519 med25519;
  };
};

bool muxed_account_from_address(char *address,
                                struct MuxedAccount *muxed_account);

bool muxed_account_to_address(const struct MuxedAccount *muxed_account,
                              char *address);

#endif // MUXED_ACCOUNT_H
