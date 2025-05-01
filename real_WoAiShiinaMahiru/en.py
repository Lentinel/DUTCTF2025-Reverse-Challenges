def wrapping_add(x, y):
    return (x + y) & 0xFF

def wrapping_mul(x, y):
    return (x * y) & 0xFF

def modified_WTF_encrypt(input_bytes: bytes, key: bytes) -> bytes:
    s = [0] * 256
    seed = 0x42
    for i in range(256):
        seed = wrapping_mul(seed, 31)
        seed = wrapping_add(seed, i)
        s[i] = seed

    j = 0
    for i in range(256):
        j ^= s[i] ^ key[i % len(key)]
        j = wrapping_add(j, s[i])
        s[i], s[j] = s[j], s[i]

    i = 0
    j = 0
    output = bytearray()

    for byte in input_bytes:
        i = wrapping_add(i, 1)
        j = wrapping_add(j, s[i])
        s[i], s[j] = s[j], s[i]
        k = s[(s[i] + s[j]) % 256]
        encrypted = (byte ^ (k ^ 0x5A))
        output.append(encrypted)

    return bytes(output)

if __name__ == "__main__":
    # 你自己的 flag
    flag = b"DUTCTF{680b46b5-2cec-800e-9128-2151eb44ccf7}"
    key = b"CIPPUSSSS"

    ciphertext = modified_WTF_encrypt(flag, key)
    print("Ciphertext bytes:")
    print(list(ciphertext))  # 直接打印方便替换到 Rust
