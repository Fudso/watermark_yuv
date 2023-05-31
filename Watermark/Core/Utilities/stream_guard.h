#ifndef CORE_UTILITIES_STREAM_GUARD_H
#define CORE_UTILITIES_STREAM_GUARD_H

#include <string>
#include <fstream>

namespace Core
{
	template <typename T>
	class StreamGuard 
	{
	public:
		StreamGuard(const std::string& fileName, std::ios_base::openmode mode) 
			: _stream(fileName, mode)
		{
		}

		bool IsOpen() const
		{
			return _stream.is_open();
		}

		T& GetStrem()
		{
			return _stream;
		}

		~StreamGuard()
		{
			if (_stream.is_open())
			{
				_stream.close();
			}
		}

	private:
		T _stream;
	};

}
#endif
