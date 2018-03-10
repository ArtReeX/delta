//---------------------------------------------------------------------------

#ifndef TestForm_DeltaH
#define TestForm_DeltaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "MainForm_Delta.h"


//-- ОНДЙКЧВЕМХЕ JSON --//
#include <System.JSON.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Imaging.pngimage.hpp>

class TTestForm : public TForm
{
__published:

	TMemo *ParamMemo;
	TStaticText *ParamStatic;
	TStaticText *AnswerStatic;
	TMemo *AnswerMemo;
	TButton *SendButton;
	TStaticText *MethodStatic;
	TEdit *MethodEdit;
	TImage *TestImage;
	TStaticText *InfoText;
	TEdit *ToBase64Edit;
	TEdit *FromBase64Edit;
	TButton *ToBase64Button;
	TButton *FromBase64Button;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SendButton_OneClick(TObject *Sender);
	void __fastcall ToBase64Button_OneClick(TObject *Sender);
	void __fastcall FromBase64Button_OneClick(TObject *Sender);

private:


public:

	//-- тсмйжхъ сярюмнбйх щкелемрнб тнплш б ондйкчвеммнл пефхле --//
	void SetElementConnect();

    //-- тсмйжхъ сярюмнбйх щкелемрбн тнплш б нрйкчвеммнл пефхле --//
	void SetElementDisconnect();

	__fastcall TTestForm(TComponent* Owner);

};


//-- напюанрвхй реярнбни тнплш --//
void TestForm_HandlerTest(TJSONObject *json_object_parse);


//---------------------------------------------------------------------------
extern PACKAGE TTestForm *TestForm;
//---------------------------------------------------------------------------
#endif
