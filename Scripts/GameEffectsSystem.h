#pragma once

#include <CatalogObject.h>
#include <SFML/System.hpp>
#include <forward_list>
#include <CollectionsExts.h>
#include <ICallbackRec_Upd.h>
#include <_Events.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {

	class IGameEffTarget;

	class ComposeGameEffect;
	class ComposeGameEff_Instant;
	class ComposeGameEff_Permanent;
	class ComposeGameEff_Temporal;
	class ComposeGameEff_Periodical;


	class IGameEffect {

	public:
		virtual ~IGameEffect(){}

		virtual IGameEffect& Clone() const = 0;

	protected:
		IGameEffect(){}

		virtual void Activate(IGameEffTarget& target) = 0;

	private:
		friend class ComposeGameEffect;
	};

	class IGameEffect_Durable : public IGameEffect {

	public:
		virtual ~IGameEffect_Durable(){}

	protected:
		IGameEffect_Durable(){}

		virtual void Deactivate(IGameEffTarget& target) = 0;

	private:
		friend class ComposeGameEff_Permanent;
		friend class ComposeGameEff_Permanent;
		friend class ComposeGameEff_Temporal;
	};

	class IGameEffect_TimeDepended : public IGameEffect_Durable {

	public:
		virtual ~IGameEffect_TimeDepended(){}

	protected:
		IGameEffect_TimeDepended(){}

		virtual void UpdateByTimer(IGameEffTarget& target, const Clock& timer) = 0;

	private:
		friend class ComposeGameEff_Temporal;
	};

	class IGameEffect_Instant : public IGameEffect {

	public:
		virtual ~IGameEffect_Instant(){}

	protected:
		IGameEffect_Instant(){}

	private:
		friend class ComposeGameEff_Instant;
		friend class ComposeGameEff_Periodical;
	};


	class ComposeGameEffect : public CatalogObject {

	public:
		virtual ~ComposeGameEffect();

		virtual ComposeGameEffect& Clone() const = 0;

		void Set_IsStackable(bool isStackable);

		unsigned int GetSourcesCount() const;
		bool Get_IsStackable() const;

	protected:
		ComposeGameEffect(size_t CatalogID = 0, std::byte SubcatalogID = (std::byte)0);
		ComposeGameEffect(const ComposeGameEffect& copy);

		virtual void OnApplyToTarget(IGameEffTarget& target) = 0;
		virtual void OnRemoveFromTarget(IGameEffTarget& target) = 0;

	private:
		friend class IGameEffTarget;

		unsigned int SourcesCount = 0;
		bool IsStackable = false;
	};

	class ComposeGameEff_Instant : public ComposeGameEffect {

	public:
		ComposeGameEff_Instant
			(size_t CatalogID = 0,
			std::byte SubcatalogID = (std::byte)0);
		ComposeGameEff_Instant (const ComposeGameEff_Instant& copy);
		virtual ~ComposeGameEff_Instant();

		ComposeGameEffect& Clone() const override;

		void AddGameEffect(IGameEffect_Instant& eff);
		void RemoveGameEffect(const IGameEffect_Instant& eff);

	protected:
		void OnApplyToTarget(IGameEffTarget& target) override;
		void OnRemoveFromTarget(IGameEffTarget& target) override final;

	private:
		vector<IGameEffect_Instant*> GameEffects;
	};

	class ComposeGameEff_Permanent : public ComposeGameEffect{

	public:
		explicit ComposeGameEff_Permanent
			(size_t CatalogID = 0,
			std::byte SubcatalogID = (std::byte)0);
		explicit  ComposeGameEff_Permanent(const ComposeGameEff_Permanent& copy);
		virtual ~ComposeGameEff_Permanent();

		void AddGameEffect_Durable(IGameEffect_Durable& eff);
		void RemoveGameEffect_Durable(IGameEffect_Durable& eff);

		ComposeGameEffect& Clone() const override;

	protected:
		void OnApplyToTarget(IGameEffTarget& target) override;
		void OnRemoveFromTarget(IGameEffTarget& target) override;

	private:
		vector<IGameEffect_Durable*> GameEffects_Durable;
	};

	class ComposeGameEff_Temporal : public ComposeGameEff_Permanent, public virtual ICallbackRec_Upd {

	public:
		ComposeGameEff_Temporal
			(float EffTime,
			size_t CatalogID = 0,
			std::byte SubcatalogID = (std::byte)0);
		ComposeGameEff_Temporal(const ComposeGameEff_Temporal& copy);
		virtual ~ComposeGameEff_Temporal();

		void AddGameEffect_TimeDepended(IGameEffect_TimeDepended& eff);
		void RemoveGameEffect_TimeDepended(IGameEffect_TimeDepended& eff);
		float GetEffectTime() const;
		void SetEffectTime(float EffTime);

		void Update(CallbackRecArgs_Upd args) override;
		ComposeGameEffect& Clone() const override;

	protected:
		void OnApplyToTarget(IGameEffTarget& target) override;
		void OnRemoveFromTarget(IGameEffTarget& target) override;

		virtual void Update_Action(CallbackRecArgs_Upd& args) {}

		IGameEffTarget& GetTarget() const;

	private:
		vector<IGameEffect_TimeDepended*> GameEffects_TimeDepended;
		IGameEffTarget* Target = nullptr;
		Clock Timer;
		float EffTime;
		bool IsActive = false;
	};

	class ComposeGameEff_Periodical : public ComposeGameEff_Temporal {

	public:
		ComposeGameEff_Periodical
			(ComposeGameEff_Instant& TickGameEffect,
			float TickTime, 
			float EffTime = FLT_MAX,
			size_t CatalogID = 0,
			std::byte SubcatalogID = (std::byte)0);
		ComposeGameEff_Periodical(const ComposeGameEff_Periodical& copy);
		virtual ~ComposeGameEff_Periodical();

		ComposeGameEffect& Clone() const override;

		float GetTickTime() const;
		void SetTickTime(float TickTime);

	protected:
		void OnApplyToTarget(IGameEffTarget& target) override;
		void Update_Action(CallbackRecArgs_Upd& args) override;

	private:
		ComposeGameEff_Instant& TickGameEffect;
		Clock TickTimer;
		float TickTime;
	};


	class IGameEffTarget {
		
	public:
		ExecutedEvent<const ComposeGameEffect&> AddGameEffEvent;
		ExecutedEvent<const ComposeGameEffect&> RemoveGameEffEvent;

		virtual ~IGameEffTarget();

		void AddGameEff(ComposeGameEffect& eff);

		void RemoveGameEff(ComposeGameEffect& eff);

		/// <summary>
		/// Only for unstackable effects
		/// </summary>
		/// <param name="catalogID"></param>
		/// <param name="subCatalogID"></param>
		void RemoveGameEffByID(size_t catalogID, std::byte subCatalogID);
		/// <summary>
		/// Only for unstackable effects
		/// </summary>
		/// <param name="catalogID"></param>
		/// <param name="subCatalogID"></param>
		void RemoveGameEffByID(size_t catalogID);

		bool HasGameEffect(size_t catalogID, std::byte subcatalogID);

	protected:
		IGameEffTarget();

	private:
		forward_list<ComposeGameEffect*> AppliedGameEffects;

		EventHandler<const ComposeGameEffect&> AddGameEffEventHan = EventHandler<const ComposeGameEffect&>(AddGameEffEvent);
		EventHandler<const ComposeGameEffect&> RemoveGameEffEventHan = EventHandler<const ComposeGameEffect&>(RemoveGameEffEvent);
	};
}