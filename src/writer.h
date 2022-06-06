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

bool write_operation(const operation_t *op, sha256_update_func sha256_update_func);

bool write_transaction_source(const muxed_account_t *source, sha256_update_func sha256_update_func);

bool write_transaction_fee(uint32_t fee, sha256_update_func sha256_update_func);

bool write_transaction_sequence(sequence_number_t sequence_number,
                                sha256_update_func sha256_update_func);

bool write_transaction_preconditions(preconditions_t *preconditions,
                                     sha256_update_func sha256_update_func);

bool write_transaction_memo(memo_t *memo, sha256_update_func sha256_update_func);

bool write_transaction_operation_len(uint8_t operations_len, sha256_update_func sha256_update_func);

bool write_transaction_details(const transaction_details_t *transaction_details,
                               sha256_update_func sha256_update_func);

bool write_transaction_ext(sha256_update_func sha256_update_func);

bool write_decorated_signature_len(uint8_t len, sha256_update_func sha256_update_func);

bool write_decorated_signature(const decorated_signature_t *decorated_signature,
                               sha256_update_func sha256_update_func);

bool write_fee_bump_transaction_fee_source(const muxed_account_t *fee_source,
                                           sha256_update_func sha256_update_func);

bool write_fee_bump_transaction_fee(int64_t fee, sha256_update_func sha256_update_func);

bool write_fee_bump_transaction_details(
    const fee_bump_transaction_details_t *fee_bump_transaction_details,
    sha256_update_func sha256_update_func);

bool write_fee_bump_transaction_ext(sha256_update_func sha256_update_func);

bool write_transaction_envelope_type(envelope_type_t envelope_type,
                                     sha256_update_func sha256_update_func);

#ifdef TEST
bool write_signer_key(const signer_key_t *signer_key, sha256_update_func sha256_update_func);
#endif  // TEST

#endif  // LIBSTELLAR_WRITER_H
