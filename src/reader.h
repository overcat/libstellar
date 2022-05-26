#ifndef LIBSTELLAR_READER_H
#define LIBSTELLAR_READER_H
#include <stdint.h>
#include <string.h>

#include "types.h"

typedef bool (*xdr_type_reader)(buffer_t *, void *);

bool buffer_can_read(const buffer_t *buffer, size_t num_bytes);

void buffer_advance(buffer_t *buffer, size_t num_bytes);

bool buffer_read32(buffer_t *buffer, uint32_t *n);

bool buffer_read64(buffer_t *buffer, uint64_t *n);

bool buffer_read_bool(buffer_t *buffer, bool *b);

bool buffer_read_bytes(buffer_t *buffer, uint8_t *out, size_t size);

size_t num_bytes(size_t size);

bool check_padding(const uint8_t *buffer, size_t offset, size_t length);

bool read_string_ptr(buffer_t *buffer, const char **string, size_t *out_len, size_t max_length);

bool read_optional_type(buffer_t *buffer, xdr_type_reader parser, void *dst, bool *opted);

bool read_signer_key(buffer_t *buffer, signer_key_t *key);

bool read_account_id(buffer_t *buffer, const uint8_t **account_id);

bool read_muxed_account(buffer_t *buffer, muxed_account_t *muxed_account);

bool read_time_bounds(buffer_t *buffer, time_bounds_t *bounds);

bool read_ledger_bounds(buffer_t *buffer, ledger_bounds_t *ledger_bounds);

bool read_extra_signers(buffer_t *buffer);

bool read_preconditions(buffer_t *buffer, preconditions_t *cond);

bool read_memo(buffer_t *buffer, memo_t *memo);

bool read_alpha_num4_asset(buffer_t *buffer, alpha_num4_t *asset);

bool read_alpha_num12_asset(buffer_t *buffer, alpha_num12_t *asset);

bool read_asset(buffer_t *buffer, asset_t *asset);

bool read_trust_line_asset(buffer_t *buffer, trust_line_asset_t *asset);

bool read_liquidity_pool_parameters(buffer_t *buffer,
                                    liquidity_pool_parameters_t *liquidityPoolParameters);

bool read_change_trust_asset(buffer_t *buffer, change_trust_asset_t *asset);

bool read_create_account(buffer_t *buffer, create_account_op_t *create_account_op);

bool read_payment(buffer_t *buffer, payment_op_t *payment_op);

bool read_path_payment_strict_receive(buffer_t *buffer, path_payment_strict_receive_op_t *op);

bool read_allow_trust(buffer_t *buffer, allow_trust_op_t *op);

bool read_account_merge(buffer_t *buffer, account_merge_op_t *op);

bool read_manage_data(buffer_t *buffer, manage_data_op_t *op);

bool read_price(buffer_t *buffer, price_t *price);

bool read_manage_sell_offer(buffer_t *buffer, manage_sell_offer_op_t *op);

bool read_manage_buy_offer(buffer_t *buffer, manage_buy_offer_op_t *op);

bool read_create_passive_sell_offer(buffer_t *buffer, create_passive_sell_offer_op_t *op);

bool read_change_trust(buffer_t *buffer, change_trust_op_t *op);

bool read_signer(buffer_t *buffer, signer_t *signer);

bool read_set_options(buffer_t *buffer, set_options_op_t *setOptions);

bool read_bump_sequence(buffer_t *buffer, bump_sequence_op_t *op);

bool read_path_payment_strict_send(buffer_t *buffer, path_payment_strict_send_op_t *op);

bool read_claimant_predicate(buffer_t *buffer);

bool read_claimant(buffer_t *buffer, claimant_t *claimant);

bool read_create_claimable_balance(buffer_t *buffer, create_claimable_balance_op_t *op);

bool read_claimable_balance_id(buffer_t *buffer, claimable_balance_id *claimableBalanceID);

bool read_claim_claimable_balance(buffer_t *buffer, claim_claimable_balance_op_t *op);

bool read_begin_sponsoring_future_reserves(buffer_t *buffer,
                                           begin_sponsoring_future_reserves_op_t *op);

bool read_ledger_key(buffer_t *buffer, ledger_key_t *ledger_key);

bool read_revoke_sponsorship(buffer_t *buffer, revoke_sponsorship_op_t *op);

bool read_clawback(buffer_t *buffer, clawback_op_t *op);

bool read_clawback_claimable_balance(buffer_t *buffer, clawback_claimable_balance_op_t *op);

bool read_set_trust_line_flags(buffer_t *buffer, set_trust_line_flags_op_t *op);

bool read_liquidity_pool_deposit(buffer_t *buffer, liquidity_pool_deposit_op_t *op);

bool read_liquidity_pool_withdraw(buffer_t *buffer, liquidity_pool_withdraw_op_t *op);

bool read_operation(buffer_t *buffer, operation_t *opDetails);

bool read_tx_details(buffer_t *buffer, transaction_details_t *transaction);

bool read_fee_bump_tx_details(buffer_t *buffer, fee_bump_transaction_details_t *feeBumpTransaction);

bool read_transaction_envelope_type(buffer_t *buffer, envelope_type_t *envelope_type);
#endif  // LIBSTELLAR_READER_H
