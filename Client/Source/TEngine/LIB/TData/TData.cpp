  //-----------------------------------------------------------//
  //-------------------------- TData- -------------------------//
  //--------------------------(CPP)----------------------------//

//-- подключение заголовочного файла --//
#include "TData.h"

namespace TDataNS
{

    //-- стандартный конструктор --//
	TData::TData()
	:   data(new SData)
	{
	}

    //-- стандартный деструктор --//
	TData::~TData()
	{
	}

	//-- возврат хранилища данных --//
	SData* TData::Data()
	{
		return data.get();
	}


    //-- функция сортировки источников --//
	void TData::SortSources(const unsigned int Type, bool TypeInd)
	{
		//-- очистка вектора и индексами --//
		sorted_sources.clear();

		//-- очистка листинга --//
		string_list.clear();




		//-- если необходимо отсортировать по ID --//
		if(Type == eID)
		{
			for(MSource::iterator iterator_source = data.get()->map_sources.begin(); iterator_source != data.get()->map_sources.end(); iterator_source ++)
			{
				sorted_sources.push_back(iterator_source->first);
			}
		}


		//-- если необходимо отсортировать по NAME --//
		if(Type == eNAME)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MSource::iterator iterator_source = data.get()->map_sources.begin(); iterator_source != data.get()->map_sources.end(); iterator_source ++)
			{
				string_list.push_back( iterator_source->second.name );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MSource::iterator iterator_source;

				for(iterator_source = data.get()->map_sources.begin(); iterator_source != data.get()->map_sources.end(); iterator_source ++)
				{
					if(*iterator_list == iterator_source->second.name)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_sources.begin(); iterator_dublicate != sorted_sources.end(); iterator_dublicate ++)
						{
							if(iterator_source->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_sources.end())
                            break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_source != data.get()->map_sources.end())
					sorted_sources.push_back( iterator_source->first );
			}
		}


		//-- если необходимо отсортировать по URL --//
		if(Type == eURL)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MSource::iterator iterator_source = data.get()->map_sources.begin(); iterator_source != data.get()->map_sources.end(); iterator_source ++)
			{
				string_list.push_back( iterator_source->second.url );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MSource::iterator iterator_source;

				for(iterator_source = data.get()->map_sources.begin(); iterator_source != data.get()->map_sources.end(); iterator_source ++)
				{
					if(*iterator_list == iterator_source->second.url)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_sources.begin(); iterator_dublicate != sorted_sources.end(); iterator_dublicate ++)
						{
							if(iterator_source->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_sources.end())
                            break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_source != data.get()->map_sources.end())
					sorted_sources.push_back( iterator_source->first );
			}
		}


		//-- если необходимо отсортировать по DATAURL --//
		if(Type == eDATAURL)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MSource::iterator iterator_source = data.get()->map_sources.begin(); iterator_source != data.get()->map_sources.end(); iterator_source ++)
			{
				string_list.push_back( iterator_source->second.dataurl );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MSource::iterator iterator_source;

				for(iterator_source = data.get()->map_sources.begin(); iterator_source != data.get()->map_sources.end(); iterator_source ++)
				{
					if(*iterator_list == iterator_source->second.dataurl)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_sources.begin(); iterator_dublicate != sorted_sources.end(); iterator_dublicate ++)
						{
							if(iterator_source->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_sources.end())
                            break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_source != data.get()->map_sources.end())
					sorted_sources.push_back( iterator_source->first );
			}
		}


		//-- если необходимо отсортировать по GETTER --//
		if(Type == eGETTER)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MSource::iterator iterator_source = data.get()->map_sources.begin(); iterator_source != data.get()->map_sources.end(); iterator_source ++)
			{
				string_list.push_back( iterator_source->second.getter );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MSource::iterator iterator_source;

				for(iterator_source = data.get()->map_sources.begin(); iterator_source != data.get()->map_sources.end(); iterator_source ++)
				{
					if(*iterator_list == iterator_source->second.getter)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_sources.begin(); iterator_dublicate != sorted_sources.end(); iterator_dublicate ++)
						{
							if(iterator_source->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_sources.end())
                            break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_source != data.get()->map_sources.end())
					sorted_sources.push_back( iterator_source->first );
			}
		}


		//-- если необходимо отсортировать по ENABLED --//
		if(Type == eENABLED)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MSource::iterator iterator_source = data.get()->map_sources.begin(); iterator_source != data.get()->map_sources.end(); iterator_source ++)
			{
				string_list.push_back( iterator_source->second.enabled );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MSource::iterator iterator_source;

				for(iterator_source = data.get()->map_sources.begin(); iterator_source != data.get()->map_sources.end(); iterator_source ++)
				{
					if(*iterator_list == iterator_source->second.enabled)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_sources.begin(); iterator_dublicate != sorted_sources.end(); iterator_dublicate ++)
						{
							if(iterator_source->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_sources.end())
                            break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_source != data.get()->map_sources.end())
					sorted_sources.push_back( iterator_source->first );
			}
		}



		//-- если необходимо отсортировать по NOTES --//
		if(Type == eNOTES)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MSource::iterator iterator_source = data.get()->map_sources.begin(); iterator_source != data.get()->map_sources.end(); iterator_source ++)
			{
				string_list.push_back( iterator_source->second.notes );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MSource::iterator iterator_source;

				for(iterator_source = data.get()->map_sources.begin(); iterator_source != data.get()->map_sources.end(); iterator_source ++)
				{
					if(*iterator_list == iterator_source->second.notes)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_sources.begin(); iterator_dublicate != sorted_sources.end(); iterator_dublicate ++)
						{
							if(iterator_source->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_sources.end())
                            break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_source != data.get()->map_sources.end())
					sorted_sources.push_back( iterator_source->first );
			}
		}


		//-- изменение индексов в векторе на обратный в зависимости от параметра сортироки от А до Я --//
		if(!TypeInd)
			std::reverse(sorted_sources.begin(), sorted_sources.end());

        //-- обновление данных с параметрами сортировки --//
		UpdateWithSortParam();
	}


	//-- функция сортировки валют --//
	void TData::SortCurrencys(const unsigned int Type, bool TypeInd)
	{
		//-- очистка вектора и индексами --//
		sorted_currencys.clear();

		//-- очистка листинга --//
		string_list.clear();


		//-- если необходимо отсортировать по ID --//
		if(Type == eID)
		{
			for(MCurrency::iterator iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
			{
				sorted_currencys.push_back(iterator_currency->first);
			}
		}


		//-- если необходимо отсортировать по NAME --//
		if(Type == eNAME)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MCurrency::iterator iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
			{
				string_list.push_back( iterator_currency->second.name );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MCurrency::iterator iterator_currency;

				for(iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
				{
					if(*iterator_list == iterator_currency->second.name)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_currencys.begin(); iterator_dublicate != sorted_currencys.end(); iterator_dublicate ++)
						{
							if(iterator_currency->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_currencys.end())
                            break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_currency != data.get()->map_currencys.end())
					sorted_currencys.push_back( iterator_currency->first );
			}
		}


		//-- если необходимо отсортировать по SHORT --//
		if(Type == eSHORTN)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MCurrency::iterator iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
			{
				string_list.push_back( iterator_currency->second.shortn );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MCurrency::iterator iterator_currency;

				for(iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
				{
					if(*iterator_list == iterator_currency->second.shortn)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_currencys.begin(); iterator_dublicate != sorted_currencys.end(); iterator_dublicate ++)
						{
							if(iterator_currency->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_currencys.end())
                            break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_currency != data.get()->map_currencys.end())
					sorted_currencys.push_back( iterator_currency->first );
			}
		}


		//-- если необходимо отсортировать по FEE --//
		if(Type == eFEE)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MCurrency::iterator iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
			{
				string_list.push_back( iterator_currency->second.fee );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MCurrency::iterator iterator_currency;

				for(iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
				{
					if(*iterator_list == iterator_currency->second.fee)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_currencys.begin(); iterator_dublicate != sorted_currencys.end(); iterator_dublicate ++)
						{
							if(iterator_currency->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_currencys.end())
                            break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_currency != data.get()->map_currencys.end())
					sorted_currencys.push_back( iterator_currency->first );
			}
		}


		//-- если необходимо отсортировать по MINSUM --//
		if(Type == eMINSUM)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MCurrency::iterator iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
			{
				string_list.push_back( iterator_currency->second.minSum );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MCurrency::iterator iterator_currency;

				for(iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
				{
					if(*iterator_list == iterator_currency->second.minSum)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_currencys.begin(); iterator_dublicate != sorted_currencys.end(); iterator_dublicate ++)
						{
							if(iterator_currency->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_currencys.end())
                            break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_currency != data.get()->map_currencys.end())
					sorted_currencys.push_back( iterator_currency->first );
			}
		}

		//-- если необходимо отсортировать по BASE --//
		if(Type == eBASE)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MCurrency::iterator iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
			{
				string_list.push_back( iterator_currency->second.base );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MCurrency::iterator iterator_currency;

				for(iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
				{
					if(*iterator_list == iterator_currency->second.base)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_currencys.begin(); iterator_dublicate != sorted_currencys.end(); iterator_dublicate ++)
						{
							if(iterator_currency->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_currencys.end())
                            break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_currency != data.get()->map_currencys.end())
					sorted_currencys.push_back( iterator_currency->first );
			}
		}


		//-- если необходимо отсортировать по ENABLED --//
		if(Type == eENABLED)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MCurrency::iterator iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
			{
				string_list.push_back( iterator_currency->second.enabled );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MCurrency::iterator iterator_currency;

				for(iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
				{
					if(*iterator_list == iterator_currency->second.enabled)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_currencys.begin(); iterator_dublicate != sorted_currencys.end(); iterator_dublicate ++)
						{
							if(iterator_currency->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_currencys.end())
                            break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_currency != data.get()->map_currencys.end())
					sorted_currencys.push_back( iterator_currency->first );
			}
		}


		//-- если необходимо отсортировать по NOTES --//
		if(Type == eNOTES)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MCurrency::iterator iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
			{
				string_list.push_back( iterator_currency->second.notes );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MCurrency::iterator iterator_currency;

				for(iterator_currency = data.get()->map_currencys.begin(); iterator_currency != data.get()->map_currencys.end(); iterator_currency ++)
				{
					if(*iterator_list == iterator_currency->second.notes)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_currencys.begin(); iterator_dublicate != sorted_currencys.end(); iterator_dublicate ++)
						{
							if(iterator_currency->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_currencys.end())
							break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_currency != data.get()->map_currencys.end())
					sorted_currencys.push_back( iterator_currency->first );
			}
		}


        //-- изменение индексов в векторе на обратный в зависимости от параметра сортироки от А до Я --//
		if(!TypeInd)
			std::reverse(sorted_currencys.begin(), sorted_currencys.end());

        //-- обновление данных с параметрами сортировки --//
		UpdateWithSortParam();
	}


    //-- функция сортировки линий --//
	void TData::SortLines(const unsigned int Type, bool TypeInd)
	{
		//-- очистка вектора и индексами --//
		sorted_lines.clear();

		//-- очистка листинга --//
		string_list.clear();

		//-- обновление данных с параметрами сортировки --//
		UpdateWithSortParam();

		//-- если необходимо отсортировать по ID --//
		if(Type == eID)
		{
			for(MLine::iterator iterator_line = data.get()->map_lines.begin(); iterator_line != data.get()->map_lines.end(); iterator_line ++)
			{
				sorted_lines.push_back(iterator_line->first);
			}
		}


		//-- если необходимо отсортировать по NAME --//
		if(Type == eNAME)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MLine::iterator iterator_line = data.get()->map_lines.begin(); iterator_line != data.get()->map_lines.end(); iterator_line ++)
			{
				string_list.push_back( iterator_line->second.name );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MLine::iterator iterator_line;

				for(iterator_line = data.get()->map_lines.begin(); iterator_line != data.get()->map_lines.end(); iterator_line ++)
				{
					if(*iterator_list == iterator_line->second.name)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_lines.begin(); iterator_dublicate != sorted_lines.end(); iterator_dublicate ++)
						{
							if(iterator_line->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_lines.end())
							break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_line != data.get()->map_lines.end())
					sorted_lines.push_back( iterator_line->first );
			}
		}


		//-- если необходимо отсортировать по ENABLED --//
		if(Type == eENABLED)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MLine::iterator iterator_line = data.get()->map_lines.begin(); iterator_line != data.get()->map_lines.end(); iterator_line ++)
			{
				string_list.push_back( iterator_line->second.enabled );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MLine::iterator iterator_line;

				for(iterator_line = data.get()->map_lines.begin(); iterator_line != data.get()->map_lines.end(); iterator_line ++)
				{
					if(*iterator_list == iterator_line->second.enabled)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_lines.begin(); iterator_dublicate != sorted_lines.end(); iterator_dublicate ++)
						{
							if(iterator_line->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_lines.end())
							break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_line != data.get()->map_lines.end())
					sorted_lines.push_back( iterator_line->first );
			}
		}


		//-- изменение индексов в векторе на обратный в зависимости от параметра сортироки от А до Я --//
		if(!TypeInd)
			std::reverse(sorted_lines.begin(), sorted_lines.end());
	}



    //-- функция сортировки коррекций --//
	void TData::SortCorrections(const unsigned int Type, bool TypeInd)
	{
		//-- очистка вектора и индексами --//
		sorted_corrections.clear();

		//-- очистка листинга --//
		string_list.clear();


		//-- если необходимо отсортировать по ID --//
		if(Type == eID)
		{
			for(MCorrection::iterator iterator_correction = data.get()->map_corrections.begin(); iterator_correction != data.get()->map_corrections.end(); iterator_correction ++)
			{
				sorted_corrections.push_back(iterator_correction->first);
			}
		}


		//-- если необходимо отсортировать по SOURCE --//
		if(Type == eSOURCE)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MCorrection::iterator iterator_correction = data.get()->map_corrections.begin(); iterator_correction != data.get()->map_corrections.end(); iterator_correction ++)
			{
				if( data.get()->map_sources.find( iterator_correction->second.sourceId.ToInt() ) != data.get()->map_sources.end() )
					string_list.push_back( data.get()->map_sources.find( iterator_correction->second.sourceId.ToInt() )->second.name );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MCorrection::iterator iterator_correction;

				for(iterator_correction = data.get()->map_corrections.begin(); iterator_correction != data.get()->map_corrections.end(); iterator_correction ++)
				{
					if( data.get()->map_sources.find( iterator_correction->second.sourceId.ToInt() ) != data.get()->map_sources.end() )
					{
                        if(*iterator_list == data.get()->map_sources.find( iterator_correction->second.sourceId.ToInt() )->second.name)
						{
							//-- проверка на добавление уже добавленного идентификатора --//
							std::vector< int >::iterator iterator_dublicate;

							for(iterator_dublicate = sorted_corrections.begin(); iterator_dublicate != sorted_corrections.end(); iterator_dublicate ++)
							{
								if(iterator_correction->first == *iterator_dublicate)
									break;
							}

							if(iterator_dublicate == sorted_corrections.end())
								break;
						}
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_correction != data.get()->map_corrections.end())
					sorted_corrections.push_back( iterator_correction->first );
			}
		}


		//-- если необходимо отсортировать по CURROUT --//
		if(Type == eCURROUT)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MCorrection::iterator iterator_correction = data.get()->map_corrections.begin(); iterator_correction != data.get()->map_corrections.end(); iterator_correction ++)
			{
				if( data.get()->map_currencys.find( iterator_correction->second.currOut.ToInt() ) != data.get()->map_currencys.end() )
					string_list.push_back( data.get()->map_currencys.find( iterator_correction->second.currOut.ToInt() )->second.name );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MCorrection::iterator iterator_correction;

				for(iterator_correction = data.get()->map_corrections.begin(); iterator_correction != data.get()->map_corrections.end(); iterator_correction ++)
				{
					if( data.get()->map_currencys.find( iterator_correction->second.currOut.ToInt() ) != data.get()->map_currencys.end() )
					{
                        if(*iterator_list == data.get()->map_currencys.find( iterator_correction->second.currOut.ToInt() )->second.name)
						{
							//-- проверка на добавление уже добавленного идентификатора --//
							std::vector< int >::iterator iterator_dublicate;

							for(iterator_dublicate = sorted_corrections.begin(); iterator_dublicate != sorted_corrections.end(); iterator_dublicate ++)
							{
								if(iterator_correction->first == *iterator_dublicate)
									break;
							}

							if(iterator_dublicate == sorted_corrections.end())
								break;
						}
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_correction != data.get()->map_corrections.end())
					sorted_corrections.push_back( iterator_correction->first );
			}
		}


		//-- если необходимо отсортировать по CURRIN --//
		if(Type == eCURRIN)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MCorrection::iterator iterator_correction = data.get()->map_corrections.begin(); iterator_correction != data.get()->map_corrections.end(); iterator_correction ++)
			{
				if( data.get()->map_currencys.find( iterator_correction->second.currIn.ToInt() ) != data.get()->map_currencys.end() )
					string_list.push_back( data.get()->map_currencys.find( iterator_correction->second.currIn.ToInt() )->second.name );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MCorrection::iterator iterator_correction;

				for(iterator_correction = data.get()->map_corrections.begin(); iterator_correction != data.get()->map_corrections.end(); iterator_correction ++)
				{
					if( data.get()->map_currencys.find( iterator_correction->second.currIn.ToInt() ) != data.get()->map_currencys.end() )
					{
                        if(*iterator_list == data.get()->map_currencys.find( iterator_correction->second.currIn.ToInt() )->second.name)
						{
							//-- проверка на добавление уже добавленного идентификатора --//
							std::vector< int >::iterator iterator_dublicate;

							for(iterator_dublicate = sorted_corrections.begin(); iterator_dublicate != sorted_corrections.end(); iterator_dublicate ++)
							{
								if(iterator_correction->first == *iterator_dublicate)
									break;
							}

							if(iterator_dublicate == sorted_corrections.end())
								break;
						}
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_correction != data.get()->map_corrections.end())
					sorted_corrections.push_back( iterator_correction->first );
			}
		}


		//-- если необходимо отсортировать по FEE --//
		if(Type == eFEE)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MCorrection::iterator iterator_correction = data.get()->map_corrections.begin(); iterator_correction != data.get()->map_corrections.end(); iterator_correction ++)
			{
				string_list.push_back( iterator_correction->second.fee );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MCorrection::iterator iterator_correction;

				for(iterator_correction = data.get()->map_corrections.begin(); iterator_correction != data.get()->map_corrections.end(); iterator_correction ++)
				{
					if(*iterator_list == iterator_correction->second.fee)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_corrections.begin(); iterator_dublicate != sorted_corrections.end(); iterator_dublicate ++)
						{
							if(iterator_correction->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_corrections.end())
							break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_correction != data.get()->map_corrections.end())
					sorted_corrections.push_back( iterator_correction->first );
			}
		}


		//-- если необходимо отсортировать по ENABLED --//
		if(Type == eENABLED)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MCorrection::iterator iterator_correction = data.get()->map_corrections.begin(); iterator_correction != data.get()->map_corrections.end(); iterator_correction ++)
			{
				string_list.push_back( iterator_correction->second.enabled );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MCorrection::iterator iterator_correction;

				for(iterator_correction = data.get()->map_corrections.begin(); iterator_correction != data.get()->map_corrections.end(); iterator_correction ++)
				{
					if(*iterator_list == iterator_correction->second.enabled)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_corrections.begin(); iterator_dublicate != sorted_corrections.end(); iterator_dublicate ++)
						{
							if(iterator_correction->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_corrections.end())
							break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_correction != data.get()->map_corrections.end())
					sorted_corrections.push_back( iterator_correction->first );
			}
		}


		//-- если необходимо отсортировать по NOTES --//
		if(Type == eNOTES)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MCorrection::iterator iterator_correction = data.get()->map_corrections.begin(); iterator_correction != data.get()->map_corrections.end(); iterator_correction ++)
			{
				string_list.push_back( iterator_correction->second.notes );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MCorrection::iterator iterator_correction;

				for(iterator_correction = data.get()->map_corrections.begin(); iterator_correction != data.get()->map_corrections.end(); iterator_correction ++)
				{
					if(*iterator_list == iterator_correction->second.notes)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_corrections.begin(); iterator_dublicate != sorted_corrections.end(); iterator_dublicate ++)
						{
							if(iterator_correction->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_corrections.end())
							break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_correction != data.get()->map_corrections.end())
					sorted_corrections.push_back( iterator_correction->first );
			}
		}


        //-- изменение индексов в векторе на обратный в зависимости от параметра сортироки от А до Я --//
		if(!TypeInd)
			std::reverse(sorted_corrections.begin(), sorted_corrections.end());
	}


    //-- функция сортировки арбитражей --//
	void TData::SortArbitrations(const unsigned int Type, bool TypeInd)
	{
        //-- очистка вектора и индексами --//
		sorted_arbitrations.clear();

		//-- очистка листинга --//
		string_list.clear();


		//-- если необходимо отсортировать по ID --//
		if(Type == eID)
		{
			for(MArbitration::iterator iterator_arbitration = data.get()->map_arbitrations.begin(); iterator_arbitration != data.get()->map_arbitrations.end(); iterator_arbitration ++)
			{
				sorted_arbitrations.push_back(iterator_arbitration->first);
			}
		}


		//-- если необходимо отсортировать по FACTOR --//
		if(Type == eFACTOR)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MArbitration::iterator iterator_arbitration = data.get()->map_arbitrations.begin(); iterator_arbitration != data.get()->map_arbitrations.end(); iterator_arbitration ++)
			{
				string_list.push_back( iterator_arbitration->second.factor );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MArbitration::iterator iterator_arbitration;

				for(iterator_arbitration = data.get()->map_arbitrations.begin(); iterator_arbitration != data.get()->map_arbitrations.end(); iterator_arbitration ++)
				{
					if(*iterator_list == iterator_arbitration->second.factor)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_arbitrations.begin(); iterator_dublicate != sorted_arbitrations.end(); iterator_dublicate ++)
						{
							if(iterator_arbitration->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_arbitrations.end())
							break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_arbitration != data.get()->map_arbitrations.end())
					sorted_arbitrations.push_back( iterator_arbitration->first );
			}
		}


		//-- если необходимо отсортировать по LINE --//
		if(Type == eLINE)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MArbitration::iterator iterator_arbitration = data.get()->map_arbitrations.begin(); iterator_arbitration != data.get()->map_arbitrations.end(); iterator_arbitration ++)
			{
				if( data.get()->map_lines.find( iterator_arbitration->second.line.ToInt() ) != data.get()->map_lines.end() )
					string_list.push_back( data.get()->map_lines.find( iterator_arbitration->second.line.ToInt() )->second.name );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MArbitration::iterator iterator_arbitration;

				for(iterator_arbitration = data.get()->map_arbitrations.begin(); iterator_arbitration != data.get()->map_arbitrations.end(); iterator_arbitration ++)
				{
					if( data.get()->map_lines.find( iterator_arbitration->second.line.ToInt() ) != data.get()->map_lines.end() )
					{
                        if(*iterator_list == data.get()->map_lines.find( iterator_arbitration->second.line.ToInt() )->second.name)
						{
							//-- проверка на добавление уже добавленного идентификатора --//
							std::vector< int >::iterator iterator_dublicate;

							for(iterator_dublicate = sorted_arbitrations.begin(); iterator_dublicate != sorted_arbitrations.end(); iterator_dublicate ++)
							{
								if(iterator_arbitration->first == *iterator_dublicate)
									break;
							}

							if(iterator_dublicate == sorted_arbitrations.end())
								break;
						}
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_arbitration != data.get()->map_arbitrations.end())
					sorted_arbitrations.push_back( iterator_arbitration->first );
			}
		}



		//-- если необходимо отсортировать по TIME --//
		if(Type == eTIME)
		{
			//-- добавление всех имён в листинг с функцией сортировки --//
			for(MArbitration::iterator iterator_arbitration = data.get()->map_arbitrations.begin(); iterator_arbitration != data.get()->map_arbitrations.end(); iterator_arbitration ++)
			{
				string_list.push_back( iterator_arbitration->second.time );
			}


			//-- сортировка данных --//
			std::sort(string_list.begin(), string_list.end());


			for(std::vector< UnicodeString >::iterator iterator_list = string_list.begin(); iterator_list != string_list.end(); iterator_list ++)
			{
				MArbitration::iterator iterator_arbitration;

				for(iterator_arbitration = data.get()->map_arbitrations.begin(); iterator_arbitration != data.get()->map_arbitrations.end(); iterator_arbitration ++)
				{
					if(*iterator_list == iterator_arbitration->second.time)
					{
						//-- проверка на добавление уже добавленного идентификатора --//
						std::vector< int >::iterator iterator_dublicate;

						for(iterator_dublicate = sorted_arbitrations.begin(); iterator_dublicate != sorted_arbitrations.end(); iterator_dublicate ++)
						{
							if(iterator_arbitration->first == *iterator_dublicate)
								break;
						}

						if(iterator_dublicate == sorted_arbitrations.end())
							break;
					}
				}

				//-- добавление отсортированого элемента в вектор индексов --//
				if(iterator_arbitration != data.get()->map_arbitrations.end())
					sorted_arbitrations.push_back( iterator_arbitration->first );
			}
		}


        //-- изменение индексов в векторе на обратный в зависимости от параметра сортироки от А до Я --//
		if(!TypeInd)
			std::reverse(sorted_arbitrations.begin(), sorted_arbitrations.end());
	}


	//-- функция обновления всех данных в зависимости от типа сортировки --//
	void TData::UpdateWithSortParam()
	{

		//-- ИЗМЕНЕНИЕ ПОРЯДКА ИСТОЧНИКОВ В ЛИНИЯХ В ЗАВИСИМОСТИ ОТ СОРТИРОВКИ --//
		for(MLine::iterator iterator_line = data.get()->map_lines.begin(); iterator_line != data.get()->map_lines.end(); iterator_line ++)
		{
			if(sorted_sources.size())
			{
				//-- переписывание вектора перед изменением --//
				std::vector< int > temp;
				for(std::vector< int >::iterator iterator_sources = iterator_line->second.sources.begin(); iterator_sources != iterator_line->second.sources.end(); iterator_sources ++)
				{
					temp.push_back( *iterator_sources );
				}

				//-- очистка вектора --//
				iterator_line->second.sources.clear();

				//-- изменение порядка в зависимости от типа сортировки --//
				for(std::vector< int >::iterator iterator_sources = sorted_sources.begin(); iterator_sources != sorted_sources.end(); iterator_sources ++)
				{
					std::vector< int >::iterator iterator_find;

					for(iterator_find = temp.begin(); iterator_find != temp.end(); iterator_find ++)
					{
						if(*iterator_find == *iterator_sources)
							break;
					}

					if(iterator_find != temp.end())
					{
						iterator_line->second.sources.push_back( *iterator_find );
					}

				}
			}
		}



		//-- ИЗМЕНЕНИЕ ПОРЯДКА ВАЛЮТ В ЛИНИЯХ В ЗАВИСИМОСТИ ОТ СОРТИРОВКИ --//
		for(MLine::iterator iterator_line = data.get()->map_lines.begin(); iterator_line != data.get()->map_lines.end(); iterator_line ++)
		{
			if(sorted_currencys.size())
			{
				//-- переписывание вектора перед изменением --//
				std::vector< int > temp;
				for(std::vector< int >::iterator iterator_currencys = iterator_line->second.сurrencys.begin(); iterator_currencys != iterator_line->second.сurrencys.end(); iterator_currencys ++)
				{
					temp.push_back( *iterator_currencys );
				}

				//-- очистка вектора --//
				iterator_line->second.сurrencys.clear();

				//-- изменение порядка в зависимости от типа сортировки --//
				for(std::vector< int >::iterator iterator_currencys = sorted_currencys.begin(); iterator_currencys != sorted_currencys.end(); iterator_currencys ++)
				{
					std::vector< int >::iterator iterator_find;

					for(iterator_find = temp.begin(); iterator_find != temp.end(); iterator_find ++)
					{
						if(*iterator_find == *iterator_currencys)
							break;
					}

					if(iterator_find != temp.end())
					{
						iterator_line->second.сurrencys.push_back( *iterator_find );
					}

				}
			}
		}


		//-- ИЗМЕНЕНИЕ ПОРЯДКА БАЗОВЫХ ВАЛЮТ В ЛИНИЯХ В ЗАВИСИМОСТИ ОТ СОРТИРОВКИ --//
		for(MLine::iterator iterator_line = data.get()->map_lines.begin(); iterator_line != data.get()->map_lines.end(); iterator_line ++)
		{
			if(sorted_currencys.size())
			{
				//-- переписывание вектора перед изменением --//
				std::vector< int > temp;
				for(std::vector< int >::iterator iterator_currencys = iterator_line->second.bases.begin(); iterator_currencys != iterator_line->second.bases.end(); iterator_currencys ++)
				{
					temp.push_back( *iterator_currencys );
				}

				//-- очистка вектора --//
				iterator_line->second.bases.clear();

				//-- изменение порядка в зависимости от типа сортировки --//
				for(std::vector< int >::iterator iterator_currencys = sorted_currencys.begin(); iterator_currencys != sorted_currencys.end(); iterator_currencys ++)
				{
					std::vector< int >::iterator iterator_find;

					for(iterator_find = temp.begin(); iterator_find != temp.end(); iterator_find ++)
					{
						if(*iterator_find == *iterator_currencys)
							break;
					}

					if(iterator_find != temp.end())
					{
						iterator_line->second.bases.push_back( *iterator_find );
					}

				}
			}
		}

    }


	//-- функция возврата векторов индексов отсортированых источников --//
	std::vector< int > &TData::GetSortedSources()
	{
		return sorted_sources;
	}

	//-- функция возврата векторов индексов отсортированых валют --//
	std::vector< int > &TData::GetSortedСurrencys()
	{
		return sorted_currencys;
	}

	//-- функция возврата векторов индексов отсортированых линий --//
	std::vector< int > &TData::GetSortedLines()
	{
		return sorted_lines;
    }

	//-- функция возврата векторов индексов отсортированых коррекций --//
	std::vector< int > &TData::GetSortedCorrections()
	{
		return sorted_corrections;
    }

	//-- функция возврата векторов индексов отсортированых арбитражей --//
	std::vector< int > &TData::GetSortedArbitrations()
	{
		return sorted_arbitrations;
    }

};


