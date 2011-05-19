///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005-2011 Alexander Wemmer, Philipp Münzel and Anton Volkov
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////////////////////////////////////////////////////////////////////

#include "XPLMProcessing.h"
#include "XPLMPlugin.h"
#include "vascommands.h"
#include "Systems/FMS/FMSSystem.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>

namespace VASCORE {

FMSSystem* global_FMS = 0;

}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID plugin, long input, void* param)
{
    if (plugin != XPLM_PLUGIN_XPLANE)
    {
        switch (input)
        {
        case VASCORE::createFSystem:
        {
            if (VASCORE::global_FMS)
            {
                delete VASCORE::global_FMS;
                VASCORE::global_FMS = 0;
            }
            if (!VASCORE::global_FMS)
                VASCORE::global_FMS = new FMSSystem;
            int* result = static_cast<int*>(param);
            *result = 1;
        }
            break;
        case VASCORE::FSystem:
        {
            VASCORE::InterfaceQuery* iq = static_cast<VASCORE::InterfaceQuery*>(param);
            switch (iq->interfaceId)
            {
            case FMSSystem::iid:
                iq->itsInterface = static_cast<FMSSystem*>(VASCORE::global_FMS);

                break;
            default:
                std::abort();
                iq->itsInterface = 0;
                break;
            }
        }
            break;

        default:
             printf("unrecognized input to vascore, probably another plugin. Ignore.\n");
        }
    }
}


PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc)
{
    strcpy(outName, "Embedded vasCore");
    strcpy(outSig, "org.vas-project.embedded-core");
    strcpy(outDesc, "Provides core navigation functionality of vasFMC to X-Plane aircraft.");
    return 1;
}

PLUGIN_API int XPluginEnable(void)
{
    return 1;
}

PLUGIN_API void XPluginDisable(void)
{

}

PLUGIN_API void XPluginStop(void)
{
    delete VASCORE::global_FMS;
}
