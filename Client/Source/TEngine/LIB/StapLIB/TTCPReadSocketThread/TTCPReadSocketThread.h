//---------------------------------------------------------------------------

#ifndef TTCPReadSocketThreadH
#define TTCPReadSocketThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//--************************************************************************--//

//-- подключение Indy TCP Client --//
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>

//-- подключение интеллектуальных указателей --//
#include <memory>

//-- подключение MAP --//
#include <map>

//-- подключение JSON --//
#include <System.JSON.hpp>

typedef void (*FHandler)(TJSONObject*);
typedef std::map< UnicodeString, FHandler > MHandlers;

class TTCPReadSocketThread : public TThread
{
private:

	//-- создание указателя на TCPClient --//
	TIdTCPClient *tcp_client;

	//-- указатели на обработчики функций --//
	MHandlers *handlers;
	MHandlers::iterator handlers_it;

	//-- создание JSON-объекта --//
	std::shared_ptr< TJSONObject > json_object_parse;

	//-- ИМЯ ПОИСКОВОГО ЗАПРОСА В СТРОКЕ --//
	UnicodeString name_search;

	//-- файл логов--//
	TStringList *logs;

	//-- вызываемый обработчик --//
	FHandler handler;

	//-- JSON-объект для передачи --//
	TJSONObject *json_object;

protected:

	void __fastcall Execute();

    void __fastcall CallHandler();


public:

	__fastcall TTCPReadSocketThread(TIdTCPClient *TCPClient, MHandlers *Handlers, UnicodeString Key, TStringList *Logs);

};

//--************************************************************************--//

#endif
