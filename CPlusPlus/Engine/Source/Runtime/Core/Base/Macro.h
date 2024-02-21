#pragma once

/**
* Predefined Macros
*/



/**
* Compiler
* 
* Supported:
* 1.Microsoft C++ compiler
*/
#if defined(_MSC_VER)
#define COMPILER_MSVC
#else
#error Unknown C++ compiler
#endif


/**
* Standard
* 
* Required:
* C++17 or later
*/
#if defined(COMPILER_MSVC) & (_MSVC_LANG < 201703)
#error C++17 required
#endif


/**
* Platform
* 
* Supported:
* 1.Windows 64-bit
*/
#if defined(COMPILER_MSVC) & defined(_WIN64)
#define PLATFORM_WINDOWS
#else
#error Current platform is not supported
#endif


#pragma region
/**
* Export/Import dynamic link library
* 
* Note:
* Used by this:			[Export]
* Used by the other:	[Import]
*/
#if defined(COMPILER_MSVC)
#define DLL_EXPORT	__declspec(dllexport)
#define DLL_IMPORT	__declspec(dllimport)
#else
#error DLL_EXPORT and DLL_IMPORT are undefined
#endif


#if !defined(ENGINE_API_IMPORTS)
#define ENGINE_API	DLL_EXPORT
#else
#define ENGINE_API	DLL_IMPORT
#endif

#pragma endregion


#pragma region Enable bitwise operators(&, |, ^ and ~) for nested enum class

#define CLASS_ENUMCLASS_FLAGS(EnumClass)																		\
friend inline EnumClass operator&(EnumClass leftHandSide, EnumClass rightHandSide)								\
{																												\
	using UnderlyingType = __underlying_type(EnumClass);														\
																												\
																												\
	return EnumClass( static_cast<UnderlyingType>(leftHandSide) & static_cast<UnderlyingType>(rightHandSide) );	\
}																												\
																												\
friend inline EnumClass operator|(EnumClass leftHandSide, EnumClass rightHandSide)								\
{																												\
	using UnderlyingType = __underlying_type(EnumClass);														\
																												\
																												\
	return EnumClass( static_cast<UnderlyingType>(leftHandSide) | static_cast<UnderlyingType>(rightHandSide) );	\
}																												\
																												\
friend inline EnumClass operator^(EnumClass leftHandSide, EnumClass rightHandSide)								\
{																												\
	using UnderlyingType = __underlying_type(EnumClass);														\
																												\
																												\
	return EnumClass( static_cast<UnderlyingType>(leftHandSide) ^ static_cast<UnderlyingType>(rightHandSide) );	\
}																												\
																												\
friend inline EnumClass operator~(EnumClass instance)															\
{																												\
	using UnderlyingType = __underlying_type(EnumClass);														\
																												\
																												\
	return EnumClass( ~static_cast<UnderlyingType>(instance) );													\
}																												\
																												\
friend inline EnumClass& operator&=(EnumClass& leftHandSide, EnumClass rightHandSide)							\
{																												\
	leftHandSide = leftHandSide & rightHandSide;																\
																												\
	return leftHandSide;																						\
}																												\
																												\
friend inline EnumClass& operator|=(EnumClass& leftHandSide, EnumClass rightHandSide)							\
{																												\
	leftHandSide = leftHandSide | rightHandSide;																\
																												\
	return leftHandSide;																						\
}																												\
																												\
friend inline EnumClass& operator^=(EnumClass& leftHandSide, EnumClass rightHandSide)							\
{																												\
	leftHandSide = leftHandSide ^ rightHandSide;																\
																												\
	return leftHandSide;																						\
}

#pragma endregion


// Disable class/struct's copy/move constructors and copy/move assignment operators
#define NONCOPYABLE(Type)					\
		Type(const Type&)		= delete;	\
		Type(Type&&)			= delete;	\
Type&	operator=(const Type&)	= delete;	\
Type&	operator=(Type&&)		= delete


// Check runtime error(s)
#if defined(DEBUG) | defined(_DEBUG)
#define ASSERT(condition, ...)	if( !condition ) *reinterpret_cast<char*>(0) = 0 /** Dereference null pointer, and throw access violation exception */
#else
#define ASSERT(condition, ...) /** Dont anything */
#endif