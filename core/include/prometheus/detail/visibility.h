#pragma once

#ifndef PROMETHEUSCPP_API
#if __GNUC__ >= 4
#define PROMETHEUSCPP_API __attribute__((visibility("default")))
#else
#define PROMETHEUSCPP_API
#endif
#endif
