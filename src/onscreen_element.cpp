#include "onscreen_element.h"

OnscreenElement::OnscreenElement(){
    static GuidGenerator generator;
    auto newGuid = generator.newGuid();
    m_guid = std::hash<Guid>{}(newGuid);
    m_symbol = ' ';
    m_x = 0;
    m_y = 0;
    m_depth = INT_MAX;
}

bool operator<(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs){
    return lhs.guid() < rhs.guid();
}

bool operator>(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs){
    return rhs < lhs;
}

bool operator<=(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs){
    return !(lhs > rhs);
}

bool operator>=(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs){
    return !(lhs < rhs);
}

bool operator==(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs){
    return lhs.guid() == rhs.guid();
}

bool operator!=(
        const OnscreenElement& lhs,
        const OnscreenElement& rhs){
    return !(lhs.guid() == rhs.guid());
}

bool OnscreenElementPtrComp::operator()(
        const OnscreenElement* lhs,
        const OnscreenElement* rhs) const {
    return *lhs < *rhs;
}

