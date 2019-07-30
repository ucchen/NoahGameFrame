/*
            This file is part of: 
                NoahFrame
            https://github.com/ketoo/NoahGameFrame

   Copyright 2009 - 2019 NoahFrame(NoahGameFrame)

   File creator: lvsheng.huang
   
   NoahFrame is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#ifndef NFI_SCHEDULE_MODULE_H
#define NFI_SCHEDULE_MODULE_H

#include <string>
#include "NFComm/NFCore/NFMap.hpp"
#include "NFComm/NFCore/NFList.hpp"
#include "NFComm/NFCore/NFDataList.hpp"
#include "NFComm/NFCore/NFDateTime.hpp"
#include "NFComm/NFPluginModule/NFIModule.h"

typedef std::function<int(const NFGUID&, const std::string&, const float, const int)> OBJECT_SCHEDULE_FUNCTOR;
typedef std::function<int(const std::string&, const float, const int)> MODULE_SCHEDULE_FUNCTOR;

typedef NF_SHARE_PTR<OBJECT_SCHEDULE_FUNCTOR> OBJECT_SCHEDULE_FUNCTOR_PTR;//HEART
typedef NF_SHARE_PTR<MODULE_SCHEDULE_FUNCTOR> MODULE_SCHEDULE_FUNCTOR_PTR;//HEART


class  NFScheduleElement
{
public:
	NFScheduleElement()
	{
		mstrScheduleName = "";
		mfIntervalTime = 0.0f;
		mnNextTriggerTime = 0;
		mnStartTime = 0;
		mnRemainCount = 0;
		mnAllCount = 0;
		mbForever = false;
	};

	virtual ~NFScheduleElement()
	{
	}

	void DoHeartBeatEvent();

	std::string mstrScheduleName;
	float mfIntervalTime;
	NFINT64 mnNextTriggerTime;
	NFINT64 mnStartTime;
	int mnRemainCount;
	int mnAllCount;
	bool mbForever;

	NFGUID self;

	NFList<OBJECT_SCHEDULE_FUNCTOR_PTR> mxObjectFunctor;
	NFList<MODULE_SCHEDULE_FUNCTOR_PTR> mxModuleFunctor;
};

class NFIScheduleModule
	:public  NFIModule
{
public:
	virtual ~NFIScheduleModule() {}

	///for module
	virtual bool AddSchedule(const std::string& strScheduleName, const MODULE_SCHEDULE_FUNCTOR_PTR& cb, const float fTime, const int nCount) = 0;
	virtual bool AddSchedule(const std::string& strScheduleName, const MODULE_SCHEDULE_FUNCTOR_PTR& cb, const int nCount, const NFDateTime& date) = 0;
	virtual bool RemoveSchedule(const std::string& strScheduleName) = 0;
	virtual bool ExistSchedule(const std::string& strScheduleName) = 0;

	template<typename BaseType>
	bool AddSchedule(const std::string& strScheduleName, BaseType* pBase, int (BaseType::*handler)(const std::string&, const float, const int), const float fIntervalTime, const int nCount)
	{
		MODULE_SCHEDULE_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		MODULE_SCHEDULE_FUNCTOR_PTR functorPtr(NF_NEW MODULE_SCHEDULE_FUNCTOR(functor));
		return AddSchedule(strScheduleName, functorPtr, fIntervalTime, nCount);
	}
	
	///for object
	virtual bool AddSchedule(const NFGUID self, const std::string& strScheduleName, const OBJECT_SCHEDULE_FUNCTOR_PTR& cb, const float fTime, const int nCount) = 0;
	virtual bool AddSchedule(const NFGUID self, const std::string& strScheduleName, const OBJECT_SCHEDULE_FUNCTOR_PTR& cb, const int nCount, const NFDateTime& date) = 0;
	virtual bool RemoveSchedule(const NFGUID self) = 0;
	virtual bool RemoveSchedule(const NFGUID self, const std::string& strScheduleName) = 0;
	virtual bool ExistSchedule(const NFGUID self, const std::string& strScheduleName) = 0;
	virtual NF_SHARE_PTR<NFScheduleElement> GetSchedule(const NFGUID self, const std::string& strScheduleName) = 0;

	template<typename BaseType>
	bool AddSchedule(const NFGUID self, const std::string& strScheduleName, BaseType* pBase, int (BaseType::*handler)(const NFGUID&, const std::string&, const float, const int), const float fIntervalTime, const int nCount)
	{
		OBJECT_SCHEDULE_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
		OBJECT_SCHEDULE_FUNCTOR_PTR functorPtr(NF_NEW OBJECT_SCHEDULE_FUNCTOR(functor));
		return AddSchedule(self, strScheduleName, functorPtr, fIntervalTime, nCount);
	}
};

#endif
