#include "network.h"
#include "string.h"

const char PUBLIC_NETWORK_PASSPHRASE[] =
    "Public Global Stellar Network ; September 2015";
const char TESTNET_NETWORK_PASSPHRASE[] = "Test SDF Network ; September 2015";

void network_id(const char *networkPassphrase, char *networkId) {
  SHA256_CTX sha256;
  sha256_init(&sha256);
  sha256_update(&sha256, networkPassphrase, strlen(networkPassphrase));
  sha256_final(&sha256, networkId);
}