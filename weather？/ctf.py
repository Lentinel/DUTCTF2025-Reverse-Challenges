import base64

# 自定义 Base64 表
custom_b64_table = "ZYXABCDEFGHIJKLMNOPQRSTUVWzyxabcdefghijklmnopqrstuvw0123456789+/"

# 自定义 Base64 编码函数
def encode_custom_b64(input_str):
    # 标准 Base64 编码
    standard_b64 = base64.b64encode(input_str.encode()).decode()
    # 替换为自定义的 Base64 表
    table_dict = {chr(i): custom_b64_table[i] for i in range(len(custom_b64_table))}
    custom_b64 = ''.join([table_dict.get(c, c) for c in standard_b64])
    return custom_b64

# 凯撒加密函数（右移3位）
def caesar_cipher(text, shift=3):
    result = ''
    for char in text:
        if char.isalpha():  # 对字母进行加密
            shift_base = ord('A') if char.isupper() else ord('a')
            result += chr((ord(char) - shift_base + shift) % 26 + shift_base)
        else:
            result += char  # 非字母字符不变
    return result

# 异或加密函数（使用固定的密钥0x12）
def xor_encrypt(text, key=0x12):
    return ''.join(chr(ord(c) ^ key) for c in text)

# 原始 flag
original_flag = "DUTCTF{perhaps_today_is_Monday}"

# 步骤1: 进行自定义 Base64 编码
encoded_b64 = encode_custom_b64(original_flag)

# 步骤2: 进行凯撒加密
encoded_caesar = caesar_cipher(encoded_b64, 3)

# 步骤3: 进行异或加密
encoded_xor = xor_encrypt(encoded_caesar)

# 输出最终加密结果
print(f"Original flag: {original_flag}")
print(f"Base64 encoded (custom): {encoded_b64}")
print(f"Caesar cipher (shift 3): {encoded_caesar}")
print(f"XOR encrypted result: {encoded_xor}")
