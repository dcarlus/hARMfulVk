#include "utils/IDObject.hpp"

using namespace Doom ;

id_t IDObject::CurrentID = 0 ;
std::unordered_set<id_t> IDObject::AvailableIDs = std::unordered_set<id_t>() ;
std::mutex IDObject::ClassMutex;

IDObject::~IDObject() noexcept {
    Free(*this);
}

id_t IDObject::Generate() {
    const std::lock_guard<std::mutex> lock(ClassMutex);

    if (AvailableIDs.size() == 0) {
        id_t newID = ++CurrentID ;
        return newID ;
    }
    else {
        auto beginIDs = AvailableIDs.begin() ;
        id_t id = *beginIDs ;
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

bool IDObject::operator==(const IDObject& other) {
    return m_id == other.m_id;
}

bool IDObject::operator!=(const IDObject& other) {
    return m_id != other.m_id;
}