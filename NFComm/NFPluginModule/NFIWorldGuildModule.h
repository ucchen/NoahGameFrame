/*
            This file is part of: 
                NoahFrame
            https://github.com/ketoo/NoahGameFrame

   Copyright 2009 - 2019 NoahFrame(NoahGameFrame)

   File creator: flyicegood
   
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


#ifndef NFI_WORLD_Clan_MODULE_H
#define NFI_WORLD_Clan_MODULE_H

#include "NFIModule.h"

class NFIWorldClanModule
    : public NFIModule
{
public:
    virtual const NFGUID& CreateClan(const NFGUID& self, const std::string& strName, const std::string& strRoleName, const int nLevel, const int nJob , const int nDonation , const int nVIP) = 0;
    virtual bool JoinClan(const NFGUID& self, const NFGUID& xClanID) = 0;
    virtual bool LeaveClan(const NFGUID& self, const NFGUID& xClanID) = 0;
    virtual bool UpClanMmember(const NFGUID& self, const NFGUID& xClanID, const NFGUID& xMmember) = 0;
    virtual bool DownClanMmember(const NFGUID& self, const NFGUID& xClanID, const NFGUID& xMmember) = 0;
    virtual bool KickClanMmember(const NFGUID& self, const NFGUID& xClanID, const NFGUID& xMmember) = 0;

    virtual bool GetClanBaseInfo(const NFGUID& self, const NFGUID& xClanID) = 0;
    virtual bool GetClanMemberInfo(const NFGUID& self, const NFGUID& xClanID) = 0;
    virtual bool GetClanMemberInfo(const NFGUID& self, const NFGUID& xClanID, const NFGUID& xMmember) = 0;

    virtual bool GetOnlineMember(const NFGUID& self, const NFGUID& xClan, NFDataList& varMemberList, NFDataList& varGameList) = 0;
    virtual bool MemberOnline(const NFGUID& self, const NFGUID& xClan, const int& nGameID) = 0;
    virtual bool MemberOffline(const NFGUID& self, const NFGUID& xClan) = 0;

private:
};

#endif