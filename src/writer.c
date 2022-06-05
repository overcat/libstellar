#include "writer.h"

void write_uint32(uint32_t value, sha256_update_func sha256_update_func) {
    uint8_t data[4] = {0};
    data[0] = (value >> 24) & 0xFF;
    data[1] = (value >> 16) & 0xFF;
    data[2] = (value >> 8) & 0xFF;
    data[3] = value & 0xFF;
    sha256_update_func(data, sizeof(data));
}

void write_uint64(uint64_t value, sha256_update_func sha256_update_func) {
    uint8_t data[8] = {0};
    data[0] = (value >> 56) & 0xFF;
    data[1] = (value >> 48) & 0xFF;
    data[2] = (value >> 40) & 0xFF;
    data[3] = (value >> 32) & 0xFF;
    data[4] = (value >> 24) & 0xFF;
    data[5] = (value >> 16) & 0xFF;
    data[6] = (value >> 8) & 0xFF;
    data[7] = value & 0xFF;
    sha256_update_func(data, sizeof(data));
}

void write_bool(bool value, sha256_update_func sha256_update_func) {
    uint32_t b = value ? 1 : 0;
    write_uint32(b, sha256_update_func);
}

void write_string(const uint8_t *data, size_t len, sha256_update_func sha256_update_func) {
    write_uint32((uint32_t) len, sha256_update_func);
    sha256_update_func(data, len);

    // If len isn't a multiple of 4, add padding bytes.
    int remainder = len % 4;
    uint8_t null_byte[1] = {0x00};
    if (remainder) {
        while (remainder < 4) {
            sha256_update_func(null_byte, 1);
            remainder++;
        }
    }
}

void write_account_id(account_id_t account_id, sha256_update_func sha256_update_func) {
    write_uint32(PUBLIC_KEY_TYPE_ED25519, sha256_update_func);
    sha256_update_func(account_id, 32);
}

void write_muxed_account_med25519(const muxed_account_med25519_t *med25519,
                                  sha256_update_func sha256_update_func) {
    write_uint64(med25519->id, sha256_update_func);
    sha256_update_func(med25519->ed25519, 32);
}

bool write_muxed_account(const muxed_account_t *muxed_account,
                         sha256_update_func sha256_update_func) {
    write_uint32(muxed_account->type, sha256_update_func);
    switch (muxed_account->type) {
        case KEY_TYPE_ED25519:
            sha256_update_func(muxed_account->ed25519, 32);
            break;
        case KEY_TYPE_MUXED_ED25519:
            write_muxed_account_med25519(&muxed_account->med25519, sha256_update_func);
            break;
        default:
            return false;
    }
    return true;
}

void write_time_bounds(const time_bounds_t *time_bounds, sha256_update_func sha256_update_func) {
    write_uint64(time_bounds->min_time, sha256_update_func);
    write_uint64(time_bounds->max_time, sha256_update_func);
}

void write_ledger_bounds(const ledger_bounds_t *ledger_bounds,
                         sha256_update_func sha256_update_func) {
    write_uint32(ledger_bounds->min_ledger, sha256_update_func);
    write_uint32(ledger_bounds->max_ledger, sha256_update_func);
}

void write_preconditions(const preconditions_t *preconditions,
                         sha256_update_func sha256_update_func) {
    if (preconditions->ledger_bounds_present || preconditions->min_seq_num_present ||
        preconditions->min_seq_age || preconditions->min_seq_ledger_gap ||
        preconditions->extra_signers_len) {
        write_uint32(PRECOND_V2, sha256_update_func);
        if (preconditions->time_bounds_present) {
            write_bool(true, sha256_update_func);
            write_time_bounds(&preconditions->time_bounds, sha256_update_func);
        } else {
            write_bool(false, sha256_update_func);
        }

        if (preconditions->ledger_bounds_present) {
            write_bool(true, sha256_update_func);
            write_ledger_bounds(&preconditions->ledger_bounds, sha256_update_func);
        } else {
            write_bool(false, sha256_update_func);
        }

        if (preconditions->min_seq_num_present) {
            write_bool(true, sha256_update_func);
            write_uint64(preconditions->min_seq_num, sha256_update_func);
        } else {
            write_bool(false, sha256_update_func);
        }

        write_uint64(preconditions->min_seq_age, sha256_update_func);
        write_uint32(preconditions->min_seq_ledger_gap, sha256_update_func);
        write_uint32(preconditions->extra_signers_len, sha256_update_func);
        for (uint8_t i = 0; i < preconditions->extra_signers_len; i++) {
            write_signer_key(preconditions->extra_signers + i, sha256_update_func);
        }
    } else if (preconditions->time_bounds_present) {
        write_uint32(PRECOND_TIME, sha256_update_func);
        write_time_bounds(&preconditions->time_bounds, sha256_update_func);
    } else {
        write_uint32(PRECOND_NONE, sha256_update_func);
    }
}

bool write_asset(const asset_t *asset, sha256_update_func sha256_update_func) {
    write_uint32(asset->type, sha256_update_func);
    switch (asset->type) {
        case ASSET_TYPE_NATIVE:
            break;
        case ASSET_TYPE_CREDIT_ALPHANUM4: {
            char code4[4 + 1] = {0};
            strlcpy(code4, asset->alpha_num4.asset_code, sizeof(code4));
            sha256_update_func((uint8_t *) code4, 4);
            write_account_id(asset->alpha_num4.issuer, sha256_update_func);
            break;
        }
        case ASSET_TYPE_CREDIT_ALPHANUM12: {
            char code12[12 + 1] = {0};
            strlcpy(code12, asset->alpha_num12.asset_code, sizeof(code12));
            sha256_update_func((uint8_t *) code12, 12);
            write_account_id(asset->alpha_num12.issuer, sha256_update_func);
            break;
        }
        default:
            return false;
    }
    return true;
}

bool write_change_trust_asset(const change_trust_asset_t *asset,
                              sha256_update_func sha256_update_func) {
    switch (asset->type) {
        case ASSET_TYPE_NATIVE:
        case ASSET_TYPE_CREDIT_ALPHANUM4:
        case ASSET_TYPE_CREDIT_ALPHANUM12:
            return write_asset((asset_t *) asset, sha256_update_func);
        case ASSET_TYPE_POOL_SHARE:
            write_uint32(asset->type, sha256_update_func);
            write_uint32(asset->liquidity_pool.type, sha256_update_func);
            write_asset(&asset->liquidity_pool.constant_product.assetA, sha256_update_func);
            write_asset(&asset->liquidity_pool.constant_product.assetB, sha256_update_func);
            write_uint32(asset->liquidity_pool.constant_product.fee, sha256_update_func);
            break;
        default:
            return false;
    }
    return true;
}

void write_create_account_op(const create_account_op_t *op, sha256_update_func sha256_update_func) {
    write_account_id(op->destination, sha256_update_func);
    write_uint64(op->starting_balance, sha256_update_func);
}

void write_payment_op(const payment_op_t *op, sha256_update_func sha256_update_func) {
    write_muxed_account(&op->destination, sha256_update_func);
    write_asset(&op->asset, sha256_update_func);
    write_uint64(op->amount, sha256_update_func);
}

void write_path_payment_strict_receive_op(const path_payment_strict_receive_op_t *op,
                                          sha256_update_func sha256_update_func) {
    write_asset(&op->send_asset, sha256_update_func);
    write_uint64(op->send_max, sha256_update_func);
    write_muxed_account(&op->destination, sha256_update_func);
    write_asset(&op->dest_asset, sha256_update_func);
    write_uint64(op->dest_amount, sha256_update_func);
    write_uint32(op->path_len, sha256_update_func);
    for (int i = 0; i < op->path_len; i++) {
        write_asset(&op->path[i], sha256_update_func);
    }
}

void write_price(const price_t *price, sha256_update_func sha256_update_func) {
    write_uint32(price->n, sha256_update_func);
    write_uint32(price->d, sha256_update_func);
}

void write_manage_sell_offer_op(const manage_sell_offer_op_t *op,
                                sha256_update_func sha256_update_func) {
    write_asset(&op->selling, sha256_update_func);
    write_asset(&op->buying, sha256_update_func);
    write_uint64(op->amount, sha256_update_func);
    write_price(&op->price, sha256_update_func);
    write_uint64(op->offer_id, sha256_update_func);
}

void write_create_passive_sell_offer_op(const create_passive_sell_offer_op_t *op,
                                        sha256_update_func sha256_update_func) {
    write_asset(&op->selling, sha256_update_func);
    write_asset(&op->buying, sha256_update_func);
    write_uint64(op->amount, sha256_update_func);
    write_price(&op->price, sha256_update_func);
}

bool write_signer_key(const signer_key_t *signer_key, sha256_update_func sha256_update_func) {
    write_uint32(signer_key->type, sha256_update_func);
    switch (signer_key->type) {
        case SIGNER_KEY_TYPE_ED25519:
            sha256_update_func(signer_key->ed25519, 32);
            break;
        case SIGNER_KEY_TYPE_PRE_AUTH_TX:
            sha256_update_func(signer_key->pre_auth_tx, 32);
            break;
        case SIGNER_KEY_TYPE_HASH_X:
            sha256_update_func(signer_key->hash_x, 32);
            break;
        case SIGNER_KEY_TYPE_ED25519_SIGNED_PAYLOAD:
            sha256_update_func(signer_key->ed25519_signed_payload.ed25519, 32);
            write_uint32(signer_key->ed25519_signed_payload.payload_len, sha256_update_func);
            sha256_update_func(signer_key->ed25519_signed_payload.payload,
                               signer_key->ed25519_signed_payload.payload_len);
            int remainder = signer_key->ed25519_signed_payload.payload_len % 4;
            uint8_t null_byte[1] = {0x00};
            if (remainder) {
                while (remainder < 4) {
                    sha256_update_func(null_byte, 1);
                    remainder++;
                }
            }
            break;
        default:
            return false;
    }
    return true;
}

void write_signer(const signer_t *signer, sha256_update_func sha256_update_func) {
    write_signer_key(&signer->key, sha256_update_func);
    write_uint32(signer->weight, sha256_update_func);
}

void write_set_options_op(const set_options_op_t *op, sha256_update_func sha256_update_func) {
    if (op->inflation_destination_present) {
        write_bool(true, sha256_update_func);
        write_account_id(op->inflation_destination, sha256_update_func);
    } else {
        write_bool(false, sha256_update_func);
    }

    if (op->clear_flags_present) {
        write_bool(true, sha256_update_func);
        write_uint32(op->clear_flags, sha256_update_func);
    } else {
        write_bool(false, sha256_update_func);
    }

    if (op->set_flags_present) {
        write_bool(true, sha256_update_func);
        write_uint32(op->set_flags, sha256_update_func);
    } else {
        write_bool(false, sha256_update_func);
    }

    if (op->master_weight_present) {
        write_bool(true, sha256_update_func);
        write_uint32(op->master_weight, sha256_update_func);
    } else {
        write_bool(false, sha256_update_func);
    }

    if (op->low_threshold_present) {
        write_bool(true, sha256_update_func);
        write_uint32(op->low_threshold, sha256_update_func);
    } else {
        write_bool(false, sha256_update_func);
    }

    if (op->medium_threshold_present) {
        write_bool(true, sha256_update_func);
        write_uint32(op->medium_threshold, sha256_update_func);
    } else {
        write_bool(false, sha256_update_func);
    }

    if (op->high_threshold_present) {
        write_bool(true, sha256_update_func);
        write_uint32(op->high_threshold, sha256_update_func);
    } else {
        write_bool(false, sha256_update_func);
    }

    if (op->home_domain_present) {
        write_bool(true, sha256_update_func);
        write_string(op->home_domain, op->home_domain_size, sha256_update_func);
    } else {
        write_bool(false, sha256_update_func);
    }

    if (op->signer_present) {
        write_bool(true, sha256_update_func);
        write_signer(&op->signer, sha256_update_func);
    } else {
        write_bool(false, sha256_update_func);
    }
}

void write_change_trust_op(const change_trust_op_t *op, sha256_update_func sha256_update_func) {
    write_change_trust_asset(&op->line, sha256_update_func);
    write_uint64(op->limit, sha256_update_func);
}

void write_allow_trust_op(const allow_trust_op_t *op, sha256_update_func sha256_update_func) {
    write_account_id(op->trustor, sha256_update_func);
    size_t len = strlen(op->asset_code);
    if (len <= 4) {
        write_uint32(ASSET_TYPE_CREDIT_ALPHANUM4, sha256_update_func);
        char code4[4 + 1] = {0};
        strlcpy(code4, op->asset_code, sizeof(code4));
        sha256_update_func((uint8_t *) code4, 4);
    } else {
        write_uint32(ASSET_TYPE_CREDIT_ALPHANUM12, sha256_update_func);
        char code12[12 + 1] = {0};
        strlcpy(code12, op->asset_code, sizeof(code12));
        sha256_update_func((uint8_t *) code12, 12);
    }
    write_uint32(op->authorize, sha256_update_func);
}

void write_account_merge_op(const account_merge_op_t *op, sha256_update_func sha256_update_func) {
    write_muxed_account(&op->destination, sha256_update_func);
}

void write_manage_data_op(const manage_data_op_t *op, sha256_update_func sha256_update_func) {
    write_string(op->data_name, op->data_name_size, sha256_update_func);
    if (op->data_value_size) {
        write_bool(true, sha256_update_func);
        write_string(op->data_value, op->data_value_size, sha256_update_func);
    } else {
        write_bool(false, sha256_update_func);
    }
}

void write_bump_sequence_op(const bump_sequence_op_t *op, sha256_update_func sha256_update_func) {
    write_uint64(op->bump_to, sha256_update_func);
}

void write_manage_buy_offer_op(const manage_buy_offer_op_t *op,
                               sha256_update_func sha256_update_func) {
    write_asset(&op->selling, sha256_update_func);
    write_asset(&op->buying, sha256_update_func);
    write_uint64(op->buy_amount, sha256_update_func);
    write_price(&op->price, sha256_update_func);
    write_uint64(op->offer_id, sha256_update_func);
}

void write_path_payment_strict_send_op(const path_payment_strict_send_op_t *op,
                                       sha256_update_func sha256_update_func) {
    write_asset(&op->send_asset, sha256_update_func);
    write_uint64(op->send_amount, sha256_update_func);
    write_muxed_account(&op->destination, sha256_update_func);
    write_asset(&op->dest_asset, sha256_update_func);
    write_uint64(op->dest_min, sha256_update_func);
    write_uint32(op->path_len, sha256_update_func);
    for (int i = 0; i < op->path_len; i++) {
        write_asset(&op->path[i], sha256_update_func);
    }
}

bool write_create_claimable_balance_op(const create_claimable_balance_op_t *op,
                                       sha256_update_func sha256_update_func) {
    // create_claimable_balance_op is currently not supported.
    return false;
}

void write_claimable_balance_id(const claimable_balance_id *claimable_balance_id,
                                sha256_update_func sha256_update_func) {
    write_uint32(claimable_balance_id->type, sha256_update_func);
    sha256_update_func(claimable_balance_id->v0, 32);
}

void write_claim_claimable_balance_op(const claim_claimable_balance_op_t *op,
                                      sha256_update_func sha256_update_func) {
    write_claimable_balance_id(&op->balance_id, sha256_update_func);
}

void write_begin_sponsoring_future_reserves_op(const begin_sponsoring_future_reserves_op_t *op,
                                               sha256_update_func sha256_update_func) {
    write_account_id(op->sponsored_id, sha256_update_func);
}

bool write_trust_line_asset(const trust_line_asset_t *asset,
                            sha256_update_func sha256_update_func) {
    switch (asset->type) {
        case ASSET_TYPE_NATIVE:
        case ASSET_TYPE_CREDIT_ALPHANUM4:
        case ASSET_TYPE_CREDIT_ALPHANUM12:
            return write_asset((asset_t *) asset, sha256_update_func);
        case ASSET_TYPE_POOL_SHARE:
            write_uint32(asset->type, sha256_update_func);
            sha256_update_func(asset->liquidity_pool_id, sizeof(asset->liquidity_pool_id));
            break;
        default:
            return false;
    }
    return true;
}

bool write_revoke_sponsorship_ledger_entry(const ledger_key_t *ledger_key,
                                           sha256_update_func sha256_update_func) {
    write_uint32(ledger_key->type, sha256_update_func);
    switch (ledger_key->type) {
        case ACCOUNT:
            write_account_id(ledger_key->account.account_id, sha256_update_func);
            break;
        case TRUSTLINE:
            write_account_id(ledger_key->trust_line.account_id, sha256_update_func);
            write_trust_line_asset(&ledger_key->trust_line.asset, sha256_update_func);
            break;
        case OFFER:
            write_account_id(ledger_key->offer.seller_id, sha256_update_func);
            write_uint64(ledger_key->offer.offer_id, sha256_update_func);
            break;
        case DATA:
            write_account_id(ledger_key->data.account_id, sha256_update_func);
            write_string(ledger_key->data.data_name,
                         ledger_key->data.data_name_size,
                         sha256_update_func);
            break;
        case CLAIMABLE_BALANCE:
            write_claimable_balance_id(&ledger_key->claimable_balance.balance_id,
                                       sha256_update_func);
            break;
        case LIQUIDITY_POOL:
            sha256_update_func(ledger_key->liquidity_pool.liquidity_pool_id, 32);
            break;
        default:
            return false;
    }
    return true;
}

bool write_revoke_sponsorship_op(const revoke_sponsorship_op_t *op,
                                 sha256_update_func sha256_update_func) {
    write_uint32(op->type, sha256_update_func);
    switch (op->type) {
        case REVOKE_SPONSORSHIP_LEDGER_ENTRY:
            return write_revoke_sponsorship_ledger_entry(&op->ledger_key, sha256_update_func);
        case REVOKE_SPONSORSHIP_SIGNER:
            write_account_id(op->signer.account_id, sha256_update_func);
            write_signer_key(&op->signer.signer_key, sha256_update_func);
            break;
        default:
            return false;
    }
    return true;
}

void write_clawback_op(const clawback_op_t *op, sha256_update_func sha256_update_func) {
    write_asset(&op->asset, sha256_update_func);
    write_muxed_account(&op->from, sha256_update_func);
    write_uint64(op->amount, sha256_update_func);
}

void write_clawback_claimable_balance_op(const clawback_claimable_balance_op_t *op,
                                         sha256_update_func sha256_update_func) {
    write_claimable_balance_id(&op->balance_id, sha256_update_func);
}

void write_set_trust_line_flags_op(const set_trust_line_flags_op_t *op,
                                   sha256_update_func sha256_update_func) {
    write_account_id(op->trustor, sha256_update_func);
    write_asset(&op->asset, sha256_update_func);
    write_uint32(op->clear_flags, sha256_update_func);
    write_uint32(op->set_flags, sha256_update_func);
}

void write_liquidity_pool_deposit_op(const liquidity_pool_deposit_op_t *op,
                                     sha256_update_func sha256_update_func) {
    sha256_update_func(op->liquidity_pool_id, 32);
    write_uint64(op->max_amount_a, sha256_update_func);
    write_uint64(op->max_amount_b, sha256_update_func);
    write_price(&op->min_price, sha256_update_func);
    write_price(&op->max_price, sha256_update_func);
}

void write_liquidity_pool_withdraw_op(const liquidity_pool_withdraw_op_t *op,
                                      sha256_update_func sha256_update_func) {
    sha256_update_func(op->liquidity_pool_id, 32);
    write_uint64(op->amount, sha256_update_func);
    write_uint64(op->min_amount_a, sha256_update_func);
    write_uint64(op->min_amount_b, sha256_update_func);
}

bool write_operation(const operation_t *op, sha256_update_func sha256_update_func) {
    if (op->source_account_present) {
        write_bool(true, sha256_update_func);
        write_muxed_account(&op->source_account, sha256_update_func);
    } else {
        write_bool(false, sha256_update_func);
    }
    write_uint32(op->type, sha256_update_func);
    switch (op->type) {
        case OPERATION_TYPE_CREATE_ACCOUNT:
            write_create_account_op(&op->create_account_op, sha256_update_func);
            break;
        case OPERATION_TYPE_PAYMENT:
            write_payment_op(&op->payment_op, sha256_update_func);
            break;
        case OPERATION_TYPE_PATH_PAYMENT_STRICT_RECEIVE:
            write_path_payment_strict_receive_op(&op->path_payment_strict_receive_op,
                                                 sha256_update_func);
            break;
        case OPERATION_TYPE_MANAGE_SELL_OFFER:
            write_manage_sell_offer_op(&op->manage_sell_offer_op, sha256_update_func);
            break;
        case OPERATION_TYPE_CREATE_PASSIVE_SELL_OFFER:
            write_create_passive_sell_offer_op(&op->create_passive_sell_offer_op,
                                               sha256_update_func);
            break;
        case OPERATION_TYPE_SET_OPTIONS:
            write_set_options_op(&op->set_options_op, sha256_update_func);
            break;
        case OPERATION_TYPE_CHANGE_TRUST:
            write_change_trust_op(&op->change_trust_op, sha256_update_func);
            break;
        case OPERATION_TYPE_ALLOW_TRUST:
            write_allow_trust_op(&op->allow_trust_op, sha256_update_func);
            break;
        case OPERATION_TYPE_ACCOUNT_MERGE:
            write_account_merge_op(&op->account_merge_op, sha256_update_func);
            break;
        case OPERATION_TYPE_INFLATION:
            break;
        case OPERATION_TYPE_MANAGE_DATA:
            write_manage_data_op(&op->manage_data_op, sha256_update_func);
            break;
        case OPERATION_TYPE_BUMP_SEQUENCE:
            write_bump_sequence_op(&op->bump_sequence_op, sha256_update_func);
            break;
        case OPERATION_TYPE_MANAGE_BUY_OFFER:
            write_manage_buy_offer_op(&op->manage_buy_offer_op, sha256_update_func);
            break;
        case OPERATION_TYPE_PATH_PAYMENT_STRICT_SEND:
            write_path_payment_strict_send_op(&op->path_payment_strict_send_op, sha256_update_func);
            break;
        case OPERATION_TYPE_CREATE_CLAIMABLE_BALANCE:
            return write_create_claimable_balance_op(&op->create_claimable_balance_op,
                                                     sha256_update_func);
        case OPERATION_TYPE_CLAIM_CLAIMABLE_BALANCE:
            write_claim_claimable_balance_op(&op->claim_claimable_balance_op, sha256_update_func);
            break;
        case OPERATION_TYPE_BEGIN_SPONSORING_FUTURE_RESERVES:
            write_begin_sponsoring_future_reserves_op(&op->begin_sponsoring_future_reserves_op,
                                                      sha256_update_func);
            break;
        case OPERATION_TYPE_END_SPONSORING_FUTURE_RESERVES:
            break;
        case OPERATION_TYPE_REVOKE_SPONSORSHIP:
            write_revoke_sponsorship_op(&op->revoke_sponsorship_op, sha256_update_func);
            break;
        case OPERATION_TYPE_CLAWBACK:
            write_clawback_op(&op->clawback_op, sha256_update_func);
            break;
        case OPERATION_TYPE_CLAWBACK_CLAIMABLE_BALANCE:
            write_clawback_claimable_balance_op(&op->clawback_claimable_balance_op,
                                                sha256_update_func);
            break;
        case OPERATION_TYPE_SET_TRUST_LINE_FLAGS:
            write_set_trust_line_flags_op(&op->set_trust_line_flags_op, sha256_update_func);
            break;
        case OPERATION_TYPE_LIQUIDITY_POOL_DEPOSIT:
            write_liquidity_pool_deposit_op(&op->liquidity_pool_deposit_op, sha256_update_func);
            break;
        case OPERATION_TYPE_LIQUIDITY_POOL_WITHDRAW:
            write_liquidity_pool_withdraw_op(&op->liquidity_pool_withdraw_op, sha256_update_func);
            break;
        default:
            return false;
    }
    return true;
}

bool write_memo(const memo_t *memo, sha256_update_func sha256_update_func) {
    write_uint32(memo->type, sha256_update_func);
    switch (memo->type) {
        case MEMO_NONE:
            break;
        case MEMO_TEXT:
            write_string(memo->text.text, memo->text.text_size, sha256_update_func);
            break;
        case MEMO_ID:
            write_uint64(memo->id, sha256_update_func);
            break;
        case MEMO_HASH:
            sha256_update_func(memo->hash, 32);
            break;
        case MEMO_RETURN:
            sha256_update_func(memo->return_hash, 32);
            break;
        default:
            return false;
    }
    return true;
}

void write_transaction_source(const muxed_account_t *source,
                              sha256_update_func sha256_update_func) {
    write_muxed_account(source, sha256_update_func);
}

void write_transaction_fee(uint32_t fee, sha256_update_func sha256_update_func) {
    write_uint32(fee, sha256_update_func);
}

void write_transaction_sequence(sequence_number_t sequence_number,
                                sha256_update_func sha256_update_func) {
    write_uint64(sequence_number, sha256_update_func);
}

void write_transaction_preconditions(preconditions_t *preconditions,
                                     sha256_update_func sha256_update_func) {
    write_preconditions(preconditions, sha256_update_func);
}

void write_transaction_memo(memo_t *memo, sha256_update_func sha256_update_func) {
    write_memo(memo, sha256_update_func);
}

void write_transaction_operation_len(uint8_t operations_len,
                                     sha256_update_func sha256_update_func) {
    write_uint32(operations_len, sha256_update_func);
}

void write_transaction_details(const transaction_details_t *transaction_details,
                               sha256_update_func sha256_update_func) {
    write_transaction_source(&transaction_details->source_account, sha256_update_func);
    write_transaction_fee(transaction_details->fee, sha256_update_func);
    write_transaction_sequence(transaction_details->sequence_number, sha256_update_func);
    write_preconditions(&transaction_details->cond, sha256_update_func);
    write_memo(&transaction_details->memo, sha256_update_func);
    write_transaction_operation_len(transaction_details->operations_len, sha256_update_func);
}

void write_transaction_ext(sha256_update_func sha256_update_func) {
    write_uint32(0, sha256_update_func);
}

void write_fee_bump_transaction_fee_source(const muxed_account_t *fee_source,
                                           sha256_update_func sha256_update_func) {
    write_muxed_account(fee_source, sha256_update_func);
}

void write_fee_bump_transaction_fee(int64_t fee, sha256_update_func sha256_update_func) {
    write_uint64(fee, sha256_update_func);
}

void write_fee_bump_transaction_details(
    const fee_bump_transaction_details_t *fee_bump_transaction_details,
    sha256_update_func sha256_update_func) {
    write_fee_bump_transaction_fee_source(&fee_bump_transaction_details->fee_source,
                                          sha256_update_func);
    write_fee_bump_transaction_fee(fee_bump_transaction_details->fee, sha256_update_func);
}

void write_transaction_envelope_type(const envelope_type_t *envelope_type,
                                     sha256_update_func sha256_update_func) {
    write_uint32(*envelope_type, sha256_update_func);
}