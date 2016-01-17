#include <stdint.h>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <deque>
struct Quote
{
	uint32_t timestamp;
	uint32_t orderid;
	char type;
	char side;
	uint32_t price;
	uint32_t size;
};
struct OrderInfo
{
	uint32_t m_orderId;
	uint32_t m_size;
	uint32_t m_price;
};
struct LevelInfo
{
	std::deque<OrderInfo> m_queue;
	uint32_t m_size;
	uint32_t m_price;
};

class OrderBook 
{
public:
	OrderBook(std::vector<std::vector<std::string>>&);
	void UpdateOrderBook(uint32_t);   // update the orderbook to timestamp
	void PrintOrderBook(uint32_t);    // print the snapshot of the book at timestamp
private:
	void InitQuotes(std::vector<std::vector<std::string>>&);  // initialize quote stream
	void HandleTradeEvent(const Quote&);
	void HandleNewEvent(const Quote&);
	void HandleModifyEvent(const Quote&);
	void HandleDeleteEvent(const Quote&);

	std::vector<Quote> m_quotes;
	std::unordered_map<uint32_t, OrderInfo> m_orderMap;   // <order_id, orderInfo>
	std::deque<LevelInfo> m_bidLevel;
	std::deque<LevelInfo> m_askLevel;
};