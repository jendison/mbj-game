//auto create by tocpp.rb, plz don't modify it!
//2013-11-01 15:20:30 +0800

#include "TemplateScene.h"

using std::string;

TemplateScene::TemplateScene()
{
	m_sn = 0;
//
}

bool TemplateScene::ReadJsonImpl(const CSJson::Value& obj)
{
		//sn
	 getJsonVal(obj["sn"], m_sn); 
		//游戏里显示在主UI上
	 getJsonVal(obj["ShowName"], m_ShowName); 
		//初始资源数量
	 getJsonVal(obj["initRes"], m_initRes); 
		//场景的地图文件
	 getJsonVal(obj["mapFile"], m_mapFile); 
		//背景音乐
	 getJsonVal(obj["bgMusic"], m_bgMusic); 
		//下一关
	 getJsonVal(obj["completeLuaFunc"], m_completeLuaFunc); 
		//下一关
	 getJsonVal(obj["nextScene"], m_nextScene); 

				//出战兵列表
	
		 const CSJson::Value& tmp = obj["arms"];
		uint32t nSize = tmp.size();
		for (uint32t i = 0; i < nSize; ++i)
		{
			ArmBirthData n;
			n.ReadJsonImpl(tmp[i]);
			m_arms.push_back(n);
		}		
		
	return true;
}



