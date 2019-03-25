#pragma once

#include <cstring>
#include <vector>
#include <cstdint>
#include <string>

namespace translayor
{
    class ByteArray : public std::vector<char>
    {
    public:
        ByteArray() = default;

        ByteArray(size_t size) :
                std::vector<char>(size) {
        }

        ByteArray(const char* buffer,int32_t size) :
                std::vector<char>(buffer,buffer+size) { 
        }

        ByteArray(const std::string & str) :
                std::vector<char>(str.size()){
            memcpy(data(),str.c_str(),str.size());
        }

        std::string ToStdString() const {
            std::string result(this->cbegin(),this->cend());
            return result;
        }

        ByteArray& Concat(const ByteArray& buffer2) {
            size_t oldSize = size();
            size_t newSize = oldSize + buffer2.size();
            resize(newSize);
            memcpy(this->data() + oldSize, buffer2.data(), buffer2.size());

            return *this;
        }

        ByteArray operator+(const ByteArray& buffer2) const {
            ByteArray buffer1(this->size() + buffer2.size());
            memcpy(buffer1.data(), this->data(), this->size());
            memcpy(buffer1.data() + this->size(), buffer2.data(), buffer2.size());

            return buffer1;
        }
    };
}