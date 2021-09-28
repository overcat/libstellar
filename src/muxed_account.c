#include "muxed_account.h"

bool starts_with(const char *pre, const char *str) {
  if (strncmp(pre, str, strlen(str)) == 0)
    return true;
  return false;
}

bool muxed_account_from_address(char *address,
                                struct MuxedAccount *muxed_account) {
  if (starts_with(address, MUXED_ACCOUNT_STARTING_LETTER)) {
    muxed_account->type = KEY_TYPE_MUXED_ED25519;
    stellarxdr_MuxedAccountMed25519 med_25519_xdr;
    if (!decode_med25519_public_key(address, &med_25519_xdr)) {
      return false;
    }
    char ed25519[ED25519_PUBLIC_KEY_LENGTH + 1];
    uint8_t ed25519_raw[32];
    memcpy(ed25519_raw, med_25519_xdr.ed25519, 32);
    if (!encode_ed25519_public_key(ed25519_raw, ed25519)) {
      return false;
    }
    struct MuxedAccountMed25519 med25519 = {.ed25519 = ed25519,
                                            .id = med_25519_xdr.id};
    muxed_account->med25519 = med25519;
    return true;
  } else if (starts_with(address, ED25519_PUBLIC_KEY_ACCOUNT_STARTING_LETTER)) {
    muxed_account->type = KEY_TYPE_ED25519;
    muxed_account->ed25519 = address;
    return true;
  } else {
    return false;
  }
}

bool muxed_account_to_address(const struct MuxedAccount *muxed_account,
                              char *address) {
  if (muxed_account->type == KEY_TYPE_ED25519) {
    strcpy(address, muxed_account->ed25519);
    return true;
  } else if (muxed_account->type == KEY_TYPE_MUXED_ED25519) {
    uint8_t ed25519_raw[32];
    if (!decode_ed25519_public_key(muxed_account->med25519.ed25519,
                                   ed25519_raw)) {
      return false;
    }
    stellarxdr_MuxedAccountMed25519 med_25519_xdr;
    memcpy(med_25519_xdr.ed25519, ed25519_raw, 32);
    med_25519_xdr.id = muxed_account->med25519.id;
    if (!encode_med25519_public_key(&med_25519_xdr, address)) {
      return false;
    }
    return true;
  } else {
    return false;
  }
}