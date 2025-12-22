
#pragma once

#include <SFML/System.hpp>
#include <ICallbackRec_Upd.h>
#include <vector>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Core;

namespace KrostganEngine::PlayerControl {

	class PlayerInputManager;

	class IPlayerInputHandler {

	public:
		virtual ~IPlayerInputHandler(){}

		virtual void Update(const CallbackRecArgs_Upd& args) = 0;

	protected:
		IPlayerInputHandler(){}
	};


	/// <summary>
	/// With creating added itself to collection in PlayerInputManager.
	/// Works only when PlayerInputManager hasn't active IPriorityInputHandler.
	/// </summary>
	class IBaseInputHandler : public IPlayerInputHandler {

	public:
		virtual ~IBaseInputHandler();

	protected:
		IBaseInputHandler();
	};


	/// <summary>
	/// Inactive since creating. To activate need call StartHandling(), and script will be added in field of PlayerInputManager.
	/// While active - locks base input handlers' calling
	/// </summary>
	class IPriorityInputHandler : public IPlayerInputHandler{

	public:
		virtual ~IPriorityInputHandler();

		void StartHandling();
		void AbortHandling();

	protected:
		IPriorityInputHandler(){}

		virtual void StartHandling_Action(){}
		virtual void AbortHandling_Action(){}
	};



	/// <summary>
	/// With creating added itself to collection in PlayerInputManager
	/// </summary>
	class IWindowInputHandler : public IPlayerInputHandler {

	public:
		virtual ~IWindowInputHandler();

	protected:
		IWindowInputHandler();
	};



	class PlayerInputManager final : public ICallbackRec_Upd{

	public:
		PlayerInputManager();
		~PlayerInputManager();

		void Update(CallbackRecArgs_Upd args) override;

	private:
		vector<IBaseInputHandler*>		InputHandlers;
		vector<IWindowInputHandler*>	WindInputHandlers;
		IPriorityInputHandler*			PriorityInputHan = nullptr;

		void AddInputHandler(IBaseInputHandler& handler);
		void RemoveInputHandler(IBaseInputHandler& handler);
		void AddPriorityInputHan(IPriorityInputHandler& handler);
		void RemovePriorityInputHan(IPriorityInputHandler& handler);
		void AddWindInputHandler(IWindowInputHandler& handler);
		void RemoveWindInputHandler(IWindowInputHandler& handler);

		friend class IBaseInputHandler;
		friend class IPriorityInputHandler;
		friend class IWindowInputHandler;

	public:
		static const PlayerInputManager& GetInstance();
		static void Clear();

		/// <summary>
		/// Return true if reserved button
		/// </summary>
		static bool GetBtnState_Escape();
		static void SetBtnState_Escape(bool newState);

		static bool GetBtnState_Shift();
		static bool GetBtnState_Alt();
		static bool GetBtnState_Ctrl();

		static bool HasPriorityInputHandler();

	private:
		static inline PlayerInputManager* Singleton = nullptr;

		static inline bool	IsReservedBtn_Escape = false;
		static inline bool	FreeBtn_Escape = false;
		static inline bool	IsPressed_Shift = false;
		static inline bool	IsPressed_Alt = false;
		static inline bool	IsPressed_Ctrl = false;
		static inline Clock ReservBtnDelay_Escape;
	};
}