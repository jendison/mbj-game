/*
** Lua binding: TemplateToLua
** Generated automatically by tolua++-1.0.92 on 11/04/13 11:03:56.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_TemplateToLua_open (lua_State* tolua_S);

#include "TypeDefine.h"
#include "TemplateScene.h"
//注意 仅导出需要的函数即可。

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"TemplateScene");
}

/* method: getNextscene of class  TemplateScene */
#ifndef TOLUA_DISABLE_tolua_TemplateToLua_TemplateScene_getNextscene00
static int tolua_TemplateToLua_TemplateScene_getNextscene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TemplateScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TemplateScene* self = (const TemplateScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNextscene'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->getNextscene();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNextscene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_TemplateToLua_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"TemplateScene","TemplateScene","",NULL);
  tolua_beginmodule(tolua_S,"TemplateScene");
   tolua_function(tolua_S,"getNextscene",tolua_TemplateToLua_TemplateScene_getNextscene00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_TemplateToLua (lua_State* tolua_S) {
 return tolua_TemplateToLua_open(tolua_S);
};
#endif

