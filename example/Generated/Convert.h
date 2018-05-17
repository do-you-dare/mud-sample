
#pragma once

#include <example/Generated/Types.h>

#include <obj/Reflect/Meta.h>
#include <obj/Reflect/Enum.h>
#include <obj/String/StringConvert.h>

namespace mud
{
    template <> inline void from_string(const string& str, ShapeType& val) { val = static_cast<ShapeType>(meta<ShapeType>().m_enum->value(str.c_str())); };
    template <> inline void to_string(const ShapeType& val, string& str) { str = meta<ShapeType>().m_enum->m_map[size_t(val)]; };
    
    
}
