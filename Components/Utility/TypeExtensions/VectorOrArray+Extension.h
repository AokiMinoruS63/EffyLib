/**
 * @file VectorOrArray+Extension.h
 * @brief Vectorに適用出来るForEach, Filter, Map, Reduce処理関数
 * 
 */

#ifndef VECTOR_OR_ARRAY_EXTENSION_H
#define VECTOR_OR_ARRAY_EXTENSION_H

// https://pgon.dev/blog/posts/building-map-filter-and-reduce-in-c-with-templates-and-iterators/

template <typename IteratorType>
using ItemType = typename std::iterator_traits<typename IteratorType::iterator>::value_type;

/**
 * @brief ForEach: Vectorや配列の要素をループで回す
 * 
 * @tparam T ジェネリクス
 * @param items Vector
 * @param forEachCb 適用するメソッド
 */
template <typename IteratorType>
void ForEach(IteratorType &items, std::function<void(ItemType<IteratorType> &item)> forEachCb)
{
    for (typename IteratorType::iterator ptr = items.begin(); ptr != items.end(); ++ptr)
        forEachCb(*ptr);
}
/* ForEachの使用例

std::list<char> chars {'a', 'b', 'c', 'd'};
std::vector<int> nums { 1, 2, 3, 4, 5 };
std::string word { "Hello" };

ForEach<std::list<char>>(chars, [](char &chr){ std::cout << chr << std::endl; });
ForEach<std::vector<int>>(nums, [](int &num) { std::cout << num << std::endl; });
ForEach<std::string>(word,[](char &letter) { std::cout << letter << std::endl; });

*/

/**
 * @brief Map: Vectorや構造体配列の要素からマップを作成する
 * 
 * @tparam T 
 * @tparam T2 
 * @param items 
 * @param mapCb 
 * @return std::vector<T2> 
 */
template <typename IteratorType>
IteratorType Map(IteratorType &items, std::function<ItemType<IteratorType>(ItemType<IteratorType> &item)> mapCb)
{
    IteratorType mappedIterator;
    ForEach<IteratorType>(items, [&mappedIterator, &mapCb](auto &item) { mappedIterator.push_back(mapCb(item)); });
    return mappedIterator;
}
/* Mapの使用例

使用例1:

std::vector<int> nums { 1, 2, 3, 4, 5 };

struct IntContainer
{
    IntContainer(int v): val(v) { }
    int val {0};
};

auto mappedVed = Map<int, IntContainer>(nums, [](int &num) {return IntContainer(num * num); });

使用例2:

std::string word { "Hello" };
auto mappedWord = Map<std::string>(word, [](char &chr) { return static_cast<char>(chr + 1); });

使用例3:

std::map<int,char> items {std::pair<int, char>(5, 'a'), std::pair<int, char>(6, 'b'), std::pair<int, char>(7, 'c')};
ForEach<std::map<int,char>>(items, [](std::pair<int,char> pair){ std::cout << pair.first << ": " << pair.second << std::endl; } );

*/


/**
 * @brief Filter: Vector型を条件で絞り込みしたVectorに返す
 * 
 * @tparam T 
 * @param items 
 * @param filterCb 
 * @return std::vector<T> 
 */
template <typename IteratorType>
IteratorType Filter(IteratorType &items, std::function<bool(ItemType<IteratorType> &item)> filterCb)
{
    IteratorType filteredIterator;
    ForEach<IteratorType>(items, [&filteredIterator, &filterCb](auto &item) { if (filterCb(item)) filteredIterator.push_back(item); });
    return filteredIterator;
}
/* Filterの使用例

class HogeTest {
public:
	HogeTest(int id){this->id = id;}
	~HogeTest(){}
private:
	int id;
};
std::vector<HogeTest> vec;
vec.push_back(HogeTest(3));
vec.push_back(HogeTest(4));
vec.push_back(HogeTest(5));
vec.push_back(HogeTest(6));

Filter(vec, [](HogeTest &item){return item.hoge > 4;});	// HogeTest[5], HogeTest[6]が入る
*/

/**
 * @brief 
 * 
 * @tparam T 
 * @tparam T2 
 * @param items 
 * @param reduceCb 
 * @param start 
 * @return T2 
 */
template<typename T, typename T2>
T2 Reduce(std::vector<T> &items, std::function<T2(T &item, T2 &memo)> reduceCb, const T2 &start)
{
    T2 memo = start;
    ForEach<T>(items, [&memo, &reduceCb](T &item) { memo = reduceCb(item, memo); });
    return memo;
}

/* Reduceの使用例

std::string word { "Hello" };
int wordToNum = Reduce<std::string, int>(word, [](char &chr, int &memo){ return memo + (int)chr; }, 0);
// The above equals exactly 500 🤯

*/


/**
 * @brief std::vectorの要素が空なら**true**
 * 
 * @param vector 
 * @return true 
 * @return false 
 */
template <typename T>
bool IsEmpty(std::vector<T> vector) {
	return vector.size() == 0;
}

#endif