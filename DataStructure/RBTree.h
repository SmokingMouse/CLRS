#pragma once
#include<memory>

namespace CLRS {
	namespace DataStructure {
		using std::shared_ptr;
		using std::weak_ptr;

		extern const bool BLACK;
		extern const bool RED;

		template<class KeyType, class Compare>
		struct RBNode {
			typedef KeyType KeyType;
			typedef Compare Compare;
			typedef bool Color;


			RBNode() :key_(KeyType()), parent_(0), left_(0), right_(0), color_(RED) {}
			RBNode(const KeyType& v):key_(v),parent_(0),left_(0),right_(0),color_(RED){}
			RBNode(const KeyType& v, Color c) :key_(v), color_(c) ,left_(0),right_(0),parent_(0){}

			~RBNode() {
				if (!left_) delete left_;
				if (!right_) delete right_;
			}

			Color color_;
			KeyType key_;
			RBNode* parent_;
			RBNode* left_;
			RBNode* right_;
		};

		template<class Node>
		class RBTree {
		public:
			typedef typename Node::Color Color;
			typedef typename Node::Compare Compare;
			typedef typename Node::KeyType KeyType;

			RBTree():root_(NULL){}
			RBTree(Compare compare):compare_(compare){}
			~RBTree() { delete root_; }

			Node* Search(const KeyType& key) {
				return search_(key, root_);
			}

			void Insert(const KeyType& key) {
				Node* p = NULL;
				Node* insertPlace = root_;
				while (insertPlace) {
					p = insertPlace;
					if (compare_(key, insertPlace->key_)) insertPlace = insertPlace->left_;
					else insertPlace = insertPlace->right_;
				}
				insertPlace = new Node(key);
				if (p)
				{
					if (compare_(key, p->key_)) p->left_ = insertPlace;
					else p->right_ = insertPlace;
				}else root_ = insertPlace;
				insertPlace->parent_ = p;

				Insert_Adjust(insertPlace);
			}

			void Insert_Adjust(Node* ptr) {
				if (ptr->color_ == BLACK) return;
				Node* p = ptr->parent_;
				if (!p) {
					ptr->color_ = BLACK;
					return;
				}
				if (p->color_ == BLACK) return;
				Node* g_p = p->parent_;
				Node* uncle = p == g_p->left_ ? g_p->right_ : g_p->left_;
							//p == RED, which means p->parent can be null.
				if (uncle && uncle->color_ == RED) {
					p->color_ = BLACK;
					uncle->color_ = BLACK;
					ptr = p->parent_;
					ptr->color_ = RED;
					Insert_Adjust(ptr);
				}
				else if (p == g_p->left_) {
					if (ptr == p->left_) {
						RightRotate(p);
						p->color_ = BLACK;
						g_p->color_ = RED;
					}
					else {
						LeftRotate(ptr);
						Insert_Adjust(p);
					}
				}
				else {
					if (ptr == p->right_) {
						LeftRotate(p);
						p->color_ = BLACK;
						g_p->color_ = RED;
					}
					else {
						RightRotate(ptr);
						Insert_Adjust(p);
					}
				}
			}

			void LeftRotate(Node* ptr) {
				if (!ptr || !ptr->parent_) return;
				Node* p = ptr->parent_;
				p->right_ = ptr->left_;
				if (ptr->left_) ptr->left_->parent_ = p;
				ptr->parent_ = p->parent_;
				if (!p->parent_) {
					root_ = ptr;
				}
				else if (p == p->parent_->left_) {
					p->parent_->left_ = ptr;
				}
				else {
					p->parent_->right_ = ptr;
				}
				ptr->left_ = p;
				p->parent_ = ptr;
			}

			void RightRotate(Node* ptr) {
				if (!ptr || !ptr->parent_) return;
				Node* p = ptr->parent_;
				p->left_ = ptr->right_;
				if (ptr->right_) ptr->right_->parent_ = p;
				ptr->parent_ = p->parent_;
				if (!p->parent_) {
					root_ = ptr;
				}
				else if (p == p->parent_->left_) {
					p->parent_->left_ = ptr;
				}
				else {
					p->parent_->right_ = ptr;
				}
				ptr->right_ = p;
				p->parent_ = ptr;
			}

			void Delete(Node* ptr) {
				if (!ptr) return;
				Node* toFix;
				Color original_color = ptr->color_;
				if (!ptr->left_) {
					transplant(ptr, ptr->right_);
					toFix = ptr->right_;
				}
				else if (!ptr->right_) {
					transplant(ptr, ptr->left_);
					toFix = ptr->left_;
				}
				else {
					Node* next = TreeMinmum(ptr->right_);
					original_color = next->color_;
					toFix = next->right_;
					if (next->parent_ != ptr) {
						transplant(next, next->right_);
						next->right_ = ptr->right_;
						next->right_->parent_ = next;
					}
					transplant(ptr, next);
					next->left_ = ptr->left_;
					if (next->left_) next->left_->parent_ = next;
					next->color_ = ptr->color_;
				}
				if (original_color == BLACK) Delete_Adjust(toFix);
				ptr->left_ = NULL; ptr->right_ = NULL;
				delete ptr;
			}

			void Delete_Adjust(Node* fixNode) {
				while (fixNode != root_ && fixNode->color_ == BLACK) {
					if (fixNode == fixNode->parent_->left_) {
						Node* brother = fixNode->parent_->right_;
									// The brother can't be Null, otherwise black left > black right.
						if (brother->color_ == RED) {
							brother->color_ = brother->parent_->color_;
							brother->parent_->color_ = RED;
							LeftRotate(brother);
							brother = fixNode->parent_->right_;
						}
						if ((!brother->left_ || brother->left_->color_ == BLACK)
							&& (!brother->right_ || brother->right_->color_ == BLACK))
						{
							brother->color_ = RED;
							fixNode = fixNode->parent_;
						}
						else if ((brother->left_&&brother->left_->color_ == RED) &&
							(!brother->right_ || brother->right_->color_ == BLACK)) {
							brother->color_ = RED;
							brother->left_->color_ = BLACK;
							RightRotate(brother->left_);
							brother = fixNode->parent_->right_;
						}
						else {
							brother->right_->color_ = BLACK;
							brother->color_ = brother->parent_->color_;
							brother->parent_->color_ = BLACK;
							LeftRotate(brother);
							fixNode = root_;
						}
					}
					else {
						Node* brother = fixNode->parent_->left_;
						if (brother->color_ == RED) {
							brother->color_ = brother->parent_->color_;
							brother->parent_->color_ = RED;
							RightRotate(brother);
							brother = fixNode->parent_->left_;
						}
						if ((!brother->left_ || brother->left_->color_ == BLACK)
							&& (!brother->right_ || brother->right_->color_ == BLACK))
						{
							brother->color_ = RED;
							fixNode = fixNode->parent_;
						}
						else if ((brother->right_&&brother->right_->color_ == RED) &&
							(!brother->left_ || brother->left_->color_ == BLACK)) {
							brother->color_ = RED;
							brother->right_->color_ = BLACK;
							LeftRotate(brother->right_);
							brother = fixNode->parent_->left_;
						}
						else {
							brother->left_->color_ = BLACK;
							brother->color_ = brother->parent_->color_;
							brother->parent_->color_ = BLACK;
							RightRotate(brother);
							fixNode = root_;
						}
					}
				}
				fixNode->color_ = BLACK;
			}

			void transplant(Node* p, Node* q) {
				if (p == root_) root_ = q;
				else if (p == p->parent_->left_) p->parent_->left_ = q;
				else p->parent_->right_ = q;
				if (q) q->parent_ = p->parent_;
			}

			Node* TreeMinmum(Node* root) {
				if (!root||!root->left_) return root;
				return TreeMinmum(root->left_);
			}
		
			Node* search_(const KeyType& key, Node* root) {
				if (!root) return NULL;
				if (root->key_ == key) return root;
				else if (compare_(key, root->key_)) return search_(key, root->left_);
				else return search_(key, root->right_);
			}

		private:
			Node* root_;
			Compare compare_;
		};


	}
}




