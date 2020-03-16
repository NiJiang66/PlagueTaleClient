#pragma once
#include "Engine/KBECommon.h"
#include "Engine/PtRoleBase.h"

namespace KBEngine
{
	class PtRole : public PtRoleBase
	{
	public:
		PtRole();
		virtual ~PtRole();

	public:
		virtual void __init__() override;
		virtual void onDestroy() override;

	public:
		/**	移动动画更新						，服务器对客户端的回调 */
		virtual void OnAnimUpdate(const ANIM_INFO& arg1) override;

		/**	基础hp变化						，服务器对客户端的回调 */
		virtual void onBaseHPChanged(int16 oldValue) override;
		/**	防御力变化						，服务器对客户端的回调 */
		virtual void onDefenseChanged(int16 oldValue) override;
		/**	生命值变化						，服务器对客户端的回调 */
		virtual void onHPChanged(int16 oldValue) override;
		/**	力量值变化						，服务器对客户端的回调 */
		virtual void onPowerRatioChanged(float oldValue) override;
		/**	速度变化							，服务器对客户端的回调 */
		virtual void onSpeedRatioChanged(float oldValue) override;

		/**	攻击								，服务器对客户端的回调 */
		virtual void OnAttack() override;

		/**	往背包增加物品					，服务器对客户端的回调 */
		virtual void OnIncreaseGood(uint8 arg1, const GOOD_INFO& arg2) override;
		/**	移动物品							，服务器对客户端的回调 */
		virtual void OnPassGood(uint8 arg1, const GOOD_INFO& arg2, uint8 arg3, const GOOD_INFO& arg4) override;
		/**	使用物品							，服务器对客户端的回调 */
		virtual void OnReduceGood(uint8 arg1, uint8 arg2, const GOOD_INFO& arg3) override;
		/**	请求所有背包数据					，服务器对客户端的回调 */
		virtual void OnReqBagList(const BAG_INFO& arg1, const BAG_INFO& arg2, const BAG_INFO& arg3, const BAG_INFO& arg4) override;


	};


}