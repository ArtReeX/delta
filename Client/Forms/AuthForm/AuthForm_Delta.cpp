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
//------------ ����������� ����������� ������� ------------//
//---------------------------------------------------------//

//-- ������� ������ ����� --//
void __fastcall TAuthForm::FormShow(TObject *Sender)
{
	//-- ���������� ����� ������� ��� ������ --//
	LoginEdit->Text = MainForm->engine->Config()->LoginServer;

	PasswordEdit->PasswordChar = '*';
	PasswordEdit->Text = MainForm->engine->Config()->PasswordServer;
}




//---------------------------------------------------------//
//------------- ����������� ������� ��������� -------------//
//---------------------------------------------------------//

//-- ������� ������ �� ������� ������ "Log in" --//
void __fastcall TAuthForm::AuthButton_OneClick(TObject *Sender)
{
	//-- �������� �� ������� ����� --//
	if(LoginEdit->Text.IsEmpty() || PasswordEdit->Text.IsEmpty())
	{
		ShowMessage("Please fill in all fields.");
	}
	else
	{
		//-- ��������� ������ � ������ --//
		MainForm->engine->Config()->LoginServer = LoginEdit->Text;
        MainForm->engine->Config()->PasswordServer = PasswordEdit->Text;

		//-- ������������ ������ ����������� � ������������ ����������� --//
		UnicodeString param = "\"login\":\"" + LoginEdit->Text + "\"," +
						  "\"passwd\":\"" + PasswordEdit->Text + "\"";

		//-- ����������� �� ������� --//
		MainForm->engine->Send("auth", param, "CheckAuthorization");

		//-- �������� ����� ����������� --//
		Close();
	}
}



