#include <iostream>
#include <vector>
#include <string>
#include <fstream>
const std::string filename = "Contacts.txt";

class Contact
{
private:
    typedef struct
    {
        std::string name;
        std::string number;
        std::string email;
    } contact_info;

    std::vector<contact_info> Contacts_vect;

public:
    void AddContact(void)
    {
        std::string temp;
        contact_info new_contact;
        std::cout << "Enter contact name: " << std::endl;
        std::getline(std::cin, temp);
        new_contact.name = temp;
        temp.clear();
        std::cout << "Enter contact number: " << std::endl;
        std::getline(std::cin, temp);
        new_contact.number = temp;
        temp.clear();
        std::cout << "Enter contact email: " << std::endl;
        std::getline(std::cin, temp);
        new_contact.email = temp;
        temp.clear();
        Contacts_vect.push_back(new_contact);
        std::cout << "Contact Added!" << std::endl;
        ViewContact();
    }

    void ViewContact(void)
    {
        int size = Contacts_vect.size();
        int i = 0;
        if (size)
        {
            for (i; i < size; i++)
            {
                std::cout << "Contact Name: " << Contacts_vect[i].name << std::endl;
                std::cout << "Contact Number: " << Contacts_vect[i].number << std::endl;
                std::cout << "Contact email: " << Contacts_vect[i].email << std::endl;
            }
        }
        else
        {
            std::cout << "No Contacts to view!" << std::endl;
        }
    }

    void DeleteContact()
    {
        std::string temp;
        char exists = 0;
        std::cout << "Enter contact name to delete: " << std::endl;
        std::getline(std::cin, temp);
        int i = 0;
        int size = Contacts_vect.size();
        for (i; i < size; i++)
        {
            if (Contacts_vect[i].name == temp)
            {
                exists = 1;
                temp.clear();
                Contacts_vect.erase(Contacts_vect.begin() + i);
                std::cout << "Contact Deleted!" << std::endl;
            }
        }
        if (exists == 0)
        {
            std::cout << "No contact with such name!" << std::endl;
        }
    }

    void EditContact()
    {
        std::string temp;
        char exists = 0;
        std::cout << "Enter contact name to edit: " << std::endl;
        std::getline(std::cin, temp);
        int i = 0;
        int size = Contacts_vect.size();
        for (i; i < size; i++)
        {
            if (Contacts_vect[i].name == temp)
            {
                exists = 1;
                temp.clear();
                std::cout << "Enter new name (leave blank if don't want to change): " << std::endl;
                std::getline(std::cin, temp);
                if (!temp.empty())
                {
                    Contacts_vect[i].name = temp;
                    temp.clear();
                }

                std::cout << "Enter new number (leave blank if don't want to change): " << std::endl;
                std::getline(std::cin, temp);
                if (!temp.empty())
                {
                    Contacts_vect[i].number = temp;
                    temp.clear();
                }

                std::cout << "Enter new  email (leave blank if don't want to change): " << std::endl;
                std::getline(std::cin, temp);
                if (!temp.empty())
                {
                    Contacts_vect[i].email = temp;
                    temp.clear();
                }
            }
        }
        if (exists == 0)
        {
            std::cout << "No contact with such name!" << std::endl;
        }
        else
        {
            std::cout << "Contact Edited!" << std::endl;
            ViewContact();
        }
    }

    void SaveContactsToFile(void)
    {
        std::ofstream outfile(filename);
        for (const contact_info &contact : Contacts_vect)
        {
            outfile << contact.name << std::endl;
            outfile << contact.number << std::endl;
            outfile << contact.email << std::endl;
        }

        outfile.close();

        std::cout << "Contacts saved to file: " << filename << std::endl;
    }

    void LoadContactsFromFile(void)
    {
        std::ifstream infile(filename);
        Contacts_vect.clear();
        while (!infile.eof())
        {
            contact_info newContact;

            std::getline(infile, newContact.name);
            std::getline(infile, newContact.number);
            std::getline(infile, newContact.email);

            if (!infile.fail())
            {
                Contacts_vect.push_back(newContact);
            }
        }
        std::cout << "Contacts loaded from file: " << filename << std::endl;
    }
};

int main()
{
    bool loop = 1;
    char User_selection;
    Contact C1;
    C1.LoadContactsFromFile();
    while (loop)
    {
        std::cout << "Choose an option." << std::endl;
        std::cout << "1. Add Contact" << std::endl;
        std::cout << "2. View Contact" << std::endl;
        std::cout << "3. Edit Contact" << std::endl;
        std::cout << "4. Delete Contact" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cin >> User_selection;
        std::cin.ignore();
        switch (User_selection)
        {
        case '1':
            C1.AddContact();
            break;

        case '2':
            C1.ViewContact();
            break;

        case '3':
            C1.EditContact();
            break;

        case '4':
            C1.DeleteContact();
            break;

        case '5':
            loop = 0;
            break;
        }
    }
    C1.SaveContactsToFile();

    return 0;
}
