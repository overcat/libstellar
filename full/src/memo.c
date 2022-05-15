#include "memo.h"
#include <stdbool.h>

void memo_none(struct Memo *memo) { memo->type = MEMO_NONE; }

void memo_text(struct Memo *memo, char *text) {
  memo->type = MEMO_TEXT;
  memo->text = text;
}

void memo_id(struct Memo *memo, const uint64_t id) {
  memo->type = MEMO_ID;
  memo->id = id;
}

void memo_hash(struct Memo *memo, const uint8_t *hash) {
  memo->type = MEMO_HASH;
  memcpy(memo->hash, hash, 32);
}

void memo_return(struct Memo *memo, const uint8_t *return_hash) {
  memo->type = MEMO_RETURN;
  memcpy(memo->return_hash, return_hash, 32);
}

bool memo_to_xdr_object(const struct Memo *in, stellarxdr_Memo *out) {
  switch (in->type) {
  case MEMO_NONE:
    out->type = stellarxdr_MEMO_NONE;
    break;
  case MEMO_TEXT:
    out->type = stellarxdr_MEMO_TEXT;
    out->stellarxdr_Memo_u.text = in->text;
    break;
  case MEMO_ID:
    out->type = stellarxdr_MEMO_ID;
    out->stellarxdr_Memo_u.id = in->id;
    break;
  case MEMO_HASH:
    out->type = stellarxdr_MEMO_HASH;
    memcpy(out->stellarxdr_Memo_u.hash, in->hash, 32);
    break;
  case MEMO_RETURN:
    out->type = stellarxdr_MEMO_RETURN;
    memcpy(out->stellarxdr_Memo_u.retHash, in->return_hash, 32);
    break;
  default:
    return false;
  }
  return true;
}

bool memo_from_xdr_object(const stellarxdr_Memo *in, struct Memo *out) {
  switch (in->type) {
  case stellarxdr_MEMO_NONE:
    out->type = MEMO_NONE;
    break;
  case stellarxdr_MEMO_TEXT:
    out->type = MEMO_TEXT;
    out->text = in->stellarxdr_Memo_u.text;
    break;
  case stellarxdr_MEMO_ID:
    out->type = MEMO_ID;
    out->id = in->stellarxdr_Memo_u.id;
    break;
  case stellarxdr_MEMO_HASH:
    out->type = MEMO_HASH;
    memcpy(out->hash, in->stellarxdr_Memo_u.hash, 32);
    break;
  case stellarxdr_MEMO_RETURN:
    out->type = MEMO_RETURN;
    memcpy(out->return_hash, in->stellarxdr_Memo_u.retHash, 32);
    break;
  default:
    return false;
  }
  return true;
}

// TODO: remove
bool memo_to_xdr(const struct Memo *in, char **buf, size_t *buf_size) {
  stellarxdr_Memo memo_xdr;
  memo_to_xdr_object(in, &memo_xdr);
  FILE *fp = open_memstream(buf, buf_size);
  XDR xdr;
  xdrstdio_create(&xdr, fp, XDR_ENCODE);
  if (!xdr_stellarxdr_Memo(&xdr, &memo_xdr)) {
    fclose(fp);
    return false;
  }
  fclose(fp);
  return true;
}