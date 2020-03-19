// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/GameEngine.h"
#include "PtCommon.generated.h"


//框架自定义Debug输出类
#pragma region LogDebug

class KBENGINEPLUGINS_API PtRecord
{
private:
	//自身单例
	static TSharedPtr<PtRecord> RecordInst;

	//生成的字符串
	FString RecordInfo;

	//显示时间
	float ShowTime;

	//显示颜色
	FColor ShowColor;

public:

	//打印模式, 0 : Debug, 1 : Log, 2 : Warning, 3 : Error
	uint8 PatternID;

public:

	//构造函数
	inline PtRecord() {}

	~PtRecord() {}

	static TSharedPtr<PtRecord> Get();

	//设定参数
	inline void InitParam(float InTime, FColor InColor)
	{
		ShowTime = InTime;
		ShowColor = InColor;
	}

	//执行打印方法
	inline void Output() {
		return;

		switch (PatternID)
		{
		case 0:
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, ShowTime, ShowColor, RecordInfo);
		}
		break;
		case 1:
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *RecordInfo);
		}
		break;
		case 2:
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *RecordInfo);
		}
		break;
		case 3:
		{
			UE_LOG(LogTemp, Error, TEXT("%s"), *RecordInfo);
		}
		break;
		}
		//清空字符串
		RecordInfo.Empty();
	}

	//重写操作符<<
	inline PtRecord& operator<<(FString Info) { RecordInfo.Append(Info); return *this; }
	inline PtRecord& operator<<(FName Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline PtRecord& operator<<(FText Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline PtRecord& operator<<(const char* Info) { RecordInfo += Info; return *this; }
	inline PtRecord& operator<<(const char Info) { RecordInfo.AppendChar(Info); return *this; }
	inline PtRecord& operator<<(int32 Info) { RecordInfo.Append(FString::FromInt(Info)); return *this; }
	inline PtRecord& operator<<(uint8 Info) { RecordInfo.Append(FString::FromInt(Info)); return *this; }
	inline PtRecord& operator<<(uint64 Info) { RecordInfo.Append(FString::FromInt(Info)); return *this; }
	inline PtRecord& operator<<(float Info) { RecordInfo.Append(FString::SanitizeFloat(Info)); return *this; }
	inline PtRecord& operator<<(double Info) { RecordInfo.Append(FString::SanitizeFloat(Info)); return *this; }
	inline PtRecord& operator<<(bool Info) { RecordInfo.Append(Info ? FString("true") : FString("false")); return *this; }
	inline PtRecord& operator<<(FVector2D Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline PtRecord& operator<<(FVector Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline PtRecord& operator<<(FRotator Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline PtRecord& operator<<(FQuat Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline PtRecord& operator<<(FTransform Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline PtRecord& operator<<(FMatrix Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline PtRecord& operator<<(FColor Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline PtRecord& operator<<(FLinearColor Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline PtRecord& operator<<(FMargin Info) { RecordInfo.Append((FString::SanitizeFloat(Info.Left) + FString(" , ") + FString::SanitizeFloat(Info.Top) + FString(" , ") + FString::SanitizeFloat(Info.Right) + FString(" , ") + FString::SanitizeFloat(Info.Bottom))); return *this; }

	//输出
	inline void operator<<(PtRecord& Record) { Record.Output(); }
};


//PtRecord::Get() << FString("qqqqq") << FName << int << float << PtRecord::Get();


#pragma endregion




namespace PtH
{
	#define DEBUG_TIME 30.f

	FORCEINLINE PtRecord& Debug(float InTime = DEBUG_TIME, FColor InColor = FColor::Yellow)
	{
		PtRecord::Get()->PatternID = 0;
		PtRecord::Get()->InitParam(InTime, InColor);
		return *PtRecord::Get();
	}

	FORCEINLINE PtRecord& Debug(FColor InColor)
	{
		return Debug(DEBUG_TIME, InColor);
	}

	FORCEINLINE PtRecord& Log()
	{
		PtRecord::Get()->PatternID = 1;
		return *PtRecord::Get();
	}

	FORCEINLINE PtRecord& Warning()
	{
		PtRecord::Get()->PatternID = 2;
		return *PtRecord::Get();
	}

	FORCEINLINE PtRecord& Error()
	{
		PtRecord::Get()->PatternID = 3;
		return *PtRecord::Get();
	}


	FORCEINLINE PtRecord& Endl()
	{
		return *PtRecord::Get();
	}

	//将传入的Enum值对应的FString输出, 直接输出Value对应的值
	template<typename TEnum>
	FORCEINLINE FString GetEnumValueAsString(const FString& Name, TEnum Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!EnumPtr)
			return FString("InValid");
		return EnumPtr->GetEnumName((int32)Value);
	}

	//将传入的Enum值对应的FName输出
	template<typename TEnum>
	FORCEINLINE FName GetEnumValueAsName(const FString& Name, TEnum Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!EnumPtr) {
			return FName("InValid");
		}
		return FName(*EnumPtr->GetEnumName((int32)Value));
	}

	//将传入的FName对应的Enum输出
	template<typename TEnum>
	FORCEINLINE TEnum GetEnumValueFromName(const FString& Name, FName Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!EnumPtr) {
			return TEnum(0);
		}
		return (TEnum)EnumPtr->GetIndexByName(Value);
	}

	//将传入的FName对应的Enum的序号输出
	FORCEINLINE int32 GetEnumIndexFromName(const FString& Name, FName Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, *Name, true);
		if (!EnumPtr) {
			return -1;
		}
		return EnumPtr->GetIndexByName(Value);
	}
}



/**
 * 
 */
UCLASS()
class KBENGINEPLUGINS_API UPtCommon : public UObject
{
	GENERATED_BODY()

public:

	static UPtCommon* Get();

protected:

	static UPtCommon* PtInst;
	
};
