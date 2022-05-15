#ifndef LIBSTELLAR_WRITER_H
#define LIBSTELLAR_WRITER_H
#include <stdint.h>
#include <string.h>

#include "types.h"

// e.x.
// void sha256_update(const uint8_t *data, size_t len) {
//     // update it
// };
typedef void (*sha256_update_func)(const uint8_t *, size_t);

void write_uint32(uint32_t value, sha256_update_func sha256_update_func);

void write_uint64(uint64_t value, sha256_update_func sha256_update_func);

void write_bool(bool value, sha256_update_func sha256_update_func);

void write_string(const uint8_t *data, size_t len, sha256_update_func sha256_update_func);

void write_account_id(const account_id_t *account_id, sha256_update_func sha256_update_func);

void write_muxed_account_med25519(const muxed_account_med25519_t *med25519,
                                  sha256_update_func sha256_update_func);

bool write_muxed_account(const muxed_account_t *muxed_account,
                         sha256_update_func sha256_update_func);

void write_time_bounds(const time_bounds_t *time_bounds, sha256_update_func sha256_update_func);

void write_ledger_bounds(const ledger_bounds_t *ledger_bounds,
                         sha256_update_func sha256_update_func);

void write_preconditions(const preconditions_t *preconditions,
                         sha256_update_func sha256_update_func);

bool write_asset(const asset_t *asset, sha256_update_func sha256_update_func);

bool write_change_trust_asset(const change_trust_asset_t *asset,
                              sha256_update_func sha256_update_func);

void write_create_account_op(const create_account_op_t *op, sha256_update_func sha256_update_func);

void write_payment_op(const payment_op_t *op, sha256_update_func sha256_update_func);

void write_path_payment_strict_receive_op(const path_payment_strict_receive_op_t *op,
                                          sha256_update_func sha256_update_func);

void write_price(const price_t *price, sha256_update_func sha256_update_func);

void write_manage_sell_offer_op(const manage_sell_offer_op_t *op,
                                sha256_update_func sha256_update_func);

void write_create_passive_sell_offer_op(const create_passive_sell_offer_op_t *op,
                                        sha256_update_func sha256_update_func);

bool write_signer_key(const signer_key_t *signer_key, sha256_update_func sha256_update_func);
void write_signer(const signer_t *signer, sha256_update_func sha256_update_func);

void write_set_options_op(const set_options_op_t *op, sha256_update_func sha256_update_func);

void write_change_trust_op(const change_trust_op_t *op, sha256_update_func sha256_update_func);

void write_allow_trust_op(const allow_trust_op_t *op, sha256_update_func sha256_update_func);

void write_account_merge_op(const account_merge_op_t *op, sha256_update_func sha256_update_func);

void write_manage_data_op(const manage_data_op_t *op, sha256_update_func sha256_update_func);

void write_bump_sequence_op(const bump_sequence_op_t *op, sha256_update_func sha256_update_func);

void write_manage_buy_offer_op(const manage_buy_offer_op_t *op,
                               sha256_update_func sha256_update_func);

void write_path_payment_strict_send_op(const path_payment_strict_send_op_t *op,
                                       sha256_update_func sha256_update_func);

void write_create_claimable_balance_op(const create_claimable_balance_op_t *op,
                                       sha256_update_func sha256_update_func);

void write_claimable_balance_id(const claimable_balance_id *claimable_balance_id,
                                sha256_update_func sha256_update_func);

void write_claim_claimable_balance_op(const claim_claimable_balance_op_t *op,
                                      sha256_update_func sha256_update_func);

void write_begin_sponsoring_future_reserves_op(const begin_sponsoring_future_reserves_op_t *op,
                                               sha256_update_func sha256_update_func);

void write_revoke_sponsorship_op(const revoke_sponsorship_op_t *op,
                                 sha256_update_func sha256_update_func);

void write_clawback_op(const clawback_op_t *op, sha256_update_func sha256_update_func);

void write_clawback_claimable_balance_op(const clawback_claimable_balance_op_t *op,
                                         sha256_update_func sha256_update_func);

void write_set_trust_line_flags_op(const set_trust_line_flags_op_t *op,
                                   sha256_update_func sha256_update_func);

void write_liquidity_pool_deposit_op(const liquidity_pool_deposit_op_t *op,
                                     sha256_update_func sha256_update_func);
void write_liquidity_pool_withdraw_op(const liquidity_pool_withdraw_op_t *op,
                                      sha256_update_func sha256_update_func);

bool write_operation(const operation_t *op, sha256_update_func sha256_update_func);

bool write_memo(const memo_t *memo, sha256_update_func sha256_update_func);

void write_transaction_details(const transaction_details_t *transaction_details,
                               sha256_update_func sha256_update_func);

void write_fee_bump_transaction_details(
    const fee_bump_transaction_details_t *fee_bump_transaction_details,
    sha256_update_func sha256_update_func);

#endif  // LIBSTELLAR_WRITER_H
