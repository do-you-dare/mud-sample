

#pragma once

#include <example/Generated/Module.h>

#include <obj/Any.h>
#include <obj/Reflect/MetaDecl.h>
#include <obj/System/System.h>

namespace mud
{
#ifdef EXAMPLE_REFLECTION_IMPL
    // Exported types
    template <>  Type& cls<ShapeType>() { static Type ty("ShapeType"); return ty; }
    
    template <>  Type& cls<MyObject>() { static Type ty("MyObject"); return ty; }
#endif

    // Base Types
    
    // Enums
    template <>
    struct Reflection<ShapeType> : public Meta
    {
        cstring m_name = "ShapeType";
        size_t m_size = sizeof(ShapeType);
        TypeClass m_type_class = TypeClass::Enum;
        bool m_scoped_enum = true;
        std::vector<cstring> m_enum_names = { "Circle", "Sphere", "Cube" };
        std::vector<size_t> m_enum_indices = { 0, 1, 2 };
        std::vector<Var> m_enum_values = { var(ShapeType::Circle), var(ShapeType::Sphere), var(ShapeType::Cube) };
        
        Reflection() : Meta(cls<ShapeType>()) { meta_enum(*this, *this); }
    };
    
    
    // Sequences
    
    
    
        
    // MyObject
    template <>
    struct Reflection<MyObject> : public Meta
    {
        cstring m_name = "MyObject";
        size_t m_size = sizeof(MyObject);
        TypeClass m_type_class = TypeClass::Object;
        bool m_serializable = false;
        struct {
            Member m_visible = { cls<MyObject>(), member_address(&MyObject::m_visible), cls<bool>(), "visible", member_getter<bool>(&MyObject::m_visible), member_setter<bool>(&MyObject::m_visible), var(bool()), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_number = { cls<MyObject>(), member_address(&MyObject::m_number), cls<int>(), "number", member_getter<int>(&MyObject::m_number), member_setter<int>(&MyObject::m_number), var(int(0)), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_name = { cls<MyObject>(), member_address(&MyObject::m_name), cls<std::string>(), "name", member_getter<std::string>(&MyObject::m_name), member_setter<std::string>(&MyObject::m_name), var(std::string()), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_shape = { cls<MyObject>(), member_address(&MyObject::m_shape), cls<ShapeType>(), "shape", member_getter<ShapeType>(&MyObject::m_shape), member_setter<ShapeType>(&MyObject::m_shape), var(ShapeType()), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_position = { cls<MyObject>(), member_address(&MyObject::m_position), cls<mud::vec3>(), "position", member_getter<mud::vec3>(&MyObject::m_position), member_setter<mud::vec3>(&MyObject::m_position), var(mud::vec3()), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_colour = { cls<MyObject>(), member_address(&MyObject::m_colour), cls<mud::Colour>(), "colour", member_getter<mud::Colour>(&MyObject::m_colour), member_setter<mud::Colour>(&MyObject::m_colour), var(mud::Colour()), MEMBER_VALUE|MEMBER_MUTABLE };
            Member m_floats = { cls<MyObject>(), member_address(&MyObject::m_floats), cls<std::vector<float>>(), "floats", member_getter<std::vector<float>>(&MyObject::m_floats), member_setter<std::vector<float>>(&MyObject::m_floats), var(std::vector<float>()), MEMBER_VALUE|MEMBER_MUTABLE };
        } members;
        struct {
            Method method = { cls<MyObject>(), "method", member_address(&MyObject::method), [](Ref object, array<Var> args, Var& result) { UNUSED(args);result = var(val<MyObject>(object).method()); }, {}, var(int()) };
        } methods;
        struct {
            ConstructorFunc construct_0 = [](Ref ref, array<Var> args) { new(&val<MyObject>(ref)) MyObject( val<ShapeType>(args[0]), val<mud::Colour>(args[1]) ); };
            Constructor constructor_0 = { cls<MyObject>(), construct_0, { { "shape", var(ShapeType()) }, { "colour", var(mud::Colour()) } } };
        } constructors;
        std::vector<Member> m_members = { members.m_visible, members.m_number, members.m_name, members.m_shape, members.m_position, members.m_colour, members.m_floats };
        std::vector<Method> m_methods = { methods.method };
        std::vector<Constructor> m_constructors = { constructors.constructor_0 };
        
        Reflection() : Meta(cls<MyObject>()) { init_pool<MyObject>(*this); meta_class(*this, *this); }
    };
    

    
#ifdef EXAMPLE_REFLECTION_IMPL
    void example_meta(Module& module)
    {   
        rfl<ShapeType>();
        module.m_types.push_back(&cls<ShapeType>());
        rfl<MyObject>();
        module.m_types.push_back(&cls<MyObject>());
    
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  ::foo(val<int>(args[0])); };
            std::vector<Param> params = { { "arg", var(int()) } };
            module.m_functions.push_back({ &namspc({ "" }), "foo", function_id<void(*)(int)>(&::foo), func, params, Var() });
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  ::bar(val<MyObject>(args[0])); };
            std::vector<Param> params = { { "object", Ref(cls<MyObject>()) } };
            module.m_functions.push_back({ &namspc({ "" }), "bar", function_id<void(*)(MyObject&)>(&::bar), func, params, Var() });
        }
    }
#endif

}
