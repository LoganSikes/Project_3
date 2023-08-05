#include "song.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void Playlist::Insert(Song* song, const string& option, const string& adj, bool exp, int year, const string& artist){
    // check the if user specified arist, year of explicit content
    if ((!exp && song->exp) || (artist != "any" && artist != song->artist)){
        delete song;
        return;
    }

        // Check if the songs year is within the decade inserted by user
    else if (option == "decade") {
        int lower = ((song->year % 100) / 10) * 10;
        int upper = lower + 10;
        if (year%100 >= lower && year%100 <= upper) {
            song->rating = song->tempo;
            songs.push_back(song);
        }
    }

        // if mood or event type was selected
    else if (year == 0 || year == song->year) {
        if (option == "mood") {
            if (adj == "happy" && song->tempo >= 120 && song->tempo <= 140 && song->dance >= 70 && song->energy >= 50 &&  // high mid energy, valence, dance
                song->energy <= 90 && song->valence >= 70 && song->valence <= 90 && song->mode == 1 && song->loud >= -20) {
                // create rating relevant to playlist selection
                song->rating = song->tempo + song->dance + song->energy;
                // add song to playlist
                songs.push_back(song);
            } else if (adj == "sad" && song->tempo >= 50 && song->tempo <= 80 && song->energy <= 40 && song->dance <= 40 && // low energy, valence, dance
                       song->valence <= 40 && song->mode == 0 && song->loud <= -30) {
                song->rating = 180 - song->tempo + (100 - song->loud) + (100 - song->dance) + (100 - song->energy);
                songs.push_back(song);
            } else if (adj == "relaxed" && song->tempo >= 60 && song->tempo <= 90 && song->energy >= 10 && song->energy <= 50 && // low mid energy, valence, dance
                       song->dance <= 40 && song->loud >= -40 && song->loud <= -20 && song->valence >= 30 && song->valence <= 70 && song->mode == 0) {
                song->rating = 180 - song->tempo + (100 - song->loud) + (100 - song->dance) + (100 - song->energy);
                songs.push_back(song);
            } else if (adj == "victory" && song->tempo >= 120 && song->tempo <= 140 && song->valence >= 70 && song->energy >= 50 && // high energy, valence, dance
                       song->energy <= 90 && song->dance >= 70 && song->mode == 1 && song->loud >= -20) {
                song->rating = song->tempo + song->dance + song->energy;
                songs.push_back(song);
            } else if (adj == "angry" && song->tempo >= 130 && song->valence <= 60 && song->valence >= 30 && song->energy >= 50 && // high energy upbeat, aggressive
                       song->energy >= 70 && song->dance >= 70 && song->loud >= -10) {
                song->rating = song->tempo + song->dance+ song->energy + song->loud;
                songs.push_back(song);
            } else if (adj == "sleepy" && song->tempo >= 40 && song->tempo <= 70 && song->dance <= 30 && // low energy, valence, dance, soft
                       song->energy <= 30 && song->loud <= -30 && song->loud >= -60){
                song->rating = (180 - song->tempo) + (100 - song->dance) + (100 - song->energy);
                songs.push_back(song);
            }
        } else if (option == "event") {
            if (adj == "dinner" && song->tempo >= 50 && song->tempo <= 90 && song->dance <= 50 && song->energy >= 40 && song->loud >= -40 && song->loud <= -20) { // relaxed with more vibes
                song->rating = 180 - song->tempo + (100 - song->loud) + (100 - song->dance) + (100 - song->energy);
                songs.push_back(song);
            } else if (adj == "party" && song->tempo >= 120 && song->energy >= 80 && song->dance >= 80 && song->valence >= 80 && song->loud >= -20 && song->mode == 1) { // happier verison of happy
                song->rating = song->tempo + song->dance + song->energy;
                songs.push_back(song);
            } else if (adj == "workout" && song->tempo >= 130 && song->tempo <= 150 && song->valence >= 50 && song->valence <= 90 &&  // softer angry
                       song->energy >= 70 && song->dance >= 50 && song->dance <= 90 && song->loud >= -10 && song->mode == 1) {
                song->rating = song->tempo + song->dance + song->energy  + song->loud ;
                songs.push_back(song);
            } else if (adj == "after party" && song->tempo >= 90 && song->tempo <= 120 && song->dance >= 50 && song->dance <= 80 && // fun happy party but a little relaxed
                       song->energy <= 80 && song->energy >= 40 && song->valence >= 30 && song->valence <= 80 && song->loud >= -20) {
                song->rating = song->tempo + song->dance + song->energy ;
                songs.push_back(song);
            }
            else if (adj == "studying" && song->tempo <= 100 && song->tempo >= 60 && song->dance <= 40 && song->dance >= 10 && // more fun sleeping
                     song->energy >= 10 && song->energy <= 50 && song->loud >= -40 && song->loud <= -20){
                song->rating = (180 - song->tempo) + (100 - song->dance) + (100 - song->energy);
                songs.push_back(song);
            }
        } else if (option == "artist") { // check if user selected artist
            song->rating = song->tempo;
            songs.push_back(song);
        }
    }
        // if song is not applicable
    else
        delete song;
}

void Playlist::PrintAll(){
    if (songs.empty()){
        cout << "Sorry! No applicable songs :(" << endl << endl;
        return;
    }
    cout << "Your playlist has " << songs.size() << " songs!" << endl << endl;
    for (const auto& i : songs){
        cout << "Title: " << i->name << endl;
        cout << "Artist: " << i->artist << endl;
        cout << "Album: " << i->album << endl << endl;
    }

}

void Playlist::PrintN(int n){
    if (songs.empty()){
        cout << "Sorry! No applicable songs :(" << endl << endl;
        return;
    }
    if (n > songs.size()){
        cout << "Your playlist has " << songs.size() << " songs!" << endl;

        for (int i = songs.size() - 1; i > 0; i--) {
            cout << "Title: " << songs[i]->name << endl;
            cout << "Artist: " << songs[i]->artist << endl;
            cout << "Album: " << songs[i]->album << endl << endl;
        }
    }
        
    // n is less than size
    else{
        cout << "Your playlist has " << n << " songs!" << endl;
        for (int i = songs.size() - 1; i > songs.size() - 1 - n; i--){
            cout << "Title: " << songs[i]->name << endl;
            cout << "Artist: " << songs[i]->artist << endl;
            cout << "Album: " << songs[i]->album << endl << endl;
        }
    }
}

void Song::Deserialize(istringstream& stream) {
    string token;
    getline(stream, token, ','); // ignore id

    getline(stream, name, ','); // get name
    if (name[0] == '\"'){
        while (name[name.size() - 1] != '\"'){   // check if contains commas
            getline(stream, token, ',');
            name += ',' + token;
        }
        while (name[0] == '\'' || name[0] == '\"')
            name.erase(0, 1);
        while (name[name.size() - 1] == '\'' || name[name.size() - 1] == '\"')
            name.erase(name.size() - 1, 1);
    }

    getline(stream, album, ',');        // get album
    if (album[0] == '\"'){
        while (album[album.size() - 1] != '\"'){   // check if contains commas
            getline(stream, token, ',');
            album += ',' + token;
        }
        while (album[0] == '\'' || album[0] == '\"')
            album.erase(0, 1);
        while (album[album.size() - 1] == '\'' || album[album.size() - 1] == '\"')
            album.erase(album.size() - 1, 1);
    }

    getline(stream, token, ','); // ignore album id
    while (!isdigit(token[0]))
        getline(stream, token, ',');

    getline(stream, artist, ','); // get artist
    if (artist[0] == '\"'){
        artist.erase(0, 1);
        while(artist[artist.size() - 1] == '\'')
            artist.erase(artist.size() - 1,1);
        while (artist[artist.size() - 1] != '\"'){
            getline(stream, token, ',');
            if (token[token.size() - 2] == ']')
                break;
            while(token[0] == '\'')
                token.erase(0,1);
            while(token[1] == '\'')
                token.erase(1,1);
            while(token[token.size() - 1] == '\'')
                token.erase(token.size() - 1,1);
            artist += "," + token;
        }
    }

    while (artist[0] == '\'' || artist[0] == '\"' || artist[0] == '[')
        artist.erase(0, 1);
    while (artist[artist.size() - 1] == '\'' || artist[artist.size() - 1] == '\"' || artist[artist.size() - 1] == ']')
        artist.erase(artist.size() - 1, 1);

    cout << artist;
    getline(stream, token, ','); // ignore artist id

    getline(stream, token, ','); // ignore track num
    while (!isdigit(token[0]))
        getline(stream, token, ',');

    getline(stream, token, ','); // ignore disk num

    getline(stream, token, ','); // get if explicit

    if (token.size() == 4){
        this->exp = true;
    }
    else
        this->exp = false;

    getline(stream, token, ','); // get danceability


    dance = int(stod(token) * 100);

    getline(stream, token, ','); // get energy

    energy = int(stod(token) * 100);


    getline(stream, token, ','); // get key

    key = stoi(token);


    getline(stream, token, ','); // get loudness

    loud = stoi(token);

    getline(stream, token, ','); // get mode

    mode = stoi(token);


    getline(stream, token, ','); // ignore speechiness

    getline(stream, token, ','); // ingore acousticness

    getline(stream, token, ','); // ignore instrumental

    getline(stream, token, ','); // ignore liveness

    getline(stream, token, ','); // get valence

    valence = int(stod(token) * 100);

    getline(stream, token, ','); // get tempo

    tempo = stoi(token);

    getline(stream, token, ','); // ignore duration
    // ignore duration

    getline(stream, token, ','); // ignore time signiture

    getline(stream, token, ',');    // get year
    year = stoi(token);

    getline(stream, token, ','); // ignore release date
}

void Playlist::Clear(){
    for (auto& i : songs){
        delete i;
    }
}

Playlist::~Playlist() {
}
