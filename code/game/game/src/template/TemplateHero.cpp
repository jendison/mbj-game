//auto create by tocpp.rb, plz don't modify it!
//2013-10-23 14:19:45 +0800

#include "TemplateHero.h"

using std::string;

TemplateHero::TemplateHero()
{
	m_sn = 0;
	m_LevelUpIncAttack = 0;
	m_LevelUpIncDefence = 0;
	m_LevelUpIncHP = 0;
	m_LevelUpIncEnergy = 0;

}

bool TemplateHero::ReadJsonImpl(const CSJson::Value& obj)
{
		//
	 getJsonVal(obj["sn"], m_sn); 
		//���õı���ģ��
	 getJsonVal(obj["Arm"], m_Arm); 
		//Ӣ�۵�Ʒ��
	 getJsonVal(obj["Quality"], (int&)m_Quality); 
		//��������������
	 getJsonVal(obj["LevelUpIncAttack"], m_LevelUpIncAttack); 
		//��������������
	 getJsonVal(obj["LevelUpIncDefence"], m_LevelUpIncDefence); 
		//����������HP
	 getJsonVal(obj["LevelUpIncHP"], m_LevelUpIncHP); 
		//��������������
	 getJsonVal(obj["LevelUpIncEnergy"], m_LevelUpIncEnergy); 

	return true;
}



