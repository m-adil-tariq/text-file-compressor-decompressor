#include<iostream>
#include<fstream>
#include<bitset>
using namespace std;

template <typename T>
class ListNode {
	private:
	    T data;
	    ListNode<T>* next;
	    
	public:
	    ListNode(T d) { data = d;	next = NULL; }
	    
		void setNext(ListNode<T>* n) { next = n; }
		void setData(T d) { data = d; }
		
		ListNode<T>* getNext() { return next; }
		T getData() { return data; }
};

template <typename T>
class List {
private:
    ListNode<T>* head;
    int size;
public:
    List() { head = NULL; size = 0; }
    int getSize() { return size; }
    void insert(T d) 
	{
        ListNode<T>* newNode = new ListNode<T>(d);
        if (!head) 
			head = newNode;
			
        else 
		{
            ListNode<T>* temp = head;
            while (temp->getNext())
				temp = temp->getNext();
            temp->setNext(newNode);
        }
        size++;
    }
    T getAt(int index)
	{
        ListNode<T>* temp = head;
        for (int i = 0; i < index; i++) 
			temp = temp->getNext();
        return temp->getData();
    }
    void setAt(int index, T val)
	{
        ListNode<T>* temp = head;
        for (int i = 0; i < index; i++) 
			temp = temp->getNext();
        temp->setData(val);
    }
    int indexOf(T d) 
	{
        ListNode<T>* temp = head;
        for (int i = 0; i < size; i++)
		{
            if (temp->getData() == d) 
				return i;
            temp = temp->getNext();
        }
        return -1;
    }
};

class ReadTextFile {
	private:
	    List<char> chars;
	    List<int> freqs;
	    int totalUnique;
	
	public:
	    ReadTextFile() { totalUnique = 0; }
	    
	    void Read(string path) 
		{
	        ifstream file(path.c_str());
	        if(!file)
	        {
	        	cout<<"\n\nPath is not correct!!";
	        	return;
			}
	        char ch;
	        while (file.get(ch))
			{
	            int idx = chars.indexOf(ch);
	            if (idx == -1) 
				{
	                chars.insert(ch);
	                freqs.insert(1);
	                totalUnique++;
	            } 
				else 
	                freqs.setAt(idx, freqs.getAt(idx) + 1);
	        }
	        file.close();
	    }
	    void getData(int &a, List<char> &c, List<int> &f)
	    {
	    	for(int i = 0; i < totalUnique; i++)
	    	{
	    		c.insert(chars.getAt(i));
	    		f.insert(freqs.getAt(i));
			}
			a = totalUnique;
		}
};

class HeapNode{
	private:
		HeapNode *parent;
		HeapNode *left;
		HeapNode *right;
		HeapNode *internalLeft;
		HeapNode *internalRight;
		int value;
		char data;
		
	public:
		HeapNode(int v, char d = '\0')
		{
			value = v;
			data = d;
			parent = left = right = internalLeft = internalRight = NULL;
		}
		
		HeapNode* getLeft()	{ return left; }
		HeapNode* getRight() { return right; }
		HeapNode* getParent() {	return parent; }
		HeapNode* getInternalLeft()	{ return internalLeft; }
		HeapNode* getInternalRight() { return internalRight; }
		int getValue() { return value; }
		char getData() { return data; }
		
		void setLeft(HeapNode *n) { left = n; }
		void setRight(HeapNode *n) { right = n;	}
		void setParent(HeapNode *n)	{ parent = n; }
		void setinternalLeft(HeapNode *n) {	internalLeft = n; }
		void setInternalRight(HeapNode *n) { internalRight = n; }
		void setValue(int v) { value = v; }
		void setData(char d) { data = d; }
};

string toBinary(int d)
{
	if(d == 0) return "0";
	
	string s = "";
	while(d != 0)
	{
		s += (d % 2) + '0';
		d /= 2;
	}
	for(int i = 0; i < s.length() / 2; i++)
		swap(s[i], s[s.length() - 1 - i]);
		
	return s;
}

class Heap{
	private:
		HeapNode *Root;
		int size;
		
		void swapNodes(HeapNode *a, HeapNode *b)
		{
			HeapNode* tempL = a->getInternalLeft();
			HeapNode* tempR = a->getInternalRight();
			int tempV = a->getValue();
			char tempD = a->getData();
			
			a->setinternalLeft(b->getInternalLeft());
			a->setInternalRight(b->getInternalRight());
			a->setValue(b->getValue());
			a->setData(b->getData());
			
			b->setinternalLeft(tempL);
			b->setInternalRight(tempR);
			b->setValue(tempV);
			b->setData(tempD);
		}
		void HeapifyUp(HeapNode *n)
		{
			if(!n || !n->getParent())
				return;
				
			if(n->getValue() < n->getParent()->getValue())
			{
				swapNodes(n, n->getParent());
				HeapifyUp(n->getParent());
			}
		}
		void HeapifyDown(HeapNode *n)
		{
			if(!n) return;
			
			HeapNode *smallest = n;
			if(n->getLeft() && n->getLeft()->getValue() < smallest->getValue())
				smallest = n->getLeft();
			if(n->getRight() && n->getRight()->getValue() < smallest->getValue())
				smallest = n->getRight();
			
			if(smallest != n)
			{
				swapNodes(n, smallest);
				HeapifyDown(smallest);
			}
		}
		void display(HeapNode *n)
		{
			if(!n) return;
			
			cout<<n->getData()<<"("<<n->getValue()<<")"<<"  ";
			display(n->getLeft());
			display(n->getRight());
		}
		
	public:
		Heap() { Root = NULL; size = 0; }
		
		void Insert(HeapNode *n)
		{
			size++;
			if(!Root)
			{
				Root = n;
				return;
			}
			
			HeapNode *parent = Root;
			string path = toBinary(size);
			for(int i = 1; i < path.length() - 1; i++)
				(path[i] == '0') ? parent = parent->getLeft() : parent = parent->getRight();
				
			if(path[path.length() - 1] == '0')
				parent->setLeft(n);
			else
				parent->setRight(n);
				
			n->setParent(parent);
			HeapifyUp(n);
		}
		HeapNode* ExtractRoot()
		{
			if(!Root) return NULL;
			
			HeapNode *res = new HeapNode(Root->getValue(), Root->getData());
			res->setinternalLeft(Root->getInternalLeft());
			res->setInternalRight(Root->getInternalRight());
			
			if(size == 1)
			{
				delete Root;
				Root = NULL;
				size--;
				return res;
			}
			
			HeapNode *curr = Root, *parent = NULL;
			string path = toBinary(size);
			for(int  i = 1; i < path.length(); i++)
			{
				parent = curr;
				if(path[i] == '0')
					curr = curr->getLeft();
				else
					curr = curr->getRight();
			}
			swapNodes(Root, curr);
			
			if(parent->getLeft() == curr)
				parent->setLeft(NULL);
			else
				parent->setRight(NULL);
				
			delete curr;
			size--;
			HeapifyDown(Root);
			
			return res;
		}		
		HeapNode *getRoot()	{ return Root; }
		int getSize() { return size; }
		void Display()
		{
			cout<<"\nPreOrder : ";
			display(Root);
			cout<<"\n";
		}
};

class HuffmanTree{
	private:
		Heap *h;
		void GenerateCodes(HeapNode *n, string code, char *chars, string *codes, int &idx)
		{
			if(!n) return;
			
			if(n->getData() != '\0')
			{
				chars[idx] = n->getData();
				codes[idx] = code;
				idx++;
				return;
			}
			GenerateCodes(n->getInternalLeft(), code + "0", chars, codes, idx);
			GenerateCodes(n->getInternalRight(), code + "1", chars, codes, idx);
		}
		void printPreorder(HeapNode* node) 
		{
	        if (node == NULL) return;
	
	        if(node->getData() == '\0')
	        	cout<<"NULL"<<"("<<node->getValue()<<")  ";
	        else
	        	cout<<node->getData()<<"("<<node->getValue()<<")  ";
	        	
	        printPreorder(node->getInternalLeft());
	        printPreorder(node->getInternalRight());
    	}
		
	public:
		HuffmanTree(Heap *H) { h = H; }
		void BuildHuffmanTree()
		{
			while(h->getSize() > 1)
			{
				HeapNode *l = h->ExtractRoot();
				HeapNode *r = h->ExtractRoot();
				HeapNode *n = new HeapNode(l->getValue() + r->getValue(), '\0');
				n->setinternalLeft(l);
				n->setInternalRight(r);
				h->Insert(n);
			}
			Display();
		}
		void getCodes(char *chars, string *codes)
		{
			int idx = 0;
			GenerateCodes(h->getRoot(), "", chars, codes, idx);
		}
		void serializeTree(HeapNode* n, ofstream& out)
		{
		    if (!n) return;
		
		    if (n->getData() != '\0') {
		        out.put('1');              // leaf
		        out.put(n->getData());     // character
		    } else {
		        out.put('0');              // internal node
		        serializeTree(n->getInternalLeft(), out);
		        serializeTree(n->getInternalRight(), out);
		    }
		}
		HeapNode* getRoot()	{ return h->getRoot(); }
		void Display()
		{
			cout<<"\nPreorder:\n";
			printPreorder(h->getRoot());
			cout<<"\n\n";
		}
};

class WriteTextFile {
private:
    char* chars;
    string* codes;
    int noOfChar;

    string getCode(char c)
    {
        for (int i = 0; i < noOfChar; i++)
		{
            if (chars[i] == c)
                return codes[i];
        }
        return "";
    }

    unsigned char BitStringToByte(const string& bits)
    {
        bitset<8> b(bits);
        return (unsigned char)b.to_ulong();
    }

public:
    WriteTextFile(char* ch, string* cd, int n)
    { chars = ch; codes = cd; noOfChar = n; }

    void writeFile(string inputPath, string outputPath, HuffmanTree* tree)
    {
        ifstream in(inputPath.c_str());
        ofstream out(outputPath.c_str(), ios::binary);

        if (!in || !out)
		{
            cout << "File error!\n";
            return;
        }

        tree->serializeTree(tree->getRoot(), out);

        out.put('#');

        long long textLength = 0;
        char temp;
        while (in.get(temp)) textLength++;

        in.clear();
        in.seekg(0);

        out.write(reinterpret_cast<char*>(&textLength), sizeof(textLength));

        string buffer = "";
        char curr;

        while (in.get(curr))
        {
            buffer += getCode(curr);

            while (buffer.length() >= 8)
            {
                out.put(BitStringToByte(buffer.substr(0, 8)));
                buffer.erase(0, 8);
            }
        }

        if (!buffer.empty())
        {
            while (buffer.length() < 8)
                buffer += "0";

            out.put(BitStringToByte(buffer));
        }

        in.close();
        out.close();
    }
};

class DecodeBinaryFile{
	private:
		string inputPath;
		string outputPath;
		
		HeapNode* deserializeTree(ifstream& in)
		{
		    char flag;
		    in.get(flag);
		
		    if (flag == '1')
			{
		        char c;
		        in.get(c);
		        return new HeapNode(0, c);
		    }
		
		    HeapNode* n = new HeapNode(0);
		    n->setinternalLeft(deserializeTree(in));
		    n->setInternalRight(deserializeTree(in));
		    return n;
		}
		void display(HeapNode *n)
		{
			if(!n) return;
			
			if(n->getData() != '\0')
				cout<<"("<<n->getData()<<")  ";
			else
				cout<<"(NULL)  ";
				
			display(n->getInternalLeft());
			display(n->getInternalRight());
		}
		
	public:
		DecodeBinaryFile(string in, string out)
		{
			inputPath = in;
			outputPath = out;
		}
		void Decode()
		{
			ifstream in(inputPath.c_str(), ios::binary);
			ofstream out(outputPath.c_str());
			
			HeapNode* root = deserializeTree(in);
			cout<<"Step 1: Reading data from file and reconstructing Huffman Tree:\n";
			system("pause");

			cout<<"PreOrder: ";
			display(root);
			cout<<"\n\n";
			char sep;
			in.get(sep);
			
			long long textLength;
			in.read(reinterpret_cast<char*>(&textLength), sizeof(textLength));
	
			cout<<"Step 2: Traversing the Huffman Tree with respect to compressed data bits from binary files:\n";
			system("pause");

			HeapNode* curr = root;
			long long count = 0;
			char byte;
			
			while(in.get(byte) && count < textLength)
			{
			    for(int i = 7; i >= 0; i--)
			    {
			        bool bit = (byte >> i) & 1;
			        curr = bit ? curr->getInternalRight() : curr->getInternalLeft();
			
			        if(curr->getData() != '\0')
			        {
			            out.put(curr->getData());
			            count++;
			            cout<<curr->getData();
			            curr = root;
			            if(count == textLength) break;
			        }
			    }
			}
			cout<<"\nStep 3:Writing this Data to "<<outputPath<<endl;
			system("pause");
			cout<<"\nData Written!!";
			in.close(); out.close();
		}
};

void Compress()
{
	cout<<"Enter the path of the Text File: \n";
	cout<<">> ";
	string txt;
	cin>>txt;
	
	cout<<"\nStep 1: Reading Text File\n";
	system("pause");

	ReadTextFile reader;
	reader.Read(txt);
	
	int noOfChar;
	List<char> chars;
	List<int> freqs;
	
	reader.getData(noOfChar, chars, freqs);
	
	if(noOfChar == 0)
		{ cout<<"File Empty!!"; return; }
	
	cout<<"No of unique characters: "<<noOfChar;
	cout<<"\n\nCharacter \tFrequency\n\n";
	for(int i = 0; i < noOfChar; i++)
		cout<<"    "<<chars.getAt(i)<<"\t\t   "<<freqs.getAt(i)<<"\n";
		
	cout<<"\n";
	
	cout<<"Step 2: Building a MinHeap from obtained data:\n";
	system("pause");

	Heap *heap = new Heap();
	for(int i = 0; i < noOfChar; i++)
	{
		heap->Insert(new HeapNode(freqs.getAt(i), chars.getAt(i)));
		cout<<"\n\nAfter Inserting "<<chars.getAt(i)<<"("<<freqs.getAt(i)<<")\n";
		heap->Display();
	}
	
	cout<<"\nStep 3: Building Huffman Tree from the MinHeap:\n\n";
	system("pause");

	HuffmanTree *ht = new HuffmanTree(heap);
	ht->BuildHuffmanTree();
	char* finalChars   = new char[noOfChar];
    string* finalCodes = new string[noOfChar];
    ht->getCodes(finalChars, finalCodes);
    
    cout<<"\nStep 4: Extracting Codes:\n\n";
   	system("pause");

    cout<<"Character\tCode\n\n";
    for(int i = 0; i < noOfChar; i++)
    	cout<<"    "<<finalChars[i]<<"\t\t"<<finalCodes[i]<<endl;
    	
    cout<<"\nStep 5: Write Compressed Binary File\n";
   	system("pause");

    WriteTextFile writer(finalChars, finalCodes, noOfChar);
    string bin = txt;
	bin.erase(bin.length() - 4, 4);
	bin += "_compressed.bin";
    writer.writeFile(txt, bin, ht);
    cout<<"\nFile Written at: "<<bin;
}
void Decompress()
{
	cout<<"Enter the Path of the Binary File: ";
	cout<<">> ";
	string bin;
	cin>>bin;
		
	string txt = bin;
	txt.erase(txt.length() - 4, 4);
	txt += "_decompressed.txt";
	DecodeBinaryFile decoder(bin, txt);
	decoder.Decode();
}

int main()
{
	cout<<"Text File Compressor and Decompressor\n\n";

	cout<<"\n\nEnter Your choice ( 1 / 2 / 3) :\n";
	cout<<"1 - Compress a Text File to Binary File\n";
	cout<<"2 - Decompress a Binary File to a Text File\n";
	cout<<"3 - Exit\n\n";
	int c;
	cout<<">> ";
	cin>>c;
	cout<<"\n\n";
	system("pause");
	switch(c)
	{
		case 1:
			Compress();
			break;
		case 2:
			Decompress();
			break;
		case 3:
			return 0;
		default:
			cout<<"Invalid Choice!! Try Again\n\n";
			break;
	}
}
