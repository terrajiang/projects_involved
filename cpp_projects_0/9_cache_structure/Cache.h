#ifndef _CACHE_H_
#define _CACHE_H_

#include <iostream>
#include <functional>
#include <utility>
#include <stdexcept>


namespace pic10b
{
	template<typename T, std::size_t N, typename ord = std::less<T>>
	class cache
	{
	private:

		ord order;
		T* theCache[N];

	public:

		// typedefs, aliases
		using Type = T;
		using Order = ord;
		
		// nested class
		class const_iterator;



		// dafault constructor
		constexpr cache(const Order& _order = ord()) noexcept
			: order(_order)
		{
			theCache = {};
		}

		
		~cache()							// destructor
		{
			
		}

		constexpr cache(const cache& that)			// copy constructor
			: order(that.order)
		{
			for (std::size_t i = 0; i < N; ++i)
			{
				theCache[i] = that.theCache[i];
			}
		}
		
		constexpr cache(cache&& that) noexcept		// move constructor
			: cache(ord())
		{
			std::swap(order, that.order);
			
			for (std::size_t i = 0; i < N; ++i)
			{
				std::swap(theCache[i], that.theCache[i]);		// swap two caches
			}
		}

		constexpr cache& operator=(cache that)&		// assignment operator
		{
			std::swap(order, that.order);

			for (std::size_t i = 0; i < N; ++i)
			{
				std::swap(theCache[i], that.theCache[i]);		// swap two caches
			}

			return *this; // return the swapped cache 'this'
		}


		template<typename Type>
		constexpr void insert(Type&& _value) // adds lvalue/rvalue
		{
			if (size() > N)
			{
				throw std::logic_error("out of storage!");
			}
			else if (size() == N) // when the cache is full
			{
				Type* tempCache[N] = {}; // to store temporary cache

				for (std::size_t i = 1; i < N; ++i) // for element 1 to end
				{
					tempCache[i - 1] = theCache[i]; // copy the temp cache with first element ignored
				}

				for (std::size_t i = 0; i < N; ++i) // for all copied elements
				{
					theCache[i] = tempCache[i]; // reset the cache
				}

				theCache[size() - 1] = std::forward<Type>(_value); // insert the value into the array
			}
			else // when the cache is not full, can still insert
			{
				theCache[size() - 1] = std::forward<Type>(_value); // insert the value into the array
			}
		}

		//emplace (templated)
		template<typename... Types>
		constexpr void emplace(std::size_t i = 0, Types&&... args)
		{
			theCache[i] = Type(std::forward<Types>(args)...); // pass parameters to make a Type
		}

		constexpr void pop() // remove the oldest one
		{
			if (size() == 0) // when empty
			{
				throw std::logic_error("no mememories to be popped!");
			}
			else // when not empty
			{
				Type* tempCache[N] = {}; // to store temporary cache

				for (std::size_t i = 1; i < N; ++i) // for element 1 to end
				{
					tempCache[i - 1] = theCache[i]; // copy the temp cache with first element ignored
				}

				for (std::size_t i = 0; i < N; ++i) // for all copied elements
				{
					theCache[i] = tempCache[i]; // reset the cache
				}
			}
		}
		

		constexpr const_iterator begin()  const
		{
			return const_iterator(size() - 1, *this); // return most recent iterator
		}

		constexpr const_iterator end() const
		{
			return const_iterator(0, *this); // return most distant iterator
		}


		constexpr std::size_t size() const
		{
			std::size_t theSize = 0; // to count the number of elements

			for (std::size_t i = 0; i < N; ++i) // for all elements in the memory
			{
				if (theCache[i] != nullptr) // when it's not empty
				{
					++theSize; // increase the size count
				}
			}

			return theSize; // return the number of elements filled
		}


		constexpr Type get_low() const
		{
			return theCache[0]; // return the lowest value
		}

		constexpr Type get_high() const
		{
			return theCache[size() - 1]; // return the highest value
		}


		// free function
		friend void print(const cache& _cache)
		{
			for (std::size_t i = 0; i < N; ++i)
			{
				std::cout << _cache.theCache[i] << " ";
			}
		}




		// nested class
		class const_iterator
		{
			friend cache;

			friend constexpr bool operator!=(const const_iterator& left, const const_iterator& right)
			{
				return !((left.value == right.value) && (left.index == right.index) &&
					(left.container == right.container));
			}

		private:

			Type value;///////
			size_t* index;///////
			const cache* container;

		public:

			constexpr const_iterator(size_t* _index, const cache* _cache)
				: index(_index), container(_cache)
			{
				value = container->theCache[index];
			}

			constexpr const_iterator& operator++()				// prefix++ operator
			{
				value = container->theCache[++index]; // go to the next element in the array
			}

			constexpr const_iterator operator++(int unused)		// postfix++ operator
			{
				const_iterator copy(*this); // make a copy for non-increased iterator
				++(*this); // increment

				return copy; // return the non-increased copy
			}


			constexpr const_iterator& operator--()				// prefix-- operator
			{
				value = container->theCache[--index]; // go to the previous element in the array
			}

			constexpr const_iterator operator--(int unused)		// postfix-- operator
			{
				const_iterator copy(*this); // make a copy for non-decreased iterator
				--(*this); // decreased

				return copy; // return the non-decreased copy
			}


			constexpr Type& operator*() const				// dereference operator
			{
				return value; // return the value of stored in the iterator
			}

			constexpr Type* operator->() const				// arrow operator
			{
				return &value; // return the value stored in the iterator
			}

		};

	};
}

#endif