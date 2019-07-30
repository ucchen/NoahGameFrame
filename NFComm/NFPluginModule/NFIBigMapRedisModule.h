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

#ifndef NFI_BIGMAP_REDIS_MODULE_H
#define NFI_BIGMAP_REDIS_MODULE_H

#include "NFIModule.h"
#include "NFComm/NFMessageDefine/NFMsgDefine.h"

class NFIBigMapRedisModule
    : public NFIModule
{
public:

	virtual bool GetGridBaseInfo(const std::string& strGridID, NFMsg::BigMapGridBaseInfo& xBaseInfo) = 0;
	virtual bool GetGridBaseInfo(std::vector<NFMsg::BigMapGridBaseInfo>& xBaseInfo) = 0;
	virtual bool GetGridBaseInfo(const std::vector<std::string>& strGridID, std::vector<NFMsg::BigMapGridBaseInfo>& xBaseInfo) = 0;

	virtual bool GetGridLeaveMsgInfo(const std::string& strGridID, std::vector<NFMsg::BigMapLeaveMsg>& xLeaveMsgList) = 0;
	virtual bool GetGridWarHistoryInfo(const std::string& strGridID, std::vector<NFMsg::BigMapWarHistory>& xWarHistoryList) = 0;
	virtual bool GetGridStationInfo(const std::string& strGridID, std::vector<NFMsg::GridClanBaseInfo>& xWarHistoryList) = 0;

	virtual bool SetGridBaseInfo(const std::string& strGridID, const NFMsg::BigMapGridBaseInfo& xBaseInfo) = 0;

	virtual bool AddGridLeaveMsgInfo(const std::string& strGridID, const NFMsg::BigMapLeaveMsg& xLeaveMsg) = 0;
	virtual bool AddGridWarHistoryInfo(const std::string& strGridID, const NFMsg::BigMapWarHistory& xWarHistory) = 0;
	
	virtual bool AddGridStationInfo(const std::string& strGridID, const NFGUID& self, const int nResource) = 0;
	virtual bool RemoveGridStationInfo(const std::string& strGridID, const NFGUID& self, const int nResource) = 0;


};

#endif