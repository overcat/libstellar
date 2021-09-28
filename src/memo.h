#ifndef MEMO_H
#define MEMO_H

#include "stdbool.h"
#include "stellarxdr.h"
enum MemoType {
  MEMO_NONE = 0,
  MEMO_TEXT = 1,
  MEMO_ID = 2,
  MEMO_HASH = 3,
  MEMO_RETURN = 4,
};

struct Memo {
  enum MemoType type;
  union {
    uint64_t id;
    char *text;
    uint8_t hash[32];
    uint8_t return_hash[32];
  };
};

void memo_none(struct Memo *memo);

void memo_text(struct Memo *memo, char *text);

void memo_id(struct Memo *memo, uint64_t id);

void memo_hash(struct Memo *memo, const uint8_t *hash);

void memo_return(struct Memo *memo, const uint8_t *return_hash);

bool memo_to_xdr_object(const struct Memo *in, stellarxdr_Memo *out);

bool memo_from_xdr_object(const stellarxdr_Memo *in, struct Memo *out);

// TODO: remove
bool memo_to_xdr(const struct Memo *in, char **buf, size_t *buf_size);
#endif // MEMO_H
