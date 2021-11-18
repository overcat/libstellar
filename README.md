# c-stellar-base

`c-stellar-base` is a pure C library for parsing and building Stellar transactions, our goal is to make it run on embedded devices, such as hardware wallets.

## Motivation

When I was contributing code to the [Ledger Wallet](https://github.com/LedgerHQ/app-stellar) and [Trezor Wallet](https://github.com/trezor/trezor-firmware/), 
I found that each wallet had to write repetitive code to parse and build Stellar transactions, 
so I hope to write this library to speed up the efficiency of integrating Stellar into various hardware devices.
