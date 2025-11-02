
#include <UserInterfacesDeserializer.h>
#include <UserInterfaceLoader.h>
#include <Extensions.h>
#include <iostream>
#include <ExtVisual_UI.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::UI;
using namespace std;

void UserInterfaceLoader::Load(const xml_document<>& layout) {

	UserInterfaceManager::Unload();
	UIEmpty& root = UserInterfaceManager::GetRoot();
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
	forward_list<IUIDependency*> depends;
	while (node != nullptr) {

		Vector2f pos=DEFAULT_POSITION;
		Vector2f scale = DEFAULT_SCALE;
		Vector2f anchor= DEFAULT_ANCHOR;
		byte layer(DEFAULT_RENDLAYER_UI);
		bool active(true);
		bool resizeUIInherit(false);

		Shader* shad = nullptr;
		Color color = Color::White;

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
				layer = (byte)stoi(attr->value());
			}
			else if (attr->name() == ATTR_ACTIVE) {
				active = FStreamExts::ParseBool(attr->value());
			}
			else if (attr->name() == ATTR_RESIZEINHERIT_UI) {
				resizeUIInherit = FStreamExts::ParseBool(attr->value());
			}
			else if (attr->name() == ATTR_COLOR) {
				color = Color(stoul(attr->value(), nullptr, 16));
			}
			else if (attr->name() == ATTR_SHADER) {
				shad= &dynamic_cast<ExtGlRes_Shader*>(ExternalGlobalResources::GetRes(string(attr->value())))->Shader_;
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
				fontSize,
				shad,
				layer);

			textB->SetLocalPosition(pos);
			textB->SetLocalScale(scale);
			textB->SetAnchor(anchor);
			textB->SetActivity(active);
			textB->SetColor(color);
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
				shad,
				layer);
			spr->SetLocalPosition(pos);
			spr->SetLocalScale(scale);
			spr->SetAnchor(anchor);
			spr->SetColor(color);
			el = spr;
		}
		else if (node->name() == UIEL_NAME_EMPTY) {

			UIEmpty* empt = new UIEmpty(&parent, parent.GetGlobalUISize());
			empt->SetLocalPosition(pos);
			empt->SetLocalScale(scale);
			empt->SetAnchor(anchor);
			el = empt;
		}

		if (el != nullptr) {

			el->SetResizingUIByInherit(resizeUIInherit);
			//Read dependencies
			char* name = nullptr;
			attr = node->first_attribute();
			bool isFirstSelEntityAttr = false;
			DependStatsWrapperType wrType = DependStatsWrapperType::ABSENT;
			while (attr != nullptr)
			{
				if (attr->name() == ATTR_TAG_DEPEND_HIEACT_GRS) {
					depends.push_front(new HieObjActDepend_GroupSelect(*el));
				}
				else if (attr->name() == ATTR_DEPEND_HIEACT_GRS_THRESHOLD) {
					auto dep = dynamic_cast<HieObjActDepend_GroupSelect*>(GetDependencyByType(depends, typeid(HieObjActDepend_GroupSelect*)));
					dep->SetSelectionThreshold(stoi(attr->value()));
				}
				else if (attr->name() == ATTR_DEPEND_HIEACT_GRS_GREAT) {
					auto dep = dynamic_cast<HieObjActDepend_GroupSelect*>(GetDependencyByType(depends, typeid(HieObjActDepend_GroupSelect*)));
					dep->SetGreaterCondition(FStreamExts::ParseBool(attr->value()));
				}
				else if (attr->name() == ATTR_DEPEND_HIEACT_GRS_EQUAL) {
					auto dep = dynamic_cast<HieObjActDepend_GroupSelect*>(GetDependencyByType(depends, typeid(HieObjActDepend_GroupSelect*)));
					dep->SetEqualCondition(FStreamExts::ParseBool(attr->value()));
				}
				//Text only dependencies
				else if (attr->name() == ATTR_TAG_DEPEND_FIRST_SEL_ENTITY) {
					isFirstSelEntityAttr = true;
					if (attr->value() == ATTR_DEPEND_STATS_CONTAINER_BASE) {
						wrType = DependStatsWrapperType::Base;
					}
					else if (attr->value() == ATTR_DEPEND_STATS_CONTAINER_AA) {
						wrType = DependStatsWrapperType::AutoAttack;
					}
				}
				else if (attr->name() == ATTR_DEPEND_TXT_BATSTAT_FIELDTYPE) {
					if (node->name() != UIEL_NAME_TEXT)
						cout << "WARNING!!!: attribute is used only for TextBlock" << endl;
					else{

						int statType = -1;
						const GetEntStatsWrapperFunc* gStWrFunc = nullptr;

						switch (wrType)
						{
						case KrostganEngine::Core::UserInterfaceLoader::DependStatsWrapperType::Base:
							gStWrFunc = &EntityStatsWrGettingFuncs::GetBaseStatsFunc;
							statType = (int)EntityBattleStats::StrToStat(attr->value());
							break;
						case KrostganEngine::Core::UserInterfaceLoader::DependStatsWrapperType::AutoAttack:
							gStWrFunc = &EntityStatsWrGettingFuncs::GetAutoAttackStatsFunc;
							statType = (int)AutoAttackStats::StrToStat(attr->value());
							break;
						default:
							throw exception("Invalid type of stat wrapper's type.");
						}

						if ((int)statType != -1) {			//Check if parsing was succesfull
							if (isFirstSelEntityAttr) {			//Create dependency for UI-panel of first selected entity

								IEntityUIDependency* depend=nullptr;
								ModStatsWrapper_Consts::StatType fieldType = IModifiableStatsWrapper::GetFieldType((int)statType);
								string* fmt = new string(dynamic_cast<UIText*>(el)->GetString());
								if (fmt->length() <= 1) {
									delete fmt;
									fmt = new string{ "{}" };
								}
								switch (fieldType)
								{
								case KrostganEngine::GameObjects::ModStatsWrapper_Consts::StatType::t_size_t:
									depend = new BattleStatDepend_toTxt_s_t(nullptr, *gStWrFunc, (int)statType, *dynamic_cast<UIText*>(el), nullptr,*fmt);
									break;
								case KrostganEngine::GameObjects::ModStatsWrapper_Consts::StatType::t_float:
									depend = new BattleStatDepend_toTxt_f(nullptr, *gStWrFunc, (int)statType, *dynamic_cast<UIText*>(el), nullptr, *fmt);
									break;
								}

								if(depend!=nullptr)
									UserInterfaceManager::GetFirstSelEntityDepend().AddDependency(*depend);
							}
						}
					}
				}
				else if (attr->name() == ATTR_TAG_DEPEND_TXT_CURRHP) {
					if(node->name()!=UIEL_NAME_TEXT)
						cout<< "WARNING!!!: attribute is used only for TextBlock" << endl;
					else {
						if (isFirstSelEntityAttr) {		//Create dependency for UI-panel of first selected entity

							string* fmt = new string(dynamic_cast<UIText*>(el)->GetString());
							if (fmt->length() <= 1) {
								delete fmt;
								fmt = new string{ "{}" };
							}
							auto depend = new CurrHPDepend_toTxt(nullptr, *dynamic_cast<UIText*>(el), *fmt);
							UserInterfaceManager::GetFirstSelEntityDepend().AddDependency(*depend);
						}
					}
				}

				attr = attr->next_attribute();
			}

			for (auto dep : depends) {
				UserInterfaceManager::AddDependency(*dep);
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