#include "echo.h"
#include "prefix.h"

#include <tll/channel/module.h>

TLL_DEFINE_IMPL(Echo);
TLL_DEFINE_IMPL(Prefix);

TLL_DEFINE_MODULE(Echo, Prefix);
