
#include <UserInterfacesDeserializer.h>
#include <UserInterfaceLoader.h>
#include <_Extensions.h>
#include <iostream>
#include <_ExtVisual_UI.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::UI;
using namespace std;

void UserInterfaceLoader::Load(const xml_document<>& layout) {

	UserInterfaceManager::Unload();
	UIRoot& root = UserInterfaceManager::GetRoot();
	DeserializeNode(layout.first_node()->first_node(), root);
}
void UserInterfaceLoader::Load(const string& layoutName) {
	Load(UserInterfacesDeserializer::GetInstance()->GetLayout(layoutName));
}
void UserInterfaceLoader::UnloadCurrent() {
	UserInterfaceManager::Unload();
}
void UserInterfaceLoader::DeserializeNode(xml_node<>* node, UIElement& parent)
{

	UIElement* el = nullptr;
	xml_attribute<>* attr = nullptr;
	xml_node<>* child = nullptr;
	while (node != nullptr) {

		Vector2f pos=DEFAULT_POSITION;
		Vector2f scale = DEFAULT_SCALE;
		Vector2f anchor= DEFAULT_ANCHOR;
		Vector2f uisize = DEFAULT_SCALE;
		Vector2f origin = DEFAULT_ORIGIN;
		float rotation = 0;
		std::byte layer(DEFAULT_RENDLAYER_UI);
		bool active(true);
		bool resizeUIInherit(false);
		string name = "";

		Shader* shad = nullptr;
		Color color = Color::White;

		//read attributes for ui-element
		attr = node->first_attribute();

		char* attrName = nullptr;

		while (attr != nullptr) {

			attrName= attr->name();

			if (attrName == ATTR_POSITION_X) {
				pos.x = stof(attr->value());
			}
			else if (attrName == ATTR_POSITION_Y) {
				pos.y = stof(attr->value());
			}
			else if (attrName == ATTR_SCALE_X) {
				scale.x = stof(attr->value());
			}
			else if (attrName == ATTR_SCALE_Y) {
				scale.y = stof(attr->value());
			}
			else if (attrName == ATTR_ANCHOR_X) {
				anchor.x = stof(attr->value());
			}
			else if (attrName == ATTR_ANCHOR_Y) {
				anchor.y = stof(attr->value());
			}
			else if (attrName == ATTR_ORIGIN_X) {
				origin.x = stof(attr->value());
			}
			else if (attrName == ATTR_ORIGIN_Y) {
				origin.y = stof(attr->value());
			}
			else if (attrName == ATTR_ROTATION) {
				rotation = stof(attr->value());
			}
			else if (attrName == ATTR_LAYER) {
				layer = (std::byte)stoi(attr->value());
			}
			else if (attrName == ATTR_ACTIVE) {
				active = FStreamExts::ParseBool(attr->value());
			}
			else if (attrName == ATTR_RESIZEINHERIT_UI) {
				resizeUIInherit = FStreamExts::ParseBool(attr->value());
			}
			else if (attrName == ATTR_COLOR) {
				color = Color(stoul(attr->value(), nullptr, 16));
			}
			else if (attrName == ATTR_SHADER) {
				shad= &dynamic_cast<ExtGlRes_Shader*>(ExternalGlobalResources::GetRes(string(attr->value())))->Shader_;
			}
			else if (attrName == ATTR_NAME) {
				name = attr->value();
			}
			else if (attrName == ATTR_UISIZE_X) {
				uisize.x = stof(attr->value());
			}
			else if (attrName == ATTR_UISIZE_Y) {
				uisize.y = stof(attr->value());
			}
			attr = attr->next_attribute();
		}

		if (node->name() == UIEL_NAME_TEXT) {

			string text;
			unsigned int fontSize(DEFAULT_FONTSIZE);
			string fontPath("");

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

				attr = attr->next_attribute();
			}

			UIText* textB = new UIText(
				&parent,
				text, 
				&name,
				fontSize,
				shad,
				layer);

			textB->SetOrigin(origin);
			textB->SetLocalPosition(pos);
			textB->SetLocalScale(scale);
			textB->SetAnchor(anchor);
			textB->SetColor(color);
			textB->SetLocalRotation(rotation);
			if (fontPath != "")
				textB->SetFont(ExternalGlobalResources::GetRes_t<ExtGlRes_Font>(fontPath)->Font_);
			el = textB;
		}
		else if (node->name() == UIEL_NAME_SPRITE) {

			ExtGlRes_Sprite* sprSource = nullptr;
			const Texture* tex = nullptr;

			//read attributes
			attr = node->first_attribute();
			while (attr != nullptr) {
				if (attr->name() == ATTR_SPRITE_SOURCE) {
					sprSource=dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(string(attr->value())));
					tex = &sprSource->Tex;
					if(shad==nullptr)
						shad = sprSource->RenShader;
				}

				attr = attr->next_attribute();
			}

			if (tex == nullptr)
				throw exception("Empty texture");

			UISprite* spr = new UISprite(
				*tex,
				&parent,
				&name,
				shad,
				layer);
			spr->SetOrigin(origin);
			spr->SetLocalPosition(pos);
			spr->SetLocalScale(scale);
			spr->SetAnchor(anchor);
			spr->SetColor(color);
			spr->SetLocalRotation(rotation);
			el = spr;
		}
		else if (node->name() == UIEL_NAME_EMPTY) {

			UIEmpty* empt = new UIEmpty(&parent, &name, parent.GetGlobalUISize());
			empt->SetOrigin(origin);
			empt->SetLocalPosition(pos);
			empt->SetLocalScale(scale);
			empt->SetAnchor(anchor);
			empt->SetLocalRotation(rotation);
			el = empt;
		}

		if (el != nullptr) {

			el->SetResizingUIByInherit(resizeUIInherit);
			el->SetActivity(active);
			if (uisize != DEFAULT_SCALE)
				el->SetLocalUISize(uisize);
			//Read dependencies
			char* name = nullptr;
			attr = node->first_attribute();

			while (attr != nullptr) {
				name = attr->name();

				//HieObjActDepend_GroupSelect
				if (name == ATTR_TAG_DEPEND_HIEACT_GRS) {

					HieObjActDepend_GroupSelect* depend_groupSel = new HieObjActDepend_GroupSelect(*el);

					auto nextAttr = attr->next_attribute();

					while (nextAttr != nullptr) {

						name = attr->name();
						if (name == ATTR_DEPEND_HIEACT_GRS_THRESHOLD) {
							depend_groupSel->SetSelectionThreshold(stoi(attr->value()));
						}
						else if (name == ATTR_DEPEND_HIEACT_GRS_GREAT) {
							depend_groupSel->SetGreaterCondition(FStreamExts::ParseBool(attr->value()));
						}
						else if (name == ATTR_DEPEND_HIEACT_GRS_EQUAL) {
							depend_groupSel->SetEqualCondition(FStreamExts::ParseBool(attr->value()));
						}

						nextAttr = nextAttr->next_attribute();
					}
				}

				//First selected entitiy's dependencies
				else if (name == ATTR_TAG_DEPEND_FIRST_SEL_ENTITY) {

					char* value = attr->value();
					DependStatsWrapperType wrType = DependStatsWrapperType::ABSENT;

					if (value == ATTR_DEPEND_STATS_CONTAINER_BASE) {
						
						wrType = DependStatsWrapperType::Base;
					}
					else if (value == ATTR_DEPEND_STATS_CONTAINER_AA) {

						wrType = DependStatsWrapperType::AutoAttack;
					}

					auto nextAttr = attr->next_attribute();

					while (nextAttr != nullptr) {

						name = nextAttr->name();
						//Initialize dependency on battle stats
						if (name == ATTR_DEPEND_TXT_BATSTAT_FIELDTYPE) {

							int statType = -1;
							const GetEntStatsWrapperFunc* gStWrFunc = nullptr;

							switch (wrType)
							{
							case KrostganEngine::Core::UserInterfaceLoader::DependStatsWrapperType::Base:
								gStWrFunc = &EntityStatsWrGettingFuncs::GetBaseStatsFunc;
								statType = (int)EntityBattleStats::StrToStat(nextAttr->value());
								break;
							case KrostganEngine::Core::UserInterfaceLoader::DependStatsWrapperType::AutoAttack:
								gStWrFunc = &EntityStatsWrGettingFuncs::GetAutoAttackStatsFunc;
								statType = (int)AutoAttackStats::StrToStat(nextAttr->value());
								break;
							default:
								throw exception("Invalid type of stat wrapper's type for dependency on battle stat of entity.");
							}


							if ((int)statType != -1) {			//Check if parsing was succesfull

								IEntityUIDependency* depend = nullptr;
								ModStatsWrapper_Consts::StatType fieldType = IModifiableStatsWrapper::GetFieldType((int)statType);
								string* fmt = new string(dynamic_cast<UIText*>(el)->GetString());
								if (fmt->length() <= 1) {
									delete fmt;
									fmt = new string{ "{}" };
								}
								switch (fieldType)
								{
								case KrostganEngine::GameObjects::ModStatsWrapper_Consts::StatType::t_size_t:
									depend = new BattleStatDepend_toTxt_s_t(nullptr, *gStWrFunc, (int)statType, *dynamic_cast<UIText*>(el), nullptr, *fmt);
									break;
								case KrostganEngine::GameObjects::ModStatsWrapper_Consts::StatType::t_float:
									depend = new BattleStatDepend_toTxt_f(nullptr, *gStWrFunc, (int)statType, *dynamic_cast<UIText*>(el), nullptr, *fmt);
									break;
								default:
									throw exception("Unknown type of stat");
								}

								if (depend != nullptr)
									UserInterfaceManager::GetFirstSelEntityDepend().AddDependency(*depend);
							}
							else
								throw exception("Unknown type of stat");

							break;
						}
						//Initialize dependency on current hp
						else if (name == ATTR_TAG_DEPEND_TXT_CURRHP) {

							string* fmt = new string(dynamic_cast<UIText*>(el)->GetString());
							if (fmt->length() <= 1) {
								delete fmt;
								fmt = new string{ "{}" };
							}
							auto depend = new CurrHPDepend_toTxt(nullptr, *dynamic_cast<UIText*>(el), *fmt);
							UserInterfaceManager::GetFirstSelEntityDepend().AddDependency(*depend);

							break;
						}

						nextAttr = nextAttr->next_attribute();
					}
				}

				//Hierarchy activity depended on first selected activity
				else if (name == ATTR_TAG_DEPEND_HIEACT_ABLE2AA) {

					HieObjActDepend_AutoAtkActivity* depend_aaAct = 
						new HieObjActDepend_AutoAtkActivity(
							*el,
							EntityStatsWrGettingFuncs::GetAutoAttackStatsFunc, 
							FStreamExts::ParseBool(attr->value()));

					UserInterfaceManager::GetFirstSelEntityDepend().AddDependency(*depend_aaAct);
				}

				attr = attr->next_attribute();
			}

			DeserializeNode(node->first_node(), *el);
		}

		node = node->next_sibling();
	}
}
IUIDependency* UserInterfaceLoader::GetDependencyByType(forward_list<IUIDependency*>& list, const type_info& typeInfo) {

	auto pred = new GetDependByTypePred(typeInfo);
	auto dep = *CollectionsExts::Get(list, *pred);
	if (dep == nullptr)
		throw exception("Depend wasn't initialized.");
	return dep;
}