#pragma once

#include <rapidxml.hpp>

namespace rapidxml {
	
	/// <summary>
	/// Positive offset means that target attr is next in order and is previous otherwise
	/// </summary>
	/// <param name="attr"></param>
	/// <param name="offset"></param>
	static void TakeOtherAttrInOrder(xml_attribute<>* attr, int offset) {

		if (offset > 0) {

			while (offset > 0) {
				attr = attr->next_attribute();
				--offset;
			}
		}
		else {

			while (offset < 0) {
				attr = attr->previous_attribute();
				++offset;
			}
		}
	}
}