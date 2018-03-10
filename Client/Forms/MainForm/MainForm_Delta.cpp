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
   //-- установка списка изображений для анимации в трее --//
   TrayIcon->Icons = TrayImageList;

   //-- установка поискового ключа --//
   engine->SetSearchKey("call");

   //-- УСТАНОВКА ОБРАБОТЧИКОВ --//

	//-- общее --//
	engine->SetHandler("CheckAuthorization", HandlersNS::CheckAuthorization);
	engine->SetHandler("start",HandlersNS::start);
	engine->SetHandler("stop",HandlersNS::stop);
	engine->SetHandler("getState",HandlersNS::getState);
	engine->SetHandler("chain",HandlersNS::chain);

	//-- параметры --//
	engine->SetHandler("getParams", HandlersNS::getParams);
	engine->SetHandler("CheckEditParams", HandlersNS::CheckEditParams);
	engine->SetHandler("editParams", HandlersNS::editParams);

	//-- источники --//
	engine->SetHandler("getSources", HandlersNS::getSources);
	engine->SetHandler("CheckAddSource", HandlersNS::CheckAddSource);
	engine->SetHandler("CheckEditSource", HandlersNS::CheckEditSource);
	engine->SetHandler("CheckDeleteSource", HandlersNS::CheckDeleteSource);
	engine->SetHandler("addSource", HandlersNS::addSource);
	engine->SetHandler("editSource", HandlersNS::editSource);
	engine->SetHandler("deleteSource", HandlersNS::deleteSource);

	//-- валюты --//
	engine->SetHandler("getCurrencys", HandlersNS::getCurrencys);
	engine->SetHandler("CheckAddCurrency", HandlersNS::CheckAddCurrency);
	engine->SetHandler("CheckEditCurrency", HandlersNS::CheckEditCurrency);
	engine->SetHandler("CheckDeleteCurrency", HandlersNS::CheckDeleteCurrency);
	engine->SetHandler("addCurrency", HandlersNS::addCurrency);
	engine->SetHandler("editCurrency", HandlersNS::editCurrency);
	engine->SetHandler("deleteCurrency", HandlersNS::deleteCurrency);

	//-- линии --//
	engine->SetHandler("getLines", HandlersNS::getLines);
	engine->SetHandler("CheckAddLine", HandlersNS::CheckAddLine);
	engine->SetHandler("CheckEditLine", HandlersNS::CheckEditLine);
	engine->SetHandler("CheckDeleteLine", HandlersNS::CheckDeleteLine);
	engine->SetHandler("addLine", HandlersNS::addLine);
	engine->SetHandler("editLine", HandlersNS::editLine);
	engine->SetHandler("deleteLine", HandlersNS::deleteLine);

	//-- коррекции --//
	engine->SetHandler("getCorrections", HandlersNS::getCorrections);
	engine->SetHandler("CheckAddCorrection", HandlersNS::CheckAddCorrection);
	engine->SetHandler("CheckEditCorrection", HandlersNS::CheckEditCorrection);
	engine->SetHandler("CheckDeleteCorrection", HandlersNS::CheckDeleteCorrection);
	engine->SetHandler("addCorrection", HandlersNS::addCorrection);
	engine->SetHandler("editCorrection", HandlersNS::editCorrection);
	engine->SetHandler("deleteCorrection", HandlersNS::deleteCorrection);

	//-- сбор данных --//
    engine->SetHandler("collect",HandlersNS::collect);
	engine->SetHandler("collected",HandlersNS::collected);
	engine->SetHandler("processSource",HandlersNS::processSource);
}



//---------------------------------------------------------//
//------------ ОБРАБОТЧИКИ СТАНДАРТНЫХ СОБЫТИЙ ------------//
//---------------------------------------------------------//

//-- ФУНКЦИЯ СОЗДАНИЯ ФОРМЫ --//
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	//-- загрузка настроек программы из файла --//
	engine->LoadConfig();

	//-- задание версии программы --//
	MainForm->Caption = "Delta " + interface_conf.version;

    //-- задание темы --//
	SetThemeProgram();

	//-- задание минимального размера главной формы --//
	MainForm->Constraints->MinWidth = interface_conf.min_size_width;
	MainForm->Constraints->MinHeight = interface_conf.min_size_height;

	//-- задание размера главной формы --//
	MainForm->Width = engine->Config()->MainFormWidth;
	MainForm->Height = engine->Config()->MainFormHeight;


    //-- установка стандартной вкладки интерфейса --//
   PageControl->TabIndex = 0;

   //-- запрет доступа к интерфейсу без авторизации на сервере --//
   PageControl->Enabled = false;
   ContrServButton->Enabled = false;


   //-- УСТАНОВКА СТАНДАРТНЫХ НАДПИСЕЙ ТАБЛИЦ --//
   DefaultSourcesGrid();
   DefaultCurrencysGrid();
   DefaultLinesGrid();
   DefaultCorrectionsGrid();
   DefaultArbitrationsGrid();
   DefaultCollectionsGrid();


	//-- подключение к серверу при запуске --//
	engine->Connecting(engine->Config()->HostServer, engine->Config()->PortServer);
}

//-- ФУНКЦИЯ ЗАКРЫТИЯ ФОРМЫ --//
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	//-- определение, нужно ли сворачивать в трей --//
	if(interface_conf.tray_minimize)
	{
		if(engine->Config()->TrayMinimize)
		{
            //-- прерываем команду закрытия --//
			Action=caNone;

			//-- меняем состояние индикатора свёрнутого режима --//
			interface_conf.tray_minimize_state = true;

			//-- отображаем иконку в трее --//
			TrayIcon->Visible = true;

			//-- скрываем программу --//
			Application->ShowMainForm = false;
			ShowWindow(Handle,SW_HIDE);

			//-- скрываем кнопку с TaskBar'а --//
			ShowWindow(Application->Handle,SW_HIDE);
        }
	}

    //-- запись параметров размера окна главной формы --//
	engine->Config()->MainFormWidth = MainForm->Width;
	engine->Config()->MainFormHeight = MainForm->Height;


	//-- запись настроек программы в файл --//
	if(!engine->NeedToRestart())
		engine->SaveConfig();
}

//-- ФУНКЦИЯ ОБРАБОТКИ КЛАВИШ --//
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	//-- если нажата клавиша "F12" --//
	if(Key == 123)
	{
		//-- проверка активности соединения --//
		if(!engine->ConnectState())
			ShowMessage("You are not connected to the server.");
		else
		{
			//-- вывод окна "Test" --//
			TestForm->ShowModal();
		}
		return;
	}

	//-- если нажата клавиша "F11" --//
	if(Key == 122)
	{
		//-- вывод окна "Debug" --//
		DebugForm->ShowModal();

		return;
	}
}

//-- ФУНКЦИЯ ПОКАЗА ГЛАВНОЙ ФОРМЫ --//
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	//-- перезапуск программы при необходимости --//
	if(engine->NeedToRestart())
		Close();

	//-- установка значений последнего обновления данных --//
	UpdateLastCollected(false);

	//-- установка параметров элементов --//
	SetParamElements();
}


//-- ФУНКЦИЯ ИЗМЕНЕНИЯ РАЗМЕРОВ ЭЛЕМЕНТОВ ПРИ ИЗМЕНЕНИИ РАЗМЕРОВ --//
void __fastcall TMainForm::FormResize(TObject *Sender)
{
	SetParamElements();
}


//-- ФУНКЦИЯ ПЕРЕКЛЮЧЕНИЯ ВКЛАДОК --//
void __fastcall TMainForm::PageControlChange(TObject *Sender)
{
	SetParamElements();
}



//---------------------------------------------------------//
//------------- ОБРАБОТЧИКИ СОБЫТИЙ ЭЛЕМЕНТОВ -------------//
//---------------------------------------------------------//

//-- ФУНКЦИЯ ПОКАЗА ИНФОРМАЦИИ "ABOUT" --//
void __fastcall TMainForm::AboutButton_OneClick(TObject *Sender)
{
	//-- вывод окна "About" --//
	AboutForm->ShowModal();
}

//-- ФУНКЦИЯ ВЫХОДА ИЗ ПРОГРАММЫ --//
void __fastcall TMainForm::ExitButton_OneClick(TObject *Sender)
{
	//-- отключаем сворачивание в трей --//
	interface_conf.tray_minimize = false;

	//-- закрытие программы --//
	Close();
}

//-- ФУНКЦИЯ НАЖАТИЯ НА ЗНАЧОК В ТРЕЕ --//
void __fastcall TMainForm::TrayIcon_OneClick(TObject *Sender)
{
	//-- меняем состояние индикатора свёрнутого режима --//
	interface_conf.tray_minimize_state = false;

	//-- скрываем иконку в трее --//
	TrayIcon->Visible = false;

	Application->ShowMainForm = true;

	//-- показываем программу --//
	ShowWindow(Handle,SW_SHOW);

	//-- показываем кнопку в TaskBar'е --//
	ShowWindow(Application->Handle,SW_SHOW);
}

//-- ФУНКЦИЯ ОПОВЕЩЕНИЯ --//
void TMainForm::ShowHint(const UnicodeString Text)
{
	if(MainForm->engine->Config()->NotificationsHint)
	{
        if(interface_conf.tray_minimize_state)
		{
			//-- текст подсказки --//
			TrayIcon->BalloonHint = Text;

			//-- вывод подсказки --//
			TrayIcon->ShowBalloonHint();
		}

		//-- воспроизведение звукового сигнала --//
        Beep(1000, 100);
	}
}


//-- ФУНКЦИЯ ВЫДЕЛЕНИЯ АКТИВНОЙ СТРОКИ LINES NAMES GRID --//
void __fastcall TMainForm::Lines_NamesStringGridSelectCell(TObject *Sender, int ACol,
		  int ARow, bool &CanSelect)
{
    //-- проверка на необходимость обновления таблицы --//
	if(Lines_NamesStringGrid->RowCount == engine->Data()->map_lines.size() + 1)
	{
        //-- обновление таблицы --//
		UpdateLines(ARow);
	}
}


//-- ФУНКЦИЯ ПОКАЗА ФОРМЫ НАСТРОЕК --//
void __fastcall TMainForm::Setting_OneClick(TObject *Sender)
{
	//-- вывод окна "Setting" --//
	SettingForm->ShowModal();
}

//-- ФУНКЦИЯ ВЫВОДА ФОРМЫ ДОБАВЛЕНИЯ ИСТОЧНИКА --//
void __fastcall TMainForm::Source_AddButton_OneClick(TObject *Sender)
{
	//-- вывод окна "AddSources" --//
	AddFormSources->ShowModal();
}

//-- ФУНКЦИЯ УДАЛЕНИЯ ИСТОЧНИКА--//
void __fastcall TMainForm::Source_DeleteButton_OneClick(TObject *Sender)
{
	//-- ФОРМИРОВАНИЕ СТРОКИ УДАЛЕНИЯ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
	UnicodeString param = "\"id\":\"" + UnicodeString(Sources_StringGrid->Cells[0][Sources_StringGrid->Row].ToInt()) + "\"";

	//-- отправка запроса удаления источника на сервер --//
	engine->Send("deleteSource", param, "CheckDeleteSource");
}

//-- ФУНКЦИЯ ВЫВОДА ФОРМЫ РЕДАКТИРОВАНИЯ ИСТОЧНИКА  --//
void __fastcall TMainForm::Sources_EditButton_OneClick(TObject *Sender)
{
	//-- вывод окна "EditSources" --//
	EditFormSources->ShowModal();
}

//-- ФУНКЦИЯ ВЫВОДА ФОРМЫ АВТОРИЗАЦИИ --//
void __fastcall TMainForm::Login_OneClick(TObject *Sender)
{
	//-- вывод окна "Athorization" --//
	AuthForm->ShowModal();
}

//-- ФУНКЦИЯ ВЫВОДА ФОРМЫ ДОБАВЛЕНИЯ ВАЛЮТЫ --//
void __fastcall TMainForm::Currencys_AddButton_OneClick(TObject *Sender)
{
	//-- вывод окна "AddCurrencys" --//
	AddFormCurrencys->ShowModal();
}

//-- ФУНКЦИЯ ВЫВОДА ФОРМЫ ИЗМЕНЕНИЯ ВАЛЮТЫ --//
void __fastcall TMainForm::Currencys_EditButton_OneClick(TObject *Sender)
{
	//-- вывод окна "AddCurrencys" --//
	EditFormCurrencys->ShowModal();
}


//-- ФУНКЦИЯ ВЫВОДА ФОРМЫ ДОБАВЛЕНИЯ КОРРЕКЦИИ --//
void __fastcall TMainForm::Corrections_AddButton_OneClick(TObject *Sender)
{
	//-- вывод окна "AddCorrections" --//
	AddFormCorrections->ShowModal();
}

//-- ФУНКЦИЯ УДАЛЕНИЯ ВАЛЮТЫ --//
void __fastcall TMainForm::Currencys_DeleteButton_OneClick(TObject *Sender)
{
	//-- ФОРМИРОВАНИЕ СТРОКИ УДАЛЕНИЯ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
	UnicodeString param = "\"id\":\"" + UnicodeString(Currencys_StringGrid->Cells[0][Currencys_StringGrid->Row].ToInt()) + "\"";

	//-- отправка запроса удаления валюты на сервер --//
	engine->Send("deleteCurrency", param, "CheckDeleteCurrency");
}


//-- ФУНКЦИЯ УДАЛЕНИЯ ЛИНИИ --//
void __fastcall TMainForm::Lines_DeleteButton_OneClick(TObject *Sender)
{
	//-- ФОРМИРОВАНИЕ СТРОКИ УДАЛЕНИЯ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
	UnicodeString param = "\"id\":\"" + UnicodeString(Lines_NamesStringGrid->Cells[0][Lines_NamesStringGrid->Row].ToInt()) + "\"";

	//-- отправка запроса удаления линии на сервер --//
	engine->Send("deleteLine", param, "CheckDeleteCurrency");
}


//-- ФУНКЦИЯ УДАЛЕНИЯ КОРРЕКЦИИ --//
void __fastcall TMainForm::Corrections_DeleteButton_OneClick(TObject *Sender)
{
	//-- ФОРМИРОВАНИЕ СТРОКИ УДАЛЕНИЯ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
	UnicodeString param = "\"id\":\"" + UnicodeString(Corrections_StringGrid->Cells[0][Corrections_StringGrid->Row].ToInt()) + "\"";

	//-- отправка запроса удаления линии на сервер --//
	engine->Send("deleteCorrection", param, "CheckDeleteCorrection");
}



//-- ФУНКЦИЯ ДОБАВЛЕНИЯ ЛИНИИ --//
void __fastcall TMainForm::Lines_AddButton_OneClick(TObject *Sender)
{
	//-- вывод окна "AddLines" --//
	AddFormLines->ShowModal();
}


//-- ФУНКЦИЯ ИЗМЕНЕНИЯ ЛИНИИ --//
void __fastcall TMainForm::Lines_EditButton_OneClick(TObject *Sender)
{
	//-- вывод окна "EditLines" --//
	EditFormLines->ShowModal();
}


//-- ФУНКЦИЯ ИЗМЕНЕНИЯ КОРРЕКЦИИ --//
void __fastcall TMainForm::Corrections_EditButton_OneClick(TObject *Sender)
{
	//-- вывод окна "EditCorrection" --//
	EditFormCorrections->ShowModal();
}



//-- ФУНКЦИЯ ИЗМЕНЕНИЯ ПАРАМЕТРОВ --//
void __fastcall TMainForm::Parameters_SaveButton_OneClick(TObject *Sender)
{
	//-- ФОРМИРОВАНИЕ СТРОКИ РЕДАКТИРОВАНИЯ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//

	UnicodeString param;


	//-- коэфициент --//
	//-- ************************************ --//
	if(!Parameters_CoefficientEdit->Text.IsEmpty() && Parameters_CoefficientEdit->Text != engine->Data()->params.factor)
	{
        //-- добавление запятой между параметрами --//
		if(!param.IsEmpty())
			param = param + ",";

		param = param + "\"factor\":" + engine->FloatWithDots( Parameters_CoefficientEdit->Text ) ;
	}
	//-- ************************************ --//



	//-- длинна цепочки --//
	//-- ************************************ --//
	if(!Parameters_MaxLengthEdit->Text.IsEmpty() && Parameters_MaxLengthEdit->Text != engine->Data()->params.maxChainLen)
	{
        //-- добавление запятой между параметрами --//
		if(!param.IsEmpty())
			param = param + ",";

		param = param + "\"maxChainLen\":" + engine->FloatWithDots( Parameters_MaxLengthEdit->Text );
	}
	//-- ************************************ --//


	//-- отправка запроса редактирования параметров на сервер --//
	MainForm->engine->Send("editParams", param, "CheckEditParams");



    //-- отправка запроса на остановку сервера --//
	engine->Send("stop", "stop");

	//-- отправка запроса на запуск сервера --//
	engine->Send("start", "start");



    //-- удаление всех операций --//
	engine->Data()->map_arbitrations.clear();

	//-- обновление сортированного списка --//
	engine->SortArbitrations(engine->Config()->SortArbitrations);

	//-- обновление таблицы --//
	UpdateArbitrations(Arbitrations_ActionsGrid->Row, false);
}


//-- ФУНКЦИЯ ЗАПУСКА СЕРВЕРА --//
void __fastcall TMainForm::StartButton_OneClick(TObject *Sender)
{
	//-- отправка запроса на запуск сервера --//
	engine->Send("start", "start");
}



//-- ФУНКЦИЯ ОСТАНОВКИ СЕРВЕРА --//
void __fastcall TMainForm::StopButton_OneClick(TObject *Sender)
{
	//-- отправка запроса на остановку сервера --//
	engine->Send("stop", "stop");
}


//-- ФУНКЦИЯ ПЕРЕЗАПУСКА СЕРВЕРА --//
void __fastcall TMainForm::RestartButton_OneClick(TObject *Sender)
{
	//-- отправка запроса на остановку сервера --//
	engine->Send("stop", "stop");

	//-- отправка запроса на запуск сервера --//
	engine->Send("start", "start");
}


//-- ФУНКЦИЯ ВКЛЮЧЕНИЯ ВСЕХ ИСТОЧНИКОВ --//
void __fastcall TMainForm::Sources_EnableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Sources_StringGrid->Selection.Top ; i != Sources_StringGrid->Selection.Bottom + 1; i ++)
	{
        //-- ФОРМИРОВАНИЕ СТРОКИ ВКЛЮЧЕНИЯ ИСТОЧНИКОВ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Sources_StringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":1";

		//-- отправка запроса включения на сервер --//
		MainForm->engine->Send("editSource", param, "NULL");
	}
}


//-- ФУНКЦИЯ ВЫКЛЮЧЕНИЯ ВСЕХ ИСТОЧНИКОВ --//
void __fastcall TMainForm::Sources_DisableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Sources_StringGrid->Selection.Top ; i != Sources_StringGrid->Selection.Bottom + 1; i ++)
	{
		//-- ФОРМИРОВАНИЕ СТРОКИ ВКЛЮЧЕНИЯ ИСТОЧНИКОВ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Sources_StringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":0";

		//-- отправка запроса включения на сервер --//
		MainForm->engine->Send("editSource", param, "NULL");
	}
}


//-- ФУНКЦИЯ ВКЛЮЧЕНИЯ ВСЕХ ВАЛЮТ --//
void __fastcall TMainForm::Currencys_EnableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Currencys_StringGrid->Selection.Top ; i != Currencys_StringGrid->Selection.Bottom + 1; i ++)
	{
		//-- ФОРМИРОВАНИЕ СТРОКИ ВКЛЮЧЕНИЯ ИСТОЧНИКОВ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Currencys_StringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":1";

		//-- отправка запроса включения на сервер --//
		MainForm->engine->Send("editCurrency", param, "NULL");
	}
}


//-- ФУНКЦИЯ ВЫКЛЮЧЕНИЯ ВСЕХ ВАЛЮТ --//
void __fastcall TMainForm::Currencys_DisableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Currencys_StringGrid->Selection.Top ; i != Currencys_StringGrid->Selection.Bottom + 1; i ++)
	{
		//-- ФОРМИРОВАНИЕ СТРОКИ ВКЛЮЧЕНИЯ ИСТОЧНИКОВ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Currencys_StringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":0";

		//-- отправка запроса включения на сервер --//
		MainForm->engine->Send("editCurrency", param, "NULL");
	}
}


//-- ФУНКЦИЯ ВКЛЮЧЕНИЯ ВСЕХ ЛИНИЙ --//
void __fastcall TMainForm::Lines_EnableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Lines_NamesStringGrid->Selection.Top ; i != Lines_NamesStringGrid->Selection.Bottom + 1; i ++)
	{
		//-- ФОРМИРОВАНИЕ СТРОКИ ВКЛЮЧЕНИЯ ИСТОЧНИКОВ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Lines_NamesStringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":1";

		//-- отправка запроса включения на сервер --//
		MainForm->engine->Send("editLine", param, "NULL");
	}
}


//-- ФУНКЦИЯ ВЫКЛЮЧЕНИЯ ВСЕХ ЛИНИЙ --//
void __fastcall TMainForm::Lines_DisableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Lines_NamesStringGrid->Selection.Top ; i != Lines_NamesStringGrid->Selection.Bottom + 1; i ++)
	{
		//-- ФОРМИРОВАНИЕ СТРОКИ ВКЛЮЧЕНИЯ ИСТОЧНИКОВ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Lines_NamesStringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":0";

		//-- отправка запроса включения на сервер --//
		MainForm->engine->Send("editLine", param, "NULL");
	}
}



//-- ФУНКЦИЯ ВКЛЮЧЕНИЯ ВСЕХ КОРРЕКЦИЙ --//
void __fastcall TMainForm::Corrections_EnableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Corrections_StringGrid->Selection.Top ; i != Corrections_StringGrid->Selection.Bottom + 1; i ++)
	{
		//-- ФОРМИРОВАНИЕ СТРОКИ ВКЛЮЧЕНИЯ ИСТОЧНИКОВ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Corrections_StringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":1";

		//-- отправка запроса включения на сервер --//
		MainForm->engine->Send("editCorrection", param, "NULL");
	}
}


//-- ФУНКЦИЯ ВЫКЛЮЧЕНИЯ ВСЕХ КОРРЕКЦИЙ --//
void __fastcall TMainForm::Corrections_DisableAllButton_OneClick(TObject *Sender)
{
	for(unsigned int i = Corrections_StringGrid->Selection.Top ; i != Corrections_StringGrid->Selection.Bottom + 1; i ++)
	{
		//-- ФОРМИРОВАНИЕ СТРОКИ ВКЛЮЧЕНИЯ ИСТОЧНИКОВ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
		UnicodeString param = "\"id\":\"" + UnicodeString( Corrections_StringGrid->Cells[0][i] ) + "\"" + ",\"enabled\":0";

		//-- отправка запроса включения на сервер --//
		MainForm->engine->Send("editCorrection", param, "NULL");
	}
}


//-- ФУНКЦИЯ ОТКРЫТИЯ ФОРМЫ РЕДАКТИРОВАНИЯ ИСТОЧНИКОВ ПО ДВОЙНОМУ КЛИКУ --//
void __fastcall TMainForm::Sources_StringGridDblClick(TObject *Sender)
{
	//-- вывод окна "EditSources" --//
	if(!Sources_StringGrid->Cells[0][1].IsEmpty())
		EditFormSources->ShowModal();
}


//-- ФУНКЦИЯ ОТКРЫТИЯ ФОРМЫ РЕДАКТИРОВАНИЯ ВАЛЮТ ПО ДВОЙНОМУ КЛИКУ --//
void __fastcall TMainForm::Currencys_StringGridDblClick(TObject *Sender)
{
	//-- вывод окна "EditCurrencys" --//
	if(!Currencys_StringGrid->Cells[0][1].IsEmpty())
		EditFormCurrencys->ShowModal();
}



//-- ФУНКЦИЯ ОТКРЫТИЯ ФОРМЫ РЕДАКТИРОВАНИЯ ЛИНИЙ ПО ДВОЙНОМУ КЛИКУ --//
void __fastcall TMainForm::Lines_NamesStringGridDblClick(TObject *Sender)
{
	//-- вывод окна "EditLines" --//
	if(!Lines_NamesStringGrid->Cells[0][1].IsEmpty())
		EditFormLines->ShowModal();
}


//-- ФУНКЦИЯ ОТКРЫТИЯ ФОРМЫ РЕДАКТИРОВАНИЯ КОРРЕКЦИЙ ПО ДВОЙНОМУ КЛИКУ --//
void __fastcall TMainForm::Corrections_StringGridDblClick(TObject *Sender)
{
	//-- вывод окна "EditCorrections" --//
	if(!Corrections_StringGrid->Cells[0][1].IsEmpty())
		EditFormCorrections->ShowModal();
}


//-- ФУНКЦИЯ ИЗМЕНЕНИЯ ТИПА СОРТИРОВКИ ИСТОЧНИКОВ ПРИ КЛИКЕ ПО НАЗВАНИЮ КОЛОНКИ --//
void __fastcall TMainForm::Sources_StringGridFixedCellClick(TObject *Sender, int ACol,
		  int ARow)
{

	//-- запоминание типа текущей сортировки --//
	unsigned int TypeSort = engine->Config()->SortSources;

	//-- определение типа сортировки --//
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


	//-- изменение параметра сортировки от А до Я --//
	if(TypeSort == engine->Config()->SortSources)
		engine->Config()->SortSourcesInd = !engine->Config()->SortSourcesInd;
	else
		engine->Config()->SortSourcesInd = true;

	//-- изменение надписей в таблице --//
	DefaultSourcesGrid();

	//-- сортировка по указатному типу --//
	engine->SortSources(engine->Config()->SortSources, engine->Config()->SortSourcesInd);

	//-- обновление таблицы --//
	UpdateSources();
}


//-- ФУНКЦИЯ ИЗМЕНЕНИЯ ТИПА СОРТИРОВКИ ВАЛЮТ ПРИ КЛИКЕ ПО НАЗВАНИЮ КОЛОНКИ --//
void __fastcall TMainForm::Currencys_StringGridFixedCellClick(TObject *Sender, int ACol,
		  int ARow)
{

	//-- запоминание типа текущей сортировки --//
	unsigned int TypeSort = engine->Config()->SortCurrencys;

	//-- определение типа сортировки --//
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


	//-- изменение параметра сортировки от А до Я --//
	if(TypeSort == engine->Config()->SortCurrencys)
		engine->Config()->SortCurrencysInd = !engine->Config()->SortCurrencysInd;
	else
		engine->Config()->SortCurrencysInd = true;


	//-- изменение надписей в таблице --//
	DefaultCurrencysGrid();

    //-- сортировка по заданому типу --//
	engine->SortCurrencys(engine->Config()->SortCurrencys, engine->Config()->SortCurrencysInd);

    //-- обновление таблицы --//
	UpdateCurrencys();
}


//-- ФУНКЦИЯ ИЗМЕНЕНИЯ ТИПА СОРТИРОВКИ ЛИНИЙ ПРИ КЛИКЕ ПО НАЗВАНИЮ КОЛОНКИ --//
void __fastcall TMainForm::Lines_NamesStringGridFixedCellClick(TObject *Sender, int ACol,
		  int ARow)
{
    //-- запоминание типа текущей сортировки --//
	unsigned int TypeSort = engine->Config()->SortLines;

	//-- определение типа сортировки --//
	if(ACol == 0)
		engine->Config()->SortLines = eID;

	if(ACol == 1)
		engine->Config()->SortLines = eNAME;

	if(ACol == 2)
		engine->Config()->SortLines = eENABLED;


	//-- изменение параметра сортировки от А до Я --//
	if(TypeSort == engine->Config()->SortLines)
		engine->Config()->SortLinesInd = !engine->Config()->SortLinesInd;
	else
    	engine->Config()->SortLinesInd = true;


	//-- изменение надписей в таблице --//
	DefaultLinesGrid();

	//-- сортировка по заданому типу --//
	engine->SortLines(engine->Config()->SortLines, engine->Config()->SortLinesInd);


	//-- обновление таблицы --//
	UpdateLines();
}


//-- ФУНКЦИЯ ИЗМЕНЕНИЯ ТИПА СОРТИРОВКИ КОРРЕКЦИЙ ПРИ КЛИКЕ ПО НАЗВАНИЮ КОЛОНКИ --//
void __fastcall TMainForm::Corrections_StringGridFixedCellClick(TObject *Sender, int ACol,
		  int ARow)
{
	//-- запоминание типа текущей сортировки --//
	unsigned int TypeSort = engine->Config()->SortCorrections;

	//-- определение типа сортировки --//
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


	//-- изменение параметра сортировки от А до Я --//
	if(TypeSort == engine->Config()->SortCorrections)
		engine->Config()->SortCorrectionsInd = !engine->Config()->SortCorrectionsInd;
	else
		engine->Config()->SortCorrectionsInd = true;


	//-- изменение надписей в таблице --//
	DefaultCorrectionsGrid();

    //-- сортировка по заданому типу --//
	engine->SortCorrections(engine->Config()->SortCorrections, engine->Config()->SortCorrectionsInd);

	//-- обновление таблицы --//
	UpdateCorrections();
}


//-- ФУНКЦИЯ ИЗМЕНЕНИЯ ТИПА СОРТИРОВКИ АРБИТРАЖЕЙ ПРИ КЛИКЕ ПО НАЗВАНИЮ КОЛОНКИ --//
void __fastcall TMainForm::Arbitrations_ActionsGridFixedCellClick(TObject *Sender,
		  int ACol, int ARow)
{
    //-- запоминание типа текущей сортировки --//
	unsigned int TypeSort = engine->Config()->SortArbitrations;

	//-- определение типа сортировки --//
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

		//-- изменение параметра сортировки от А до Я --//
		if(TypeSort == engine->Config()->SortArbitrations)
			engine->Config()->SortArbitrationsInd = !engine->Config()->SortArbitrationsInd;
		else
			engine->Config()->SortArbitrationsInd = true;


		//-- изменение надписей в таблице --//
		DefaultArbitrationsGrid();

		//-- сортировка по заданому типу --//
		engine->SortArbitrations(engine->Config()->SortArbitrations, engine->Config()->SortArbitrationsInd);

		//-- обновление таблицы --//
		UpdateArbitrations();
	}
}




//-- ФУНКЦИЯ ЗАДАНИЯ ЦВЕТА ЯЧЕЕК АРБИТРАЖЕЙ --//
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
						//-- выбор цвета ячейки и закрашивание АКТИВНЫХ НЕ ВЫДЕЛЕНЫХ ячеек --//
						Arbitrations_ActionsGrid->Canvas->Brush->Color = clTeal;
						Arbitrations_ActionsGrid->Canvas->FillRect(Rect);

						//-- выбор цвета текста на закрашенные ячейки--//
						Arbitrations_ActionsGrid->Canvas->Font->Color = clBlack;
						Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2, Arbitrations_ActionsGrid->Cells[ACol][ARow]);
					}
					else
					{
						//-- выбор цвета ячейки и закрашивание АКТИВНЫХ ВЫДЕЛЕНЫХ ячеек --//
						Arbitrations_ActionsGrid->Canvas->Brush->Color = clLime;
						Arbitrations_ActionsGrid->Canvas->FillRect(Rect);

						//-- выбор цвета текста на закрашенные ячейки--//
						Arbitrations_ActionsGrid->Canvas->Font->Color = clBlack;
						Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2, Arbitrations_ActionsGrid->Cells[ACol][ARow]);
					}
				}
				else
				{
					if(Arbitrations_ActionsGrid->Row != ARow)
					{
						//-- выбор цвета ячейки и закрашивание НЕАКТИВНЫХ НЕ ВЫДЕЛЕНЫХ ячеек --//
						Arbitrations_ActionsGrid->Canvas->Brush->Color = clMaroon;
						Arbitrations_ActionsGrid->Canvas->FillRect(Rect);

						//-- выбор цвета текста на закрашенные ячейки--//
						Arbitrations_ActionsGrid->Canvas->Font->Color = clWhite;
						Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2, Arbitrations_ActionsGrid->Cells[ACol][ARow]);
					}
					else
					{
                        //-- выбор цвета ячейки и закрашивание НЕАКТИВНЫХ ВЫДЕЛЕНЫХ ячеек --//
						Arbitrations_ActionsGrid->Canvas->Brush->Color = clRed;
						Arbitrations_ActionsGrid->Canvas->FillRect(Rect);

						//-- выбор цвета текста на закрашенные ячейки--//
						Arbitrations_ActionsGrid->Canvas->Font->Color = clWhite;
						Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2, Arbitrations_ActionsGrid->Cells[ACol][ARow]);
                    }
				}



				//--------------------------------------//
				//---------- ВЫВОД ОПЕРАЦИЙ ------------//
				//--------------------------------------//

				if( (ACol == 2 || ACol == 3 || ACol == 4 || ACol == 5 || ACol == 6 || ACol == 7 || ACol == 8 || ACol == 9) )
				{
					MArbitration::iterator map_iterator = engine->Data()->map_arbitrations.find( Arbitrations_ActionsGrid->Cells[0][ARow].ToInt() );

					if(map_iterator != engine->Data()->map_arbitrations.end())
					{
						if(map_iterator->second.operations.size())
						{

							//-- начальные координаты для вывода строк в ячейке --//
							unsigned int coord = 0;


							UnicodeString end;

							for(std::vector< SOperation >::iterator iterator_operations = map_iterator->second.operations.begin(); iterator_operations != map_iterator->second.operations.end(); iterator_operations ++)
							{
								//-- задание размера строк --//
								Arbitrations_ActionsGrid->RowHeights[ARow] = map_iterator->second.operations.size() * 22;


								if(ACol == 3)
								{
                                    //-- исходящая валюта --//
									if( engine->Data()->map_currencys.find( iterator_operations->currOut.ToInt() ) != engine->Data()->map_currencys.end() )
									{
										end = engine->Data()->map_currencys.find( iterator_operations->currOut.ToInt() )->second.name.Length()>Arbitrations_ActionsGrid->ColWidths[3]/8 ? end = "..." : end = "";
										Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2 + coord, engine->Data()->map_currencys.find( iterator_operations->currOut.ToInt() )->second.name.SubString(0, Arbitrations_ActionsGrid->ColWidths[3]/8) + end);
									}
								}


								if(ACol == 4)
								{
									//-- входящая валюта --//
									if( engine->Data()->map_currencys.find( iterator_operations->currIn.ToInt() ) != engine->Data()->map_currencys.end() )
									{
										end = engine->Data()->map_currencys.find( iterator_operations->currIn.ToInt() )->second.name.Length()>Arbitrations_ActionsGrid->ColWidths[4]/8 ? end = "..." : end = "";
										Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2 + coord, engine->Data()->map_currencys.find( iterator_operations->currIn.ToInt() )->second.name.SubString(0, Arbitrations_ActionsGrid->ColWidths[4]/8) + end);
									}
								}


								if(ACol == 5)
								{
									//-- источник --//
									if( engine->Data()->map_sources.find( iterator_operations->idSource.ToInt() ) != engine->Data()->map_sources.end() )
									{
										Arbitrations_ActionsGrid->Canvas->Font->Color = clBlack;

										end = engine->Data()->map_sources.find( iterator_operations->idSource.ToInt() )->second.name.Length()>Arbitrations_ActionsGrid->ColWidths[5]/8 ? end = "..." : end = "";
										Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2 + coord, engine->Data()->map_sources.find( iterator_operations->idSource.ToInt() )->second.name.SubString(0, Arbitrations_ActionsGrid->ColWidths[5]/8) + end);
									}
								}

								if(ACol == 6)
								{
									//-- комментарии --//
									if( engine->Data()->map_sources.find( iterator_operations->idSource.ToInt() ) != engine->Data()->map_sources.end() )
									{
										Arbitrations_ActionsGrid->Canvas->Font->Color = clBlack;

										end = engine->Data()->map_sources.find( iterator_operations->idSource.ToInt() )->second.notes.Length()>Arbitrations_ActionsGrid->ColWidths[6]/8 ? end = "..." : end = "";
										Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2 + coord, engine->Data()->map_sources.find( iterator_operations->idSource.ToInt() )->second.notes.SubString(0, Arbitrations_ActionsGrid->ColWidths[6]/8) + end);
									}
								}


								if(ACol == 7)
								{
									//-- прямой курс обмена --//
									end = iterator_operations->rate.Length()>Arbitrations_ActionsGrid->ColWidths[6]/8 ? end = "..." : end = "";
									Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2 + coord, iterator_operations->rate.SubString(0, Arbitrations_ActionsGrid->ColWidths[6]/8) + end);
								}


								if(ACol == 8)
								{
									//-- курс обмена с комиссией --//
									end = iterator_operations->realRate.Length()>Arbitrations_ActionsGrid->ColWidths[7]/8 ? end = "..." : end = "";
									Arbitrations_ActionsGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2 + coord, iterator_operations->realRate.SubString(0, Arbitrations_ActionsGrid->ColWidths[7]/8) + end);
								}

								if(ACol == 9)
								{
									//-- доступная к обмену сумма входящей валюты --//
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


//-- ФУНКЦИЯ ВЫДЕЛЕНИЯ КЛЕТОК В ТАБЛИЦЕ ИСТОЧНИКОВ ПРИ ВЫВОДЕ --//
void __fastcall TMainForm::Sources_StringGridDrawCell(TObject *Sender, int ACol, int ARow,
		  TRect &Rect, TGridDrawState State)
{
	/*
	if((ACol == 2 || ACol == 3) && ARow > 0)
	{
		//-- выбор цвета ячейки и закрашивание АКТИВНЫХ НЕ ВЫДЕЛЕНЫХ ячеек --//
		Sources_StringGrid->Canvas->Brush->Color = clWhite;
		Sources_StringGrid->Canvas->FillRect(Rect);

		//-- выбор цвета текста на закрашенные ячейки--//
		Sources_StringGrid->Canvas->Font->Color = clBlue;
		Sources_StringGrid->Canvas->TextOutW(Rect.Left + 2, Rect.Top + 2, Sources_StringGrid->Cells[ACol][ARow]);
	}
    */
}


//-- ФУНКЦИЯ ПЕРЕХОДА ПО URL ИСТОЧНИКА --//
void __fastcall TMainForm::Sources_StringGridSelectCell(TObject *Sender, int ACol,
		  int ARow, bool &CanSelect)
{
	//-- переход по url --//

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


//-- ФУНКЦИЯ ОЧИСТКИ АРБИТРАЖНЫХ ОПЕРАЦИЙ --//
void __fastcall TMainForm::Arbitrations_ClearButton_OneClick(TObject *Sender)
{
	//-- удаление всех операций --//
	engine->Data()->map_arbitrations.clear();

	//-- обновление сортированного списка --//
	engine->SortArbitrations(engine->Config()->SortArbitrations);

	//-- обновление таблицы --//
	UpdateArbitrations(Arbitrations_ActionsGrid->Row, false);
}





//---------------------------------------------------------//
//------------- ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ КЛАССА -------------//
//---------------------------------------------------------//

//-- ФУНКЦИЯ УСТАНОВКИ ТЕМЫ ОФОРМЛЕНИЯ --//
void TMainForm::SetThemeProgram()
{
	//-- задание темы оформления --//
	if(MainForm->engine->Config()->Theme)
		TStyleManager::TrySetStyle("Light");
	else
		TStyleManager::TrySetStyle("Charcoal Dark Slate");
}


//-- ФУНКЦИЯ УСТАНОВКИ ВСЕХ ПАРАМЕТРОВ ЭЛЕМЕНТОВ (РАЗМЕР и т.д.) --//
void TMainForm::SetParamElements()
{
	unsigned int size_scroll = 16;

	//-- если активная вкладка - Sources, изменяем параметры элементов --//
	if(PageControl->ActivePageIndex == 0)
	{
		//-- задание размера таблицы --//
		Sources_StringGrid->Width = SourcesTab->Width - 5;
		Sources_StringGrid->Height = SourcesTab->Height - StatusBar->Height;

		//-- задание размера столбцов --//
		Sources_StringGrid->ColWidths[0] = (Sources_StringGrid->Width-size_scroll) * engine->Config()->SourcesCol_0;
		Sources_StringGrid->ColWidths[1] = (Sources_StringGrid->Width-size_scroll) * engine->Config()->SourcesCol_1;
		Sources_StringGrid->ColWidths[2] = (Sources_StringGrid->Width-size_scroll) * engine->Config()->SourcesCol_2;
		Sources_StringGrid->ColWidths[3] = (Sources_StringGrid->Width-size_scroll) * engine->Config()->SourcesCol_3;
		Sources_StringGrid->ColWidths[4] = (Sources_StringGrid->Width-size_scroll) * engine->Config()->SourcesCol_4;
		Sources_StringGrid->ColWidths[5] = (Sources_StringGrid->Width-size_scroll) * engine->Config()->SourcesCol_5;
		Sources_StringGrid->ColWidths[6] = (Sources_StringGrid->Width-size_scroll) * engine->Config()->SourcesCol_6;

		//-- перезапись таблицы --//
		UpdateSources(Sources_StringGrid->Row, true);

		return;
	}

	//-- если активная вкладка - Currencys, изменяем параметры элементов --//
	if(PageControl->ActivePageIndex == 1)
	{
		//-- задание размера таблицы --//
		Currencys_StringGrid->Width = CurrencysTab->Width - 5;
		Currencys_StringGrid->Height = CurrencysTab->Height - StatusBar->Height;

		//-- задание размера столбцов --//
		Currencys_StringGrid->ColWidths[0] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_0;
		Currencys_StringGrid->ColWidths[1] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_1;
		Currencys_StringGrid->ColWidths[2] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_2;
		Currencys_StringGrid->ColWidths[3] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_3;
		Currencys_StringGrid->ColWidths[4] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_4;
		Currencys_StringGrid->ColWidths[5] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_5;
		Currencys_StringGrid->ColWidths[6] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_6;
		Currencys_StringGrid->ColWidths[7] = (Currencys_StringGrid->Width-size_scroll) * engine->Config()->CurrencysCol_7;

		//-- перезапись таблицы --//
		UpdateCurrencys(Currencys_StringGrid->Row, true);

		return;
	}

	//-- если активная вкладка - Lines, изменяем параметры элементов --//
	if(PageControl->ActivePageIndex == 2)
	{
		//-- задание размера таблиц --//
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

		//-- задание размера поля заметок --//
		Lines_NotesMemo->Left = Lines_NotesStatic->Left + Lines_NotesStatic->Width + 20;
		Lines_NotesMemo->Width = LinesTab->Width - 100;

		//-- задание размера столбцов --//
		Lines_NamesStringGrid->ColWidths[0] = (Lines_NamesStringGrid->Width-size_scroll) * engine->Config()->LinesNamesCol_0;
		Lines_NamesStringGrid->ColWidths[1] = (Lines_NamesStringGrid->Width-size_scroll) * engine->Config()->LinesNamesCol_1;
		Lines_NamesStringGrid->ColWidths[2] = (Lines_NamesStringGrid->Width-size_scroll) * engine->Config()->LinesNamesCol_2;

		Lines_SourcesStringGrid->ColWidths[0] = Lines_SourcesStringGrid->Width-size_scroll;

		Lines_CurrencysStringGrid->ColWidths[0] = Lines_CurrencysStringGrid->Width-size_scroll;

		Lines_BasesStringGrid->ColWidths[0] = Lines_BasesStringGrid->Width-size_scroll;



		//-- перезапись таблицы --//
		UpdateLines(Lines_NamesStringGrid->Row, Lines_SourcesStringGrid->Row, Lines_CurrencysStringGrid->Row, Lines_BasesStringGrid->Row, true);

		return;
	}


	//-- если активная вкладка - Corrections, изменяем параметры элементов --//
	if(PageControl->ActivePageIndex == 4)
	{
		//-- задание размера таблицы --//
		Corrections_StringGrid->Width = CorrectionsTab->Width - 5;
		Corrections_StringGrid->Height = CorrectionsTab->Height - StatusBar->Height;

		//-- задание размера столбцов --//
		Corrections_StringGrid->ColWidths[0] = (Corrections_StringGrid->Width-size_scroll) * engine->Config()->CorrectionsCol_0;
		Corrections_StringGrid->ColWidths[1] = (Corrections_StringGrid->Width-size_scroll) * engine->Config()->CorrectionsCol_1;
		Corrections_StringGrid->ColWidths[2] = (Corrections_StringGrid->Width-size_scroll) * engine->Config()->CorrectionsCol_2;
		Corrections_StringGrid->ColWidths[3] = (Corrections_StringGrid->Width-size_scroll) * engine->Config()->CorrectionsCol_3;
		Corrections_StringGrid->ColWidths[4] = (Corrections_StringGrid->Width-size_scroll) * engine->Config()->CorrectionsCol_4;
		Corrections_StringGrid->ColWidths[5] = (Corrections_StringGrid->Width-size_scroll) * engine->Config()->CorrectionsCol_5;
		Corrections_StringGrid->ColWidths[6] = (Corrections_StringGrid->Width-size_scroll) * engine->Config()->CorrectionsCol_6;

		//-- перезапись таблицы --//
		UpdateCorrections(Corrections_StringGrid->Row, true);

		return;
	}

	//-- если активная вкладка - Arbitrations, изменяем параметры элементов --//
	if(PageControl->ActivePageIndex == 5)
	{
		//-- задание размера таблиц --//
		Arbitrations_ActionsGrid->Left = 0;
		Arbitrations_ActionsGrid->Width = ArbitrationsTab->Width - 5;
		Arbitrations_ActionsGrid->Height = ArbitrationsTab->Height - StatusBar->Height;


		//-- задание размера столбцов --//
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


		//-- перезапись таблицы --//
		//UpdateArbitrations(Arbitrations_ActionsGrid->Row, true);

		return;
	}


	//-- если активная вкладка - Collections, изменяем параметры элементов --//
	if(PageControl->ActivePageIndex == 6)
	{
		//-- задание размера таблицы --//
		Collections_StringGrid->Width = СollectionsTab->Width - 5;
		Collections_StringGrid->Height = СollectionsTab->Height - StatusBar->Height;

		//-- задание размера столбцов --//
		Collections_StringGrid->ColWidths[0] = (Collections_StringGrid->Width-size_scroll) * 0.30;
		Collections_StringGrid->ColWidths[1] = (Collections_StringGrid->Width-size_scroll) * 0.70;

		//-- перезапись таблицы --//
		//UpdateCollections();

		return;
	}
}


//-- ФУНКЦИЯ ИЗМЕНЕНИЯ РАЗМЕРА ШИРИНЫ КОЛОНОК ВО ВКЛАДКЕ SOURCES --//
void __fastcall TMainForm::Sources_StringGridMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	unsigned int size_scroll = 16;

	//-- проверка на изменения размера ширины колонок --//
	if( (Sources_StringGrid->Width-size_scroll)/Sources_StringGrid->ColWidths[0] != engine->Config()->SourcesCol_0 ||
		(Sources_StringGrid->Width-size_scroll)/Sources_StringGrid->ColWidths[1] != engine->Config()->SourcesCol_1 ||
		(Sources_StringGrid->Width-size_scroll)/Sources_StringGrid->ColWidths[2] != engine->Config()->SourcesCol_2 ||
		(Sources_StringGrid->Width-size_scroll)/Sources_StringGrid->ColWidths[3] != engine->Config()->SourcesCol_3 ||
		(Sources_StringGrid->Width-size_scroll)/Sources_StringGrid->ColWidths[4] != engine->Config()->SourcesCol_4 ||
		(Sources_StringGrid->Width-size_scroll)/Sources_StringGrid->ColWidths[5] != engine->Config()->SourcesCol_5 ||
		(Sources_StringGrid->Width-size_scroll)/Sources_StringGrid->ColWidths[6] != engine->Config()->SourcesCol_6
	  )
	  {
		  //-- в случае, если пользователь изменил ширину колонки, проверяем её корректность --//
		  if(Sources_StringGrid->ColWidths[0] +
			 Sources_StringGrid->ColWidths[1] +
			 Sources_StringGrid->ColWidths[2] +
			 Sources_StringGrid->ColWidths[3] +
			 Sources_StringGrid->ColWidths[4] +
			 Sources_StringGrid->ColWidths[5] +
			 Sources_StringGrid->ColWidths[6]
			 > Sources_StringGrid->Width - size_scroll)
			 {
				 //-- в случае неверных размеров, восстанавливаем размер --//
				 SetParamElements();
			 }
		  else
		  {
			//-- в случае верных размеровов, сохраняем параметры ширины --//
			engine->Config()->SourcesCol_0 = (float)Sources_StringGrid->ColWidths[0]/(Sources_StringGrid->Width-size_scroll);
			engine->Config()->SourcesCol_1 = (float)Sources_StringGrid->ColWidths[1]/(Sources_StringGrid->Width-size_scroll);
			engine->Config()->SourcesCol_2 = (float)Sources_StringGrid->ColWidths[2]/(Sources_StringGrid->Width-size_scroll);
			engine->Config()->SourcesCol_3 = (float)Sources_StringGrid->ColWidths[3]/(Sources_StringGrid->Width-size_scroll);
			engine->Config()->SourcesCol_4 = (float)Sources_StringGrid->ColWidths[4]/(Sources_StringGrid->Width-size_scroll);
			engine->Config()->SourcesCol_5 = (float)Sources_StringGrid->ColWidths[5]/(Sources_StringGrid->Width-size_scroll);
			engine->Config()->SourcesCol_6 = (float)Sources_StringGrid->ColWidths[6]/(Sources_StringGrid->Width-size_scroll);

			//-- применение параметров --//
			SetParamElements();
		  }
	  }
}


//-- ФУНКЦИЯ ИЗМЕНЕНИЯ РАЗМЕРА ШИРИНЫ КОЛОНОК ВО ВКЛАДКЕ CURRENCYS --//
void __fastcall TMainForm::Currencys_StringGridMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	unsigned int size_scroll = 16;

	//-- проверка на изменения размера ширины колонок --//
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
		  //-- в случае, если пользователь изменил ширину колонки, проверяем её корректность --//
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
				 //-- в случае неверных размеров, восстанавливаем размер --//
				 SetParamElements();
			 }
		  else
		  {
			//-- в случае верных размеровов, сохраняем параметры ширины --//
			engine->Config()->CurrencysCol_0 = (float)Currencys_StringGrid->ColWidths[0]/(Currencys_StringGrid->Width-size_scroll);
			engine->Config()->CurrencysCol_1 = (float)Currencys_StringGrid->ColWidths[1]/(Currencys_StringGrid->Width-size_scroll);
			engine->Config()->CurrencysCol_2 = (float)Currencys_StringGrid->ColWidths[2]/(Currencys_StringGrid->Width-size_scroll);
			engine->Config()->CurrencysCol_3 = (float)Currencys_StringGrid->ColWidths[3]/(Currencys_StringGrid->Width-size_scroll);
			engine->Config()->CurrencysCol_4 = (float)Currencys_StringGrid->ColWidths[4]/(Currencys_StringGrid->Width-size_scroll);
			engine->Config()->CurrencysCol_5 = (float)Currencys_StringGrid->ColWidths[5]/(Currencys_StringGrid->Width-size_scroll);
			engine->Config()->CurrencysCol_6 = (float)Currencys_StringGrid->ColWidths[6]/(Currencys_StringGrid->Width-size_scroll);
			engine->Config()->CurrencysCol_7 = (float)Currencys_StringGrid->ColWidths[7]/(Currencys_StringGrid->Width-size_scroll);

			//-- применение параметров --//
			SetParamElements();
		  }
	  }
}


//-- ФУНКЦИЯ ИЗМЕНЕНИЯ РАЗМЕРА ШИРИНЫ КОЛОНОК ВО ВКЛАДКЕ LINES --//
void __fastcall TMainForm::Lines_NamesStringGridMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
    unsigned int size_scroll = 16;

	//-- проверка на изменения размера ширины колонок --//
	if( (Lines_NamesStringGrid->Width-size_scroll)/Lines_NamesStringGrid->ColWidths[0] != engine->Config()->LinesNamesCol_0 ||
		(Lines_NamesStringGrid->Width-size_scroll)/Lines_NamesStringGrid->ColWidths[1] != engine->Config()->LinesNamesCol_1 ||
		(Lines_NamesStringGrid->Width-size_scroll)/Lines_NamesStringGrid->ColWidths[2] != engine->Config()->LinesNamesCol_2
	  )
	  {
		  //-- в случае, если пользователь изменил ширину колонки, проверяем её корректность --//
		  if(Lines_NamesStringGrid->ColWidths[0] +
			 Lines_NamesStringGrid->ColWidths[1] +
			 Lines_NamesStringGrid->ColWidths[2]
			 > Lines_NamesStringGrid->Width - size_scroll)
			 {
				 //-- в случае неверных размеров, восстанавливаем размер --//
				 SetParamElements();
			 }
		  else
		  {
			//-- в случае верных размеровов, сохраняем параметры ширины --//
			engine->Config()->LinesNamesCol_0 = (float)Lines_NamesStringGrid->ColWidths[0]/(Lines_NamesStringGrid->Width-size_scroll);
			engine->Config()->LinesNamesCol_1 = (float)Lines_NamesStringGrid->ColWidths[1]/(Lines_NamesStringGrid->Width-size_scroll);
			engine->Config()->LinesNamesCol_2 = (float)Lines_NamesStringGrid->ColWidths[2]/(Lines_NamesStringGrid->Width-size_scroll);

			//-- применение параметров --//
			SetParamElements();
		  }
	  }
}



//-- ФУНКЦИЯ ИЗМЕНЕНИЯ РАЗМЕРА ШИРИНЫ КОЛОНОК ВО ВКЛАДКЕ CORRECTIONS --//
void __fastcall TMainForm::Corrections_StringGridMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	unsigned int size_scroll = 16;

	//-- проверка на изменения размера ширины колонок --//
	if( (Corrections_StringGrid->Width-size_scroll)/Corrections_StringGrid->ColWidths[0] != engine->Config()->CorrectionsCol_0 ||
		(Corrections_StringGrid->Width-size_scroll)/Corrections_StringGrid->ColWidths[1] != engine->Config()->CorrectionsCol_1 ||
		(Corrections_StringGrid->Width-size_scroll)/Corrections_StringGrid->ColWidths[2] != engine->Config()->CorrectionsCol_2 ||
		(Corrections_StringGrid->Width-size_scroll)/Corrections_StringGrid->ColWidths[3] != engine->Config()->CorrectionsCol_3 ||
		(Corrections_StringGrid->Width-size_scroll)/Corrections_StringGrid->ColWidths[4] != engine->Config()->CorrectionsCol_4 ||
		(Corrections_StringGrid->Width-size_scroll)/Corrections_StringGrid->ColWidths[5] != engine->Config()->CorrectionsCol_5 ||
		(Corrections_StringGrid->Width-size_scroll)/Corrections_StringGrid->ColWidths[6] != engine->Config()->CorrectionsCol_6
	  )
	  {
		  //-- в случае, если пользователь изменил ширину колонки, проверяем её корректность --//
		  if(Corrections_StringGrid->ColWidths[0] +
			 Corrections_StringGrid->ColWidths[1] +
			 Corrections_StringGrid->ColWidths[2] +
			 Corrections_StringGrid->ColWidths[3] +
			 Corrections_StringGrid->ColWidths[4] +
			 Corrections_StringGrid->ColWidths[5] +
			 Corrections_StringGrid->ColWidths[6]
			 > Corrections_StringGrid->Width - size_scroll)
			 {
				 //-- в случае неверных размеров, восстанавливаем размер --//
				 SetParamElements();
			 }
		  else
		  {
			//-- в случае верных размеровов, сохраняем параметры ширины --//
			engine->Config()->CorrectionsCol_0 = (float)Corrections_StringGrid->ColWidths[0]/(Corrections_StringGrid->Width-size_scroll);
			engine->Config()->CorrectionsCol_1 = (float)Corrections_StringGrid->ColWidths[1]/(Corrections_StringGrid->Width-size_scroll);
			engine->Config()->CorrectionsCol_2 = (float)Corrections_StringGrid->ColWidths[2]/(Corrections_StringGrid->Width-size_scroll);
			engine->Config()->CorrectionsCol_3 = (float)Corrections_StringGrid->ColWidths[3]/(Corrections_StringGrid->Width-size_scroll);
			engine->Config()->CorrectionsCol_4 = (float)Corrections_StringGrid->ColWidths[4]/(Corrections_StringGrid->Width-size_scroll);
			engine->Config()->CorrectionsCol_5 = (float)Corrections_StringGrid->ColWidths[5]/(Corrections_StringGrid->Width-size_scroll);
			engine->Config()->CorrectionsCol_6 = (float)Corrections_StringGrid->ColWidths[6]/(Corrections_StringGrid->Width-size_scroll);

			//-- применение параметров --//
			SetParamElements();
		  }
	  }
}


//-- ФУНКЦИЯ ИЗМЕНЕНИЯ РАЗМЕРА ШИРИНЫ КОЛОНОК ВО ВКЛАДКЕ ARBITRATIONS --//
void __fastcall TMainForm::Arbitrations_ActionsGridMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
    unsigned int size_scroll = 16;

	//-- блокировка изменений скрытых ячеек --//
	if(Arbitrations_ActionsGrid->ColWidths[0] != 0)
	{
		SetParamElements();
	}


	//-- проверка на изменения размера ширины колонок --//
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
		  //-- в случае, если пользователь изменил ширину колонки, проверяем её корректность --//
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
				 //-- в случае неверных размеров, восстанавливаем размер --//
				 SetParamElements();
			 }
		  else
		  {
			//-- в случае верных размеров, сохраняем параметры ширины --//

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


			//-- применение параметров --//
			SetParamElements();
		  }
	  }
}


//-- ФУНКЦИЯ ОБНОВЛЕНИЯ ЗНАЧЕНИЙ ПОСЛЕДНЕГО ОБНОВЛЕНИЯ ДАННЫХ --//
void TMainForm::UpdateLastCollected(const bool SetTime)
{
	//-- проверка на необходимость записи параметров текущего времени --//
	if(SetTime)
	{
		//--  определение времени на сбор данных --//
		unsigned int StartTimeInSecond = time_collect.StartCollectSS + time_collect.StartCollectNN * 60 + time_collect.StartCollectHH * 3600
									   + time_collect.StartCollectDD * 86400 + time_collect.StartCollectMM * 2628000 + time_collect.StartCollectYY * 31536000;

		unsigned int EndTimeInSecond = time_collect.EndCollectSS + time_collect.EndCollectNN * 60 + time_collect.EndCollectHH * 3600
									   + time_collect.EndCollectDD * 86400 + time_collect.EndCollectMM * 2628000 + time_collect.EndCollectYY * 31536000;


		//-- запись параметра окончания сбора данных --//
		engine->Config()->LastCollectedDD = time_collect.EndCollectDD;
		engine->Config()->LastCollectedMM = time_collect.EndCollectMM;
		engine->Config()->LastCollectedYY = time_collect.EndCollectYY;
		engine->Config()->LastCollectedHH = time_collect.EndCollectHH;
		engine->Config()->LastCollectedNN = time_collect.EndCollectNN;
		engine->Config()->LastCollectedSS = time_collect.EndCollectSS;

		//-- время, затраченное на сбор данных --//
		if(EndTimeInSecond - StartTimeInSecond < 99999)
			engine->Config()->LastTimeOnCollect = EndTimeInSecond - StartTimeInSecond;
	}

	//-- обновление статус бара --//
	MainForm->StatusBar->Panels->Items[1]->Text = 	"Last collected: "
													+ UnicodeString( engine->Config()->LastCollectedDD )
													+ "." + UnicodeString( engine->Config()->LastCollectedMM )
													+ "." + UnicodeString( engine->Config()->LastCollectedYY )
													+ " " + UnicodeString( engine->Config()->LastCollectedHH )
													+ ":" + UnicodeString( engine->Config()->LastCollectedNN )
													+ ":" + UnicodeString( engine->Config()->LastCollectedSS )
													+ "  Time on collected: "
													+ engine->Config()->LastTimeOnCollect + " s.";

	//-- обновление подсказки в трее --//
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

//-- ФУНКЦИЯ УСТАНОВКИ СТАНДАРТНЫХ НАДПИСЕЙ ТАБЛИЦЫ SOURCE GRID --//
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

//-- ФУНКЦИЯ УСТАНОВКИ СТАНДАРТНЫХ НАДПИСЕЙ ТАБЛИЦЫ CURRENCYS GRID --//
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


//-- ФУНКЦИЯ УСТАНОВКИ СТАНДАРТНЫХ НАДПИСЕЙ ТАБЛИЦЫ LINES GRID --//
void TMainForm::DefaultLinesGrid()
{
	Lines_NamesStringGrid->Cells[0][0] = "ID:" + UnicodeString( engine->Config()->SortLines == eID ? " *" : "" );
	Lines_NamesStringGrid->Cells[1][0] = "Name:" + UnicodeString( engine->Config()->SortLines == eNAME ? " *" : "" );
	Lines_NamesStringGrid->Cells[2][0] = "Enabled:" + UnicodeString( engine->Config()->SortLines == eENABLED ? " *" : "" );

	Lines_SourcesStringGrid->Cells[0][0] = "Sources:";
	Lines_CurrencysStringGrid->Cells[0][0] = "Currensys:";
	Lines_BasesStringGrid->Cells[0][0] = "Bases:";
}

//-- ФУНКЦИЯ УСТАНОВКИ СТАНДАРТНЫХ НАДПИСЕЙ ТАБЛИЦЫ CORRECTIONS GRID --//
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

//-- ФУНКЦИЯ УСТАНОВКИ СТАНДАРТНЫХ НАДПИСЕЙ ТАБЛИЦЫ ARBITRATIONS GRID --//
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

//-- ФУНКЦИЯ УСТАНОВКИ СТАНДАРТНЫХ НАДПИСЕЙ ТАБЛИЦЫ COLLECTIONS GRID --//
void TMainForm::DefaultCollectionsGrid()
{
	Collections_StringGrid->Cells[0][0] = "Sources:";
    Collections_StringGrid->Cells[1][0] = "Notes:";
}


//-- ФУНКЦИЯ ОЧИСТКИ STRING GRID --//
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


//-- ФУНКЦИЯ ОБНОВЛЕНИЯ SOURCES GRID --//
void TMainForm::UpdateSources(unsigned int Row, bool AutoUpdate)
{

    //-- если было выполнено удаление, сбрасываем активную строку --//
	if(engine->GetSortedSources().size() + 1 < Sources_StringGrid->RowCount)
		Row = Row - 1;

	//-- проверка входящих данных --//
	if(Row == 0)
		Row = 1;

	//-- очистка таблицы --//
	ClearStringGrid( Sources_StringGrid );


	if(engine->GetSortedSources().size())
	{
		//-- заполнение данными --//
		int row_count=1;
		for(std::vector< int >::iterator source_iterator = engine->GetSortedSources().begin(); source_iterator != engine->GetSortedSources().end(); source_iterator ++)
		{
			//-- поиск в MAP'e нужного элемента по отсортированому списку --//
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

				//-- добавление строки --//
				Sources_StringGrid->RowCount ++;
			}
		}

        //-- удаление лишней строки --//
		Sources_StringGrid->RowCount --;

		//-- установка активной ячейки --//
		if(AutoUpdate && PageControl->ActivePageIndex == 0)
		{
			Sources_StringGrid->Row = Row;
			Sources_StringGrid->SetFocus();
		}
	}


    //-- определение активности элементов вкладки Sources --//
	//-- в зависимости от наличия данных в таблице --//
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


//-- ФУНКЦИЯ ОБНОВЛЕНИЯ CURRENCYS --//
void TMainForm::UpdateCurrencys(unsigned int Row, bool AutoUpdate)
{
	//-- если было выполнено удаление, сбрасываем активную строку --//
	if(engine->GetSortedСurrencys().size() + 1 < Currencys_StringGrid->RowCount)
		Row = Row - 1;

	//-- проверка входящих данных --//
	if(Row == 0)
		Row = 1;


	//-- очистка таблицы --//
	ClearStringGrid( Currencys_StringGrid );


	if(engine->GetSortedСurrencys().size())
	{

		//-- заполнение данными --//
		int row_count=1;
		for(std::vector< int >::iterator currency_iterator = engine->GetSortedСurrencys().begin(); currency_iterator != engine->GetSortedСurrencys().end(); currency_iterator ++)
		{
			//-- поиск в MAP'e нужного элемента по отсортированому списку --//
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

				//-- добавление строки --//
				Currencys_StringGrid->RowCount ++;
			 }
		}

		//-- удаление лишней строки --//
		Currencys_StringGrid->RowCount --;

		//-- установка активной ячейки --//
		if(AutoUpdate && PageControl->ActivePageIndex == 1)
		{
			Currencys_StringGrid->Row = Row;
			Currencys_StringGrid->SetFocus();
		}
	}


    //-- определение активности элементов вкладки Currencys --//
	//-- в зависимости от наличия данных в таблице --//
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



//-- ФУНКЦИЯ ОБНОВЛЕНИЯ LINES --//
void TMainForm::UpdateLines(unsigned int NamesRow, unsigned int SourcesRow, unsigned int CurrencysRow, unsigned int BasesRow, bool AutoUpdate)
{

	//-- если было выполнено удаление, сбрасываем активную строку --//
	if(engine->GetSortedLines().size() + 1 < Lines_NamesStringGrid->RowCount)
		NamesRow = NamesRow - 1;

	//-- проверка входящих данных --//
	if(NamesRow == 0)
		NamesRow = 1;


	//-- очистка таблицы --//
	ClearStringGrid( Lines_NamesStringGrid );


	if(engine->GetSortedLines().size())
	{
		//-- очистка поля заметок --//
		Lines_NotesMemo->Clear();


		//-- заполнение таблицы имён данными --//
		int row_count=1;
		for(std::vector< int >::iterator line_iterator = engine->GetSortedLines().begin(); line_iterator != engine->GetSortedLines().end(); line_iterator ++)
		{
			//-- поиск в MAP'e нужного элемента по отсортированому списку --//

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

				//-- добавление строки --//
				Lines_NamesStringGrid->RowCount ++;
			 }
		}

		//-- удаление лишней строки --//
		if(engine->GetSortedLines().size())
			Lines_NamesStringGrid->RowCount --;




		//-- поиск ID активной ячейки --//
		MLine::iterator map_iterator_activy = MainForm->engine->Data()->map_lines.find( Lines_NamesStringGrid->Cells[0][NamesRow].ToInt() );

		if(map_iterator_activy == MainForm->engine->Data()->map_lines.end())
			return;

        //-- если было выполнено удаление, сбрасываем активную строку --//
		if(map_iterator_activy->second.sources.size() + 1 < Lines_SourcesStringGrid->RowCount)
			SourcesRow = SourcesRow - 1;

		if(map_iterator_activy->second.сurrencys.size() + 1 < Lines_SourcesStringGrid->RowCount)
			CurrencysRow = CurrencysRow - 1;

		if(map_iterator_activy->second.bases.size() + 1 < Lines_BasesStringGrid->RowCount)
			BasesRow = BasesRow - 1;

        //-- проверка входящих данных --//
		if(SourcesRow == 0)
		SourcesRow = 1;
		if(CurrencysRow == 0)
			CurrencysRow = 1;
		if(BasesRow == 0)
			BasesRow = 1;

		//-- очистка таблиц --//
		ClearStringGrid( Lines_SourcesStringGrid );
		ClearStringGrid( Lines_CurrencysStringGrid );
		ClearStringGrid( Lines_BasesStringGrid );




		//-- заполнение таблицы источников данными --//
		for(int k=0; k != map_iterator_activy->second.sources.size(); k ++)
		{
			//-- поиск имя источника по ID --//
			MSource::iterator map_iterator_source = engine->Data()->map_sources.find( map_iterator_activy->second.sources[k] );

			if(map_iterator_source != engine->Data()->map_sources.end())
			{
				//-- запись имени источника --//
				UnicodeString end;

				end = map_iterator_source->second.name.Length()>Lines_SourcesStringGrid->ColWidths[0]/8 ? end = "..." : end = "";
				Lines_SourcesStringGrid->Cells[0][k+1] = map_iterator_source->second.name.SubString(0, Lines_SourcesStringGrid->ColWidths[0]/8) + end;

				//-- добавление строки --//
				Lines_SourcesStringGrid->RowCount ++;
			}
		}

		//-- удаление лишней строки --//
		if(map_iterator_activy->second.sources.size())
			Lines_SourcesStringGrid->RowCount --;



		//-- заполнение таблицы валют данными --//
		for(int k=0; k != map_iterator_activy->second.сurrencys.size(); k ++)
		{
			//-- поиск имя валюты по ID --//
			MCurrency::iterator map_iterator_currency = engine->Data()->map_currencys.find( map_iterator_activy->second.сurrencys[k] );

			if(map_iterator_currency != engine->Data()->map_currencys.end())
			{
				//-- запись имени валюты --//
				UnicodeString end;

				end = map_iterator_currency->second.name.Length()>Lines_CurrencysStringGrid->ColWidths[0]/8 ? end = "..." : end = "";
				Lines_CurrencysStringGrid->Cells[0][k+1] = map_iterator_currency->second.name.SubString(0, Lines_CurrencysStringGrid->ColWidths[0]/8) + end;

				//-- добавление строки --//
				Lines_CurrencysStringGrid->RowCount ++;
			}
		}

		//-- удаление лишней строки --//
		if(map_iterator_activy->second.сurrencys.size())
			Lines_CurrencysStringGrid->RowCount --;



		//-- заполнение таблицы базовых валют данными --//
		for(int k=0; k != map_iterator_activy->second.bases.size(); k ++)
		{
			//-- поиск имя валюты по ID --//
			MCurrency::iterator map_iterator_base = engine->Data()->map_currencys.find( map_iterator_activy->second.bases[k] );

			if(map_iterator_base != engine->Data()->map_currencys.end())
			{
				//-- запись имени валюты --//
				UnicodeString end;

				end = map_iterator_base->second.name.Length()>Lines_BasesStringGrid->ColWidths[0]/8 ? end = "..." : end = "";
				Lines_BasesStringGrid->Cells[0][k+1] = map_iterator_base->second.name.SubString(0, Lines_BasesStringGrid->ColWidths[0]/8) + end;

				//-- добавление строки --//
				Lines_BasesStringGrid->RowCount ++;
			}
		}

		//-- удаление лишней строки --//
		if(map_iterator_activy->second.bases.size())
			Lines_BasesStringGrid->RowCount --;


        //-- заполнение поля заметок данными --//
		Lines_NotesMemo->Text = map_iterator_activy->second.notes;


		//-- установка активных ячеек--//
		if(AutoUpdate && PageControl->ActivePageIndex == 2)
		{
			//-- таблица имён --//
			Lines_NamesStringGrid->Row = NamesRow;
			Lines_NamesStringGrid->SetFocus();

			//-- таблица источников --//
			Lines_SourcesStringGrid->Row = SourcesRow;
			Lines_SourcesStringGrid->SetFocus();

			//-- таблица валют --//
			Lines_CurrencysStringGrid->Row = CurrencysRow;
			Lines_CurrencysStringGrid->SetFocus();

			//-- таблица базовых валют --//
			Lines_BasesStringGrid->Row = BasesRow;
			Lines_BasesStringGrid->SetFocus();
		}

	}


    //-- определение активности элементов вкладки Lines --//
    //-- в зависимости от наличия данных в таблице --//
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



//-- ФУНКЦИЯ ОБНОВЛЕНИЯ PARAMETERS --//
void TMainForm::UpdateParams()
{
	//-- обновление данных коэффициента прибыли --//
	Parameters_CoefficientEdit->Text = engine->Data()->params.factor;

	//-- обновление данных максимальной длинны цепочки --//
	Parameters_MaxLengthEdit->Text 	 = engine->Data()->params.maxChainLen;
}



//-- ФУНКЦИЯ ОБНОВЛЕНИЯ CORRECTIONS --//
void TMainForm::UpdateCorrections(unsigned int Row, bool AutoUpdate)
{

    //-- если было выполнено удаление, сбрасываем активную строку --//
	if(engine->GetSortedCorrections().size() + 1 < Corrections_StringGrid->RowCount)
		Row = Row - 1;

	//-- проверка входящих данных --//
	if(Row == 0)
		Row = 1;

	//-- очистка таблицы --//
	ClearStringGrid( Corrections_StringGrid );


	if(engine->GetSortedCorrections().size())
	{

		//-- заполнение данными --//
		int row_count=1;
		for(std::vector< int >::iterator correction_iterator = engine->GetSortedCorrections().begin(); correction_iterator != engine->GetSortedCorrections().end(); correction_iterator ++)
		{
			//-- поиск в MAP'e нужного элемента по отсортированому списку --//
			MCorrection::iterator map_iterator = engine->Data()->map_corrections.find( *correction_iterator );

			if(map_iterator != engine->Data()->map_corrections.end())
			{

				//-- ID --//
				Corrections_StringGrid->Cells[0][row_count] = map_iterator->first;

				UnicodeString end;

				//-- добавление значения источника --//

				if(engine->Data()->map_sources.find( map_iterator->second.sourceId.ToInt() ) != engine->Data()->map_sources.end())
				{
					end = engine->Data()->map_sources.find( map_iterator->second.sourceId.ToInt() )->second.name.Length()>Corrections_StringGrid->ColWidths[1]/8 ? end = "..." : end = "";

					Corrections_StringGrid->Cells[1][row_count]
						= engine->Data()->map_sources.find( map_iterator->second.sourceId.ToInt() )->second.name.SubString(0, Corrections_StringGrid->ColWidths[1]/8) + end;
				}

				//-- добавление значения исходящей валюты --//


				if(engine->Data()->map_currencys.find( map_iterator->second.currOut.ToInt() ) != engine->Data()->map_currencys.end())
				{
					end = engine->Data()->map_currencys.find( map_iterator->second.currOut.ToInt() )->second.name.Length()>Corrections_StringGrid->ColWidths[2]/8 ? end = "..." : end = "";

					Corrections_StringGrid->Cells[2][row_count]
						= engine->Data()->map_currencys.find( map_iterator->second.currOut.ToInt() )->second.name.SubString(0, Corrections_StringGrid->ColWidths[2]/8) + end;
				}

				//-- добавление значения входящей валюты --//


				if(engine->Data()->map_currencys.find( map_iterator->second.currIn.ToInt() ) != engine->Data()->map_currencys.end())
				{
					end = engine->Data()->map_currencys.find( map_iterator->second.currIn.ToInt() )->second.name.Length()>Corrections_StringGrid->ColWidths[3]/8 ? end = "..." : end = "";

					Corrections_StringGrid->Cells[3][row_count]
						= engine->Data()->map_currencys.find( map_iterator->second.currIn.ToInt() )->second.name.SubString(0, Corrections_StringGrid->ColWidths[3]/8) + end;
				}

				//-- добавление дополнительных значений --//

				end = map_iterator->second.fee.Length()>Corrections_StringGrid->ColWidths[4]/8 ? end = "..." : end = "";
				Corrections_StringGrid->Cells[4][row_count] = engine->FloatWithDots( map_iterator->second.fee ).SubString(0, Corrections_StringGrid->ColWidths[4]/8) + end;



				end =  map_iterator->second.enabled.Length()>Corrections_StringGrid->ColWidths[5]/8 ? end = "..." : end = "";
				Corrections_StringGrid->Cells[5][row_count] =  map_iterator->second.enabled.SubString(0, Corrections_StringGrid->ColWidths[5]/8) + end;



				end = map_iterator->second.notes.Length()>Corrections_StringGrid->ColWidths[6]/8 ? end = "..." : end = "";
				Corrections_StringGrid->Cells[6][row_count] = map_iterator->second.notes.SubString(0, Corrections_StringGrid->ColWidths[6]/8) + end;;


				row_count ++;

				//-- добавление строки --//
				Corrections_StringGrid->RowCount ++;
			}
		}

		//-- удаление лишней строки --//
		Corrections_StringGrid->RowCount --;

        //-- установка активной ячейки --//
		if(AutoUpdate && PageControl->ActivePageIndex == 4)
		{
			Corrections_StringGrid->Row = Row;
			Corrections_StringGrid->SetFocus();
		}
	}


    //-- определение активности элементов вкладки Corrections --//
	//-- в зависимости от наличия данных в таблице --//
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



//-- ФУНКЦИЯ ОБНОВЛЕНИЯ ARBITRATIONS --//
void TMainForm::UpdateArbitrations(unsigned int Row, bool AutoUpdate)
{

	//-- если было выполнено удаление, сбрасываем активную строку --//
	if(engine->GetSortedArbitrations().size() + 1 < Arbitrations_ActionsGrid->RowCount)
		Row = Row - 1;

	//-- проверка входящих данных --//
	if(Row == 0)
		Row = 1;

	//-- очистка таблицы --//
	ClearStringGrid( Arbitrations_ActionsGrid );

	if(engine->GetSortedArbitrations().size())
	{

		//-- заполнение данными --//
		int row_count = 1;

		//-- вывод сначала АКТУАЛЬНЫХ операций --//
		for(std::vector< int >::iterator arbitration_iterator = engine->GetSortedArbitrations().begin(); arbitration_iterator != engine->GetSortedArbitrations().end(); arbitration_iterator ++)
		{

			//-- поиск в MAP'e нужного элемента по отсортированому списку --//
			MArbitration::iterator map_iterator = engine->Data()->map_arbitrations.find( *arbitration_iterator );

			if(map_iterator != engine->Data()->map_arbitrations.end())
			{
				if(map_iterator->second.relevance.ToInt())
				{
					//-- ID --//
					Arbitrations_ActionsGrid->Cells[0][row_count] = map_iterator->first;

					UnicodeString end;

					//-- коефициент прибыльности --//
					end = map_iterator->second.factor.Length()>Arbitrations_ActionsGrid->ColWidths[1]/8 ? end = "..." : end = "";
					Arbitrations_ActionsGrid->Cells[1][row_count] = map_iterator->second.factor.SubString(0, Arbitrations_ActionsGrid->ColWidths[1]/8) + end;

					//-- линия --//
					if( engine->Data()->map_lines.find( map_iterator->second.line.ToInt() ) != engine->Data()->map_lines.end() )
					{
						end = engine->Data()->map_lines.find( map_iterator->second.line.ToInt() )->second.name.Length()>Arbitrations_ActionsGrid->ColWidths[2]/8 ? end = "..." : end = "";
						Arbitrations_ActionsGrid->Cells[2][row_count] = engine->Data()->map_lines.find( map_iterator->second.line.ToInt() )->second.name.SubString(0, Arbitrations_ActionsGrid->ColWidths[2]/8) + end;
					}


					//-- время --//
					end = map_iterator->second.time.Length()>Arbitrations_ActionsGrid->ColWidths[9]/8 ? end = "..." : end = "";
					Arbitrations_ActionsGrid->Cells[10][row_count] = map_iterator->second.time.SubString(0, Arbitrations_ActionsGrid->ColWidths[9]/8) + end;



					row_count ++;

					//-- добавление строки --//
					Arbitrations_ActionsGrid->RowCount ++;
				}
			}
		}


		//-- вывод затем НЕАКТУАЛЬНЫХ операций --//
		for(std::vector< int >::iterator arbitration_iterator = engine->GetSortedArbitrations().begin(); arbitration_iterator != engine->GetSortedArbitrations().end(); arbitration_iterator ++)
		{

			//-- поиск в MAP'e нужного элемента по отсортированому списку --//
			MArbitration::iterator map_iterator = engine->Data()->map_arbitrations.find( *arbitration_iterator );

			if(map_iterator != engine->Data()->map_arbitrations.end())
			{
				if(!map_iterator->second.relevance.ToInt())
				{
					//-- ID --//
					Arbitrations_ActionsGrid->Cells[0][row_count] = map_iterator->first;

					UnicodeString end;

					//-- коефициент прибыльности --//
					end = map_iterator->second.factor.Length()>Arbitrations_ActionsGrid->ColWidths[1]/8 ? end = "..." : end = "";
					Arbitrations_ActionsGrid->Cells[1][row_count] = map_iterator->second.factor.SubString(0, Arbitrations_ActionsGrid->ColWidths[1]/8) + end;

					//-- линия --//
					if( engine->Data()->map_lines.find( map_iterator->second.line.ToInt() ) != engine->Data()->map_lines.end() )
					{
						end = engine->Data()->map_lines.find( map_iterator->second.line.ToInt() )->second.name.Length()>Arbitrations_ActionsGrid->ColWidths[2]/8 ? end = "..." : end = "";
						Arbitrations_ActionsGrid->Cells[2][row_count] = engine->Data()->map_lines.find( map_iterator->second.line.ToInt() )->second.name.SubString(0, Arbitrations_ActionsGrid->ColWidths[2]/8) + end;
					}


					//-- время --//
					end = map_iterator->second.time.Length()>Arbitrations_ActionsGrid->ColWidths[9]/8 ? end = "..." : end = "";
					Arbitrations_ActionsGrid->Cells[10][row_count] = map_iterator->second.time.SubString(0, Arbitrations_ActionsGrid->ColWidths[9]/8) + end;



					row_count ++;

					//-- добавление строки --//
					Arbitrations_ActionsGrid->RowCount ++;
				}
			}
		}


		//-- удаление лишней строки --//
		Arbitrations_ActionsGrid->RowCount --;

		//-- установка активных ячеек --//
		if(AutoUpdate && PageControl->ActivePageIndex == 5)
		{
			//-- таблица action's --//
			Arbitrations_ActionsGrid->Row = Row;
			Arbitrations_ActionsGrid->SetFocus();
		}
	}

}



//-- ФУНКЦИЯ ОБНОВЛЕНИЯ COLLECTIONS --//
void TMainForm::UpdateCollections(unsigned int Row, bool AutoUpdate)
{

	//-- если было выполнено удаление, сбрасываем активную строку --//
	if(engine->Data()->map_collections.size() + 1 < Collections_StringGrid->RowCount)
		Row = Row - 1;

	//-- проверка входящих данных --//
	if(Row == 0)
		Row = 1;

	//-- очистка таблицы --//
	ClearStringGrid( Collections_StringGrid );

	if(engine->Data()->map_collections.size())
	{

		//-- заполнение данными --//
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

            //-- добавление строки --//
			Collections_StringGrid->RowCount ++;
		}


		//-- удаление лишней строки --//
		Collections_StringGrid->RowCount --;


        //-- установка активной ячейки --//
		if(AutoUpdate && PageControl->ActivePageIndex == 6)
		{
			Collections_StringGrid->Row = Row;
			Collections_StringGrid->SetFocus();
		}
	}
}




