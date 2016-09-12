#include "onscreen_element.h"

Guid OnscreenElement::guid(){
  if(m_guid == Guid()){
    GuidGenerator generator;
    auto newGuid = generator.newGuid();
    m_guid = newGuid;
  }
  return m_guid;
}
