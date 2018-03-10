//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SettingForm_Delta.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettingForm *SettingForm;
//---------------------------------------------------------------------------
__fastcall TSettingForm::TSettingForm(TComponent* Owner)
	: TForm(Owner)
{
}



//---------------------------------------------------------//
//------------ ����������� ����������� ������� ------------//
//---------------------------------------------------------//

//-- ������� ������ ����� --//
void __fastcall TSettingForm::FormShow(TObject *Sender)
{
	//-- ������� ��������� �������� ��������� --//
	HostEdit->Text = MainForm->engine->Config()->HostServer;
	PortEdit->Text = MainForm->engine->Config()->PortServer;

	TrayMinimizeCheck->Checked = MainForm->engine->Config()->TrayMinimize;

	NotificationsCheck->Checked = MainForm->engine->Config()->NotificationsHint;

	if(MainForm->engine->Config()->Theme)
		ThemeWhiteRadioButton->Checked = true;
	else
		ThemeBlackRadioButton->Checked = true;
}




//---------------------------------------------------------//
//------------- ����������� ������� ��������� -------------//
//---------------------------------------------------------//

//-- ������� ������� �� ������� "Save" --//
void __fastcall TSettingForm::SaveButton_OneClick(TObject *Sender)
{
	//-- ������ ����� �������� � ������������ ��������� --//

	//-- ������ ���������� ���������� --//
	MainForm->engine->Config()->TrayMinimize = TrayMinimizeCheck->Checked;

    //-- ������ ���������� ���������� --//
	MainForm->engine->Config()->NotificationsHint = NotificationsCheck->Checked;


	//-- ������ ���� ���������� --//
	if(ThemeWhiteRadioButton->Checked)
	{
		MainForm->engine->Config()->Theme = true;
		MainForm->SetThemeProgram();
	}
	else
	{
        MainForm->engine->Config()->Theme = false;
		MainForm->SetThemeProgram();
	}

    //-- ���� ����/���� ��������� --//
	if(HostEdit->Text != MainForm->engine->Config()->HostServer || PortEdit->Text.ToInt() != MainForm->engine->Config()->PortServer)
	{
		//-- ������ ���������� ����/���� --//
		MainForm->engine->Config()->HostServer = HostEdit->Text;
		MainForm->engine->Config()->PortServer = PortEdit->Text.ToInt();

        //-- ���� ���������� �������, ��������� ���������� --//
		if(MainForm->engine->ConnectState())
			MainForm->engine->Disconnect();




        //-- ��������� ��������� ��������� � ����������� �� ����������� --//

		//-- �������� ������� � ���������� --//
		MainForm->PageControl->Enabled = false;

		//-- ���������� ������ ���������� �������� --//
		MainForm->ContrServButton->Enabled = false;

		//-- ��������� ��������� ������ ����������� --//
		MainForm->LoginButton->Enabled = true;


		//-- ���������� ��������������� --//
		MainForm->engine->Connecting(MainForm->engine->Config()->HostServer, MainForm->engine->Config()->PortServer);
	}

	//-- �������� ����� --//
	Close();
}


