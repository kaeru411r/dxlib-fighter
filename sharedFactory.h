#pragma once
#include<memory>
#include<any>

namespace ike {
	template<class T>
	concept LazyConstractable = requires {std::derived_from<T, class SharedFactory >; };

	template <LazyConstractable <T> >
	class SharedFactory : public std::enable_shared_from_this<T> {

	public:

		virtual void constructor() = 0;
		virtual void constructor(std::any value) {}

		static [[nodiscard]] std::shared_ptr<T> Create(){
			T* p = new T();
			p->constructor();
			y_<T> = T();
			return std::shared_ptr<T>(p);
		}

		static [[nodiscard]] std::shared_ptr<T> Create(std::any value) {
			T* p = new T();
			p->constructor(value);
			return std::shared_ptr<T>(p);
		}

	protected:

		SharedFactory() {};


	};
}