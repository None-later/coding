template <typename T> 
class QueueItem 
{
	T item; 
	QueueItem* next;
	QueueItem(const T &t) : item(t), next(0) {};
};

template <typename T>
class Queue
{
	QueueItem<T>* head;
	QueueItem<T>* tail;
	void destroy();		// delete all items
	void copy_elems(const Queue &);

	// practive member template to convert different types between templates, pg. 661
	template <typename Iter> void copy_elems(Iter, Iter);

public:
	Queue() : head(0), tail(0) { }
	Queue(const Queue &q) : head(0), tail(0) { copy_elems(q); }
	Queue& operator=(const Queue &);
	~Queue() { destroy(); }

	T& front() { return head->item;	}
	const T& front() { return head->item; }
	void push(const T &);
	void pop();
	bool empty() const { return head == 0; }

	// practive member template to convert different types between templates, pg. 661
	template <typename It> Queue(It beg, It end) : head(0), tail(0) { copy_elems(beg, end); }
	template <typename Iter> void assign(Iter, Iter);
};
