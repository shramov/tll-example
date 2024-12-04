#include "echo.h"
#include "logic.h"
#include "prefix.h"

#include <tll/channel/module.h>

TLL_DEFINE_IMPL(Echo);
TLL_DEFINE_IMPL(EchoLogic);
TLL_DEFINE_IMPL(Prefix);

TLL_DEFINE_MODULE(Echo, EchoLogic, Prefix);
