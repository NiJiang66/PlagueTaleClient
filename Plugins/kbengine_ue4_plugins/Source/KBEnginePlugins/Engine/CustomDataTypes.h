/*
	Generated by KBEngine!
	Please do not modify this file!
	tools = kbcmd
*/

#pragma once
#include "KBECommon.h"
#include "KBETypes.h"
#include "MemoryStream.h"
#include "Bundle.h"
#include "DataTypes.h"
namespace KBEngine
{


class KBENGINEPLUGINS_API DATATYPE_ROLE_DATA : DATATYPE_BASE
{
public:
	void createFromStreamEx(MemoryStream& stream, ROLE_DATA& datas);
	void addToStreamEx(Bundle& stream, const ROLE_DATA& v);
};


class KBENGINEPLUGINS_API DATATYPE_ROLE_INFO : DATATYPE_BASE
{
public:
	DATATYPE_ROLE_DATA Data_DataType;
	void createFromStreamEx(MemoryStream& stream, ROLE_INFO& datas);
	void addToStreamEx(Bundle& stream, const ROLE_INFO& v);
};


class KBENGINEPLUGINS_API DATATYPE_ROLE_LIST : DATATYPE_BASE
{
public:
	class KBENGINEPLUGINS_API DATATYPE__ROLE_LIST_Value_ArrayType_ChildArray : public DATATYPE_BASE
	{
	public:
		DATATYPE_ROLE_INFO itemType;

		void createFromStreamEx(MemoryStream& stream, TArray<ROLE_INFO>& datas)
		{
			uint32 size = stream.readUint32();
			while(size > 0)
			{
				--size;
				itemType.createFromStreamEx(stream, datas.EmplaceAt_GetRef(datas.Num()));
			};

		}

		void addToStreamEx(Bundle& stream, const TArray<ROLE_INFO>& v)
		{
			stream.writeUint32((uint32)v.Num());
			for(int i=0; i<v.Num(); ++i)
			{
				itemType.addToStreamEx(stream, v[i]);
			};
		}
	};

	DATATYPE__ROLE_LIST_Value_ArrayType_ChildArray Value_DataType;

	void createFromStreamEx(MemoryStream& stream, ROLE_LIST& datas);
	void addToStreamEx(Bundle& stream, const ROLE_LIST& v);
};


}