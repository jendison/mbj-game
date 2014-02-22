//auto create by tocpp.rb, plz don't modify it!
//2013-11-01 15:20:30 +0800
#include <string>
#include "cocos-ext.h"
#include "TemplateCommon.h"
#include "TypeDefine.h"
#include "TemplateBase.h"

#ifndef _TEMPLATESCENE_H__
#define _TEMPLATESCENE_H__
using std::string;

struct ArmBirthData:public TemplateBase
{
	ArmBirthData()
	{
		time = 0;
	}
	//兵
	int32t arm;
	//以场景创建完为0
	int32t time;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//兵
	 getJsonVal(obj["arm"], arm); 
		//以场景创建完为0
	 getJsonVal(obj["time"], time); 
		return true;
	}
};

class TemplateScene : public TemplateBase
{
public:
	TemplateScene();
	~TemplateScene(){}
	
	bool ReadJsonImpl(const CSJson::Value& obj);
	int32t getSNImpl() {return m_sn;}
	
public:
	const std::string& getShowname() const{ return m_ShowName;}
	int32t getInitres() const{ return m_initRes;}
	const std::string& getMapfile() const{ return m_mapFile;}
	const std::string& getBgmusic() const{ return m_bgMusic;}
	const std::string& getCompleteluafunc() const{ return m_completeLuaFunc;}
	int32t getNextscene() const{ return m_nextScene;}
	const vector<ArmBirthData>& getArms() const{ return m_arms;}

	
private:
	//sn
	int32t m_sn;
	//游戏里显示在主UI上
	std::string m_ShowName;
	//初始资源数量
	int32t m_initRes;
	//场景的地图文件
	std::string m_mapFile;
	//背景音乐
	std::string m_bgMusic;
	//下一关
	std::string m_completeLuaFunc;
	//下一关
	int32t m_nextScene;
	//出战兵列表
	vector<ArmBirthData> m_arms;

};

#endif //_TEMPLATESCENE_H__
