use wasm_bindgen::prelude::*;

#[wasm_bindgen]
pub fn modified_WTF_encrypt(input: &[u8], key: &[u8]) -> Vec<u8> {
    let mut s = [0u8; 256];
    let mut seed: u8 = 0x42;
    for i in 0..256 {
        seed = seed.wrapping_mul(31).wrapping_add(i as u8);
        s[i] = seed;
    }

    let mut j = 0u8;
    for i in 0..256 {
        j ^= s[i] ^ key[i as usize % key.len()];
        j = j.wrapping_add(s[i]);
        s.swap(i as usize, j as usize);
    }

    let mut i = 0u8;
    j = 0u8;
    let mut output = Vec::with_capacity(input.len());

    for &byte in input {
        i = i.wrapping_add(1);
        j = j.wrapping_add(s[i as usize]);
        s.swap(i as usize, j as usize);
        let k = s[(s[i as usize].wrapping_add(s[j as usize])) as usize % 256];
        let encrypted = (byte ^ (k ^ 0x5A));
        output.push(encrypted);
    }

    output
}

#[wasm_bindgen]
pub fn check_flag(ptr: *const u8, len: usize) -> u32 {
    let input = unsafe { std::slice::from_raw_parts(ptr, len) };
    let key = b"CIPPUSSSS";

    let cipher = modified_WTF_encrypt(input, key);

    let target_ciphertext: Vec<u8> = vec![40, 194, 235, 111, 219, 87, 89, 101, 107, 76, 146, 13, 255, 202, 152, 237, 227, 139, 48, 186, 121, 52, 232, 110, 205, 166, 25, 136, 49, 175, 27, 52, 217, 1, 24, 8, 195, 162, 127, 139, 54, 34, 191, 235];

    if cipher == target_ciphertext {
        1
    } else {
        0
    }
}

#[wasm_bindgen]
pub fn alloc(len: usize) -> *mut u8 {
    let mut buf = Vec::with_capacity(len);
    let ptr = buf.as_mut_ptr();
    std::mem::forget(buf);
    ptr
}
