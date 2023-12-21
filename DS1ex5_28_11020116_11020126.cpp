// �q��T 11020116 ��q�s  �q��T 11020126 �G����
// ���ϥ�C++11

#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void GetCommand(int &command)
{
    while (true) {
        std::cout << "\n";
        std::cout << "***** Pokemon Tree and Heap *****\n";
        std::cout << "* 0. QUIT                       *\n";
        std::cout << "* 1. Read a file to build BST   *\n";
        std::cout << "* 2. Transform it into Max Heap *\n";
        std::cout << "*********************************\n";
        std::cout << "Input a choice(0, 1, 2): ";
        std::cin >> command;

        // If the command is valid, exit the loop
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nCommand does not exist!\n";
            continue;
        }
        if (command >= 0 && command <= 2) {
            break;
        } else {
            std::cout << "\nCommand does not exist!" << "\n";
        }
    }
}

void Inputtxt(ifstream &inputFile, string &filenum, bool &check) // Ū�Jinput��txt
{
    string filename;
    while(filename != "0"){
    	cout << "\nInput a file number [0: quit]: ";
    	cin >> filename;
    	if(filename == "0"){
    		break;
		}
    	filenum = filename;
    	filename = "input" + filename + ".txt";
    	inputFile.open(filename);
    	if (!inputFile) {
    	    cout << "\n###" << filename << " does not exist! ###" << endl;
    	    cin.clear();
    	    check = false;
    	} else {
    	    check = true;
    	    break;
    	}
	} 

}

struct Pokemondata
{ // �ΨӦU�ۦsŪ�i���Ҧ����
	int number = -1;
    string name ;
    string type1;
    string type2 = "-1";
    int total;
    int hp;
    int atk;
    int def;
    int spatk;
    int spdef;
    int speed;
    int generation;
    string legendary;
};


class List { //�Hvector�إ�Schooldata��List 
private: 
	vector<Pokemondata> alldata;

public:
    void clearlist() { // �M�ŰO���� 
		alldata.clear();
    }
    void add(Pokemondata data){ // �[�Jlist 
    	alldata.push_back(data);
	}
    int getsize(){ // �^�Ǹ�Ƽƶq 
    	return alldata.size();
	}	
    Pokemondata getdata(int i) { // �H�U���O�����i�Ӹ�ƪ��Y����T 
		return alldata[i];
    }
	int gethp(int i){
		Pokemondata temp = alldata[i];
		return temp.hp; 
	}

	void printlist(){
		Pokemondata data;
		for(int i = 0; i < alldata.size(); i ++){
			data = alldata[i];
			if(i<9){
				cout << "[ " << i+1 << "]\t";
			}
			else{
				cout << "[" << i+1 << "]\t";
			}
			cout << data.number << "\t";
			cout << data.name << "\t\t\t";
			if(data.name.length() < 8){
				cout << "\t";
			}

			cout << data.type1 << "\t";
			if(data.type1.length() < 8){
				cout << "\t";
			}
			cout << data.hp << "\t";
			cout << data.atk << "\t";	
			cout << data.def << "\n";			
		}
	}

};

// for�إ�BST���`�I�A�C�Ӹ`�I�s�@��schooldata
template <typename T> class TreeNode
{
public:
    T data;
    Pokemondata pokemondata;
    TreeNode *left;
    TreeNode *right;
    TreeNode(T val, Pokemondata target) : data(val), pokemondata(target), left(nullptr), right(nullptr) {}
};

template <typename T> class BinarySearchTree
{
private:
    TreeNode<T> *root;

    TreeNode<T> *insert(TreeNode<T> *node, T value, Pokemondata data)
    {
        if (node == nullptr) {
            return new TreeNode<T>(value, data);
        }

        if (value < node->data) {
            node->left = insert(node->left, value, data);
        } else if (value >= node->data) {
            node->right = insert(node->right, value, data);
        }

        return node;
    }
    TreeNode<T>* findMin(TreeNode<T>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode<T>* findMax(TreeNode<T>* node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    // �d�߾�
    int height(TreeNode<T> *node)
    {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return 1 + std::max(leftHeight, rightHeight);
    }

    // ����Ŷ�
    void clear(TreeNode<T> *node)
    {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);

        delete node;
    }




public:
    // for�~���I�s
    BinarySearchTree() : root(nullptr) {}

    void insert(T value, Pokemondata data)
    {
        root = insert(root, value, data);
    }
    Pokemondata findMin() {
		return findMin(root)->pokemondata;
    }

    Pokemondata findMax() {
		
        return findMax(root)->pokemondata;
    }

    int getHeight()
    {
        return height(root);
    }

    bool search(int value)
    {
        return search(root, value) != nullptr;
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }

};

string removeCommas(string str) {
    str.erase(remove(str.begin(), str.end(), ','), str.end());
    str.erase(remove(str.begin(), str.end(), '\"'), str.end());

    return str;
}



int main()
{
    int command = 0;
    GetCommand(command);
    ifstream inputFile;
    ofstream outputFile;
    List datalist;
    BinarySearchTree<int> hptree;
    string filenum;
    bool check = false;

    // ����O����0�A�N�~��Ū�����O
    while (command != 0) {
        if (command == 1) {
        	Inputtxt(inputFile, filenum, check);
            string s;   
			getline(inputFile, s);
			s.clear();       
            if(inputFile.eof() || check == false){ // �p�Gtxt���S�F�� �N���� 
            	if(inputFile.eof()){
            		cout << "\n### Get nothing from the file input" << filenum << ".txt ! ###\n" ;	
				}
			}
			else{
				datalist.clearlist();
				hptree.clear();
				cout << "        #       Name                            Type 1          HP      Attack  Defense" << "\n";
				while(!inputFile.eof()){ //��stringstream���Ψç��Ʀs�ilist 
					Pokemondata data;
					string temp;
					stringstream ss;
					getline(inputFile, s);
					ss << s;
					
					ss >> data.number;
					ss >> data.name;
					ss >> data.type1;
					ss >> data.type2;
					
					
					ss >> data.total;
					ss >> data.hp;
					ss >> data.atk;
					ss >> data.def;
					ss >> data.spatk;
					ss >> data.spdef;
					ss >> data.speed;
					ss >> data.generation;
					ss >> data.legendary;

					if(data.number!=-1){ //�קK����F�� 
						datalist.add(data);
					}
					
					ss.clear();
					ss.str("");

				}

				datalist.printlist();
				for(int i = 0; i < datalist.getsize(); i ++){
					hptree.insert(datalist.gethp(i), datalist.getdata(i)); //�H���~�H�Ƭ�key�إߤ@��Tree 
				}

				cout << "HP tree height = " << hptree.getHeight() << "\n";
				Pokemondata temp = hptree.findMin();
				cout << "Leftmost node:\n";
				cout << "        #       Name                            Type 1          HP      Attack  Defense" << "\n";
				for(int i = 0; i < datalist.getsize(); i ++){
					if(datalist.getdata(i).number == temp.number){
						if(i<9){
							cout << "[ " << i+1 << "]\t";
						}
						else{
							cout << "[" << i+1 << "]\t";
						}
						cout << temp.number << "\t";
						cout << temp.name << "\t\t\t";
						if(temp.name.length() < 8){
							cout << "\t";
						}

						cout << temp.type1 << "\t";
						if(temp.type1.length() < 8){
							cout << "\t";
						}
						cout << temp.hp << "\t";
						cout << temp.atk << "\t";	
						cout << temp.def << "\n";	
					}
				}
				temp = hptree.findMax();
				cout << "Rightmost node:\n";
				cout << "        #       Name                            Type 1          HP      Attack  Defense" << "\n";
				for(int i = 0; i < datalist.getsize(); i ++){
					if(datalist.getdata(i).number == temp.number){
						if(i<9){
							cout << "[ " << i+1 << "]\t";
						}
						else{
							cout << "[" << i+1 << "]\t";
						}
						cout << temp.number << "\t";
						cout << temp.name << "\t\t\t";
						if(temp.name.length() < 8){
							cout << "\t";
						}

						cout << temp.type1 << "\t";
						if(temp.type1.length() < 8){
							cout << "\t";
						}
						cout << temp.hp << "\t";
						cout << temp.atk << "\t";	
						cout << temp.def << "\n";	
					}
				}				

			}

			inputFile.close();
        }
		else {
            printf("Command does not exist!\n"); // ���~���O
        }
        GetCommand(command);
    }

    return 0;
}
