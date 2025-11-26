#pragma once

#include <GameObjStatParameter.h>
#include <Events.h>
#include <LvlLoadingStructs.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {
	struct ModStatsWrapper_Consts final {

		static inline const short STATTYPE_TYPEDEF_BITSCOUNT = 4;
		/// <summary>
		/// Describes type of field like int, size_t, float and etc.
		/// 
		/// Every stat type of hereditary class should use the same definitions of field's types.
		/// 
		/// Stats in enum is wrotten directly in the same order like in STATTYPE_NAMES and in countable set
		/// for each field type individually
		/// 
		/// For example:
		///		//int
		///		MaxHP			= t_size_t | (1 << STATTYPE_TYPEDEF_BITSCOUNT),
		///		RegenHP_Amount	= t_size_t | (2 << STATTYPE_TYPEDEF_BITSCOUNT),
		///		AADamage		= t_size_t | (3 << STATTYPE_TYPEDEF_BITSCOUNT),
		///		//float
		///		RegenHP_Tick	= t_float | (1 << STATTYPE_TYPEDEF_BITSCOUNT),
		///		MovingSpeed		= t_float | (2 << STATTYPE_TYPEDEF_BITSCOUNT),
		///		AASpeed			= t_float | (3 << STATTYPE_TYPEDEF_BITSCOUNT),
		/// 
		/// Stat with type [0 << STATTYPE_TYPEDEF_BITSCOUNT] describes empty field and shouldn't be used in definition of
		/// stat type of hereditary class.
		/// </summary>
		enum class StatType : int {
			t_size_t = 0,
			t_float = 1,
			t_bool = 2,
			type_mask = 15,
			r_type_mask = ~type_mask
		};

	private:
		ModStatsWrapper_Consts() {}
	};


	class IModifiableStatsWrapper {

	public:

		/// <summary>
		/// Return nullptr of field has another type or field don't exists
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const size_t*	GetFieldRef_s_t(int type, bool isDefField = false) const { return _GetFieldRef_s_t(type, isDefField); }
		/// <summary>
		/// Return nullptr of field has another type or field don't exists
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const float*	GetFieldRef_f(int type, bool isDefField = false) const {return _GetFieldRef_f(type,isDefField); }
		/// <summary>
		/// Return nullptr of field has another type or field don't exists
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const bool*		GetFieldRef_bool(int type) const {return _GetFieldRef_bool(type); }
		/// <summary>
		/// Return nullptr of field has another type or field don't exists
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const void*		GetFieldRef(int type, bool isDefField = false) const {return _GetFieldRef(type,isDefField); }

		virtual bool WriteParam(Attr& param)=0;

		/// <summary>
		/// Return nullptr if field has another type of field doesn't exist
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const Parameter<size_t>*	GetParameterByType_s_t(int type) const {return _GetParameterByType_s_t(type); }
		/// <summary>
		/// Return nullptr if field has another type of field doesn't exist
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const Parameter<float>*		GetParameterByType_f(int type) const {return _GetParameterByType_f(type); }
		/// <summary>
		/// Return nullptr if field has another type of field doesn't exist
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const void*					GetParameterByType(int type) const {return _GetParameterByType(type); }

		static ModStatsWrapper_Consts::StatType	GetFieldType(int type) {
			return (ModStatsWrapper_Consts::StatType)(type & (int)ModStatsWrapper_Consts::StatType::type_mask);
		}

		ExecutedEvent<int> StatChangedEvent = ExecutedEvent<int>();
		ExecutedEvent<int> DefaultStatChangedEvent = ExecutedEvent<int>();

	protected:
		IModifiableStatsWrapper(){}

		virtual const size_t*	_GetFieldRef_s_t(int type, bool isDefField = false) const = 0;
		virtual const float*	_GetFieldRef_f(int type, bool isDefField = false) const = 0;
		virtual const bool*		_GetFieldRef_bool(int type) const = 0;
		virtual const void*		_GetFieldRef(int type, bool isDefField = false) const = 0;

		virtual const Parameter<size_t>*	_GetParameterByType_s_t(int type) const = 0;
		virtual const Parameter<float>*		_GetParameterByType_f(int type) const = 0;
		virtual const void*					_GetParameterByType(int type) const = 0;

		EventHandler<int> StatChangedEventHan = EventHandler<int>(StatChangedEvent);
		EventHandler<int> DefaultStatChangedEventHan = EventHandler<int>(DefaultStatChangedEvent);

	};
}