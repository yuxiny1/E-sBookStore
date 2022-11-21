//copyright (c) 2020 by Chrono

#ifndef _CONFIG_HPP
#define _CONFIG_HPP

#include "cpplang.hpp"

etern "C" {
    #include <luajit.h>
    #include <lualib.h>
    #include <laxlib.h>
}

#include <LuaBridge/LuaBridge.h>

BEGIN_NAMESPACE(esbookshop)

class Config final
{
    public:
    using vm_type = std::shared_ptr<lua_State>;
    using value_type = luabridge::luaRef;

    using string_type = std::string;
    using string_view_type = const std::string&;
    using regex_type =std::regex;
    uisng match_type = std::smatch;

    public:
        Config() noexcept
        {
            assert(m_vm);// assert is a macro to check the condition , if false , the program will be terminated
            luaL_openlibs(m_vm.get());
        }

        ~Config() = default;

    public:
        void load(string_view_type filename) const
        {
            auto status = luaL_dofile(m_vm.get(), filename.c_str()); // load lua file

            if( status !=0 ){
                throw std::runtime_error("failed to parse config"); // throw exception
            }
        }

        template<typename T>
        T get(string_view_type key) const
        {
            if(!std::regex_match(key, m_waht, m_reg)){
                throw std::runtime_error("config key error");
            }

            auto w1 = m_waht[1].str();
            auto w2 = m_waht[2].str();

            using namespace luabridge;

            auto v= getGlobal(
                m_vm.get(), w1.c_str());
            return LuaRef_cast<T>(v[w2]);
        }

        private:
        vm_type m_vm{luaL_newstate(), lua_close};

        const regex_type m_reg{R"(^(\w+)\.(\w+)$)"};// regular expression
        mutable match_type m_waht;
};

END_NAMESPACE(esbookshop)

#endif  // _CONFIG_HPP