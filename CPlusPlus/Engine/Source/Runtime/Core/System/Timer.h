#pragma once

#include "../Base.h"



namespace Engine
{
	class ENGINE_API Timer
	{
	public:
		Timer();


		// Record current system time
		Void Reset();


		RealType Elapsed() const;
		SizeType ElapsedMilliseconds() const;
	private:
		/**
		* Time point
		* 
		* 
		* @remark
		* Unit is millisecond
		*/
		SizeType start;
	};
}