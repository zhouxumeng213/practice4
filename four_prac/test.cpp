#include<stdio.h>
#include<assert.h>
#include<stack>

//题目一：输入两个整数序列，第一个序列表示栈的压人顺序，请判断第二个序列是否为该栈的弹出
//顺序。假设压人栈的所有数字均不相等。例如序列1、2、3、4、5是某栈的压入序列，序列4、5、3、
//2、1是该压栈序列对应的一个弹出序列，但4、3、5、1、2就不可能是该压栈序列的弹出序列。

//思路：解决这个问题的最直接办法就是借助一个辅助栈，把压入序列依次压入该辅助栈，并按照出栈
//序列从辅助栈中弹出数字，若最后辅助栈为空，并且出栈序列全部走完，则是弹出序列

bool IsPopOrder(int * PushOrder, int * PopOrder, int len)
{
	//PushOrder:入栈序列
	//PopOrder:出栈序列
	assert(PushOrder);
	assert(PopOrder);
	if (len < 0)
		return false;
	if (PushOrder != NULL && PopOrder != NULL && len>0)
	{
		int * PushIndex = PushOrder;//PushIndex：指向入栈序列的指针
		int * PopIndex = PopOrder;//PopIndex：指向出栈序列的指针
		std::stack<int> DataStack;//辅助栈，模拟压栈出栈过程
		while (PopIndex - PopOrder < len)
		{
			//辅助栈为空或者弹出序列的第一个数不等于栈顶时，继续压人
			while (DataStack.empty() || DataStack.top != *PopIndex)
			{
				if (PushIndex - PushOrder == len)//全部入栈，但没有出栈的，故不是弹出序列
					break;
				DataStack.push(*PushIndex);
				PushIndex++;
			}
			if (DataStack.top != *PopIndex)
				break;
			DataStack.pop();
			PopIndex++;
		}
		//如果栈为空，并且出栈序列已经全部弹完，说明是正确的出栈序列
		if (DataStack.empty() && PopIndex - PopOrder == len)
			return true;
	}
	return false;
}


//题目二：从上往下打印出二叉树的每个结点，同一层的结点按照从左到右的顺序打印。二叉树
//节点定义如下

//思路：此题相当于对二叉树做层序遍历，打印出每个节点。可以用一个队列来实现，每遍历一个
//结点，就把它的左右结点保存在队列里，最后弹出队列

#include<queue>
struct BinaryTreeNode
{
	int data;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
};
void sequenceOrder(BinaryTreeNode* root)
{
	assert(root);
	std::queue<BinaryTreeNode*> q;
	q.push(root);//先把根结点保存
	while (!q.empty())
	{
		BinaryTreeNode* front = q.front();
		printf("%d ", front->data);
		q.pop();

		if (front->left)//递归判断左孩子
			sequenceOrder(front->left);
		if (front->right)//递归判断右孩子
			sequenceOrder(front->right);
	}
}



//题目三：输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则返回true
//,否则返回false。假设输入的数组的任意两个数字都互不相同。

//思路：二叉搜索树：左孩子比根结点小，右孩子比根结点大。在后序遍历中，最后一个结点是根结点
//再递归判断根结点的左右孩子是否满足二叉搜索树

bool IsBST(int sequence[],int len)
{
	assert(sequence);
	if (len < 0)
		return false;
	int root = sequence[len - 1];
	//将二叉搜索树的左子树找出来,即定位左子树
	int i = 0;
	for (i = 0; i < len-1; i++)
	{
		if (sequence[i]>root)
			break;
	}
	//将二叉搜索树的右子树找出来，即定位右子树
	int j = i;
	for (j = 0; j < len - 1; j++)
	{
		if (sequence[j] < root)
			break;
	}
	//递归判断左子树是否满足二叉搜索树
	bool left = true;
	if (i>0)
		IsBST(sequence, i);
	//递归判断右子树是否满足二叉搜索树
	bool right = true;
	if (j < len - 1)
		IsBST(sequence, len - i - 1);

	return (left && right);
}
int main()
{
	int arr[7] = { 5, 7, 6, 9, 11, 10, 8 };
	bool sign = IsBST(arr, 7);
	if (sign == true)
		printf("true");
	return 0;
}


//题目四：输入一颗二叉树和一个整数，打印出二叉树中结点值得和为输入整数的所有路径。从树的
//根结点开始往下一直到叶结点所经过的结点形成一条路径。二叉树结点定义如下：

//思路：按照前序遍历的方式遍历二叉树，然后将经过的路径保存起来，将值相加，如果相加的值为
//所给的整数，则找到一条路径，不相等，继续遍历左子树，知道叶子节点，如果还是不相等，回到
//父节点，删除刚才左子树的结点，遍历右子树。
//此题用vector模拟栈来保存路径。没有直接用stack的原因是最后要打印路径，而stack只能找到栈
//顶元素
#include<vector>
struct BinaryTreeNode
{
	int data;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
};
void Find(BinaryTreeNode* root, int val, std::vector<int> path, int CurrentVal)
{
	CurrentVal += root->data;
	path.push_back(root->data);
	//如果是叶子结点，并且路径上结点的和等于输入的值
	bool IsLeaf = root->left == NULL && root->right == NULL;
	if (CurrentVal == val && IsLeaf)
	{
		//打印结点路径
		printf("1 path is find: ");
		std::vector<int>::iterator iter = path.begin();
		for (; iter != path.end(); iter++)
			printf("%d\t", *iter);

		printf("\n");
	}
	//如果不是叶子结点，则遍历它的子结点
	if (root->left)
		Find(root->left, val, path, CurrentVal);
	if (root->right)
		Find(root->right, val, path, CurrentVal);
	//在返回到父节点之前，删除该路径上当前结点
	path.pop_back();
}
void FindPath(BinaryTreeNode* root, int val)
{
	assert(root);
	if (val < root->data)
		return;
	std::vector<int> path;
	int CurrentVal = 0;
	Find(root, val, path, CurrentVal);
}


//题目五：请实现函数ComplexListNode* Clone(ComplexListNode* pHead),复制一个复杂链表。在复杂
//链表中，每个结点除了有一个Next指针指向下一个结点外，还有一个Sibling指向链表中的任意
//结点或者NULL。结点定义如下：

//思路1、先完成链表的复制，并用next连接起来，然后设置每个结点的Sibling指针。但每次都要从
//链表的头部开始找，时间复杂度O(n2)。

//思路2、还是先完成链表的复制，并用next连接起来，然后将新结点和原始结点的配对信息保存在
//哈希表中。时间复杂度为O(n)，这相当于用空间换时间

//思路3、将复制好的链表结点接在源节点的后面，然后设置复制出来的结点的Sibling，最后分离两个
//链表，奇数位置是原始链表，偶数位置是新链表
struct ComplexListNode
{
	int data;
	ComplexListNode* next;
	ComplexListNode* Sibling;
};
//第一步：复制原始链表的任意结点并创建新结点，将新结点链接到原始结点的后面
void CloneNodes(ComplexListNode* pHead)
{
	assert(pHead);
	ComplexListNode* begin = pHead;//begin遍历整个链表的指针
	while (begin)
	{
		ComplexListNode* newNode = new ComplexListNode();//创建新结点

		//设置新结点的data、next、Sibling
		newNode->data = begin->data;
		newNode->next = begin->next;
		newNode->Sibling = NULL;

		//更新begin指向，使新结点位于原始结点的后面
		begin->next = newNode;

		begin = newNode->next;
	}
}
//第二步：设置复制出来的结点的Sibling。如果原始链表上的结点N的Sibling指向S，则它对应的复制结点N'
//的Sibling指向S的下一个结点S'
void ConnectSiblingNodes(ComplexListNode* pHead)
{
	assert(pHead);
	ComplexListNode* begin = pHead;
	while (begin)
	{
		ComplexListNode* newNode = begin->next;
		if (begin->Sibling)
		{
			//新结点的Sibling是原始结点的Sibling的下一个
			newNode->Sibling = begin->Sibling->next;
		}
		begin = newNode->next;
	}
}
//第三步：把得到的链表拆分成两个链表，奇数位置上是原始链表，偶数位置上是复制出来的链表
ComplexListNode* SeparateNodes(ComplexListNode* pHead)
{
	assert(pHead);
	ComplexListNode* begin = pHead;
	ComplexListNode* newHead = NULL;
	ComplexListNode* newNode = NULL;
	if (begin)
	{
		//设置新链表的头结点
		newHead = newNode = begin->next;
		begin->next = newNode->next;
		begin = begin->next;
	}
	while (begin)
	{
		//分离两个链表
		newNode->next = begin->next;
		newNode = newNode->next;
		begin->next = newNode->next;
		begin = begin->next;
	}
	return newHead;
}
ComplexListNode* Clone(ComplexListNode* pHead)
{
	CloneNodes(pHead);
	ConnectSiblingNodes(pHead);
	return SeparateNodes(pHead);
}


//题目六：输入一颗二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何
//新的结点，只能调整树中结点指针的指向。二叉树结点定义如下：

//思路：由于这是一个二叉搜索树，所以可以采用中序遍历，因为二叉搜索树左孩子比根结点小，右
//孩子比根结点大。因此在排序成双向链表时，原先指向左子结点的指针调整为链表中指向前一个结点
//的指针，原先指向右子结点的指针调整为链表中指向后一个结点的指针
struct BinaryTreeNode
{
	int data;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
};
void ConvertNode(BinaryTreeNode* root, BinaryTreeNode** list)
{
	assert(root);
	assert(list);
	BinaryTreeNode* begin = root;
	//递归遍历左子树，从叶子结点开始
	if (begin->left)
		ConvertNode(begin->left, list);

	//置当前结点的left，即指向前一个结点的指针
	begin->left = *list;

	//如果是非叶子结点，将之前的叶子节点的right指向当前结点
	if (*list != NULL)
		(*list)->right = begin;

	//更新链表尾结点指针
	*list = begin;

	//递归遍历右子树
	if (begin->right)
		ConvertNode(begin->right, list);
}
BinaryTreeNode* Convert(BinaryTreeNode* root)
{
	assert(root);
	//list：指向双向链表的尾结点
	BinaryTreeNode* list = NULL;
	ConvertNode(root, &list);

	//返回头结点
	BinaryTreeNode* newHead = list;
	while (newHead && newHead->left)
	{
		newHead = newHead->left;
	}
	return newHead;
}


//题目七：输入一个字符串，打印出该字符串中字符的所有排列。例如输入字符串abc,则打印出由字符
//a,b,c所能排列出来的所有字符串abc、acb、bca、cab、cba

//思路：首先分析第一位置可能出现的数字，然后把这个数字和后面的数字分成两部分，对后面的
//那部分做相同的操作，然后把这个数字往后移。
void Permute(char* str)
{
	assert(str);
	Permutation(str, str);
}
void Permutation(char* str, char* begin)
{
	assert(str);
	if (begin == '\0')
		printf("%s\n", str);
	else
	{
		for (char* ch = begin; *ch != '\0'; ++ch)
		{
			char tmp = *ch;
			*ch = *begin;
			*begin = tmp;

			Permutation(str, begin + 1);

			tmp = *ch;
			*ch = *begin;
			*begin = tmp;
		}
	}
}