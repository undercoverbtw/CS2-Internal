#pragma once

#include <array>
#include <vector>

namespace sdk {
    template <typename Data, class KeyType = std::uint64_t>
    struct HashFixedDataInternal {
        KeyType ui_key;
        HashFixedDataInternal* next;
        Data data;
    };

    template <typename Data, class KeyType = std::uint64_t>
    struct HashFixedStructDataInternal {
        Data data;
        KeyType ui_key;
        std::uint8_t padding_0[0x8];
    };

    template <typename Data, class KeyType = std::uint64_t>
    struct HashBucketDataInternal {
        Data data;
        HashFixedDataInternal<Data>* next;
        KeyType ui_key;
    };

    template <class T>
    struct HashStructData {
        std::uint8_t padding_0[0x10];
        std::array<HashFixedStructDataInternal<T>, 256> list;
    };

    template <class T>
    struct HashAllocatedData {
        std::uint8_t padding_0[0x18];
        std::array<HashFixedDataInternal<T>, 128> list;
    };

    template <class T, class KeyType = std::uint64_t>
    struct HashUnallocatedData {
        HashUnallocatedData* next;
        KeyType unk_1;
        KeyType ui_key;
        KeyType unk_2;
        std::array<HashBucketDataInternal<T>, 256> current_block_list;
    };

    template <class T, class KeyType = std::uint64_t>
    struct HashBucket {
        HashStructData<T>* struct_data;
        void* mutex_list;
        HashAllocatedData<T>* allocated_data;
        HashUnallocatedData<T, KeyType>* unallocated_data;
    };

    class UtlMemoryPool {
    public:
        UtlMemoryPool() = default;

        [[nodiscard]] std::int32_t get_block_size() const {
            return blocks_per_blob_;
        }

        [[nodiscard]] std::int32_t get_count() const {
            return block_allocated_size_;
        }

        [[nodiscard]] std::int32_t get_peak_count() const {
            return peak_alloc_;
        }

    private:
        std::int32_t block_size_{ 0 };
        std::int32_t blocks_per_blob_{ 0 };
        std::int32_t grow_mode_{ 0 };
        std::int32_t blocks_allocated_{ 0 };
        std::int32_t block_allocated_size_{ 0 };
        std::int32_t peak_alloc_{ 0 };
    };

    template <class T, class KeyType = std::uint64_t>
    class UtlTSHash {
    public:
        [[nodiscard]] std::int32_t get_block_size() const;

        [[nodiscard]] std::int32_t get_count() const;

        std::vector<T> get_elements();

        static std::uint64_t invalid_handle() {
            return static_cast<std::uint64_t>(0);
        }

    private:
        UtlMemoryPool entry_memory_;

        HashBucket<T, KeyType> buckets_;

        bool needs_commit_{ false };
    };

    template <class T, class KeyType>
    std::int32_t UtlTSHash<T, KeyType>::get_block_size() const {
        return entry_memory_.get_block_size();
    }

    template <class T, class KeyType>
    std::int32_t UtlTSHash<T, KeyType>::get_count() const {
        return entry_memory_.get_count();
    }

    template <class T, class KeyType>
    std::vector<T> UtlTSHash<T, KeyType>::get_elements() {
        std::vector<T> list;

        const std::int32_t count = get_count();

        const auto& unallocated_data = buckets_.unallocated_data;

        std::size_t index = 0;

        for (auto element = unallocated_data; element; element = element->next) {
            for (std::int32_t i = 0; i < get_block_size() && i != count; ++i) {
                list.emplace_back(element->current_block_list.at(i).data);

                index++;

                if (index >= count)
                    break;
            }
        }

        return list;
    }
}