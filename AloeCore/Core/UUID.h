#pragma once

#include <xhash>

namespace Aloe
{
    class UUID
    {
    public:
        UUID();
        UUID(uint64_t uuid);
        UUID(const UUID&) = default;

        operator uint64_t() const { return m_UUID; }

        const uint64_t GetUIID() { return m_UUID; }

    private:
        uint64_t m_UUID = 0;
    };

}

namespace std
{
    // Provide a specialized template for the hash function, so we can
    // use UUID directly in maps
    template<>
    struct hash<Aloe::UUID>
    {
        std::size_t operator()(const Aloe::UUID& uuid) const
        {
            return hash<uint64_t>()((uint64_t)uuid);
        }
    };

}