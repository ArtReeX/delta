//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>

USEFORM("Forms\TestForm\TestForm_Delta.cpp", TestForm);
USEFORM("Forms\MainForm\MainForm_Delta.cpp", MainForm);
USEFORM("Forms\DebugForm\DebugForm_Delta.cpp", DebugForm);
USEFORM("Forms\SettingForm\SettingForm_Delta.cpp", SettingForm);
USEFORM("Forms\AboutForm\AboutForm_Delta.cpp", AboutForm);
USEFORM("Forms\AuthForm\AuthForm_Delta.cpp", AuthForm);
USEFORM("Forms\TabsForm\LinesForm\EditForm\EditForm_Lines_Delta.cpp", EditFormLines);
USEFORM("Forms\TabsForm\LinesForm\AddForm\AddForm_Lines_Delta.cpp", AddFormLines);
USEFORM("Forms\TabsForm\SourcesForm\AddForm\AddForm_Sources_Delta.cpp", AddFormSources);
USEFORM("Forms\TabsForm\SourcesForm\EditForm\EditForm_Sources_Delta.cpp", EditFormSources);
USEFORM("Forms\TabsForm\CorrectionsForm\EditForm\EditForm_Corrections_Delta.cpp", EditFormCorrections);
USEFORM("Forms\TabsForm\CorrectionsForm\AddForm\AddForm_Corrections_Delta.cpp", AddFormCorrections);
USEFORM("Forms\TabsForm\CurrencysForm\AddForm\AddForm_Currencys_Delta.cpp", AddFormCurrencys);
USEFORM("Forms\TabsForm\CurrencysForm\EditForm\EditForm_Currencys_Delta.cpp", EditFormCurrencys);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
        Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TAuthForm), &AuthForm);
		Application->CreateForm(__classid(TSettingForm), &SettingForm);
		Application->CreateForm(__classid(TTestForm), &TestForm);
		Application->CreateForm(__classid(TAboutForm), &AboutForm);
		Application->CreateForm(__classid(TAddFormSources), &AddFormSources);
		Application->CreateForm(__classid(TEditFormSources), &EditFormSources);
		Application->CreateForm(__classid(TAddFormCurrencys), &AddFormCurrencys);
		Application->CreateForm(__classid(TEditFormCurrencys), &EditFormCurrencys);
		Application->CreateForm(__classid(TAddFormLines), &AddFormLines);
		Application->CreateForm(__classid(TEditFormLines), &EditFormLines);
		Application->CreateForm(__classid(TAddFormCorrections), &AddFormCorrections);
		Application->CreateForm(__classid(TEditFormCorrections), &EditFormCorrections);
		Application->CreateForm(__classid(TDebugForm), &DebugForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
