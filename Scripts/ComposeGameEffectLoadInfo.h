#pragma once

#include <string>
#include <SFML/System.hpp>
#include <GameEffectsSystem.h>
#include <ObjectsCatalog.h>
#include <LvlLoadingStructs.h>

using namespace std;
using namespace sf;

namespace KrostganEngine::GameObjects {

	struct ComposeGameEffectLoadInfo : public ObjectLoadInfo {

		virtual ~ComposeGameEffectLoadInfo();

		string Name = "";
		bool IsStackable = false;

		virtual ComposeGameEffect& InstantiateGameEff() const = 0;

		/// <summary>
		/// Return true if param was wrotten.
		/// </summary>
		/// <param name="param"></param>
		/// <returns></returns>
		virtual bool WriteParam(Attr& param);
		/// <summary>
		/// Read general game effects and write them into compose game effect
		/// </summary>
		/// <param name="param"></param>
		/// <returns></returns>
		virtual void WriteGeneralGameEff(xml_node<>& node) = 0;

		virtual ComposeGameEffectLoadInfo& Clone() const = 0;

	protected:
		ComposeGameEffectLoadInfo();
		ComposeGameEffectLoadInfo(const ComposeGameEffectLoadInfo& copy);

		/// <summary>
		/// Return nullptr if cant deserialize game effect
		/// </summary>
		/// <param name="node"></param>
		/// <returns></returns>
		IGameEffect* DeserializeGeneralGameEff(xml_node<>& node) const;

		static const char& GetGenGameEffType(xml_node<>& genGameEffNode);

	private:
		IGameEffect& DeserializeGameEff_Dur_Deserter(xml_node<>& node, string& nameBuffer) const;
		IGameEffect& DeserializeGameEff_Dur_Disarm(xml_node<>& node, string& nameBuffer) const;
		IGameEffect& DeserializeGameEff_Dur_EntBatStatConst_Bool(xml_node<>& node, string& nameBuffer) const;
		IGameEffect& DeserializeGameEff_Dur_EntBatStatMult(xml_node<>& node, string& nameBuffer) const;
		IGameEffect& DeserializeGameEff_Inst_AddDurEff(xml_node<>& node, string& nameBuffer) const;
	};

	struct ComposeGameEffectLoadInfo_Instant : public ComposeGameEffectLoadInfo {

		ComposeGameEffectLoadInfo_Instant();
		ComposeGameEffectLoadInfo_Instant(const ComposeGameEffectLoadInfo_Instant& copy);
		virtual ~ComposeGameEffectLoadInfo_Instant();

		ComposeGameEffect& InstantiateGameEff() const override;
		ComposeGameEffectLoadInfo& Clone() const override;
		void WriteGeneralGameEff(xml_node<>& node) override;

		vector<IGameEffect_Instant*> GeneralGameEffects_Inst;
		
	private:
		bool ValidateGeneralGameEff(xml_node<>& node) const;
	};

	struct ComposeGameEffectLoadInfo_Permanent : public ComposeGameEffectLoadInfo {

		ComposeGameEffectLoadInfo_Permanent();
		ComposeGameEffectLoadInfo_Permanent(const ComposeGameEffectLoadInfo_Permanent& copy);
		virtual ~ComposeGameEffectLoadInfo_Permanent();

		ComposeGameEffect& InstantiateGameEff() const override;
		ComposeGameEffectLoadInfo& Clone() const override;
		void WriteGeneralGameEff(xml_node<>& node) override;

		vector<IGameEffect_Durable*> GeneralGameEffects_Dur;

	private:
		bool ValidateGeneralGameEff(xml_node<>& node) const;
	};

	struct ComposeGameEffectLoadInfo_Temporal : public ComposeGameEffectLoadInfo_Permanent {

		ComposeGameEffectLoadInfo_Temporal();
		ComposeGameEffectLoadInfo_Temporal(const ComposeGameEffectLoadInfo_Temporal& copy);
		virtual ~ComposeGameEffectLoadInfo_Temporal();

		float EffTime = FLT_MAX;

		ComposeGameEffect& InstantiateGameEff() const override;
		ComposeGameEffectLoadInfo& Clone() const override;
		void WriteGeneralGameEff(xml_node<>& node) override;
		bool WriteParam(Attr& param) override;

		vector<IGameEffect_TimeDepended*> GeneralGameEffects_TimeDep;

	private:
		bool ValidateGeneralGameEff(xml_node<>& node, int& effType) const;

		static inline const int TYPE_INVALID = -1;
		static inline const int TYPE_DUR = 0;
		static inline const int TYPE_TIMEDEP = 1;
	};

	struct ComposeGameEffectLoadInfo_Periodical : public ComposeGameEffectLoadInfo_Temporal {

		ComposeGameEffectLoadInfo_Periodical();
		ComposeGameEffectLoadInfo_Periodical(const ComposeGameEffectLoadInfo_Periodical& copy);
		virtual ~ComposeGameEffectLoadInfo_Periodical();

		size_t TickGameEff_CatalogID = EMPTY_CATALOG_ID;
		std::byte TickGameEff_SubCatalogID = ABSENT_SUB_CATALOG_ID;
		float TickTime = FLT_MAX;

		ComposeGameEffect& InstantiateGameEff() const override;
		ComposeGameEffectLoadInfo& Clone() const override;
		bool WriteParam(Attr& param) override;
	};
}