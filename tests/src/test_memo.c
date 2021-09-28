#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "../../src/memo.h"
#include <cmocka.h>

void test_memo_none(void **state) {
  struct Memo memo;
  memo_none(&memo);
  assert_int_equal(memo.type, MEMO_NONE);
  stellarxdr_Memo memo_to;
  memo_to_xdr_object(&memo, &memo_to);
  assert_int_equal(memo_to.type, stellarxdr_MEMO_NONE);
  struct Memo memo_from;
  memo_from_xdr_object(&memo_to, &memo_from);
  assert_int_equal(memo_from.type, MEMO_NONE);
  // TODO: remove
  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(memo_to_xdr(&memo, &buf, &buf_size));
  char m[] = {0, 0, 0, 0};
  assert_memory_equal(buf, m, 4);
}

void test_memo_text(void **state) {
  // TODO: char or uint8
  struct Memo memo;
  char text[] = "Hello Stellar";
  memo_text(&memo, text);
  assert_int_equal(memo.type, MEMO_TEXT);
  assert_memory_equal(memo.text, text, 16);
  stellarxdr_Memo memo_to;

  memo_to_xdr_object(&memo, &memo_to);
  assert_int_equal(memo_to.type, stellarxdr_MEMO_TEXT);
  assert_memory_equal(memo_to.stellarxdr_Memo_u.text, text, 16);
  struct Memo memo_from;
  memo_from_xdr_object(&memo_to, &memo_from);
  assert_int_equal(memo_from.type, MEMO_TEXT);
  assert_memory_equal(memo_from.text, text, 16);

  // TODO: remove
  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(memo_to_xdr(&memo, &buf, &buf_size));
  char m[] = {0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0xd,
              0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x53, 0x74,
              0x65, 0x6c, 0x6c, 0x61, 0x72, 0x0,  0x0,  0x0};
  assert_memory_equal(buf, m, 24);
}

void test_memo_id(void **state) {
  struct Memo memo;
  uint64_t id = 1234567890;
  memo_id(&memo, id);
  assert_int_equal(memo.type, MEMO_ID);
  assert_int_equal(memo.id, id);
  stellarxdr_Memo memo_to;

  memo_to_xdr_object(&memo, &memo_to);
  assert_int_equal(memo_to.type, stellarxdr_MEMO_ID);
  assert_int_equal(memo_to.stellarxdr_Memo_u.id, id);
  struct Memo memo_from;
  memo_from_xdr_object(&memo_to, &memo_from);
  assert_int_equal(memo_from.type, MEMO_ID);
  assert_int_equal(memo_from.id, id);
}

void test_memo_hash(void **state) {
  struct Memo memo;
  uint8_t hash[] = {0xad, 0xe1, 0xc1, 0x53, 0xe7, 0xf5, 0x1d, 0x1a,
                    0x76, 0xa4, 0x55, 0xb4, 0x18, 0x56, 0xc4, 0xcb,
                    0x1b, 0x77, 0x26, 0x4,  0x7c, 0x6f, 0x6d, 0xac,
                    0xbb, 0x81, 0xe9, 0x88, 0xef, 0x6b, 0x7,  0xeb};
  memo_hash(&memo, hash);
  assert_int_equal(memo.type, MEMO_HASH);
  assert_memory_equal(memo.hash, hash, 32);
  stellarxdr_Memo memo_to;

  memo_to_xdr_object(&memo, &memo_to);
  assert_int_equal(memo_to.type, stellarxdr_MEMO_HASH);
  assert_memory_equal(memo_to.stellarxdr_Memo_u.hash, hash, 32);

  struct Memo memo_from;
  memo_from_xdr_object(&memo_to, &memo_from);
  assert_int_equal(memo_from.type, MEMO_HASH);
  assert_memory_equal(memo_from.hash, hash, 32);
}

void test_memo_return_hash(void **state) {
  struct Memo memo;
  uint8_t return_hash[] = {0xad, 0xe1, 0xc1, 0x53, 0xe7, 0xf5, 0x1d, 0x1a,
                           0x76, 0xa4, 0x55, 0xb4, 0x18, 0x56, 0xc4, 0xcb,
                           0x1b, 0x77, 0x26, 0x4,  0x7c, 0x6f, 0x6d, 0xac,
                           0xbb, 0x81, 0xe9, 0x88, 0xef, 0x6b, 0x7,  0xeb};
  memo_return(&memo, return_hash);
  assert_int_equal(memo.type, MEMO_RETURN);
  assert_memory_equal(memo.hash, return_hash, 32);
  stellarxdr_Memo memo_to;

  memo_to_xdr_object(&memo, &memo_to);
  assert_int_equal(memo_to.type, stellarxdr_MEMO_RETURN);
  assert_memory_equal(memo_to.stellarxdr_Memo_u.hash, return_hash, 32);

  struct Memo memo_from;
  memo_from_xdr_object(&memo_to, &memo_from);
  assert_int_equal(memo_from.type, MEMO_RETURN);
  assert_memory_equal(memo_from.hash, return_hash, 32);
}

int main() {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_memo_none),        cmocka_unit_test(test_memo_text),
      cmocka_unit_test(test_memo_id),          cmocka_unit_test(test_memo_hash),
      cmocka_unit_test(test_memo_return_hash),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
