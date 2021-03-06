#pragma once

#include "Core/Headers/TemplateDefs.h"
#include "Core/Headers/PtrDefs.h"

using namespace std;

namespace Core
{
	namespace Functionality
	{
		// typename T should not be defined there - need to make the type 'T' generic to allow lambdas (and possibly other things?)
		template <typename rT, typename ...Ts>
		struct Function
		{
			struct FunctionImplBase
			{
				virtual rT operator()(Ts... args) = 0;
			};

			template <typename O>
			struct FunctionImpl : FunctionImplBase
			{
				O Object;

				FunctionImpl(O object)
					: Object(move(object))
				{}

				rT operator()(Ts... args)
				{
					return Object(args...);
				}
			};

			SharedPtr<FunctionImplBase> FunctionObject = nullptr;

			Function() = default;

			template <typename O>
			Function(O object)
			{
				FunctionObject = MakeShared<FunctionImpl<O>>(object);
			}

			Function(Function&& function)
			{
				FunctionObject = move(function.FunctionObject);
				function.FunctionObject = nullptr;
			}

			// NOTE: We currently need this to allow use with the std::vector since it requires copy-construction
			// https://en.cppreference.com/w/cpp/container/vector
			// Once we implement our own list we can get rid of this (and not have the FunctionObject be a SharedPtr - since that is terrible)
			Function(const Function& function)
			{
				// do we want it to be set up like this? I don't think so
				FunctionObject = function.FunctionObject;
			}

			~Function()
			{

			}

			rT Call(Ts... args)
			{
				return (*this)(args...);
			}

			operator bool()
			{
				return (FunctionObject != nullptr);
			}

			// NOTE: We currently need this to allow use with the std::vector since it requires copy-construction
			// https://en.cppreference.com/w/cpp/container/vector
			// Once we implement our own list we can get rid of this (and not have the FunctionObject be a SharedPtr - since that is terrible)
			Function& operator= (const Function& function)
			{
				FunctionObject = function.FunctionObject;

				return (*this);
			}

			Function& operator= (Function&& function)
			{
				FunctionObject = move(function.FunctionObject);

				return (*this);
			}

			rT operator()(Ts... args)
			{
				return (*FunctionObject)(args...);
			}
		};
		
		/*	TYPE DEFS	*/
		template <typename ...Ts>
		using BoolFunction = Function<bool, Ts...>;

		template <typename ...Ts>
		using VoidFunction = Function<void, Ts...>;

		/*
		Not using the below because there is likely no need, and the method in which I was using this (having a base class with overloaded () operator) does not work
		but I did not know enough about templates at the time of conception

		Leaving it here incase it becomes useful

		template <typename rT, typename T, typename ...Ts>
		struct MemberFunction
		{
			using F = rT(T::*)(Ts...);
			MemberFunction(T& object, F action)
				: Object(object), Action(action)
			{}

			bool HoldsObject(T const& otherObject) const
			{
				return (otherObject == Object);
			}

			template <typename oT> // used if (oT != T)
			bool HoldsObject(oT const& otherObject) const
			{
				return false;
			}

			bool operator()(Ts&&... args)
			{
				return (Object.(*Action))(Forward<Ts>(args)...);
			}

		private:
			T& Object;
			F Action;
		};
		
		template <typename T, typename ...Ts>
		using MemberFunction_Bool = MemberFunction<bool, T, Ts...>;
		*/
	}
}