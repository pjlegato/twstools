/*** tws_client.h -- IB/API TWSClient class
 *
 * Copyright (C) 2010-2018 Ruediger Meier
 * Author:  Ruediger Meier <sweet_f_a@gmx.de>
 * License: BSD 3-Clause, see LICENSE file
 *
 ***/

#ifndef TWS_CLIENT_H
#define TWS_CLIENT_H

#include <string>

#include <twsapi/twsapi_config.h>
#include "config.h"

#ifndef TWSAPI_NO_NAMESPACE
namespace IB {
#endif
	class Contract;
	class ContractDetails;
	class Order;
	class OrderState;
	class Execution;
	class ExecutionFilter;
	class EWrapper;

#if ! defined TWS_ORIG_CLIENT
	class EPosixClientSocket;
#else
	class EReaderOSSignal;
	class EReader;
	class EClientSocket;
#endif
#ifndef TWSAPI_NO_NAMESPACE
}
using namespace IB;
#endif

class TWSClient
{
	public:
		TWSClient( EWrapper *ew );
		~TWSClient();

		bool isConnected() const;

		void selectStuff( int msec );

		/////////////////////////////////////////////////////
		bool connectTWS( const std::string &host, int port, int clientId,
			int ai_family );
		void disconnectTWS();

		int serverVersion();
		std::string TwsConnectionTime();

		void reqMktData( int tickerId, const Contract &contract, const std::string &genericTickList, bool snapshot );
		void cancelMktData( int tickerId );
		void placeOrder( int id, const Contract &contract, const Order &order );
		void cancelOrder( int id );
		void reqOpenOrders();
		void reqAllOpenOrders();
		void reqAutoOpenOrders( bool bAutoBind );
		void reqExecutions(int reqId, const ExecutionFilter& filter);
		void reqAccountUpdates( bool subscribe, const std::string &acctCode );
		void reqIds( int numIds );
		void reqContractDetails( int reqId, const Contract &contract );
		void setServerLogLevel( int logLevel );
		void reqHistoricalData ( int tickerId, const Contract &contract,
			const std::string &endDateTime, const std::string &durationStr,
			const std::string &barSizeSetting, const std::string &whatToShow,
			int useRTH, int formatDate );
		void reqCurrentTime();
		void reqMarketDataType(int marketDataType);
		void reqSecDefOptParams(int reqId, const Contract &c);

// 	private:
		EWrapper* myEWrapper;
#if ! defined TWS_ORIG_CLIENT
		EPosixClientSocket* ePosixClient;
#else
		EReaderOSSignal *eSignal;
		EReader *eReader;
		EClientSocket *ePosixClient;
#endif
};


#endif
