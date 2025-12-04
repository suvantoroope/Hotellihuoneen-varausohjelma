//Roope Suvanto
//Hotellihuoneen varausjärjestelmä
// 4 pisteen ohjelma


#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib> 
#include <limits>
#include <string>

using namespace std;

// Määritellään hotellihuoneen rakenne
struct hotelRoom {
    int roomNumber;
    int roomType;
    double pricePerNight;
    bool isBooked;
    string guestName;
    int reservationNumber;
};

// Alustetaan hotellihuoneet
void initializeRooms(vector<hotelRoom>& rooms, int numberOfRooms) {
    for (int i = 1; i <= numberOfRooms; ++i) {
        
        // Luodaan uusi huone
        hotelRoom h;

        // Asetetaan huoneen tiedot
        h.roomNumber = i;
        h.isBooked = false;
        // Puolitetaan huoneet yksittäisiin ja kaksittäisiin
        if (i <= numberOfRooms / 2) {
            h.roomType = 1;
            h.pricePerNight = 100.0;
        }
        else {
            h.roomType = 2;
            h.pricePerNight = 150.0;
        }
        // Lisätään huone vektoriin
        rooms.push_back(h);
    }
    // Tulostetaan huoneiden määrä
    int half = numberOfRooms / 2;
    cout << "Hotel initalized with " << numberOfRooms << " rooms." << endl;
    cout << half << " Singles and " << half << " Doubles." << endl;
}

// Syötteen tarkitus
int checkInput() {
    int input;
    // Jatketaan, kunnes saadaan kelvollinen syöte
    while (true) {
        if (cin >> input) {
            // Palautetaan kelvollinen syöte
            return input;
        }
        // Käsitellään virheellinen syöte
        else {
            cout << "Invalid input. Please use numbers only" << endl;
            // Tyhjennetään syötevirhe
            cin.clear();
            // Ohitetaan virheellinen syöte
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }




int main() {

    // Alustetaan satunnaislukugeneraattori
    srand(time(0));

    // Määritellään huoneiden määrä välillä 40-200
    int numberOfRooms = 40 + rand() % 161;

    // Varmistetaan, että huoneiden määrä on parillinen
    if(numberOfRooms % 2 != 0) {
        numberOfRooms++;
    }

    // Luodaan vektori hotellihuoneille
    vector<hotelRoom> rooms;

    // Kutsutaan funktiota huoneiden alustamiseksi
    initializeRooms(rooms, numberOfRooms);

    // Pääsilmukka
    while (true) {

        // Näytetään valikko
        cout << "\nHotel Room Booking System" << endl;
        cout << "1. Book a Room" << endl;
        cout << "2. Exit" << endl;
        cout << "Select option: ";
      
        // Luetaan käyttäjän valinta
        int option = checkInput();


        if (option == 1) {
            // Kysytään huonetyyppiä
            cout << "\nChoose room type:" << endl;
            cout << "1. Single (100e/night)" << endl;
            cout << "2. Double (150e/night)" << endl;
            
            // Luetaan huonetyyppi
            int type = checkInput();

            // Etsitään vapaat huoneet
            vector<int> availableRooms;
            
            // Käydään huoneet läpi
            for (int i = 0; i < rooms.size(); ++i) {
                if (rooms[i].roomType == type && rooms[i].isBooked == false) {
                    availableRooms.push_back(i);
                }
            }

            // Näytetään tulos
            if (availableRooms.size() == 0) {
                cout << "No available rooms of selected type." << endl;
                // Jos huoneita ei ole, palataan valikkoon    
                } 
                
                else {
                        // Näytetään saatavilla olevien huoneiden määrä
                    cout << "Found " << availableRooms.size() << " available rooms." << endl;
                    int randomIndex = rand() % availableRooms.size();
                    int chosenRoomIndex = availableRooms[randomIndex];
                    
                    // Kysytään yöpymisten määrä
                    cout << "\nHow many nights would you like to stay? ";
                    int nights = checkInput();

                    //Kysytään varaajan nimi
                    cout << "Whose name is the reservetion under? ";
                    cin.ignore();
                    string name;
                    getline(cin, name);

                    // Luodaan satunnainen varausnumero väliltä 10000-99999
                    int reservationNumber = 10000 + rand() % 90000;

                    // Lasketaan kokonaishinta
                    double totalPrice = rooms[chosenRoomIndex].pricePerNight * nights;

                    // Merkitään huone varatuksi
                    rooms[chosenRoomIndex].isBooked = true;
                    rooms[chosenRoomIndex].guestName = name;
                    rooms[chosenRoomIndex].reservationNumber = reservationNumber;

                    // Näytetään varausvahvistus
                    cout << "\nBooking Confirmation" << endl;
                    cout << "Reservation Number: " << reservationNumber << endl;
                    cout << "Guest Name: " << name << endl;
                    cout << "Room Number: " << rooms[chosenRoomIndex].roomNumber << endl;
                    cout << "Room Type: " << (rooms[chosenRoomIndex].roomType  == 1 ? "Single" : "Double") << endl;
                    cout << "Nights: " << nights << endl;
                    cout << "Total Price: " << totalPrice << "e" << endl;
                }
        }


        // Käsitellään poistuminen
        else if (option == 2) {
            cout << "Goodbye!" << endl;
            break;
        }
    }

    return 0;
    }       
