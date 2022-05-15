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
    struct MuxedAccountMed25519 med25519 = {.id = med_25519_xdr.id};
    memcpy(med25519.ed25519, ed25519, ED25519_PUBLIC_KEY_LENGTH + 1);
    muxed_account->med25519 = med25519;
    return true;
  } else if (starts_with(address, ED25519_PUBLIC_KEY_ACCOUNT_STARTING_LETTER)) {
    muxed_account->type = KEY_TYPE_ED25519;
    strcpy(muxed_account->ed25519, address);
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

bool muxed_account_to_xdr_object(const struct MuxedAccount *in,
                                 stellarxdr_MuxedAccount *out) {
  if (in->type == KEY_TYPE_ED25519) {
    uint8_t ed25519_raw[32];
    if (!decode_ed25519_public_key(in->ed25519, ed25519_raw)) {
      return false;
    }
    out->type = stellarxdr_KEY_TYPE_ED25519;
    memcpy(out->stellarxdr_MuxedAccount_u.ed25519, ed25519_raw, 32);
    return true;
  } else if (in->type == KEY_TYPE_MUXED_ED25519) {
    uint8_t ed25519_raw[32];
    if (!decode_ed25519_public_key(in->med25519.ed25519, ed25519_raw)) {
      return false;
    }
    out->type = stellarxdr_KEY_TYPE_MUXED_ED25519;
    memcpy(out->stellarxdr_MuxedAccount_u.med25519.ed25519, ed25519_raw, 32);
    out->stellarxdr_MuxedAccount_u.med25519.id = in->med25519.id;
    return true;
  } else {
    return false;
  }
}

bool muxed_account_from_xdr_object(const stellarxdr_MuxedAccount *in,
                                   struct MuxedAccount *out) {
  if (in->type == stellarxdr_KEY_TYPE_ED25519) {
    uint8_t ed25519_raw[32];
    memcpy(ed25519_raw, in->stellarxdr_MuxedAccount_u.ed25519, 32);
    if (!encode_ed25519_public_key(ed25519_raw, out->ed25519)) {
      return false;
    }
    out->type = KEY_TYPE_ED25519;
    return true;
  } else if (in->type == stellarxdr_KEY_TYPE_MUXED_ED25519) {
    uint8_t ed25519_raw[32];
    memcpy(ed25519_raw, in->stellarxdr_MuxedAccount_u.med25519.ed25519, 32);
    if (!encode_ed25519_public_key(ed25519_raw, out->med25519.ed25519)) {
      return false;
    }
    out->med25519.id = in->stellarxdr_MuxedAccount_u.med25519.id;
    out->type = KEY_TYPE_MUXED_ED25519;
    return true;
  } else {
    return false;
  }
}