#ifndef ASSET_H
#define ASSET_H

#include "keypair.h"
#include "stellarxdr.h"
#include "strkey.h"
#include <stdbool.h>
#include <stdint.h>

enum AssetType {
  ASSET_TYPE_NATIVE = 0,
  ASSET_TYPE_CREDIT_ALPHANUM4 = 1,
  ASSET_TYPE_CREDIT_ALPHANUM12 = 2,
};

struct Asset {
  enum AssetType type;
  char *code;
  char *issuer;
};

bool asset_to_xdr_object(const struct Asset *in, stellarxdr_Asset *out);

bool asset_from_xdr_object(const stellarxdr_Asset *in, struct Asset *out);

bool asset_to_trust_line_asset_xdr_object(const struct Asset *in,
                                          stellarxdr_TrustLineAsset *out);

bool asset_from_trust_line_asset_xdr_object(const stellarxdr_TrustLineAsset *in,
                                            struct Asset *out);

bool asset_to_change_trust_asset_xdr_object(const struct Asset *in,
                                            stellarxdr_ChangeTrustAsset *out);

bool asset_from_change_trust_asset_xdr_object(
    const stellarxdr_ChangeTrustAsset *in, struct Asset *out);

#endif
