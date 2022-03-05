#pragma once
namespace funcmatrix {
	struct Point {
		int x, y;
		int value;
		Point(int x,int y, int value);
	};

	struct NodeList {
	private:
		struct Node {
			Node* next;
			NodeList* p;
			Point* data;
			Node(Point* data,NodeList* p);
		};
		Node* head = nullptr;
		Node* tail = nullptr;
	public:
		void readfromfile(int* af,const char* a);
		void build_linked_index(NodeList* p);
		void build_compr(NodeList p);
		void add_to_list(int x, int y, int value);
		void print_out_matrix(int x, int y,int i);
		void add_matrix(int* af1,int* af, NodeList* l);
		void multiply_matrix(int* af1, int* af, NodeList* l);
	};
}
void startprog();