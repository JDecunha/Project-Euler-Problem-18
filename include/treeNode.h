#pragma once

class treeNode
{
	public:
		treeNode(int value, treeNode* pLeftCon, treeNode* pBottomLeftCon, treeNode* pBottomRightCon)
		: _value(value), _pLeftConnection(pLeftCon), _pBottomLeftConnection(pBottomLeftCon), _pBottomRightConnection(pBottomRightCon)
		{}

		treeNode* _pBottomLeftConnection;
		treeNode* _pBottomRightConnection;
		treeNode* _pLeftConnection;
		int _value;
};