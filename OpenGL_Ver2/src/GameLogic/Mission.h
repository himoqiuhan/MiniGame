#pragma once
#include <string>

class Mission
{
private:
	int m_Tag;
	float m_Progress;//任务进度
	std::string m_Name;
	std::string m_Impler;//任务的执行者
	bool isDoing;

public:
	Mission(int tag,std::string name):m_Tag(tag),m_Name(name), m_Progress(0), isDoing(false), m_Impler("NoOne") {}
	~Mission() {}

	inline int GetTag() { return m_Tag; }
	inline int GetProgress() { return m_Progress; }
	inline std::string GetName() { return m_Name; }
	inline std::string GetImpler() { return m_Impler; }
	inline bool GetisDoing() { return isDoing; }


	void ChangeImpler(std::string impler)
	{
		m_Impler = impler;
	}

	void ChangeProgress(float value)
	{
		m_Progress += value;
	}

	void OnDoing() 
	{ 
		isDoing = true; 
	}

};
