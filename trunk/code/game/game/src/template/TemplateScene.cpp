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
		//��Ϸ����ʾ����UI��
	 getJsonVal(obj["ShowName"], m_ShowName); 
		//��ʼ��Դ����
	 getJsonVal(obj["initRes"], m_initRes); 
		//�����ĵ�ͼ�ļ�
	 getJsonVal(obj["mapFile"], m_mapFile); 
		//��������
	 getJsonVal(obj["bgMusic"], m_bgMusic); 
		//��һ��
	 getJsonVal(obj["completeLuaFunc"], m_completeLuaFunc); 
		//��һ��
	 getJsonVal(obj["nextScene"], m_nextScene); 

				//��ս���б�
	
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



