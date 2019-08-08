#pragma once

#include <cassert>

class Counter
{
public:
	Counter() :smartCount(0), weakCount(0) {}
	~Counter() { assert(smartCount == 0); assert(weakCount == 0); }

	long smartCount;
	long weakCount;
};

template<class T>
class SmartPointer
{
public:
	SmartPointer(T* ptr = nullptr) :pointer(ptr)
	{
		if (ptr)
		{
			counter = new Counter();
			counter->smartCount++;
		}
	}

	SmartPointer(const SmartPointer& smartPtr)
	{
		CheckCountersAndDelete();
		pointer = smartPtr.pointer;
		counter = smartPtr.counter;
		if (counter)
		{
			counter->smartCount++;
		}
	}

	SmartPointer(SmartPointer&& smartPtr)
	{
		CheckCountersAndDelete();
		pointer = smartPtr.pointer;
		counter = smartPtr.counter;
	}

	inline ~SmartPointer() { CheckCountersAndDelete(); }

	SmartPointer& operator=(const SmartPointer& smartPtr)
	{
		//Check for self assignment
		assert(pointer != smartPtr.pointer);
		CheckCountersAndDelete();
		counter = smartPtr.counter;
		if (counter)
		{
			counter->smartCount++;
		}
		pointer = smartPtr.pointer;
		return *this;
	}

	SmartPointer& operator=(SmartPointer&& smartPtr)
	{
		//Check for self assignment
		assert(pointer != smartPtr.pointer);
		CheckCountersAndDelete();
		pointer = smartPtr.pointer;
		smartPtr.pointer = nullptr;
		counter = smartPtr.counter;
		smartPtr.counter = nullptr;
		return *this;
	}

	bool operator==(const SmartPointer& smartPtr) const { return pointer == smartPtr.pointer; }
	bool operator!=(const SmartPointer& smartPtr) const { return pointer != smartPtr.pointer; }
	bool operator==(T* ptr) const { return pointer == ptr; }
	bool operator!=(T* ptr) const { return pointer != ptr; }
	bool operator!() const { return pointer == nullptr; }
	T& operator*() const { return *pointer; }
	T* operator->() const { return pointer; }
	T* Get() const { return pointer; }

	void swap(SmartPointer& swapPointer)
	{
		T* tempPointer = swapPointer.pointer;
		Counter* tempCounter = swapPointer.counter;
		swapPointer.pointer = pointer;
		swapPointer.counter = counter;
		pointer = tempPointer;
		counter = tempCounter;
	}

private:
	T*			pointer;
	Counter*	counter;

	void CheckCountersAndDelete()
	{
		if (counter)
		{
			if (counter->weakCount == 0 && counter->smartCount == 1)
			{
				counter->smartCount--;
				delete counter;
				delete pointer;
			}
			else if (counter->smartCount > 1)
			{
				counter->smartCount--;
			}
			else
			{
				delete pointer;
			}
		}
	}
};
