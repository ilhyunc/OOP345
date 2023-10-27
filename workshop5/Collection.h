#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <string>

namespace sdds {
	template<typename T>
	class Collection {
		std::string m_name{};
		T* m_array{};
		size_t m_size{};
		//a pointer to a function that returns void and receives two parameters of type const Collection<T>& and const T& in that order. 함수아님!
		void (*m_observer)(const Collection<T>&, const T&) {};//함수포인터 선언시, <리턴타입>(*함수포인터 변수이름)(파라미터...), 때에따라 Book or Moive observer;
	public:
		Collection(const std::string& name) : m_name(name) {}

		Collection(const Collection& I) = delete;
		Collection(Collection&& I) = delete;
		Collection& operator=(const Collection& other) = delete;
		Collection& operator=(Collection&& other) = delete;
		~Collection()
		 {
			delete[] m_array;
		}


		const std::string& name() const { return m_name; }
		size_t size() const { return m_size; }
		                 //(함수 그 자체를 받아옴)
		void setObserver(void (*observer)(const Collection<T>&, const T&)) { m_observer = observer; }

		Collection<T>& operator+=(const T& item) 
		{
			bool isFound = false;

			if (m_size == 0) 
			{
				m_array = new T[1];
				m_array[m_size] = item;
				m_size++;
			}
			else if (m_size > 0)
			{
				for (size_t i = 0; i < m_size && !isFound; i++)
				{
					if (m_array[i].title() == item.title()) 
					{
						isFound = true;
					}
				}

				if (!isFound) 
				{
					T* temp = m_array;
					m_array = new T[m_size + 1];

					for (size_t i = 0; i < m_size; i++)
					{
						m_array[i] = temp[i];
					}
					m_array[m_size++] = item;
					delete[] temp;

					if (m_observer != nullptr)
					{
						m_observer(*this, item);
					}
				}
			}
			return *this;
		}

		T& operator[](size_t idx) const
		{
			if (idx < 0 || idx >= m_size)
			{
				throw std::out_of_range(std::string("Bad index [") + std::to_string(idx) + std::string("]. Collection has [") + std::to_string(m_size) + std::string("] items."));// std::to_string(idx) = concat
			}
			else 
			{
				return m_array[idx];
			}
		}

		T* operator[](const std::string& title) const
		{
			int isFound = -1;

			for (size_t i = 0; i < m_size && isFound < 0; i++)
			{
				if (m_array[i].title() == title) 
				{
					isFound = i;
				}
			}

			return isFound >= 0 ? &m_array[isFound] : nullptr;
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Collection<T>& collection)
	{
		for (size_t i = 0; i < collection.size(); i++)
		{
			os << collection[i];
		}

		return os;
	}

}

#endif
