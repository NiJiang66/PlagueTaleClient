#pragma once
#include "Engine/KBECommon.h"
#include "Engine/PtAccountBase.h"

namespace KBEngine
{
	class PtAccount : public PtAccountBase
	{
	public:
		PtAccount();
		virtual ~PtAccount();

	public:
		virtual void __init__() override;
		virtual void onDestroy() override;

		/**	请求角色列表回调函数 */
		virtual void OnReqRoleList(const ROLE_LIST& arg1) override;
		/**	创建角色结果回调函数 */
		virtual void OnCreateRoleResult(uint8 arg1, const ROLE_INFO& arg2) override;
		/**	移除角色回调函数 */
		virtual void OnRemoveRole(uint64 arg1) override;
		/**	选择角色进入游戏回调函数 */
		virtual void OnSelectRoleGame(uint8 arg1, uint64 arg2) override;

		/**	请求房间列表回调函数 */
		virtual void OnReqRoomList(const ROOM_LIST& arg1) override;
		/**	创建房间回调函数 */
		virtual void OnCreateRoom(uint8 arg1, const ROOM_INFO& arg2) override;

	public:
		/**	客户端请求创建新角色 */
		void ReqCreateRole(uint8 RoleType, const FString& Name);
		/**	客户端请求移除角色 */
		void ReqRemoveRole(const FString& Name);
		//void RegRemoveRole(uint64 Dbid);
		/**	客户端请求选择角色进入游戏 */
		void SelectRoleGame(uint64 Dbid);

		/**	客户端请求房间列表 */
		void ReqRoomList();
		/**	客户端请求创建房间 */
		void ReqCreateRoom(const FString& Name);
		/**	客户端请求选择房间进入游戏 */
		void SelectRoomGame(uint64 RoomId);

	public:



	protected:
		/**	注册客户端请求事件，这些事件是用于在PtRoleGameMode通过KBENGINE_EVENT_FIRE宏触发事件时可以调用到这里注册的函数 */
		void RegisterClientReqEvent();


	public:
		/**	本地存储角色信息列表 */
		ROLE_LIST RoleList;
	};


}
