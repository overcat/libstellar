#include "transaction_envelope.h"

bool transaction_envelope_to_xdr_object(const struct TransactionEnvelope *in,
                                        stellarxdr_TransactionEnvelope *out) {
  stellarxdr_Transaction stellarxdrTransaction;
  transaction_to_xdr_object(&in->transaction, &stellarxdrTransaction);

  out->type = stellarxdr_ENVELOPE_TYPE_TX;
  out->stellarxdr_TransactionEnvelope_u.v1.tx = stellarxdrTransaction;
  out->stellarxdr_TransactionEnvelope_u.v1.signatures.signatures_len =
      in->signatures_len;
  out->stellarxdr_TransactionEnvelope_u.v1.signatures.signatures_val =
      malloc(in->signatures_len * sizeof(stellarxdr_DecoratedSignature));
  for (int i = 0; i < in->signatures_len; i++) {
    struct stellarxdr_DecoratedSignature stellarxdrDecoratedSignature;
    if (!decorated_signature_to_xdr_object(in->signatures + i,
                                           &stellarxdrDecoratedSignature)) {
      return false;
    }
    memcpy(
        out->stellarxdr_TransactionEnvelope_u.v1.signatures.signatures_val + i,
        &stellarxdrDecoratedSignature, sizeof(stellarxdr_DecoratedSignature));
  }
  return true;
};

bool transaction_envelope_from_xdr_object(
    const stellarxdr_TransactionEnvelope *in, struct TransactionEnvelope *out) {
  out->signatures_len =
      in->stellarxdr_TransactionEnvelope_u.v1.signatures.signatures_len;
  struct Transaction transaction;
  if (!transaction_from_xdr_object(&in->stellarxdr_TransactionEnvelope_u.v1.tx,
                                   &transaction)) {
    return false;
  }
  out->signatures =
      malloc(out->signatures_len * sizeof(struct DecoratedSignature));
  for (int i = 0; i < out->signatures_len; i++) {
    struct DecoratedSignature decoratedSignature;
    if (!decorated_signature_from_xdr_object(
            in->stellarxdr_TransactionEnvelope_u.v1.signatures.signatures_val +
                i,
            &decoratedSignature)) {
      return false;
    }
    memcpy(out->signatures + i, &decoratedSignature,
           sizeof(stellarxdr_DecoratedSignature));
  }
  return true;
  //    out->transaction = transaction_from_xdr_object()
};

bool transaction_envelope_hash(struct TransactionEnvelope *transactionEnvelope,
                               char *hash) {
  char networkId[32];
  network_id(transactionEnvelope->networkPassphrase, networkId);
  SHA256_CTX sha256;
  char data[] = {0x0, 0x0, 0x0, 0x2};
  char xdr[] = {
      0x0,  0x0,  0x0,  0x0,  0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff, 0x7,  0x57,
      0x3b, 0x97, 0x74, 0xcd, 0x32, 0x2e, 0x74, 0x46, 0xa5, 0xc9, 0x30, 0x5f,
      0x99, 0x49, 0x6,  0xbd, 0xfc, 0x74, 0xdb, 0x7d, 0x6e, 0x1d, 0x9d, 0x12,
      0x0,  0x0,  0x0,  0x64, 0x0,  0x0,  0x0,  0x0,  0x49, 0x96, 0x2,  0xd2,
      0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
      0x0,  0x0,  0x0,  0x0,  0x61, 0x53, 0xd8, 0x7b, 0x0,  0x0,  0x0,  0x1,
      0x0,  0x0,  0x0,  0xf,  0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x53,
      0x74, 0x65, 0x6c, 0x6c, 0x61, 0x72, 0x21, 0x0,  0x0,  0x0,  0x0,  0x1,
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0xb,  0x0,  0x0,  0x0,  0x0,
      0x49, 0x96, 0x2,  0xd2, 0x0,  0x0,  0x0,  0x0};
  sha256_init(&sha256);
  sha256_update(&sha256, networkId, 32);
  sha256_update(&sha256, data, sizeof data);
  sha256_update(&sha256, xdr, sizeof xdr);
  sha256_final(&sha256, hash);
}

// bool transaction_envelope_sign(const struct Keypair *signer, struct
// TransactionEnvelope *TransactionEnvelope){
//   SHA256_CTX sha256;
//   sha256_init(&sha256);
//   sha256_update(&sha256, networkPassphrase, strlen(networkPassphrase));
//   sha256_final(&sha256, networkId);
// }