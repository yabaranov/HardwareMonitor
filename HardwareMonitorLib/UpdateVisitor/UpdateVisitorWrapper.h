#pragma once

#include "UpdateVisitor.h"
#include <msclr/auto_gcroot.h>

struct UpdateVisitorWrapper
{
   msclr::auto_gcroot<UpdateVisitor^> API;
};