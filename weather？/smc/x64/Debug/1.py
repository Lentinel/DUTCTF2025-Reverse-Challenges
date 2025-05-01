import pefile

def encrypt_section(pe_file, section_name, xor_key):
    """
    加密PE文件中指定的区段
    """
    # 找到对应的section
    for section in pe_file.sections:
        # 使用strip()清理区段名的空字符，避免与目标区段名不匹配
        section_name_clean = section.Name.decode().strip('\x00')
        if section_name_clean == section_name:
            print(f"[*] Found {section_name} section at 0x{section.PointerToRawData:08x}")
            data = section.get_data()
            encrypted_data = bytes([data[i] ^ xor_key for i in range(len(data))])
            pe_file.set_bytes_at_offset(section.PointerToRawData, encrypted_data)
            print(f"[*] Encrypted {len(data)} bytes at 0x{section.PointerToRawData:08x}")
            return

    print(f"[!] {section_name} section not found!")

if __name__ == "__main__":
    filename = "weather.exe"  # 需要加密的文件名
    section_name = ".func"  # 需要加密的区段名
    xor_key = 0x3  # 异或加密的键

    print(f"[*] Loading {filename}")
    pe_file = pefile.PE(filename)

    # 加密指定区段
    print("[*] Encrypting section")
    encrypt_section(pe_file, section_name, xor_key)

    # 保存修改后的PE文件
    new_filename = filename[:-4] + "_encrypted.exe"
    print(f"[*] Saving as {new_filename}")
    pe_file.write(new_filename)
    pe_file.close()
