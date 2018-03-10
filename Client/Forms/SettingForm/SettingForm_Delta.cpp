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
//------------ ОБРАБОТЧИКИ СТАНДАРТНЫХ СОБЫТИЙ ------------//
//---------------------------------------------------------//

//-- ФУНКЦИЯ ПОКАЗА ФОРМЫ --//
void __fastcall TSettingForm::FormShow(TObject *Sender)
{
	//-- задание начальных значений элементам --//
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
//------------- ОБРАБОТЧИКИ СОБЫТИЙ ЭЛЕМЕНТОВ -------------//
//---------------------------------------------------------//

//-- ФУНКЦИЯ НАЖАТИЯ НА КЛАВИШУ "Save" --//
void __fastcall TSettingForm::SaveButton_OneClick(TObject *Sender)
{
	//-- ЗАПИСЬ НОВЫХ ЗНАЧЕНИЙ В КОНФИГУРАЦИЮ ПРОГРАММЫ --//

	//-- запись индикатора оповещений --//
	MainForm->engine->Config()->TrayMinimize = TrayMinimizeCheck->Checked;

    //-- запись индикатора оповещений --//
	MainForm->engine->Config()->NotificationsHint = NotificationsCheck->Checked;


	//-- запись темы оформления --//
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

    //-- если ХОСТ/ПОРТ изменился --//
	if(HostEdit->Text != MainForm->engine->Config()->HostServer || PortEdit->Text.ToInt() != MainForm->engine->Config()->PortServer)
	{
		//-- запись параметров ХОСТ/ПОРТ --//
		MainForm->engine->Config()->HostServer = HostEdit->Text;
		MainForm->engine->Config()->PortServer = PortEdit->Text.ToInt();

        //-- если соединение активно, выполняем отключение --//
		if(MainForm->engine->ConnectState())
			MainForm->engine->Disconnect();




        //-- установка состояния элементов в зависимости от подключения --//

		//-- закрытие доступа к интерфейсу --//
		MainForm->PageControl->Enabled = false;

		//-- выключение кнопок управления сервером --//
		MainForm->ContrServButton->Enabled = false;

		//-- изменение состояния кнопки авторизации --//
		MainForm->LoginButton->Enabled = true;


		//-- выполнение переподключения --//
		MainForm->engine->Connecting(MainForm->engine->Config()->HostServer, MainForm->engine->Config()->PortServer);
	}

	//-- закрытие формы --//
	Close();
}


