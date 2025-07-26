#pragma once
#include <string>
#include <vector>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

namespace KrostganEngine::Core {
	class ValuesListDeserializer
	{
	public:
		~ValuesListDeserializer();

		bool static CouldBeName(const string& value);

	protected:
		struct ValueDefPair {
			ValueDefPair(string Name, string Value) {
				this->Name = Name;
				this->Value = Value;
			}
			ValueDefPair():ValueDefPair("",""){}
			string Name;
			string Value;
		};

		ValuesListDeserializer();

		void DeserializeValues();
		void DeserializeValues(vector<string>& serValues);

		/// <summary>
		/// Return true if value by definition is exists
		/// </summary>
		/// <param name="definition"></param>
		/// <param name="value"></param>
		/// <returns></returns>
		bool			TryGetValue				(const string& definition, string& value);
		/// <summary>
		/// Throw exception if value by definition doesn't exists
		/// </summary>
		/// <param name="definition"></param>
		/// <param name="buffer"></param>
		void			GetValueByDef			(const string& definition, string& buffer);
		/// <summary>
		/// Throw exception if value by definition doesn't exists
		/// </summary>
		/// <param name="definition"></param>
		/// <param name="value"></param>
		/// <returns></returns>
		float			DeserValueByDef_float	(const string& definition, string& value);
		/// <summary>
		/// Throw exception if value by definition doesn't exists
		/// </summary>
		/// <param name="definition"></param>
		/// <param name="value"></param>
		/// <returns></returns>
		int				DeserValueByDef_int		(const string& definition, string& value);
		/// <summary>
		/// Throw exception if value by definition doesn't exists
		/// </summary>
		/// <param name="definition"></param>
		/// <param name="value"></param>
		/// <returns></returns>
		unsigned int	DeserValueByDef_uint	(const string& definition, string& value);
		/// <summary>
		/// Throw exception if value by definition doesn't exists
		/// </summary>
		/// <param name="definition"></param>
		/// <param name="value"></param>
		/// <returns></returns>
		size_t			DeserValueByDef_size_t	(const string& definition, string& value);
		/// <summary>
		/// Throw exception if value by definition doesn't exists
		/// </summary>
		/// <param name="definition"></param>
		/// <param name="value"></param>
		/// <returns></returns>
		Vector2u		DeserValueByDef_Vec2u	(const string& definition, string& value);
		/// <summary>
		/// Throw exception if value by definition doesn't exists
		/// </summary>
		/// <param name="definition"></param>
		/// <param name="value"></param>
		/// <returns></returns>
		Vector2f		DeserValueByDef_Vec2f	(const string& definition, string& value);

		vector<ValueDefPair> StrValuesArr;

		virtual const string	GetFilePath()			{ return ""; }
		virtual const char		GetValuesDefEndSym()	{ return ' '; }
	};
}