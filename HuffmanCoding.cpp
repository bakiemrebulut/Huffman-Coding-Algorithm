#include <iostream>

using namespace std;
class Node  
{  
    public: 
    int Freq;  
    char data;
    string code;
    Node *begin;
    Node *Next=nullptr;  
	Node *left=nullptr;
    Node *right=nullptr;
    Node* End(Node* begin)
    {
    	head=begin;
    	while(head->Next!=nullptr)
		{
			head=head->Next;
		}
		return head;
    }
    Node* End()
    {
    	head=Next;
    	while(head->Next!=nullptr)
		{
			head=head->Next;
		}
		return head;
    }
private:
	Node *head;
};

void printList(Node* node) 
{ 
    cout<<"Data of list:"<<endl;
    Node* n;
    n=node;
    while (n != nullptr) { 
        cout << n->data << " "; 
        n = n->Next; 
    } 
    cout<<endl;
} 

void printFreq(Node* node) 
{ 
    cout<<"Frequencies of list:"<<endl;
    Node* n;
    n=node;
    while (n != nullptr) { 
        cout << n->Freq << " "; 
        n = n->Next; 
    } 
    cout<<endl;
} 
void printTreeLeftAndRight(Node* node) 
{ 
        Node* n;
        Node* n2;
        n=node;
        while (n != nullptr) { 
	    	
	        if(n->right!=nullptr)
	        {
	        	n2=n->right;
	        	cout <<"right of "<<n->data<<": "<< n2->data << " "<<endl;; 
	        }
	        if(n->left!=nullptr)
	        {
	        	n2=n->left;
	        	cout <<"left of "<<n->data<<": "<< n2->data << " "<<endl; 
	        }
	        n = n->Next; 
        }
} 
void printTreeCode(Node* node) 
{ 
        cout<<endl<<"Codes of Leaves:"<<endl<<"----------------";
        Node* n;
        n=node;
        while (n != nullptr) 
        { 
	    	
	       	cout <<endl<<n->data<<": "<<n->code; 
	        n = n->Next; 
        }
        cout<<endl<<"---------"<<endl;
} 
void push(Node** head_ref, char new_data)  
{  
    Node* new_node = new Node(); 
  
    new_node->data = new_data;  
  	new_node->Freq = 1;
    new_node->Next = (*head_ref);  
  
    (*head_ref) = new_node;  
}  
void sort(Node** Chars)
{
	Node* temp=*Chars;
	Node* temp2=temp;
	Node* Sorted=temp;

	while(Sorted!=nullptr)
	{
		temp=temp2;
		while(temp->Next!=nullptr)
		{
			if(temp->Freq > temp->Next->Freq)
			{
				int tempFreq=temp->Freq;
				temp->Freq=temp->Next->Freq;
				temp->Next->Freq=tempFreq;

				char tempChar=temp->data;
				temp->data=temp->Next->data;
				temp->Next->data=tempChar;

				
				Node* tempNode=temp->left;
				temp->left=temp->Next->left;
				temp->Next->left=tempNode;
				
				tempNode=temp->right;
				temp->right=temp->Next->right;
				temp->Next->right=tempNode;
				

				
			}
			temp=temp->Next;
		}
		Sorted=Sorted->Next;
	}
	*Chars=temp2;
}

Node* insert(string message)
{
	Node *Chars=nullptr;
	Node *tempChars=nullptr;
	bool inserted=true;

	for (int i=0; i<message.length();i++)
	{
		if(Chars==nullptr)//only for first time
		{
			push(&Chars,message[i]);
		}
		else
		{
			tempChars=Chars;
			while(tempChars!=nullptr )
			{
				if(message[i]==tempChars->data)
				{
					tempChars->Freq=tempChars->Freq+1;
					inserted=true;
					break;
				}
				inserted=false;
				tempChars=tempChars->Next;
			}
			if(!inserted)
			{
				push(&Chars,message[i]);
			}
		}
	}
	return Chars;
}
//char spChar='A'-1;
Node* huffmanTree(Node* Chars)
{	
	Node* tChars=nullptr;
	Node* temp=new Node();
	Node* left=new Node();
	Node* right=new Node();
	
	if(Chars==nullptr||Chars->Next==nullptr )
	{
		sort(&tChars);
		printList(tChars);cout<<"in loop"<<endl;

		return tChars;
	}
	if(Chars->Next->Next==nullptr )
	{
		temp=new Node();
		//spChar++;
		temp->Next=tChars;
		//temp->data=spChar;
		temp->Freq=Chars->Freq+Chars->Next->Freq;
		temp->left=Chars;
		temp->right=Chars->Next;
		Chars=Chars->Next;
		Chars=Chars->Next;
		tChars=temp;
		sort(&Chars);
		sort(&temp);

		return tChars;
	}


	temp=new Node();
	//spChar++;
	temp->Next=tChars;
	//temp->data=spChar;
	temp->Freq=Chars->Freq+Chars->Next->Freq;
	temp->left=Chars;
	temp->right=Chars->Next;
	Chars=Chars->Next;
	Chars=Chars->Next;
	tChars=temp;
	sort(&Chars);
	sort(&temp);
	Node* end=tChars->End(tChars);//end of tChars
	Node* head=Chars->End(Chars); //head of Chars
	head->Next=tChars;//add tChars to Chars
	end->Next=huffmanTree(Chars);//recursion with new list

	return tChars;
}


string compress(string message,Node* Chars)
{
	Node* temp=Chars;
	string turn;
	for (int i=0;i<message.length();i++)
	{
		temp=Chars;
		while(temp->Next!=nullptr)
		{
			if(message[i]==temp->data)
			{
				turn+=temp->code;
				break;
			}
			temp=temp->Next;
		}
	}
	return turn;
}

string decompress(string message,Node* head)
{
	string ans = ""; 
    Node* curr = head; 
    for (int i=0;i<message.size();i++) 
    { 
        if (message[i] == '0') 
           curr = curr->left; 
        else
           curr = curr->right; 
  
        // reached leaf node 
        if (curr->left==nullptr and curr->right==nullptr) 
        { 
            ans += curr->data; 
            curr = head; 
        } 
    } 
    return ans+'\0'; 
}
void comCode(Node** head)
{
	Node* temp=*head;
	
	if(temp->left!=nullptr)
	{
		temp->right->code=temp->code+'1';
		temp->left ->code=temp->code+'0';
		comCode(&temp->right);
		comCode(&temp->left);

	}
	else return;
}
int main(){
	string message="Hacettepe University Department of Electrical and Electronics Engineering ELE-411 Data Structure Course Implementation Project";
	cout<<"Input:"<<message<<endl;
	Node* Chars=insert(message);
	cout<<endl<<"Inserted Chars:"<<endl;
	printList(Chars);
	printFreq(Chars);

	sort(&Chars); 
	cout<<endl<<"Sorted list:"<<endl;
	printList(Chars);
	printFreq(Chars);

	Node* head=Chars->End();//end node of list for adding new chars to the Chars
	head->Next=huffmanTree(Chars);
	cout<<"Data and Frequencies in Tree:"<<endl;
	printList(Chars);
	printFreq(Chars);
	cout<<endl<<"Left and Rights of Each Leaves :"<<endl;
	printTreeLeftAndRight(Chars); cout<<endl;
	
	head=Chars->End();
	
	comCode(&head);

	printTreeCode(Chars) ;
	
	cout<<"message   :"<<endl<<message<<endl<<endl;

	string compressed=compress(message,Chars);
	cout<<"Compressed:"<<endl<<compressed<<endl<<endl;

	cout<<"length of compressed message  :"<<compressed.length()<<endl;
	cout<<"length of uncompressed message:"<<message.length()*8<<endl;
	
	string decompressed=decompress(compressed,head);
	cout<<endl<<"Decompressed:"<<endl<<decompressed<<endl<<endl;
	return 0;
}