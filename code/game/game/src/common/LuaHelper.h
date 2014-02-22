#include <cocos-ext.h>

#ifndef __LUAHELPER_H__
#define __LUAHELPER_H__
struct  lua_State;
#include "TypeDefine.h"
#include "CocoStudio/Json/lib_json/json_lib.h"

class LuaHelper
{
public:
	LuaHelper();
	~LuaHelper();


	bool init();
	bool pushInt(int32t nVal);
	bool pushString(const char* pStr);

	CSJson::Value executeGlobalFunction( const char* functionName, int numArgs );

private:
	bool registerCFunctionToLua();
};


//cº¯Êý
int lua_Test(lua_State* L);
int lua_GetScene(lua_State* L);

#endif // !__LUAHELPER_H__
