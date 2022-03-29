#pragma once

#include <deque>
#include <functional>
#include <iterator>
/**
* ������ ������������ ���������. ���������� ����������.
* \param Iterator ��� ���������.
* \param T ��� ������.
* 
*/
template <typename T, typename Iterator>
class _Cyclic_Iterator : public std::iterator <std::bidirectional_iterator_tag, T, ptrdiff_t>
{
	Iterator   _cursor; /// ������� ������� � ����������
	Iterator   _begin;  /// ������ ����������
	Iterator   _end;    /// ����� ����������

public:
	typedef typename Iterator::value_type value_type;
	using reference = value_type&;

	_Cyclic_Iterator() = delete;

	/**
	* �����������
	* \param[in] begin ������ ����������.
	* \param[in] end ����� ����������.
	*/
	_Cyclic_Iterator(const Iterator& begin, const Iterator& end) : _cursor(begin), _begin(begin), _end(end) {}

	bool operator == (const _Cyclic_Iterator& i) const{
		return _cursor == i._cursor;
	}

	bool operator != (const _Cyclic_Iterator& i) const{
		return !(*this == i);
	}

	reference operator*() const{
		return *_cursor;
	}

	/**
	* ������������� ���������. ���� ��������� ����� - ��������� � ������ ������.
	* ����� ������� ������ �� ������ ����� �����������.
	* 
	* ��������� ����������� ���:
	* \code
	*   auto i = container.cybegin()
	*   while(i != container.end()) //����������� ����
	*   {
	*     ...
	*     i++;
	*	}
	* \endcode
	* 
	*/
	_Cyclic_Iterator& operator++(){
		++_cursor;
		if (_cursor == _end)
			_cursor = _begin;
		return *this;
	}

	_Cyclic_Iterator operator++(int){
		_Cyclic_Iterator i = *this;
		++*this;
		return i;
	}

	_Cyclic_Iterator& operator--(){
		if (_cursor == _begin)
			_cursor = _end;
		--_cursor;
		return *this;
	}

	_Cyclic_Iterator operator--(int){
		_Cyclic_Iterator i = *this;
		--*this;
		return i;
	}
};


/**
* ������ ���������� ������ ��� ������ ���� ������.
* �������� ����������� �� std::deque ����� �������� 
* ��������������� ��������� ��� ������������� ��������������
* �������
* 
* \param T ��� �������� ������
* \param _Alloc ��������� ������. �� ��������� std::allocator<T>
* 
* ������ �������������:
* \code
*   cyclic_buffer<int> b = { 1,2,3,4,5 };
*   auto cyter = b.cybegin();
* 
*   int i = 0; // �� �������� �������, ����� ������ �� ������ ����� �����������
*	auto cyter = b.cybegin();
*	while (i < 15)
*	{
*       (*cyter)++; //�������������� �������� � ����������.
*		cout << *(cyter++) << " "; //������� � �������
*		i++;
*	}
*	cout << endl; // ���������: 1 2 3 4 5 2 3 4 5 6 3 4 5 6 7
* \endcode
* 
* 
* 
*/
template <class _T, class _Alloc = std::allocator<_T>>
class cyclic_buffer : private std::deque<_T, _Alloc>
{
public:
	// ��� ��� ����� ��� ������������� �� ������������ ��������� STL ����� � deque
	typedef std::deque<_T, _Alloc>			  deque;

	typedef _T                                        value_type;
	typedef size_t                                    size_type;
	typedef typename deque::pointer                   pointer;
	typedef typename deque::const_pointer             const_pointer;
	typedef typename deque::reference                 reference;
	typedef typename deque::const_reference           const_reference;
	typedef typename deque::iterator                  iterator;
	typedef typename deque::const_iterator            const_iterator;
	typedef _Alloc                                    allocator_type;
	typedef _Cyclic_Iterator<_T, iterator>            cyclic_iterator;

	// � ������������� � � ���������� ������� ����������� ������������ ������ ����������.
	// 
	cyclic_buffer() : deque(), _max_size(0) {}
	virtual ~cyclic_buffer() {}

	cyclic_buffer(std::initializer_list<_T> _Ilist, const _Alloc& _Al = allocator_type()) : deque(_Ilist, _Al) {
		_max_size = std::distance(_Ilist.begin(), _Ilist.end());
	}

	explicit cyclic_buffer(size_type _Count, const _Alloc& _Al = _Alloc()) : deque(_Count, _Al) {
		_max_size = _Count;
	}

	template <class _Iter, typename = std::_RequireInputIter<_Iter> >
	cyclic_buffer(_Iter _First, _Iter _Last) : deque(_First, _Last) {
		_max_size = std::distance(_First, _Last);
	}

	cyclic_buffer& operator=(std::initializer_list<_T> _Ilist) {
		_max_size = std::distance(_Ilist.begin(), _Ilist.end());
		return deque::operator=(_Ilist);
	}

	size_type size() const noexcept {
		return deque::size();
	}

	size_type max_size() const noexcept {
		return _max_size;
	}

	void push_front(_T&& _Val) {
		deque::push_front(_Val);
		_fit_size(std::bind(&cyclic_buffer::pop_back, this));
	}

	void push_front(const _T& _Val) {
		deque::push_front(_Val);
		_fit_size(std::bind(&cyclic_buffer::pop_back, this));
	}

	void push_back(_T&& _Val) {
		deque::push_back(_Val);
		_fit_size(std::bind(&cyclic_buffer::pop_front, this));
	}

	void push_back(const _T& _Val) {
		deque::push_back(_Val);
		_fit_size(std::bind(&cyclic_buffer::pop_front, this));
	}

	void pop_front() noexcept {
		deque::pop_front();
	}

	void pop_back() noexcept {
		deque::pop_back();
	}

	void clear() noexcept {
		deque::clear();
	}

	iterator begin() noexcept {
		return deque::begin();
	}

	const_iterator begin() const noexcept {
		return deque::begin();
	}
	
	cyclic_iterator cybegin() noexcept {
		return cyclic_iterator(begin(), end());
	}

	iterator end() noexcept {
		return deque::end();
	}

	const_iterator end() const noexcept {
		return deque::end();
	}

private:
	size_type _max_size;

	/**
	* ��������� ������ ����������. ���� �� ������ ������������� - ��������� ������� 
	* ���������� ������� ����������.
	* 
	* \param shrink_function[in] ������� ����������� ������ ����������
	*/
	void _fit_size(std::function<void(void)> shrink_function) {
		if (size() > _max_size) {
			shrink_function();
		}
	}

};


template <class _T, class _Alloc>
bool operator==(const cyclic_buffer<_T, _Alloc>& _Left, const cyclic_buffer<_T, _Alloc>& _Right) {
	return _Left.size() == _Right.size()
		&& std::equal(_Left.begin(), _Left.end(), _Right.begin());
}

#if !_HAS_CXX20
template <class _T, class _Alloc>
bool operator!=(const cyclic_buffer<_T, _Alloc>& _Left, const cyclic_buffer<_T, _Alloc>& _Right) {
	return !(_Left == _Right);
}
#endif // !_HAS_CXX20
