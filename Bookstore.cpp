#include<iostream>
#include<fstream>

using namespace std;

const int HASH_TABLE_SIZE = 10;

struct Book
{
    string b_id;
    string b_name;
    string a_name;
    int no_copy;
};

struct HashNode
{
    Book book;
    HashNode* next;
};

class bookshop
{
private:
    HashNode* hashTable[HASH_TABLE_SIZE];

public:
    bookshop()
    {
        for (int i = 0; i < HASH_TABLE_SIZE; i++)
        {
            hashTable[i] = nullptr;
        }
    }

    int calculateHash(string b_id)
    {
        int sum = 0;
        for (char c : b_id)
        {
            sum += c;
        }
        return sum % HASH_TABLE_SIZE;
    }

    void insertBook(Book book)
    {
        int hashValue = calculateHash(book.b_id);

        HashNode* newNode = new HashNode;
        newNode->book = book;
        newNode->next = nullptr;

        if (hashTable[hashValue] == nullptr)
        {
            hashTable[hashValue] = newNode;
        }
        else
        {
            HashNode* current = hashTable[hashValue];
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }

        ofstream file("book.txt", ios::app);
        if (file.is_open())
        {
            file << book.b_id << " " << book.b_name << " " << book.a_name << " " << book.no_copy << "\n";
            file.close();
        }
    }

    Book* searchBook(string b_id)
    {
        int hashValue = calculateHash(b_id);

        HashNode* current = hashTable[hashValue];
        while (current != nullptr)
        {
            if (current->book.b_id == b_id)
            {
                return &(current->book);
            }
            current = current->next;
        }

        return nullptr;
    }

    void deleteBook(string b_id)
    {
        int hashValue = calculateHash(b_id);

        HashNode* previous = nullptr;
        HashNode* current = hashTable[hashValue];

        while (current != nullptr)
        {
            if (current->book.b_id == b_id)
            {
                if (previous == nullptr)
                {
                    hashTable[hashValue] = current->next;
                }
                else
                {
                    previous->next = current->next;
                }
                delete current;
                break;
            }

            previous = current;
            current = current->next;
        }

        // Update the file after deleting the book
        ofstream file("book.txt");
        if (file.is_open())
        {
            for (int i = 0; i < HASH_TABLE_SIZE; i++)
            {
                HashNode* currentNode = hashTable[i];
                while (currentNode != nullptr)
                {
                    file << currentNode->book.b_id << " " << currentNode->book.b_name << " " << currentNode->book.a_name << " " << currentNode->book.no_copy << "\n";
                    currentNode = currentNode->next;
                }
            }
            file.close();
        }
    }

    void control_panel();
    void add_book();
    void show_books();
    void check_book();
    void update_book();
    void del_book();
};

void bookshop::control_panel()
{
    system("cls");
    cout << "\n\n\t\t\t\t\t  _______________________________";
    cout << "\n\t\t\t\t\t  ||BOOK STORE MANAGEMENT SYSTEM||";
    cout << "\n\t\t\t\t\t  *******************************";
    cout << "\n\n\n\t\t\t\t\t\t 1. Add New Book";
    cout << "\n\n\t\t\t\t\t\t 2. Display Books";
    cout << "\n\n\t\t\t\t\t\t 3. Check Specific Book";
    cout << "\n\n\t\t\t\t\t\t 4. Update Book";
    cout << "\n\n\t\t\t\t\t\t 5. Delete Book";
    cout << "\n\n\t\t\t\t\t\t 6. Exit";
}

void bookshop::add_book()
{
    system("cls");
    Book book;
    cout << "\n\n\n\t\t\t\t\t\t |Add New Book|";
    cout << "\n\t\t\t\t\t\t----------------";
    cout << "\n\n Book ID : ";
    cin >> book.b_id;
    cout << "\n\n Book Name : ";
    cin >> book.b_name;
    cout << "\n\n Author Name : ";
    cin >> book.a_name;
    cout << "\n\n No. of Copies : ";
    cin >> book.no_copy;

    insertBook(book);

    cout << "\n\n Book Added Successfully!";
}

void bookshop::show_books()
{
    system("cls");
    ifstream file("book.txt");
    if (!file)
    {
        cout << "\n\n File Opening Error!";
        return;
    }

    Book book;
    cout << "\n\n\n\t\t\t\t\t\t |Display Books|";
    cout << "\n\t\t\t\t\t\t-----------------";
    cout << "\n\n Book ID\t\tBook Name\t\tAuthor Name\t\tNo. of Copies\n\n";

    while (file >> book.b_id >> book.b_name >> book.a_name >> book.no_copy)
    {
        cout << "  " << book.b_id << "\t\t\t" << book.b_name << "\t\t\t" << book.a_name << "\t\t\t" << book.no_copy << "\n\n";
    }

    file.close();
}

void bookshop::check_book()
{
    system("cls");
    string b_id;
    cout << "\n\n\n\t\t\t\t\t\t |Check Specific Book|";
    cout << "\n\t\t\t\t\t\t-----------------------";
    cout << "\n\n\n Book ID : ";
    cin >> b_id;

    Book* book = searchBook(b_id);
    if (book != nullptr)
    {
        system("cls");
        cout << "\n\n\t\t\t\t\t\t  Check Specific Book";
        cout << "\n\n Book ID : " << book->b_id;
        cout << "\n\n Name : " << book->b_name;
        cout << "\n\n Author Name : " << book->a_name;
        cout << "\n\n No. of Copies : " << book->no_copy;
    }
    else
    {
        cout << "\n\n Book ID Not Found!";
    }
}

void bookshop::update_book()
{
    system("cls");
    string b_id;
    cout << "\n\n\n\t\t\t\t\t\t |Update Book Record|";
    cout << "\n\t\t\t\t\t\t----------------------";
    cout << "\n\n Book ID : ";
    cin >> b_id;

    Book* book = searchBook(b_id);
    if (book != nullptr)
    {
        system("cls");
        cout << "\n\n\t\t\t\t\tUpdate Book Record";
        cout << "\n\n\n New Book Name : ";
        cin >> book->b_name;
        cout << "\n\n Author Name : ";
        cin >> book->a_name;
        cout << "\n\n No. of Copies : ";
        cin >> book->no_copy;

        // Update the file after modifying the book
        ofstream file("book.txt");
        if (file.is_open())
        {
            for (int i = 0; i < HASH_TABLE_SIZE; i++)
            {
                HashNode* currentNode = hashTable[i];
                while (currentNode != nullptr)
                {
                    file << currentNode->book.b_id << " " << currentNode->book.b_name << " " << currentNode->book.a_name << " " << currentNode->book.no_copy << "\n";
                    currentNode = currentNode->next;
                }
            }
            file.close();
        }

        cout << "\n\n Book Record Updated Successfully!";
    }
    else
    {
        cout << "\n\n Book ID Not Found!";
    }
}

void bookshop::del_book()
{
    system("cls");
    string b_id;
    cout << "\n\n\n\t\t\t\t\t\t |Delete Book Record|";
    cout << "\n\t\t\t\t\t\t-----------------------";
    cout << "\n\n Book ID : ";
    cin >> b_id;

    Book* book = searchBook(b_id);
    if (book != nullptr)
    {
        deleteBook(b_id);
        cout << "\n\n Book Record Deleted Successfully!";
    }
    else
    {
        cout << "\n\n Book ID Not Found!";
    }
}

int main()
{
cout<<"\n\n\t\t Book Store Management"<<endl;
	  string username,password;
    cout<<"\n\n\n\t\t****Signup****"<<endl;
	cout<<"\t\tEnter new username: ";
	cin>>username;
	cout<<"\t\tEnter new password: ";
	cin>>password;
	cout<<"\t\tYour new id is creating please wait";

	for(int i=0;i<6;i++)
	{
		cout<<".";
		// Sleep(500);
	}
	cout<<"\n\t\tYour id created successfully";
	// Sleep(2000);
	start:
	system("CLS");
	string usrn,pswd;
	cout<<"\n\n\t\tSuperMarket Billing System"<<endl;
	cout<<"\n\n\n\t\t   LOGIN"<<endl;
	cout<<"\t\tEnter username: ";
	cin>>usrn;
	cout<<"\t\tEnter password: ";
	cin>>pswd;
	if(usrn==username&&pswd==password)
{
    bookshop b;
    int choice;


    while (true)
    {
        b.control_panel();
        cout << "\n\n Enter your choice (1-6) : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            b.add_book();
            break;
        case 2:
            b.show_books();
            break;
        case 3:
            b.check_book();
            break;
        case 4:
            b.update_book();
            break;
        case 5:
            b.del_book();
            break;
        case 6:
            exit(0);
        default:
            cout << "\n\n Invalid Choice!";
        }
        cout << "\n\n";
        system("pause");
    }

    return 0;
}
}