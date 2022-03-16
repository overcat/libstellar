#include "asset.h"

struct LiquidityPoolAsset {
  struct Asset assetA;
  struct Asset assetB;
  int32_t fee;
};

bool liquidity_pool_asset_to_change_trust_asset_xdr_object(
    const struct LiquidityPoolAsset *in, stellarxdr_ChangeTrustAsset *out);

bool liquidity_pool_asset_from_change_trust_asset_xdr_object(
    const stellarxdr_ChangeTrustAsset *in, struct LiquidityPoolAsset *out);

bool liquidity_pool_asset_is_valid_lexicographic_order(struct Asset assetA,
                                                       struct Asset assetB);

bool liquidity_pool_asset_liquidity_pool_id(const struct LiquidityPoolAsset *in,
                                            char *liquidityPoolID);