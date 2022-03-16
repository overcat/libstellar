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
  if (assetA.type == ASSET_TYPE_NATIVE && assetB.type == ASSET_TYPE_NATIVE) {
    return false;
  }
  if ((assetA.type == ASSET_TYPE_CREDIT_ALPHANUM4 &&
       assetB.type == ASSET_TYPE_CREDIT_ALPHANUM4) ||
      (assetA.type == ASSET_TYPE_CREDIT_ALPHANUM12 &&
       assetB.type == ASSET_TYPE_CREDIT_ALPHANUM12)) {
    if (strcmp(assetA.code, assetB.code) == 0 &&
        strcmp(assetA.issuer, assetB.issuer) == 0) {
      return false;
    }
  }
  if (assetA.type == ASSET_TYPE_NATIVE) {
    return true;
  } else if (assetA.type == ASSET_TYPE_CREDIT_ALPHANUM4) {
    if (assetB.type == ASSET_TYPE_NATIVE) {
      return false;
    }
    if (assetB.type == ASSET_TYPE_CREDIT_ALPHANUM12) {
      return true;
    }
  } else {
    if (assetB.type != ASSET_TYPE_CREDIT_ALPHANUM12) {
      return false;
    }
  }

  if (strcmp(assetA.code, assetB.code) != 0) {
    return strcmp(assetA.code, assetB.code) < 0;
  }

  return strcmp(assetA.issuer, assetB.issuer) < 0;
}

bool liquidity_pool_asset_liquidity_pool_id(const struct LiquidityPoolAsset *in,
                                            char *liquidityPoolID) {
  stellarxdr_LiquidityPoolParameters liquidityPoolParameters;
  if (!liquidity_pool_asset_liquidity_pool_parameters(
          in, &liquidityPoolParameters)) {
    return false;
  }

  char *buf = NULL;
  size_t buf_size = 0;
  FILE *fp = open_memstream(&buf, &buf_size);
  XDR xdr;
  xdrstdio_create(&xdr, fp, XDR_ENCODE);
  if (!xdr_stellarxdr_LiquidityPoolParameters(&xdr, &liquidityPoolParameters)) {
    fclose(fp);
    return false;
  }
  fclose(fp);

  unsigned char liquidityPoolIDHash[32];
  SHA256_CTX sha256;
  sha256_init(&sha256);
  sha256_update(&sha256, buf, buf_size);
  sha256_final(&sha256, liquidityPoolIDHash);

  for (size_t i = 0; i < 32; i++) {
    sprintf(liquidityPoolID + (i * 2), "%.2x", liquidityPoolIDHash[i]);
  }
  liquidityPoolID[64] = '\0';
  return true;
}
