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
	while(it->timestamp <= timestamp)
	{
		// new orderId, add to orderMap
		if (m_orderMap.find(it->orderid) == m_orderMap.end())
		{
			HandleNewEvent(*it);
		}
		// existing orderId, modify or delete
		else 
		{
			if (it->type == 'M')
			{
				uint32_t originPrc = m_orderMap[it->orderid].m_price;
				uint32_t originSz = m_orderMap[it->orderid].m_size;
				// price changed, or both changed 
				if (it->price != originPrc)
				{
					if (it->side == 'B' && !m_askLevel.empty() && it->price >= m_askLevel[0].m_price
					  ||it->side == 'S' && !m_bidLevel.empty() && it->price <= m_bidLevel[0].m_price)
					{
						HandleTradeEvent(*it);	
					}					
					else
						HandleModifyEvent(*it);
				}
				else // size changed
				{
					HandleModifyEvent(*it);	
				}
			}
			if (it->type == 'D')
			{
				m_orderMap.erase(it->orderid);

				HandleDeleteEvent(*it);	
				//if (it->side == 'B')
				//{
				//		
				//}
				//if (it->side == 'S')
				//{
				//
				//}
			}
		}
		++it;
	}
}

void OrderBook::HandleTradeEvent(Quote& qt)
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
void OrderBook::HandleNewEvent(Quote& qt)
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
		else if (qt.price > m_bidLevel[0].m_price)
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
		else if (qt.price < m_askLevel[0].m_price)
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
void OrderBook::HandleModifyEvent(Quote qt)
{
	uint32_t originPrc = m_orderMap[qt.orderid].m_price;
	uint32_t originSz = m_orderMap[qt.orderid].m_size;
	
	// price changed, or both price and size changed 
	//if (qt.price != originPrc)
	//{
	//	if (it->side == 'B' && !m_askLevel.empty() && it->price >= m_askLevel[0].m_price
	//		||it->side == 'S' && !m_bidLevel.empty() && it->price <= m_bidLevel[0].m_price)
	//	{
	//		HandleTradeEvent(*it);	
	//	}					
	//	else
	//		HandleModifyEvent(*it);
	//}
	//else // size changed
	//{
	//	HandleModifyEvent(*it);	
	//}

	if (qt.side == 'B')
	{
		// search existing m_bidLevel	
		for (auto level = m_bidLevel.begin(); level != m_bidLevel.end(); ++level)
		{
			if (originPrc == level->m_price)  // found the level
			{
				level->m_size -= originSz;
				// searching the queue
				for (auto it = level->m_queue.begin(); it != level->m_queue.end(); ++it)
				{
					if (it->m_orderId == qt.orderid)   
					{
						level->m_queue.erase(it);
					}

				}
			}
		}
	}
	else 
	{
		// search existing m_askLevel	
		for (auto level = m_askLevel.begin(); level != m_askLevel.end(); ++level)
		{
			// found the level
			if (originPrc == level->m_price)
			{
				
			}
		}	
	}
}
void OrderBook::HandleDeleteEvent(Quote qt)
{
	if (qt.side == 'B')
	{
	
	}
	else 
	{
	
	}
}
void OrderBook::PrintOrderBook(uint32_t timestamp)
{




	UpdateOrderBook(timestamp);

}
