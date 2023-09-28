/*
 * Fowler–Noll–Vo hash function (FNV-1a)
 *
 * Luke McCarthy 2023-09-27
 */

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static const uint32_t fnv_prime_32 = (UINT32_C(1) << 24) + (UINT32_C(1) << 8) + 0x93;
static const uint32_t offset_basis_32 = UINT32_C(0x811c9dc5);

uint32_t fnv1a_hash_32(uint32_t hash, const uint8_t *data, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        hash ^= data[i];
        hash = (hash * fnv_prime_32) & UINT32_C(0xffffffff);
    }
    return hash;
}

static const uint64_t fnv_prime_64 = (UINT64_C(1) << 40) + (UINT64_C(1) << 8) + 0xb3;
static const uint64_t offset_basis_64 = UINT64_C(0xcbf29ce484222325);

uint64_t fnv1a_hash_64(uint64_t hash, const uint8_t *data, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        hash ^= data[i];
        hash = (hash * fnv_prime_64) & UINT64_C(0xffffffffffffffff);
    }
    return hash;
}

int main()
{
    size_t num_read, total_read;
    uint8_t buf[1024];

    uint32_t hash32 = offset_basis_32;
    uint64_t hash64 = offset_basis_64;

    total_read = 0;
    while ((num_read = fread(buf, 1, sizeof(buf), stdin)) != 0) {
        hash32 = fnv1a_hash_32(hash32, buf, num_read);
        hash64 = fnv1a_hash_64(hash64, buf, num_read);
        total_read += num_read;
    }

    printf("%zu %" PRIx32 " %" PRIx64 "\n", total_read, hash32, hash64);
    return 0;
}
