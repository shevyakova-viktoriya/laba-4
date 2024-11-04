#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* root; //указатель для обращения к дереву и его эл-там

struct Node* CreateTree(struct Node* root, struct Node* r, int data) //создание дерева
{
	if (r == NULL) //если нет корня
	{
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("Ошибка выделения памяти");
			exit(0);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;

		if (data > root->data)	root->left = r;
		else root->right = r;
		return r;
	}

	if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);

	return root;
}

void print_tree(struct Node* r, int l) //вывод дерева на экран
{

	if (r == NULL)
	{
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf(" ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}

struct Node *find(struct Node* r, int data) {
	if (r->data == data) return r;

	else if (r->data < data && r->left != NULL) {
		find(r->left, data);
	}

	else if (r->data > data && r->right != NULL) {
		find(r->right, data);
	}
	else {
		cout << "Не найден";
		return NULL;
	}
}

int fcount(struct Node* r, int data, int count) {
	if (r == NULL) return count;
	if (r->data == data) count++;
	count = fcount(r->right, data, count);
	count = fcount(r->left, data, count);
	return count;
}

int main()
{
	setlocale(LC_ALL, "");
	int D, start = 1, co;
	struct Node* r = NULL;

	root = NULL;
	printf("-1 - окончание построения дерева\n");
	while (start)
	{
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == -1)
		{
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D);
	}

	print_tree(root, 0);


	cout << ("\nЭлемент, который нужно найти -> ");
	cin >> D;

	r = find(root, D);
	if (r != NULL) printf("\nНайденный элемент = %d", r->data);

	co = fcount(root, D, 0);
	printf("\nКоличество вхождений заданного элемента = %d", co);
	return 0;
}
