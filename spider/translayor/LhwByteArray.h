#pragma once

#include <cstring>
#include <vector>
#include <cstdint>
#include <string>

namespace translayor
{
    class LhwByteArray : public std::vector<char>
    {
    public:
        LhwByteArray() = default;

        LhwByteArray(size_t size) :
                std::vector<char>(size) {
        }

        LhwByteArray(const char* buffer,int32_t size) :
                std::vector<char>(buffer,buffer+size) { 
        }

        LhwByteArray(const std::string & str) :
                std::vector<char>(str.size()){
            memcpy(data(),str.c_str(),str.size());
        }

        std::string ToStdString() const 
        {
            std::string result(this->cbegin(),this->cend());
            return result;
        }

        LhwByteArray& Concat(const LhwByteArray& buffer2) 
        {
            size_t oldSize = size();
            size_t newSize = oldSize + buffer2.size();
            resize(newSize);
            memcpy(this->data() + oldSize, buffer2.data(), buffer2.size());

            return *this;
        }

        LhwByteArray operator+(const LhwByteArray& buffer2) const 
        {
            LhwByteArray buffer1(this->size() + buffer2.size());
            memcpy(buffer1.data(), this->data(), this->size());
            memcpy(buffer1.data() + this->size(), buffer2.data(), buffer2.size());

            return buffer1;
        }
    };
}