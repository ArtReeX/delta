//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AuthForm_Delta.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAuthForm *AuthForm;
//---------------------------------------------------------------------------
__fastcall TAuthForm::TAuthForm(TComponent* Owner)
	: TForm(Owner)
{
}




//---------------------------------------------------------//
//------------ ОБРАБОТЧИКИ СТАНДАРТНЫХ СОБЫТИЙ ------------//
//---------------------------------------------------------//

//-- ФУНКЦИЯ ПОКАЗА ФОРМЫ --//
void __fastcall TAuthForm::FormShow(TObject *Sender)
{
	//-- заполнение полей данными при показе --//
	LoginEdit->Text = MainForm->engine->Config()->LoginServer;

	PasswordEdit->PasswordChar = '*';
	PasswordEdit->Text = MainForm->engine->Config()->PasswordServer;
}




//---------------------------------------------------------//
//------------- ОБРАБОТЧИКИ СОБЫТИЙ ЭЛЕМЕНТОВ -------------//
//---------------------------------------------------------//

//-- ФУНКЦИЯ ВЫХОДА ПО НАЖАТИЮ КНОПКИ "Log in" --//
void __fastcall TAuthForm::AuthButton_OneClick(TObject *Sender)
{
	//-- проверка на пустоту полей --//
	if(LoginEdit->Text.IsEmpty() || PasswordEdit->Text.IsEmpty())
	{
		ShowMessage("Please fill in all fields.");
	}
	else
	{
		//-- запоминие логина и пароля --//
		MainForm->engine->Config()->LoginServer = LoginEdit->Text;
        MainForm->engine->Config()->PasswordServer = PasswordEdit->Text;

		//-- ФОРМИРОВАНИЕ СТРОКИ АВТОРИЗАЦИИ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
		UnicodeString param = "\"login\":\"" + LoginEdit->Text + "\"," +
						  "\"passwd\":\"" + PasswordEdit->Text + "\"";

		//-- авторизация на сервере --//
		MainForm->engine->Send("auth", param, "CheckAuthorization");

		//-- закрытие формы авторизации --//
		Close();
	}
}



