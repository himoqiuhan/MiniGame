#pragma once

#include <string>
#include <iostream>

using namespace std;

const int MaxMissionNum = 2;
//自定义类型，来规定队员的职能。分别为程序、美工和策划。
enum TeamMateType
{
	CX, MG, CH, Null
};
//描述任务成功程度。
enum Success_Value
{
	S = 90, A = 80, B = 60, D = 0, N = -1
};
//打分函数
Success_Value judge(int demand, int ability)
{
	if (ability >= demand)
	{
		return S;
	}
	else if (demand - ability <= 10)
	{
		return A;
	}
	else
	{
		return B;
	}
}
//声明一下任务类,方便使用.
class Mission;
//声明一下任务循环单链表。
// 阉割了。
//class MissionDemandCLinkListNode;

//第一个类是队员类，为队员的最基类,且为虚基类。
class TeamMate
{
public:
	TeamMate() :name("null"), id("null"), mateType(Null), mood(100), missionNum(0), description("null")
	{
		*missions = NULL;
	};
	TeamMate(string newN, string newID, TeamMateType newT, string newD) :name(newN), id(newID), mateType(newT),
		mood(100), missionNum(0), description(newD)
	{
		*missions = NULL;
	};
	~TeamMate() {};
	virtual void ShowDescription() const = 0;
	virtual void ShowStatus() const = 0;
	virtual string getType() const final;
	virtual void ClearMission() final;
	virtual int getmood() final
	{
		return this->mood;
	};
	virtual void consumeMood() final
	{
		if (this->mood >= 20)
		{
			this->mood -= 20;
		}
		else
		{
			this->mood = 0;
		}
	}
	virtual void getMission(Mission* newM) final
	{
		if (missionNum == MaxMissionNum)
		{
			missions[0] = missions[1];
			missions[1] = newM;
		}
		else
		{
			if (missionNum = 0)
			{
				missions[0] = newM;
				missionNum++;
			}
			else
			{
				missions[1] = newM;
				missionNum++;
			}
		}
	}
	virtual void moodUp() final
	{
		if (mood <= 60)
		{
			mood += 40;
		}
		else
		{
			mood = 100;
		}
	}
private:
	const string name;
	const string id;
	const TeamMateType mateType;
	int mood;
	int missionNum;
	Mission* missions[MaxMissionNum];
	const string description;
};

void TeamMate::ClearMission()
{
	*missions = NULL;
	missionNum = 0;
}

string TeamMate::getType() const
{
	switch (this->mateType)
	{
	case CX:
		return "CX";
		break;
	case MG:
		return "MG";
		break;
	case CH:
		return "CH";
		break;
	default:
		return "Null";
		break;
	}
}
//这几个子类拿来区分职能，并且可被构造。
class CHType :public TeamMate
{
public:
	CHType(string newN, string newID, TeamMateType newT, string newD,
		int newImagin = 0, int newLogical = 0, int newCom = 0);
	~CHType() {};
	void  ShowDescription() const override;
	void  ShowStatus() const override;
	int getIma() const;
	int getLogic() const;
	int getCom() const;
private:
	const int imagination_Ability;
	const int logical_Ability;
	const int communication_Ability;
};
CHType::CHType(string newN, string newID, TeamMateType newT, string newD,
	int newImagin, int newLogical, int newCom) :TeamMate(newN, newID, newT,
		newD), imagination_Ability(newImagin), logical_Ability(newLogical), communication_Ability(newCom)
{

}
int CHType::getIma() const
{
	return this->imagination_Ability;
}
int CHType::getLogic() const
{
	return this->logical_Ability;
}
int CHType::getCom() const
{
	return this->communication_Ability;
}
class CXType :public TeamMate
{
public:
	CXType(string newN, string newID, TeamMateType newT, string newD,
		int newIQ, int newP, int newGra);
	~CXType() {};
	void  ShowDescription() const override;
	void  ShowStatus() const override;
	int getIQ() const;
	int getPrograming() const;
	int getGraphic() const;
private:
	const int IQ;
	const int programming_Ability;
	const int graphic_Ability;
};
int CXType::getIQ() const
{
	return this->IQ;
}
int CXType::getPrograming() const
{
	return this->programming_Ability;
}
int CXType::getGraphic() const
{
	return this->graphic_Ability;
}
CXType::CXType(string newN, string newID, TeamMateType newT, string newD,
	int newIQ, int newP, int newGra) :TeamMate(newN, newID, newT,
		newD), IQ(newIQ), programming_Ability(newP), graphic_Ability(newGra)
{

}
class MGType :public TeamMate
{
public:
	MGType(string newN, string newID, TeamMateType newT, string newD, int new2D = 0, int new3D = 0);
	~MGType() {};
	void  ShowDescription() const override;
	void  ShowStatus() const override;
	int get2D() const;
	int get3D() const;
private:
	const int twoD_Ability;
	const int threeD_Ability;
};
int MGType::get2D() const
{
	return this->twoD_Ability;
}
int MGType::get3D() const
{
	return this->threeD_Ability;
}
MGType::MGType(string newN, string newID, TeamMateType newT, string newD, int new2D,
	int new3D) :TeamMate(newN, newID, newT,
		newD), twoD_Ability(new2D), threeD_Ability(new3D)
{

}
//这个类是用来描述任务的，可被实例化。
class Mission
{
public:
	Mission(string newN, string newID, string newDes, string newDA, int newDV) :
		name(newN), id(newID), description(newDes), DemandedAbility(newDA), DemandedValue(newDV), mission_Score(N)
		, isUnlock(false)
	{};
	~Mission()
	{};
	void tryFinish(TeamMate* theMate);//这是用来判断队员完成任务评分的函数，只有isUnlock=true时才应该被执行。
	void Unlock() { isUnlock = true; }
private:
	const string name;
	const string id;
	const string description;
	const string DemandedAbility;
	const int DemandedValue;
	int mission_Score;
	bool isUnlock;
};
void Mission::tryFinish(TeamMate* theMate)
{
	theMate->consumeMood();
	if (this->DemandedAbility == "Null")
	{
		theMate->moodUp();
		return;
	}
	if (this->DemandedAbility == "imagination_Ability" || this->DemandedAbility == "logical_Ability" ||
		this->DemandedAbility == "communication_Ability")
	{
		if (theMate->getType() != "CH")
		{
			this->mission_Score = D;
			this->isUnlock = false;
		}
		else
		{
			CHType* theCH = (CHType*)theMate;
			if (this->DemandedAbility == "imagination_Ability")
			{
				this->mission_Score = judge(DemandedValue, theCH->getIma());
			}
			else if (this->DemandedAbility == "logical_Ability")
			{
				this->mission_Score = judge(DemandedValue, theCH->getLogic());
			}
			else
			{
				this->mission_Score = judge(DemandedValue, theCH->getCom());
			}
		}
	}
	else if (this->DemandedAbility == "IQ" || this->DemandedAbility == "programming_Ability" || this->DemandedAbility
		== "graphic_Ability")
	{
		if (theMate->getType() != "CH")
		{
			this->mission_Score = D;
			this->isUnlock = false;
		}
		else
		{
			CXType* theCX = (CXType*)theMate;
			if (this->DemandedAbility == "IQ")
			{
				this->mission_Score = judge(DemandedValue, theCX->getIQ());
			}
			else if (this->DemandedAbility == "programming_Ability")
			{
				this->mission_Score = judge(DemandedValue, theCX->getPrograming());
			}
			else if (this->DemandedAbility == "graphic_Ability")
			{
				this->mission_Score = judge(DemandedValue, theCX->getGraphic());
			}
		}
	}
	else
	{
		if (theMate->getType() != "MG")
		{
			this->mission_Score = D;
			this->isUnlock = false;
		}
		else
		{
			MGType* theMG = (MGType*)theMate;
			if (this->DemandedAbility == "twoD_Ability")
			{
				this->mission_Score = judge(DemandedValue, theMG->get2D());
			}
			else
			{
				this->mission_Score = judge(DemandedValue, theMG->get3D());
			}
		}
	}
	if (theMate->getmood() >= 60)
	{
		mission_Score += 10;
	}

}
//最后实现一下任务循环单链表。

//阉割了。
//class MissionDemandCLinkListNode
//{
//
//public:
//	MissionDemandCLinkListNode();
//	MissionDemandCLinkListNode(string newDe,int newVa);
//	~MissionDemandCLinkListNode();
//	void PushElem(string newDe, int newVa);
//	string getDemandedType() const;
//	int getDemandedValue() const;
//	MissionDemandCLinkListNode* getNext() const;
//private:
//	const string DemandedType;
//	const int DemandedValue;//大于这个值就是S，差10A，差10以上B，不对D。
//	MissionDemandCLinkListNode* next;
//};
//
//MissionDemandCLinkListNode::MissionDemandCLinkListNode()
//{
//	next = NULL;
//}
//MissionDemandCLinkListNode::MissionDemandCLinkListNode(string newDe, int newVa)
//{
//	DemandedType = newDe;
//	DemandValue = newVa;
//	next = NULL;
//}
//MissionDemandCLinkListNode::~MissionDemandCLinkListNode()
//{
//	MissionDemandCLinkListNode * p=this->next,*pre=this;
//	p = p->next, pre = pre->next;
//	while (p != this)
//	{
//		delete pre;
//		pre = p, p = p->next;
//	}
//	delete pre;
//	delete p;
//}
//void MissionDemandCLinkListNode::PushElem(string newDe, int newVa)
//{
//	MissionDemandCLinkListNode* newP = new MissionDemandCLinkListNode(newDe, newVa);
//	MissionDemandCLinkListNode* p = this;
//	//找到最后一个元素。
//	while (p->next != this)
//	{
//		p = p->next;
//	}
//	//将newP的next置为头，然后将newP放在最后一个元素后面.
//	newP->next = this;
//	p->next = newP;
//}
//string MissionDemandCLinkListNode::getDemandedType() const
//{
//	return this->DemandedType;
//}
//int MissionDemandCLinkListNode::getDemandedValue() const
//{
//	return this->DemandedValue;
//}
//MissionDemandCLinkListNode* MissionDemandCLinkListNode::getNext() const 
//{
//	return this->next;
//}

//任务树
class MissionBTreeNode
{
public:
	MissionBTreeNode();
	~MissionBTreeNode();
	void PreOrderShowUnlockedMission();
	void UnlockNext();
	MissionBTreeNode* lchild;
	MissionBTreeNode* rchild;
	Mission* data;
private:

};
MissionBTreeNode::MissionBTreeNode()
{
	lchild = NULL;
	rchild = NULL;
	data = NULL;
}
MissionBTreeNode::~MissionBTreeNode()
{
	if (this != NULL)
	{
		this->lchild->~MissionBTreeNode();
		this->rchild->~MissionBTreeNode();
		delete(this);
	}
}
void MissionBTreeNode::UnlockNext()
{
	this->lchild->data->Unlock();
	this->rchild->data->Unlock();
}