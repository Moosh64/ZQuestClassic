#ifndef ZC_DIALOG_SETPASSWORD_H
#define ZC_DIALOG_SETPASSWORD_H

#include <gui/dialog.h>
#include <gui/checkbox.h>
#include <gui/text_field.h>
#include <functional>
#include <string_view>

void call_password_dlg();

class SetPasswordDialog: public GUI::Dialog<SetPasswordDialog>
{
public:
	enum class message { OK, CANCEL };

	SetPasswordDialog(bool useKeyFile,
		std::function<void(std::string_view, bool)> setPassword);

	std::shared_ptr<GUI::Widget> view() override;
	bool handleMessage(message msg);

private:
	bool useKeyFile;
	std::shared_ptr<GUI::Checkbox> saveKeyFileCB;
	std::shared_ptr<GUI::TextField> pwField;
	std::function<void(std::string_view, bool)> setPassword;
};

#endif
