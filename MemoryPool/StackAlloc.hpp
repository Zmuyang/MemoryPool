// StackAlloc.hpp

#ifndef STACK_ALLOC_H
#define STACK_ALLOC_H

#include <memory>

template <typename T>
struct StackNode_
{
	T data;
	StackNode_* prev;
};

// T Ϊ�洢�Ķ�������, Alloc Ϊʹ�õķ�����,��Ĭ��ʹ�� std::allocator ��Ϊ����ķ�����
template <class T, class Alloc = std::allocator<T> >
class StackAlloc
{
public:
	// ʹ�� typedef ��������
	typedef StackNode_<T> Node;
	typedef typename Alloc::template rebind<Node>::other allocator;  //�������Ҫ��rebind��allocator��һ����Ա��Ҳ����һ��ģ�壬��template�ز�����

	// Ĭ�Ϲ���
	StackAlloc() { head_ = 0; }
	// Ĭ������
	~StackAlloc() { clear(); }

	// ��ջ��Ԫ��Ϊ��ʱ���� true
	bool empty() { return (head_ == 0); }

	// �ͷ�ջ��Ԫ�ص������ڴ�
	void clear() {
		Node* curr = head_;
		while (curr != 0)
		{
			Node* tmp = curr->prev;
			allocator_.destroy(curr);
			allocator_.deallocate(curr, 1);  //������䣬�൱��C���free
			curr = tmp;
		}
		head_ = 0;
	}

	// ��ջ
	void push(T element) {
		// Ϊһ���ڵ�����ڴ�
		Node* newNode = allocator_.allocate(1);
		//allocator����Ķ�����δ�����������ʹ��ǰ��Ҫ����construct����
		//�ڴ��ڴ��й������ newNode ������һ������Ϊ Node* ��ָ�룬ָ��һ����allocator�����δ�����ڴ�ռ䡣
		//Node() Ϊ����T���캯���Ĳ����������� newNode ָ����ڴ�ռ��й���һ��Node ���Ͷ���
		allocator_.construct(newNode, Node());

		// ��ջ����
		newNode->data = element;
		newNode->prev = head_;
		head_ = newNode;
	}

	// ��ջ
	T pop() {
		// ��ջ���� ���س�ջ���
		T result = head_->data;
		Node* tmp = head_->prev;
		allocator_.destroy(head_);
		allocator_.deallocate(head_, 1);
		head_ = tmp;
		return result;
	}

	// ����ջ��Ԫ��
	T top() { return (head_->data); }

private:
	allocator allocator_;
	Node* head_;
};

#endif // STACK_ALLOC_H