#ifndef ZC_DIALOG_INITDLG_H
#define ZC_DIALOG_INITDLG_H

#include <gui/dialog.h>
#include <gui/checkbox.h>
#include <gui/label.h>
#include <gui/text_field.h>
#include <gui/list_data.h>
#include <functional>
#include <string_view>
#include <map>
#include <gui/switcher.h>

void call_init_dlg(zinitdata& sourcezinit, bool zc);

class InitDataDialog: public GUI::Dialog<InitDataDialog>
{
public:
	enum class message { OK, CANCEL, LEVEL };

	InitDataDialog(zinitdata const& start, bool zc, std::function<void(zinitdata const&)> setVals);

	std::shared_ptr<GUI::Widget> view() override;
	bool handleMessage(const GUI::DialogMessage<message>& msg);

private:
	void setOfs(size_t ofs);
	std::shared_ptr<GUI::TextField> sBombMax;
	std::shared_ptr<GUI::Label> l_lab[10];
	std::shared_ptr<GUI::Checkbox> l_maps[10];
	std::shared_ptr<GUI::Checkbox> l_comp[10];
	std::shared_ptr<GUI::Checkbox> l_bkey[10];
	std::shared_ptr<GUI::TextField> l_keys[10];
	std::shared_ptr<GUI::Switcher> icswitcher;
	std::map<int32_t,int32_t> switchids;
	zinitdata local_zinit;
	size_t levelsOffset;
	GUI::ListData list_dmaps, list_items;
	bool isZC;
	
	std::function<void(zinitdata const&)> setVals;

	// Various helper functions to build the GUI.
	std::shared_ptr<GUI::Widget> WORD_FIELD(word* member);
	template <typename T>
	std::shared_ptr<GUI::Widget> VAL_FIELD_IMPL(T minval, T maxval, T* member, bool dis);
	std::shared_ptr<GUI::Widget> COUNTER_FRAME(const char* name, std::shared_ptr<GUI::Widget> field1, std::shared_ptr<GUI::Widget> field2);
	std::shared_ptr<GUI::Widget> LEVEL_FIELD(int ind);
	std::shared_ptr<GUI::Widget> BTN_100(int val);
	std::shared_ptr<GUI::Widget> BTN_10(int val);
	std::shared_ptr<GUI::Widget> TRICHECK(int ind);
};

#endif
