#include<vector>

class MyPriority_Queue {
public:
	// 本题中我们的容器使用vector，存储的数据为int类型，如果想支持更多类型，请自行了解C++模板。
	
	/* 
	*  出于封装的考虑，我们应该将容器设置为私有，只允许内部函数对其进行修改，但为了同学们能够
	*  自行定义辅助函数对堆进行操作，本题中的所有成员均为Public变量。
	*  注意Container下标从1开始，这是为了便于求解每个元素的左子树/右子树和父亲
	*/
	struct Data {
		int value, priority;
	};
	std::vector<Data> container;
	int size;


	/*************************** 以下代码为助教提供的函数 ******************************/
	/***************** 请勿修改此类函数，判题机上的函数和本文件中相同 ******************/
	
	MyPriority_Queue(std::vector<Data>arr) {
		size = arr.size();
		container = std::vector<Data>(size+1, { 0,0 });
		for (int i = 0; i < size; i++) {
			container[i + 1] = arr[i];
		}
		
		build_heap();
	}

	MyPriority_Queue() : size(0), container(1, { 0,0 }) {}

	/******************************* 以下代码为待实现函数 ******************************/
	
	/*
	*	函数功能：		调整container中的某一个下标，使得该节点符合堆的特性
	*	函数参数：		
	*					index: 待修改位置的下标
	*	函数返回值：	无
	*/
	void heapify(int index);


	/*
	*	函数功能：		将container中的元素进行重新排序以构成一个堆
	*	函数参数：		无
	*	函数返回值：	无
	*/
	void build_heap();


	/*
	*	函数功能：		向堆中插入一个有特定优先级的元素
	*	函数参数：		
	*					value：		插入元素的值
	*					priority：  插入元素的优先级
	*	函数返回值：	无
	*/
	void push(int value, int priority);

	/*
	*	函数功能：		取走堆中优先级最高的元素，若堆为空，则什么也不做
	*	函数参数：		
	*					无
	*	函数返回值：	无
	*/
	void pop();

	/*
	*	函数功能：		返回堆中优先级最高的元素的值与优先级，若堆为空，则返回-1
	*	函数参数：		
	*					value:	   优先级最高的元素的值
	*					priority： 优先级最高元素的优先级
	*	函数返回值：	如果堆为空，则返回-1，否则返回 0
	*/
	int top(int &value,int &priority);


	/*
	*	函数功能：		检验堆是否为空
	*	函数参数：		无
	*	函数返回值：	如果堆为空，则返回true，否则返回false
	*/
	int empty();
};


// 为了防止大家不熟悉C++结构体外如何实现函数定义，这里提供一个例子

/*

void MyPriority_Queue::heapify(int index) {
	// TODO ：在你的代码里实现这个函数
}

*/