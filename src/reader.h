/**
 * The following APIs allow you to decode encoded Stellar transactions.
 *
 * First you should call `read_transaction_envelope_type` to determine what type of
 * transaction is, currently two types are supported.
 *
 * if it is of type `ENVELOPE_TYPE_TX`, you should call the following functions
 * in turn to get the corresponding data:
 *   1. read_transaction_source
 *   2. read_transaction_fee
 *   3. read_transaction_sequence
 *   4. read_transaction_preconditions
 *   5. read_transaction_memo
 *   6. read_transaction_operation_len
 *   7. read_operation (repeat)
 *   8. read_transaction_ext
 *   9. read_decorated_signature_len (optional)
 *   10. read_decorated_signature (repeat, optional)
 * You can directly call the `read_transaction_details` function, which includes steps 1 to 6.
 *
 * if it is of type `ENVELOPE_TYPE_TX_FEE_BUMP`, you should call the following functions
 * in turn to get the corresponding data:
 *   1. read_fee_bump_transaction_fee_source
 *   2. read_fee_bump_transaction_fee
 *   3. read_transaction_envelope_type (it should always be ENVELOPE_TYPE_TX)
 *   4. read_transaction_source
 *   5. read_transaction_fee
 *   6. read_transaction_sequence
 *   7. read_transaction_preconditions
 *   8. read_transaction_memo
 *   9. read_transaction_operation_len
 *   10. read_operation (repeat)
 *   11. read_transaction_ext
 *   12. read_decorated_signature_len
 *   13. read_decorated_signature (repeat)
 *   14. read_fee_bump_transaction_ext
 *   15 read_decorated_signature_len (optional)
 *   16. read_decorated_signature (repeat, optional)
 * You can directly call the `read_fee_bump_transaction_details` function, which includes steps 1 to
 * 2, and can also directly call the `read_transaction_details` function, which includes steps 4
 * to 9.
 */

#ifndef LIBSTELLAR_READER_H
#define LIBSTELLAR_READER_H
#include <stdint.h>
#include <string.h>

#include "types.h"

typedef bool (*xdr_type_reader)(buffer_t *, void *);

bool read_operation(buffer_t *buffer, operation_t *operation);

bool read_transaction_source(buffer_t *buffer, muxed_account_t *source);

bool read_transaction_fee(buffer_t *buffer, uint32_t *fee);

bool read_transaction_sequence(buffer_t *buffer, sequence_number_t *sequence_number);

bool read_transaction_preconditions(buffer_t *buffer, preconditions_t *preconditions);

bool read_transaction_memo(buffer_t *buffer, memo_t *memo);

bool read_transaction_operation_len(buffer_t *buffer, uint8_t *operations_count);

bool read_transaction_details(buffer_t *buffer, transaction_details_t *transaction);

bool read_transaction_ext(buffer_t *buffer);

bool read_decorated_signature_len(buffer_t *buffer, uint8_t *len);

bool read_decorated_signature(buffer_t *buffer, decorated_signature_t *decorated_signature);

bool read_fee_bump_transaction_fee_source(buffer_t *buffer, muxed_account_t *fee_source);

bool read_fee_bump_transaction_fee(buffer_t *buffer, int64_t *fee);

bool read_fee_bump_transaction_details(buffer_t *buffer,
                                       fee_bump_transaction_details_t *feeBumpTransaction);

bool read_fee_bump_transaction_ext(buffer_t *buffer);

bool read_transaction_envelope_type(buffer_t *buffer, envelope_type_t *envelope_type);

#ifdef TEST
bool read_signer_key(buffer_t *buffer, signer_key_t *key);
#endif  // TEST

#endif  // LIBSTELLAR_READER_H
