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


#ifndef NOAHFRAME_NFSKILLCOOLDOWNMODULE_H
#define NOAHFRAME_NFSKILLCOOLDOWNMODULE_H


#include <NFComm/NFPluginModule/NFISkillModule.h>
#include <NFComm/NFCore/NFIObject.h>
#include <NFComm/NFPluginModule/NFINetModule.h>
#include <NFComm/NFPluginModule/NFIKernelModule.h>
#include <NFComm/NFPluginModule/NFIPropertyModule.h>
#include <NFComm/NFPluginModule/NFILogModule.h>
#include <NFComm/NFPluginModule/NFIEventModule.h>
#include <NFComm/NFPluginModule/NFISkillConsumeManagerModule.h>
#include <NFComm/NFPluginModule/NFIElementModule.h>
#include <NFComm/NFPluginModule/NFISceneProcessModule.h>
#include <NFComm/NFPluginModule/NFIGameServerNet_ServerModule.h>
#include <NFComm/NFPluginModule/NFISkillCooldownModule.h>

class NFSkillCooldownModule
        : public NFISkillCooldownModule
{
public:

    NFSkillCooldownModule( NFIPluginManager* p )
    {
        pPluginManager = p;
    }

    virtual bool AfterInit();

    virtual void AddSkillCD( const NFGUID& self, const std::string& strSkillName );
    virtual bool ExistSkillCD( const NFGUID& self, const std::string& strSkillName );

private:
	std::string mstrCommonSkillID = "CommonSkillID";
private:

    NFIKernelModule* m_pKernelModule;
    NFIElementModule* m_pElementModule;
};

#endif //NOAHFRAME_NFSKILLCOOLDOWNMODULE_H
