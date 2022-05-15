#ifndef NETWORK_H
#define NETWORK_H
#include "vendor/sha256/sha256.h"

extern const char PUBLIC_NETWORK_PASSPHRASE[];
extern const char TESTNET_NETWORK_PASSPHRASE[];

void network_id(const char *networkPassphrase, char *networkId);
#endif // NETWORK_H
