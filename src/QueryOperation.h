//---------------------------------------------------------------------------------------------------------------------------------
// File: OdbcOperation.h
// Contents: ODBC Operation objects called on background thread
// 
// Copyright Microsoft Corporation and contributors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// You may obtain a copy of the License at:
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//---------------------------------------------------------------------------------------------------------------------------------

#pragma once

#include "OdbcOperation.h"

namespace mssql
{
	using namespace std;
	using namespace v8;

	class OdbcConnection;
	class OdbcStatement;
	class BoundDatumSet;

	class QueryOperation : public OdbcOperation
	{
	public:
		QueryOperation(shared_ptr<OdbcConnection> connection, const wstring& query, size_t queryId, bool polling, u_int timeout, Handle<Object> callback);
		bool BindParameters(Handle<Array> & node_params) const;
		// called by BindParameters when an error occurs.  It passes a node.js error to the user's callback.
		bool ParameterErrorToUserCallback(uint32_t param, const char* error) const;
		bool TryInvokeOdbc() override;
		Local<Value> CreateCompletionArg() override;

	protected:
	

		bool polling;
		u_int timeout;
		wstring query;
		shared_ptr<BoundDatumSet> params;
		int output_param_count;
	};
}

