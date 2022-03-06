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
    const stellarxdr_TransactionEnvelope *in, struct TransactionEnvelope *out,
    char *networkPassphrase) {

  struct Transaction transaction;
  if (!transaction_from_xdr_object(&in->stellarxdr_TransactionEnvelope_u.v1.tx,
                                   &transaction)) {
    return false;
  }
  out->transaction = transaction;

  out->signatures_len =
      in->stellarxdr_TransactionEnvelope_u.v1.signatures.signatures_len;
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
           sizeof(struct DecoratedSignature));
  }
  out->networkPassphrase = malloc(strlen(networkPassphrase) + 1);
  strcpy(out->networkPassphrase, networkPassphrase);
  return true;
};

bool transaction_envelope_hash(struct TransactionEnvelope *transactionEnvelope,
                               unsigned char *hash) {
  char networkId[32];
  network_id(transactionEnvelope->networkPassphrase, networkId);
  SHA256_CTX sha256;
  char txType[] = {0x0, 0x0, 0x0, 0x2}; // stellarxdr_ENVELOPE_TYPE_TX

  char *buf = NULL;
  size_t buf_size = 0;
  stellarxdr_Transaction transaction_xdr;
  if (!transaction_to_xdr_object(&transactionEnvelope->transaction,
                                 &transaction_xdr)) {
    return false;
  }
  FILE *fp = open_memstream(&buf, &buf_size);
  XDR xdr;
  xdrstdio_create(&xdr, fp, XDR_ENCODE);
  if (!xdr_stellarxdr_Transaction(&xdr, &transaction_xdr)) {
    fclose(fp);
    return false;
  }
  if (fclose(fp) != 0) {
    return false;
  };

  sha256_init(&sha256);
  sha256_update(&sha256, networkId, 32);
  sha256_update(&sha256, txType, sizeof txType);
  sha256_update(&sha256, buf, buf_size);
  sha256_final(&sha256, hash);
  return true;
}

bool transaction_envelope_sign(
    const struct Keypair *signer,
    struct TransactionEnvelope *transactionEnvelope) {
  unsigned char hash[32];
  if (!transaction_envelope_hash(transactionEnvelope, hash)) {
    return false;
  };

  uint8_t signature[64];
  if (!keypair_sign(signer, signature, hash, sizeof hash)) {
    return false;
  };

  uint8_t signatureHint[4];
  if (!keypair_signature_hint(signer, signatureHint)) {
    return false;
  }

  struct DecoratedSignature decoratedSignature;
  memcpy(decoratedSignature.signatureHint, signatureHint, 4);
  memcpy(decoratedSignature.signature, signature, 64);
  transactionEnvelope->signatures =
      realloc(transactionEnvelope->signatures,
              (transactionEnvelope->signatures_len + 1) *
                  sizeof(struct DecoratedSignature));
  memcpy(transactionEnvelope->signatures + transactionEnvelope->signatures_len,
         &decoratedSignature, sizeof(struct DecoratedSignature));
  transactionEnvelope->signatures_len += 1;
  return true;
}