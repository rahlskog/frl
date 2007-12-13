#ifndef FRL_SSTREAM_H_STREAM_STD_
#define FRL_SSTREAM_H_STREAM_STD_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <sstream>
#include "frl_types.h"

namespace frl
{
	namespace stream_std
	{
		// Переопределяем переменные
		// stringstream
		typedef std::basic_stringstream< frl::Char > StringStream;
		// stringbuf
		typedef std::basic_stringbuf< frl::Char > StringBuf;
		// ostringstream
		typedef std::basic_ostringstream< frl::Char > OutString;
		// istringstream
		typedef std::basic_istringstream< frl::Char > InString;
	}// namespace stream_std
}// namespace FatRat Library

#endif /* FRL_SSTREAM_H_STREAM_STD_ */
