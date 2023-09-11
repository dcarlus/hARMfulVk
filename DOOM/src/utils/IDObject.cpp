#include "utils/IDObject.hpp"

using namespace Doom ;

uint32_t IDObject::CurrentID = 0 ;
std::unordered_set<uint32_t> IDObject::AvailableIDs = std::unordered_set<uint32_t>() ;
std::mutex IDObject::ClassMutex;

uint32_t IDObject::Generate() {
    const std::lock_guard<std::mutex> lock(ClassMutex);

    if (AvailableIDs.size() == 0) {
        uint32_t newID = ++CurrentID ;
        return newID ;
    }
    else {
        auto beginIDs = AvailableIDs.begin() ;
        uint32_t id = *beginIDs ;
        AvailableIDs.erase(beginIDs) ;
        return id ;
    }
}

void IDObject::Free(IDObject& obj)
{
    const std::lock_guard<std::mutex> lock(ClassMutex);

    if (AvailableIDs.count(obj.m_id) == 0) {
        AvailableIDs.emplace(obj.m_id) ;
        obj.m_id = 0 ;
    }
    else {
        throw std::runtime_error("") ;
    }
}
