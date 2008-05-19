#include "logging/frl_logging_writers.h"

namespace frl
{
namespace logging
{

namespace private_
{
String getStr( const logging::ListLogElements &elements, const frl::logging::LogParameter &param )
{
	String tmp;
	for( logging::ListLogElements::const_iterator it = elements.begin(); it != elements.end(); ++it )
		tmp += (*it)->proccess( param );
	return tmp;
}
}

lock::SemaphoreMutex ConsoleWriter::guard;

ConsoleWriter::~ConsoleWriter()
{
}

void ConsoleWriter::write( const ListLogElements &elements, const LogParameter &param )
{
	lock::ScopeGuard scopeGuard( guard );
	console_std::Out << private_::getStr( elements, param );
}

void FileWriter::closeFile()
{
	if( desc != io::fs::InvalidFileDescriptor )
		io::fs::close( desc );
}

FileWriter::FileWriter()
	:	desc( io::fs::InvalidFileDescriptor)
{
}

FileWriter::FileWriter( const String &fileName_ )
	:	desc( io::fs::InvalidFileDescriptor ),
		fileName( fileName_ )
{
	if( fileName.empty() )
		return;
	openFile();
}

FileWriter::FileWriter( const FileWriter &other )
	:	ILogWriter( other ),
		desc( io::fs::InvalidFileDescriptor )
{
	if( other.fileName.empty() )
		return;
	fileName = FRL_STR("new");
	openFile();
}

void FileWriter::openFile()
{
	String dir = io::fs::getCurrentDirectory();
	io::fs::addSlashToEndPath( dir );
	fileName = dir + fileName;
	try
	{
		if( ! io::fs::isExist( fileName) )
		{
			io::fs::open( desc, fileName, io::fs::openWriteOnly | io::fs::openCreate );
			#if( FRL_CHARACTER == FRL_CHARACTER_UNICODE  )
			unsigned short signature = 0xFEFF;
			io::fs::write( desc, &signature, 2 );
			#endif
		}
		else
		{
			io::fs::open( desc, fileName, io::fs::openWriteOnly | io::fs::openCreate | io::fs::openAppend );
		}
	}
	catch( frl::Exception& )
	{
		desc = io::fs::InvalidFileDescriptor;
	}
}

FileWriter::~FileWriter()
{
	closeFile();
}

void FileWriter::write( const ListLogElements &elements, const LogParameter &param )
{
	if( desc != io::fs::InvalidFileDescriptor )
	{
		lock::ScopeGuard guard( writeGuard );
		String tmp = private_::getStr( elements, param );
		if( tmp.length() )
			io::fs::write( desc, tmp.c_str(), ( io::fs::FileRWCount )( tmp.length() * sizeof(Char) ) );
	}
}

DebugWindowWriter::~DebugWindowWriter()
{
}

void DebugWindowWriter::write( const ListLogElements &elements, const LogParameter &param )
{
	String tmp = private_::getStr( elements, param );
	if( tmp.length() )
		::OutputDebugString( tmp.c_str() );
}

} // namespace logging
} // FatRat Library