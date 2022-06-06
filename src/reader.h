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

bool read_transaction_operation_len(buffer_t *buffer, uint8_t *operations_len);

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
