# cyclic-buffer

Шаблон кольцевого буфера для любого типа данных с циклическим итератором.
Приватно наследуется от std::deque чтобы избежать 
неопределенного поведения при использовании неперегруженых
функций

```C++
template <class _T, class _Alloc = std::allocator<_T>>
class cyclic_buffer : private std::deque<_T, _Alloc>
```
**T** Тип хранимых данных<br>
**_Alloc** Аллокатор памяти. По умолчанию std::allocator<T>

Пример использования:
```c++
cyclic_buffer<int> b = { 1,2,3,4,5 };
auto cyter = b.cybegin();
  
int i = 0; // не забудьте счетчик, иначе проход по буферу будет бесконечный

while (i < 15)
{
  (*cyter)++; //инкрементируем значения в контейнере.
	cout << *(cyter++) << " "; //выводим в консоль
	i++;
}
cout << endl; // результат: 1 2 3 4 5 2 3 4 5 6 3 4 5 6 7
```
 
