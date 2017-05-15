// Extension lib defines 
#define EXTENSION_NAME html5nativeext
#define LIB_NAME "html5nativeext"
#define MODULE_NAME LIB_NAME

// Defold SDK
#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

#include <emscripten.h>

/////////

static int Multiply(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    lua_Number a = luaL_checknumber(L, 1);
    lua_Number b = luaL_checknumber(L, 2);
    
    lua_Number result = a * b;

    lua_pushnumber(L, result);
    return 1;
}

// Testing emscripten macros
// https://kripken.github.io/emscripten-site/docs/api_reference/emscripten.h.html?highlight=em_asm#c.EM_ASM
static int Max(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    lua_Number a = luaL_checknumber(L, 1);
    lua_Number b = luaL_checknumber(L, 2);

    lua_Number result = EM_ASM_DOUBLE({
        return Math.max($0, $1);
    }, a, b);

    lua_pushnumber(L, result);
    return 1;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] =
{
    {"multiply", Multiply},
    {"max", Max},
    //{"dostuff_js", DoStuffJS},
    //{"getdata", GetData},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

static dmExtension::Result AppInitializeExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeExtension(dmExtension::Params* params)
{
    // Init Lua
    LuaInit(params->m_L);
    printf("Registered %s Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeExtension(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#else

static dmExtension::Result AppInitializeExtension(dmExtension::AppParams* params)
{
    dmLogWarning("Registered %s (null) Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeExtension(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeExtension(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#endif

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeExtension, AppFinalizeExtension, InitializeExtension, 0, 0, FinalizeExtension)
