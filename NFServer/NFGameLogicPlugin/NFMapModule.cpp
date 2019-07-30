/*
            This file is part of: 
                NoahFrame
            https://github.com/ketoo/NoahGameFrame

   Copyright 2009 - 2018 NoahFrame(NoahGameFrame)

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


#include "NFMapModule.h"
#include "NFComm/NFMessageDefine/NFProtocolDefine.hpp"

bool NFMapModule::Init()
{
	m_pNetModule = pPluginManager->FindModule<NFINetModule>();
	//m_pBigMapRedisModule = pPluginManager->FindModule<NFIBigMapRedisModule>();
	m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();
	m_pLogicClassModule = pPluginManager->FindModule<NFIClassModule>();
	m_pElementModule = pPluginManager->FindModule<NFIElementModule>();
	//m_pGuildRedisModule = pPluginManager->FindModule<NFIGuildRedisModule>();
	m_pGameServerNet_ServerModule = pPluginManager->FindModule<NFIGameServerNet_ServerModule>();

    return true;
}

bool NFMapModule::Shut()
{
    return true;
}

bool NFMapModule::Execute()
{
    return true;
}

bool NFMapModule::AfterInit()
{

	if (!m_pNetModule->AddReceiveCallBack(NFMsg::EGameMsgID::EGMI_REQ_BIG_MAP_INFO, this, &NFMapModule::ReqBigMapsInfo)) { return false; }
	if (!m_pNetModule->AddReceiveCallBack(NFMsg::EGameMsgID::EGMI_REQ_MAP_GRID_INFO, this, &NFMapModule::ReqMapTitleInfo)) { return false; }

	if (!m_pNetModule->AddReceiveCallBack(NFMsg::EGameMsgID::EGMI_REQ_HOLD_MAP_GRID, this, &NFMapModule::ReqStation)) { return false; }
	if (!m_pNetModule->AddReceiveCallBack(NFMsg::EGameMsgID::EGMI_REQ_GET_MAP_GRID_AWARD, this, &NFMapModule::ReqGetMapAward)) { return false; }
	if (!m_pNetModule->AddReceiveCallBack(NFMsg::EGameMsgID::EGMI_REQ_LEAVE_MSG_MAP_GRID, this, &NFMapModule::ReqLeaveMsgToMap)) { return false; }

	if (!m_pNetModule->AddReceiveCallBack(NFMsg::EGameMsgID::EGMI_REQ_MAP_GRID_HUNTING, this, &NFMapModule::ReqMapHunting)) { return false; }
	if (!m_pNetModule->AddReceiveCallBack(NFMsg::EGameMsgID::EGMI_REQ_MAP_GRID_KING_WAR, this, &NFMapModule::ReqMapKingWar)) { return false; }

    return true;
}

void NFMapModule::ReqBigMapsInfo(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	CLIENT_MSG_PROCESS( nMsgID, msg, nLen, NFMsg::ReqBigMapInfo);


	NF_SHARE_PTR<NFIClass> xLogicClass = m_pLogicClassModule->GetElement(NFrame::Map::ThisName());
	/*
	//find all title info
	NFMsg::AckBigMapInfo xAckBigMapInfo;
	std::vector<NFMsg::BigMapGridBaseInfo> xBigMapGridBaseInfoList;
	if (m_pBigMapRedisModule->GetGridBaseInfo(xBigMapGridBaseInfoList))
	{
		for (std::vector<NFMsg::BigMapGridBaseInfo>::iterator it = xBigMapGridBaseInfoList.begin();
		it != xBigMapGridBaseInfoList.end(); ++it)
		{
			NFMsg::BigMapGridBaseInfo* pBigMapGridBaseInfo = xAckBigMapInfo.add_grid_base_info();
			if (pBigMapGridBaseInfo)
			{
				pBigMapGridBaseInfo->CopyFrom(*it);
			}
		}

		m_pGameServerNet_ServerModule->SendMsgPBToGate(NFMsg::EGMI_ACK_BIG_MAP_INFO, xAckBigMapInfo, nPlayerID);
	}
	*/
}

void NFMapModule::ReqMapTitleInfo(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	CLIENT_MSG_PROCESS( nMsgID, msg, nLen, NFMsg::ReqBigMapGridInfo);
	
	/*
	NFMsg::AckBigMapGridInfo xAckBigMapGridInfo;

	int nTitleCount = xMsg.map_title_id_size();
	for (int i = 0; i < nTitleCount; ++i)
	{
		std::string strTitleID = xMsg.map_title_id(i);

		if (!m_pElementModule->ExistElement(strTitleID))
		{
			continue;
		}

		NFMsg::BigMapGridBaseInfo xGridBaseInfo;
		if (!m_pBigMapRedisModule->GetGridBaseInfo(strTitleID, xGridBaseInfo))
		{
			continue;
		}

		std::vector<NFMsg::BigMapLeaveMsg> xLeaveMsgList;
		if (!m_pBigMapRedisModule->GetGridLeaveMsgInfo(strTitleID, xLeaveMsgList))
		{
			continue;
		}

		std::vector<NFMsg::BigMapWarHistory> xWarHistoryList;
		if (!m_pBigMapRedisModule->GetGridWarHistoryInfo(strTitleID, xWarHistoryList))
		{
			continue;
		}

		NFMsg::BigMapGridDetailInfo* pBigMapGridDetailInfo = xAckBigMapGridInfo.add_map_data();
		if (pBigMapGridDetailInfo)
		{
			pBigMapGridDetailInfo->mutable_grid_base_info()->CopyFrom(xGridBaseInfo);
		}

		std::vector<NFMsg::BigMapLeaveMsg>::iterator itLeaveMsg = xLeaveMsgList.begin();
		for (; itLeaveMsg != xLeaveMsgList.end(); ++itLeaveMsg)
		{
			NFMsg::BigMapLeaveMsg* pBigMapLeaveMsg = pBigMapGridDetailInfo->add_leave_msg();
			if (pBigMapLeaveMsg)
			{
				pBigMapLeaveMsg->CopyFrom(*itLeaveMsg);
			}
		}

		std::vector<NFMsg::BigMapWarHistory>::iterator itWar = xWarHistoryList.begin();
		for (; itWar != xWarHistoryList.end(); ++itWar)
		{
			NFMsg::BigMapWarHistory* pBigMapWarHistory = pBigMapGridDetailInfo->add_war_history();
			if (pBigMapWarHistory)
			{
				pBigMapWarHistory->CopyFrom(*itWar);
			}
		}
	}

	m_pGameServerNet_ServerModule->SendMsgPBToGate(NFMsg::EGMI_ACK_MAP_GRID_INFO, xAckBigMapGridInfo, nPlayerID);
	*/
}

void NFMapModule::ReqStation(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	CLIENT_MSG_PROCESS( nMsgID, msg, nLen, NFMsg::ReqHoldMapGrid);

	if (!m_pElementModule->ExistElement(xMsg.map_title_id()))
	{
		return;
	}
	/*
	NFGUID xGuildID = NFINetModule::PBToNF(xMsg.guild_id());
	NF_SHARE_PTR<NFIPropertyManager> xPropertyManager = m_pGuildRedisModule->GetGuildCachePropertyInfo(xGuildID);
	if (!xPropertyManager)
	{
		return;
	}
	//remove form last grid

	int nResourece = xPropertyManager->GetPropertyInt(NFrame::Guild::KingWarResource());
	m_pBigMapRedisModule->AddGridStationInfo(xMsg.map_title_id(), xGuildID, nResourece);
	*/

}

void NFMapModule::ReqGetMapAward(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	CLIENT_MSG_PROCESS( nMsgID, msg, nLen, NFMsg::ReqGetMapAward);

	if (!m_pElementModule->ExistElement(xMsg.map_title_id()))
	{
		return;
	}

	//get guild informatin and send mail to all members to send award item
}

void NFMapModule::ReqLeaveMsgToMap(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	CLIENT_MSG_PROCESS( nMsgID, msg, nLen, NFMsg::ReqLeaveMapMsg);

	if (!m_pElementModule->ExistElement(xMsg.map_title_id()))
	{
		return;
	}

	//m_pBigMapRedisModule->AddGridLeaveMsgInfo(xMsg.map_title_id(), xMsg.leave_msg());
}

void NFMapModule::ReqMapHunting(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	CLIENT_MSG_PROCESS( nMsgID, msg, nLen, NFMsg::ReqMapHunting);
	/*
	if (!m_pElementModule->ExistElement(xMsg.map_title_id()))
	{
		return;
	}

	NFMsg::BigMapGridBaseInfo xGridBaseInfo;
	if (!m_pBigMapRedisModule->GetGridBaseInfo(xMsg.map_title_id(), xGridBaseInfo))
	{
		return;
	}

	xGridBaseInfo.set_hurting_time(pPluginManager->GetNowTime());
	xGridBaseInfo.mutable_hurter()->CopyFrom(NFINetModule::NFToPB(nPlayerID));

	m_pBigMapRedisModule->SetGridBaseInfo(xMsg.map_title_id(), xGridBaseInfo);
	*/
	//show msgbox
}

void NFMapModule::ReqMapKingWar(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	CLIENT_MSG_PROCESS( nMsgID, msg, nLen, NFMsg::ReqMapKingWar);

	if (!m_pElementModule->ExistElement(xMsg.map_title()))
	{
		return;
	}
	/*

	NFMsg::BigMapGridBaseInfo xGridBaseInfo;
	if (!m_pBigMapRedisModule->GetGridBaseInfo(xMsg.map_title(), xGridBaseInfo))
	{
		return;
	}

	xGridBaseInfo.set_kingwar_time(pPluginManager->GetNowTime());
	xGridBaseInfo.mutable_kingwarrer()->CopyFrom(NFINetModule::NFToPB(nPlayerID));

	m_pBigMapRedisModule->SetGridBaseInfo(xMsg.map_title(), xGridBaseInfo);
	*/
	//show msgbox
}

void NFMapModule::EndMapHunting(const std::string& strTitleID)
{
	/*
	NFMsg::BigMapGridBaseInfo xGridBaseInfo;
	if (!m_pBigMapRedisModule->GetGridBaseInfo(strTitleID, xGridBaseInfo))
	{
		return;
	}

	xGridBaseInfo.set_hurting_time(0);
	xGridBaseInfo.mutable_kingwarrer()->CopyFrom(NFINetModule::NFToPB(NFGUID()));

	m_pBigMapRedisModule->SetGridBaseInfo(strTitleID, xGridBaseInfo);
	*/
	//show msgbox and send mail to award
}

void NFMapModule::EndMapKingWar(const std::string& strTitleID)
{
	/*
	NFMsg::BigMapGridBaseInfo xGridBaseInfo;
	if (!m_pBigMapRedisModule->GetGridBaseInfo(strTitleID, xGridBaseInfo))
	{
		return;
	}

	xGridBaseInfo.set_kingwar_time(0);
	xGridBaseInfo.mutable_kingwarrer()->CopyFrom(NFINetModule::NFToPB(NFGUID()));

	m_pBigMapRedisModule->SetGridBaseInfo(strTitleID, xGridBaseInfo);
	*/
	//show msgbox and send mail to award
}

void NFMapModule::SetKingForGrid(const std::string& strTitleID, const NFGUID& xGuildID)
{
	/*
	if (!m_pElementModule->ExistElement(strTitleID))
	{
		return;
	}

	NFMsg::BigMapGridBaseInfo xGridBaseInfo;
	if (!m_pBigMapRedisModule->GetGridBaseInfo(strTitleID, xGridBaseInfo))
	{
		return;
	}

	//get all guild information to set in grid base info
	NF_SHARE_PTR<NFIPropertyManager> xPropertyManager = m_pGuildRedisModule->GetGuildCachePropertyInfo(xGuildID);
	const NFGUID xGUID = xPropertyManager->GetPropertyObject(NFrame::Guild::GuildID());
	const std::string& strIcon = xPropertyManager->GetPropertyString(NFrame::Guild::GuildIcon());
	const int nLevel = xPropertyManager->GetPropertyInt(NFrame::Guild::GuildLevel());
	const int nMemberCount = xPropertyManager->GetPropertyInt(NFrame::Guild::GuildMemeberCount());
	const int nResource = xPropertyManager->GetPropertyInt(NFrame::Guild::KingWarResource());

	xGridBaseInfo.mutable_guild_info()->mutable_id()->CopyFrom(NFINetModule::NFToPB(xGUID));
	xGridBaseInfo.mutable_guild_info()->set_level(nLevel);
	xGridBaseInfo.mutable_guild_info()->set_count(nMemberCount);
	xGridBaseInfo.mutable_guild_info()->set_icon(strIcon);
	xGridBaseInfo.mutable_guild_info()->set_resource(nResource);

	m_pBigMapRedisModule->SetGridBaseInfo(strTitleID, xGridBaseInfo);
	*/
}

void NFMapModule::LeaveStation(const std::string& strTitleID, const NFGUID& xGuildID)
{

}

