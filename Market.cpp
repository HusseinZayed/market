#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
using namespace std;
class Product
{
private:
	char Id[5];
	char Name[20];
	char Price[10];
	char Qty[10];
	char Pick [50];
public:
	friend ostream &operator << (ostream &output, Product &P)
	{
		output << fixed << left << '|' << setw(5) << P.Id <<  '|' << setw(20) <<  P.Name <<  '|' << setw(10) << P.Price <<  '|' << setw(29) << P.Qty << '|' << endl;
		return output;
	}
	friend istream &operator >> (istream &input, Product &P)
	{
		cout << "| - Enter the product's Name      :";
		input.getline(P.Name, 20);
		cout << "| - Enter the product's Price     :";
		input.getline(P.Price, 10);
		cout << "| - Enter the product's Quantity  :";
		input.getline(P.Qty, 10);
		return input;
	}
	bool operator==(Product & P){
		if (strcmp(Id, P.Id) == 0)
			return true;
		else
			return false;
	}
	void read(fstream &F)
	{
		F.getline(Id, 5, '|');
		F.getline(Name, 20, '|');
		F.getline(Price, 10, '|');
		F.getline(Qty, 10, '\n');
	}
	void Write(fstream &F)
	{
		strcpy(Pick,"");
		strcat(Pick,Id);
		strcat(Pick,"|");
		strcat(Pick,Name);
		strcat(Pick,"|");
		strcat(Pick,Price);
		strcat(Pick,"|");
		strcat(Pick,Qty);
		strcat(Pick,"\n");
		F << Pick;
	}
	void SetId()
	{
		cout << "| - Enter the product's ID (####) :";
		cin.getline(Id, 5);
	}
};

void Update()
{
    char O[3];
	Product Reader[100], Pro;
	fstream F;
	do{
		bool Found = false;
		int counter = -1;
		F.open("Store.txt", ios::in);
		Pro.SetId();
		if(F)
            while (!F.eof()){
                counter++;
                Reader[counter].read(F);
            }
		F.close();
		F.open("Store.txt",ios::out);
		for(int i = 0; i < counter; i++){
            if((Pro == Reader[i])){
                    cout << "************************************************************************" << endl;
                    cout << fixed << left << '|' << setw(5) << "Id" <<  '|' << setw(20) <<  "Name" <<  '|' << setw(10) << "Price" <<  '|' << setw(29) << "Qty" << '|' << endl;
                    cout << Reader[i];
                    cout << "\n" << endl;
                    cin >> Reader[i];
                    Reader[i].Write(F);
                Found = true;
                }
            else
                Reader[i].Write(F);
        }
        F.close();
		if (Found)
            cout << "| - The product Updated successfully !" << endl;
		else
			cout << "| - The product not found !" << endl;

        cout << "| - To Add another Product Enter (Y/y) : "; cin.getline(O,3);
	} while (O[0] == 'Y' || O[0] == 'y');
}

void Delete()
{
    char O[3];
	Product Reader[100], Pro;
	fstream F;
	do{
		bool Found = false;
		int counter = -1;
		F.open("Store.txt", ios::in);
		Pro.SetId();
		if(F)
            while (!F.eof()){
                counter++;
                Reader[counter].read(F);
            }
		F.close();
		F.open("Store.txt",ios::out);
		for(int i = 0; i < counter; i++)
        {
            if((Pro == Reader[i]))
                Found = true;
            else
                Reader[i].Write(F);
        }
        F.close();
		if (Found)
            cout << "| - The product deleted successfully !" << endl;
		else
			cout << "| - The product not found !" << endl;

        cout << "| - To Add another Product Enter (Y/y) : "; cin.getline(O,3);
	} while (O[0] == 'Y' || O[0] == 'y');
}
void Search()
{
	char O[3];
	Product Reader, Pro;
	fstream F;
	do{
		bool Found = false;
		F.open("Store.txt", ios::in);
		Pro.SetId();
		if(F)
            while (!F.eof()){
                Reader.read(F);
                if (Pro == Reader){
                    Found = true;
                    break;
                }
            }
		F.close();
		if (Found){
            cout << "****************************************************************************" << endl;
            cout << fixed << left << '|' << setw(5) << "Id" <<  '|' << setw(20) <<  "Name" <<  '|' << setw(10) << "Price" <<  '|' << setw(29) << "Qty" << '|' << endl;
            cout << Reader;
            cout << "\n" << endl;
		}
		else
			cout << "| - The product not found !" << endl;
        cout << "| - To Add another Product Enter (Y/y) : "; cin.getline(O,3);
	} while (O[0] == 'Y' || O[0] == 'y');
}
void Add ()
{
	char O[3];
	Product Reader, Pro;
	fstream F;
	do{
		bool UID = true;
		F.open("Store.txt", ios::in);
		Pro.SetId();
		if(F)
		while (!F.eof()){
			Reader.read(F);
			if (Pro == Reader){
				UID = false;
				break;
			}
		}
		F.close();
		if (UID){
			F.open("Store.txt", ios::app);
			cin >> Pro;
			Pro.Write(F);
			cout << "| - The product successfully added !" << endl;
			F.close();
		}
		else
			cout << "| - The product is already exit !" << endl;
        cout << "| - To Add another Product Enter (Y/y) : "; cin.getline(O,3);
	} while (O[0] == 'Y' || O[0] == 'y');
}
void DisplayAll()
{
	Product Reader;
	fstream F;
	F.open("Store.txt",ios::in);

    cout << fixed << left << '|' << setw(5) << "Id" <<  '|' << setw(20) <<  "Name" <<  '|' << setw(10) << "Price" <<  '|' << setw(29) << "Qty" << '|' << endl;
    if(F)
		while (!F.eof()){
			Reader.read(F);
            if(!F.eof())
            cout << Reader;
		}
  cout << "\n" << endl;
    F.close();
    cout<<"*******************************************************************\n";
}
int main()
{
	char O[3];
	while (true)
	{

		cout << " 1- Add    a new product                                           " << endl;
		cout << " 2- Delete a product                                               " << endl;
		cout << " 3- Update a product                                               " << endl;
		cout << " 4- Search on a product                                            " << endl;
		cout << " 5- Display All  products                                          " << endl;
		cout << " 6- Exit from program                                              " << endl;
		cout <<"********************************************************************" << endl;
		cout << "\t\t - choice the number of option (1-6) :\n "; cin.getline(O, 3);
		if (O[0] == '6')
			break;
		else if (!(O[0] == '1' || O[0] == '2' || O[0] == '3' || O[0] == '4' || O[0] == '5'))
		{
			cout << "\a| - Wrong option please choice the number of option (1-6) : "; cin.getline(O, 3);
		}
		else
		{
			switch (O[0])
			{
			case '1':
				Add();
				break;
			case '2':
                Delete();
				break;
			case '3':
                Update();
				break;
			case '4':
                Search();
				break;
			case '5':
                DisplayAll();
				break;
			}
		}
	}

	cout << endl << "----------------------------- Good Bay ------------------------------" << endl;
	system("pause");
	return 0;
}

