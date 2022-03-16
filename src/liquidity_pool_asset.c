#include "liquidity_pool_asset.h"

bool liquidity_pool_asset_liquidity_pool_parameters(
    const struct LiquidityPoolAsset *in,
    stellarxdr_LiquidityPoolParameters *out) {
  stellarxdr_LiquidityPoolConstantProductParameters
      liquidityPoolConstantProductParameters;
  if (!asset_to_xdr_object(&in->assetA,
                           &liquidityPoolConstantProductParameters.assetA)) {
    return false;
  }
  if (!asset_to_xdr_object(&in->assetB,
                           &liquidityPoolConstantProductParameters.assetB)) {
    return false;
  }
  liquidityPoolConstantProductParameters.fee = in->fee;
  out->type = stellarxdr_LIQUIDITY_POOL_CONSTANT_PRODUCT;
  out->stellarxdr_LiquidityPoolParameters_u.constantProduct =
      liquidityPoolConstantProductParameters;
  return true;
}

bool liquidity_pool_asset_to_change_trust_asset_xdr_object(
    const struct LiquidityPoolAsset *in, stellarxdr_ChangeTrustAsset *out) {
  out->type = stellarxdr_ASSET_TYPE_POOL_SHARE;
  stellarxdr_LiquidityPoolParameters liquidityPoolParameters;
  if (!liquidity_pool_asset_liquidity_pool_parameters(
          in, &liquidityPoolParameters)) {
    return false;
  }
  out->stellarxdr_ChangeTrustAsset_u.liquidityPool = liquidityPoolParameters;
  return true;
}

bool liquidity_pool_asset_from_change_trust_asset_xdr_object(
    const stellarxdr_ChangeTrustAsset *in, struct LiquidityPoolAsset *out) {
  if (in->type != stellarxdr_ASSET_TYPE_POOL_SHARE) {
    return false;
  }

  out->fee = in->stellarxdr_ChangeTrustAsset_u.liquidityPool
                .stellarxdr_LiquidityPoolParameters_u.constantProduct.fee;
  if (!asset_from_xdr_object(
          &in->stellarxdr_ChangeTrustAsset_u.liquidityPool
               .stellarxdr_LiquidityPoolParameters_u.constantProduct.assetA,
          &out->assetA)) {
    return false;
  }
  if (!asset_from_xdr_object(
          &in->stellarxdr_ChangeTrustAsset_u.liquidityPool
               .stellarxdr_LiquidityPoolParameters_u.constantProduct.assetB,
          &out->assetB)) {
    return false;
  }
  return true;
}

bool liquidity_pool_asset_is_valid_lexicographic_order(struct Asset assetA,
                                                       struct Asset assetB) {
  return true;
}

bool liquidity_pool_asset_liquidity_pool_id(const struct LiquidityPoolAsset *in,
                                            char *liquidityPoolID) {
  return true;
}
