#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "include/base32.h"
#include "include/base58.h"
#include "include/format.h"

#define MUXED_ACCOUNT_MED_25519_SIZE 43
#define BINARY_MAX_SIZE              36
static const char base64Alphabet[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static int base64ModTable[] = {0, 2, 1};

bool base64_encode(const uint8_t *data, size_t in_len, char *out, size_t out_len) {
    size_t encoded_len = 4 * ((in_len + 2) / 3);
    if (encoded_len > out_len) {
        return false;
    }

    for (unsigned int i = 0, j = 0; i < in_len;) {
        uint32_t octet_a = i < in_len ? data[i++] : 0;
        uint32_t octet_b = i < in_len ? data[i++] : 0;
        uint32_t octet_c = i < in_len ? data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        out[j++] = base64Alphabet[(triple >> 3 * 6) & 0x3F];
        out[j++] = base64Alphabet[(triple >> 2 * 6) & 0x3F];
        out[j++] = base64Alphabet[(triple >> 1 * 6) & 0x3F];
        out[j++] = base64Alphabet[(triple >> 0 * 6) & 0x3F];
    }

    int i;
    for (i = 0; i < base64ModTable[in_len % 3]; i++) {
        out[encoded_len - 1 - i] = '=';
    }

    out[encoded_len] = '\0';
    return true;
}

uint16_t crc16(const uint8_t *input_str, int num_bytes) {
    int crc;
    crc = 0;
    while (--num_bytes >= 0) {
        crc = crc ^ (int) *input_str++ << 8;
        int i = 8;
        do {
            if (crc & 0x8000)
                crc = crc << 1 ^ 0x1021;
            else
                crc = crc << 1;
        } while (--i);
    }
    return crc;
}

bool encode_key(const uint8_t *in, uint8_t version_byte, char *out, uint8_t out_len) {
    if (out_len < 56 + 1) {
        return false;
    }
    uint8_t buffer[35];
    buffer[0] = version_byte;
    for (uint8_t i = 0; i < 32; i++) {
        buffer[i + 1] = in[i];
    }
    uint16_t crc = crc16(buffer, 33);  // checksum
    buffer[33] = crc;
    buffer[34] = crc >> 8;
    if (base32_encode(buffer, 35, (uint8_t *) out, 56) == -1) {
        return false;
    }
    out[56] = '\0';
    return true;
}

bool encode_ed25519_public_key(const uint8_t raw_public_key[static RAW_ED25519_PUBLIC_KEY_SIZE],
                               char *out,
                               size_t out_len) {
    return encode_key(raw_public_key, VERSION_BYTE_ED25519_PUBLIC_KEY, out, out_len);
}

bool encode_hash_x_key(const uint8_t raw_hash_x[static RAW_HASH_X_KEY_SIZE],
                       char *out,
                       size_t out_len) {
    return encode_key(raw_hash_x, VERSION_BYTE_HASH_X, out, out_len);
}

bool encode_pre_auth_x_key(const uint8_t raw_pre_auth_tx[static RAW_PRE_AUTH_TX_KEY_SIZE],
                           char *out,
                           size_t out_len) {
    return encode_key(raw_pre_auth_tx, VERSION_BYTE_PRE_AUTH_TX_KEY, out, out_len);
}

bool encode_muxed_account(const muxed_account_t *raw_muxed_account, char *out, size_t out_len) {
    if (raw_muxed_account->type == KEY_TYPE_ED25519) {
        return encode_ed25519_public_key(raw_muxed_account->ed25519, out, out_len);
    } else {
        if (out_len < ENCODED_MUXED_ACCOUNT_KEY_LENGTH) {
            return false;
        }
        uint8_t buffer[MUXED_ACCOUNT_MED_25519_SIZE];
        buffer[0] = VERSION_BYTE_MUXED_ACCOUNT;
        memcpy(buffer + 1, raw_muxed_account->med25519.ed25519, RAW_ED25519_PUBLIC_KEY_SIZE);
        for (int i = 0; i < 8; i++) {
            buffer[33 + i] = raw_muxed_account->med25519.id >> 8 * (7 - i);
        }
        uint16_t crc = crc16(buffer, MUXED_ACCOUNT_MED_25519_SIZE - 2);  // checksum
        buffer[41] = crc;
        buffer[42] = crc >> 8;
        if (base32_encode(buffer,
                          MUXED_ACCOUNT_MED_25519_SIZE,
                          (uint8_t *) out,
                          ENCODED_MUXED_ACCOUNT_KEY_LENGTH) == -1) {
            return false;
        }
        out[69] = '\0';
        return true;
    }
}

bool print_summary(const char *in,
                   char *out,
                   size_t out_len,
                   uint8_t num_chars_l,
                   uint8_t num_chars_r) {
    uint8_t result_len = num_chars_l + num_chars_r + 2;
    if (out_len < result_len + 1) {
        return false;
    }
    uint16_t in_len = strlen(in);
    if (in_len > result_len) {
        memcpy(out, in, num_chars_l);
        out[num_chars_l] = '.';
        out[num_chars_l + 1] = '.';
        memcpy(out + num_chars_l + 2, in + in_len - num_chars_r, num_chars_r);
        out[result_len] = '\0';
    } else {
        memcpy(out, in, in_len);
        out[in_len] = '\0';
    }
    return true;
}

bool print_binary(const uint8_t *in,
                  size_t in_len,
                  char *out,
                  size_t out_len,
                  uint8_t num_chars_l,
                  uint8_t num_chars_r) {
    if (num_chars_l > 0) {
        char buffer[BINARY_MAX_SIZE * 2 + 1];  // FIXME
        if (!format_hex(in, in_len, buffer, sizeof(buffer))) {
            return false;
        }
        return print_summary(buffer, out, out_len, num_chars_l, num_chars_r);
    }
    return format_hex(in, in_len, out, out_len);
}

bool print_account_id(const account_id_t account_id,
                      char *out,
                      size_t out_len,
                      uint8_t num_chars_l,
                      uint8_t num_chars_r) {
    if (num_chars_l > 0) {
        char buffer[ENCODED_ED25519_PUBLIC_KEY_LENGTH];
        if (!encode_ed25519_public_key(account_id, buffer, sizeof(buffer))) {
            return false;
        }
        return print_summary(buffer, out, out_len, num_chars_l, num_chars_r);
    }
    return encode_ed25519_public_key(account_id, out, out_len);
}

bool print_muxed_account(const muxed_account_t *muxed_account,
                         char *out,
                         size_t out_len,
                         uint8_t num_chars_l,
                         uint8_t num_chars_r) {
    if (num_chars_l > 0) {
        char buffer[ENCODED_MUXED_ACCOUNT_KEY_LENGTH];
        if (!encode_muxed_account(muxed_account, buffer, sizeof(buffer))) {
            return false;
        }
        return print_summary(buffer, out, out_len, num_chars_l, num_chars_r);
    }
    return encode_muxed_account(muxed_account, out, out_len);
}

bool print_claimable_balance_id(const claimable_balance_id_t *claimable_balance_id,
                                char *out,
                                size_t out_len) {
    if (out_len < 36 * 2 + 1) {
        return false;
    }
    uint8_t data[36];
    memcpy(data, &claimable_balance_id->type, 4);
    memcpy(data + 4, claimable_balance_id->v0, 32);
    return print_binary(data, 36, out, out_len, 0, 0);
}

bool print_uint(uint64_t num, char *out, size_t out_len) {
    char buffer[AMOUNT_MAX_LENGTH];
    uint64_t d_val = num;
    size_t i, j;

    if (num == 0) {
        if (out_len < 2) {
            return false;
        }
        strlcpy(out, "0", out_len);
        return true;
    }

    memset(buffer, 0, AMOUNT_MAX_LENGTH);
    for (i = 0; d_val > 0; i++) {
        if (i >= AMOUNT_MAX_LENGTH) {
            return false;
        }
        buffer[i] = (d_val % 10) + '0';
        d_val /= 10;
    }
    if (out_len <= i) {
        return false;
    }
    // reverse order
    for (j = 0; j < i; j++) {
        out[j] = buffer[i - j - 1];
    }
    out[i] = '\0';
    return true;
}

bool print_int(int64_t num, char *out, size_t out_len) {
    if (out_len == 0) {
        return false;
    }
    if (num < 0) {
        out[0] = '-';
        return print_uint(-num, out + 1, out_len - 1);
    }
    return print_uint(num, out, out_len);
}

bool print_time(uint64_t seconds, char *out, size_t out_len) {
    if (seconds > 253402300799) {
        // valid range 1970-01-01 00:00:00 - 9999-12-31 23:59:59
        return false;
    }
    char time_str[20] = {0};  // 1970-01-01 00:00:00

    if (out_len < sizeof(time_str)) {
        return false;
    }
    struct tm tm;
    if (!gmtime_r((time_t *) &seconds, &tm)) {
        return false;
    };

    if (snprintf(time_str,
                 sizeof(time_str),
                 "%04d-%02d-%02d %02d:%02d:%02d",
                 tm.tm_year + 1900,
                 tm.tm_mon + 1,
                 tm.tm_mday,
                 tm.tm_hour,
                 tm.tm_min,
                 tm.tm_sec) < 0) {
        return false;
    };
    strlcpy(out, time_str, out_len);
    return true;
}

bool print_asset_name(const asset_t *asset, char *out, size_t out_len) {
    switch (asset->type) {
        case ASSET_TYPE_NATIVE:
            strlcpy(out, "XLM", out_len);
            return true;
        case ASSET_TYPE_CREDIT_ALPHANUM4:
            for (int i = 0; i < 4; i++) {
                out[i] = asset->alpha_num4.asset_code[i];
                if (out[i] == 0) {
                    break;
                }
            }
            out[4] = 0;
            return true;
        case ASSET_TYPE_CREDIT_ALPHANUM12:
            for (int i = 0; i < 12; i++) {
                out[i] = asset->alpha_num12.asset_code[i];
                if (out[i] == 0) {
                    break;
                }
            }
            out[12] = 0;
            return true;
        default:
            return false;
    }
}

bool print_asset(const asset_t *asset, char *out, size_t out_len) {
    char asset_code[12 + 1];
    char asset_issuer[3 + 2 + 4 + 1];
    print_asset_name(asset, asset_code, sizeof(asset_code));

    switch (asset->type) {
        case ASSET_TYPE_CREDIT_ALPHANUM4:
            print_account_id(asset->alpha_num4.issuer, asset_issuer, sizeof(asset_issuer), 3, 4);
            break;
        case ASSET_TYPE_CREDIT_ALPHANUM12:
            print_account_id(asset->alpha_num12.issuer, asset_issuer, sizeof(asset_issuer), 3, 4);
            break;
        default:
            break;
    }
    strlcpy(out, asset_code, out_len);
    if (asset->type != ASSET_TYPE_NATIVE) {
        strlcat(out, "@", out_len);
        strlcat(out, asset_issuer, out_len);
    }
    return true;
}

static void print_flag(char *flag, char *out, size_t out_len) {
    if (out[0]) {
        strlcat(out, ", ", out_len);
    }
    strlcat(out, flag, out_len);
}

void print_flags(uint32_t flags, char *out, size_t out_len) {
    if (flags & 0x01u) {
        print_flag("Auth required", out, out_len);
    }
    if (flags & 0x02u) {
        print_flag("Auth revocable", out, out_len);
    }
    if (flags & 0x04u) {
        print_flag("Auth immutable", out, out_len);
    }
}

void print_trust_line_flags(uint32_t flags, char *out, size_t out_len) {
    if (flags & AUTHORIZED_FLAG) {
        print_flag("AUTHORIZED", out, out_len);
    }
    if (flags & AUTHORIZED_TO_MAINTAIN_LIABILITIES_FLAG) {
        print_flag("AUTHORIZED_TO_MAINTAIN_LIABILITIES", out, out_len);
    }
    if (flags & TRUSTLINE_CLAWBACK_ENABLED_FLAG) {
        print_flag("TRUSTLINE_CLAWBACK_ENABLED", out, out_len);
    }
}

bool print_amount(uint64_t amount, const asset_t *asset, char *out, size_t out_len) {
    char buffer[AMOUNT_MAX_LENGTH] = {0};
    uint64_t dVal = amount;
    int i;

    for (i = 0; dVal > 0 || i < 9; i++) {
        if (dVal > 0) {
            buffer[i] = (dVal % 10) + '0';
            dVal /= 10;
        } else {
            buffer[i] = '0';
        }
        if (i == 6) {  // stroops to xlm: 1 xlm = 10000000 stroops
            i += 1;
            buffer[i] = '.';
        }
        if (i >= AMOUNT_MAX_LENGTH) {
            return false;
        }
    }

    // reverse order
    for (int j = 0; j < i / 2; j++) {
        char c = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = c;
    }

    // strip trailing 0s
    i -= 1;
    while (buffer[i] == '0') {
        buffer[i] = 0;
        i -= 1;
    }
    // strip trailing .
    if (buffer[i] == '.') buffer[i] = 0;
    strlcpy(out, buffer, out_len);

    char assetInfo[23];  // BANANANANANA@GBD..KHK4, 12 + 1 + 3 + 2 + 4 = 22

    if (asset) {
        // qualify amount
        if (!print_asset(asset, assetInfo, 23)) {
            return false;
        };
        strlcat(out, " ", out_len);
        strlcat(out, assetInfo, out_len);
    }
    return true;
}