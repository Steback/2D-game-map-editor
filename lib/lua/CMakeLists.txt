file(GLOB LUA_HEADERS src/*.h)
file(GLOB LUA_SOURCE src/*.c)
file(GLOB LUA_CXX_HEADERS src/*.hpp)

include_directories(${PROJECT_SOURCE_DIR}/lib/lua/src)

add_library(LuaLib SHARED ${LUA_SOURCE} ${LUA_HEADERS} ${LUA_CXX_HEADERS})