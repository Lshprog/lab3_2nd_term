#include "Header.h"
#include<iostream>
#include <fstream>


std::ifstream F;

const char FILE_IN_NAME[] = "mynewfiles\\entermatrix.txt";
const char FILE_IN_NAME_2[] = "mynewfiles\\entermatrix2.txt";


funcmatrix::NodeList::Node::Node(Point* data,NodeList* p)
{
	this->data = data;
	this->p = p;
}

funcmatrix::Point::Point(int x, int y, int value)
{
	this->x = x;
	this->y = y;
	this->value = value;
}

void startprog(){

	
	int c;
	int af[2] = {0,0};
	int af2[2] = { 0,0 };
	funcmatrix::NodeList list = funcmatrix::NodeList();
	funcmatrix::NodeList list_compr = funcmatrix::NodeList();
	funcmatrix::NodeList list_cons = funcmatrix::NodeList();
	funcmatrix::NodeList list2 = funcmatrix::NodeList();
	funcmatrix::NodeList list_compr2 = funcmatrix::NodeList();
	funcmatrix::NodeList list_cons2 = funcmatrix::NodeList();
	

	std::cout << "Enter 0 to read first matrix from the first file \n Working with the first matrix: \n";
	std::cout << "\tEnter 1 to create short connect \n";
	std::cout << "\tEnter 2 to create index form \n";
	std::cout << "\tEnter 3 to print out 1 way \n";
	std::cout << "\tEnter 4 to print out 2 way \n";
	std::cout << "Enter 5 to read second matrix from the second file \n Working with the second matrix: \n";
	std::cout << "\tEnter 6 to create short connect \n";
	std::cout << "\tEnter 7 to create index form \n";
	std::cout << "\tEnter 8 to print out 1 way \n";
	std::cout << "\tEnter 9 to print out 2 way \n";
	std::cout << "\nEnter 10 to add this 2 matrices \n";

	while (true) {
		std::cin >> c;

		switch (c) {
		case 0:
			list.readfromfile(*(&af),FILE_IN_NAME);
			std::cout << "What else ? \n";
			continue;
		case 1:
			list_compr.build_compr(list);
			std::cout << "What else ? \n";
			continue;
		case 2:
			list_cons.build_linked_index(&list);
			std::cout << "What else ? \n";
			continue;
		case 3:
			list_compr.print_out_matrix(af[0],af[1],0);
			std::cout << "What else ? \n";
			continue;
		case 4:
			list_cons.print_out_matrix(af[0], af[1],0);
			std::cout << "What else ? \n";
			continue;
		case 5:
			list2.readfromfile(*(&af2), FILE_IN_NAME_2);
			std::cout << "What else ? \n";
			continue;
		case 6:
			list_compr2.build_compr(list2);
			std::cout << "What else ? \n";
			continue;
		case 7:
			list_cons2.build_linked_index(&list2);
			std::cout << "What else ? \n";
			continue;
		case 8:
			list_compr2.print_out_matrix(af2[0], af2[1], 0);
			std::cout << "What else ? \n";
			continue;
		case 9:
			list_cons2.print_out_matrix(af2[0], af2[1], 0);
			std::cout << "What else ? \n";
			continue;
		case 10:
			list_compr.add_matrix(*(&af), *(&af2), &list_compr2);
			std::cout << "What else ? \n";
			continue;
		case 11:
			list_compr.multiply_matrix(*(&af), *(&af2), &list_compr2);
			std::cout << "What else ? \n";
			continue;
		case 123:
			break;
	}
	}
	return;
}

void funcmatrix::NodeList::readfromfile(int *af,const char* FILE_IN_NAME)
{
	F.open(FILE_IN_NAME, std::ios::in);
	int x,y;
	char c;
	
	F >> x;
	F >> c;
	F >> y;

	for (int i = 0; i < x; i++) {
		for (int t = 0; t < y; t++) {
			NodeList* listq =new NodeList();
			Point* sq = new Point(0, 0, 0);
			F >> sq->value;
			sq->x = i;
			sq->y = t;
			Node* node = new Node(sq, listq);
			if (head == nullptr&&tail == nullptr) {
				head = node;
				tail = node;
			}
			else {
				tail->next = node;
				tail = node;
			}
		}
	}
	F.close();
	af[0] = x;
	af[1] = y;
	return;
}

void funcmatrix::NodeList::build_linked_index(NodeList* l)
{
	int k;
	Node* temp = l->head;

	
	for (int i = 0; i <= l->tail->data->x;i++) {
		k = i;
		while (k > 9)
			k /= 10;
		Point* sq = new Point(k, 0, 0);
		NodeList* listq = new NodeList();
		Node* node = new Node(sq,listq);
		Node* tempd = node;
		if (head == nullptr && tail == nullptr) {
			head = node;
			tail = node;
		}
		else {
			tempd = head;
			while (true) {
				if (tempd->data->x == node->data->x) 
					break;
				if (tempd == tail) {
					add_to_list(k, 0, 0);
					tempd = tail;
					break;
				}
				tempd = tempd->next;
			}
		}
		
		for (int j = 0; j <= l->tail->data->y; j++) {
			if (temp->data->value == 0) {
				temp = temp->next;
				continue;
			}
			tempd->p->add_to_list(i, j, temp->data->value);
			temp = temp->next;
		}
	}
	return;
}

void funcmatrix::NodeList::build_compr(NodeList l)
{

	Node* temp = l.head;
	

	for (int i = 0; i <= l.tail->data->x; i++) {
		for (int j = 0; j <= l.tail->data->y; j++) {
			if (temp->data->value == 0) {
				temp =temp->next;
				continue;
			}
			
			add_to_list(i, j, temp->data->value);
			temp = temp->next;
			
			
		}
	}
	return;

}

void funcmatrix::NodeList::add_to_list(int x,int y,int value)
{
	Point* sq = new Point(x, y, value);
	NodeList* listq = new NodeList();
	Node* node = new Node(sq,listq);

	if (head == nullptr && tail == nullptr) {
		head = node;
		tail = node;
	}
	else {
		tail->next = node;
		tail = node;
	}
	return;
}

void funcmatrix::NodeList::print_out_matrix(int x1,int y1,int kk)
{
	Node* temp = head;
	int i = kk;
	int j = 0;

	while (true) {
		if (temp->p->head == nullptr && temp->p->tail == nullptr) {
			if ((temp->data->value == 0) && (temp->data->y == 0)) {
				for (int z = 0; z < y1; z++) {
					std::cout << "0 ";
				}
				std::cout << '\n';
				i++;
				temp = temp->next;
				continue;
			}
			if (temp->data->x != i || temp->data->y != j) {
				std::cout << "0 ";
			}
			else {
				std::cout << temp->data->value <<" ";
				if (temp == tail) {
					while (j + 1 < y1) {
						std::cout << "0 ";
						j++;
					}
					std::cout << '\n';
					return;
				}
				temp = temp->next;
			}
		}
		else {
			
			temp->p->print_out_matrix(temp->data->x,y1,temp->data->x);
			j = 0;
			i++;
			if (temp == tail)
				return;
			temp = temp->next;
			continue;
		}
		if (j+1==y1) {
			i++;
			j = 0;
			std::cout<<'\n';
			continue;
		}
		j++;
	}
	return;
}

void funcmatrix::NodeList::add_matrix(int* af, int* af1, NodeList* l)
{
	if (af[0] != af1[0]|| af[1] != af1[1]) {
		std::cout << "Error! \n";
		return;
	}

	Node* temp = l->head;
	Node* temd = head;
	int i = 0, j = 0;

	while (true) {
		if ((temp->data->x != i || temp->data->y != j) && (temd->data->x != i || temd->data->y != j))
			std::cout << " 0";
		else if ((temp->data->x != i || temp->data->y != j) && (temd->data->x == i && temd->data->y == j)) {
			std::cout << " " << temd->data->value;
			if (temd != tail)
				temd = temd->next;
		}
		else if ((temd->data->x != i || temd->data->y != j) && (temp->data->x == i && temp->data->y == j)) {
			std::cout << " " << temp->data->value;
			if (temp != l->tail)
				temp = temp->next;
		}
		else {
			std::cout << " " << temp->data->value + temd->data->value;
			if (temd != tail)
				temd = temd->next;
			if (temp != l->tail)
				temp = temp->next;
		}
		if (j +1== af[1]) {
			if (i + 1 == af[0]) {
				break;
			}
			j = 0;
			i++;
			std::cout << '\n';
			continue;
		}
		j++;
			
	}
	return;
}

void funcmatrix::NodeList::multiply_matrix(int* af1, int* af, NodeList* l)
{
	if (af[1] != af1[0]) {
		std::cout << "Error! \n";
		return;
	}


	for (int k = 0; k < af1[1]; k++) {
		for (int i = 0; i < af[0]; i++) {
			int sum = 0;
			Node* temp = l->head;
			Node* temd = head;
			while (temp->data->x < k) {
				temp = temp->next;
			}
			if (temp->data->x != k) {
				for (int z = 0; i < af[1]; i++) {
					std::cout << " 0";
				}
				continue;

			}
			for (int j = 0; j < af[1]; j++) {
				if (temp->data->y != j) {
					if (temd->data->x == j && temd->data->y == i) {
						temd = temd->next;
					}
				}
				else {
					if (temd->data->x == j && temd->data->y == i) {
						sum += temd->data->value * temp->data->value;
						if(temd!=tail)
							temd = temd->next;
						if (temp != l->tail)
							temp = temp->next;
					}
					else {
						while ((temd->data->x < j) || (temd->data->y < i)) {
							if (temd != tail) {
								temd = temd->next;
								continue;
							}
							break;
						}
						if (temd->data->x == j && temd->data->y == i) {
							sum += temd->data->value * temp->data->value;
							if (temd != tail)
								temd = temd->next;
							if (temp != l->tail)
								temp = temp->next;
						}
						if (temp != l->tail)
							temp = temp->next;
					}
				}
			}

		std::cout << " " << sum;
	}
		std::cout << '\n';
	}
	std::cout << '\n';
	return;
}
