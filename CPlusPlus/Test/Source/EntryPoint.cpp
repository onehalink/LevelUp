#include "Engine.h"

#include <iostream>



using namespace Engine;


Int32 EntryPoint()
{
	{
		Variant<Int8, Int16, Int32, Int64> variant;

		
		using T1 = typename RemoveReference<decltype(Visit<0>(variant))>::Type;
		using T2 = typename RemoveReference<decltype(Visit<1>(variant))>::Type;
		using T3 = typename RemoveReference<decltype(Visit<2>(variant))>::Type;
		using T4 = typename RemoveReference<decltype(Visit<3>(variant))>::Type;
	}

	{
		using List = LinkedList<Int32>;
		using Node = List::Node;


		List list;
		for (SizeType index = 0; index < 10; index++)
		{
			Node* node = Allocator::Allocate<Node>(1);
			node->element = index;

			list.Add(node);
		}


		auto Fn = [](const List& list, const Char8* tag)
			{
				std::cout << "List(" << tag << "):\n";
				std::cout << "Count - " << list.GetCount() << "\n";
				std::cout << "Values - ";
				for (auto& node : list)
					std::cout << node.element << ", ";
				std::cout << "\n";
			};

		Fn(list, "Reference");

		std::cout << "---\n";

		Node* inserted = Allocator::Allocate<Node>(1);
		inserted->element = 999;
		list.InsertAt(0, inserted);

		list.RemoveAt(1);

		Fn(list, "Modified");
	}

	{
		auto result = SquareRoot(25);

		int breakpoint = -1;
	}

	{
		// Parse Test
		{
			Bool boolValue;
			Float32 float32Value;
			Int32 int32Value;

			Bool parseResult = false;

			TryParseBool(&boolValue, "false");
			TryParseBool(&boolValue, "true");

			TryParseFloat32(&float32Value, "1.2345");
			TryParseFloat32(&float32Value, "-1.2345");

			TryParseInt32(&int32Value, "88");
			TryParseInt32(&int32Value, "-88");

			int breakpoint = -1;
		}

		// Convert Test
		{
			Char8 boolBuffer[16];
			Char8 float32Buffer[16];
			Char8 int32Buffer[16];

			TryConvertBool(boolBuffer, sizeof(boolBuffer), false);
			TryConvertBool(boolBuffer, sizeof(boolBuffer), true);

			TryConvertFloat32(float32Buffer, sizeof(float32Buffer), 10.225);
			TryConvertFloat32(float32Buffer, sizeof(float32Buffer), -10.225);

			TryConvertInt32(int32Buffer, sizeof(int32Buffer), 123);
			TryConvertInt32(int32Buffer, sizeof(int32Buffer), -123);

			int breakpoint = -1;
		}
	}

	return 0;
}


int main(int count, char** arguments)
{
	return EntryPoint();
}