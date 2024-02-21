#pragma once

#include "../Base.h"



namespace Engine
{
	template<typename Return, typename ...Parameters>
	using Function = Return(*)(Parameters ...);


	template<typename ...Parameter>
	using Action = Function<Void, Parameter ...>;


	template<typename ClassOrStruct, typename Return, typename ...Parameters>
	using MemberFunction = Return(ClassOrStruct::*)(Parameters ...);
	

	template<typename ClassOrStruct, typename ...Parameters>
	using MemberAction = MemberFunction<ClassOrStruct, Void, Parameters ...>;
}