# libstellar

`libstellar` is a pure C library for parsing and building Stellar transactions, our goal is to make it run on embedded
devices, such as hardware wallets.

## How to use

Currently, there are two methods for processing Stellar transactions on hardware wallets:

1. send the entire XDR to the wallet, you can parse this XDR through this library to show the transaction
   information to the user, if the user approves the transaction, you need to get the transaction hash through
   this XDR, sign it, and finally return the signature, Ledger wallet uses this method, if you want to use it too,
   start from `src/reader.h`.

2. send the transaction information (such as source, fee and operations, etc, due to memory constraints, a transaction
   is usually split into multiple details and sent separately) to the wallet,
   the wallet needs to assemble these information to get the hash of the transaction, and return the signature,
   Trezor wallet uses this method, if you want to use it too, start from `src/writer.h`.

