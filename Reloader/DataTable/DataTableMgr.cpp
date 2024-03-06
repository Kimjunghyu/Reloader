#include "pch.h"
#include "DataTableMgr.h"
#include "StringTable.h"

DataTableMgr::DataTableMgr()
{
}

DataTableMgr::~DataTableMgr()
{
	Release();
}

void DataTableMgr::Init()
{
	Release();

	DataTable* table = new StringTable(DataTable::Types::String);
	table->Load();
	tables.insert({ DataTable::Types::String, table });//타입이 추가될때마다 위 세줄 추가해서 사용
}

void DataTableMgr::Release()
{
	for (auto pair : tables)
	{
		delete pair.second;
	}
	tables.clear();
}
