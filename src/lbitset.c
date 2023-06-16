#include <stdlib.h>
#include <stdint.h>

#include "lua.h"
#include "lauxlib.h"

#include "bitset.h"

#if defined(_WIN32) || defined(_WIN64)
#define DLLEXPORT __declspec(dllexport)
#elif
#define DLLEXPORT
#endif /* _WIN32 */

static int
lbitset_clear(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must have a bitset");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_clear(*ud);
    return 0;
}

static int
lbitset_fill(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must have a bitset");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_fill(*ud);
    return 0;
}

static int
lbitset_copy(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must have a bitset");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_t *copyed = bitset_copy(*ud);
    if (copyed == NULL)
    {
        return luaL_error(L, "failed to call bitset_copy");
    }
    bitset_t **ret = (bitset_t **) lua_newuserdata(L, sizeof(bitset_t *));
    *ret = copyed;
    luaL_setmetatable(L, "bitset.Bitset");
    return 1;
}

static int
lbitset_resize(lua_State *L)
{
    if (lua_gettop(L) != 3)
    {
        return luaL_error(L, "must have a bitset, newarraysize, padwithzeroes");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    size_t newarraysize = (size_t) luaL_checkinteger(L, 2);
    bool padwithzeroes = (bool) lua_toboolean(L, 3);

    lua_pushboolean(L, (int) bitset_resize(*ud, newarraysize, padwithzeroes));
    return 1;
}

static int
lbitset_size_in_bytes(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must have a bitset");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    lua_pushinteger(L, (lua_Integer) bitset_size_in_bytes(*ud));
    return 1;
}

static int
lbitset_size_in_bits(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must have a bitset");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    lua_pushinteger(L, (lua_Integer) bitset_size_in_bits(*ud));
    return 1;
}

static int
lbitset_size_in_words(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must have a bitset");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    lua_pushinteger(L, (lua_Integer) bitset_size_in_words(*ud));
    return 1;
}

static int
lbitset_grow(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have a bitset and newarraysize");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    size_t newarraysize = (size_t) luaL_checkinteger(L, 2);

    lua_pushboolean(L, (int) bitset_grow(*ud, newarraysize));
    return 1;
}

static int
lbitset_trim(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must have a bitset");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    lua_pushboolean(L, (int) bitset_trim(*ud));
    return 1;
}

static int
lbitset_shift_left(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have a bitset and size");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    size_t s = luaL_checkinteger(L, 2);
    bitset_shift_left(*ud, s);
    return 0;
}

static int
lbitset_shift_right(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have a bitset and size");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    size_t s = luaL_checkinteger(L, 2);
    bitset_shift_right(*ud, s);
    return 0;
}

static int
lbitset_set(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have a bitset and data");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    size_t i = luaL_checkinteger(L, 2);
    bitset_set(*ud, i);
    return 0;
}

static int
lbitset_set_to_value(lua_State *L)
{
    if (lua_gettop(L) != 3)
    {
        return luaL_error(L, "must have a bitset, data and flag");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    size_t i = luaL_checkinteger(L, 2);
    bool flag = (bool) lua_toboolean(L, 3);
    bitset_set_to_value(*ud, i, flag);
    return 0;
}

static int
lbitset_get(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have a bitset, data");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    size_t i = luaL_checkinteger(L, 2);
    lua_pushboolean(L, (int) bitset_get(*ud, i));
    return 1;
}

static int
lbitset_count(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must have a bitset");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    lua_pushinteger(L, (lua_Integer) bitset_count(*ud));
    return 1;
}

static int
lbitset_minimum(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must have a bitset");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    lua_pushinteger(L, (lua_Integer) bitset_minimum(*ud));
    return 1;
}

static int
lbitset_maximum(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must have a bitset");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    lua_pushinteger(L, (lua_Integer) bitset_maximum(*ud));
    return 1;
}


static int
lbitset_inplace_union(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have two bitsets");
    }
    bitset_t **ud1 = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_t **ud2 = (bitset_t **) luaL_checkudata(L, 2, "bitset.Bitset");
    lua_pushboolean(L, (int) bitset_inplace_union(*ud1, *ud2));
    return 1;
}

static int
lbitset_union_count(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have two bitsets");
    }
    bitset_t **ud1 = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_t **ud2 = (bitset_t **) luaL_checkudata(L, 2, "bitset.Bitset");
    lua_pushinteger(L, (lua_Integer) bitset_union_count(*ud1, *ud2));
    return 1;
}

static int
lbitset_inplace_intersection(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have two bitsets");
    }
    bitset_t **ud1 = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_t **ud2 = (bitset_t **) luaL_checkudata(L, 2, "bitset.Bitset");
    bitset_inplace_intersection(*ud1, *ud2);
    return 0;
}

static int
lbitset_intersection_count(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have two bitsets");
    }
    bitset_t **ud1 = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_t **ud2 = (bitset_t **) luaL_checkudata(L, 2, "bitset.Bitset");
    lua_pushinteger(L, (lua_Integer) bitset_intersection_count(*ud1, *ud2));
    return 1;
}

static int
lbitsets_disjoint(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have two bitsets");
    }
    bitset_t **ud1 = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_t **ud2 = (bitset_t **) luaL_checkudata(L, 2, "bitset.Bitset");
    lua_pushboolean(L, (int) bitsets_disjoint(*ud1, *ud2));
    return 1;
}

static int
lbitsets_intersect(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have two bitsets");
    }
    bitset_t **ud1 = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_t **ud2 = (bitset_t **) luaL_checkudata(L, 2, "bitset.Bitset");
    lua_pushboolean(L, (int) bitsets_intersect(*ud1, *ud2));
    return 1;
}

static int
lbitset_contains_all(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have two bitsets");
    }
    bitset_t **ud1 = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_t **ud2 = (bitset_t **) luaL_checkudata(L, 2, "bitset.Bitset");
    lua_pushboolean(L, (int) bitset_contains_all(*ud1, *ud2));
    return 1;
}


static int
lbitset_inplace_difference(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have two bitsets");
    }
    bitset_t **ud1 = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_t **ud2 = (bitset_t **) luaL_checkudata(L, 2, "bitset.Bitset");
    bitset_inplace_difference(*ud1, *ud2);
    return 0;
}


static int
lbitset_difference_count(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have two bitsets");
    }
    bitset_t **ud1 = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_t **ud2 = (bitset_t **) luaL_checkudata(L, 2, "bitset.Bitset");
    lua_pushinteger(L, (lua_Integer) bitset_difference_count(*ud1, *ud2));
    return 1;
}

static int
lbitset_inplace_symmetric_difference(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have two bitsets");
    }
    bitset_t **ud1 = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_t **ud2 = (bitset_t **) luaL_checkudata(L, 2, "bitset.Bitset");
    lua_pushboolean(L, (int) bitset_inplace_symmetric_difference(*ud1, *ud2));
    return 1;
}

static int
lbitset_symmetric_difference_count(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have two bitsets");
    }
    bitset_t **ud1 = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_t **ud2 = (bitset_t **) luaL_checkudata(L, 2, "bitset.Bitset");
    lua_pushinteger(L, (lua_Integer) bitset_symmetric_difference_count(*ud1, *ud2));
    return 1;
}


static int
_lbitset_iterfunc(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have two param");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    size_t index = (size_t) lua_tointeger(L, lua_upvalueindex(1)); /*0 for the first time*/

    if (bitset_next_set_bit(*ud, &index))
    {
        lua_pushinteger(L, (lua_Integer) index);
        lua_pushinteger(L, (lua_Integer) ++index);
        lua_copy(L, -1, lua_upvalueindex(1));
        lua_pop(L, 1);
    }
    else
    {
        lua_pushnil(L);
    }
    return 1;
}


static int
lbitset_iter(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must have a bitset");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset"); /*ensure the type*/
    lua_pushinteger(L, 0);
    lua_pushcclosure(L, &_lbitset_iterfunc, 1);
    lua_pushvalue(L, 1);
    lua_pushnil(L); /*func table nil*/
    return 3;
}

static bool
cb(size_t value, void *param)
{
    lua_State *L = (lua_State *) param; /*ud func*/
    lua_pushvalue(L, -1); /*ud func func*/
    lua_pushinteger(L, (lua_Integer) value);  /*ud func func integer  */
    lua_call(L, 1, 1); /*ud func result || You'd better not fail!! */
    bool ret = (bool) lua_toboolean(L, -1);
    lua_pop(L, 1); /*ud func*/
    return ret;
}

static int
lbitset_for_each(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have a bitset and callback");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    if (lua_type(L, 2) != LUA_TFUNCTION)
    {
        return luaL_error(L, "callback must be a function");
    }
    lua_pushboolean(L, (int) bitset_for_each(*ud, &cb, L));
    return 1;
}

static int
lbitset_print(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must have a bitset");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_print(*ud);
    return 0;
}


static int
lbitset_gc(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must have a bitset");
    }
    bitset_t **ud = (bitset_t **) luaL_checkudata(L, 1, "bitset.Bitset");
    bitset_free(*ud);
    *ud = NULL;
    return 0;
}

static luaL_Reg lua_bitset_methods[] = {
        {"__gc",                         &lbitset_gc},
        {"clear",                        &lbitset_clear},
        {"fill",                         &lbitset_fill},
        {"copy",                         &lbitset_copy},
        {"resize",                       &lbitset_resize},
        {"size_in_bytes",                &lbitset_size_in_bytes},
        {"size_in_bits",                 &lbitset_size_in_bits},
        {"size_in_words",                &lbitset_size_in_words},
        {"grow",                         &lbitset_grow},
        {"trim",                         &lbitset_trim},
        {"shift_left",                   &lbitset_shift_left},
        {"shift_right",                  &lbitset_shift_right},
        {"set",                          &lbitset_set},
        {"set_to_value",                 &lbitset_set_to_value},
        {"get",                          &lbitset_get},
        {"count",                        &lbitset_count},
        {"minimum",                      &lbitset_minimum},
        {"maximum",                      &lbitset_maximum},
        {"inplace_union",                &lbitset_inplace_union},
        {"union_count",                  &lbitset_union_count},
        {"inplace_intersection",         &lbitset_inplace_intersection},
        {"intersection_count",           &lbitset_intersection_count},
        {"disjoint",                     &lbitsets_disjoint},
        {"intersect",                    &lbitsets_intersect},
        {"contains_all",                 &lbitset_contains_all},
        {"inplace_difference",           &lbitset_inplace_difference},
        {"difference_count",             &lbitset_difference_count},
        {"inplace_symmetric_difference", &lbitset_inplace_symmetric_difference},
        {"symmetric_difference_count",   &lbitset_symmetric_difference_count},
        {"iter",                         &lbitset_iter},
        {"for_each",                     &lbitset_for_each},
        {"print",                        &lbitset_print},
        {NULL, NULL}
};


static int
lbitset_new(lua_State *L)
{
    size_t size = 0;
    switch (lua_gettop(L))
    {
        case 0:
            size = 0;
            break;
        case 1:
            size = (size_t) luaL_checkinteger(L, 1);
            break;
        default:
            return luaL_error(L, "too many arguments");
    }
    bitset_t **ud = (bitset_t **) lua_newuserdata(L, sizeof(bitset_t *));
    bitset_t *b = NULL;
    if (size == 0)
    {
        b = bitset_create();
    }
    else
    {
        b = bitset_create_with_capacity(size);
    }
    if (b == NULL)
    {
        return luaL_error(L, "failed to malloc bitset_t");
    }
    *ud = b;
    luaL_setmetatable(L, "bitset.Bitset");
    return 1;
}


static luaL_Reg lua_funcs[] = {
        {"new", &lbitset_new},
        {NULL, NULL}
};

DLLEXPORT int luaopen_bitset(lua_State *L)
{
    if (!luaL_newmetatable(L, "bitset.Bitset"))
    {
        return luaL_error(L, "bitset.Bitset already in register");
    }
    lua_pushvalue(L, -1); // mt mt
    lua_setfield(L, -2, "__index"); // mt
    luaL_setfuncs(L, lua_bitset_methods, 0); // mt

    luaL_newlib(L, lua_funcs);
    return 1;
}