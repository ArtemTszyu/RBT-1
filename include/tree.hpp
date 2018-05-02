#include <sstream>
#include<iostream>
#include<string>

template<typename T>
class tree_t
{
private:
	struct node_t {
		bool red;
		T value;
		node_t * left;
		node_t * right;
	};
private:
	node_t * root_;
public:
	tree_t()
	{
		root_ = nullptr;
	}

	~tree_t()
	{
		del(root_);
	}

	void del(node_t * node)
	{
		if (root_ != nullptr) {
			if (node->left) del(node->left);
			if (node->right) del(node->right);
		}
		delete node;
	}

	node_t *new_node(T value)
	{
		node_t *node = new node_t;
		node->value = value;
		node->left = nullptr;
		node->right = nullptr;
		node->red = true;
		return node;
	}

	node_t *rotate_left(node_t* node)
	{
		node_t *right = node->right;
		node_t *left_of_right = right->left;
		right->left = node;
		node->right = left_of_right;
		return right;
	}

	node_t *rotate_right(node_t* node)
	{
		node_t *left = node->left;
		node_t *right_of_left = left->right;
		left->right = node;
		node->left = right_of_left;
		return left;
	}
	
	void balance_insert(node_t** root)
	{
		node_t *left, *right, *temp_left, *temp_right;
		node_t *node = *root;
		if (node->red) return;
		left = node->left;
		right = node->right;
		if (left && left->red) {
			temp_right = left->right;
			if (temp_right && temp_right->red)
			{
				left = node->left = rotate_left(left);
			}
			temp_left = left->left;
			if (temp_left && temp_left->red) {
				node->red = true;
				left->red = false;
				if (right && right->red) {
					right->red = false;
					return;
				}
				*root = rotate_right(node);
				return;
			}
		}
		if (right && right->red) {
			temp_left = right->left;
			if (temp_left && temp_left->red)
			{
				right = node->right = rotate_right(right);
			}
			temp_right = right->right;
			if (temp_right && temp_right->red) {
				node->red = true;
				right->red = false;
				if (left && left->red) {
					left->red = false;
					return;
				}
				*root = rotate_left(node);
				return;
			}
		}
	}

	bool insert(T value, node_t** root)
	{
		node_t *node = *root;
		if (!node)
		{
			*root = new_node(value);
		}
		else
		{
			if (value == node->value)
			{
				return true;
			}
			if (insert(value, value < node->value ? &node->left : &node->right))
			{
				return true;
			}
			balance_insert(root);
		}
		return false;
	}			
	
	void insert(T value)
	{
		insert(value,&root_);
		if (root_) root_->red = false;
	}

	bool find(T value) const
	{
		node_t * time = root_;
		while (time != nullptr) {
			if (value == time->value) {
				return true;
			}
			else {
				if (value < time->value) {
					time = time->left;
				}
				else {
					time = time->right;
				}
			}
		}
		return false;
	}

	node_t * root() const
	{
		return  root_;
	}

	void print(std::ostream & stream, node_t * node, size_t i = 1) const
	{
		if (node->right) {
			i++;
			print(stream, node->right, i);
			i--;
		}
		for (size_t k = 0; k < i; k++) {
			stream << "--";
		}
		stream << node->value << std::endl;
		if (node->left) {
			i++;
			print(stream, node->left, i);
			i--;
		}
	}
	
	bool isEmpty()
	{
		return (!root_);
	}

	bool balance_remove_left(node_t** root)
	{
		node_t *node = *root;
		node_t *left = node->left;
		node_t *right = node->right;
		if (left && left->red) {
			left->red = false;
			return false;
		}
		if (right && right->red) { // 1
			node->red = true;
			right->red = false;
			node = *root = rotate_left(node);
			if (balance_remove_left(&node->left))
			{
				node->left->red = false;
			}
			return false;
		}
		unsigned int mask = 2; // case
		node_t *left_of_right = right->left;
		node_t *right_of_right = right->right;
		if (left_of_right && left_of_right->red) mask = 3;
		if (right_of_right && right_of_right->red) mask = 4;
		switch (mask)
		{
		case 2:	 
			right->red = true;
			return true;
			break;
		case 3:		 
			right->red = true;
			left_of_right->red = false;
			right = node->right = rotate_right(right);
			right_of_right = right->right;
			break;
		case 4:		
			right->red = node->red;
			right_of_right->red = node->red = false;
			*root = rotate_left(node);
			break;
		}
		return false;
	}

	bool balance_remove_right(node_t** root)
	{
		node_t *node = *root;
		node_t *left = node->left;
		node_t *right = node->right;
		if (right && right->red)
		{
			right->red = false;
			return false;
		}
		if (left && left->red) { // 1
			node->red = true;
			left->red = false;
			node = *root = rotate_right(node);
			if (balance_remove_right(&node->right))
			{
				node->right->red = false;
			}
			return false;
		}
		unsigned int mask = 2;
		node_t *left_of_left = left->left;
		node_t *right_of_left = left->right;
		if (left_of_left && left_of_left->red) mask = 4;
		if (right_of_left && right_of_left->red) mask = 3;
		switch (mask) {
		case 2:		
			left->red = true;
			return true;
			break;
		case 3:		
			left->red = true;
			right_of_left->red = false;
			left = node->left = rotate_left(left);
			left_of_left = left->left;
			break;
		case 4:		
			left->red = node->red;
			left_of_left->red = node->red = false;
			*root = rotate_right(node);
			break;
		}
		return false;
	}

	// обычное удаление(как в бинарном дереве) 
	// root корень дерева в котором надо найти элемент
	// key элемент который был удалён
	// result true если нужен баланс
	bool simple_remove(node_t **root, node_t **removed_key)
	{
		node_t *node = *root;
		if (node->left) {
			if (simple_remove(&node->left, removed_key)){
				return balance_remove_left(root);
			}
		}
		else {
			*root = node->right;
			*removed_key = node;
			return !node->red;
		}
		return false;
	}

	bool remove(node_t** root, T value, size_t * success)
	{
		node_t * temp;
		node_t *node = *root;
		if (!node) {
			return false;
		}
		if (node->value < value) {
			if (remove(&node->right, value,success)){
				return balance_remove_right(root);
			}
		}
		else if (node->value > value) {
			if (remove(&node->left, value,success)){
				return balance_remove_left(root);
			}
		}
		else {
			
			bool result;
			if (!node->right) {
				*root = node->left;
				result = !node->red;
			}
			else {
				result = simple_remove(&node->right, root);
				temp = *root; // продолжение удаления 
				temp->red = node->red;
				temp->left = node->left;
				temp->right = node->right;
				if (result) {
					result = balance_remove_right(root);
				}
			}
			delete node;
			*success = 1;
			return result;
		}
		return false;
	}

	bool remove(T value)
	{
		size_t success = 0;
		remove(&root_, value,&success);
		if (success == 1) {
			return true;
		}
		else return false;
	}

	bool equal(node_t * lhs, node_t * rhs) const
	{
		if (!lhs && !rhs) {
			return true;
		}
		else if (lhs && rhs && lhs->value == rhs->value) {
			return equal(lhs->left, rhs->left) && equal(lhs->right, rhs->right);
		}
		else {
			return false;
		}
	}

	bool operator==(tree_t const & other) const
	{
		node_t * a, *b;
		a = root_;
		b = other.root();
		return(equal(a, b));
	}

	tree_t(std::initializer_list<T> keys)
	{
		size_t size = keys.size();

		for (size_t i = 0; i < size; i++) {
			T a = *(keys.begin() + i);
			(*this).insert(a);
		}
	}
};
