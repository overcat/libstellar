/**
 * The following APIs allow you to encoded Stellar transactions.
 *
 * if the transaction is of type `ENVELOPE_TYPE_TX`, you should call the following functions
 * in turn to encode the corresponding data:
 *   1. write_transaction_source
 *   2. write_transaction_fee
 *   3. write_transaction_sequence
 *   4. write_transaction_preconditions
 *   5. write_transaction_memo
 *   6. write_transaction_operation_len
 *   7. write_operation (repeat)
 *   8. write_transaction_ext
 *   9. write_decorated_signature_len (optional)
 *   10. write_decorated_signature (repeat, optional)
 * You can directly call the `write_transaction_details` function, which includes steps 1 to 6.
 *
 * if the transaction is of type `ENVELOPE_TYPE_TX_FEE_BUMP`, you should call the following
 * functions in turn to encode the corresponding data:
 *   1. write_fee_bump_transaction_fee_source
 *   2. write_fee_bump_transaction_fee
 *   3. write_transaction_envelope_type (it should always be ENVELOPE_TYPE_TX)
 *   4. write_transaction_source
 *   5. write_transaction_fee
 *   6. write_transaction_sequence
 *   7. write_transaction_preconditions
 *   8. write_transaction_memo
 *   9. write_transaction_operation_len
 *   10. write_operation (repeat)
 *   11. write_transaction_ext
 *   12. write_decorated_signature_len
 *   13. write_decorated_signature (repeat)
 *   14. write_fee_bump_transaction_ext
 *   15 write_decorated_signature_len (optional)
 *   16. write_decorated_signature (repeat, optional)
 * You can directly call the `write_fee_bump_transaction_details` function, which includes steps 1
 * to 2, and can also directly call the `write_transaction_details` function, which includes steps 4
 * to 9.
 */

#ifndef LIBSTELLAR_WRITER_H
#define LIBSTELLAR_WRITER_H
#include <stdint.h>
#include <string.h>

#include "types.h"

/**
 * This function allows you to update the hash object with sha256.
 *
 * e.x.
 * void sha256_update(const uint8_t *data, size_t len) {
 *     func(data, len);
 * }
 *
 */
typedef void (*sha256_update_func)(const uint8_t *, size_t);

bool write_operation(const operation_t *op, sha256_update_func sha256_update_func);

bool write_transaction_source(const muxed_account_t *source, sha256_update_func sha256_update_func);

bool write_transaction_fee(uint32_t fee, sha256_update_func sha256_update_func);

bool write_transaction_sequence(sequence_number_t sequence_number,
                                sha256_update_func sha256_update_func);

bool write_transaction_preconditions(preconditions_t *preconditions,
                                     sha256_update_func sha256_update_func);

bool write_transaction_memo(memo_t *memo, sha256_update_func sha256_update_func);

bool write_transaction_operation_len(uint8_t operations_count,
                                     sha256_update_func sha256_update_func);

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
