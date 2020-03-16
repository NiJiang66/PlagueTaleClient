#include "CustomDataTypes.h"
#include "EntityDef.h"
#include "KBDebug.h"
#include "DataTypes.h"
#include "Runtime/Core/Public/Misc/Variant.h"

namespace KBEngine
{

void DATATYPE_ENTITYID_LIST::createFromStreamEx(MemoryStream& stream, ENTITYID_LIST& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readInt32());
	};

}

void DATATYPE_ENTITYID_LIST::addToStreamEx(Bundle& stream, const ENTITYID_LIST& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeInt32(v[i]);
	};
}

void DATATYPE_ROLE_DATA::createFromStreamEx(MemoryStream& stream, ROLE_DATA& datas)
{
	datas.DataType = stream.readInt8();
	datas.DataValue = stream.readBlob();
}

void DATATYPE_ROLE_DATA::addToStreamEx(Bundle& stream, const ROLE_DATA& v)
{
	stream.writeInt8(v.DataType);
	stream.writeBlob(v.DataValue);
}

void DATATYPE_ROLE_INFO::createFromStreamEx(MemoryStream& stream, ROLE_INFO& datas)
{
	datas.Dbid = stream.readUint64();
	datas.Name = stream.readUnicode();
	datas.RoleType = stream.readUint8();
	Data_DataType.createFromStreamEx(stream, datas.Data);
}

void DATATYPE_ROLE_INFO::addToStreamEx(Bundle& stream, const ROLE_INFO& v)
{
	stream.writeUint64(v.Dbid);
	stream.writeUnicode(v.Name);
	stream.writeUint8(v.RoleType);
	Data_DataType.addToStreamEx(stream, v.Data);
}

void DATATYPE_ROLE_LIST::createFromStreamEx(MemoryStream& stream, ROLE_LIST& datas)
{
	Value_DataType.createFromStreamEx(stream, datas.Value);
}

void DATATYPE_ROLE_LIST::addToStreamEx(Bundle& stream, const ROLE_LIST& v)
{
	Value_DataType.addToStreamEx(stream, v.Value);
}

void DATATYPE_ROOM_INFO::createFromStreamEx(MemoryStream& stream, ROOM_INFO& datas)
{
	datas.RoomId = stream.readUint64();
	datas.Name = stream.readUnicode();
}

void DATATYPE_ROOM_INFO::addToStreamEx(Bundle& stream, const ROOM_INFO& v)
{
	stream.writeUint64(v.RoomId);
	stream.writeUnicode(v.Name);
}

void DATATYPE_ROOM_LIST::createFromStreamEx(MemoryStream& stream, ROOM_LIST& datas)
{
	Value_DataType.createFromStreamEx(stream, datas.Value);
}

void DATATYPE_ROOM_LIST::addToStreamEx(Bundle& stream, const ROOM_LIST& v)
{
	Value_DataType.addToStreamEx(stream, v.Value);
}

void DATATYPE_ANIM_INFO::createFromStreamEx(MemoryStream& stream, ANIM_INFO& datas)
{
	datas.Speed = stream.readFloat();
	datas.Direction = stream.readFloat();
}

void DATATYPE_ANIM_INFO::addToStreamEx(Bundle& stream, const ANIM_INFO& v)
{
	stream.writeFloat(v.Speed);
	stream.writeFloat(v.Direction);
}

void DATATYPE_GOOD_INFO::createFromStreamEx(MemoryStream& stream, GOOD_INFO& datas)
{
	datas.BlockId = stream.readUint8();
	datas.GoodId = stream.readUint8();
	datas.Number = stream.readUint8();
}

void DATATYPE_GOOD_INFO::addToStreamEx(Bundle& stream, const GOOD_INFO& v)
{
	stream.writeUint8(v.BlockId);
	stream.writeUint8(v.GoodId);
	stream.writeUint8(v.Number);
}

void DATATYPE_BAG_INFO::createFromStreamEx(MemoryStream& stream, BAG_INFO& datas)
{
	Value_DataType.createFromStreamEx(stream, datas.Value);
}

void DATATYPE_BAG_INFO::addToStreamEx(Bundle& stream, const BAG_INFO& v)
{
	Value_DataType.addToStreamEx(stream, v.Value);
}


}