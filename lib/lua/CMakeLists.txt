file(GLOB LUA_SOURCE ${PROJECT_SOURCE_DIR}/lib/lua/*.c)

add_library(LuaLib STATIC ${LUA_SOURCE})