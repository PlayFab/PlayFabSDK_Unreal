#pragma once

#ifndef RETURN_HR
#define RETURN_HR(hr)                   return(hr)
#endif

#ifndef RETURN_IF_FAILED
#define RETURN_IF_FAILED(hr)            do { HRESULT __hrRet = hr; if (FAILED(__hrRet)) { RETURN_HR(__hrRet); }} while (0, 0)
#endif

#define RETURN_FALSE_IF_FAILED(hr)      do { HRESULT __hrRet = hr; if (FAILED(__hrRet)) { return false; }} while (0, 0)
#define RETURN_FALSE_IF_NULL(ptr)       do { if (!(ptr)) { return false; }} while (0, 0)
#define RETURN_FALSE_IF_EMPTY(str)      do { if ((str).IsEmpty()) { return false; }} while (0, 0)