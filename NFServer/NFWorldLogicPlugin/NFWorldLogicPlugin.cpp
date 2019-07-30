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

#include "NFWorldLogicModule.h"
#include "NFWorldPVPModule.h"
#include "NFWorldPropsModule.h"
#include "NFWorldLogicPlugin.h"

NF_EXPORT void DllStartPlugin(NFIPluginManager* pm)
{
    CREATE_PLUGIN(pm, NFWorldLogicPlugin)
};

NF_EXPORT void DllStopPlugin(NFIPluginManager* pm)
{
    DESTROY_PLUGIN(pm, NFWorldLogicPlugin)
};

//////////////////////////////////////////////////////////////////////////

const int NFWorldLogicPlugin::GetPluginVersion()
{
    return 0;
}

const std::string NFWorldLogicPlugin::GetPluginName()
{
    return GET_CLASS_NAME(NFWorldLogicPlugin);
}

void NFWorldLogicPlugin::Install()
{
	REGISTER_MODULE(pPluginManager, NFIWorldLogicModule, NFWorldLogicModule)
	REGISTER_MODULE(pPluginManager, NFIWorldPVPModule, NFWorldPVPModule)
	REGISTER_MODULE(pPluginManager, NFIWorldPropsModule, NFWorldPropsModule)
}

void NFWorldLogicPlugin::Uninstall()
{
	UNREGISTER_MODULE(pPluginManager, NFIWorldPropsModule, NFWorldPropsModule)
	UNREGISTER_MODULE(pPluginManager, NFIWorldPVPModule, NFWorldPVPModule)
	UNREGISTER_MODULE(pPluginManager, NFIWorldLogicModule, NFWorldLogicModule)
}
