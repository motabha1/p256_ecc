# p256_ecc
 Elliptic curve key exchange on NIST P256 

## Parameters

- By the FIPS 186-2 standard, I have taken the elliptic curve over prime p = 2^256 - 2^224 + 2^192 + 2^96 - 1
- EC : y^2 = x^3 + Ax + B
- Parameters:
    - P256 = 0xFFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF
    - A = 0xFFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFC
    - B = 0x5AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B
    - Gx = 0x6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296
    - Gy = 0x4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5
- Here (Gx, Gy) is the base point

- These parameters were chosen from [here](https://www.secg.org/SEC2-Ver-1.0.pdf)

## Organisation

| File  | Description |
| :---: | :---:       |
| utility | contains parameters, utility functions |
| field_arithmetic | contains arithmetic operations in F_p |
| ec_arithmetic | contains arithmetic over points of Elliptic curve | 
| test | file that tests all the functionalities |
| main | runner function that can test the functionalities | 

## Instructions

This file for now contains only the code to test the functionality
If you want to exchange a secret given private key inputs, that can be easily added by changing the test_field() method in the test.cpp to output the shared secret instead of simply checking the validity. 

```
git clone https://github.com/motabha1/p256_ecc.git
cd p256_ecc
./run

```

## References

> Darrel Hankerson, Alfred J. Menezes, and Scott Vanstone. 2010. Guide to Elliptic Curve Cryptography (1st. ed.). Springer Publishing Company, Incorporated

> [https://kel.bz/post/sage-p256/](https://kel.bz/post/sage-p256/)

> Adalier, M., & Teknik, A. (2015). Efficient and Secure Elliptic Curve Cryptography Implementation of Curve P-256.