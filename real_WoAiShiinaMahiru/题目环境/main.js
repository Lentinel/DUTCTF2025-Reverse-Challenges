import init from './WoAiShiinaMahiru.js';

async function main() {
    const wasm = await init();
    const { check_flag, alloc, memory } = wasm;

    document.getElementById("verifyButton").addEventListener("click", async () => {
        const input = document.getElementById("flagInput").value;
        const encoded = new TextEncoder().encode(input);
        const ptr = alloc(encoded.length);
        new Uint8Array(memory.buffer, ptr, encoded.length).set(encoded);
        document.getElementById("result").textContent = 
            check_flag(ptr, encoded.length) === 1 ? "✅ Correct!" : "❌ Wrong.";
    });
}

main();