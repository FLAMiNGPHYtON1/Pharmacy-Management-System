#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <ctime>
#include <time.h>
#include <cstdlib>
#include <random>
#include <ctime>
#include <sstream>
#include <vector>
#include <iomanip>


using namespace std;

// This functions takes login details entered and verifies it with details present in Login_Details.txt to see if
// the entered information exists and is correct. If its correct the user is taken to their respective menu.
int login_verifier(string Username, string Password, string Role)
{
	fstream login_textfile_object;
	string u_id, u_ps, u_rl;
	int count = 0;
	login_textfile_object.open("Login_Details.txt", ios::in);

	if (login_textfile_object.is_open())
	{
		while (login_textfile_object >> u_id >> u_ps >> u_rl)
		{
			if (u_id == Username && u_ps == Password && u_rl == Role)
			{
				count = 1;
			}
		}
		login_textfile_object.close();
		if (count == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		cout << "-----------------------------------------------------------------------------\n";
		cout << "|            Error in opening user detail file! Aborting Program...         |\n";
		cout << "-----------------------------------------------------------------------------\n";
		exit;
	}
}
// This function check if user has inputted the letter x or X, upon which it stops whatever task the user is doing and returns them to the main menu
int exit_function(string input)
{
	if (input == "x" || input == "X")
	{
		return 1;
	}
}
// This function generates a random ID for each medicine record in the system, allowing multiple medicines of possibly the same name, price and manufacturer to exist without breaking the system.
string random_ID_generator()
{
	int ID = 0;
	string Full_ID = "";
	random_device r;
	default_random_engine generator(r());
	uniform_int_distribution<int> distribution(10000, 99999);
	ID = distribution(generator);
	Full_ID = "AL" + to_string(ID);
	return Full_ID;
}
// This function asks user to input manufacturing and expiry date in the correct format taking into account of differing days for each month and leap year possibilties.
string Date_input(string context)
{
	struct date
	{
		int day;
		int month;
		int year;
	};

	struct date Obj1;
	string Final_Date = "";
	cout << "\nPlease enter date of " << context << " for this medicine in this format DD/MM/YYYY:- ";
	try
	{
		cin >> Obj1.day;
		if (cin.fail())
		{
			throw 1;
		}
		else
		{
			if (cin.get() != '/')
			{
				cout << "\n---------------------------------------------------------------------------\n";
				cout << "|                  expected / character after day value                     |\n";
				cout << "-----------------------------------------------------------------------------\n";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return Final_Date;
			}
			try
			{
				cin >> Obj1.month;
				if (cin.fail())
				{
					throw 1;
				}
				else
				{
					if (cin.get() != '/')
					{
						cout << "\n-----------------------------------------------------------------------------\n";
						cout << "|                  expected / character after motnh value                   |\n";
						cout << "-----------------------------------------------------------------------------\n";
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						return Final_Date;
					}
					try
					{
						cin >> Obj1.year;
						if (cin.fail())
						{
							throw 1;
						}
						else
						{
							int check = 0;
							if (context == "Manufacturing")
							{
								if (Obj1.year >= 2022)
								{
									if ((Obj1.month == 1 || Obj1.month == 3 || Obj1.month == 5 || Obj1.month == 7 || Obj1.month == 8 || Obj1.month == 10 || Obj1.month == 12) && Obj1.day >> 00 && Obj1.day <= 31)
									{
										check = 1;
									}
									else if ((Obj1.month == 4 || Obj1.month == 6 || Obj1.month == 9 || Obj1.month == 11) && Obj1.day > 0 && Obj1.day <= 30)
									{
										check = 1;
									}
									else if (Obj1.month == 2)
									{
										if ((Obj1.year % 400 == 0 || (Obj1.year % 100 != 0 && Obj1.year % 4 == 0)) && Obj1.day > 0 && Obj1.day <= 29)
										{
											check = 1;
										}
										else if (Obj1.day > 0 && Obj1.day <= 28)
										{
											check = 1;
										}
										else
										{
											check = 0;
										}
									}
									else
									{
										check = 0;
									}
								}
								else
								{
									check = 0;
								}
								if (check == 1)
								{
									Final_Date = to_string(Obj1.day) + "/" + to_string(Obj1.month) + "/" + to_string(Obj1.year);
									return Final_Date;
								}
								else
								{
									cout << "\n-----------------------------------------------------------------------------\n";
									cout << "|               Incorrect Date entered! Please try again!                   |\n";
									cout << "-----------------------------------------------------------------------------\n";
									cin.clear();
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									return Final_Date;
								}
							}
							else
							{
								if (Obj1.year >= 2022)
								{
									if ((Obj1.month == 1 || Obj1.month == 3 || Obj1.month == 5 || Obj1.month == 7 || Obj1.month == 8 || Obj1.month == 10 || Obj1.month == 12) && Obj1.day >> 00 && Obj1.day <= 31)
									{
										check = 1;
									}
									else if ((Obj1.month == 4 || Obj1.month == 6 || Obj1.month == 9 || Obj1.month == 11) && Obj1.day > 0 && Obj1.day <= 30)
									{
										check = 1;
									}
									else if (Obj1.month == 2)
									{
										if ((Obj1.year % 400 == 0 || (Obj1.year % 100 != 0 && Obj1.year % 4 == 0)) && Obj1.day > 0 && Obj1.day <= 29)
										{
											check = 1;
										}
										else if (Obj1.day > 0 && Obj1.day <= 28)
										{
											check = 1;
										}
										else
										{
											check = 0;
										}
									}
									else
									{
										check = 0;
									}
								}
								else
								{
									check = 0;
								}
								if (check == 1)
								{
									Final_Date = to_string(Obj1.day) + "/" + to_string(Obj1.month) + "/" + to_string(Obj1.year);	
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									return Final_Date;
								}
								else
								{
									cout << "\n-----------------------------------------------------------------------------\n";
									cout << "|               Incorrect Date entered! Please try again!                   |\n";
									cout << "-----------------------------------------------------------------------------\n";
									cin.clear();
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									return Final_Date;
								}
							}
						}
					}
					catch (int err)
					{
						cout << "\n-----------------------------------------------------------------------------\n";
						cout << "|           Incorrect Year value entered! Please try again!                 |\n";
						cout << "-----------------------------------------------------------------------------\n";
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						return Final_Date;
					}
				}
			}
			catch (int err)
			{
				cout << "\n-----------------------------------------------------------------------------\n";
				cout << "|           Incorrect Month value entered! Please try again!                |\n";
				cout << "-----------------------------------------------------------------------------\n";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return Final_Date;
			}
		}
	}
	catch (int err)
	{
		cout << "\n-----------------------------------------------------------------------------\n";
		cout << "|             Incorrect Day value entered! Please try again!                |\n";
		cout << "-----------------------------------------------------------------------------\n";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return Final_Date;
	}
		
}
// This function compares the manufacturing and expiry date given by user to determine it is correct chornologically
int Date_comparision(string Manufacturing_Date, string Expiry_Date)
{
	struct date
	{
		int day;
		int month;
		int year;
	};

	vector <int> Dates1;
	vector <int> Dates2;

	struct date Obj1, Obj2;
	stringstream String_Obj1, String_Obj2;
	String_Obj1 << Manufacturing_Date;
	String_Obj2 << Expiry_Date;
	string str_token1;
	int token1;
	string str_token2;
	int token2;
	string temp_string1, temp_string2;
	int temp_int1, temp_int2;

	while (getline(String_Obj1, str_token1, '/'))
	{
		token1 = stoi(str_token1);
		Dates1.push_back(token1);
	
	}

	while (getline(String_Obj2, str_token2, '/'))
	{
		token2 = stoi(str_token2);
		Dates2.push_back(token2);
	}

	Obj1.day = Dates1.at(0);
	Obj1.month = Dates1.at(1);
	Obj1.year = Dates1.at(2);
	Obj2.day = Dates2.at(0);
	Obj2.month = Dates2.at(1);
	Obj2.year = Dates2.at(2);

	if (Obj2.year < Obj1.year)
	{
		return 0;
	}
	if (Obj2.year == Obj1.year)
	{
		if (Obj2.month < Obj1.month)
		{
			return 0;
		}
		else if (Obj2.month == Obj1.month)
		{
			if (Obj2.day <= Obj1.day)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 1;
	}


}
// This function calculates the months from manufacturing date to expiry date
int Expiry_Month_Calculation(string Manufacturing_Date, string Expiry_Date)
{

	{
		struct date
		{
			int day;
			int month;
			int year;
		};

		vector <int> Dates1;
		vector <int> Dates2;

		int month_difference;
		int year_difference;

		struct date Obj1, Obj2;
		stringstream String_Obj1, String_Obj2;
		String_Obj1 << Manufacturing_Date;
		String_Obj2 << Expiry_Date;
		string str_token1;
		int token1;
		string str_token2;
		int token2;
		string temp_string1, temp_string2;
		int temp_int1, temp_int2;

		while (getline(String_Obj1, str_token1, '/'))
		{
			token1 = stoi(str_token1);
			Dates1.push_back(token1);

		}

		while (getline(String_Obj2, str_token2, '/'))
		{
			token2 = stoi(str_token2);
			Dates2.push_back(token2);
		}

		Obj1.day = Dates1.at(0);
		Obj1.month = Dates1.at(1);
		Obj1.year = Dates1.at(2);
		Obj2.day = Dates2.at(0);
		Obj2.month = Dates2.at(1);
		Obj2.year = Dates2.at(2);

		if (Obj2.year == Obj1.year)
		{
			month_difference = Obj2.month - Obj1.month;
			return month_difference;
		}
		else
		{
			year_difference = Obj2.year - Obj1.year;
			month_difference = Obj2.month - Obj1.month;
			month_difference = month_difference + (year_difference * 12);
			return month_difference;
		}
	
	}
}


// This function is used by admin user to add a medicine record to system.
void add_medicine()
{
	
	fstream Medicine_textfile_object;
	string Medicine_Name, Manufacturer_Name, Medicine_ID, string_price;
	string Manufacturing_Date = "", Expiry_Date = "";
	string Medicine_information;
	int available_stock, price;
	// Date of Manufacture, Date of Expiry
	
	cout << "\n\n\n*****************************************************************************\n";
	cout << "*                          Ali's Medicine Pharmacy                          *\n";
	cout << "*****************************************************************************\n";
	cout << "*                  Please enter new medicine's details:-                    *\n";
	cout << "*****************************************************************************\n";
	cout << "*****************************************************************************\n";
	cout << "*                 Enter X at any time to return to admin menu               *\n";
	cout << "*                 Enter 0 at Price/Stock field to return to admin menu      *\n";
	cout << "*****************************************************************************\n";
	while (true)
	{
		int check = 0;
		cout << "\nEnter name of Manufacturer:- ";
		getline(cin, Manufacturer_Name);
		if (exit_function(Manufacturer_Name) == 1)
		{
			break;
		}
		if (regex_match(Manufacturer_Name, regex("^[a-zA-Z]*$")))
		{		
			cout << "\nEnter name of Medicine:- ";
			getline(cin, Medicine_Name);
			
			if (exit_function(Medicine_Name) == 1)
			{
				break;
			}
			if (regex_match(Medicine_Name, regex("^[a-zA-Z]*$")))
			{				
				Medicine_ID = random_ID_generator();

				cout << "\nEnter available stock of Medicine:- ";
				try
				{
					cin >> available_stock;
					if (cin.fail())
					{
						throw 1;
					}
					else if (available_stock < 0 || available_stock > 999)
					{
						throw 2;
					}
					else if (available_stock == 0)
					{
						throw 3;
					}
					else
					{
						cout << "\nEnter price per unit of Medicine:- ";
						try
						{
							cin >> price;

							if (cin.fail())
							{
								throw 1;
							}
							else if (price < 0 || price > 999)
							{
								throw 2;
							}
							else if (price == 0)
							{
								throw 3;
							}
							else
							{
								string_price = "RM" + to_string(price);

								Manufacturing_Date = Date_input("Manufacturing");				
								if (Manufacturing_Date == "")
								{
									cout << " ";
								}
								else
								{
									Expiry_Date = Date_input("Expiry");
									if (Expiry_Date == "")
									{
										cout << " ";
									}
									else
									{
										check = Date_comparision(Manufacturing_Date, Expiry_Date);
										if (check == 1)
										{
											Medicine_information = Medicine_ID + " " + Manufacturer_Name + " " + Medicine_Name + " " + string_price + " " + to_string(available_stock) + " " + Manufacturing_Date + " " + Expiry_Date + "\n";
											Medicine_textfile_object.open("Medicine_Details.txt", ios::app);
											if (Medicine_textfile_object.is_open())
											{
												Medicine_textfile_object << Medicine_information;
												system("CLS");
												cout << "-----------------------------------------------------------------------------\n";
												cout << "|                Medicine has been added successfully!                      |\n";
												cout << "-----------------------------------------------------------------------------\n\n\n";
												Medicine_textfile_object.close();

												break;
											}
											else
											{
												cout << "-----------------------------------------------------------------------------\n";
												cout << "|            Error in opening medicine detail file! Aborting Program...     |\n";
												cout << "-----------------------------------------------------------------------------\n";
												exit(0);
											}
										}
										else
										{
											cout << "-----------------------------------------------------------------------------\n";
											cout << "|                Invalid Dates entered! Please try again!                   |\n";
											cout << "-----------------------------------------------------------------------------\n";
										}
									}
								}										
							}
						}
						catch (int err)
						{
							if (err == 1 || 2)
							{
								cout << "\n-----------------------------------------------------------------------------\n";
								cout << "\n|       Invalid Price entered! Please enter between a range of 1 - 999      |\n";
								cout << "\n-----------------------------------------------------------------------------\n";
								cin.clear();
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							}
							else
							{
								break;
							}
						}
					}
				}
				catch (int err)
				{
					if (err == 1 || 2)
					{
						cout << "\n-----------------------------------------------------------------------------\n";
						cout << "\n|       Invalid Stock entered! Please enter between a range of 1 - 999      |\n";
						cout << "\n-----------------------------------------------------------------------------\n";
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					}
					else
					{
						break;
					}
					
				}
			}
			else
			{
				cout << "\n-----------------------------------------------------------------------------\n";
				cout << "\n|      Illegal Characters used! Please use only alphabetical characters!    |\n";
				cout << "\n-----------------------------------------------------------------------------\n";
			}
		}
		else
		{
			cout << "\n-----------------------------------------------------------------------------\n";
			cout << "\n|      Illegal Characters used! Please use only alphabetical characters!    |\n";
			cout << "\n-----------------------------------------------------------------------------\n";
		}
		
	}
}
// This function is used by admin user to completlely remove a single medical record from the system;
void delete_medicine()
{
	system("CLS");
	fstream Medicine_textfile_Object;
	fstream Temp_file;


	string Medicine_Name, Manufacturer_Name, Medicine_ID, string_price;
	string Manufacturing_Date = "", Expiry_Date = "";
	int available_stock, price;
	Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
	cout << "*********************************************************************************************************\n";
	cout << "*                                     Ali's Medicine Pharmacy                                           *\n";
	cout << "*********************************************************************************************************\n";
	cout << "*                                       Medicine Records                                                *\n";
	cout << "*********************************************************************************************************\n\n";
	cout << left << setw(16) << "Medicine ID"
		<< left << setw(22) << "Manufacturer Name"
		<< left << setw(18) << "Medicine Name"
		<< left << setw(10) << "Price"
		<< left << setw(13) << "Quantity"
		<< left << setw(15) << "DOM"
		<< left << setw(15) << "DOE"
		<< endl;
	if (Medicine_textfile_Object.is_open())
	{
		while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
		{
			cout << left << setw(16) << Medicine_ID

				<< left << setw(22) << Manufacturer_Name

				<< left << setw(18) << Medicine_Name

				<< left << setw(10) << string_price

				<< left << setw(13) << available_stock

				<< left << setw(15) << Manufacturing_Date

				<< left << setw(15) << Expiry_Date

				<< endl;
		}
	}
	Medicine_textfile_Object.close();

	while (true)
	{
		int check = 0;
		string Medicine_ID_Deletion;
		cout << endl;
		cout << "You can enter X to return to the main menu\n";
		cout << "\nEnter the ID of the medicine you would like to delete:- ";
		getline(cin, Medicine_ID_Deletion);
		if (exit_function(Medicine_ID_Deletion) == 1)
		{
			system("CLS");
			break;
		}
		else
		{
			Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
			Temp_file.open("Temp_File.txt", ios::out);
			if (Medicine_textfile_Object.is_open())
			{
				while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
				{
					if (Medicine_ID != Medicine_ID_Deletion)
					{
						Temp_file << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
					}
					else
					{
						check = 1;
					}
				}

			}
			if (check == 1)
			{
				Medicine_textfile_Object.close();
				Temp_file.close();
				remove("Medicine_Details.txt");
				rename("Temp_File.txt", "Medicine_Details.txt");
				system("CLS");
				cout << "\n----------------------------------------------------------------------------\n";
				cout << "|                 Medicine record removed succesfully!                     |\n";
				cout << "----------------------------------------------------------------------------\n\n";
				break;
			}
			else
			{
				Medicine_textfile_Object.close();
				Temp_file.close();
				cout << "\n----------------------------------------------------------------------------\n";
				cout << "|                         ID does not exist!                                |\n";
				cout << "-----------------------------------------------------------------------------\n\n";
			}
		}	
		
	}
}
// This function is used by admin user to modify each and every field of a medicine record besides its UNIQUE ID
void modify_medicine()
{
	system("CLS");
	fstream Medicine_textfile_Object;
	fstream Temp_Object1;
	string Medicine_Name, Manufacturer_Name, Medicine_ID, string_price;
	string Manufacturing_Date = "", Expiry_Date = "";
	int available_stock, price;
	int while_state1 = 0;



	Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
	cout << "*********************************************************************************************************\n";
	cout << "*                                     Ali's Medicine Pharmacy                                           *\n";
	cout << "*********************************************************************************************************\n";
	cout << "*                                       Medicine Records                                                *\n";
	cout << "*********************************************************************************************************\n\n";
	cout << left << setw(16) << "Medicine ID"
		<< left << setw(22) << "Manufacturer Name"
		<< left << setw(18) << "Medicine Name"
		<< left << setw(10) << "Price"
		<< left << setw(13) << "Quantity"
		<< left << setw(15) << "DOM"
		<< left << setw(15) << "DOE"
		<< endl;



	if (Medicine_textfile_Object.is_open())
	{
		while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
		{
			cout << left << setw(16) << Medicine_ID

				<< left << setw(22) << Manufacturer_Name

				<< left << setw(18) << Medicine_Name

				<< left << setw(10) << string_price

				<< left << setw(13) << available_stock

				<< left << setw(15) << Manufacturing_Date

				<< left << setw(15) << Expiry_Date

				<< endl;
		}
	}
	Medicine_textfile_Object.close();
	while (true)
	{
		if (while_state1 == 1)
		{
			break;
		}
		else
		{
			while_state1 = 0;
		}


		int check = 0;
		string Medicine_ID_Modify;


		cout << endl;
		cout << "*********************************************************************************************************\n";
		cout << "*                           You can enter X at any time to return to the main menu                      *\n";
		cout << "*                           Enter 0 at Price/Stock field to return to admin menu                        *\n";
		cout << "*                           Enter the ID of the medicine you would like to modify:-                     *\n";
		cout << "*********************************************************************************************************\n";


		getline(cin, Medicine_ID_Modify);
		if (exit_function(Medicine_ID_Modify) == 1)
		{
			system("CLS");
			break;
		}
		else
		{
			Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
			if (Medicine_textfile_Object.is_open())
			{
				while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
				{
					if (Medicine_ID == Medicine_ID_Modify)
					{				
						check += 1;
					}
					else
					{
						// Do nothing
					}
				}
			}

			else
			{
				cout << "-----------------------------------------------------------------------------\n";
				cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
				cout << "-----------------------------------------------------------------------------\n";
				exit(0);
			}

			Medicine_textfile_Object.close();
			if (check > 0)
			{
				char choice;
				string string_choice;
				int selection = 0;

				string Medicine_Name_Modify, Manufacturer_Name_Modify, string_price_Modify;
				string Manufacturing_Date_Modify = "", Expiry_Date_Modify = "";
				int available_stock_Modify, price_Modify;						
				while (true)
				{
					cout << "\n\n";
					cout << "*********************************************************************************************************\n";
					cout << "*                                     Ali's Medicine Pharmacy                                           *\n";
					cout << "*********************************************************************************************************\n";
					cout << "*                     What would you like to modify for Medicine ID " << Medicine_ID_Modify << "?       *\n";
					cout << "*********************************************************************************************************\n";
					cout << "*  |A| - Medicine Name                                                                                  *\n";
					cout << "*                                                                                                       *\n";
					cout << "*  |B| - Manufacturer Name                                                                              *\n";
					cout << "*                                                                                                       *\n";
					cout << "*  |C| - Price of Medicine                                                                              *\n";
					cout << "*                                                                                                       *\n";
					cout << "*  |D| - Available Stock of Medicine                                                                    *\n";
					cout << "*                                                                                                       *\n";
					cout << "*  |E| - Manufacturing Date of Medicine                                                                 *\n";
					cout << "*                                                                                                       *\n";
					cout << "*  |F| - Expiry Date of Medicine                                                                        *\n";
					cout << "*                                                                                                       *\n";
					cout << "*  |K| - Exit to Admin menu                                                                             *\n";
					cout << "*********************************************************************************************************\n";
					cout << endl;
					cout << "Enter your selection: ";
					getline(cin, string_choice);
					if (string_choice.length() == 1)
					{
						choice = string_choice.at(0);
						switch (choice)
						{
						case 'A':
						case 'a':
							selection = 1;
							break;
						case 'B':
						case 'b':
							selection = 2;
							break;
						case 'C':
						case 'c':
							selection = 3;
							break;
						case 'D':
						case 'd':
							selection = 4;
							break;
						case 'E':
						case 'e':
							selection = 5;
							break;
						case 'F':
						case 'f':
							selection = 6;
							break;
						case 'K':
						case 'k':
							system("CLS");
							while_state1 = 1;
							break;
						default:
							
							cout << "\n\n-----------------------------------------------------------------------------\n";
							cout << "|              Invalid input! Please enter a correct input                  |\n";
							cout << "-----------------------------------------------------------------------------\n\n";
						}
						if (while_state1 == 1)
						{
							break;
						}
					}
					else
					{
			
						cout << "\n\n-----------------------------------------------------------------------------\n";
						cout << "|                 Please only enter a single character!                     |\n";
						cout << "-----------------------------------------------------------------------------\n\n";

					}
					if (selection == 1)
					{
						cout << "\nEnter name of Medicine:- ";
						getline(cin, Medicine_Name_Modify);

						if (exit_function(Medicine_Name_Modify) == 1)
						{
							while_state1 = 1;
							break;
						}
						else
						{
							if (regex_match(Medicine_Name_Modify, regex("^[a-zA-Z]*$")))
							{
								Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
								Temp_Object1.open("Temp_File.txt", ios::out);							
								if (Medicine_textfile_Object.is_open())
								{
									while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
									{
										if (Medicine_ID != Medicine_ID_Modify)
										{
											Temp_Object1 << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";											
										} 
										else
										{
											Temp_Object1 << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name_Modify << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
										}
									}

								}
								else
								{
									cout << "-----------------------------------------------------------------------------\n";
									cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
									cout << "-----------------------------------------------------------------------------\n";
									exit(0);
								}
								Medicine_textfile_Object.close();
								Temp_Object1.close();
								remove("Medicine_Details.txt");
								rename("Temp_File.txt", "Medicine_Details.txt");
								system("CLS");
								cout << "\n----------------------------------------------------------------------------\n";
								cout << "|                 Medicine record modified successfully!                     |\n";
								cout << "----------------------------------------------------------------------------\n\n";
								while_state1 = 1;
								break;
								
							}
							else
							{
								cout << "\n-----------------------------------------------------------------------------\n";
								cout << "\n|      Illegal Characters used! Please use only alphabetical characters!    |\n";
								cout << "\n-----------------------------------------------------------------------------\n";
							}
						}
					}
					else if (selection == 2)
					{
						cout << "\nEnter name of Manufacturer:- ";
						getline(cin, Manufacturer_Name_Modify);

						if (exit_function(Manufacturer_Name_Modify) == 1)
						{
							while_state1 = 1;
							break;
						}
						else
						{
							if (regex_match(Manufacturer_Name_Modify, regex("^[a-zA-Z]*$")))
							{
								Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
								Temp_Object1.open("Temp_File.txt", ios::out);
								if (Medicine_textfile_Object.is_open())
								{
									while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
									{
										if (Medicine_ID != Medicine_ID_Modify)
										{
											Temp_Object1 << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
										}
										else
										{
											Temp_Object1 << Medicine_ID << " " << Manufacturer_Name_Modify << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
										}
									}

								}
								else
								{
									cout << "-----------------------------------------------------------------------------\n";
									cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
									cout << "-----------------------------------------------------------------------------\n";
									exit(0);
								}
								Medicine_textfile_Object.close();
								Temp_Object1.close();
								remove("Medicine_Details.txt");
								rename("Temp_File.txt", "Medicine_Details.txt");
								system("CLS");
								cout << "\n----------------------------------------------------------------------------\n";
								cout << "|                 Medicine record modified successfully!                   |\n";
								cout << "----------------------------------------------------------------------------\n\n";
								while_state1 = 1;
								break;

							}
							else
							{

								cout << "\n-----------------------------------------------------------------------------\n";
								cout << "\n|      Illegal Characters used! Please use only alphabetical characters!    |\n";
								cout << "\n-----------------------------------------------------------------------------\n";
							}
						}
					}
					else if (selection == 3)
					{
						cout << "\nEnter price of Medicine:- ";
						try
						{
							cin >> price_Modify;
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							if (cin.fail())
							{
								throw 1;
							}
							else if (price_Modify < 0 || price_Modify > 999)
							{
								throw 2;
							}
							else if (price_Modify == 0)
							{
								throw 3;
							}
							else
							{
								string_price_Modify = "RM" + to_string(price_Modify);
								Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
								Temp_Object1.open("Temp_File.txt", ios::out);
								if (Medicine_textfile_Object.is_open())
								{
									while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
									{
										if (Medicine_ID != Medicine_ID_Modify)
										{
											Temp_Object1 << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
										}
										else
										{
											Temp_Object1 << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price_Modify << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
										}
									}

								}
								else
								{
									cout << "-----------------------------------------------------------------------------\n";
									cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
									cout << "-----------------------------------------------------------------------------\n";
									exit(0);
								}
								Medicine_textfile_Object.close();
								Temp_Object1.close();
								remove("Medicine_Details.txt");
								rename("Temp_File.txt", "Medicine_Details.txt");
								system("CLS");
								cout << "\n----------------------------------------------------------------------------\n";
								cout << "|                 Medicine record modified successfully!                   |\n";
								cout << "----------------------------------------------------------------------------\n\n";
								while_state1 = 1;
								break;
							}

						}
						catch (int err)
						{
							if (err == 1 || 2)
							{
								cout << "\n-----------------------------------------------------------------------------\n";
								cout << "\n|       Invalid Stock entered! Please enter between a range of 1 - 999      |\n";
								cout << "\n-----------------------------------------------------------------------------\n";
								cin.clear();
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

							}
							else
							{
								system("CLS");
								while_state1 = 1;
								break;
							}
						}
					}
					else if (selection == 4)
					{
						cout << "\nEnter available stock of Medicine:- ";
						try
						{
							cin >> available_stock_Modify;
							if (cin.fail())
							{
								throw 1;
							}
							else if (available_stock_Modify < 0 || available_stock_Modify > 999)
							{
								throw 2;
							}
							else if (available_stock_Modify == 0)
							{
								throw 3;
							}
							else
							{
								Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
								Temp_Object1.open("Temp_File.txt", ios::out);
								if (Medicine_textfile_Object.is_open())
								{
									while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock_Modify >> Manufacturing_Date >> Expiry_Date)
									{
										if (Medicine_ID != Medicine_ID_Modify)
										{
											Temp_Object1 << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
										}
										else
										{
											Temp_Object1 << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock_Modify << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
										}
									}

								}
								else
								{
									system("CLS");
									cout << "-----------------------------------------------------------------------------\n";
									cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
									cout << "-----------------------------------------------------------------------------\n";
									exit(0);
								}
								Medicine_textfile_Object.close();
								Temp_Object1.close();
								remove("Medicine_Details.txt");
								rename("Temp_File.txt", "Medicine_Details.txt");
								system("CLS");
								cout << "\n----------------------------------------------------------------------------\n";
								cout << "|                 Medicine record modified successfully!                     |\n";
								cout << "----------------------------------------------------------------------------\n\n";
								while_state1 = 1;
								break;
							}

						}
						catch (int err)
						{
							if (err == 1 || 2)
							{
								cout << "\n-----------------------------------------------------------------------------\n";
								cout << "\n|       Invalid Stock entered! Please enter between a range of 1 - 999      |\n";
								cout << "\n-----------------------------------------------------------------------------\n";
								cin.clear();
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

							}
							else
							{
								system("CLS");
								while_state1 = 1;
								break;
							}
						}
					}
					else if (selection == 5)
					{
						int check;
						Manufacturing_Date_Modify = Date_input("Manufacturing");	
						if (Manufacturing_Date_Modify == "")
						{
							cout << " ";
						}
						else
						{
							Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
							if (Medicine_textfile_Object.is_open())
							{
								while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
								{
									if (Medicine_ID == Medicine_ID_Modify)
									{
										break;
									}
									else
									{
										// Do nothing
									}
								
								}
								check = Date_comparision(Manufacturing_Date_Modify, Expiry_Date);
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								if (check == 1)
								{
									Medicine_textfile_Object.close();
									Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
									Temp_Object1.open("Temp_File.txt", ios::out);
									if (Medicine_textfile_Object.is_open())
									{
										while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
										{

											if (Medicine_ID != Medicine_ID_Modify)
											{
												Temp_Object1 << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
											}
											else
											{
												Temp_Object1 << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date_Modify << " " << Expiry_Date << "\n";
											}
										}

									}
									else
									{
										cout << "-----------------------------------------------------------------------------\n";
										cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
										cout << "-----------------------------------------------------------------------------\n";
										exit(0);
									}
									Medicine_textfile_Object.close();
									Temp_Object1.close();
									remove("Medicine_Details.txt");
									rename("Temp_File.txt", "Medicine_Details.txt");
									system("CLS");
									cout << "\n----------------------------------------------------------------------------\n";
									cout << "|                 Medicine record modified successfully!                   |\n";
									cout << "----------------------------------------------------------------------------\n\n";
									while_state1 = 1;
									break;
								}
								else
								{
									Medicine_textfile_Object.close();
									cout << "-----------------------------------------------------------------------------\n";
									cout << "|                Invalid Dates entered! Please try again!                   |\n";
									cout << "-----------------------------------------------------------------------------\n";
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								}
							}
							else
							{
								cout << "-----------------------------------------------------------------------------\n";
								cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
								cout << "-----------------------------------------------------------------------------\n";
								exit(0);
							}
						}
						
					}
					else 
					{
						int check;
						Expiry_Date_Modify = Date_input("Expiry");
						if (Expiry_Date_Modify == "")
						{
							cout << " ";
						}
						else
						{
							Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
							if (Medicine_textfile_Object.is_open())
							{
								while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
								{
									if (Medicine_ID == Medicine_ID_Modify)
									{
										break;
									}
									else
									{
										// Do nothing
									}

								}
								check = Date_comparision(Manufacturing_Date, Expiry_Date_Modify);		
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								if (check == 1)
								{
									Medicine_textfile_Object.close();
									Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
									Temp_Object1.open("Temp_File.txt", ios::out);
									if (Medicine_textfile_Object.is_open())
									{
										while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
										{

											if (Medicine_ID != Medicine_ID_Modify)
											{
												Temp_Object1 << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
											}
											else
											{
												Temp_Object1 << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date_Modify << "\n";
											}
										}

									}
									else
									{
										cout << "-----------------------------------------------------------------------------\n";
										cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
										cout << "-----------------------------------------------------------------------------\n";
										exit(0);
									}
									Medicine_textfile_Object.close();
									Temp_Object1.close();
									remove("Medicine_Details.txt");
									rename("Temp_File.txt", "Medicine_Details.txt");
									system("CLS");
									cout << "\n----------------------------------------------------------------------------\n";
									cout << "|                 Medicine record modified successfully!                   |\n";
									cout << "----------------------------------------------------------------------------\n\n";
									while_state1 = 1;
									break;
								}
								else
								{
									Medicine_textfile_Object.close();
									cout << "-----------------------------------------------------------------------------\n";
									cout << "|                Invalid Dates entered! Please try again!                   |\n";
									cout << "-----------------------------------------------------------------------------\n";
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								}
							}
							else
							{
								cout << "-----------------------------------------------------------------------------\n";
								cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
								cout << "-----------------------------------------------------------------------------\n";
								exit(0);
							}
						}
					}
				}				
			}
			else
			{
				cout << "\n----------------------------------------------------------------------------\n";
				cout << "|                         ID does not exist!                                |\n";
				cout << "-----------------------------------------------------------------------------\n\n";
			}
		}
	}
}
// This function is used by admin user to view ALL medicines that are currently present in the system
void view_medicine()
{
	system("CLS");
	fstream Medicine_textfile_Object;
	string Medicine_Name, Manufacturer_Name, Medicine_ID, string_price;
	string Manufacturing_Date = "", Expiry_Date = "";
	int available_stock, price, months;
	Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
	cout << "**********************************************************************************************************************************\n";
	cout << "*                                                 Ali's Medicine Pharmacy                                                        *\n";
	cout << "**********************************************************************************************************************************\n";
	cout << "*                                                   Medicine Records                                                             *\n";
	cout << "**********************************************************************************************************************************\n\n";
	cout<< left << setw(16) << "Medicine ID"
		<< left << setw(22) << "Manufacturer Name"
		<< left << setw(18) << "Medicine Name"
		<< left << setw(10) << "Price"
		<< left << setw(13) << "Quantity"
		<< left << setw(15) << "DOM"
		<< left << setw(15) << "DOE"
		<< left << setw(7)  << "Months before expiry"
		<< endl;
	if (Medicine_textfile_Object.is_open())
	{
		while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
		{
			months = Expiry_Month_Calculation(Manufacturing_Date, Expiry_Date);

			cout << left << setw(16) << Medicine_ID

				<< left << setw(22) << Manufacturer_Name

				<< left << setw(18) << Medicine_Name

				<< left << setw(10) << string_price
	
				<< left << setw(13) << available_stock
		
				<< left << setw(15) << Manufacturing_Date
		
				<< left << setw(15) << Expiry_Date

				<< left << setw(7) << months
			
				<< endl;
		}
	}
	Medicine_textfile_Object.close();
	while (true)
	{
		string check;
		cout << "**********************************************************************************************************************************\n";
		cout << "*                                               Enter X to go back to main menu                                                  *\n";
		cout << "**********************************************************************************************************************************\n";
		cin >> check;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (exit_function(check) == 1)
		{
			system("CLS");
			break;
		}
		else
		{
			cout << "-----------------------------------------------------------------------------\n";
			cout << "|                         Invalid Input! Try Again!                         |\n";
			cout << "-----------------------------------------------------------------------------\n";
		}
	}
}
// This function is used by admin user to search for a specific medicine by name, resulting in medicine which might have the same name, but unique IDs
void search_medicine()
{
	system("CLS");

	fstream Medicine_textfile_Object;
	fstream Temp_Object;
	string Medicine_Name, Manufacturer_Name, Medicine_ID, string_price;
	string Manufacturing_Date = "", Expiry_Date = "";

	int available_stock, price, while_state1 = 0;

	cout << "*********************************************************************************************************\n";
	cout << "*                                     Ali's Medicine Pharmacy                                           *\n";
	cout << "*********************************************************************************************************\n";
	cout << "*                                       Medicine Records                                                *\n";
	cout << "*********************************************************************************************************\n\n";
	while (true)
	{
		if (while_state1 == 1)
		{
			break;
		}
		else
		{
			while_state1 = 0;
		}
		int check = 0;
		string Medicine_Name_Find;
		cout << endl;
		cout << "You can enter X to return to the main menu\n";
		cout << "\nEnter the Name of the medicine you would like to find:- ";
		getline(cin, Medicine_Name_Find);
		if (exit_function(Medicine_Name_Find) == 1)
		{
			system("CLS");
			break;
		}
		else
		{
			Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
			Temp_Object.open("Temp_File.txt", ios::out);
			if (Medicine_textfile_Object.is_open())
			{
				while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
				{
					if (Medicine_Name == Medicine_Name_Find)
					{
						Temp_Object << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
						check += 1;
					}
					else
					{
						// Do nothing
					}
				}
			}
			else
			{
				cout << "-----------------------------------------------------------------------------\n";
				cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
				cout << "-----------------------------------------------------------------------------\n";
				exit(0);
			}
			Medicine_textfile_Object.close();
			Temp_Object.close();
			if (check > 0)
			{
				
				cout << "\n\n";
				Temp_Object.open("Temp_File.txt", ios::in);
				cout << left << setw(16) << "Medicine ID"
					<< left << setw(22) << "Manufacturer Name"
					<< left << setw(18) << "Medicine Name"
					<< left << setw(10) << "Price"
					<< left << setw(13) << "Quantity"
					<< left << setw(15) << "DOM"
					<< left << setw(15) << "DOE"
					<< endl;
				if (Temp_Object.is_open())
				{
					while (Temp_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
					{
						cout << left << setw(16) << Medicine_ID

							<< left << setw(22) << Manufacturer_Name

							<< left << setw(18) << Medicine_Name

							<< left << setw(10) << string_price

							<< left << setw(13) << available_stock

							<< left << setw(15) << Manufacturing_Date

							<< left << setw(15) << Expiry_Date

							<< endl;
					}
					cout << "\nThese are the medicine records found with the name " << Medicine_Name_Find << endl;
					Temp_Object.close();
					remove("Temp_File.txt");
					while (true)
					{
						string check;
						cout << "\n*********************************************************************************************************\n";
						cout << "*                                 Enter X to go back to main menu                                       *\n";
						cout << "*                                 Enter Y to search for another medicine                                *\n";
						cout << "*********************************************************************************************************\n";
						cin >> check;
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						if (exit_function(check) == 1)
						{
							while_state1 = 1;
							system("CLS");
							break;
							
						}
						else if (check == "Y" || check == "y")
						{
							system("CLS");
							break;
						}
						else
						{
							cout << "-----------------------------------------------------------------------------\n";
							cout << "|                         Invalid Input! Try Again!                         |\n";
							cout << "-----------------------------------------------------------------------------\n";
						}
					}

				}
				else
				{
					cout << "-----------------------------------------------------------------------------\n";
					cout << "|            Error in opening medicine detail file! Aborting Program...     |\n";
					cout << "-----------------------------------------------------------------------------\n";
					remove ("Temp_File.txt");
					exit(0);
				}
			}
			else
			{
				
				cout << "\n----------------------------------------------------------------------------\n";
				cout << "|                         ID does not exist!                                |\n";
				cout << "-----------------------------------------------------------------------------\n\n";
			}
		}
	}

}
// This function is used by admin user to add a new user, either an admin or a customer to the system so they can login.
void add_user()
{

	system("CLS");
	fstream login_textfile_object;
	string u_id, u_ps, u_rl;
	string u_id2, u_ps2, u_rl2;
	cout << "*****************************************************************************\n";
	cout << "*                          Ali's Medicine Pharmacy                          *\n";
	cout << "*****************************************************************************\n";
	cout << "*                  Please enter new user's deatils below:-                  *\n";
	cout << "*****************************************************************************\n";
	while (true)
	{
		int count = 0;
		cout << "\nEnter username in this format [FirstName_LastName] :- ";
		getline(cin, u_id);
		if (regex_match(u_id, regex("^[a-zA-Z0-9]*_{1}[a-zA-Z0-9]*$")))
		{
			cout << "\nEnter password:- ";
			getline(cin, u_ps);

			if (regex_match(u_ps, regex("^[\\S]*$")))
			{
				cout << "\nEnter role of user (A or C):- ";
				cin >> u_rl;
				if (u_rl == "A" || u_rl == "C")
				{
					login_textfile_object.open("Login_Details.txt", ios::in);
					if (login_textfile_object.is_open())
					{
						while (login_textfile_object >> u_id2 >> u_ps2 >> u_rl2)
						{
							
							if (u_id == u_id2)
							{

								if (u_rl == u_rl2)
								{
									count = 1;
									break;
								}
								else
								{
									//Do Nothing
								}
							}
							else
							{
								//Do Nothing
							}
						    
						}
						login_textfile_object.close();
						if (count == 1)
						{
							cout << "-----------------------------------------------------------------------------\n";
							cout << "|             This username with selected role already exists!              |\n";
							cout << "-----------------------------------------------------------------------------\n";
						}
						else
						{
							login_textfile_object.open("Login_Details.txt", ios::app);
							if (login_textfile_object.is_open())
							{
								login_textfile_object <<  u_id << " " << u_ps << " " << u_rl << "\n";
								system("CLS");
								cout << "-----------------------------------------------------------------------------\n";
								cout << "|                     Registration successful!                              |\n";
								cout << "-----------------------------------------------------------------------------\n\n\n";
								login_textfile_object.close();
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								break;
							}
							else
							{
								cout << "-----------------------------------------------------------------------------\n";
								cout << "|            Error in opening user detail file! Aborting Program...         |\n";
								cout << "-----------------------------------------------------------------------------\n";
								exit(0);
							}

						}
					}
					else
					{
						cout << "-----------------------------------------------------------------------------\n";
						cout << "|            Error in opening user detail file! Aborting Program...         |\n";
						cout << "-----------------------------------------------------------------------------\n";
						exit;
					}

				}
				else
				{
					cout << "-----------------------------------------------------------------------------\n";
					cout << "|                      Invalid Role! Try Again!                             |\n";
					cout << "-----------------------------------------------------------------------------\n";
				}
			}
			else
			{
				cout << "-----------------------------------------------------------------------------\n";
				cout << "|                   Invalid Password! Try Again!                            |\n";
				cout << "-----------------------------------------------------------------------------\n";
			}

		}
		else
		{
			cout << "-----------------------------------------------------------------------------\n";
			cout << "|                       Invalid Username! Try Again!                        |\n";
			cout << "-----------------------------------------------------------------------------\n";
		}

	}
	


}
//This function is used by admin user to remove a user, either an admin or a customer from the system.
void remove_user(string username)
{
	system("CLS");
	fstream login_textfile_object;
	fstream Temp_file;
	string u_id, u_ps, u_rl;
	string u_id_deletion, u_ps2, u_rl2;
	int compare2 = 0;
	int compare = 0;
	cout << "*****************************************************************************\n";
	cout << "*                          Ali's Medicine Pharmacy                          *\n";
	cout << "*****************************************************************************\n";
	cout << "*                 You can enter X to return to the main menu                *\n";
	cout << "*                  Please enter username of user to delete:-                *\n";
	cout << "*****************************************************************************\n";
	while (true)
	{
		int check = 0;
		string u_id_deletion;
		cout << endl;
		cout << "Enter here:- ";
		getline(cin, u_id_deletion);
		if (u_id_deletion == username)
		{
			cout << "\n----------------------------------------------------------------------------\n";
			cout << "|                     You cannot remove your self!                           |\n";
			cout << "----------------------------------------------------------------------------\n\n";
			break;
		}
		if (exit_function(u_id_deletion) == 1)
		{
			system("CLS");
			break;
		}
		else
		{
			login_textfile_object.open("Login_Details.txt", ios::in);
			Temp_file.open("Temp_File.txt", ios::out);
			if (login_textfile_object.is_open())
			{
				while (login_textfile_object >> u_id >> u_ps >> u_rl)
				{
					if (u_id_deletion != u_id)
					{
						Temp_file << u_id << " " << u_ps << " " << u_rl << "\n";
					}
					else
					{
						check = 1;
					}
				}
			}
			if (check == 1)
			{
				login_textfile_object.close();
				Temp_file.close();
				remove("Login_Details.txt");
				rename("Temp_File.txt", "Login_Details.txt");
				system("CLS");
				cout << "\n----------------------------------------------------------------------------\n";
				cout << "|                        User removed succesfully!                           |\n";
				cout << "----------------------------------------------------------------------------\n\n";
				break;
			}
			else
			{
				login_textfile_object.close();
				Temp_file.close();
				cout << "\n----------------------------------------------------------------------------\n";
				cout << "|                         User does not exist!                               |\n";
				cout << "-----------------------------------------------------------------------------\n\n";
				break;
			}
		}

	}
}
//This function is used by admin user to view all purchase history in system.
void view_all_purchase_history()
{
	system("CLS");
	fstream Purchase_textfile_Object;
	string Medicine_Name, Manufacturer_Name, Medicine_ID, string_price;
	string Manufacturing_Date = "", Expiry_Date = "";
	string Username;
	int stock_purchase, price;
	Purchase_textfile_Object.open("Purchase_History.txt", ios::in);
	cout << "**********************************************************************************************************************************\n";
	cout << "*                                                 Ali's Medicine Pharmacy                                                        *\n";
	cout << "**********************************************************************************************************************************\n";
	cout << "*                                                   Medicine Records                                                             *\n";
	cout << "**********************************************************************************************************************************\n\n";
	cout << left << setw(13) << "Username"
		<< left << setw(16) << "Medicine ID"
		<< left << setw(22) << "Manufacturer Name"
		<< left << setw(18) << "Medicine Name"
		<< left << setw(10) << "Price"
		<< left << setw(23) << "Quantity Purchased"
		<< left << setw(15) << "DOM"
		<< left << setw(15) << "DOE"
		<< endl;
	if (Purchase_textfile_Object.is_open())
	{
		while (Purchase_textfile_Object >> Username >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> stock_purchase >> Manufacturing_Date >> Expiry_Date)
		{
			cout << left << setw(13) << Username

				<< left << setw(16) << Medicine_ID

				<< left << setw(22) << Manufacturer_Name

				<< left << setw(18) << Medicine_Name

				<< left << setw(10) << string_price

				<< left << setw(23) << stock_purchase

				<< left << setw(15) << Manufacturing_Date

				<< left << setw(15) << Expiry_Date

				<< endl << endl;
	
		}
	}
	Purchase_textfile_Object.close();
	while (true)
	{
		string check;
		cout << "**********************************************************************************************************************************\n";
		cout << "*                                               Enter X to go back to main menu                                                  *\n";
		cout << "**********************************************************************************************************************************\n";
		cin >> check;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (exit_function(check) == 1)
		{
			system("CLS");
			break;
		}
		else
		{
			cout << "-----------------------------------------------------------------------------\n";
			cout << "|                         Invalid Input! Try Again!                         |\n";
			cout << "-----------------------------------------------------------------------------\n";
		}
	}
}
// This function displays the menu an admin user sees when they succesfully login into the system
void admin_menu(string Username)
{
	system("CLS");
	while (true)
	{
		int while_state1 = 0;
		system("Color 0F");
		char choice;
		string string_choice;
		cout << "*****************************************************************************\n";
		cout << "*                          Ali's Medicine Pharmacy                          *\n";
		cout << "*****************************************************************************\n";
		cout << "*                                  Menu                                     *\n";
		cout << "*****************************************************************************\n";
		cout << "Welcome " << Username << "!                                                \n\n";
		cout << "*  |A| - Add a Medicine.                                                    *\n";
		cout << "*                                                                           *\n";
		cout << "*  |B| - Display All Medicine Records.                                      *\n";
		cout << "*                                                                           *\n";
		cout << "*  |C| - Search a Medicine by Name                                          *\n";
		cout << "*                                                                           *\n";
		cout << "*  |D| - Update a Medicine's details                                        *\n";
		cout << "*                                                                           *\n";
		cout << "*  |E| - Delete a Medicine's details from the system                        *\n";
		cout << "*                                                                           *\n";
		cout << "*  |F| - Add User.                                                          *\n";
		cout << "*                                                                           *\n";
		cout << "*  |G| - Remove User.                                                       *\n";
		cout << "*                                                                           *\n";
		cout << "*  |H| - View All Purchase History.                                         *\n";
		cout << "*                                                                           *\n";
		cout << "*  |K| - Exit.                                                              *\n";
		cout << "*****************************************************************************\n";
		cout << endl;
		cout << "Enter your selection: ";
		getline(cin, string_choice);
		if (string_choice.length() == 1)
		{
			choice = string_choice.at(0);
			switch (choice)
			{
			case 'A':
			case 'a':
				add_medicine();
				break;
			case 'B':
			case 'b':
				view_medicine();
				break;
			case 'C':
			case 'c':
				search_medicine();
				break;
			case 'D':
			case 'd':
				modify_medicine();
				break;
			case 'E':
			case 'e':
				delete_medicine();
				break;
			case 'F':
			case 'f':
				add_user();
				break;
			case 'G':
			case 'g':
				remove_user(Username);
				break;
			case 'H':
			case 'h':
				view_all_purchase_history();
				break;
			case 'K':
			case 'k':
				while_state1 = 1;
				break;
			default:
				system("CLS");
				cout << "\n\n-----------------------------------------------------------------------------\n";
				cout << "|              Invalid input! Please enter a correct input                  |\n";
				cout << "-----------------------------------------------------------------------------\n\n";
			}
			if (while_state1 == 1)
			{
				break;
			}
		}
		else
		{		
			system("CLS");
			cout << "\n\n-----------------------------------------------------------------------------\n";
			cout << "|                 Please only enter a single character!                     |\n";
			cout << "-----------------------------------------------------------------------------\n\n";		
		}			
	}		
}


// This functions allows customer to first search for a medicine by its name, then once they are found, search for its respective details
void medicine_availability()
{
	fstream Medicine_textfile_Object;
	fstream Temp_Object;
	string Medicine_Name, Manufacturer_Name, Medicine_ID, string_price;
	string Manufacturing_Date = "", Expiry_Date = "";

	int available_stock, price, while_state1 = 0, while_state2 = 0;
	system("CLS");
	cout << "*****************************************************************************\n";
	cout << "*                          Ali's Medicine Pharmacy                          *\n";
	cout << "*****************************************************************************\n";
	while (true)
	{
		if (while_state1 == 1)
		{
			break;
		}
		else
		{
			while_state1 = 0;
		}
		int check = 0;
		string Medicine_Name_Find;
		cout << endl;
		cout << "You can enter X to return to the main menu";
		cout << "\nEnter the Name of the medicine you would like to see the availability of:- ";
		getline(cin, Medicine_Name_Find);
		if (exit_function(Medicine_Name_Find) == 1)
		{
			system("CLS");
			break;
		}
		else
		{
			Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
			Temp_Object.open("Temp_File.txt", ios::out);
			if (Medicine_textfile_Object.is_open())
			{
				while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
				{
					if (Medicine_Name == Medicine_Name_Find)
					{
						Temp_Object << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
						check += 1;
					}
					else
					{
						// Do nothing
					}
				}
			}
			else
			{
				cout << "-----------------------------------------------------------------------------\n";
				cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
				cout << "-----------------------------------------------------------------------------\n";
				exit(0);
			}
			Medicine_textfile_Object.close();
			Temp_Object.close();
			if (check > 0)
			{

				cout << "\n\n";
				Temp_Object.open("Temp_File.txt", ios::in);
				cout
					<< left << setw(16) << "Medicine ID"
					<< left << setw(18) << "Medicine Name"
					<< left << setw(10) << "Availability"
					<< endl;

				if (Temp_Object.is_open())
				{
					while (Temp_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
					{
						string availability;
						if (available_stock > 0)
						{
							availability = "Available";
						}
						else
						{
							availability = "Unavailable";
						}
						cout << "\n";
							
						cout << left << setw(16) << Medicine_ID

							 << left << setw(18) << Medicine_Name

							 << left << setw(10) << availability

							 << endl;
					}
					cout << "\nThese are the medicine records found with the name " << Medicine_Name_Find << endl;
					Temp_Object.close();
					remove("Temp_File.txt");
					while (true)
					{
						if (while_state2 == 1)
						{
							break;
						}
						else
						{
							while_state2 = 0;
						}

						string check;
						cout << "\n******************************************************************************************************\n";
						cout << "*                                 Enter X to go back to main menu                                    *\n";
						cout << "*                     Enter Y to display details of medicines with name "<< Medicine_Name_Find<<"                            *\n";
						cout << "******************************************************************************************************\n";
						cin >> check;
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						if (exit_function(check) == 1)
						{
							while_state1 = 1;
							system("CLS");
							break;

						}
						else if (check == "Y" || check == "y")
						{
							system("CLS");
							Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
							Temp_Object.open("Temp_File.txt", ios::out);
							if (Medicine_textfile_Object.is_open())
							{
								while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
								{
									if (Medicine_Name == Medicine_Name_Find)
									{
										Temp_Object << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
									}
									else
									{
										// Do nothing
									}
								}
							}
							else
							{
								cout << "-----------------------------------------------------------------------------\n";
								cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
								cout << "-----------------------------------------------------------------------------\n";
								exit(0);
							}
							Medicine_textfile_Object.close();
							Temp_Object.close();

							cout << "\n\n";
							Temp_Object.open("Temp_File.txt", ios::in);
							cout << left << setw(16) << "Medicine ID"
								<< left << setw(22) << "Manufacturer Name"
								<< left << setw(18) << "Medicine Name"
								<< left << setw(10) << "Price"
								<< left << setw(15) << "DOM"
								<< left << setw(15) << "DOE"
								<< endl;
							if (Temp_Object.is_open())
							{
								while (Temp_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
								{
									cout << left << setw(16) << Medicine_ID

										<< left << setw(22) << Manufacturer_Name

										<< left << setw(18) << Medicine_Name

										<< left << setw(10) << string_price

										<< left << setw(15) << Manufacturing_Date

										<< left << setw(15) << Expiry_Date

										<< endl;
								}
								cout << "\nThese are the medicine details found with the name " << Medicine_Name_Find << endl;
								Temp_Object.close();
								remove("Temp_File.txt");
								while (true)
								{
									string check;
									cout << "\n*********************************************************************************************************\n";
									cout << "*                                 Enter X to go back to main menu                                       *\n";
									cout << "*                                 Enter Y to search for another medicine                                *\n";
									cout << "*********************************************************************************************************\n";
									cin >> check;
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									if (exit_function(check) == 1)
									{
										while_state2 = 1;
										while_state1 = 1;
										system("CLS");
										break;

									}
									else if (check == "Y" || check == "y")
									{
										while_state2 = 1;
										system("CLS");
										break;
									}
									else
									{
										cout << "-----------------------------------------------------------------------------\n";
										cout << "|                         Invalid Input! Try Again!                         |\n";
										cout << "-----------------------------------------------------------------------------\n";
									}
								}
							}

						}
						else
						{
							cout << "-----------------------------------------------------------------------------\n";
							cout << "|                         Invalid Input! Try Again!                         |\n";
							cout << "-----------------------------------------------------------------------------\n";
						}
					}
			

				}
				else
				{
					cout << "-----------------------------------------------------------------------------\n";
					cout << "|            Error in opening medicine detail file! Aborting Program...     |\n";
					cout << "-----------------------------------------------------------------------------\n";
					remove("Temp_File.txt");
					exit(0);
				}
			}
			else
			{

				cout << "\n----------------------------------------------------------------------------\n";
				cout << "|                         Name does not exist!                               |\n";
				cout << "-----------------------------------------------------------------------------\n\n";
			}
		}
	}
}
// This functions allows customer to buy any quantity of a selected medicine granted enough stock is present, after which their purchase details are saved into the system to be viewed later.
void buy_medicine(string username)
{
	
	system("CLS");
	fstream Medicine_textfile_Object;
	fstream Temp_Object;
	fstream Purchase_textfile_Object;
	string Medicine_Name, Manufacturer_Name, Medicine_ID, string_price, Medicine_ID_Purchase;
	string Manufacturing_Date = "", Expiry_Date = "";

	int available_stock, price, while_state1 = 0,while_state2 = 0,stock_purchase, stock_modified;
	cout << "*********************************************************************************************************\n";
	cout << "*                                     Ali's Medicine Pharmacy                                           *\n";
	cout << "*********************************************************************************************************\n";
	cout << "*                                       Medicine Records                                                *\n";
	cout << "*********************************************************************************************************\n\n";
	while (true)
	{	
		if (while_state1 == 1)
		{
			break;
		}
		else
		{
			while_state1 = 0;
			while_state2 = 0;
		}
		int check = 0;
		string Medicine_Name_Find;
		cout << endl;
		cout << "You can enter X to return to the main menu\n";
		cout << "\nEnter the Name of the medicine you would like to buy:- ";
		getline(cin, Medicine_Name_Find);
		if (exit_function(Medicine_Name_Find) == 1)
		{
			system("CLS");
			break;
		}
		else
		{
			Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
			Temp_Object.open("Temp_File.txt", ios::out);
			if (Medicine_textfile_Object.is_open())
			{
				while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
				{
					if (Medicine_Name == Medicine_Name_Find)
					{
						Temp_Object << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
						check += 1;
					}
					else
					{
						// Do nothing
					}
				}
			}
			else
			{
				cout << "-----------------------------------------------------------------------------\n";
				cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
				cout << "-----------------------------------------------------------------------------\n";
				exit(0);
			}
			Medicine_textfile_Object.close();
			Temp_Object.close();
			if (check > 0)
			{

				cout << "\n\n";
				Temp_Object.open("Temp_File.txt", ios::in);
				cout << left << setw(16) << "Medicine ID"
					<< left << setw(22) << "Manufacturer Name"
					<< left << setw(18) << "Medicine Name"
					<< left << setw(10) << "Price"
					<< left << setw(13) << "Availability"
					<< left << setw(15) << "DOM"
					<< left << setw(15) << "DOE"
					<< endl;
				if (Temp_Object.is_open())
				{
					while (Temp_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
					{
						string availability;
						if (available_stock > 0)
						{
							availability = "Available";
						}
						else
						{
							availability = "Unavailable";
						}
						cout << "\n";
						cout << left << setw(16) << Medicine_ID

							<< left << setw(22) << Manufacturer_Name

							<< left << setw(18) << Medicine_Name

							<< left << setw(10) << string_price

							<< left << setw(13) << availability

							<< left << setw(15) << Manufacturing_Date

							<< left << setw(15) << Expiry_Date

							<< endl;
					}
					cout << "\nThese are the medicine records found with the name " << Medicine_Name_Find << endl;
					Temp_Object.close();
					remove("Temp_File.txt");
					while (true)
					{
						if (while_state2 == 1)
						{
							break;
						}
						else
						{
							while_state2 = 0;
						}
						int check1 =0;				
						cout << "\n*********************************************************************************************************\n";
						cout << "*                                 Enter X to go back to main menu                                       *\n";
						cout << "*                         Enter the ID of the medicine to select it for purchase                        *\n";
						cout << "*********************************************************************************************************\n";
						getline(cin, Medicine_ID_Purchase);
						if (exit_function(Medicine_ID_Purchase) == 1)
						{
							while_state1 = 1;
							system("CLS");
							break;

						}
						else 
						{
							Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
							Temp_Object.open("Temp_File.txt", ios::out);
							if (Medicine_textfile_Object.is_open())
							{
								while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
								{
									if (Medicine_ID == Medicine_ID_Purchase)
									{
										Temp_Object << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
										check1 += 1;
									}
									else
									{
										// Do nothing
									}
								}
							}
							else
							{
								cout << "-----------------------------------------------------------------------------\n";
								cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
								cout << "-----------------------------------------------------------------------------\n";
								exit(0);
							}
							Medicine_textfile_Object.close();
							Temp_Object.close();
							if (check1 > 0)
							{
								while (true)
								{

									cout << "\n*********************************************************************************************************\n";
									cout << "*                                 Enter 0 to go back to ID selection                                    *\n";
									cout << "*                         Enter the quantiy of the medicine you wish to purchase                        *\n";
									cout << "*********************************************************************************************************\n";
									cin >> stock_purchase;
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									try
									{
										if (cin.fail())
										{
											system("CLS");
											throw 1;
										}
										else if (stock_purchase == 0)
										{
											system("CLS");
											throw 4;
										}
										else
										{
											
											Medicine_textfile_Object.open("Medicine_Details.txt", ios::in);
											Temp_Object.open("Temp_File.txt", ios::out);
											if (Medicine_textfile_Object.is_open())
											{
												while (Medicine_textfile_Object >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> available_stock >> Manufacturing_Date >> Expiry_Date)
												{
													if (Medicine_ID != Medicine_ID_Purchase)
													{
														Temp_Object << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << available_stock << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
													}
													else
													{
														stock_modified = available_stock - stock_purchase;
														if (stock_modified < 0)
														{
															cout << "-----------------------------------------------------------------------------\n";
															cout << "|                    Quantity exceeds available stock!                      |\n";
															cout << "-----------------------------------------------------------------------------\n";
															Medicine_textfile_Object.close();
															Temp_Object.close();
															remove("Temp_File.txt");
															throw 3;
														}
														else
														{
															Temp_Object << Medicine_ID << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << stock_modified << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
														}
														
													}
												}

											}
											else
											{
												system("CLS");
												cout << "-----------------------------------------------------------------------------\n";
												cout << "|           Error in opening medicine detail file! Aborting Program...      |\n";
												cout << "-----------------------------------------------------------------------------\n";
												exit(0);
											}
											Medicine_textfile_Object.close();
											Temp_Object.close();
											remove("Medicine_Details.txt");
											rename("Temp_File.txt", "Medicine_Details.txt");
											system("CLS");
											Purchase_textfile_Object.open("Purchase_History.txt", ios::app);
											if (Purchase_textfile_Object.is_open())
											{
												Purchase_textfile_Object << username << " " <<  Medicine_ID_Purchase << " " << Manufacturer_Name << " " << Medicine_Name << " " << string_price << " " << stock_purchase << " " << Manufacturing_Date << " " << Expiry_Date << "\n";
											}
											else
											{
												system("CLS");
												cout << "-----------------------------------------------------------------------------\n";
												cout << "|         Error in opening purchase history file! Aborting Program...       |\n";
												cout << "-----------------------------------------------------------------------------\n";
												exit(0);
											}
											
											int total_price = 0;
											
											string price;
											price = string_price.substr(2);										
											total_price = stoi(price);
											total_price = total_price * stock_purchase;
											string total_price1 = "RM" + to_string(total_price);
											cout << "|-----------------------------------------------------------------------------\n";
											cout << "|                           Here is your receipt!                             \n";
											cout << "|-----------------------------------------------------------------------------\n";
											cout << "| Medicine Name:-                  " << Medicine_Name << "                    \n";
											cout << "| Manufacturer Name:-              " << Manufacturer_Name << "                \n";
											cout << "| Price per unit of medicine:-     " << string_price << "                     \n";
											cout << "| Total Price:-                    " << total_price1 << "                      \n";
											cout << "| Quantity of medicine purchased:- " << stock_purchase << " units             \n";
											cout << "| Date of Expiry:-                 " << Expiry_Date << "                      \n";
											cout << "| Date of Manufacture:-            " << Manufacturing_Date << "               \n";
											cout << "|-----------------------------------------------------------------------------\n";

											while_state1 = 1;
											while_state2 = 1;
											break;
										}
									}
									catch (int err)
									{
										if (err ==  2)
										{
											cout << "\n-----------------------------------------------------------------------------\n";
											cout << "\n|       Invalid Stock entered! Please enter a value greater than 0          |\n";
											cout << "\n-----------------------------------------------------------------------------\n";
											cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

										}
										else if (err == 3)
										{
											//Restart Loop

										}
										else if (err == 1)
										{
											cout << "\n-----------------------------------------------------------------------------\n";
											cout << "\n|       Invalid Stock entered! Please enter a value greater than 0          |\n";
											cout << "\n-----------------------------------------------------------------------------\n";
											cin.clear();
											cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
										}								
										else
										{
											while_state2 = 1;
											break;
										}

									}
								}
							}
							else
							{
								cout << "\n----------------------------------------------------------------------------\n";
								cout << "|                         ID does not exist!                                |\n";
								cout << "-----------------------------------------------------------------------------\n\n";
							}
																						
						}
						
					}

				}
				else
				{
					cout << "-----------------------------------------------------------------------------\n";
					cout << "|            Error in opening medicine detail file! Aborting Program...     |\n";
					cout << "-----------------------------------------------------------------------------\n";
					remove("Temp_File.txt");
					exit(0);
				}
			}
			else
			{

				cout << "\n----------------------------------------------------------------------------\n";
				cout << "|                     Medicine does not exist!                               |\n";
				cout << "-----------------------------------------------------------------------------\n\n";
			}
		}
	}
}
// This funtion allows customer to view all past purchases they specifically made in the system
void view_past_purchases(string username)
{
	system("CLS");
	fstream Purchase_textfile_Object;
	string Medicine_Name, Manufacturer_Name, Medicine_ID, string_price;
	string Manufacturing_Date = "", Expiry_Date = "";
	string Username;
	int stock_purchase, price;
	Purchase_textfile_Object.open("Purchase_History.txt", ios::in);
	cout << "**********************************************************************************************************************************\n";
	cout << "*                                                 Ali's Medicine Pharmacy                                                        *\n";
	cout << "**********************************************************************************************************************************\n";
	cout << "*                                                   Medicine Records                                                             *\n";
	cout << "**********************************************************************************************************************************\n\n";
	cout << left << setw(13) << "Username"
		<< left << setw(16) << "Medicine ID"
		<< left << setw(22) << "Manufacturer Name"
		<< left << setw(18) << "Medicine Name"
		<< left << setw(10) << "Price"
		<< left << setw(23) << "Quantity Purchased"
		<< left << setw(15) << "DOM"
		<< left << setw(15) << "DOE"
		<< endl;
	if (Purchase_textfile_Object.is_open())
	{
		while (Purchase_textfile_Object >> Username >> Medicine_ID >> Manufacturer_Name >> Medicine_Name >> string_price >> stock_purchase >> Manufacturing_Date >> Expiry_Date)
		{
			if (Username == username)
			{
				cout << left << setw(13) << username

					<< left << setw(16) << Medicine_ID

					<< left << setw(22) << Manufacturer_Name

					<< left << setw(18) << Medicine_Name

					<< left << setw(10) << string_price

					<< left << setw(23) << stock_purchase

					<< left << setw(15) << Manufacturing_Date

					<< left << setw(15) << Expiry_Date

					<< endl << endl;
			}
			else
			{
				//Do nothing
			}
					
		}
	}
	Purchase_textfile_Object.close();
	while (true)
	{
		string check;
		cout << "**********************************************************************************************************************************\n";
		cout << "*                                               Enter X to go back to main menu                                                  *\n";
		cout << "**********************************************************************************************************************************\n";
		cin >> check;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (exit_function(check) == 1)
		{
			system("CLS");
			break;
		}
		else
		{
			cout << "-----------------------------------------------------------------------------\n";
			cout << "|                         Invalid Input! Try Again!                         |\n";
			cout << "-----------------------------------------------------------------------------\n";
		}
	}
}
//This function displays the menu a customer sees when they successfully login into the system
void customer_menu(string Username)
{
	system("CLS");
	while (true)
	{
		int while_state1 = 0;
		system("Color 0F");
		char choice;
		string string_choice;
		cout << "*****************************************************************************\n";
		cout << "*                          Ali's Medicine Pharmacy                          *\n";
		cout << "*****************************************************************************\n";
		cout << "*                                  Menu                                     *\n";
		cout << "*****************************************************************************\n";
		cout << "Welcome " << Username << "!                                                \n\n";
		cout << "*                                                                           *\n";
		cout << "*  |A| - Check if medicine is available and its details                     *\n";
		cout << "*                                                                           *\n";
		cout << "*  |B| - Buy Medicine                                                       *\n";
		cout << "*                                                                           *\n";
		cout << "*  |C| - View past purchases                                                *\n";
		cout << "*                                                                           *\n";
		cout << "*  |K| - Exit.                                                              *\n";
		cout << "*****************************************************************************\n";
		cout << endl;
		cout << "Enter your selection: ";
		getline(cin, string_choice);
		if (string_choice.length() == 1)
		{
			choice = string_choice.at(0);
			switch (choice)
			{
			case 'A':
			case 'a':
				medicine_availability();
				break;
			case 'B':
			case 'b':
				buy_medicine(Username);
				break;
			case 'C':
			case 'c':
				view_past_purchases(Username);
				break;			
			case 'K':
			case 'k':
				while_state1 = 1;
				break;
			default:
				system("CLS");
				cout << "\n\n-----------------------------------------------------------------------------\n";
				cout << "|              Invalid input! Please enter a correct input                  |\n";
				cout << "-----------------------------------------------------------------------------\n\n";
			}
			if (while_state1 == 1)
			{
				break;
			}
		}
		else
		{
			system("CLS");
			cout << "\n\n-----------------------------------------------------------------------------\n";
			cout << "|                 Please only enter a single character!                     |\n";
			cout << "-----------------------------------------------------------------------------\n\n";
		}
	}
}





void login_menu()
{
	while (true)
	{ 
		system("CLS");
		system("COLOR 0A");
		string Username, Password, Role;
		int count;
	
	
		cout << "*****************************************************************************\n";
		cout << "*                          Ali's Medicine Pharmacy                          *\n";
		cout << "*****************************************************************************\n";
		cout << "*            Welcome User! Please enter your credentials below:-            *\n";
		cout << "*****************************************************************************\n";
		cout << "Username:- ";
		cin >> Username;
		cout << "\nPassword:- ";
		cin >> Password;
		cout << "\nRole:- ";
		cin >> Role;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		count = login_verifier(Username, Password, Role);
		if (count == 1)
		{
			if (Role == "A")
			{
				admin_menu(Username);
			}
			else
			{
				customer_menu(Username);
			}
		}
		else
		{
			cout << "-----------------------------------------------------------------------------\n";
			cout << "|                 Incorrect login details! Try again!                       |\n";
			cout << "-----------------------------------------------------------------------------\n";

			system("pause");
			break;
			
		}

	}
	login_menu();
	

}


int main()
{
	login_menu();
}



