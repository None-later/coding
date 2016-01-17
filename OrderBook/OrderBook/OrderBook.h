#include <stdint.h>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>

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
	//OrderInfo(uint32_t id, uint32_t prc, uint32_t sz)
	//	: m_orderId(id), m_price(prc), m_size(sz)
	//{}
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
	void UpdateOrderBook(uint32_t);   // prints the order snapshot at the timestamp
	void PrintOrderBook(uint32_t);    // 
private:
	void InitQuotes(std::vector<std::vector<std::string>>&);  // initialize quote stream
	void HandleTradeEvent(Quote&);
	void HandleNewEvent(Quote&);
	void HandleModifyEvent(Quote);
	void HandleDeleteEvent(Quote);

	std::vector<Quote> m_quotes;
	std::unordered_map<uint32_t, OrderInfo> m_orderMap;   // <order_id, orderInfo>
	std::deque<LevelInfo> m_bidLevel;
	std::deque<LevelInfo> m_askLevel;
};