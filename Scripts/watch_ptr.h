#pragma once

#include <forward_list>

using namespace std;

namespace KrostganEngine {

	class watch_ptr;
	class watch_ptr_handler;
	class watch_ptr_handler_c;
	class w_ptr_observable;

	template <typename T> class watch_ptr_handler_wr;
	template <typename T> class watch_ptr_handler_wr_c;



	class watch_ptr final{

	private:
		w_ptr_observable* target;
		unsigned int		handlerCount = 0;

	protected:
		watch_ptr(w_ptr_observable& target)
			:target(&target) {
		}

	public:
		watch_ptr_handler&			GetPtrHandler();
		watch_ptr_handler_c&		GetPtrHandler_c();
		void						Reset();

		w_ptr_observable*			GetPtr() const {
			return target;
		}
		w_ptr_observable const*		GetPtr_c() const {
			return target;
		}

		/// <summary>
		/// Return casted pointer of watch_ptr's target
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template <typename T>
		T* GetPtr_t() const {
			return dynamic_cast<T*>(target);
		}
		/// <summary>
		/// Return constant casted pointer of watch_ptr's target
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template <typename T>
		T const* GetPtr_t_c() const {
			return dynamic_cast<T const*>(target);
		}
		template <typename T>
		watch_ptr_handler_wr<T>& GetWPtrHandler_t() {
			return new watch_ptr_handler_wr<T>(&this);
		}
		template <typename T>
		watch_ptr_handler_wr_c<T>& GetWPtrHandler_t_c() {
			return new watch_ptr_handler_wr_c<T>(&this);
		}

		~watch_ptr() {}

	private:
		friend class watch_ptr_handler;
		friend class w_ptr_observable;
	};

	class watch_ptr_handler {
	public:
		watch_ptr_handler(watch_ptr& Owner);
		watch_ptr_handler(const watch_ptr_handler& Copy);
		virtual ~watch_ptr_handler();

	protected:
		watch_ptr& Owner;

	public:
		/// <summary>
		/// Return casted pointer of watch_ptr's target
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template <typename T>
		T* GetPtr() const {
			return Owner.GetPtr_t<T>();
		}
		/// <summary>
		/// Return casted constant pointer of watch_ptr's target
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template <typename T>
		T const* GetPtr_c() const {
			return Owner.GetPtr_t_c<T>();
		}

	private:
		friend class w_ptr_observable;
	};

	/// <summary>
	/// Wrapper of watch_ptr_handler that allowed to get constant pointer only
	/// </summary>
	class watch_ptr_handler_c final : public watch_ptr_handler {
	public:
		watch_ptr_handler_c(watch_ptr& Owner);
		watch_ptr_handler_c(const watch_ptr_handler& Copy);
		watch_ptr_handler_c(const watch_ptr_handler_c& Copy);


		template <typename T>
		T const* GetPtr() const {
			return Owner.GetPtr_t_c<T>();
		}
	};

	/// <summary>
	/// !!!WARNING!!! To get watch_ptr_handler of w_ptr_observable ref to w_ptr_observable couldn't be const, because with getting 
	/// watch_ptr_handler it's internal counter is incremented
	/// It will be fixed in a next updates.
	/// </summary>
	class w_ptr_observable {

	protected:
		w_ptr_observable()
			: W_ptr(*new watch_ptr(*this)) {}

	public:
		watch_ptr_handler& GetPtr() {
			return W_ptr.GetPtrHandler();
		}
		watch_ptr_handler_c& GetPtr_c() const{
			return W_ptr.GetPtrHandler_c();
		}

		virtual ~w_ptr_observable() {
			W_ptr.Reset();
		}

	private:
		watch_ptr& W_ptr;
	};

	//Template wrapers

	template<typename T>
	class watch_ptr_handler_wr : public watch_ptr_handler {

	public:
		watch_ptr_handler_wr(watch_ptr& Owner) : watch_ptr_handler(Owner)
		{}
		watch_ptr_handler_wr(const watch_ptr_handler& Copy) : watch_ptr_handler(Copy)
		{}

		T* GetPtr_t()  const {
			return Owner.GetPtr_t<T>();
		}
		T const* GetPtr_t_c() const {
			return Owner.GetPtr_t_c<T>();
		}
	};

	template<typename T>
	class watch_ptr_handler_wr_c final : public watch_ptr_handler_wr<T> {

	public:
		watch_ptr_handler_wr_c(watch_ptr& Owner) : watch_ptr_handler_wr<T>(Owner)
		{}
		watch_ptr_handler_wr_c(const watch_ptr_handler& Copy) : watch_ptr_handler_wr<T>(Copy)
		{}
		watch_ptr_handler_wr_c(const watch_ptr_handler_c& Copy) : watch_ptr_handler_wr<T>(Copy)
		{}

		T const* GetPtr_t() const {
			return watch_ptr_handler_wr<T>::GetPtr_t();
		}

	};
}