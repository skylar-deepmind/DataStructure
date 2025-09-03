#include <stdio.h>
#include <string.h>

#include "linkedStack.h"



// 定义一个自定义结构体用于测试

typedef struct {

	int id;

	char name[20];

} Record;



void print_record(const Record* r) {

	if (r) {

		printf("Record(id: %d, name: \"%s\")", r->id, r->name);

	}

}



void test_record_stack() {

	printf("--- Testing Struct (Record) Linked Stack ---\n");

	// 创建时不再需要容量

	Stack* record_stack = stack_create(sizeof(Record));



	if (!record_stack) {

		printf("Failed to create record stack.\n");

		return;

	}



	printf("Stack created. Is empty? %s\n", stack_is_empty(record_stack) ? "Yes" : "No");



	// 创建一些数据并压栈

	Record r1 = { 1, "Alice" };

	Record r2 = { 2, "Bob" };

	Record r3 = { 3, "Charlie" };



	printf("Pushing "); print_record(&r1); printf("...\n");

	stack_push(record_stack, &r1);



	printf("Pushing "); print_record(&r2); printf("...\n");

	stack_push(record_stack, &r2);



	printf("Pushing "); print_record(&r3); printf("...\n");

	stack_push(record_stack, &r3);



	printf("Current stack size: %zu\n", get_stack_size(record_stack));



	Record peeked_record;

	if (stack_peek(record_stack, &peeked_record)) {

		printf("Peek at top: ");

		print_record(&peeked_record);

		printf("\n");

	}



	printf("\nPopping all elements:\n");

	while (!stack_is_empty(record_stack)) {

		Record popped_record;

		if (stack_pop(record_stack, &popped_record)) {

			printf("Popped: ");

			print_record(&popped_record);

			printf(" | New size: %zu\n", get_stack_size(record_stack));

		}

	}



	printf("\nIs stack empty now? %s\n", stack_is_empty(record_stack) ? "Yes" : "No");



	// 销毁栈

	stack_destroy(&record_stack);

	printf("Stack destroyed. Pointer is now %s\n", record_stack == NULL ? "NULL" : "Not NULL");

}





// ------------------------以下内容的函数是后面的课程--------------------------------------

// 检查括号是否匹配的辅助函数

bool is_opener(char c) {

	return c == '(' || c == '{' || c == '[';

}



bool matches(char opener, char closer) {

	return (opener == '(' && closer == ')') ||

		(opener == '{' && closer == '}') ||

		(opener == '[' && closer == ']');

}



bool check_brackets(const char* code) {



	Stack* stack = stack_create(sizeof(char));



	if (!stack) {



		fprintf(stderr, "Failed to create stack for bracket checking.\n");

		return false;

	}



	size_t len = strlen(code);

	for (size_t i = 0; i < len; i++) {

		char current_char = code[i];



		//  如果是开括号，则压入栈

		if (is_opener(current_char)) {

			stack_push(stack, &current_char);



			// 如果是闭括号，则检查栈顶元素

		}

		else if (current_char == ')' || current_char == '}' || current_char == ']') {



			// 错误情况1：栈为空，闭括号多余

			if (stack_is_empty(stack)) {

				fprintf(stderr, "Unmatched closing bracket '%c' found.\n", current_char);

				stack_destroy(&stack);

				return false; // 闭括号多余

			}



			char popped_opener;

			// 从栈顶弹出一个开括号进行比较

			stack_pop(stack, &popped_opener);// 将弹出的char存入popped_opener



			// 错误情况2：开括号和闭括号不匹配 （类型不匹配）

			if (!matches(popped_opener, current_char)) {



				fprintf(stderr, "Mismatched brackets: '%c' does not match '%c'.\n", popped_opener, current_char);

				stack_destroy(&stack);

				return false; // 开闭括号不匹配

			}

		}

	}



	// 错误情况3：遍历结束，但是栈中仍然有未关闭的开括号

	if (!stack_is_empty(stack)) {



		char unclosed_opener;



		// 查看一下是哪一个开括号没有关闭

		stack_peek(stack, &unclosed_opener);

		fprintf(stderr, "Unmatched opening brackets remain in stack.\n");

		stack_destroy(&stack);

		return false; // 有未关闭的开括号

	}





	// 销毁栈

	stack_destroy(&stack);

	return true;

}



void check() {

	const char* test_cases[] = {

	   "int main() { int x = (1 + 2); return 0; }", // 有效

	   "void func(int a[]);",                        // 有效

	   "([{}])",                                     // 有效

	   "int arr[5] = {1, 2, 3};",                     // 有效

	   "",                                           // 有效 (空字符串)

	   "abc",                                        // 有效 (无括号)

	   "([)]",                                       // 无效: 交叉不匹配

	   "((()",                                       // 无效: 开括号未关闭

	   "())",                                        // 无效: 闭括号无对应

	   "if (x > 0) { printf(\"hello\");",             // 无效: } 未关闭

	   "int y = { ( [ ] ) };"                         // 有效: 复杂嵌套

	};



	int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);



	for (int i = 0; i < num_cases; i++) {

		printf("正在检查: \"%s\"\n", test_cases[i]);

		if (check_brackets(test_cases[i])) {

			printf("结果: -> 有效\n\n");

		}

		else {

			printf("结果: -> 无效\n\n");

		}

	}

}



int main() {

	// ---------------测试链式栈--------------------下面的注释取消即可--------------------

	// test_record_stack();





	// ------------------------以下内容的函数是后面的课程--------------------------------------



	// 测试括号匹配器（后面的课程）

	check();



	return 0;

}