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

#ifndef NF_EVENT_MODULE_H
#define NF_EVENT_MODULE_H

#include <iostream>
#include "NFComm/NFCore/NFIObject.h"
#include "NFComm/NFPluginModule/NFGUID.h"
#include "NFComm/NFPluginModule/NFIEventModule.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"

class NFEventModule
    : public NFIEventModule
{
public:
    NFEventModule(NFIPluginManager* p)
    {
        pPluginManager = p;
    }


    virtual ~NFEventModule()
    {
    }

	virtual bool Init();
	virtual bool AfterInit();
	virtual bool BeforeShut();
	virtual bool Shut();
	virtual bool Execute();

	virtual bool DoEvent(const NFEventDefine nEventID, const NFDataList& valueList);

	virtual bool ExistEventCallBack(const NFEventDefine nEventID);

	virtual bool RemoveEventCallBack(const NFEventDefine nEventID);

	//////////////////////////////////////////////////////////
	virtual bool DoEvent(const NFGUID self, const NFEventDefine nEventID, const NFDataList& valueList);

	virtual bool ExistEventCallBack(const NFGUID self, const NFEventDefine nEventID);

	virtual bool RemoveEventCallBack(const NFGUID self, const NFEventDefine nEventID);
	virtual bool RemoveEventCallBack(const NFGUID self);

protected:

	virtual bool AddEventCallBack(const NFEventDefine nEventID, const MODULE_EVENT_FUNCTOR_PTR cb);
	virtual bool AddEventCallBack(const NFGUID self, const NFEventDefine nEventID, const OBJECT_EVENT_FUNCTOR_PTR cb);

private:

	NFIKernelModule* m_pKernelodule;

private:
	// for module
	NFList<NFEventDefine> mModuleRemoveListEx;
	NFMapEx<NFEventDefine, NFList<MODULE_EVENT_FUNCTOR_PTR>> mModuleEventInfoMapEx;

	//for object
	NFList<NFGUID> mObjectRemoveListEx;
	NFMapEx<NFGUID, NFMapEx<NFEventDefine, NFList<OBJECT_EVENT_FUNCTOR_PTR>>> mObjectEventInfoMapEx;
};

#endif