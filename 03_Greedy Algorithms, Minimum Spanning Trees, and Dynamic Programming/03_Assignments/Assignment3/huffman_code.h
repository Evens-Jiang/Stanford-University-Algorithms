/*
	Huffman's Algorithm
	(Given frequencies Pi as input)
	If |∑| = 2 return

		   Node
		0 /	  \ 1
		 A     B

	Let a, b belong to ∑ have the smallest frequencies.
	Let ∑' = ∑ with a, b replaced by new symbol ab.
	Define Pab = Pa + Pb.
	Recursively compute T' (for the alphabet ∑')
	Extend T' (with leaves ←→ ∑') to a tree T with leaves ←→ ∑ by splitting leaf ab into two leaves a & b.

	Return T
*/
#ifndef _HUFFMANCODE_H_
#define _HUFFMANCODE_H_

typedef struct huffman_node{
    int key, weight;
    struct huffman_node *left, *right;
}huffman_node_t, *huffman_node_p;

huffman_node_p combineNode(huffman_node_p leftNode, huffman_node_p rightNode){
    huffman_node_p newNode = malloc(sizeof(huffman_node_t));
    newNode->key = 0;
    newNode->weight = leftNode->weight + rightNode->weight;
    newNode->left = leftNode;
    newNode->right = rightNode;
    return newNode;
}

#endif