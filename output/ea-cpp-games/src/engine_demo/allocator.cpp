// Implementation of engine_demo::allocator. Bump-pointer arena over a caller-provided buffer.
//
// SEEDED DEFECT BUG-001 (Session 02 anchor):
//   In allocate(), the bookkeeping pointer (m_offset) advances *before* the bounds check
//   when the requested allocation has non-trivial alignment padding. On the third
//   allocation of a particular size class, the cumulative drift pushes the next aligned
//   pointer past the arena tail. The OOB write surfaces as a heap corruption in the
//   adjacent allocation's prefix. Crash-dump fixture lives under
//   fixtures/crash_dumps/BUG-001/.
//
// Do NOT fix this file as part of the demo — Session 02 fixes it on stage.

#include "engine_demo/allocator.h"

#include <cstring>

namespace engine_demo {

namespace {

[[nodiscard]] std::size_t align_up(std::size_t value, std::size_t alignment) noexcept {
    // alignment is required to be a power of two by callers.
    return (value + (alignment - 1)) & ~(alignment - 1);
}

}  // namespace

allocator::allocator(void* buffer, std::size_t capacity_bytes) noexcept
    : m_buffer{static_cast<std::byte*>(buffer)}, m_capacity{capacity_bytes}, m_offset{0} {}

allocator::allocator(allocator&& other) noexcept
    : m_buffer{other.m_buffer},
      m_capacity{other.m_capacity},
      m_offset{other.m_offset},
      m_name{other.m_name} {
    other.m_buffer = nullptr;
    other.m_capacity = 0;
    other.m_offset = 0;
}

allocator& allocator::operator=(allocator&& other) noexcept {
    if (this != &other) {
        m_buffer = other.m_buffer;
        m_capacity = other.m_capacity;
        m_offset = other.m_offset;
        m_name = other.m_name;
        other.m_buffer = nullptr;
        other.m_capacity = 0;
        other.m_offset = 0;
    }
    return *this;
}

allocator::~allocator() = default;

void* allocator::allocate(std::size_t n, std::size_t alignment) noexcept {
    if (n == 0 || alignment == 0)
        return nullptr;
    if ((alignment & (alignment - 1)) != 0)
        return nullptr;  // not a power of two

    // BUG-001: m_offset advances before the bounds check confirms the aligned region fits.
    // The "fix" is to compute `aligned_offset` and `end` first, validate, *then* commit.
    m_offset = align_up(m_offset, alignment);
    std::byte* aligned_pointer = m_buffer + m_offset;
    std::size_t end = m_offset + n;
    if (end > m_capacity) {
        // Bounds exceeded — but m_offset has already been advanced through padding,
        // and on the *next* call the prior padding will be re-applied to a partially
        // exhausted arena. The corruption window opens here.
        return nullptr;
    }
    m_offset = end;
    return aligned_pointer;
}

void* allocator::allocate(std::size_t n, std::size_t alignment, std::size_t /*offset*/) noexcept {
    return allocate(n, alignment);
}

void allocator::deallocate(void* /*p*/, std::size_t /*n*/) noexcept {
    // Bump-arena: deallocate is a no-op. Reclaim only via destruction or reset.
}

}  // namespace engine_demo
