#include "LuaHelper.h"
#include "cocos2d.h"

#include <cocos2d.h>
#include <vector>
#include <string>

#include "CCLuaEngine.h"

#include "Macro.h"
#include "GameWorld.h"
extern "C"
{
#include "lauxlib.h"
#include "tolua++.h"
};
#include "../template/TemplateScene.h"

USING_NS_CC;

LuaHelper::LuaHelper()
{

}

LuaHelper::~LuaHelper()
{
	CCScriptEngineManager::sharedManager()->removeScriptEngine();
}

bool LuaHelper::init()
{
	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

	CCLuaStack *pStack = pEngine->getLuaStack();
	lua_State *tolua_s = pStack->getLuaState();

	registerCFunctionToLua();

	std::vector<std::string> searchPaths;
	searchPaths.push_back("lua");
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
	pEngine->executeScriptFile("init.lua");
	return true;
}


CSJson::Value LuaHelper::executeGlobalFunction( const char* functionName, int numArgs )
{
	CSJson::Value retObj;
	lua_State *luaState = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();

	lua_getglobal(luaState, functionName);       /* query function by name, stack: function */
	if (lua_isfunction(luaState, -1))
	{
		if (numArgs > 0)
		{
			lua_insert(luaState, -(numArgs + 1));                        /* stack: ... func arg1 arg2 ... */
		}

		int traceback = 0;
		lua_getglobal(luaState, "__G__TRACKBACK__");                     /* stack: ... func arg1 arg2 ... G */
		if (!lua_isfunction(luaState, -1))
		{
			lua_pop(luaState, 1);                                        /* stack: ... func arg1 arg2 ... */
		}
		else
		{
			traceback = -(numArgs + 2);
			lua_insert(luaState, traceback);                             /* stack: ... G func arg1 arg2 ... */
		}

		int error = 0;
		error = lua_pcall(luaState, numArgs, 1, traceback);              /* stack: ... ret */
		if (error)
		{
			if (traceback == 0)
			{
				CCLOG("[LUA ERROR] %s", lua_tostring(luaState, - 1));    /* stack: ... error */
				lua_pop(luaState, 1); // remove error message from stack
			}
			return retObj;
		}

		// get return value

		// lua_gettop返回栈顶的索引  
		// 如果索引为0，则表示栈为空  
		while (lua_gettop( luaState ))  
		{  
			switch (lua_type( luaState, lua_gettop( luaState ) ))  
			{  
			case LUA_TNUMBER:  
				{  
					retObj["val"] = lua_tonumber( luaState, lua_gettop( luaState ) );   
					break;  
				}  
			case LUA_TTABLE:    
				{  
					// 简单的遍历表的功能  
					// ***好像lua不保存表的元素的添加顺序***  

					// 压入第一个键  
					lua_pushnil(luaState);  /* 第一个 key */  
					int t = -2;  
					CSJson::Value obj;
					while (lua_next(luaState, t) != 0)  
					{  
						/* 'key' (索引-2) 和 'value' (索引-1) */  
						
						if(lua_type(luaState, -1) == LUA_TSTRING)  
						{  
							obj[lua_tostring(luaState, -2)] = lua_tostring(luaState, -1); 
						}  
						else if(lua_type(luaState, -1) == LUA_TNUMBER)  
						{  
							// 因为lua_tostring会更改栈上的元素，  
							// 所以不能直接在key上进行lua_tostring  
							// 因此，复制一个key，压入栈顶，进行lua_tostring  
							lua_pushvalue(luaState, -2);  
							string key = lua_tostring(luaState, -1);  
							lua_pop(luaState, 1);  
							obj[key] = lua_tointeger(luaState, -1);
						}  
						else  
						{  
							obj["unknow"] = lua_tostring(luaState, -1); 
						}  

						/* 移除 'value' ；保留 'key' 做下一次迭代 */  
						lua_pop(luaState, 1);  
					}  

					retObj["val"] = obj;
					break;  
				}  
			case LUA_TSTRING:   
				{  
					retObj["val"] = lua_tostring( luaState, lua_gettop( luaState ) );  
					break;  
				}  
			case LUA_TBOOLEAN:  
				{  
					retObj["val"] = lua_toboolean( luaState, lua_gettop( luaState ) );  
					break;  
				}  
			default:   
				CCAssert(0, "lua return invalid type");
				break;  
			}  
			lua_pop( luaState, 1 );  
		}  

		return retObj;
	}
	else
	{
		CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", functionName);
		lua_pop(luaState, 1);
		lua_pop(luaState, numArgs); // remove args from stack
		return retObj;
	}
}

bool LuaHelper::pushInt( int32t nVal )
{
	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	CCLuaStack *pStack = pEngine->getLuaStack();
	pStack->pushInt(nVal);
	return true;
}

bool LuaHelper::pushString( const char* pStr )
{
	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	CCLuaStack *pStack = pEngine->getLuaStack();
	pStack->pushString(pStr);
	return true;
}


int  tolua_TemplateToLua_open (lua_State* tolua_S);

bool LuaHelper::registerCFunctionToLua()
{
	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	CCLuaStack *pStack = pEngine->getLuaStack();
	lua_State* L = pStack->getLuaState();

	static const struct luaL_reg mylib [] = {
		{"test", lua_Test},
		{"getScene", lua_GetScene},
		{NULL, NULL}  /* sentinel */
	};

	luaL_openlib(L, "game", mylib, 0);
	tolua_TemplateToLua_open(L);
	return true;
}


int lua_Test( lua_State* L )
{
	CCLOG("test by lua");
	return 0;
}

int lua_GetScene( lua_State* L )
{
	int nSceneSN = lua_tointeger(L, -1);

	const TemplateScene* pScene = GAMEWORLD->get<TemplateScene>(nSceneSN);
	tolua_pushusertype(L,(void*)pScene,"TemplateScene");

	return 1;
}
