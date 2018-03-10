//---------------------------------------------------------------------------

#ifndef TTCPReadSocketThreadH
#define TTCPReadSocketThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//--************************************************************************--//

//-- ����������� Indy TCP Client --//
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>

//-- ����������� ���������������� ���������� --//
#include <memory>

//-- ����������� MAP --//
#include <map>

//-- ����������� JSON --//
#include <System.JSON.hpp>

typedef void (*FHandler)(TJSONObject*);
typedef std::map< UnicodeString, FHandler > MHandlers;

class TTCPReadSocketThread : public TThread
{
private:

	//-- �������� ��������� �� TCPClient --//
	TIdTCPClient *tcp_client;

	//-- ��������� �� ����������� ������� --//
	MHandlers *handlers;
	MHandlers::iterator handlers_it;

	//-- �������� JSON-������� --//
	std::shared_ptr< TJSONObject > json_object_parse;

	//-- ��� ���������� ������� � ������ --//
	UnicodeString name_search;

	//-- ���� �����--//
	TStringList *logs;

	//-- ���������� ���������� --//
	FHandler handler;

	//-- JSON-������ ��� �������� --//
	TJSONObject *json_object;

protected:

	void __fastcall Execute();

    void __fastcall CallHandler();


public:

	__fastcall TTCPReadSocketThread(TIdTCPClient *TCPClient, MHandlers *Handlers, UnicodeString Key, TStringList *Logs);

};

//--************************************************************************--//

#endif
