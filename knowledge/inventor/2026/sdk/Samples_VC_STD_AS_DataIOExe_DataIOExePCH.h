#ifndef _DATAIOEXEPCH_
#define _DATAIOEXEPCH_

#include <atlbase.h>
#include <iostream>
#include <map>
#include <math.h>

// This pre-processor symbol needs to be explicitly defined in the project.
// It is left undefined on purpose. The intention is to explicitly flag to the user, 
// the need to reset the project settings appropriately, BEFORE building this project.
//

#ifndef USING_MY_ACIS
 #error You need to adjust the project settings to point to your ACIS installation (see readme.txt). You need a copy of ACIS to run this sample.
#endif

#include "kernel/kernapi/api/kernapi.hxx"
#include "kernel/kerndata/lists/lists.hxx"
#include "kernel/kerndata/top/body.hxx"
#include "kernel/kerndata/top/edge.hxx"
#include "pid_husk/api/pidapi.hxx"
#include "pid_husk/pid/pid.hxx"


#pragma warning(disable:4192) // disable 'automatically excluding * while importing type library *' warning
#pragma warning(disable : 4278) // 'name':identifier in type library 'library' is already a macro

#include "InventorUtils.h"

#endif
