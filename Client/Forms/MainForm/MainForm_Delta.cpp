//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm_Delta.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner),
	  engine(new TEngineNS::TEngine)
{
   //-- ��������� ������ ����������� ��� �������� � ���� --//
   TrayIcon->Icons = TrayImageList;

   //-- ��������� ���������� ����� --//
   engine->SetSearchKey("call");

   //-- ��������� ������������ --//

	//-- ����� --//
	engine->SetHandler("CheckAuthorization", HandlersNS::CheckAuthorization);
	engine->SetHandler("start",HandlersNS::start);
	engine->SetHandler("stop",HandlersNS::stop);
	engine->SetHandler("getState",HandlersNS::getState);
	engine->SetHandler("chain",HandlersNS::chain);

	//-- ��������� --//
	engine->SetHandler("getParams", HandlersNS::getParams);
	engine->SetHandler("CheckEditParams", HandlersNS::CheckEditParams);
	engine->SetHandler("editParams", HandlersNS::editParams);

	//-- ��������� --//
	engine->SetHandler("getSources", HandlersNS::getSources);
	engine->SetHandler("CheckAddSource", HandlersNS::CheckAddSource);
	engine->SetHandler("CheckEditSource", HandlersNS::CheckEditSource);
	engine->SetHandler("CheckDeleteSource", HandlersNS::CheckDeleteSource);
	engine->SetHandler("addSource", HandlersNS::addSource);
	engine->SetHandler("editSource", HandlersNS::editSource);
	engine->SetHandler("deleteSource", HandlersNS::deleteSource);

	//-- ������ --//
	engine->SetHandler("getCurrencys", HandlersNS::getCurrencys);
	engine->SetHandler("CheckAddCurrency", HandlersNS::CheckAddCurrency);
	engine->SetHandler("CheckEditCurrency", HandlersNS::CheckEditCurrency);
	engine->SetHandler("CheckDeleteCurrency", HandlersNS::CheckDeleteCurrency);
	engine->SetHandler("addCurrency", HandlersNS::addCurrency);
	engine->SetHandler("editCurrency", HandlersNS::editCurrency);
	engine->SetHandler("deleteCurrency", HandlersNS::deleteCurrency);

	//-- ����� --//
	engine->SetHandler("getLines", HandlersNS::getLines);
	engine->SetHandler("CheckAddLine", HandlersNS::CheckAddLine);
	engine->SetHandler("CheckEditLine", HandlersNS::CheckEditLine);
	engine->SetHandler("CheckDeleteLine", HandlersNS::CheckDeleteLine);
	engine->SetHandler("addLine", HandlersNS::addLine);
	engine->SetHandler("editLine", HandlersNS::editLine);
	engine->SetHandler("deleteLine", HandlersNS::deleteLine);

	//-- ��������� --//
	engine->SetHandler("getCorrections", HandlersNS::getCorrections);
	engine->SetHandler("CheckAddCorrection", HandlersNS::CheckAddCorrection);
	engine->SetHandler("CheckEditCorrection", HandlersNS::CheckEditCorrection);
	engine->SetHandler("CheckDeleteCorrection", HandlersNS::CheckDeleteCorrection);
	engine->SetHandler("addCorrection", HandlersNS::addCorrection);
	engine->SetHandler("editCorrection", HandlersNS::editCorrection);
	engine->SetHandler("deleteCorrection", HandlersNS::deleteCorrection);

	//-- ���� ������ --//
    engine->SetHandler("collect",HandlersNS::collect);
	engine->SetHandler("collected",HandlersNS::collected);
	engine->SetHandler("processSource",HandlersNS::processSource);
}



//---------------------------------------------------------//
//------------ ����������� ����������� ������� ------------//
//---------------------------------------------------------//

//-- ������� �������� ����� --//
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	//-- �������� �������� ��������� �� ����� --//
	engine->LoadConfig();

	//-- ������� ������ ��������� --//
	MainForm->Caption = "Delta " + interface_conf.version;

    //-- ������� ���� --//
	SetThemeProgram();

	//-- ������� ������������ ������� ������� ����� --//
	MainForm->Constraints->MinWidth = interface_conf.min_size_width;
	MainForm->Constraints->MinHeight = interface_conf.min_size_height;

	//-- ������� ������� ������� ����� --//
	MainForm->Width = engine->Config()->MainFormWidth;
	MainForm->Height = engine->Config()->MainFormHeight;


    //-- ��������� ����������� ������� ���������� --//
   PageControl->TabIndex = 0;

   //-- ������ ������� � ���������� ��� ����������� �� ������� --//
   PageControl->Enabled = false;
   ContrServButton->Enabled = false;


   //-- ��������� ����������� �������� ������ --//
   DefaultSourcesGrid();
   DefaultCurrencysGrid();
   DefaultLinesGrid();
   DefaultCorrectionsGrid();
   DefaultArbitrationsGrid();
   DefaultCollectionsGrid();


	//-- ����������� � ������� ��� ������� --//
	engine->Connecting(engine->Config()->HostServer, engine->Config()->PortServer);
}

//-- ������� �������� ����� --//
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	//-- �����������, ����� �� ����������� � ���� --//
	if(interface_conf.tray_minimize)
	{
		if(engine->Config()->TrayMinimize)
		{
            //-- ��������� ������� �������� --//
			Action=caNone;

			//-- ������ ��������� ���������� ��������� ������ --//
			interface_conf.tray_minimize_state = true;

			//-- ���������� ������ � ���� --//
			TrayIcon->Visible = true;

			//-- �������� ��������� --//
			Application->ShowMainForm = false;
			ShowWindow(Handle,SW_HIDE);

			//-- �������� ������ � TaskBar'� --//
			ShowWindow(Application->Handle,SW_HIDE);
        }
	}

    //-- ������ ���������� ������� ���� ������� ����� --//
	engine->Config()->MainFormWidth = MainForm->Width;
	engine->Config()->MainFormHeight = MainForm->Height;


	//-- ������ �������� ��������� � ���� --//
	if(!engine->NeedToRestart())
		engine->SaveConfig();
}

//-- ������� ��������� ������ --//
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	//-- ���� ������ ������� "F12" --//
	if(Key == 123)
	{
		//-- �������� ���������� ���������� --//
		if(!engine->ConnectState())
			ShowMessage("You are not connected to the server.");
		else
		{
			//-- ����� ���� "Test" --//
			TestForm->ShowModal();
		}
		return;
	}

	//-- ���� ������ ������� "F11" --//
	if(Key == 122)
	{
		//-- ����� ���� "Debug" --//
		DebugForm->ShowModal();

		return;
	}
}

//-- ������� ������ ������� ����� --//
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	//-- ���������� ��������� ��� ������������� --//
	if(engine->NeedToRestart())
		Close();

	//-- ��������� �������� ���������� ���������� ������ --//
	UpdateLastCollected(false);

	//-- ��������� ���������� ��������� --//
	SetParamElements();
}


//-- ������� ��������� �������� ��������� ��� ��������� �������� --//
void __fastcall TMainForm::FormResize(TObject *Sender)
{
	SetParamElements();
}


//-- ������� ������������ ������� --//
void __fastcall TMainForm::PageControlChange(TObject *Sender)
{
	SetParamElements();
}



//---------------------------------------------------------//
//------------- ����������� ������� ��������� -------------//
//---------------------------------------------------------//

//-- ������� ������ ���������� "ABOUT" --//
void __fastcall TMainForm::AboutButton_OneClick(TObject *Sender)
{
	//-- ����� ���� "About" --//
	AboutForm->ShowModal();
}

//-- ������� ������ �� ��������� --//
void __fastcall TMainForm::ExitButton_OneClick(TObject *Sender)
{
	//-- ��������� ������������ � ���� --//
	interface_conf.tray_minimize = false;

	//-- �������� ��������� --//
	Close();
}

//-- ������� ������� �� ������ � ���� --//
void __fastcall TMainForm::TrayIcon_OneClick(TObject *Sender)
{
	//-- ������ ��������� ���������� ��������� ������ --//
	interface_conf.tray_minimize_state = false;

	//-- �������� ������ � ���� --//
	TrayIcon->Visible = false;

	Application->ShowMainForm = true;

	//-- ���������� ��������� --//
	ShowWindow(Handle,SW_SHOW);

	//-- ���������� ������ � TaskBar'� --//
	ShowWindow(Application->Handle,SW_SHOW);
}

//-- ������� ���������� --//
void TMainForm::ShowHint(const UnicodeString Text)
{
	if(MainForm->engine->Config()->NotificationsHint)
	{
        if(interface_conf.tray_minimize_state)
		{
			//-- ����� ��������� --//
			TrayIcon->BalloonHint = Text;

			//-- ����� ��������� --//
			TrayIcon->ShowBalloonHint();
		}

		//-- ��������������� ��������� ������� --//
        Beep(1000, 100);
	}
}


//-- ������� ��������� �������� ������ LINES NAMES GRID --//
void __fastcall TMainForm::Lines_NamesStringGridSelectCell(TObject *Sender, int ACol,
		  int ARow, bool &CanSelect)
{
    //-- �������� �� ������������� ���������� ������� --//
	if(Lines_NamesStringGrid->RowCount == engine->Data()->map_lines.size() + 1)
	{
        //-- ���������� ������� --//
		UpdateLines(ARow);
	}
}


//-- ������� ������ ����� �������� --//
void __fastcall TMainForm::Setting_OneClick(TObject *Sender)
{
	//-- ����� ���� "Setting" --//
	SettingForm->ShowModal();
}

//-- ������� ������ ����� ���������� ��������� --//
void __fastcall TMainForm::Source_AddButton_OneClick(TObject *Sender)
{
	//-- ����� ���� "AddSources" --//
	AddFormSources->ShowModal();
}

//-- ������� �������� ���������--//
void __fastcall TMainForm::Source_DeleteButton_OneClick(TObject *Sender)
{
	//-- ������������ ������ �������� � ������������ ����������� --//
	UnicodeString param = "\"id\":\"" + UnicodeString(Sources_StringGrid->Cells[0][Sources_StringGrid->Row].ToInt()) + "\"";

	//-- �������� ������� �������� ��������� �� ������ --//
	engine->Send("deleteSource", param, "CheckDeleteSource");
}

//-- ������� ������ ����� �������������� ���������  --//
void __fastcall TMainForm::Sources_EditButton_OneClick(TObject *Sender)
{
	//-- ����� ���� "EditSources" --//
	EditFormSources->ShowModal();
}

//-- ������� ������ ����� ����������� --//
void __fastcall TMainForm::Login_OneClick(TObject *Sender)
{
	//-- ����� ���� "Athorization" --//
	AuthForm->ShowModal();
}

//-- ������� ������ ����� ���������� ������ --//
void __fastcall TMainForm::Currencys_AddButton_OneClick(TObject *Sender)
{
	//-- ����� ���� "AddCurrencys" --//
	AddFormCurrencys->ShowModal();
}

//-- ������� ������ ����� ��������� ������ --//
void __fastcall TMainForm::Currencys_EditButton_OneClick(TObject *Sender)
{
	//-- ����� ���� "AddCurrencys" --//
	EditFormCurrencys->ShowModal();
}


//-- ������� ������ ����� ���������� ��������� --//
void __fastcall TMainForm::Corrections_AddButton_OneClick(TObject *Sender)
{
	//-- ����� ���� "AddCorrections" --//
	AddFormCorrections->ShowModal();
}

//-- ������� �������� ������ --//
void __fastcall TMainForm::Currencys_DeleteButton_OneClick(TObject *Sender)
{
	//-- ������������ ������ �������� � ������������ ����������� --//
	UnicodeString param = "\"id\":\"" + UnicodeString(Currencys_StringGrid->Cells[0][Currencys_StringGrid->Row].ToInt()) + "\"";

	//-- �������� ������� �������� ������ �� ������ --//
	engine->Send("deleteCurrency", param, "CheckDeleteCurrency");
}


//-- ������� �������� ����� --//
void __fastcall TMainForm::Lines_DeleteButton_OneClick(TObject *Sender)
{
	//-- ������������ ������ �������� � ������������ ����������� --//
	UnicodeString param = "\"id\":\"" + UnicodeString(Lines_NamesStringGrid->Cells[0][Lines_NamesStringGrid->Row].ToInt()) + "\"";

	//-- �������� ������� �������� ����� �� ������ --//
	engine->Send("deleteLine", param, "CheckDeleteCurrency");
}


//-- ������� �������� ��������� --//
void __fastcall TMainForm::Corrections_DeleteButton_OneClick(TObject *Sender)
{
	//-- ������������ ������ �������� � ������������ ����������� --//
	UnicodeString param = "\"id\":\"" + UnicodeString(Corrections_StringGrid->Cells[0][Corrections_StringGrid->Row].ToInt()) + "\"";

	//-- �������� ������� �������� ����� �� ������ --//
	engine->Send("deleteCorrection", param, "CheckDeleteCorrection");
}



//-- ������� ���������� ����� --//
void __fastcall TMainForm::Lines_AddButton_OneClick(TObject *Sender)
{
	//-- ����� ���� "AddLines" --//
	AddFormLines->ShowModal();
}


//-- ������� ��������� ����� --//
void __fastcall TMainForm::Lines_EditButton_OneClick(TObject *Sender)
{
	//-- ����� ���� "EditLines" --//
	EditFormLines->ShowModal();
}


//-- ������� ��������� ��������� --//
void __fastcall TMainForm::Corrections_EditButton_OneClick(TObject *Sender)
{
	//-- ����� ���� "EditCorrection" --//
	EditFormCorrections->ShowModal();
}



//-- ������� ��������� ���������� --//
void __fastcall TMainForm::Parameters_SaveButton_OneClick(TObject *Sender)
{
	//-- ������������ ������ �������������� � ������������ ����������� --//

	UnicodeString param;


	//-- ���������� --//
	//-- ************************************ --//
	if(!Parameters_CoefficientEdit->Text.IsEmpty() && Parameters_CoefficientEdit->Text != engine->Data()->params.factor)
	{
        //-- ���������� ������� ����� ����������� --//
		if(!param.IsEmpty())
			param = param + ",";

		param = param + "\"factor\":" + engine->FloatWithDots( Parameters_CoefficientEdit->Text ) ;
	}
	//-- ************************************ --//



	//-- ������ ������� --//
	//-- ************************************ --//
	if(!Parameters_MaxLengthEdit->Text.IsEmpty() && Parameters_MaxLengthEdit->Text != engine->Data()->params.maxChainLen)
	{
        //-- ���������� ������� ����� ����������� --//
		if(!param.IsEmpty())
			param = param + ",";

		param = param + "\"maxChainLen\":" + engine->FloatWithDots( Parameters_MaxLengthEdit->Text );
	}
	//-- ************************************ --//


	//-- �������� ������� �������������� ���������� �� ������ --//
	MainForm->engine->Send("editParams", param, "CheckEditParams");



    //-- �������� ������� �� ��������� ������� --//
	engine->Send("stop", "stop");

	//-- �������� ������� �� ������ ������� --//
	engine->Send("start", "start");



    //-- �������� ���� �������� --//
	engine->Data()->map_arbitrations.clear();

	//-- ���������� �������������� ������ --//
	engine->SortArbitrations(engine->Config()->SortArbitrations);

	//-- ���������� ������� --//
	UpdateArbitrations(Arbitrations_ActionsGrid->Row, false);
}


//-- ������� ������� ������� --//
void __fastcall TMainForm::StartButton_OneClick(TObject *Sender)
{
	//-- �������� ������� �� ������ ������� --//
	engine->Send("start", "start");
}



//-- ������� ��������� ������� --//
void __fastcall TMainForm::StopButton_OneClick(TObject *Sender)
{
	//-- �������� ������� �� ��������� ������� --//
	engine->Send("stop", "stop");
}


//-- ������� ����������� ������� --//
void __fastcall TMainForm::RestartButton_OneClick(TObject *Sender)
{
	//-- �������� ������� �� ��������� ������� --//
	engine->Send("stop", "stop");

	//-- �������� ������� �� ������ ������� --//
	engine->Send("start", "start");
}


//-- ������� ��������� ���� ���������� --//
void __fastcall TMainForm::Sources_EnableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Sources_StringGrid->Selection.Top ; i != Sources_StringGrid->Selection.Bottom + 1; i ++)
	{
        //-- ������������ ������ ��������� ���������� � ������������ ����������� --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Sources_StringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":1";

		//-- �������� ������� ��������� �� ������ --//
		MainForm->engine->Send("editSource", param, "NULL");
	}
}


//-- ������� ���������� ���� ���������� --//
void __fastcall TMainForm::Sources_DisableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Sources_StringGrid->Selection.Top ; i != Sources_StringGrid->Selection.Bottom + 1; i ++)
	{
		//-- ������������ ������ ��������� ���������� � ������������ ����������� --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Sources_StringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":0";

		//-- �������� ������� ��������� �� ������ --//
		MainForm->engine->Send("editSource", param, "NULL");
	}
}


//-- ������� ��������� ���� ����� --//
void __fastcall TMainForm::Currencys_EnableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Currencys_StringGrid->Selection.Top ; i != Currencys_StringGrid->Selection.Bottom + 1; i ++)
	{
		//-- ������������ ������ ��������� ���������� � ������������ ����������� --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Currencys_StringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":1";

		//-- �������� ������� ��������� �� ������ --//
		MainForm->engine->Send("editCurrency", param, "NULL");
	}
}


//-- ������� ���������� ���� ����� --//
void __fastcall TMainForm::Currencys_DisableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Currencys_StringGrid->Selection.Top ; i != Currencys_StringGrid->Selection.Bottom + 1; i ++)
	{
		//-- ������������ ������ ��������� ���������� � ������������ ����������� --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Currencys_StringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":0";

		//-- �������� ������� ��������� �� ������ --//
		MainForm->engine->Send("editCurrency", param, "NULL");
	}
}


//-- ������� ��������� ���� ����� --//
void __fastcall TMainForm::Lines_EnableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Lines_NamesStringGrid->Selection.Top ; i != Lines_NamesStringGrid->Selection.Bottom + 1; i ++)
	{
		//-- ������������ ������ ��������� ���������� � ������������ ����������� --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Lines_NamesStringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":1";

		//-- �������� ������� ��������� �� ������ --//
		MainForm->engine->Send("editLine", param, "NULL");
	}
}


//-- ������� ���������� ���� ����� --//
void __fastcall TMainForm::Lines_DisableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Lines_NamesStringGrid->Selection.Top ; i != Lines_NamesStringGrid->Selection.Bottom + 1; i ++)
	{
		//-- ������������ ������ ��������� ���������� � ������������ ����������� --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Lines_NamesStringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":0";

		//-- �������� ������� ��������� �� ������ --//
		MainForm->engine->Send("editLine", param, "NULL");
	}
}



//-- ������� ��������� ���� ��������� --//
void __fastcall TMainForm::Corrections_EnableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Corrections_StringGrid->Selection.Top ; i != Corrections_StringGrid->Selection.Bottom + 1; i ++)
	{
		//-- ������������ ������ ��������� ���������� � ������������ ����������� --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Corrections_StringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":1";

		//-- �������� ������� ��������� �� ������ --//
		MainForm->engine->Send("editCorrection", param, "NULL");
	}
}


//-- ������� ���������� ���� ��������� --//
void __fastcall TMainForm::Corrections_DisableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Corrections_StringGrid->Selection.Top ; i != Corrections_StringGrid->Selection.Bottom + 1; i ++)
	{
		//-- ������������ ������ ��������� ���������� � ������������ ����������� --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Corrections_StringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":0";

		//-- �������� ������� ��������� �� ������ --//
		MainForm->engine->Send("editCorrection", param, "NULL");
	}
}


//-- ������� �������� ����� �������������� ���������� �� �������� ����� --//
void __fastcall TMainForm::Sources_StringGridDblClick(TObject *Sender)
{
	//-- ����� ���� "EditSources" --//
	if(!Sources_StringGrid->Cells[0][1].IsEmpty())
		EditFormSources->ShowModal();
}


//-- ������� �������� ����� �������������� ����� �� �������� ����� --//
void __fastcall TMainForm::Currencys_StringGridDblClick(TObject *Sender)
{
	//-- ����� ���� "EditCurrencys" --//
	if(!Currencys_StringGrid->Cells[0][1].IsEmpty())
		EditFormCurrencys->ShowModal();
}



//-- ������� �������� ����� �������������� ����� �� �������� ����� --//
void __fastcall TMainForm::Lines_NamesStringGridDblClick(TObject *Sender)
{
	//-- ����� ���� "EditLines" --//
	if(!Lines_NamesStringGrid->Cells[0][1].IsEmpty())
		EditFormLines->ShowModal();
}


//-- ������� �������� ����� �������������� ��������� �� �������� ����� --//
void __fastcall TMainForm::Corrections_StringGridDblClick(TObject *Sender)
{
	//-- ����� ���� "EditCorrections" --//
	if(!Corrections_StringGrid->Cells[0][1].IsEmpty())
		EditFormCorrections->ShowModal();
}


//-- ������� ��������� ���� ���������� ���������� ��� ����� �� �������� ������� --//
void __fastcall TMainForm::Sources_StringGridFixedCellClick(TObject *Sender, int ACol,
		  int ARow)
{

	//-- ����������� ���� ������� ���������� --//
	unsigned int TypeSort = engine->Config()->SortSources;

	//-- ����������� ���� ���������� --//
	if(ACol == 0)
		engine->Config()->SortSources = eID;

	if(ACol == 1)
		engine->Config()->SortSources = eNAME;

	if(ACol == 2)
		engine->Config()->SortSources = eURL;

	if(ACol == 3)
		engine->Config()->SortSources = eDATAURL;

	if(ACol == 4)
		engine->Config()->SortSources = eGETTER;

	if(ACol == 5)
		engine->Config()->SortSources = eENABLED;

	if(ACol == 6)
		engine->Config()->SortSources = eNOTES;


	//-- ��������� ��������� ���������� �� � �� � --//
	if(TypeSort == engine->Config()->SortSources)
		engine->Config()->SortSourcesInd = !engine->Config()->SortSourcesInd;
	else
		engine->Config()->SortSourcesInd = true;

	//-- ��������� �������� � ������� --//
	DefaultSourcesGrid();

	//-- ���������� �� ���������� ���� --//
	engine->SortSources(engine->Config()->SortSources, engine->Config()->SortSourcesInd);

	//-- ���������� ������� --//
	UpdateSources();
}


//-- ������� ��������� ���� ���������� ����� ��� ����� �� �������� ������� --//
void __fastcall TMainForm::Currencys_StringGridFixedCellClick(TObject *Sender, int ACol,
		  int ARow)
{

	//-- ����������� ���� ������� ���������� --//
	unsigned int TypeSort = engine->Config()->SortCurrencys;

	//-- ����������� ���� ���������� --//
	if(ACol == 0)
		engine->Config()->SortCurrencys = eID;

	if(ACol == 1)
		engine->Config()->SortCurrencys = eNAME;

	if(ACol == 2)
		engine->Config()->SortCurrencys = eSHORTN;

	if(ACol == 3)
		engine->Config()->SortCurrencys = eFEE;

	if(ACol == 4)
		engine->Config()->SortCurrencys = eMINSUM;

	if(ACol == 5)
		engine->Config()->SortCurrencys = eBASE;

	if(ACol == 6)
		engine->Config()->SortCurrencys = eENABLED;

	if(ACol == 7)
		engine->Config()->SortCurrencys = eNOTES;


	//-- ��������� ��������� ���������� �� � �� � --//
	if(TypeSort == engine->Config()->SortCurrencys)
		engine->Config()->SortCurrencysInd = !engine->Config()->SortCurrencysInd;
	else
		engine->Config()->SortCurrencysInd = true;


	//-- ��������� �������� � ������� --//
	DefaultCurrencysGrid();

    //-- ���������� �� �������� ���� --//
	engine->SortCurrencys(engine->Config()->SortCurrencys, engine->Config()->SortCurrencysInd);

    //-- ���������� ������� --//
	UpdateCurrencys();
}


//-- ������� ��������� ���� ���������� ����� ��� ����� �� �������� ������� --//
void __fastcall TMainForm::Lines_NamesStringGridFixedCellClick(TObject *Sender, int ACol,
		  int ARow)
{
    //-- ����������� ���� ������� ���������� --//
	unsigned int TypeSort = engine->Config()->SortLines;

	//-- ����������� ���� ���������� --//
	if(ACol == 0)
		engine->Config()->SortLines = eID;

	if(ACol == 1)
		engine->Config()->SortLines = eNAME;

	if(ACol == 2)
		engine->Config()->SortLines = eENABLED;


	//-- ��������� ��������� ���������� �� � �� � --//
	if(TypeSort == engine->Config()->SortLines)
		engine->Config()->SortLinesInd = !engine->Config()->SortLinesInd;
	else
    	engine->Config()->SortLinesInd = true;


	//-- ��������� �������� � ������� --//
	DefaultLinesGrid();

	//-- ���������� �� �������� ���� --//
	engine->SortLines(engine->Config()->SortLines, engine->Config()->SortLinesInd);


	//-- ���������� ������� --//
	UpdateLines();
}


//-- ������� ��������� ���� ���������� ��������� ��� ����� �� �������� ������� --//
void __fastcall TMainForm::Corrections_StringGridFixedCellClick(TObject *Sender, int ACol,
		  int ARow)
{
	//-- ����������� ���� ������� ���������� --//
	unsigned int TypeSort = engine->Config()->SortCorrections;

	//-- ����������� ���� ���������� --//
	if(ACol == 0)
		engine->Config()->SortCorrections = eID;

	if(ACol == 1)
		engine->Config()->SortCorrections = eSOURCE;

	if(ACol == 2)
		engine->Config()->SortCorrections = eCURROUT;

	if(ACol == 3)
		engine->Config()->SortCorrections = eCURRIN;

	if(ACol == 4)
		engine->Config()->SortCorrections = eFEE;

	if(ACol == 5)
		engine->Config()->SortCorrections = eENABLED;

	if(ACol == 6)
		engine->Config()->SortCorrections = eNOTES;


	//-- ��������� ��������� ���������� �� � �� � --//
	if(TypeSort == engine->Config()->SortCorrections)
		engine->Config()->SortCorrectionsInd = !engine->Config()->SortCorrectionsInd;
	else
		engine->Config()->SortCorrectionsInd = true;


	//-- ��������� �������� � ������� --//
	DefaultCorrectionsGrid();

    //-- ���������� �� �������� ���� --//
	engine->SortCorrections(engine->Config()->SortCorrections, engine->Config()->SortCorrectionsInd);

	//-- ���������� ������� --//
	UpdateCorrections();
}


//-- ������� ��������� ���� ���������� ���������� ��� ����� �� �������� ������� --//
void __fastcall TMainForm::Arbitrations_ActionsGridFixedCellClick(TObject *Sender,
		  int ACol, int ARow)
{
    //-- ����������� ���� ������� ���������� --//
	unsigned int TypeSort = engine->Config()->SortArbitrations;

	//-- ����������� ���� ���������� --//
	if(ACol == 0)
		engine->Config()->SortArbitrations = eID;

	if(ACol == 1)
		engine->Config()->SortArbitrations = eFACTOR;

	if(ACol == 2)
		engine->Config()->SortArbitrations = eLINE;

	/*
	if(ACol == 3)
		engine->Config()->SortArbitrations = eCURROUT;

	if(ACol == 4)
		engine->Config()->SortArbitrations = eCURRIN;

	if(ACol == 5)
		engine->Config()->SortArbitrations = eSOURCE;

	if(ACol == 6)
		engine->Config()->SortArbitrations = eRATE;

	if(ACol == 7)
		engine->Config()->SortArbitrations = eREALRATE;

    if(ACol == 8)
		engine->Config()->SortArbitrations = eAMOUNT;
    */

	if(ACol == 10)
		engine->Config()->SortArbitrations = eTIME;

	if(ACol == 0 || ACol == 1 || ACol == 2 || ACol == 10)
	{

		//-- ��������� ��������� ���������� �� � �� � --//
		if(TypeSort == engine->Config()->SortArbitrations)
			engine->Config()->SortArbitrationsInd = !engine->Config()->SortArbitrationsInd;
		else
			engine->Config()->SortArbitrationsInd = true;


		//-- ��������� �������� � ������� --//
		DefaultArbitrationsGrid();

		//-- ���������� �� �������� ���� --//
		engine->SortArbitrations(engine->Config()->SortArbitrations, engine->Config()->SortArbitrationsInd);

		//-- ���������� ������� --//
		UpdateArbitrations();
	}
}




//-- ������� ������� ����� ����� ���������� --//
void __fastcall TMainForm::Arbitrations_ActionsGridDrawCell(TObject *Sender, int ACol,
		  int ARow, TRect &Rect, TGridDrawState State)
{
	if(ACol >= 0 && ARow >= 1)
	{
		if(!Arbitrations_ActionsGrid->Cells[0][ARow].IsEmpty())
		{
			if( engine->Data()->map_arbitrations.find( Arbitrations_ActionsGrid->Cells[0][ARow].ToInt() ) != engine->Data()->map_arbitrations.end() )
			{
				if(engine->Data()->map_arbitrations.find( Arbitrations_ActionsGrid->Cells[0][ARow].ToInt() )->second.relevance.ToInt() == true)
				{
					if(Arbitrations_ActionsGrid->Row != ARow)
					{
						//-- ����� ����� ������ � ������������ �������� �� ��������� ����� --//
						Arbitrations_ActionsGrid->Canvas->Brush->Color = clTeal;
						Arbitrations_ActionsGrid->Canvas->FillRect(Rect);

						//-- ����� ����� ������ �� ����������� ������--//
						Arbitrations_ActionsGrid->Canvas->Font->Color = clBlack;
						Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2, Arbitrations_ActionsGrid->Cells[ACol][ARow]);
					}
					else
					{
						//-- ����� ����� ������ � ������������ �������� ��������� ����� --//
						Arbitrations_ActionsGrid->Canvas->Brush->Color = clLime;
						Arbitrations_ActionsGrid->Canvas->FillRect(Rect);

						//-- ����� ����� ������ �� ����������� ������--//
						Arbitrations_ActionsGrid->Canvas->Font->Color = clBlack;
						Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2, Arbitrations_ActionsGrid->Cells[ACol][ARow]);
					}
				}
				else
				{
					if(Arbitrations_ActionsGrid->Row != ARow)
					{
						//-- ����� ����� ������ � ������������ ���������� �� ��������� ����� --//
						Arbitrations_ActionsGrid->Canvas->Brush->Color = clMaroon;
						Arbitrations_ActionsGrid->Canvas->FillRect(Rect);

						//-- ����� ����� ������ �� ����������� ������--//
						Arbitrations_ActionsGrid->Canvas->Font->Color = clWhite;
						Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2, Arbitrations_ActionsGrid->Cells[ACol][ARow]);
					}
					else
					{
                        //-- ����� ����� ������ � ������������ ���������� ��������� ����� --//
						Arbitrations_ActionsGrid->Canvas->Brush->Color = clRed;
						Arbitrations_ActionsGrid->Canvas->FillRect(Rect);

						//-- ����� ����� ������ �� ����������� ������--//
						Arbitrations_ActionsGrid->Canvas->Font->Color = clWhite;
						Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2, Arbitrations_ActionsGrid->Cells[ACol][ARow]);
                    }
				}



				//--------------------------------------//
				//---------- ����� �������� ------------//
				//--------------------------------------//

				if( (ACol == 2 || ACol == 3 || ACol == 4 || ACol == 5 || ACol == 6 || ACol == 7 || ACol == 8 || ACol == 9) )
				{
					MArbitration::iterator map_iterator = engine->Data()->map_arbitrations.find( Arbitrations_ActionsGrid->Cells[0][ARow].ToInt() );

					if(map_iterator != engine->Data()->map_arbitrations.end())
					{
						if(map_iterator->second.operations.size())
						{

							//-- ��������� ���������� ��� ������ ����� � ������ --//
							unsigned int coord = 0;


							UnicodeString end;

							for(std::vector< SOperation >::iterator iterator_operations = map_iterator->second.operations.begin(); iterator_operations != map_iterator->second.operations.end(); iterator_operations ++)
							{
								//-- ������� ������� ����� --//
								Arbitrations_ActionsGrid->RowHeights[ARow] = map_iterator->second.operations.size() * 22;


								if(ACol == 3)
								{
                                    //-- ��������� ������ --//
									if( engine->Data()->map_currencys.find( iterator_operations->currOut.ToInt() ) != engine->Data()->map_currencys.end() )
									{
										end = engine->Data()->map_currencys.find( iterator_operations->currOut.ToInt() )->second.name.Length()>Arbitrations_ActionsGrid->ColWidths[3]/8 ? end = "..." : end = "";
										Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2 + coord, engine->Data()->map_currencys.find( iterator_operations->currOut.ToInt() )->second.name.SubString(0, Arbitrations_ActionsGrid->ColWidths[3]/8) + end);
									}
								}


								if(ACol == 4)
								{
									//-- �������� ������ --//
									if( engine->Data()->map_currencys.find( iterator_operations->currIn.ToInt() ) != engine->Data()->map_currencys.end() )
									{
										end = engine->Data()->map_currencys.find( iterator_operations->currIn.ToInt() )->second.name.Length()>Arbitrations_ActionsGrid->ColWidths[4]/8 ? end = "..." : end = "";
										Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2 + coord, engine->Data()->map_currencys.find( iterator_operations->currIn.ToInt() )->second.name.SubString(0, Arbitrations_ActionsGrid->ColWidths[4]/8) + end);
									}
								}


								if(ACol == 5)
								{
									//-- �������� --//
									if( engine->Data()->map_sources.find( iterator_operations->idSource.ToInt() ) != engine->Data()->map_sources.end() )
									{
										Arbitrations_ActionsGrid->Canvas->Font->Color = clBlack;

										end = engine->Data()->map_sources.find( iterator_operations->idSource.ToInt() )->second.name.Length()>Arbitrations_ActionsGrid->ColWidths[5]/8 ? end = "..." : end = "";
										Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2 + coord, engine->Data()->map_sources.find( iterator_operations->idSource.ToInt() )->second.name.SubString(0, Arbitrations_ActionsGrid->ColWidths[5]/8) + end);
									}
								}

								if(ACol == 6)
								{
									//-- ����������� --//
									if( engine->Data()->map_sources.find( iterator_operations->idSource.ToInt() ) != engine->Data()->map_sources.end() )
									{
										Arbitrations_ActionsGrid->Canvas->Font->Color = clBlack;

										end = engine->Data()->map_sources.find( iterator_operations->idSource.ToInt() )->second.notes.Length()>Arbitrations_ActionsGrid->ColWidths[6]/8 ? end = "..." : end = "";
										Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2 + coord, engine->Data()->map_sources.find( iterator_operations->idSource.ToInt() )->second.notes.SubString(0, Arbitrations_ActionsGrid->ColWidths[6]/8) + end);
									}
								}


								if(ACol == 7)
								{
									//-- ������ ���� ������ --//
									end = iterator_operations->rate.Length()>Arbitrations_ActionsGrid->ColWidths[6]/8 ? end = "..." : end = "";
									Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2 + coord, iterator_operations->rate.SubString(0, Arbitrations_ActionsGrid->ColWidths[6]/8) + end);
								}


								if(ACol == 8)
								{
									//-- ���� ������ � ��������� --//
									end = iterator_operations->realRate.Length()>Arbitrations_ActionsGrid->ColWidths[7]/8 ? end = "..." : end = "";
									Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2 + coord, iterator_operations->realRate.SubString(0, Arbitrations_ActionsGrid->ColWidths[7]/8) + end);
								}

								if(ACol == 9)
								{
									//-- ��������� � ������ ����� �������� ������ --//
									end = iterator_operations->amount.Length()>Arbitrations_ActionsGrid->ColWidths[8]/8 ? end = "..." : end = "";
									Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2 + coord, iterator_operations->amount.SubString(0, Arbitrations_ActionsGrid->ColWidths[8]/8) + end);Arbitrations_ActionsGrid->Cells[8][ARow] = iterator_operations->amount.SubString(0, Arbitrations_ActionsGrid->ColWidths[8]/8) + end;
                                }

								coord = coord + 22;
							}

						}
					}
				}
			}
		}
	}
}


//-- ������� ��������� ������ � ������� ���������� ��� ������ --//
void __fastcall TMainForm::Sources_StringGridDrawCell(TObject *Sender, int ACol, int ARow,
		  TRect &Rect, TGridDrawState State)
{
	/*
	if((ACol == 2 || ACol == 3) && ARow > 0)
	{
		//-- ����� ����� ������ � ������������ �������� �� ��������� ����� --//
		Sources_StringGrid->Canvas->Brush->Color = clWhite;
		Sources_StringGrid->Canvas->FillRect(Rect);

		//-- ����� ����� ������ �� ����������� ������--//
		Sources_StringGrid->Canvas->Font->Color = clBlue;
		Sources_StringGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2, Sources_StringGrid->Cells[ACol][ARow]);
	}
    */
}


//-- ������� �������� �� URL ��������� --//
void __fastcall TMainForm::Sources_StringGridSelectCell(TObject *Sender, int ACol,
		  int ARow, bool &CanSelect)
{
	//-- ������� �� url --//

	if(ACol == 2 && ARow > 0)
	{
		String url = engine->Data()->map_sources.find( Sources_StringGrid->Cells[0][ARow].ToInt() )->second.url;
		ShellExecute(Handle, NULL, url.c_str(), NULL, NULL, SW_SHOWNORMAL);
	}

	if(ACol == 3 && ARow > 0)
	{
		String url = engine->Data()->map_sources.find( Sources_StringGrid->Cells[0][ARow].ToInt() )->second.dataurl;
		ShellExecute(Handle, NULL, url.c_str(), NULL, NULL, SW_SHOWNORMAL);
	}
}


//-- ������� ������� ����������� �������� --//
void __fastcall TMainForm::Arbitrations_ClearButton_OneClick(TObject *Sender)
{
	//-- �������� ���� �������� --//
	engine->Data()->map_arbitrations.clear();

	//-- ���������� �������������� ������ --//
	engine->SortArbitrations(engine->Config()->SortArbitrations);

	//-- ���������� ������� --//
	UpdateArbitrations(Arbitrations_ActionsGrid->Row, false);
}





//---------------------------------------------------------//
//------------- �������������� ������� ������ -------------//
//---------------------------------------------------------//

//-- ������� ��������� ���� ���������� --//
void TMainForm::SetThemeProgram()
{
	//-- ������� ���� ���������� --//
	if(MainForm->engine->Config()->Theme)
		TStyleManager::TrySetStyle("Light");
	else
		TStyleManager::TrySetStyle("Charcoal Dark Slate");
}


//-- ������� ��������� ���� ���������� ��������� (������ � �.�.) --//
void TMainForm::SetParamElements()
{
	unsigned int size_scroll = 16;

	//-- ���� �������� ������� - Sources, �������� ��������� ��������� --//
	if(PageControl->ActivePageIndex == 0)
	{
		//-- ������� ������� ������� --//
		Sources_StringGrid->Width = SourcesTab->Width - 5;
		Sources_StringGrid->Height = SourcesTab->Height - StatusBar->Height;

		//-- ������� ������� �������� --//
		Sources_StringGrid->ColWidths[0] = (Sources_StringGrid->Width-size_scroll) * engine->Config()->SourcesCol_0;
		Sources_StringGrid->ColWidths[1] = (Sources_StringGrid->Width-size_scroll) * engine->Config()->SourcesCol_1;
		Sources_StringGrid->ColWidths[2] = (Sources_StringGrid->Width-size_scroll) * engine->Config()->SourcesCol_2;
		Sources_StringGrid->ColWidths[3] = (Sources_StringGrid->Width-size_scroll) * engine->Config()->SourcesCol_3;
		Sources_StringGrid->ColWidths[4] = (Sources_StringGrid->Width-size_scroll) * engine->Config()->SourcesCol_4;
		Sources_StringGrid->ColWidths[5] = (Sources_StringGrid->Width-size_scroll) * engine->Config()->SourcesCol_5;
		Sources_StringGrid->ColWidths[6] = (Sources_StringGrid->Width-size_scroll) * engine->Config()->SourcesCol_6;

		//-- ���������� ������� --//
		UpdateSources(Sources_StringGrid->Row, true);

		return;
	}

	//-- ���� �������� ������� - Currencys, �������� ��������� ��������� --//
	if(PageControl->ActivePageIndex == 1)
	{
		//-- ������� ������� ������� --//
		Currencys_StringGrid->Width = CurrencysTab->Width - 5;
		Currencys_StringGrid->Height = CurrencysTab->Height - StatusBar->Height;

		//-- ������� ������� �������� --//
		Currencys_StringGrid->ColWidths[0] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_0;
		Currencys_StringGrid->ColWidths[1] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_1;
		Currencys_StringGrid->ColWidths[2] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_2;
		Currencys_StringGrid->ColWidths[3] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_3;
		Currencys_StringGrid->ColWidths[4] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_4;
		Currencys_StringGrid->ColWidths[5] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_5;
		Currencys_StringGrid->ColWidths[6] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_6;
		Currencys_StringGrid->ColWidths[7] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_7;

		//-- ���������� ������� --//
		UpdateCurrencys(Currencys_StringGrid->Row, true);

		return;
	}

	//-- ���� �������� ������� - Lines, �������� ��������� ��������� --//
	if(PageControl->ActivePageIndex == 2)
	{
		//-- ������� ������� ������ --//
		Lines_NamesStringGrid->Left = 0;
		Lines_NamesStringGrid->Width = (LinesTab->Width/4 - 10);
		Lines_NamesStringGrid->Height = LinesTab->Height - Lines_NotesMemo->Height - StatusBar->Height;

		Lines_SourcesStringGrid->Left = LinesTab->Width/4 * 1;
		Lines_SourcesStringGrid->Width = (LinesTab->Width/4 - 10);
		Lines_SourcesStringGrid->Height = LinesTab->Height - Lines_NotesMemo->Height - StatusBar->Height;

		Lines_CurrencysStringGrid->Left = LinesTab->Width/4 * 2;
		Lines_CurrencysStringGrid->Width = (LinesTab->Width/4 - 10);
		Lines_CurrencysStringGrid->Height = LinesTab->Height - Lines_NotesMemo->Height - StatusBar->Height;

		Lines_BasesStringGrid->Left = LinesTab->Width/4 * 3 - 10;
		Lines_BasesStringGrid->Width = LinesTab->Width/4;
		Lines_BasesStringGrid->Height = LinesTab->Height - Lines_NotesMemo->Height - StatusBar->Height;

		//-- ������� ������� ���� ������� --//
		Lines_NotesMemo->Left = Lines_NotesStatic->Left + Lines_NotesStatic->Width + 20;
		Lines_NotesMemo->Width = LinesTab->Width - 100;

		//-- ������� ������� �������� --//
		Lines_NamesStringGrid->ColWidths[0] = (Lines_NamesStringGrid->Width-size_scroll) * engine->Config()->LinesNamesCol_0;
		Lines_NamesStringGrid->ColWidths[1] = (Lines_NamesStringGrid->Width-size_scroll) * engine->Config()->LinesNamesCol_1;
		Lines_NamesStringGrid->ColWidths[2] = (Lines_NamesStringGrid->Width-size_scroll) * engine->Config()->LinesNamesCol_2;

		Lines_SourcesStringGrid->ColWidths[0] = Lines_SourcesStringGrid->Width-size_scroll;

		Lines_CurrencysStringGrid->ColWidths[0] = Lines_CurrencysStringGrid->Width-size_scroll;

		Lines_BasesStringGrid->ColWidths[0] = Lines_BasesStringGrid->Width-size_scroll;



		//-- ���������� ������� --//
		UpdateLines(Lines_NamesStringGrid->Row, Lines_SourcesStringGrid->Row, Lines_CurrencysStringGrid->Row, Lines_BasesStringGrid->Row, true);

		return;
	}


	//-- ���� �������� ������� - Corrections, �������� ��������� ��������� --//
	if(PageControl->ActivePageIndex == 4)
	{
		//-- ������� ������� ������� --//
		Corrections_StringGrid->Width = CorrectionsTab->Width - 5;
		Corrections_StringGrid->Height = CorrectionsTab->Height - StatusBar->Height;

		//-- ������� ������� �������� --//
		Corrections_StringGrid->ColWidths[0] = (Corrections_StringGrid->Width-size_scroll) * engine->Config()->CorrectionsCol_0;
		Corrections_StringGrid->ColWidths[1] = (Corrections_StringGrid->Width-size_scroll) * engine->Config()->CorrectionsCol_1;
		Corrections_StringGrid->ColWidths[2] = (Corrections_StringGrid->Width-size_scroll) * engine->Config()->CorrectionsCol_2;
		Corrections_StringGrid->ColWidths[3] = (Corrections_StringGrid->Width-size_scroll) * engine->Config()->CorrectionsCol_3;
		Corrections_StringGrid->ColWidths[4] = (Corrections_StringGrid->Width-size_scroll) * engine->Config()->CorrectionsCol_4;
		Corrections_StringGrid->ColWidths[5] = (Corrections_StringGrid->Width-size_scroll) * engine->Config()->CorrectionsCol_5;
		Corrections_StringGrid->ColWidths[6] = (Corrections_StringGrid->Width-size_scroll) * engine->Config()->CorrectionsCol_6;

		//-- ���������� ������� --//
		UpdateCorrections(Corrections_StringGrid->Row, true);

		return;
	}

	//-- ���� �������� ������� - Arbitrations, �������� ��������� ��������� --//
	if(PageControl->ActivePageIndex == 5)
	{
		//-- ������� ������� ������ --//
		Arbitrations_ActionsGrid->Left = 0;
		Arbitrations_ActionsGrid->Width = ArbitrationsTab->Width - 5;
		Arbitrations_ActionsGrid->Height = ArbitrationsTab->Height - StatusBar->Height;


		//-- ������� ������� �������� --//
		Arbitrations_ActionsGrid->ColWidths[0] = (Arbitrations_ActionsGrid->Width-size_scroll) * engine->Config()->ArbitrationsCol_0;
		Arbitrations_ActionsGrid->ColWidths[1] = (Arbitrations_ActionsGrid->Width-size_scroll) * engine->Config()->ArbitrationsCol_1;
		Arbitrations_ActionsGrid->ColWidths[2] = (Arbitrations_ActionsGrid->Width-size_scroll) * engine->Config()->ArbitrationsCol_2;
		Arbitrations_ActionsGrid->ColWidths[3] = (Arbitrations_ActionsGrid->Width-size_scroll) * engine->Config()->ArbitrationsCol_3;
		Arbitrations_ActionsGrid->ColWidths[4] = (Arbitrations_ActionsGrid->Width-size_scroll) * engine->Config()->ArbitrationsCol_4;
		Arbitrations_ActionsGrid->ColWidths[5] = (Arbitrations_ActionsGrid->Width-size_scroll) * engine->Config()->ArbitrationsCol_5;
		Arbitrations_ActionsGrid->ColWidths[6] = (Arbitrations_ActionsGrid->Width-size_scroll) * engine->Config()->ArbitrationsCol_6;
		Arbitrations_ActionsGrid->ColWidths[7] = (Arbitrations_ActionsGrid->Width-size_scroll) * engine->Config()->ArbitrationsCol_7;
		Arbitrations_ActionsGrid->ColWidths[8] = (Arbitrations_ActionsGrid->Width-size_scroll) * engine->Config()->ArbitrationsCol_8;
		Arbitrations_ActionsGrid->ColWidths[9] = (Arbitrations_ActionsGrid->Width-size_scroll) * engine->Config()->ArbitrationsCol_9;
		Arbitrations_ActionsGrid->ColWidths[10] = (Arbitrations_ActionsGrid->Width-size_scroll) * engine->Config()->ArbitrationsCol_10;


		//-- ���������� ������� --//
		//UpdateArbitrations(Arbitrations_ActionsGrid->Row, true);

		return;
	}


	//-- ���� �������� ������� - Collections, �������� ��������� ��������� --//
	if(PageControl->ActivePageIndex == 6)
	{
		//-- ������� ������� ������� --//
		Collections_StringGrid->Width = �ollectionsTab->Width - 5;
		Collections_StringGrid->Height = �ollectionsTab->Height - StatusBar->Height;

		//-- ������� ������� �������� --//
		Collections_StringGrid->ColWidths[0] = (Collections_StringGrid->Width-size_scroll) * 0.30;
		Collections_StringGrid->ColWidths[1] = (Collections_StringGrid->Width-size_scroll) * 0.70;

		//-- ���������� ������� --//
		//UpdateCollections();

		return;
	}
}


//-- ������� ��������� ������� ������ ������� �� ������� SOURCES --//
void __fastcall TMainForm::Sources_StringGridMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	unsigned int size_scroll = 16;

	//-- �������� �� ��������� ������� ������ ������� --//
	if( (Sources_StringGrid->Width-size_scroll)/Sources_StringGrid->ColWidths[0] != engine->Config()->SourcesCol_0 ||
		(Sources_StringGrid->Width-size_scroll)/Sources_StringGrid->ColWidths[1] != engine->Config()->SourcesCol_1 ||
		(Sources_StringGrid->Width-size_scroll)/Sources_StringGrid->ColWidths[2] != engine->Config()->SourcesCol_2 ||
		(Sources_StringGrid->Width-size_scroll)/Sources_StringGrid->ColWidths[3] != engine->Config()->SourcesCol_3 ||
		(Sources_StringGrid->Width-size_scroll)/Sources_StringGrid->ColWidths[4] != engine->Config()->SourcesCol_4 ||
		(Sources_StringGrid->Width-size_scroll)/Sources_StringGrid->ColWidths[5] != engine->Config()->SourcesCol_5 ||
		(Sources_StringGrid->Width-size_scroll)/Sources_StringGrid->ColWidths[6] != engine->Config()->SourcesCol_6
	  )
	  {
		  //-- � ������, ���� ������������ ������� ������ �������, ��������� � ������������ --//
		  if(Sources_StringGrid->ColWidths[0] +
			 Sources_StringGrid->ColWidths[1] +
			 Sources_StringGrid->ColWidths[2] +
			 Sources_StringGrid->ColWidths[3] +
			 Sources_StringGrid->ColWidths[4] +
			 Sources_StringGrid->ColWidths[5] +
			 Sources_StringGrid->ColWidths[6]
			 > Sources_StringGrid->Width - size_scroll)
			 {
				 //-- � ������ �������� ��������, ��������������� ������ --//
				 SetParamElements();
			 }
		  else
		  {
			//-- � ������ ������ ����������, ��������� ��������� ������ --//
			engine->Config()->SourcesCol_0 = (float)Sources_StringGrid->ColWidths[0]/(Sources_StringGrid->Width-size_scroll);
			engine->Config()->SourcesCol_1 = (float)Sources_StringGrid->ColWidths[1]/(Sources_StringGrid->Width-size_scroll);
			engine->Config()->SourcesCol_2 = (float)Sources_StringGrid->ColWidths[2]/(Sources_StringGrid->Width-size_scroll);
			engine->Config()->SourcesCol_3 = (float)Sources_StringGrid->ColWidths[3]/(Sources_StringGrid->Width-size_scroll);
			engine->Config()->SourcesCol_4 = (float)Sources_StringGrid->ColWidths[4]/(Sources_StringGrid->Width-size_scroll);
			engine->Config()->SourcesCol_5 = (float)Sources_StringGrid->ColWidths[5]/(Sources_StringGrid->Width-size_scroll);
			engine->Config()->SourcesCol_6 = (float)Sources_StringGrid->ColWidths[6]/(Sources_StringGrid->Width-size_scroll);

			//-- ���������� ���������� --//
			SetParamElements();
		  }
	  }
}


//-- ������� ��������� ������� ������ ������� �� ������� CURRENCYS --//
void __fastcall TMainForm::Currencys_StringGridMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	unsigned int size_scroll = 16;

	//-- �������� �� ��������� ������� ������ ������� --//
	if( (Currencys_StringGrid->Width-size_scroll)/Currencys_StringGrid->ColWidths[0] != engine->Config()->CurrencysCol_0 ||
		(Currencys_StringGrid->Width-size_scroll)/Currencys_StringGrid->ColWidths[1] != engine->Config()->CurrencysCol_1 ||
		(Currencys_StringGrid->Width-size_scroll)/Currencys_StringGrid->ColWidths[2] != engine->Config()->CurrencysCol_2 ||
		(Currencys_StringGrid->Width-size_scroll)/Currencys_StringGrid->ColWidths[3] != engine->Config()->CurrencysCol_3 ||
		(Currencys_StringGrid->Width-size_scroll)/Currencys_StringGrid->ColWidths[4] != engine->Config()->CurrencysCol_4 ||
		(Currencys_StringGrid->Width-size_scroll)/Currencys_StringGrid->ColWidths[5] != engine->Config()->CurrencysCol_5 ||
		(Currencys_StringGrid->Width-size_scroll)/Currencys_StringGrid->ColWidths[6] != engine->Config()->CurrencysCol_6 ||
		(Currencys_StringGrid->Width-size_scroll)/Currencys_StringGrid->ColWidths[7] != engine->Config()->CurrencysCol_7
	  )
	  {
		  //-- � ������, ���� ������������ ������� ������ �������, ��������� � ������������ --//
		  if(Currencys_StringGrid->ColWidths[0] +
			 Currencys_StringGrid->ColWidths[1] +
			 Currencys_StringGrid->ColWidths[2] +
			 Currencys_StringGrid->ColWidths[3] +
			 Currencys_StringGrid->ColWidths[4] +
			 Currencys_StringGrid->ColWidths[5] +
			 Currencys_StringGrid->ColWidths[6] +
			 Currencys_StringGrid->ColWidths[7]
			 > Currencys_StringGrid->Width - size_scroll)
			 {
				 //-- � ������ �������� ��������, ��������������� ������ --//
				 SetParamElements();
			 }
		  else
		  {
			//-- � ������ ������ ����������, ��������� ��������� ������ --//
			engine->Config()->CurrencysCol_0 = (float)Currencys_StringGrid->ColWidths[0]/(Currencys_StringGrid->Width-size_scroll);
			engine->Config()->CurrencysCol_1 = (float)Currencys_StringGrid->ColWidths[1]/(Currencys_StringGrid->Width-size_scroll);
			engine->Config()->CurrencysCol_2 = (float)Currencys_StringGrid->ColWidths[2]/(Currencys_StringGrid->Width-size_scroll);
			engine->Config()->CurrencysCol_3 = (float)Currencys_StringGrid->ColWidths[3]/(Currencys_StringGrid->Width-size_scroll);
			engine->Config()->CurrencysCol_4 = (float)Currencys_StringGrid->ColWidths[4]/(Currencys_StringGrid->Width-size_scroll);
			engine->Config()->CurrencysCol_5 = (float)Currencys_StringGrid->ColWidths[5]/(Currencys_StringGrid->Width-size_scroll);
			engine->Config()->CurrencysCol_6 = (float)Currencys_StringGrid->ColWidths[6]/(Currencys_StringGrid->Width-size_scroll);
			engine->Config()->CurrencysCol_7 = (float)Currencys_StringGrid->ColWidths[7]/(Currencys_StringGrid->Width-size_scroll);

			//-- ���������� ���������� --//
			SetParamElements();
		  }
	  }
}


//-- ������� ��������� ������� ������ ������� �� ������� LINES --//
void __fastcall TMainForm::Lines_NamesStringGridMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
    unsigned int size_scroll = 16;

	//-- �������� �� ��������� ������� ������ ������� --//
	if( (Lines_NamesStringGrid->Width-size_scroll)/Lines_NamesStringGrid->ColWidths[0] != engine->Config()->LinesNamesCol_0 ||
		(Lines_NamesStringGrid->Width-size_scroll)/Lines_NamesStringGrid->ColWidths[1] != engine->Config()->LinesNamesCol_1 ||
		(Lines_NamesStringGrid->Width-size_scroll)/Lines_NamesStringGrid->ColWidths[2] != engine->Config()->LinesNamesCol_2
	  )
	  {
		  //-- � ������, ���� ������������ ������� ������ �������, ��������� � ������������ --//
		  if(Lines_NamesStringGrid->ColWidths[0] +
			 Lines_NamesStringGrid->ColWidths[1] +
			 Lines_NamesStringGrid->ColWidths[2]
			 > Lines_NamesStringGrid->Width - size_scroll)
			 {
				 //-- � ������ �������� ��������, ��������������� ������ --//
				 SetParamElements();
			 }
		  else
		  {
			//-- � ������ ������ ����������, ��������� ��������� ������ --//
			engine->Config()->LinesNamesCol_0 = (float)Lines_NamesStringGrid->ColWidths[0]/(Lines_NamesStringGrid->Width-size_scroll);
			engine->Config()->LinesNamesCol_1 = (float)Lines_NamesStringGrid->ColWidths[1]/(Lines_NamesStringGrid->Width-size_scroll);
			engine->Config()->LinesNamesCol_2 = (float)Lines_NamesStringGrid->ColWidths[2]/(Lines_NamesStringGrid->Width-size_scroll);

			//-- ���������� ���������� --//
			SetParamElements();
		  }
	  }
}



//-- ������� ��������� ������� ������ ������� �� ������� CORRECTIONS --//
void __fastcall TMainForm::Corrections_StringGridMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	unsigned int size_scroll = 16;

	//-- �������� �� ��������� ������� ������ ������� --//
	if( (Corrections_StringGrid->Width-size_scroll)/Corrections_StringGrid->ColWidths[0] != engine->Config()->CorrectionsCol_0 ||
		(Corrections_StringGrid->Width-size_scroll)/Corrections_StringGrid->ColWidths[1] != engine->Config()->CorrectionsCol_1 ||
		(Corrections_StringGrid->Width-size_scroll)/Corrections_StringGrid->ColWidths[2] != engine->Config()->CorrectionsCol_2 ||
		(Corrections_StringGrid->Width-size_scroll)/Corrections_StringGrid->ColWidths[3] != engine->Config()->CorrectionsCol_3 ||
		(Corrections_StringGrid->Width-size_scroll)/Corrections_StringGrid->ColWidths[4] != engine->Config()->CorrectionsCol_4 ||
		(Corrections_StringGrid->Width-size_scroll)/Corrections_StringGrid->ColWidths[5] != engine->Config()->CorrectionsCol_5 ||
		(Corrections_StringGrid->Width-size_scroll)/Corrections_StringGrid->ColWidths[6] != engine->Config()->CorrectionsCol_6
	  )
	  {
		  //-- � ������, ���� ������������ ������� ������ �������, ��������� � ������������ --//
		  if(Corrections_StringGrid->ColWidths[0] +
			 Corrections_StringGrid->ColWidths[1] +
			 Corrections_StringGrid->ColWidths[2] +
			 Corrections_StringGrid->ColWidths[3] +
			 Corrections_StringGrid->ColWidths[4] +
			 Corrections_StringGrid->ColWidths[5] +
			 Corrections_StringGrid->ColWidths[6]
			 > Corrections_StringGrid->Width - size_scroll)
			 {
				 //-- � ������ �������� ��������, ��������������� ������ --//
				 SetParamElements();
			 }
		  else
		  {
			//-- � ������ ������ ����������, ��������� ��������� ������ --//
			engine->Config()->CorrectionsCol_0 = (float)Corrections_StringGrid->ColWidths[0]/(Corrections_StringGrid->Width-size_scroll);
			engine->Config()->CorrectionsCol_1 = (float)Corrections_StringGrid->ColWidths[1]/(Corrections_StringGrid->Width-size_scroll);
			engine->Config()->CorrectionsCol_2 = (float)Corrections_StringGrid->ColWidths[2]/(Corrections_StringGrid->Width-size_scroll);
			engine->Config()->CorrectionsCol_3 = (float)Corrections_StringGrid->ColWidths[3]/(Corrections_StringGrid->Width-size_scroll);
			engine->Config()->CorrectionsCol_4 = (float)Corrections_StringGrid->ColWidths[4]/(Corrections_StringGrid->Width-size_scroll);
			engine->Config()->CorrectionsCol_5 = (float)Corrections_StringGrid->ColWidths[5]/(Corrections_StringGrid->Width-size_scroll);
			engine->Config()->CorrectionsCol_6 = (float)Corrections_StringGrid->ColWidths[6]/(Corrections_StringGrid->Width-size_scroll);

			//-- ���������� ���������� --//
			SetParamElements();
		  }
	  }
}


//-- ������� ��������� ������� ������ ������� �� ������� ARBITRATIONS --//
void __fastcall TMainForm::Arbitrations_ActionsGridMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
    unsigned int size_scroll = 16;

	//-- ���������� ��������� ������� ����� --//
	if(Arbitrations_ActionsGrid->ColWidths[0] != 0)
	{
		SetParamElements();
	}


	//-- �������� �� ��������� ������� ������ ������� --//
	if( (Arbitrations_ActionsGrid->Width-size_scroll)/Arbitrations_ActionsGrid->ColWidths[1] != engine->Config()->ArbitrationsCol_1 ||
		(Arbitrations_ActionsGrid->Width-size_scroll)/Arbitrations_ActionsGrid->ColWidths[2] != engine->Config()->ArbitrationsCol_2 ||
		(Arbitrations_ActionsGrid->Width-size_scroll)/Arbitrations_ActionsGrid->ColWidths[3] != engine->Config()->ArbitrationsCol_3 ||
		(Arbitrations_ActionsGrid->Width-size_scroll)/Arbitrations_ActionsGrid->ColWidths[4] != engine->Config()->ArbitrationsCol_4 ||
		(Arbitrations_ActionsGrid->Width-size_scroll)/Arbitrations_ActionsGrid->ColWidths[5] != engine->Config()->ArbitrationsCol_5 ||
		(Arbitrations_ActionsGrid->Width-size_scroll)/Arbitrations_ActionsGrid->ColWidths[6] != engine->Config()->ArbitrationsCol_6 ||
		(Arbitrations_ActionsGrid->Width-size_scroll)/Arbitrations_ActionsGrid->ColWidths[7] != engine->Config()->ArbitrationsCol_7 ||
		(Arbitrations_ActionsGrid->Width-size_scroll)/Arbitrations_ActionsGrid->ColWidths[8] != engine->Config()->ArbitrationsCol_8 ||
		(Arbitrations_ActionsGrid->Width-size_scroll)/Arbitrations_ActionsGrid->ColWidths[9] != engine->Config()->ArbitrationsCol_8 ||
		(Arbitrations_ActionsGrid->Width-size_scroll)/Arbitrations_ActionsGrid->ColWidths[10] != engine->Config()->ArbitrationsCol_10
	  )
	  {
		  //-- � ������, ���� ������������ ������� ������ �������, ��������� � ������������ --//
		  if(Arbitrations_ActionsGrid->ColWidths[0] +
			 Arbitrations_ActionsGrid->ColWidths[1] +
			 Arbitrations_ActionsGrid->ColWidths[2] +
			 Arbitrations_ActionsGrid->ColWidths[3] +
			 Arbitrations_ActionsGrid->ColWidths[4] +
			 Arbitrations_ActionsGrid->ColWidths[5] +
			 Arbitrations_ActionsGrid->ColWidths[6] +
			 Arbitrations_ActionsGrid->ColWidths[7] +
			 Arbitrations_ActionsGrid->ColWidths[8] +
			 Arbitrations_ActionsGrid->ColWidths[9] +
			 Arbitrations_ActionsGrid->ColWidths[10]
			 > Arbitrations_ActionsGrid->Width - size_scroll)
			 {
				 //-- � ������ �������� ��������, ��������������� ������ --//
				 SetParamElements();
			 }
		  else
		  {
			//-- � ������ ������ ��������, ��������� ��������� ������ --//

			engine->Config()->ArbitrationsCol_1 = (float)Arbitrations_ActionsGrid->ColWidths[1]/(Arbitrations_ActionsGrid->Width-size_scroll);
			engine->Config()->ArbitrationsCol_2 = (float)Arbitrations_ActionsGrid->ColWidths[2]/(Arbitrations_ActionsGrid->Width-size_scroll);
			engine->Config()->ArbitrationsCol_3 = (float)Arbitrations_ActionsGrid->ColWidths[3]/(Arbitrations_ActionsGrid->Width-size_scroll);
			engine->Config()->ArbitrationsCol_4 = (float)Arbitrations_ActionsGrid->ColWidths[4]/(Arbitrations_ActionsGrid->Width-size_scroll);
			engine->Config()->ArbitrationsCol_5 = (float)Arbitrations_ActionsGrid->ColWidths[5]/(Arbitrations_ActionsGrid->Width-size_scroll);
			engine->Config()->ArbitrationsCol_6 = (float)Arbitrations_ActionsGrid->ColWidths[6]/(Arbitrations_ActionsGrid->Width-size_scroll);
			engine->Config()->ArbitrationsCol_7 = (float)Arbitrations_ActionsGrid->ColWidths[7]/(Arbitrations_ActionsGrid->Width-size_scroll);
			engine->Config()->ArbitrationsCol_8 = (float)Arbitrations_ActionsGrid->ColWidths[8]/(Arbitrations_ActionsGrid->Width-size_scroll);
			engine->Config()->ArbitrationsCol_9 = (float)Arbitrations_ActionsGrid->ColWidths[9]/(Arbitrations_ActionsGrid->Width-size_scroll);
			engine->Config()->ArbitrationsCol_10 = (float)Arbitrations_ActionsGrid->ColWidths[10]/(Arbitrations_ActionsGrid->Width-size_scroll);


			//-- ���������� ���������� --//
			SetParamElements();
		  }
	  }
}


//-- ������� ���������� �������� ���������� ���������� ������ --//
void TMainForm::UpdateLastCollected(const bool SetTime)
{
	//-- �������� �� ������������� ������ ���������� �������� ������� --//
	if(SetTime)
	{
		//--  ����������� ������� �� ���� ������ --//
		unsigned int StartTimeInSecond = time_collect.StartCollectSS + time_collect.StartCollectNN * 60 + time_collect.StartCollectHH * 3600
									   + time_collect.StartCollectDD * 86400 + time_collect.StartCollectMM * 2628000 + time_collect.StartCollectYY * 31536000;

		unsigned int EndTimeInSecond = time_collect.EndCollectSS + time_collect.EndCollectNN * 60 + time_collect.EndCollectHH * 3600
									   + time_collect.EndCollectDD * 86400 + time_collect.EndCollectMM * 2628000 + time_collect.EndCollectYY * 31536000;


		//-- ������ ��������� ��������� ����� ������ --//
		engine->Config()->LastCollectedDD = time_collect.EndCollectDD;
		engine->Config()->LastCollectedMM = time_collect.EndCollectMM;
		engine->Config()->LastCollectedYY = time_collect.EndCollectYY;
		engine->Config()->LastCollectedHH = time_collect.EndCollectHH;
		engine->Config()->LastCollectedNN = time_collect.EndCollectNN;
		engine->Config()->LastCollectedSS = time_collect.EndCollectSS;

		//-- �����, ����������� �� ���� ������ --//
		if(EndTimeInSecond - StartTimeInSecond < 99999)
			engine->Config()->LastTimeOnCollect = EndTimeInSecond - StartTimeInSecond;
	}

	//-- ���������� ������ ���� --//
	MainForm->StatusBar->Panels->Items[1]->Text = 	"Last collected: "
													+ UnicodeString( engine->Config()->LastCollectedDD )
													+ "." + UnicodeString( engine->Config()->LastCollectedMM )
													+ "." + UnicodeString( engine->Config()->LastCollectedYY )
													+ " " + UnicodeString( engine->Config()->LastCollectedHH )
													+ ":" + UnicodeString( engine->Config()->LastCollectedNN )
													+ ":" + UnicodeString( engine->Config()->LastCollectedSS )
													+ "  Time on collected: "
													+ engine->Config()->LastTimeOnCollect + " s.";

	//-- ���������� ��������� � ���� --//
	TrayIcon->Hint 	= "Last collected: "
					+ UnicodeString( engine->Config()->LastCollectedDD )
					+ "." + UnicodeString( engine->Config()->LastCollectedMM )
					+ "." + UnicodeString( engine->Config()->LastCollectedYY )
					+ " " + UnicodeString( engine->Config()->LastCollectedHH )
					+ ":" + UnicodeString( engine->Config()->LastCollectedNN )
					+ ":" + UnicodeString( engine->Config()->LastCollectedSS )
                    + "  Time on collected: "
					+ engine->Config()->LastTimeOnCollect + " s.";
}

//-- ������� ��������� ����������� �������� ������� SOURCE GRID --//
void TMainForm::DefaultSourcesGrid()
{
    Sources_StringGrid->Cells[0][0] = "ID:" + UnicodeString( engine->Config()->SortSources == eID ? " *" : "" );
	Sources_StringGrid->Cells[1][0] = "Name:" + UnicodeString( engine->Config()->SortSources == eNAME ? " *" : "" );
	Sources_StringGrid->Cells[2][0] = "Url:" + UnicodeString( engine->Config()->SortSources == eURL ? " *" : "" );;
	Sources_StringGrid->Cells[3][0] = "Data Url:" + UnicodeString( engine->Config()->SortSources == eDATAURL ? " *" : "" );;
	Sources_StringGrid->Cells[4][0] = "Getter:" + UnicodeString( engine->Config()->SortSources == eGETTER ? " *" : "" );;
	Sources_StringGrid->Cells[5][0] = "Enabled:" + UnicodeString( engine->Config()->SortSources == eENABLED ? " *" : "" );;
	Sources_StringGrid->Cells[6][0] = "Notes:" + UnicodeString( engine->Config()->SortSources == eNOTES ? " *" : "" );;
}

//-- ������� ��������� ����������� �������� ������� CURRENCYS GRID --//
void TMainForm::DefaultCurrencysGrid()
{
	Currencys_StringGrid->Cells[0][0] = "ID:" + UnicodeString( engine->Config()->SortCurrencys == eID ? " *" : "" );
	Currencys_StringGrid->Cells[1][0] = "Name:" + UnicodeString( engine->Config()->SortCurrencys == eNAME ? " *" : "" );
	Currencys_StringGrid->Cells[2][0] = "Short:" + UnicodeString( engine->Config()->SortCurrencys == eSHORTN ? " *" : "" );
	Currencys_StringGrid->Cells[3][0] = "Fee:" + UnicodeString( engine->Config()->SortCurrencys == eFEE ? " *" : "" );
	Currencys_StringGrid->Cells[4][0] = "Min sum:" + UnicodeString( engine->Config()->SortCurrencys == eMINSUM ? " *" : "" );
	Currencys_StringGrid->Cells[5][0] = "Base:" + UnicodeString( engine->Config()->SortCurrencys == eBASE ? " *" : "" );
	Currencys_StringGrid->Cells[6][0] = "Enabled:" + UnicodeString( engine->Config()->SortCurrencys == eENABLED ? " *" : "" );
	Currencys_StringGrid->Cells[7][0] = "Notes:" + UnicodeString( engine->Config()->SortCurrencys == eNOTES ? " *" : "" );
}


//-- ������� ��������� ����������� �������� ������� LINES GRID --//
void TMainForm::DefaultLinesGrid()
{
	Lines_NamesStringGrid->Cells[0][0] = "ID:" + UnicodeString( engine->Config()->SortLines == eID ? " *" : "" );
	Lines_NamesStringGrid->Cells[1][0] = "Name:" + UnicodeString( engine->Config()->SortLines == eNAME ? " *" : "" );
	Lines_NamesStringGrid->Cells[2][0] = "Enabled:" + UnicodeString( engine->Config()->SortLines == eENABLED ? " *" : "" );

	Lines_SourcesStringGrid->Cells[0][0] = "Sources:";
	Lines_CurrencysStringGrid->Cells[0][0] = "Currensys:";
	Lines_BasesStringGrid->Cells[0][0] = "Bases:";
}

//-- ������� ��������� ����������� �������� ������� CORRECTIONS GRID --//
void TMainForm::DefaultCorrectionsGrid()
{
	Corrections_StringGrid->Cells[0][0] = "ID:" + UnicodeString( engine->Config()->SortCorrections == eID ? " *" : "" );
	Corrections_StringGrid->Cells[1][0] = "Source:" + UnicodeString( engine->Config()->SortCorrections == eSOURCE ? " *" : "" );
	Corrections_StringGrid->Cells[2][0] = "Curr Out:" + UnicodeString( engine->Config()->SortCorrections == eCURROUT ? " *" : "" );
	Corrections_StringGrid->Cells[3][0] = "Curr In:" + UnicodeString( engine->Config()->SortCorrections == eCURRIN ? " *" : "" );
	Corrections_StringGrid->Cells[4][0] = "Fee:" + UnicodeString( engine->Config()->SortCorrections == eFEE ? " *" : "" );
	Corrections_StringGrid->Cells[5][0] = "Enabled:" + UnicodeString( engine->Config()->SortCorrections == eENABLED ? " *" : "" );
	Corrections_StringGrid->Cells[6][0] = "Notes:" + UnicodeString( engine->Config()->SortCorrections == eNOTES ? " *" : "" );
}

//-- ������� ��������� ����������� �������� ������� ARBITRATIONS GRID --//
void TMainForm::DefaultArbitrationsGrid()
{
	Arbitrations_ActionsGrid->Cells[0][0] = "ID:" + UnicodeString( engine->Config()->SortArbitrations == eID ? " *" : "" );
	Arbitrations_ActionsGrid->Cells[1][0] = "Factor:" + UnicodeString( engine->Config()->SortArbitrations == eFACTOR ? " *" : "" );
	Arbitrations_ActionsGrid->Cells[2][0] = "Line:" + UnicodeString( engine->Config()->SortArbitrations == eLINE ? " *" : "" );
	Arbitrations_ActionsGrid->Cells[3][0] = "Cur Out:" + UnicodeString( engine->Config()->SortArbitrations == eCURROUT ? " *" : "" );
	Arbitrations_ActionsGrid->Cells[4][0] = "Cur In:" + UnicodeString( engine->Config()->SortArbitrations == eCURRIN ? " *" : "" );
	Arbitrations_ActionsGrid->Cells[5][0] = "Source:" + UnicodeString( engine->Config()->SortArbitrations == eSOURCE ? " *" : "" );
	Arbitrations_ActionsGrid->Cells[6][0] = "Notes:" + UnicodeString( engine->Config()->SortArbitrations == eNOTES ? " *" : "" );
	Arbitrations_ActionsGrid->Cells[7][0] = "Rate:" + UnicodeString( engine->Config()->SortArbitrations == eRATE ? " *" : "" );
	Arbitrations_ActionsGrid->Cells[8][0] = "Real Rate:" + UnicodeString( engine->Config()->SortArbitrations == eREALRATE ? " *" : "" );
	Arbitrations_ActionsGrid->Cells[9][0] = "Amount:" + UnicodeString( engine->Config()->SortArbitrations == eAMOUNT ? " *" : "" );
	Arbitrations_ActionsGrid->Cells[10][0] = "Time:" + UnicodeString( engine->Config()->SortArbitrations == eTIME ? " *" : "" );
}

//-- ������� ��������� ����������� �������� ������� COLLECTIONS GRID --//
void TMainForm::DefaultCollectionsGrid()
{
	Collections_StringGrid->Cells[0][0] = "Sources:";
    Collections_StringGrid->Cells[1][0] = "Notes:";
}


//-- ������� ������� STRING GRID --//
void TMainForm::ClearStringGrid(TStringGrid *StringGrid)
{
	for(int i=0; i != StringGrid->ColCount; i ++)
	{
		for(int k=1; k != StringGrid->RowCount; k ++)
		{
            StringGrid->Cells[i][k] = "";
        }
	}

	StringGrid->RowCount = 2;

	for(int i=0; i != StringGrid->ColCount; i++)
		StringGrid->Cells[i][1] = "";
}


//-- ������� ���������� SOURCES GRID --//
void TMainForm::UpdateSources(unsigned int Row, bool AutoUpdate)
{

    //-- ���� ���� ��������� ��������, ���������� �������� ������ --//
	if(engine->GetSortedSources().size() + 1 < Sources_StringGrid->RowCount)
		Row = Row - 1;

	//-- �������� �������� ������ --//
	if(Row == 0)
		Row = 1;

	//-- ������� ������� --//
	ClearStringGrid( Sources_StringGrid );


	if(engine->GetSortedSources().size())
	{
		//-- ���������� ������� --//
		int row_count=1;
		for(std::vector< int >::iterator source_iterator = engine->GetSortedSources().begin(); source_iterator != engine->GetSortedSources().end(); source_iterator ++)
		{
			//-- ����� � MAP'e ������� �������� �� ��������������� ������ --//
			MSource::iterator map_iterator = engine->Data()->map_sources.find( *source_iterator );

			if(map_iterator != engine->Data()->map_sources.end())
			{
                //-- ID --//
				Sources_StringGrid->Cells[0][row_count] = map_iterator->first;

				UnicodeString end;


				end = map_iterator->second.name.Length()>Sources_StringGrid->ColWidths[1]/8 ? end = "..." : end = "";
				Sources_StringGrid->Cells[1][row_count] = map_iterator->second.name.SubString(0, Sources_StringGrid->ColWidths[1]/8) + end;

				end = map_iterator->second.url.Length()>Sources_StringGrid->ColWidths[2]/8 ? end = "..." : end = "";
				Sources_StringGrid->Cells[2][row_count] = map_iterator->second.url.SubString(0, Sources_StringGrid->ColWidths[2]/8) + end;

				end = map_iterator->second.dataurl.Length()>Sources_StringGrid->ColWidths[3]/8 ? end = "..." : end = "";
				Sources_StringGrid->Cells[3][row_count] = map_iterator->second.dataurl.SubString(0, Sources_StringGrid->ColWidths[3]/8) + end;

				end = map_iterator->second.getter.Length()>Sources_StringGrid->ColWidths[4]/8 ? end = "..." : end = "";
				Sources_StringGrid->Cells[4][row_count] = map_iterator->second.getter.SubString(0, Sources_StringGrid->ColWidths[4]/8) + end;

				end = map_iterator->second.getter.Length()>Sources_StringGrid->ColWidths[5]/8 ? end = "..." : end = "";
				Sources_StringGrid->Cells[5][row_count] = map_iterator->second.enabled.SubString(0, Sources_StringGrid->ColWidths[5]/8) + end;;

				end = map_iterator->second.notes.Length()>Sources_StringGrid->ColWidths[6]/8 ? end = "..." : end = "";
				Sources_StringGrid->Cells[6][row_count] = map_iterator->second.notes.SubString(0, Sources_StringGrid->ColWidths[6]/8) + end;

                row_count ++;

				//-- ���������� ������ --//
				Sources_StringGrid->RowCount ++;
			}
		}

        //-- �������� ������ ������ --//
		Sources_StringGrid->RowCount --;

		//-- ��������� �������� ������ --//
		if(AutoUpdate && PageControl->ActivePageIndex == 0)
		{
			Sources_StringGrid->Row = Row;
			Sources_StringGrid->SetFocus();
		}
	}


    //-- ����������� ���������� ��������� ������� Sources --//
	//-- � ����������� �� ������� ������ � ������� --//
	if(Sources_StringGrid->Cells[0][1].IsEmpty())
	{
		Sources_EditButton->Enabled = false;
		Sources_DeleteButton->Enabled = false;

		return;
	}
	else
	{
		Sources_EditButton->Enabled = true;
		Sources_DeleteButton->Enabled = true;
	}
}


//-- ������� ���������� CURRENCYS --//
void TMainForm::UpdateCurrencys(unsigned int Row, bool AutoUpdate)
{
	//-- ���� ���� ��������� ��������, ���������� �������� ������ --//
	if(engine->GetSorted�urrencys().size() + 1 < Currencys_StringGrid->RowCount)
		Row = Row - 1;

	//-- �������� �������� ������ --//
	if(Row == 0)
		Row = 1;


	//-- ������� ������� --//
	ClearStringGrid( Currencys_StringGrid );


	if(engine->GetSorted�urrencys().size())
	{

		//-- ���������� ������� --//
		int row_count=1;
		for(std::vector< int >::iterator currency_iterator = engine->GetSorted�urrencys().begin(); currency_iterator != engine->GetSorted�urrencys().end(); currency_iterator ++)
		{
			//-- ����� � MAP'e ������� �������� �� ��������������� ������ --//
			MCurrency::iterator map_iterator = engine->Data()->map_currencys.find( *currency_iterator );

			if(map_iterator != engine->Data()->map_currencys.end())
			{

				//-- ID --//
				Currencys_StringGrid->Cells[0][row_count] = map_iterator->first;

				UnicodeString end;

				end = map_iterator->second.name.Length()>Currencys_StringGrid->ColWidths[1]/8 ? end = "..." : end = "";
				Currencys_StringGrid->Cells[1][row_count] = map_iterator->second.name.SubString(0, Currencys_StringGrid->ColWidths[1]/8) + end;

				end = map_iterator->second.shortn.Length()>Currencys_StringGrid->ColWidths[2]/8 ? end = "..." : end = "";
				Currencys_StringGrid->Cells[2][row_count] = map_iterator->second.shortn.SubString(0, Currencys_StringGrid->ColWidths[2]/8) + end;

				end = map_iterator->second.fee.Length()>Currencys_StringGrid->ColWidths[3]/8 ? end = "..." : end = "";
				Currencys_StringGrid->Cells[3][row_count] = engine->FloatWithDots( map_iterator->second.fee ).SubString(0, Currencys_StringGrid->ColWidths[3]/8) + end;

				end = map_iterator->second.minSum.Length()>Currencys_StringGrid->ColWidths[4]/8 ? end = "..." : end = "";
				Currencys_StringGrid->Cells[4][row_count] = map_iterator->second.minSum.SubString(0, Currencys_StringGrid->ColWidths[4]/8) + end;

				end = map_iterator->second.base.Length()>Currencys_StringGrid->ColWidths[5]/8 ? end = "..." : end = "";
				Currencys_StringGrid->Cells[5][row_count] = map_iterator->second.base.SubString(0, Currencys_StringGrid->ColWidths[5]/8) + end;

				end = map_iterator->second.enabled.Length()>Currencys_StringGrid->ColWidths[6]/8 ? end = "..." : end = "";
				Currencys_StringGrid->Cells[6][row_count] = map_iterator->second.enabled.SubString(0, Currencys_StringGrid->ColWidths[6]/8) + end;;

				end = map_iterator->second.notes.Length()>Currencys_StringGrid->ColWidths[7]/8 ? end = "..." : end = "";
				Currencys_StringGrid->Cells[7][row_count] = map_iterator->second.notes.SubString(0, Currencys_StringGrid->ColWidths[7]/8) + end;

                row_count ++;

				//-- ���������� ������ --//
				Currencys_StringGrid->RowCount ++;
			 }
		}

		//-- �������� ������ ������ --//
		Currencys_StringGrid->RowCount --;

		//-- ��������� �������� ������ --//
		if(AutoUpdate && PageControl->ActivePageIndex == 1)
		{
			Currencys_StringGrid->Row = Row;
			Currencys_StringGrid->SetFocus();
		}
	}


    //-- ����������� ���������� ��������� ������� Currencys --//
	//-- � ����������� �� ������� ������ � ������� --//
	if(Currencys_StringGrid->Cells[0][1].IsEmpty())
	{
		Currencys_EditButton->Enabled = false;
		Currencys_DeleteButton->Enabled = false;

		return;
	}
	else
	{
		Currencys_EditButton->Enabled = true;
		Currencys_DeleteButton->Enabled = true;
	}
}



//-- ������� ���������� LINES --//
void TMainForm::UpdateLines(unsigned int NamesRow, unsigned int SourcesRow, unsigned int CurrencysRow, unsigned int BasesRow, bool AutoUpdate)
{

	//-- ���� ���� ��������� ��������, ���������� �������� ������ --//
	if(engine->GetSortedLines().size() + 1 < Lines_NamesStringGrid->RowCount)
		NamesRow = NamesRow - 1;

	//-- �������� �������� ������ --//
	if(NamesRow == 0)
		NamesRow = 1;


	//-- ������� ������� --//
	ClearStringGrid( Lines_NamesStringGrid );


	if(engine->GetSortedLines().size())
	{
		//-- ������� ���� ������� --//
		Lines_NotesMemo->Clear();


		//-- ���������� ������� ��� ������� --//
		int row_count=1;
		for(std::vector< int >::iterator line_iterator = engine->GetSortedLines().begin(); line_iterator != engine->GetSortedLines().end(); line_iterator ++)
		{
			//-- ����� � MAP'e ������� �������� �� ��������������� ������ --//

			MLine::iterator map_iterator = engine->Data()->map_lines.find( *line_iterator );

			if(map_iterator != engine->Data()->map_lines.end())
			{

				//-- ID --//
				Lines_NamesStringGrid->Cells[0][row_count] = map_iterator->first;

				UnicodeString end;

				end = map_iterator->second.name.Length()>Lines_NamesStringGrid->ColWidths[1]/8 ? end = "..." : end = "";
				Lines_NamesStringGrid->Cells[1][row_count] = map_iterator->second.name.SubString(0, Lines_NamesStringGrid->ColWidths[1]/8) + end;

				end = map_iterator->second.enabled.Length()>Lines_NamesStringGrid->ColWidths[2]/8 ? end = "..." : end = "";
				Lines_NamesStringGrid->Cells[2][row_count] = map_iterator->second.enabled.SubString(0, Lines_NamesStringGrid->ColWidths[2]/8) + end;

                row_count ++;

				//-- ���������� ������ --//
				Lines_NamesStringGrid->RowCount ++;
			 }
		}

		//-- �������� ������ ������ --//
		if(engine->GetSortedLines().size())
			Lines_NamesStringGrid->RowCount --;




		//-- ����� ID �������� ������ --//
		MLine::iterator map_iterator_activy = MainForm->engine->Data()->map_lines.find( Lines_NamesStringGrid->Cells[0][NamesRow].ToInt() );

		if(map_iterator_activy == MainForm->engine->Data()->map_lines.end())
			return;

        //-- ���� ���� ��������� ��������, ���������� �������� ������ --//
		if(map_iterator_activy->second.sources.size() + 1 < Lines_SourcesStringGrid->RowCount)
			SourcesRow = SourcesRow - 1;

		if(map_iterator_activy->second.�urrencys.size() + 1 < Lines_SourcesStringGrid->RowCount)
			CurrencysRow = CurrencysRow - 1;

		if(map_iterator_activy->second.bases.size() + 1 < Lines_BasesStringGrid->RowCount)
			BasesRow = BasesRow - 1;

        //-- �������� �������� ������ --//
		if(SourcesRow == 0)
		SourcesRow = 1;
		if(CurrencysRow == 0)
			CurrencysRow = 1;
		if(BasesRow == 0)
			BasesRow = 1;

		//-- ������� ������ --//
		ClearStringGrid( Lines_SourcesStringGrid );
		ClearStringGrid( Lines_CurrencysStringGrid );
		ClearStringGrid( Lines_BasesStringGrid );




		//-- ���������� ������� ���������� ������� --//
		for(int k=0; k != map_iterator_activy->second.sources.size(); k ++)
		{
			//-- ����� ��� ��������� �� ID --//
			MSource::iterator map_iterator_source = engine->Data()->map_sources.find( map_iterator_activy->second.sources[k] );

			if(map_iterator_source != engine->Data()->map_sources.end())
			{
				//-- ������ ����� ��������� --//
				UnicodeString end;

				end = map_iterator_source->second.name.Length()>Lines_SourcesStringGrid->ColWidths[0]/8 ? end = "..." : end = "";
				Lines_SourcesStringGrid->Cells[0][k+1] = map_iterator_source->second.name.SubString(0, Lines_SourcesStringGrid->ColWidths[0]/8) + end;

				//-- ���������� ������ --//
				Lines_SourcesStringGrid->RowCount ++;
			}
		}

		//-- �������� ������ ������ --//
		if(map_iterator_activy->second.sources.size())
			Lines_SourcesStringGrid->RowCount --;



		//-- ���������� ������� ����� ������� --//
		for(int k=0; k != map_iterator_activy->second.�urrencys.size(); k ++)
		{
			//-- ����� ��� ������ �� ID --//
			MCurrency::iterator map_iterator_currency = engine->Data()->map_currencys.find( map_iterator_activy->second.�urrencys[k] );

			if(map_iterator_currency != engine->Data()->map_currencys.end())
			{
				//-- ������ ����� ������ --//
				UnicodeString end;

				end = map_iterator_currency->second.name.Length()>Lines_CurrencysStringGrid->ColWidths[0]/8 ? end = "..." : end = "";
				Lines_CurrencysStringGrid->Cells[0][k+1] = map_iterator_currency->second.name.SubString(0, Lines_CurrencysStringGrid->ColWidths[0]/8) + end;

				//-- ���������� ������ --//
				Lines_CurrencysStringGrid->RowCount ++;
			}
		}

		//-- �������� ������ ������ --//
		if(map_iterator_activy->second.�urrencys.size())
			Lines_CurrencysStringGrid->RowCount --;



		//-- ���������� ������� ������� ����� ������� --//
		for(int k=0; k != map_iterator_activy->second.bases.size(); k ++)
		{
			//-- ����� ��� ������ �� ID --//
			MCurrency::iterator map_iterator_base = engine->Data()->map_currencys.find( map_iterator_activy->second.bases[k] );

			if(map_iterator_base != engine->Data()->map_currencys.end())
			{
				//-- ������ ����� ������ --//
				UnicodeString end;

				end = map_iterator_base->second.name.Length()>Lines_BasesStringGrid->ColWidths[0]/8 ? end = "..." : end = "";
				Lines_BasesStringGrid->Cells[0][k+1] = map_iterator_base->second.name.SubString(0, Lines_BasesStringGrid->ColWidths[0]/8) + end;

				//-- ���������� ������ --//
				Lines_BasesStringGrid->RowCount ++;
			}
		}

		//-- �������� ������ ������ --//
		if(map_iterator_activy->second.bases.size())
			Lines_BasesStringGrid->RowCount --;


        //-- ���������� ���� ������� ������� --//
		Lines_NotesMemo->Text = map_iterator_activy->second.notes;


		//-- ��������� �������� �����--//
		if(AutoUpdate && PageControl->ActivePageIndex == 2)
		{
			//-- ������� ��� --//
			Lines_NamesStringGrid->Row = NamesRow;
			Lines_NamesStringGrid->SetFocus();

			//-- ������� ���������� --//
			Lines_SourcesStringGrid->Row = SourcesRow;
			Lines_SourcesStringGrid->SetFocus();

			//-- ������� ����� --//
			Lines_CurrencysStringGrid->Row = CurrencysRow;
			Lines_CurrencysStringGrid->SetFocus();

			//-- ������� ������� ����� --//
			Lines_BasesStringGrid->Row = BasesRow;
			Lines_BasesStringGrid->SetFocus();
		}

	}


    //-- ����������� ���������� ��������� ������� Lines --//
    //-- � ����������� �� ������� ������ � ������� --//
	if(Lines_NamesStringGrid->Cells[0][1].IsEmpty())
	{
		Lines_EditButton->Enabled = false;
		Lines_DeleteButton->Enabled = false;

		return;
	}
	else
	{
		Lines_EditButton->Enabled = true;
		Lines_DeleteButton->Enabled = true;
	}
}



//-- ������� ���������� PARAMETERS --//
void TMainForm::UpdateParams()
{
	//-- ���������� ������ ������������ ������� --//
	Parameters_CoefficientEdit->Text = engine->Data()->params.factor;

	//-- ���������� ������ ������������ ������ ������� --//
	Parameters_MaxLengthEdit->Text 	 = engine->Data()->params.maxChainLen;
}



//-- ������� ���������� CORRECTIONS --//
void TMainForm::UpdateCorrections(unsigned int Row, bool AutoUpdate)
{

    //-- ���� ���� ��������� ��������, ���������� �������� ������ --//
	if(engine->GetSortedCorrections().size() + 1 < Corrections_StringGrid->RowCount)
		Row = Row - 1;

	//-- �������� �������� ������ --//
	if(Row == 0)
		Row = 1;

	//-- ������� ������� --//
	ClearStringGrid( Corrections_StringGrid );


	if(engine->GetSortedCorrections().size())
	{

		//-- ���������� ������� --//
		int row_count=1;
		for(std::vector< int >::iterator correction_iterator = engine->GetSortedCorrections().begin(); correction_iterator != engine->GetSortedCorrections().end(); correction_iterator ++)
		{
			//-- ����� � MAP'e ������� �������� �� ��������������� ������ --//
			MCorrection::iterator map_iterator = engine->Data()->map_corrections.find( *correction_iterator );

			if(map_iterator != engine->Data()->map_corrections.end())
			{

				//-- ID --//
				Corrections_StringGrid->Cells[0][row_count] = map_iterator->first;

				UnicodeString end;

				//-- ���������� �������� ��������� --//

				if(engine->Data()->map_sources.find( map_iterator->second.sourceId.ToInt() ) != engine->Data()->map_sources.end())
				{
					end = engine->Data()->map_sources.find( map_iterator->second.sourceId.ToInt() )->second.name.Length()>Corrections_StringGrid->ColWidths[1]/8 ? end = "..." : end = "";

					Corrections_StringGrid->Cells[1][row_count]
						= engine->Data()->map_sources.find( map_iterator->second.sourceId.ToInt() )->second.name.SubString(0, Corrections_StringGrid->ColWidths[1]/8) + end;
				}

				//-- ���������� �������� ��������� ������ --//


				if(engine->Data()->map_currencys.find( map_iterator->second.currOut.ToInt() ) != engine->Data()->map_currencys.end())
				{
					end = engine->Data()->map_currencys.find( map_iterator->second.currOut.ToInt() )->second.name.Length()>Corrections_StringGrid->ColWidths[2]/8 ? end = "..." : end = "";

					Corrections_StringGrid->Cells[2][row_count]
						= engine->Data()->map_currencys.find( map_iterator->second.currOut.ToInt() )->second.name.SubString(0, Corrections_StringGrid->ColWidths[2]/8) + end;
				}

				//-- ���������� �������� �������� ������ --//


				if(engine->Data()->map_currencys.find( map_iterator->second.currIn.ToInt() ) != engine->Data()->map_currencys.end())
				{
					end = engine->Data()->map_currencys.find( map_iterator->second.currIn.ToInt() )->second.name.Length()>Corrections_StringGrid->ColWidths[3]/8 ? end = "..." : end = "";

					Corrections_StringGrid->Cells[3][row_count]
						= engine->Data()->map_currencys.find( map_iterator->second.currIn.ToInt() )->second.name.SubString(0, Corrections_StringGrid->ColWidths[3]/8) + end;
				}

				//-- ���������� �������������� �������� --//

				end = map_iterator->second.fee.Length()>Corrections_StringGrid->ColWidths[4]/8 ? end = "..." : end = "";
				Corrections_StringGrid->Cells[4][row_count] = engine->FloatWithDots( map_iterator->second.fee ).SubString(0, Corrections_StringGrid->ColWidths[4]/8) + end;



				end =  map_iterator->second.enabled.Length()>Corrections_StringGrid->ColWidths[5]/8 ? end = "..." : end = "";
				Corrections_StringGrid->Cells[5][row_count] =  map_iterator->second.enabled.SubString(0, Corrections_StringGrid->ColWidths[5]/8) + end;



				end = map_iterator->second.notes.Length()>Corrections_StringGrid->ColWidths[6]/8 ? end = "..." : end = "";
				Corrections_StringGrid->Cells[6][row_count] = map_iterator->second.notes.SubString(0, Corrections_StringGrid->ColWidths[6]/8) + end;;


				row_count ++;

				//-- ���������� ������ --//
				Corrections_StringGrid->RowCount ++;
			}
		}

		//-- �������� ������ ������ --//
		Corrections_StringGrid->RowCount --;

        //-- ��������� �������� ������ --//
		if(AutoUpdate && PageControl->ActivePageIndex == 4)
		{
			Corrections_StringGrid->Row = Row;
			Corrections_StringGrid->SetFocus();
		}
	}


    //-- ����������� ���������� ��������� ������� Corrections --//
	//-- � ����������� �� ������� ������ � ������� --//
	if(Corrections_StringGrid->Cells[0][1].IsEmpty())
	{
		Corrections_EditButton->Enabled = false;
		Corrections_DeleteButton->Enabled = false;

		return;
	}
	else
	{
		Corrections_EditButton->Enabled = true;
		Corrections_DeleteButton->Enabled = true;
	}
}



//-- ������� ���������� ARBITRATIONS --//
void TMainForm::UpdateArbitrations(unsigned int Row, bool AutoUpdate)
{

	//-- ���� ���� ��������� ��������, ���������� �������� ������ --//
	if(engine->GetSortedArbitrations().size() + 1 < Arbitrations_ActionsGrid->RowCount)
		Row = Row - 1;

	//-- �������� �������� ������ --//
	if(Row == 0)
		Row = 1;

	//-- ������� ������� --//
	ClearStringGrid( Arbitrations_ActionsGrid );

	if(engine->GetSortedArbitrations().size())
	{

		//-- ���������� ������� --//
		int row_count = 1;

		//-- ����� ������� ���������� �������� --//
		for(std::vector< int >::iterator arbitration_iterator = engine->GetSortedArbitrations().begin(); arbitration_iterator != engine->GetSortedArbitrations().end(); arbitration_iterator ++)
		{

			//-- ����� � MAP'e ������� �������� �� ��������������� ������ --//
			MArbitration::iterator map_iterator = engine->Data()->map_arbitrations.find( *arbitration_iterator );

			if(map_iterator != engine->Data()->map_arbitrations.end())
			{
				if(map_iterator->second.relevance.ToInt())
				{
					//-- ID --//
					Arbitrations_ActionsGrid->Cells[0][row_count] = map_iterator->first;

					UnicodeString end;

					//-- ���������� ������������ --//
					end = map_iterator->second.factor.Length()>Arbitrations_ActionsGrid->ColWidths[1]/8 ? end = "..." : end = "";
					Arbitrations_ActionsGrid->Cells[1][row_count] = map_iterator->second.factor.SubString(0, Arbitrations_ActionsGrid->ColWidths[1]/8) + end;

					//-- ����� --//
					if( engine->Data()->map_lines.find( map_iterator->second.line.ToInt() ) != engine->Data()->map_lines.end() )
					{
						end = engine->Data()->map_lines.find( map_iterator->second.line.ToInt() )->second.name.Length()>Arbitrations_ActionsGrid->ColWidths[2]/8 ? end = "..." : end = "";
						Arbitrations_ActionsGrid->Cells[2][row_count] = engine->Data()->map_lines.find( map_iterator->second.line.ToInt() )->second.name.SubString(0, Arbitrations_ActionsGrid->ColWidths[2]/8) + end;
					}


					//-- ����� --//
					end = map_iterator->second.time.Length()>Arbitrations_ActionsGrid->ColWidths[9]/8 ? end = "..." : end = "";
					Arbitrations_ActionsGrid->Cells[10][row_count] = map_iterator->second.time.SubString(0, Arbitrations_ActionsGrid->ColWidths[9]/8) + end;



					row_count ++;

					//-- ���������� ������ --//
					Arbitrations_ActionsGrid->RowCount ++;
				}
			}
		}


		//-- ����� ����� ������������ �������� --//
		for(std::vector< int >::iterator arbitration_iterator = engine->GetSortedArbitrations().begin(); arbitration_iterator != engine->GetSortedArbitrations().end(); arbitration_iterator ++)
		{

			//-- ����� � MAP'e ������� �������� �� ��������������� ������ --//
			MArbitration::iterator map_iterator = engine->Data()->map_arbitrations.find( *arbitration_iterator );

			if(map_iterator != engine->Data()->map_arbitrations.end())
			{
				if(!map_iterator->second.relevance.ToInt())
				{
					//-- ID --//
					Arbitrations_ActionsGrid->Cells[0][row_count] = map_iterator->first;

					UnicodeString end;

					//-- ���������� ������������ --//
					end = map_iterator->second.factor.Length()>Arbitrations_ActionsGrid->ColWidths[1]/8 ? end = "..." : end = "";
					Arbitrations_ActionsGrid->Cells[1][row_count] = map_iterator->second.factor.SubString(0, Arbitrations_ActionsGrid->ColWidths[1]/8) + end;

					//-- ����� --//
					if( engine->Data()->map_lines.find( map_iterator->second.line.ToInt() ) != engine->Data()->map_lines.end() )
					{
						end = engine->Data()->map_lines.find( map_iterator->second.line.ToInt() )->second.name.Length()>Arbitrations_ActionsGrid->ColWidths[2]/8 ? end = "..." : end = "";
						Arbitrations_ActionsGrid->Cells[2][row_count] = engine->Data()->map_lines.find( map_iterator->second.line.ToInt() )->second.name.SubString(0, Arbitrations_ActionsGrid->ColWidths[2]/8) + end;
					}


					//-- ����� --//
					end = map_iterator->second.time.Length()>Arbitrations_ActionsGrid->ColWidths[9]/8 ? end = "..." : end = "";
					Arbitrations_ActionsGrid->Cells[10][row_count] = map_iterator->second.time.SubString(0, Arbitrations_ActionsGrid->ColWidths[9]/8) + end;



					row_count ++;

					//-- ���������� ������ --//
					Arbitrations_ActionsGrid->RowCount ++;
				}
			}
		}


		//-- �������� ������ ������ --//
		Arbitrations_ActionsGrid->RowCount --;

		//-- ��������� �������� ����� --//
		if(AutoUpdate && PageControl->ActivePageIndex == 5)
		{
			//-- ������� action's --//
			Arbitrations_ActionsGrid->Row = Row;
			Arbitrations_ActionsGrid->SetFocus();
		}
	}

}



//-- ������� ���������� COLLECTIONS --//
void TMainForm::UpdateCollections(unsigned int Row, bool AutoUpdate)
{

	//-- ���� ���� ��������� ��������, ���������� �������� ������ --//
	if(engine->Data()->map_collections.size() + 1 < Collections_StringGrid->RowCount)
		Row = Row - 1;

	//-- �������� �������� ������ --//
	if(Row == 0)
		Row = 1;

	//-- ������� ������� --//
	ClearStringGrid( Collections_StringGrid );

	if(engine->Data()->map_collections.size())
	{

		//-- ���������� ������� --//
		int row_count=1;
		for(MCollection::iterator iterator_colletions = engine->Data()->map_collections.begin(); iterator_colletions != engine->Data()->map_collections.end(); iterator_colletions ++)
		{
			UnicodeString end;

			if( engine->Data()->map_sources.find( iterator_colletions->first ) != engine->Data()->map_sources.end() )
			{
				end = engine->Data()->map_sources.find( iterator_colletions->first )->second.name.Length()>Collections_StringGrid->ColWidths[0]/8 ? end = "..." : end = "";
				Collections_StringGrid->Cells[0][row_count] = engine->Data()->map_sources.find( iterator_colletions->first )->second.name.SubString(0, Collections_StringGrid->ColWidths[0]/8) + end;

            }

			end = iterator_colletions->second.Length()>Collections_StringGrid->ColWidths[1]/8 ? end = "..." : end = "";
			Collections_StringGrid->Cells[1][row_count] = iterator_colletions->second.SubString(0, Collections_StringGrid->ColWidths[1]/8) + end;


			row_count ++;

            //-- ���������� ������ --//
			Collections_StringGrid->RowCount ++;
		}


		//-- �������� ������ ������ --//
		Collections_StringGrid->RowCount --;


        //-- ��������� �������� ������ --//
		if(AutoUpdate && PageControl->ActivePageIndex == 6)
		{
			Collections_StringGrid->Row = Row;
			Collections_StringGrid->SetFocus();
		}
	}
}




