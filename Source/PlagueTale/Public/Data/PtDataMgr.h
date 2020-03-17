// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PtDataMgr.generated.h"

class UTexture;
class UPtDataAsset;
class UPtGoodDrag;

/**	背包类型 */
UENUM()
enum class EBagType : uint8
{
	MainBag = 0,
	SkillBag,
	BuffBag,
	EquipBag
};

/**	物品类型 */
UENUM()
enum class EGoodType : uint8
{
	Skill = 0,
	Buff,
	Equip
};

/**	使用物品的结果 */
UENUM()
enum class EReduceResult : uint8
{
	Succeed = 0,
	NoGood
};

/**	一个格子物品的信息 */
USTRUCT()
struct FGoodInfo
{
	GENERATED_BODY()
public:
	/**	格子ID */
	UPROPERTY()
	uint8 BlockId;
	/**	物品id */
	UPROPERTY()
	uint8 GoodId;
	/**	物品类型 */
	UPROPERTY()
	EGoodType GoodType;
	/**	物品Kind */
	UPROPERTY()
	uint8 GoodKind;
	/**	数量 */
	UPROPERTY()
	uint8 Number;

	FGoodInfo() {}
	void InitInfo(uint8 InBlockId, uint8 InGoodId, uint8 InNumber);
	FORCEINLINE bool IsEmpty() const { return Number == 0; }
};

/**	物品简易数据 */
struct FGoodData
{
	/**	物品类型 */
	EGoodType GoodType;
	/**	物品Kind */
	uint8 GoodKind;

	FGoodData(EGoodType InType, uint8 InKind) : GoodType(InType), GoodKind(InKind) {}
};




/**	更新背包格子数据的委托 */
DECLARE_DELEGATE_TwoParams(FUpdateBagBlock, EBagType, uint8)

/**
 * 数据管理器
 */
UCLASS()
class PLAGUETALE_API UPtDataMgr : public UObject
{
	GENERATED_BODY()
public:
	static UPtDataMgr* Get();

	/**	加载全部数据资产，并保存到GoodDatas物品资料表 */
	void LoadTotalData();

	/**	根据物品ID获取物品图片 */
	UTexture* GetGoodTexture(int32 GoodId);

	/**	根据物品ID获得Kind */
	uint8 GetKindByGoodId(uint8 GoodId);

	/**	根据物品ID获得类型 */
	EGoodType GetTypeByGoodId(uint8 GoodId);

	/**	判断物品是否存在 */
	bool IsGoodExit(EBagType BagType, uint8 BlockId) const;

	/**	获取一个格子的物品信息 */
	const FGoodInfo GetGoodInfo(EBagType BagType, uint8 BlockId) const;

	/**	更新一个格子的物品信息 */
	void ChangeGoodInfo(EBagType BagType, FGoodInfo GoodInfo);

	/**	拖拽中是否有物品 */
	bool IsHandGoodExit();

	/**	返回拖拽中的物品信息，如果没有则返回空信息 */
	FGoodInfo GetHandGoodInfo() const;

	/**	释放拖拽物，请求将拖拽中的物品放置到拖拽处 */
	void ReviseHandGood();

	/**	清空背包数据 */
	void ClearBagData();

public:

	/**	保存所有背包物品数据 */
	UPROPERTY()
	TMap<uint8, FGoodInfo> SkillBag;
	UPROPERTY()
	TMap<uint8, FGoodInfo> BuffBag;
	UPROPERTY()
	TMap<uint8, FGoodInfo> EquipBag;
	UPROPERTY()
	TMap<uint8, FGoodInfo> MainBag;

	/**	保存拖拽中的物品背包类型 */
	EBagType HandBagType;
	/**	保存拖拽中的物品格子Id */
	uint8 HandBlockId;
	/**	保存拖拽中的物品UI, 可以用于判断手上是否有物品 */
	UPtGoodDrag* GoodDrag;

	/**	物品资料表 */
	TMap<uint8, FGoodData> GoodDatas;

	/**	更新背包格子数据的委托 */
	FUpdateBagBlock UpdateBagBlockDel;

protected:
	/**	管理器单例 */
	static UPtDataMgr* MgrInst;

	/**	保存全部数据资产 */
	UPROPERTY()
	UPtDataAsset* TotalData;
};
