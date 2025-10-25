#pragma once

namespace KrostganEngine {

	/// <summary>
	/// Return reference to field of new object, which is the same like field of old object
	/// </summary>
	/// <typeparam name="TFieldValue"></typeparam>
	/// <typeparam name="TObj"></typeparam>
	/// <param name="oldObjField"></param>
	/// <param name="oldObj"></param>
	/// <param name="newObj"></param>
	/// <returns></returns>
	template<typename TFieldValue,typename TObj>
	static TFieldValue& GetSameFieldOfObj(TFieldValue const& oldObjField,TObj const& oldObj, TObj const& newObj) {
		size_t oldFieldRef = (size_t)(&oldObjField);
		size_t oldObjRef = (size_t)(&oldObj);
		size_t newObjRef = (size_t)(&newObj);
		return *(TFieldValue*)(oldFieldRef - oldObjRef + newObjRef);
	}
}