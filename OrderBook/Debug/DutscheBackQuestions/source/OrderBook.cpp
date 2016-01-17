#include <iostream>
#include "OrderBook.h"

OrderBook::OrderBook(std::vector<std::vector<std::string>>& csvQuotes)
{
	InitQuotes(csvQuotes);
}
void OrderBook::InitQuotes(std::vector<std::vector<std::string>>& csvQuotes)
{
	for (auto itQuote = csvQuotes.begin(); itQuote != csvQuotes.end(); ++itQuote)
	{
		if ((*itQuote).size() == 6)
		{
			auto it = (*itQuote).begin();
			Quote q;
			q.timestamp = std::atoi((*it).c_str());	 ++it;
			q.orderid   = std::atoi((*it).c_str());  ++it;
			q.type      = *(*it).c_str();			 ++it;
			q.side      = *(*it).c_str();		     ++it;
			q.price     = std::atoi((*it).c_str());  ++it;
			q.size      = std::atoi((*it).c_str());  
			m_quotes.push_back(q);
		}
	}
}
void OrderBook::UpdateOrderBook(uint32_t timestamp)
{
	auto it = m_quotes.begin();
	while(it!= m_quotes.end() && it->timestamp <= timestamp)
	{
		if (it->type == 'N')
		{
			HandleNewEvent(*it);
		}
		if (it->type == 'M')
		{
			HandleModifyEvent(*it);	
		}
		if (it->type == 'D')
		{
			HandleDeleteEvent(*it);	
		}
		++it;
	}
}
void OrderBook::HandleTradeEvent(const Quote& qt)
{
	if (qt.side == 'B')
	{
		// all buy orders get filled  
		if (qt.size <= m_askLevel[0].m_size)
		{
			uint32_t size = qt.size;
			m_askLevel[0].m_size -= size;
			m_orderMap.erase(qt.orderid);

			while (size > 0)
			{
				if (size > m_askLevel[0].m_queue.front().m_size)
				{
					size -= m_askLevel[0].m_queue.front().m_size;
					m_orderMap.erase(m_askLevel[0].m_queue.front().m_orderId);
					m_askLevel[0].m_queue.pop_front();
				}
				else
				{
					m_orderMap[m_askLevel[0].m_queue.front().m_orderId].m_size -= size;
					m_askLevel[0].m_queue.front().m_size -= size;
					size = 0;
				}
			}
		}
		// partial buy orders get filled, the remains become new best bid (up tick move)
		else  
		{
			m_orderMap[qt.orderid].m_size -= m_askLevel[0].m_size;
			LevelInfo newLevel;
			newLevel.m_queue.push_back(m_orderMap[qt.orderid]);
			newLevel.m_size = m_orderMap[qt.orderid].m_size;
			newLevel.m_price = m_orderMap[qt.orderid].m_price;
			m_bidLevel.push_front(newLevel);

			// clean up the all orders at best ask level
			while (!m_askLevel[0].m_queue.empty())	
			{
				m_orderMap.erase(m_askLevel[0].m_queue.front().m_orderId);
				m_askLevel[0].m_queue.pop_front();
			}
			m_askLevel.pop_front();
		}
	}
	else // Sell order get filled
	{
		// all sell orders get filled  
		if (qt.size <= m_bidLevel[0].m_size)
		{
			uint32_t size = qt.size;
			m_bidLevel[0].m_size -= size;
			m_orderMap.erase(qt.orderid);
			
			while (size > 0)
			{
				if (size > m_bidLevel[0].m_queue.front().m_size)
				{
					size -= m_bidLevel[0].m_queue.front().m_size;
					m_orderMap.erase(m_bidLevel[0].m_queue.front().m_orderId);
					m_bidLevel[0].m_queue.pop_front();
				}
				else
				{
					m_orderMap[m_bidLevel[0].m_queue.front().m_orderId].m_size -= size;
					m_bidLevel[0].m_queue.front().m_size -= size;
					size = 0;
				}
			}
		}
		// partial sell orders get filled, the remains become new best ask (down tick move)
		else
		{
			m_orderMap[qt.orderid].m_size -= m_bidLevel[0].m_size;
			LevelInfo newLevel;
			newLevel.m_queue.push_back(m_orderMap[qt.orderid]);
			newLevel.m_size = m_orderMap[qt.orderid].m_size;
			newLevel.m_price = m_orderMap[qt.orderid].m_price;
			m_askLevel.push_front(newLevel);

			// clean up the all orders at best ask level
			while (!m_bidLevel[0].m_queue.empty())	
			{
				m_orderMap.erase(m_bidLevel[0].m_queue.front().m_orderId);
				m_bidLevel[0].m_queue.pop_front();
			}
			m_bidLevel.pop_front();
		}	
	}
}
void OrderBook::HandleNewEvent(const Quote& qt)
{
	OrderInfo order;
	order.m_orderId = qt.orderid;
	order.m_price = qt.price;
	order.m_size = qt.size;
	m_orderMap[qt.orderid] = order;

	if (qt.side == 'B')
	{
		// market order, trade event happens
		if (!m_askLevel.empty() && qt.price >= m_askLevel[0].m_price)
		{
			HandleTradeEvent(qt);
		}
		// push to the front, becomes new best bid
		else if (m_bidLevel.empty() || qt.price > m_bidLevel[0].m_price)
		{
			LevelInfo newLevel;
			newLevel.m_queue.push_back(m_orderMap[qt.orderid]);
			newLevel.m_size = m_orderMap[qt.orderid].m_size;
			newLevel.m_price = m_orderMap[qt.orderid].m_price;
			m_bidLevel.push_front(newLevel);
		}
		// push to the back
		else if (qt.price < m_bidLevel[m_bidLevel.size()-1].m_price)
		{
			LevelInfo newLevel;
			newLevel.m_queue.push_back(m_orderMap[qt.orderid]);
			newLevel.m_size = m_orderMap[qt.orderid].m_size;
			newLevel.m_price = m_orderMap[qt.orderid].m_price;
			m_bidLevel.push_back(newLevel);		
		}
		// search existing levels, if doesn't exist then create a new level
		else  
		{
			for (auto it = m_bidLevel.begin(); it != m_bidLevel.end(); ++it)
			{
				// found the level, join the queue
				if (qt.price == it->m_price)
				{
					it->m_queue.push_back(m_orderMap[qt.orderid]);
					it->m_size += qt.size;
					break;	
				}
				// the level doesn't exist, insert a new level
				if (qt.price > it->m_price)
				{
					LevelInfo newLevel;
					newLevel.m_queue.push_back(m_orderMap[qt.orderid]);
					newLevel.m_size = m_orderMap[qt.orderid].m_size;
					newLevel.m_price = m_orderMap[qt.orderid].m_price;			
					m_bidLevel.insert(it, newLevel);
					break;
				}
			}
		}
	}
	else 
	{
		// market order, trade event happens
		if (!m_bidLevel.empty() && qt.price <= m_bidLevel[0].m_price)
		{
			HandleTradeEvent(qt);
		}
		// push to the front, becomes new best ask
		else if (m_askLevel.empty() || qt.price < m_askLevel[0].m_price)
		{
			LevelInfo newLevel;
			newLevel.m_queue.push_back(m_orderMap[qt.orderid]);
			newLevel.m_size = m_orderMap[qt.orderid].m_size;
			newLevel.m_price = m_orderMap[qt.orderid].m_price;
			m_askLevel.push_front(newLevel);				
		}
		// push to the back
		else if (qt.price > m_askLevel[m_askLevel.size()-1].m_price)
		{
			LevelInfo newLevel;
			newLevel.m_queue.push_back(m_orderMap[qt.orderid]);
			newLevel.m_size = m_orderMap[qt.orderid].m_size;
			newLevel.m_price = m_orderMap[qt.orderid].m_price;
			m_askLevel.push_back(newLevel);				
		}
		// search existing levels, if doesn't exist then create a new level
		else  
		{
			for (auto it = m_askLevel.begin(); it != m_askLevel.end(); ++it)
			{
				// found the level, join the queue
				if (qt.price == it->m_price)
				{
					it->m_queue.push_back(m_orderMap[qt.orderid]);
					it->m_size += qt.size;
					break;	
				}
				// the level doesn't exist, insert a new level
				if (qt.price < it->m_price)
				{
					LevelInfo newLevel;
					newLevel.m_queue.push_back(m_orderMap[qt.orderid]);
					newLevel.m_size = m_orderMap[qt.orderid].m_size;
					newLevel.m_price = m_orderMap[qt.orderid].m_price;			
					m_askLevel.insert(it, newLevel);
					break;
				}
			}		
		}	
	}
}
void OrderBook::HandleModifyEvent(const Quote& qt)
{
	uint32_t oldPrice = m_orderMap[qt.orderid].m_price;
	uint32_t oldSize = m_orderMap[qt.orderid].m_size;
	uint32_t newPrice = qt.price;
	uint32_t newSize = qt.size;
	if (qt.side == 'B')
	{
		// search existing m_bidLevel	
		for (auto level = m_bidLevel.begin(); level != m_bidLevel.end(); ++level)
		{
			if (oldPrice == level->m_price)  // found the level
			{
				// searching the queue of orders 
				for (auto it = level->m_queue.begin(); it != level->m_queue.end(); ++it)
				{
					if (it->m_orderId == qt.orderid)  // found the original order
					{
						// case 1 : price changed, delete currect order and place a new order at other level
						if (newPrice != oldPrice)
						{
							level->m_queue.erase(it);
							level->m_size -= oldSize;
							m_orderMap.erase(qt.orderid);
							HandleNewEvent(qt);
							if (level->m_queue.empty())
								m_bidLevel.erase(level);
						}
						// case 2 : increase the size, delete current order and rejoin the queue from the back
						if (newPrice == oldPrice && newSize > oldSize)
						{
							level->m_queue.erase(it);
							m_orderMap[qt.orderid].m_size = newSize;
							level->m_queue.push_back(m_orderMap[qt.orderid]);
							level->m_size += (newSize - oldSize);
						}
						// case 3 : decrease the size, just modify the size without rejoining the queue
						if (newPrice == oldPrice && newSize < oldSize)
						{
							it->m_size = newSize;
							m_orderMap[qt.orderid].m_size = newSize;
							level->m_size += (newSize - oldSize);
						}
						break;
					}
				}
				break;
			}
		}
	}
	else 
	{
		// search existing m_askLevel	
		for (auto level = m_askLevel.begin(); level != m_askLevel.end(); ++level)
		{
			if (oldPrice == level->m_price)  // found the level
			{
				// searching the queue of orders 
				for (auto it = level->m_queue.begin(); it != level->m_queue.end(); ++it)
				{		
					if (it->m_orderId == qt.orderid)  // found the original order
					{
						// case 1 : price changed, delete currect order and place a new order at other level
						if (newPrice != oldPrice)
						{
							level->m_queue.erase(it);
							level->m_size -= oldSize;
							m_orderMap.erase(qt.orderid);
							HandleNewEvent(qt);
							if (level->m_queue.empty())
								m_askLevel.erase(level);
						}
						// case 2 : increase the size, delete current order and rejoin the queue from the back
						if (newPrice == oldPrice && newSize > oldSize)
						{
							level->m_queue.erase(it);
							m_orderMap[qt.orderid].m_size = newSize;
							level->m_queue.push_back(m_orderMap[qt.orderid]);
							level->m_size += (newSize - oldSize);
						}
						// case 3 : decrease the size, modify current order's size
						if (newPrice == oldPrice && newSize < oldSize)
						{
							it->m_size = newSize;
							m_orderMap[qt.orderid].m_size = newSize;
							level->m_size += (newSize - oldSize);
						}
						break;					
					}
				}
				break;	
			}
		}	
	}
}
void OrderBook::HandleDeleteEvent(const Quote& qt)
{
	//m_orderMap.erase(qt.orderid);
	if (qt.side == 'B')
	{
		// search existing m_bidLevel	
		for (auto level = m_bidLevel.begin(); level != m_bidLevel.end(); ++level)
		{
			if (qt.price == level->m_price)  // found the level
			{
				// searching the queue of orders 
				for (auto it = level->m_queue.begin(); it != level->m_queue.end(); ++it)
				{
					if (it->m_orderId == qt.orderid)  // found the original order
					{
						level->m_queue.erase(it);
						level->m_size -= qt.size;
						m_orderMap.erase(qt.orderid);
						if (level->m_queue.empty())
							m_bidLevel.erase(level);
						break;
					}
				}
				break;
			}
		}
	}
	else 
	{
		// search existing m_askLevel	
		for (auto level = m_askLevel.begin(); level != m_askLevel.end(); ++level)
		{
			if (qt.price == level->m_price)  // found the level
			{
				// searching the queue of orders 
				for (auto it = level->m_queue.begin(); it != level->m_queue.end(); ++it)
				{
					if (it->m_orderId == qt.orderid)  // found the original order
					{
						level->m_queue.erase(it);
						level->m_size -= qt.size;
						m_orderMap.erase(qt.orderid);
						if (level->m_queue.empty())
							m_askLevel.erase(level);
						break;
					}
				}
				break;
			}
		}	
	}
}
void OrderBook::PrintOrderBook(uint32_t timestamp)
{
	UpdateOrderBook(timestamp);
	std::cout << "The book at time : " << timestamp << " is:" << std::endl;
	if (m_askLevel.size() >= 4)
	{
		for (int x = 3; x >= 0; --x)
		{
			std::cout << "Ask[" << x+1 << "] Price: " << m_askLevel[x].m_price << " Size: " << m_askLevel[x].m_size << std::endl;
		}
	}
	else
	{
		if (!m_askLevel.empty())
		{
			for (int x = m_askLevel.size() - 1; x >= 0; --x)
			{
				std::cout << "Ask[" << x+1 << "] Price: " << m_askLevel[x].m_price << " Size: " << m_askLevel[x].m_size << std::endl;
			}
		}
	}
	std::cout << '\n';
	if (m_bidLevel.size() >= 4)
	{
		for (int x = 0; x <= 3; ++x)
		{
			std::cout << "Bid[" << x+1 << "] Price: " << m_bidLevel[x].m_price << " Size: " << m_bidLevel[x].m_size << std::endl;
		}
	}
	else
	{
		if (!m_bidLevel.empty())
		{
			for (int x = 0; x < m_bidLevel.size(); ++x)
			{
				std::cout << "Bid[" << x+1 << "] Price: " << m_bidLevel[x].m_price << " Size: " << m_bidLevel[x].m_size << std::endl;
			}
		}
	}
}
