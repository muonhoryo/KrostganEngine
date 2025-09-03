
#include <UserInterfaceLoader.h>
#include <VectExts.h>
#include <iostream>

using namespace KrostganEngine;
using namespace std;


void UserInterfaceLoader::DeserializeNode(xml_node<>* node, UIElement& parent)
{

	UIElement* el = nullptr;
	xml_attribute<>* attr = nullptr;
	xml_node<>* child = nullptr;
	while (node != nullptr) {

		Vector2f pos=DEFAULT_POSITION;
		Vector2f scale = DEFAULT_SCALE;
		Vector2f anchor= DEFAULT_ANCHOR;
		char layer(0);
		bool active(true);

		//read attributes for ui-element
		attr = node->first_attribute();
		while (attr != nullptr) {
			if (attr->name() == ATTR_POSITION_X) {
				pos.x = stof(attr->value());
			}
			else if (attr->name() == ATTR_POSITION_Y) {
				pos.y = stof(attr->value());
			}
			else if (attr->name() == ATTR_SCALE_X) {
				scale.x = stof(attr->value());
			}
			else if (attr->name() == ATTR_SCALE_Y) {
				scale.y = stof(attr->value());
			}
			else if (attr->name() == ATTR_ANCHOR_X) {
				anchor.x = stof(attr->value());
			}
			else if (attr->name() == ATTR_ANCHOR_Y) {
				anchor.y = stof(attr->value());
			}
			else if (attr->name() == ATTR_LAYER) {
				layer = stoi(attr->value());
			}
			else if (attr->name() == ATTR_ACTIVE) {
				active = attr->value() == "0";
			}

			attr = attr->next_attribute();
		}

		if (node->name() == UIEL_NAME_TEXT) {

			string text;
			unsigned int fontSize(DEFAULT_FONTSIZE);
			string fontPath("");
			Color color;

			//read attributes
			attr = node->first_attribute();
			while (attr != nullptr) {
				if (attr->name() == ATTR_TEXT_TEXT) {
					text = string(attr->value());
				}
				else if (attr->name() == ATTR_TEXT_FONTSIZE) {
					fontSize = stoi(attr->value());
				}
				else if (attr->name() == ATTR_TEXT_FONT) {
					fontPath = string(attr->value());
				}
				else if (attr->name() == ATTR_COLOR) {
					color = Color(stoul(attr->value(), nullptr, 16));
				}

				attr = attr->next_attribute();
			}

			UIText* textB = new UIText(
				&parent,
				text,
				fontSize,
				pos,
				scale,
				anchor,
				layer);
			textB->SetActivity(active);
			textB->SetColor(color);
			if (fontPath != "")
				textB->SetFont(ExternalGlobalResources::GetRes_t<ExtGlRes_Font>(fontPath)->Font_);
			el = textB;
		}

		if (el != nullptr) {
			DeserializeNode(node->first_node(), *el);
		}

		node = node->next_sibling();
	}
}