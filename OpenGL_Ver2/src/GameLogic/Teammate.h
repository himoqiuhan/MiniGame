#pragma once
#include <string>

class Member
{
private:
	int m_Mood = 100;
	int m_Tag;
	std::string m_Mission;
public:
	Member(int tag)
		:m_Tag(tag), m_Mission("No Mission") {};
	~Member() {};

	inline void ChangeMood(int value) { m_Mood += value; }
	inline int GetTag() { return m_Tag; }
	inline std::string GetMission() { return m_Mission; }

	std::string GetMood() 
	{ 
		if (m_Mood > 75)
		{
			return "Good";
		}
		else
		{
			if (m_Mood > 50)
			{
				return "Normal";
			}
			else
			{
				return "Bad";
			}
		}
	}

	int GetEfficiency()
	{
		return m_Mood;
	}

	void ChangeMission(std::string mission)
	{
		m_Mission = mission;
	}

	void SetMood(int value) 
	{ 
		m_Mood = value; 
	}
};

