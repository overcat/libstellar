#ifndef MUXED_ACCOUNT_H
#define MUXED_ACCOUNT_H

#include "stdbool.h"
#include "stellarxdr.h"
#include "strkey.h"

struct MuxedAccountMed25519 {
  uint64_t id;
  char ed25519[57];
};

struct MuxedAccount {
  enum CryptoKeyType type;
  union {
    char ed25519[57];
    struct MuxedAccountMed25519 med25519;
  };
};

bool muxed_account_from_address(char *address,
                                struct MuxedAccount *muxed_account);

bool muxed_account_to_address(const struct MuxedAccount *muxed_account,
                              char *address);

bool muxed_account_to_xdr_object(const struct MuxedAccount *in,
                                 stellarxdr_MuxedAccount *out);

bool muxed_account_from_xdr_object(const stellarxdr_MuxedAccount *in,
                                   struct MuxedAccount *out);
#endif // MUXED_ACCOUNT_H
