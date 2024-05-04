
#include <sstream>
#include <iomanip>
#include <vector>

template<typename T>
inline std::string toHexString(const T& value)
{
    std::ostringstream oss;
    oss << std::uppercase << std::hex << std::setfill('0');
    oss << "0x" << std::setw(sizeof(T) * 2) << static_cast<int>(value);
    return oss.str();
}

inline std::string toHexString(const std::vector<uint8_t>& data)
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::uppercase;
    for (const auto& byte : data) {
        oss << "0x" << std::setw(2) << static_cast<int>(byte) << ' ';
    }
    return oss.str();


}

std::string routineControlToString(uint8_t type)
{
    switch (type) {
        case 1: return "START";
        case 2: return "STOP";
        case 3: return "RESULT";
        default: return "UNKNOW";
    }
}