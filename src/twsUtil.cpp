#include "twsUtil.h"
#include "debug.h"

// from global installed ibtws
#include "ibtws/EWrapper.h" //IB::TickType
#include "ibtws/Execution.h"
#include "ibtws/Contract.h"

#include <QtCore/QString>
#include <sys/time.h>




int64_t nowInMsecs()
{
	timeval tv;
	int err = gettimeofday( &tv, NULL );
	assert( err == 0 );
	
	const uint64_t now_ms = tv.tv_sec*1000 + tv.tv_usec/1000;
	return now_ms;
}


QString toQString( const std::string &ibString )
{
	QString retVal = QString::fromUtf8(ibString.c_str());
	return retVal;
}


std::string toIBString( const QString &qString )
{
	std::string retVal(qString.toUtf8());
	return retVal;
}


QString ibToString( int tickType) {
	switch ( tickType) {
		case IB::BID_SIZE:                    return "bidSize";
		case IB::BID:                         return "bidPrice";
		case IB::ASK:                         return "askPrice";
		case IB::ASK_SIZE:                    return "askSize";
		case IB::LAST:                        return "lastPrice";
		case IB::LAST_SIZE:                   return "lastSize";
		case IB::HIGH:                        return "high";
		case IB::LOW:                         return "low";
		case IB::VOLUME:                      return "volume";
		case IB::CLOSE:                       return "close";
		case IB::BID_OPTION_COMPUTATION:      return "bidOptComp";
		case IB::ASK_OPTION_COMPUTATION:      return "askOptComp";
		case IB::LAST_OPTION_COMPUTATION:     return "lastOptComp";
		case IB::MODEL_OPTION:                return "modelOptComp";
		case IB::OPEN:                        return "open";
		case IB::LOW_13_WEEK:                 return "13WeekLow";
		case IB::HIGH_13_WEEK:                return "13WeekHigh";
		case IB::LOW_26_WEEK:                 return "26WeekLow";
		case IB::HIGH_26_WEEK:                return "26WeekHigh";
		case IB::LOW_52_WEEK:                 return "52WeekLow";
		case IB::HIGH_52_WEEK:                return "52WeekHigh";
		case IB::AVG_VOLUME:                  return "AvgVolume";
		case IB::OPEN_INTEREST:               return "OpenInterest";
		case IB::OPTION_HISTORICAL_VOL:       return "OptionHistoricalVolatility";
		case IB::OPTION_IMPLIED_VOL:          return "OptionImpliedVolatility";
		case IB::OPTION_BID_EXCH:             return "OptionBidExchStr";
		case IB::OPTION_ASK_EXCH:             return "OptionAskExchStr";
		case IB::OPTION_CALL_OPEN_INTEREST:   return "OptionCallOpenInterest";
		case IB::OPTION_PUT_OPEN_INTEREST:    return "OptionPutOpenInterest";
		case IB::OPTION_CALL_VOLUME:          return "OptionCallVolume";
		case IB::OPTION_PUT_VOLUME:           return "OptionPutVolume";
		case IB::INDEX_FUTURE_PREMIUM:        return "IndexFuturePremium";
		case IB::BID_EXCH:                    return "bidExch";
		case IB::ASK_EXCH:                    return "askExch";
		case IB::AUCTION_VOLUME:              return "auctionVolume";
		case IB::AUCTION_PRICE:               return "auctionPrice";
		case IB::AUCTION_IMBALANCE:           return "auctionImbalance";
		case IB::MARK_PRICE:                  return "markPrice";
		case IB::BID_EFP_COMPUTATION:         return "bidEFP";
		case IB::ASK_EFP_COMPUTATION:         return "askEFP";
		case IB::LAST_EFP_COMPUTATION:        return "lastEFP";
		case IB::OPEN_EFP_COMPUTATION:        return "openEFP";
		case IB::HIGH_EFP_COMPUTATION:        return "highEFP";
		case IB::LOW_EFP_COMPUTATION:         return "lowEFP";
		case IB::CLOSE_EFP_COMPUTATION:       return "closeEFP";
		case IB::LAST_TIMESTAMP:              return "lastTimestamp";
		case IB::SHORTABLE:                   return "shortable";
		case IB::FUNDAMENTAL_RATIOS:          return "fundamentals";
		case IB::RT_VOLUME:                   return "rtVolume";
		case IB::HALTED:                      return "halted";
		default:                          return "unknown";
	}
}


QString ibToString( const IB::Execution& ex )
{
	QString retVal = QString()
		+ "orderId:%1: ,clientId:%2, execId:%3, time:%4, acctNumber:%5, exchange:%6, side:%7, "
		+ "shares:%8, price:%9, permId:%10, liquidation:%11, cumQty:%12, avgPrice:%13";
	retVal = retVal
		.arg(ex.orderId).arg(ex.clientId).arg(toQString(ex.execId)).arg(toQString(ex.time))
		.arg(toQString(ex.acctNumber)).arg(toQString(ex.exchange)).arg(toQString(ex.side))
		.arg(ex.shares).arg(ex.price).arg(ex.permId).arg(ex.liquidation).arg(ex.cumQty).arg(ex.avgPrice);
	return retVal;
}


QString ibToString( const IB::Contract &c, bool showFields )
{
	QString retString;
	retString = showFields ?
		"conId:%1,symbol:%2, secType:%3, expiry:%4, strike:%5, right:%6, multiplier:%7, exchange:%8, currency:%9, localSymbol:%10"
		: "%1,%2,%3,%4,%5,%6,%7,%8,%9,%10";
	retString = retString.arg(c.conId).arg(toQString(c.symbol)).arg(toQString(c.secType))
		.arg(toQString(c.expiry)).arg(c.strike,0,'f',1).arg(toQString(c.right))
		.arg(toQString(c.multiplier)).arg(toQString(c.exchange)).arg(toQString(c.currency))
		.arg(toQString(c.localSymbol));

	return retString;
}


const QString ibExpiryDateFormat("yyyyMMdd");

