// Minimal reproducer for BUG-001 (allocator OOB write).
//
// Build: $ c++ -std=c++20 -fno-exceptions -fno-rtti -O0 -g -I../../../include \
//             -I../../../src ../../../src/engine_demo/allocator.cpp repro.cpp -o repro
// Run:   $ ./repro     (expect SIGSEGV / heap corruption assertion in debug allocators)

#include "engine_demo/allocator.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>

int main() {
    alignas(32) std::byte buffer[192]{};
    engine_demo::allocator a{buffer, sizeof(buffer)};

    void* p1 = a.allocate(40, 32);
    void* p2 = a.allocate(40, 32);
    void* p3 = a.allocate(40, 32);

    std::printf("p1=%p p2=%p p3=%p used=%zu\n", p1, p2, p3, a.bytes_used());

    if (p3 != nullptr) {
        // Touch the just-returned region — this is where the corruption surfaces if
        // the bookkeeping was advanced past the arena tail.
        for (std::size_t i = 0; i < 40; ++i) {
            static_cast<std::byte*>(p3)[i] = static_cast<std::byte>(i);
        }
    }
    return 0;
}
