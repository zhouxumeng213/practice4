#include<stdio.h>
#include<assert.h>
#include<stack>

//��Ŀһ�����������������У���һ�����б�ʾջ��ѹ��˳�����жϵڶ��������Ƿ�Ϊ��ջ�ĵ���
//˳�򡣼���ѹ��ջ���������־�����ȡ���������1��2��3��4��5��ĳջ��ѹ�����У�����4��5��3��
//2��1�Ǹ�ѹջ���ж�Ӧ��һ���������У���4��3��5��1��2�Ͳ������Ǹ�ѹջ���еĵ������С�

//˼·���������������ֱ�Ӱ취���ǽ���һ������ջ����ѹ����������ѹ��ø���ջ�������ճ�ջ
//���дӸ���ջ�е������֣��������ջΪ�գ����ҳ�ջ����ȫ�����꣬���ǵ�������

bool IsPopOrder(int * PushOrder, int * PopOrder, int len)
{
	//PushOrder:��ջ����
	//PopOrder:��ջ����
	assert(PushOrder);
	assert(PopOrder);
	if (len < 0)
		return false;
	if (PushOrder != NULL && PopOrder != NULL && len>0)
	{
		int * PushIndex = PushOrder;//PushIndex��ָ����ջ���е�ָ��
		int * PopIndex = PopOrder;//PopIndex��ָ���ջ���е�ָ��
		std::stack<int> DataStack;//����ջ��ģ��ѹջ��ջ����
		while (PopIndex - PopOrder < len)
		{
			//����ջΪ�ջ��ߵ������еĵ�һ����������ջ��ʱ������ѹ��
			while (DataStack.empty() || DataStack.top != *PopIndex)
			{
				if (PushIndex - PushOrder == len)//ȫ����ջ����û�г�ջ�ģ��ʲ��ǵ�������
					break;
				DataStack.push(*PushIndex);
				PushIndex++;
			}
			if (DataStack.top != *PopIndex)
				break;
			DataStack.pop();
			PopIndex++;
		}
		//���ջΪ�գ����ҳ�ջ�����Ѿ�ȫ�����꣬˵������ȷ�ĳ�ջ����
		if (DataStack.empty() && PopIndex - PopOrder == len)
			return true;
	}
	return false;
}


//��Ŀ�����������´�ӡ����������ÿ����㣬ͬһ��Ľ�㰴�մ����ҵ�˳���ӡ��������
//�ڵ㶨������

//˼·�������൱�ڶԶ������������������ӡ��ÿ���ڵ㡣������һ��������ʵ�֣�ÿ����һ��
//��㣬�Ͱ��������ҽ�㱣���ڶ������󵯳�����

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
	q.push(root);//�ȰѸ���㱣��
	while (!q.empty())
	{
		BinaryTreeNode* front = q.front();
		printf("%d ", front->data);
		q.pop();

		if (front->left)//�ݹ��ж�����
			sequenceOrder(front->left);
		if (front->right)//�ݹ��ж��Һ���
			sequenceOrder(front->right);
	}
}



//��Ŀ��������һ���������飬�жϸ������ǲ���ĳ�����������ĺ�������Ľ����������򷵻�true
//,���򷵻�false���������������������������ֶ�������ͬ��

//˼·�����������������ӱȸ����С���Һ��ӱȸ������ں�������У����һ������Ǹ����
//�ٵݹ��жϸ��������Һ����Ƿ��������������

bool IsBST(int sequence[],int len)
{
	assert(sequence);
	if (len < 0)
		return false;
	int root = sequence[len - 1];
	//���������������������ҳ���,����λ������
	int i = 0;
	for (i = 0; i < len-1; i++)
	{
		if (sequence[i]>root)
			break;
	}
	//���������������������ҳ���������λ������
	int j = i;
	for (j = 0; j < len - 1; j++)
	{
		if (sequence[j] < root)
			break;
	}
	//�ݹ��ж��������Ƿ��������������
	bool left = true;
	if (i>0)
		IsBST(sequence, i);
	//�ݹ��ж��������Ƿ��������������
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


//��Ŀ�ģ�����һ�Ŷ�������һ����������ӡ���������н��ֵ�ú�Ϊ��������������·����������
//����㿪ʼ����һֱ��Ҷ����������Ľ���γ�һ��·������������㶨�����£�

//˼·������ǰ������ķ�ʽ������������Ȼ�󽫾�����·��������������ֵ��ӣ������ӵ�ֵΪ
//���������������ҵ�һ��·��������ȣ�����������������֪��Ҷ�ӽڵ㣬������ǲ���ȣ��ص�
//���ڵ㣬ɾ���ղ��������Ľ�㣬������������
//������vectorģ��ջ������·����û��ֱ����stack��ԭ�������Ҫ��ӡ·������stackֻ���ҵ�ջ
//��Ԫ��
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
	//�����Ҷ�ӽ�㣬����·���Ͻ��ĺ͵��������ֵ
	bool IsLeaf = root->left == NULL && root->right == NULL;
	if (CurrentVal == val && IsLeaf)
	{
		//��ӡ���·��
		printf("1 path is find: ");
		std::vector<int>::iterator iter = path.begin();
		for (; iter != path.end(); iter++)
			printf("%d\t", *iter);

		printf("\n");
	}
	//�������Ҷ�ӽ�㣬����������ӽ��
	if (root->left)
		Find(root->left, val, path, CurrentVal);
	if (root->right)
		Find(root->right, val, path, CurrentVal);
	//�ڷ��ص����ڵ�֮ǰ��ɾ����·���ϵ�ǰ���
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


//��Ŀ�壺��ʵ�ֺ���ComplexListNode* Clone(ComplexListNode* pHead),����һ�����������ڸ���
//�����У�ÿ����������һ��Nextָ��ָ����һ������⣬����һ��Siblingָ�������е�����
//������NULL����㶨�����£�

//˼·1�����������ĸ��ƣ�����next����������Ȼ������ÿ������Siblingָ�롣��ÿ�ζ�Ҫ��
//�����ͷ����ʼ�ң�ʱ�临�Ӷ�O(n2)��

//˼·2���������������ĸ��ƣ�����next����������Ȼ���½���ԭʼ���������Ϣ������
//��ϣ���С�ʱ�临�Ӷ�ΪO(n)�����൱���ÿռ任ʱ��

//˼·3�������ƺõ����������Դ�ڵ�ĺ��棬Ȼ�����ø��Ƴ����Ľ���Sibling������������
//��������λ����ԭʼ����ż��λ����������
struct ComplexListNode
{
	int data;
	ComplexListNode* next;
	ComplexListNode* Sibling;
};
//��һ��������ԭʼ����������㲢�����½�㣬���½�����ӵ�ԭʼ���ĺ���
void CloneNodes(ComplexListNode* pHead)
{
	assert(pHead);
	ComplexListNode* begin = pHead;//begin�������������ָ��
	while (begin)
	{
		ComplexListNode* newNode = new ComplexListNode();//�����½��

		//�����½���data��next��Sibling
		newNode->data = begin->data;
		newNode->next = begin->next;
		newNode->Sibling = NULL;

		//����beginָ��ʹ�½��λ��ԭʼ���ĺ���
		begin->next = newNode;

		begin = newNode->next;
	}
}
//�ڶ��������ø��Ƴ����Ľ���Sibling�����ԭʼ�����ϵĽ��N��Siblingָ��S��������Ӧ�ĸ��ƽ��N'
//��Siblingָ��S����һ�����S'
void ConnectSiblingNodes(ComplexListNode* pHead)
{
	assert(pHead);
	ComplexListNode* begin = pHead;
	while (begin)
	{
		ComplexListNode* newNode = begin->next;
		if (begin->Sibling)
		{
			//�½���Sibling��ԭʼ����Sibling����һ��
			newNode->Sibling = begin->Sibling->next;
		}
		begin = newNode->next;
	}
}
//���������ѵõ��������ֳ�������������λ������ԭʼ����ż��λ�����Ǹ��Ƴ���������
ComplexListNode* SeparateNodes(ComplexListNode* pHead)
{
	assert(pHead);
	ComplexListNode* begin = pHead;
	ComplexListNode* newHead = NULL;
	ComplexListNode* newNode = NULL;
	if (begin)
	{
		//�����������ͷ���
		newHead = newNode = begin->next;
		begin->next = newNode->next;
		begin = begin->next;
	}
	while (begin)
	{
		//������������
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


//��Ŀ��������һ�Ŷ��������������ö���������ת����һ�������˫������Ҫ���ܴ����κ�
//�µĽ�㣬ֻ�ܵ������н��ָ���ָ�򡣶�������㶨�����£�

//˼·����������һ�����������������Կ��Բ��������������Ϊ�������������ӱȸ����С����
//���ӱȸ���������������˫������ʱ��ԭ��ָ�����ӽ���ָ�����Ϊ������ָ��ǰһ�����
//��ָ�룬ԭ��ָ�����ӽ���ָ�����Ϊ������ָ���һ������ָ��
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
	//�ݹ��������������Ҷ�ӽ�㿪ʼ
	if (begin->left)
		ConvertNode(begin->left, list);

	//�õ�ǰ����left����ָ��ǰһ������ָ��
	begin->left = *list;

	//����Ƿ�Ҷ�ӽ�㣬��֮ǰ��Ҷ�ӽڵ��rightָ��ǰ���
	if (*list != NULL)
		(*list)->right = begin;

	//��������β���ָ��
	*list = begin;

	//�ݹ����������
	if (begin->right)
		ConvertNode(begin->right, list);
}
BinaryTreeNode* Convert(BinaryTreeNode* root)
{
	assert(root);
	//list��ָ��˫�������β���
	BinaryTreeNode* list = NULL;
	ConvertNode(root, &list);

	//����ͷ���
	BinaryTreeNode* newHead = list;
	while (newHead && newHead->left)
	{
		newHead = newHead->left;
	}
	return newHead;
}


//��Ŀ�ߣ�����һ���ַ�������ӡ�����ַ������ַ����������С����������ַ���abc,���ӡ�����ַ�
//a,b,c�������г����������ַ���abc��acb��bca��cab��cba

//˼·�����ȷ�����һλ�ÿ��ܳ��ֵ����֣�Ȼ���������ֺͺ�������ֳַ������֣��Ժ����
//�ǲ�������ͬ�Ĳ�����Ȼ���������������ơ�
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